{ lib, stdenv, fetchgit, cmake, meson, curl
  , unityExtensionFixture ? false
  , unityExtensionMemory ? false
 }:

stdenv.mkDerivation rec {
  pname = "libunitytest";
  version = "2.5.2";

  src = fetchgit {
    url = "https://github.com/ThrowTheSwitch/Unity.git";
    rev = "0b899aec14d3a9abb2bf260ac355f0f28630a6a3";
    sha256 = "10zr39qrkzcpcicwa90pw3w50yd8iz8nqmp6pr26yfb10132729n";
    fetchSubmodules = false;
  };

  nativeBuildInputs = [ cmake meson ];
  buildInputs = [ curl meson];

  cmakeFlags = [
  	"-DCMAKE_BUILD_TYPE=Release"
  	"-DCPR_BUILD_TESTS=OFF" 
    "-DUNITY_EXTENSION_FIXTURE=${if unityExtensionFixture then "ON" else "OFF"}"
    "-DUNITY_EXTENSION_MEMORY=${if unityExtensionMemory then "ON" else "OFF"}"
  ];
  
  meta = with lib; {
    homepage = "https://www.throwtheswitch.org/unity";
    description = "Unity Test is a unit testing framework built for C, with a focus on working with embedded toolchains.";
    platforms = platforms.unix;
    license = licenses.mit;
    maintainers = with maintainers; [ xdhampus ];
  };
}
