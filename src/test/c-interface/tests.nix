{ lib, llvmPackages_11 , cmake
, customLibs ? []
, openssl
}:

llvmPackages_11.stdenv.mkDerivation rec {
  pname = "ereolenwrapperctests";
  version = "0.1.0";
  
  src = ./.;

  nativeBuildInputs = [ cmake openssl ];
  buildInputs = [
  		cmake 
  ] ++ customLibs;

  cmakeFlags = [
      "-DENABLE_INSTALL=ON"
    ];

  meta = with lib; {
    homepage = "https://github.com/xdHampus/ereolenWrapper";
    description = ''
       Tests for the C interface of ereolenwrapper
    '';
    licencse = licenses.agpl3Only;
    platforms = with platforms; linux ++ darwin;
    maintainers = [ maintainers.xdhampus ];    
  };
}
