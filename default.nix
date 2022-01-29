{ lib, llvmPackages_11 , cmake
, nlohmann_json
 }:
llvmPackages_11.stdenv.mkDerivation rec {
  pname = "ereolenwrapper";
  version = "0.1.0";
  
  src = ./.;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ nlohmann_json ];

  cmakeFlags = [
    "-DENABLE_TESTING=OFF"
    "-DENABLE_INSTALL=ON"
  ];

  meta = with lib; {
    homepage = "https://github.com/xdHampus/ereolenWrapper";
    description = ''
       C++ Wrapper for eReolen.dk RPC API
    '';
    licencse = licenses.agpl3Only;
    platforms = with platforms; linux ++ darwin;
    maintainers = [ maintainers.xdhampus ];    
  };
}
