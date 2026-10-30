# koxtoolchain's prebuilt e-reader cross-toolchains, made runnable under Nix.
#
# This is a binary release, not something we build: crosstool-ng needs network
# access and hours of CPU to produce a GCC, and the whole point of pinning
# koxtoolchain is that the KOReader project already did that and everyone
# targeting a Kobo uses the result.
#
# Its 52 host binaries expect a normal FHS box -- /lib64/ld-linux-x86-64.so.2
# and libc, libm, libgcc_s, libstdc++ from /usr/lib -- none of which exist
# inside a Nix build. autoPatchelfHook rewrites their interpreter and RPATH.
#
# The ARM side (sysroot, target libs) must come through untouched: those are
# the artefacts we are cross-compiling against, and patching or stripping them
# with host tools would wreck them. autoPatchelf skips non-native ELFs by
# architecture, and dontStrip keeps the generic fixup away from them; the
# installCheck below is what actually proves both.
{ stdenv, lib, fetchurl, autoPatchelfHook
, target ? "kobo"
, triple ? "arm-kobo-linux-gnueabihf"
, toolchainHash ? "sha256-urE2gUgmMIvRou3vrH1QxPxDkKR6oCq/Y21t6uHaHyQ="
}:

stdenv.mkDerivation rec {
  pname = "koxtoolchain-${target}";
  version = "2025.05";

  src = fetchurl {
    url = "https://github.com/koreader/koxtoolchain/releases/download/${version}/${target}.tar.gz";
    hash = toolchainHash;
  };

  sourceRoot = "x-tools/${triple}";

  nativeBuildInputs = [ autoPatchelfHook ];
  buildInputs = [ stdenv.cc.cc.lib ];

  dontStrip = true;
  dontConfigure = true;
  dontBuild = true;

  installPhase = ''
    runHook preInstall
    mkdir -p "$out"
    cp -a . "$out/"
    # The tarball ships read-only directories, which makes later phases fail.
    chmod -R u+w "$out"
    runHook postInstall
  '';

  doInstallCheck = true;
  installCheckPhase = ''
    runHook preInstallCheck
    echo "--- host driver runs:"
    "$out/bin/${triple}-gcc" --version | head -1
    echo "--- and can actually compile and link for ARM:"
    echo 'int f(int x){return x+1;}' > probe.c
    "$out/bin/${triple}-gcc" -shared -fPIC -o probe.so probe.c
    "$out/bin/${triple}-readelf" -h probe.so | grep -q 'Machine:.*ARM'
    echo "--- target sysroot left alone:"
    "$out/bin/${triple}-readelf" -h \
      "$out/${triple}/sysroot/lib/libc.so.6" | grep -q 'Machine:.*ARM'
    runHook postInstallCheck
  '';

  meta = with lib; {
    description = "Prebuilt ${triple} toolchain from koreader/koxtoolchain";
    homepage = "https://github.com/koreader/koxtoolchain";
    license = licenses.gpl3Plus;
    platforms = [ "x86_64-linux" ];
    # Upstream ships binaries; there is no source build here.
    sourceProvenance = with sourceTypes; [ binaryNativeCode ];
  };
}
