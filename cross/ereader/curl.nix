# libcurl for e-readers: static, PIC, LibreSSL.
#
# Static because the device has no libcurl at all and shipping another .so
# beside the plugin means another thing to keep in step. PIC because the result
# gets linked into a shared library, and without -fPIC the ARM link fails on
# R_ARM_THM_MOVW_ABS_NC relocations.
#
# The CA bundle path is baked in at configure time. libcurl ignores
# $CURL_CA_BUNDLE -- that is a feature of the curl command-line tool, not the
# library -- so this default is the only one a build gets. It is just a
# fallback: the plugin calls ereol.ApiEnv.setCaBundle() with the path it
# actually found at runtime.
{ stdenvNoCC, lib, fetchurl, toolchain, libresslSdk
, caBundle ? "/mnt/onboard/.adds/koreader/data/ca-bundle.crt"
, target ? "kobo"
, triple ? "arm-kobo-linux-gnueabihf"
, archFlags ? "-march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard"
}:

stdenvNoCC.mkDerivation rec {
  pname = "curl-${target}";
  version = "8.21.0";

  src = fetchurl {
    url = "https://curl.se/download/curl-${version}.tar.xz";
    hash = "sha256-qhtmpw6s6D3GJFCHRWRsCK5WHeUSq0A63/uTrIf8cuY=";
  };

  nativeBuildInputs = [ toolchain ];

  # stdenv's own cross handling is not in play here: the compiler comes from
  # koxtoolchain, not from a nixpkgs cross stdenv, so --host is ours to pass.
  configurePlatforms = [ ];

  configureFlags = [
    "--host=${triple}"
    "--with-openssl=${libresslSdk}"
    "--with-pic"
    "--with-ca-bundle=${caBundle}"
    "--disable-shared"
    "--enable-static"
    # Nothing here needs them, and each one would be another ARM build.
    "--without-zlib"
    "--without-brotli"
    "--without-zstd"
    "--without-libpsl"
    "--without-nghttp2"
    "--without-libidn2"
    "--without-librtmp"
    "--disable-ldap"
    "--disable-ldaps"
    "--disable-manual"
    "--disable-docs"
  ];

  env.CFLAGS = "-O2 -fPIC ${archFlags}";

  # Only the library is wanted; building src/ would also build the curl binary.
  buildPhase = ''
    runHook preBuild
    make -j"$NIX_BUILD_CORES" -C lib
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    make -C lib install
    make -C include install
    mkdir -p "$out/lib/pkgconfig" "$out/bin"
    # `make -C lib install` installs neither of these. curl-config matters:
    # CMake's FindCURL learns which protocols libcurl supports by running it,
    # and cpr asks for the HTTP component, so without it cpr's configure fails
    # with "Could NOT find CURL (missing: HTTP)" despite finding the library.
    cp libcurl.pc "$out/lib/pkgconfig/"
    install -m 755 curl-config "$out/bin/"
    runHook postInstall
  '';

  dontStrip = true;
  dontPatchELF = true;

  doInstallCheck = true;
  installCheckPhase = ''
    runHook preInstallCheck
    test -f "$out/lib/libcurl.a"
    "$out/bin/curl-config" --protocols > protocols.txt
    grep -qx HTTPS protocols.txt || { echo "libcurl built without HTTPS"; exit 1; }
    # A stray host build would be caught here. Note the file rather than a pipe:
    # the stdenv runs with `set -o pipefail`, and `grep -q` closing the pipe
    # early makes readelf die of SIGPIPE, failing the whole pipeline.
    ${toolchain}/bin/${triple}-readelf -h \
      "$out/lib/libcurl.a" > headers.txt 2>/dev/null
    grep -q 'Machine:.*ARM' headers.txt || { echo "libcurl.a is not ARM"; exit 1; }
    runHook postInstallCheck
  '';

  meta = with lib; {
    description = "Static PIC libcurl for ${triple}, against KOReader's LibreSSL";
    homepage = "https://curl.se";
    license = licenses.curl;
    platforms = [ "x86_64-linux" ];
  };
}
