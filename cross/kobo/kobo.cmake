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
