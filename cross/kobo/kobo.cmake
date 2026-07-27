# CMake toolchain for Kobo e-readers (arm-kobo-linux-gnueabihf).
#
# Expects two environment variables:
#   KOBO_TC     -- the koxtoolchain install root, i.e. the directory holding
#                  bin/arm-kobo-linux-gnueabihf-gcc
#   KOBO_PREFIX -- where this build's own dependencies were staged
#
# build.sh sets both. See README.md for what goes into KOBO_PREFIX and why.

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(KOBO_TC "$ENV{KOBO_TC}")
set(KOBO_PREFIX "$ENV{KOBO_PREFIX}")
set(TRIPLE arm-kobo-linux-gnueabihf)

set(CMAKE_C_COMPILER   ${KOBO_TC}/bin/${TRIPLE}-gcc)
set(CMAKE_CXX_COMPILER ${KOBO_TC}/bin/${TRIPLE}-g++)

# Name the binutils explicitly rather than letting CMake pick them off PATH.
# Archiving is arch-agnostic enough that the host's ar happens to work, so a
# shell with binutils installed hides the problem; a Nix build has none at all
# and fails at "Linking CXX static library" with "Error running link command:
# no such file or directory".
#
# FORCE, because nixpkgs' CMake setup hook passes -DCMAKE_AR="$(command -v
# $AR)" on the command line. Under stdenvNoCC there is no ar on PATH, so that
# expands to nothing and seeds the cache with an empty CMAKE_AR -- which a
# plain `set(... CACHE ...)` here would then decline to overwrite, leaving a
# link line that literally begins with "".
set(CMAKE_AR      ${KOBO_TC}/bin/${TRIPLE}-ar      CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB  ${KOBO_TC}/bin/${TRIPLE}-ranlib  CACHE FILEPATH "" FORCE)
set(CMAKE_NM      ${KOBO_TC}/bin/${TRIPLE}-nm      CACHE FILEPATH "" FORCE)
set(CMAKE_STRIP   ${KOBO_TC}/bin/${TRIPLE}-strip   CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY ${KOBO_TC}/bin/${TRIPLE}-objcopy CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP ${KOBO_TC}/bin/${TRIPLE}-objdump CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER  ${KOBO_TC}/bin/${TRIPLE}-ld      CACHE FILEPATH "" FORCE)

set(CMAKE_SYSROOT ${KOBO_TC}/${TRIPLE}/sysroot)
set(CMAKE_FIND_ROOT_PATH ${KOBO_TC}/${TRIPLE}/sysroot ${KOBO_PREFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Cortex-A9 with VFPv3, hard float. Deliberately no NEON: it is not guaranteed
# across the Kobo range, and nothing here is hot enough to want it.
set(CMAKE_C_FLAGS_INIT   "-O2 -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS_INIT "-O2 -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard")
