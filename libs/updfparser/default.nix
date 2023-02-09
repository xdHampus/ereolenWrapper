{ lib, stdenv, fetchgit }:

stdenv.mkDerivation {
  pname = "updfparser";
  version = "unstable-2023-01-10";

  src = fetchgit {
    url = "git://soutade.fr/updfparser";
    rev = "a421098092ba600fb1686a7df8fc58cd67429f59";
    sha256 = "1ll0f4x3h2ilwpyvylrrwl2pv8a0iinjar2yxf9ndl647q751p9a";
  };

  installPhase = ''
    runHook preInstall
    install -Dt $out/include include/*.h
    install -Dt $out/lib libupdfparser.so
    runHook postInstall
  '';

  meta = with lib; {
    description = "A very simple PDF parser";
    homepage = "https://indefero.soutade.fr/p/updfparser";
    license = licenses.lgpl3Plus;
    maintainers = with maintainers; [ xdhampus ];
    platforms = platforms.all;
  };
}