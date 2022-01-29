{ lib, llvmPackages_11 , cmake, gtest
, enableTests ? false, customLibs ? []
, nlohmann_json, openssl, curl, zlib
}:

llvmPackages_11.stdenv.mkDerivation rec {
  pname = "ereolenwrapper";
  version = "0.1.0";
  
  src = ./.;

  nativeBuildInputs = [ cmake gtest openssl ];
  buildInputs = [ 
  		nlohmann_json 
  		curl zlib 
  ] ++ customLibs;
  
  cmakeFlags = [
      "-DENABLE_INSTALL=ON"
      "-DENABLE_TESTING=${if enableTests then "ON" else "OFF"}"
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
