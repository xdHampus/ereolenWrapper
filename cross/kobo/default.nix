# libereolenwrapper.so for Kobo e-readers, as a Nix output.
#
# Same recipe as build.sh, with the downloads turned into fixed-output
# derivations so the build itself runs offline and reproducibly. Everything is
# pinned in the files beside this one; see README.md for why each choice is
# what it is.
#
#   nix build .#kobo
#
# What comes out is one stripped ARM shared library, to be dropped next to the
# plugin's Lua at:
#   /mnt/onboard/.adds/koreader/plugins/ereolen.koplugin/libereolenwrapper.so
{ lib
, stdenvNoCC
, callPackage
, cmake
, symlinkJoin
, lua5_1
, nlohmann_json
, luabridge
, src ? lib.cleanSourceWith {
    name = "ereolenWrapper-source";
    src = ../..;
    # Keep build.sh's scratch directory out of the store: it holds ~300 MB of
    # downloads and an extracted toolchain.
    filter = path: type:
      let rel = lib.removePrefix (toString ../.. + "/") (toString path);
      in !(lib.hasPrefix "cross/kobo/work" rel);
  }
}:

let
  toolchainFile = ./kobo.cmake;
  triple = "arm-kobo-linux-gnueabihf";

  koboToolchain = callPackage ./toolchain.nix { };
  libresslSdk = callPackage ./libressl-sdk.nix { };
  koboCurl = callPackage ./curl.nix { inherit koboToolchain libresslSdk; };
  koboCpr = callPackage ./cpr.nix { inherit koboToolchain koboCurl toolchainFile; };

  # kobo.cmake points CMAKE_FIND_ROOT_PATH at exactly one prefix, and
  # FIND_ROOT_PATH_MODE_PACKAGE is ONLY, so everything findable has to live
  # under a single root. The three header-only dependencies are architecture
  # independent, so the ordinary native nixpkgs outputs are correct here.
  koboPrefix = symlinkJoin {
    name = "kobo-prefix";
    paths = [ koboCurl koboCpr nlohmann_json lua5_1 luabridge ];
  };

  # What the device can actually resolve. The Libra H2O runs glibc 2.19; the
  # C++ runtime is whatever KOReader ships, currently GLIBCXX 3.4.33 and
  # CXXABI 1.3.15. Linking something newer compiles cleanly and then fails at
  # dlopen time on the device, which is a slow way to find out.
  abiCeiling = {
    GLIBC = "2.19";
    GLIBCXX = "3.4.33";
    CXXABI = "1.3.15";
  };
