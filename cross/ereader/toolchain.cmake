# CMake toolchain for e-readers (defaults to arm-kobo-linux-gnueabihf).
#
# Expects two environment variables:
#   EREADER_TC     -- the koxtoolchain install root, containing bin/<triple>-gcc
#   EREADER_PREFIX -- where this build's own dependencies were staged
#   EREADER_TRIPLE / EREADER_ARCH_FLAGS -- optional overrides for other devices
#
# ../kobo/build.sh sets both. See README.md for the shared build layout.

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(EREADER_TC "$ENV{EREADER_TC}")
set(EREADER_PREFIX "$ENV{EREADER_PREFIX}")
set(TRIPLE "$ENV{EREADER_TRIPLE}")
if(NOT TRIPLE)
	set(TRIPLE arm-kobo-linux-gnueabihf)
endif()
set(ARCH_FLAGS "$ENV{EREADER_ARCH_FLAGS}")
if(NOT ARCH_FLAGS)
	set(ARCH_FLAGS "-march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard")
endif()

set(CMAKE_C_COMPILER   ${EREADER_TC}/bin/${TRIPLE}-gcc)
set(CMAKE_CXX_COMPILER ${EREADER_TC}/bin/${TRIPLE}-g++)

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
set(CMAKE_AR      ${EREADER_TC}/bin/${TRIPLE}-ar      CACHE FILEPATH "" FORCE)
set(CMAKE_RANLIB  ${EREADER_TC}/bin/${TRIPLE}-ranlib  CACHE FILEPATH "" FORCE)
set(CMAKE_NM      ${EREADER_TC}/bin/${TRIPLE}-nm      CACHE FILEPATH "" FORCE)
set(CMAKE_STRIP   ${EREADER_TC}/bin/${TRIPLE}-strip   CACHE FILEPATH "" FORCE)
set(CMAKE_OBJCOPY ${EREADER_TC}/bin/${TRIPLE}-objcopy CACHE FILEPATH "" FORCE)
set(CMAKE_OBJDUMP ${EREADER_TC}/bin/${TRIPLE}-objdump CACHE FILEPATH "" FORCE)
set(CMAKE_LINKER  ${EREADER_TC}/bin/${TRIPLE}-ld      CACHE FILEPATH "" FORCE)

set(CMAKE_SYSROOT ${EREADER_TC}/${TRIPLE}/sysroot)
set(CMAKE_FIND_ROOT_PATH ${EREADER_TC}/${TRIPLE}/sysroot ${EREADER_PREFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Kobo defaults to VFPv3, hard float, without assuming NEON across its range.
# KOReader's kindlepw2 family selects NEON and softfp through EREADER_ARCH_FLAGS.
set(CMAKE_C_FLAGS_INIT   "-O2 ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "-O2 ${ARCH_FLAGS}")
