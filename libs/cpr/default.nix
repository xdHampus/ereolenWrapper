{ lib, stdenv, fetchgit, cmake, curl }:

stdenv.mkDerivation rec {
  pname = "cpr";
  version = "1.7.2";

  src = fetchgit {
    url = "https://github.com/libcpr/cpr.git";
    rev = "beb9e98806bb84bcc130a2cebfbcbbc6ce62b335";
    sha256 = "19rsq1pr1mc5psr9rs8nvz7p9rfqsg1isp5inc8vc59wfa0b5ppn";
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