in
stdenvNoCC.mkDerivation {
  pname = "ereolenwrapper-kobo";
  version = "0.1.0";

  inherit src;

  nativeBuildInputs = [ cmake koboToolchain koboCurl ];

  KOBO_TC = koboToolchain;
  KOBO_PREFIX = koboPrefix;

  # Release, which is the setup hook's default and is left alone deliberately.
  # The top-level CMakeLists defines CMAKE_CXX_FLAGS_RELEASE as "-O2" and falls
  # back to Release when no build type is given, so this reproduces exactly
  # what build.sh compiles the wrapper with: -Wall -Wextra -O2 -std=gnu++20
  # -fPIC. Setting "None" instead looks tidier and silently gets -O0, because
  # the project only sets flags for the Release and Debug configurations.

  cmakeFlags = [
    "-DCMAKE_TOOLCHAIN_FILE=${toolchainFile}"
    "-DENABLE_LUA=ON"
    # KOReader's LuaJIT provides the Lua symbols in-process; linking a second
    # Lua into the module would give it two of everything.
    "-DENABLE_LUA_LINK=OFF"
    "-DENABLE_TESTING=OFF"
    "-DENABLE_INSTALL=OFF"
    "-DCMAKE_PREFIX_PATH=${koboPrefix}"
    "-DLUA_INCLUDE_DIR=${koboPrefix}/include"
    "-DLUABRIDGE_INCLUDE_DIRS=${koboPrefix}/include"
  ];

  # Anything with a space in it has to go through cmakeFlagsArray: entries of
  # cmakeFlags are word-split by the setup hook, which would hand cmake a bare
  # "-lcrypto" and make it exit with "Unknown argument".
  preConfigure = ''
    cmakeFlagsArray+=(
      "-DCMAKE_CXX_FLAGS=-Wall -Wextra -DCURL_STATICLIB"
      # libcurl.a is processed after -lssl/-lcrypto, so with the default
      # --as-needed the linker has not yet seen the SSL references and drops
      # both from DT_NEEDED; the module then fails to load on the device.
      "-DCMAKE_SHARED_LINKER_FLAGS=-L${libresslSdk}/lib -Wl,--no-as-needed -lssl -lcrypto"
    )
  '';

  # Worth having in the log: the flags are assembled from a toolchain file, the
  # setup hook and the project's own CMakeLists, and the answer is not obvious
  # from any one of them.
  postConfigure = ''
    grep '^CXX_FLAGS' src/main/CMakeFiles/ereolenwrapper.dir/flags.make
  '';

  installPhase = ''
    runHook preInstall
    mkdir -p "$out/lib"
    cp src/main/libereolenwrapper.so "$out/lib/"
    ${koboToolchain}/bin/${triple}-strip "$out/lib/libereolenwrapper.so"
    runHook postInstall
  '';

  # Host tools must not touch an ARM object.
  dontStrip = true;
  dontPatchELF = true;

  doInstallCheck = true;
  installCheckPhase = ''
    runHook preInstallCheck
    so="$out/lib/libereolenwrapper.so"
    readelf="${koboToolchain}/bin/${triple}-readelf"

    # Everything below reads readelf's output from a file rather than a pipe:
    # the stdenv sets `set -o pipefail`, so a `grep -q` that quits early kills
    # readelf with SIGPIPE and fails the pipeline regardless of what it found.
    $readelf -h "$so" > header.txt
    grep -q 'Machine:.*ARM' header.txt || { echo "not an ARM object"; exit 1; }

    $readelf -d "$so" > dynamic.txt
    echo "--- DT_NEEDED:"
    grep NEEDED dynamic.txt
    for want in libssl.so.60 libcrypto.so.57; do
      grep -q "$want" dynamic.txt \
        || { echo "$want missing from DT_NEEDED -- --no-as-needed lost it"; exit 1; }
    done

    # The check that matters: nothing may require a symbol version newer than
    # what the device has.
    echo "--- highest symbol version required per family:"
    $readelf -V "$so" > versions.txt 2>/dev/null
    fail=0
    check() {
      local family="$1" ceiling="$2" got
      got=$(grep -oE "\b''${family}_[0-9.]+" versions.txt | sed "s/''${family}_//" \
              | sort -u -V | tail -1)
      if [ -z "$got" ]; then
        echo "  $family: (none required)"
        return
      fi
      echo "  $family: needs $got, device has $ceiling"
      if [ "$(printf '%s\n%s\n' "$got" "$ceiling" | sort -V | tail -1)" != "$ceiling" ]; then
        echo "  ^ too new for the device"
        fail=1
      fi
    }
    check GLIBC   "${abiCeiling.GLIBC}"
    check GLIBCXX "${abiCeiling.GLIBCXX}"
    check CXXABI  "${abiCeiling.CXXABI}"
    [ "$fail" -eq 0 ] || exit 1

    # The Lua entry point KOReader's require() will look for.
    $readelf --dyn-syms -W "$so" > dynsyms.txt
    grep -q 'luaopen_libereolenwrapper' dynsyms.txt \
      || { echo "luaopen_libereolenwrapper not exported"; exit 1; }
    runHook postInstallCheck
  '';

  passthru = { inherit koboToolchain libresslSdk koboCurl koboCpr koboPrefix; };

  meta = with lib; {
    description = "libereolenwrapper.so cross-built for Kobo e-readers (KOReader Lua C module)";
    homepage = "https://github.com/xdHampus/ereolenWrapper";
    license = licenses.lgpl3Plus;
    platforms = [ "x86_64-linux" ];
  };
}
