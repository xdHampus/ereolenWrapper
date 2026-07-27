# A link target for LibreSSL that matches what the device actually runs.
#
# KOReader ships its own LibreSSL (libssl.so.60 / libcrypto.so.57) and the Kobo
# has no system OpenSSL, so those are the libraries our .so will resolve against
# at runtime. Linking against any other build would compile fine and then fail
# to find symbols on the device.
#
# The .so files come out of the KOReader release; the headers come from the
# matching upstream LibreSSL tarball, because a release zip carries no headers.
# Both versions are pinned together and must stay in step.
{ stdenvNoCC, lib, fetchurl, unzip }:

let
  libresslVersion = "4.2.1";
  koreaderVersion = "v2026.03";
in
stdenvNoCC.mkDerivation {
  pname = "kobo-libressl-sdk";
  version = libresslVersion;

  srcs = [
    (fetchurl {
      url = "https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-${libresslVersion}.tar.gz";
      hash = "sha256-bVwvWFg1iOp5H0yGRQBAcdAN+lVKW/eIoAbKHrWr1ws=";
    })
    (fetchurl {
      url = "https://github.com/koreader/koreader/releases/download/${koreaderVersion}/koreader-kobo-${koreaderVersion}.zip";
      hash = "sha256-UQu8RhjcxaL8VKKoBp+U6lqnpHpdbFqSt1wi17cBFG8=";
    })
  ];

  nativeBuildInputs = [ unzip ];

  # Two unrelated archives; unpack both by hand rather than picking a sourceRoot.
  unpackPhase = ''
    runHook preUnpack
    for s in $srcs; do
      case "$s" in
        *.tar.gz) tar xf "$s" ;;
        *.zip)    unzip -q "$s" -d koreader-release ;;
      esac
    done
    runHook postUnpack
  '';

  dontConfigure = true;
  dontBuild = true;
  # ARM objects: nothing on the host has any business rewriting them.
  dontStrip = true;
  dontPatchELF = true;

  installPhase = ''
    runHook preInstall
    mkdir -p "$out/include" "$out/lib"
    cp -r libressl-${libresslVersion}/include/openssl "$out/include/"
    cp -L koreader-release/koreader/libs/libssl.so.60 \
          koreader-release/koreader/libs/libcrypto.so.57 "$out/lib/"
    chmod -R u+w "$out"
    ln -s libssl.so.60    "$out/lib/libssl.so"
    ln -s libcrypto.so.57 "$out/lib/libcrypto.so"
    runHook postInstall
  '';

  doInstallCheck = true;
  installCheckPhase = ''
    runHook preInstallCheck
    grep -h LIBRESSL_VERSION_TEXT "$out/include/openssl/opensslv.h" | head -1
    grep -q '"LibreSSL ${libresslVersion}"' "$out/include/openssl/opensslv.h" \
      || { echo "header version is not ${libresslVersion}"; exit 1; }
    runHook postInstallCheck
  '';

  meta = with lib; {
    description = "LibreSSL headers plus the ARM libssl/libcrypto that KOReader ships for Kobo";
    license = licenses.isc;
    platforms = [ "x86_64-linux" ];
  };
}
