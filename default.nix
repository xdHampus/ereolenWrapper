{ lib, stdenv, cmake, gtest, nlohmann_json, openssl, curl, zlib, cpr,
enableLua ? false, enableTests ? false,
luabridge ? null, lua ? null
}:

assert enableLua -> lua != null;
assert enableLua -> luabridge != null;

stdenv.mkDerivation rec {
  pname = "ereolenwrapper";
  version = "0.1.0";

  src = ./.;

  #preConfigure = ''
  #  sed -i 's/ SHARED / STATIC /g' src/main/CMakeLists.txt
  #'';

  nativeBuildInputs = [ cmake openssl ] ++ lib.optionals enableTests [ gtest ];
  buildInputs = [ nlohmann_json curl zlib cpr ]
    ++ lib.optionals enableLua [ lua luabridge ];

  cmakeFlags = [
    "-DENABLE_INSTALL=ON"
    "-DENABLE_TESTING=${if enableTests then "ON" else "OFF"}"
    "-DENABLE_LUA=${if enableLua then "ON" else "OFF"}"
  ];

  meta = with lib; {
    homepage = "https://github.com/xdHampus/ereolenWrapper";
    description = ''
      C++ Wrapper for eReolen.dk RPC API
    '';
    licencse = licenses.lgpl3Plus;
    platforms = with platforms; linux ++ darwin;
    maintainers = [ maintainers.xdhampus ];
  };
}
