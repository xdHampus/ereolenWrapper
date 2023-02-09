{ lib, stdenv, fetchgit, fetchurl
, pugixml, updfparser,  curl, openssl, libzip }:

stdenv.mkDerivation rec {
  pname = "libgourou";
  version = "0.8.1";

  src = fetchgit {
    url = "git://soutade.fr/libgourou";
    rev = "v${version}";
    sha256 = "00cg8lfjnryszvldy949xgpir6nz674kfrwwys8av4vy7piqm7jz";
  };

  buildInputs = [ pugixml updfparser curl openssl libzip ];
  
  patches = [
    ./devendor.patch # devendor pugixml and updfparser
  ];
  
  installPhase = ''
    runHook preInstall
    install -Dt $out/include include/libgourou*.h
    install -Dt $out/lib libgourou.so
    install -Dt $out/lib libgourou.so.${version}
    install -Dt $out/bin utils/acsmdownloader
    install -Dt $out/bin utils/adept_{activate,loan_mgt,remove}
    runHook postInstall
  '';

  meta = with lib; {
    description = "Implementation of Adobe's ADEPT protocol for ePub/PDF DRM";
    homepage = "https://indefero.soutade.fr/p/libgourou";
    license = licenses.lgpl3Plus;
    maintainers = with maintainers; [ McSinyx ];
    platforms = platforms.all;
  };
}
