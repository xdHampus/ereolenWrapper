{ lib, stdenv, fetchgit, cmake, curl }:

stdenv.mkDerivation rec {
  pname = "cpr";
  version = "1.10.0";

  src = fetchgit {
    url = "https://github.com/libcpr/cpr.git";
    rev = "0817715923c9705e68994eb52ef9df3f6845beba";
    sha256 = "z9Aom5e6k1KmB2ncDHz8h0wDGkg6h1yazVJBdEZyswo=";
    fetchSubmodules = true;
  };

  nativeBuildInputs = [ cmake ];
  buildInputs = [ curl ];

  cmakeFlags = [
  	"-DCMAKE_BUILD_TYPE=Release"
  	"-DCPR_BUILD_TESTS=OFF"
  	"-DCPR_FORCE_USE_SYSTEM_CURL=ON"
  ];


  meta = with lib; {
    homepage = "https://github.com/libcpr/cpr";
    description = "C++ Requests: Curl for People, a spiritual port of Python Requests.";
    platforms = platforms.unix;
    license = licenses.mit;
    maintainers = with maintainers; [ xdHampus ];
  };
}
