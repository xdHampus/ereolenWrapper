{ lib, fetchFromGitHub, stdenv
    ,cmake
    ,cxx17-features ? true
}:

stdenv.mkDerivation rec {
  pname = "luabridge";
  version = "2.7";

  src = fetchFromGitHub {
    owner = "vinniefalco";
    repo = "LuaBridge";
    rev = "6035c2b5e115fd6dd71c1fe4f4475f02be54128d";
    sha256 = "/PHwF5yRgpITQ3nUF8ymk3/q1lUT8F1Lwcu7h2xWljg=";
    fetchSubmodules = true;
  };

  nativeBuildInputs = [ cmake ];
  buildInputs = [ ];

  cmakeFlags = [
  	#"-DCMAKE_BUILD_TYPE=Release"
  	"-DLUABRIDGE_TESTING=OFF"
  	"-DLUABRIDGE_CXX17=${if cxx17-features then "1" else "0"}"
  ];


  configurePhase = '' ls '';
  buildPhase = '' ls '';

  installPhase = ''
    mkdir -p $out/bin
    mv ./Source $out/include
  '';

  meta = with lib; {
    homepage = "https://github.com/vinniefalco/LuaBridge";
    description = "LuaBridge is a lightweight and dependency-free library for mapping data, functions, and classes back and forth between C++ and Lua.";
    platforms = platforms.unix;
    license = licenses.mit;
    maintainers = with maintainers; [ xdHampus ];
  };
}
