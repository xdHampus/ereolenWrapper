# cpr, the C++ HTTP wrapper the library actually calls, built static for ARM.
#
# CPR_ENABLE_SSL is off because cpr would otherwise go looking for OpenSSL to
# configure its own SSL backend; the TLS here belongs to libcurl, which is
# already wired to KOReader's LibreSSL. CURL_STATICLIB has to be defined for
# every translation unit that sees curl.h, or the headers declare the symbols
# dllimport-style and the link fails.
{ stdenvNoCC, lib, fetchurl, cmake, koboToolchain, koboCurl, toolchainFile }:

stdenvNoCC.mkDerivation rec {
  pname = "cpr-kobo";
  version = "1.14.2";

  src = fetchurl {
    url = "https://github.com/libcpr/cpr/archive/refs/tags/${version}.tar.gz";
    hash = "sha256-ubUptHCDv+gLuoVcpTCNEtdnrnx7YprvXvAYxDQ89is=";
  };

  # koboCurl is here for its bin/curl-config, which FindCURL runs.
  nativeBuildInputs = [ cmake koboToolchain koboCurl ];

  KOBO_TC = koboToolchain;
  KOBO_PREFIX = koboCurl;

  cmakeFlags = [
    "-DCMAKE_TOOLCHAIN_FILE=${toolchainFile}"
    "-DCPR_USE_SYSTEM_CURL=ON"
    "-DCPR_BUILD_TESTS=OFF"
    "-DCPR_ENABLE_SSL=OFF"
    "-DBUILD_SHARED_LIBS=OFF"
    "-DCMAKE_POSITION_INDEPENDENT_CODE=ON"
    "-DCMAKE_C_FLAGS=-DCURL_STATICLIB"
    "-DCMAKE_CXX_FLAGS=-DCURL_STATICLIB"
  ];

  dontStrip = true;
  dontPatchELF = true;

  doInstallCheck = true;
  installCheckPhase = ''
    runHook preInstallCheck
    test -f "$out/lib/libcpr.a"
    # Via a file, not a pipe: see the note in curl.nix about pipefail + SIGPIPE.
    ${koboToolchain}/bin/arm-kobo-linux-gnueabihf-readelf -h \
      "$out/lib/libcpr.a" > headers.txt 2>/dev/null
    grep -q 'Machine:.*ARM' headers.txt || { echo "libcpr.a is not ARM"; exit 1; }
    runHook postInstallCheck
  '';

  meta = with lib; {
    description = "Static cpr for arm-kobo-linux-gnueabihf";
    homepage = "https://github.com/libcpr/cpr";
    license = licenses.mit;
    platforms = [ "x86_64-linux" ];
  };
}
