#!/usr/bin/env bash
#
# Cross-build libereolenwrapper.so for Kobo e-readers, for use as a Lua C
# module inside KOReader. See README.md for the reasoning behind each
# dependency choice.
#
#   ./build.sh                      # fetch what is missing, then build
#   WORKDIR=/some/path ./build.sh   # keep downloads and build trees elsewhere
#
# Needs: cmake, pkg-config, a C/C++ compiler for the build machine, curl,
# tar, unzip. On a Nix box:
#
#   nix shell nixpkgs#cmake nixpkgs#pkg-config --command ./cross/kobo/build.sh
#
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="${SRC:-$(cd "$HERE/../.." && pwd)}"
WORKDIR="${WORKDIR:-$HERE/work}"

# Pinned so a rebuild months from now produces the same thing.
TC_URL="https://github.com/koreader/koxtoolchain/releases/download/2025.05/kobo.tar.gz"
CURL_VER="8.21.0"
CPR_VER="1.14.2"
# Must match the LibreSSL that the KOReader release below ships, because that
# is what we link against.
LIBRESSL_VER="4.2.1"
KOREADER_VER="v2026.03"

TRIPLE="arm-kobo-linux-gnueabihf"
DL="$WORKDIR/dl"
export KOBO_TC="$WORKDIR/tc/x-tools/$TRIPLE"
export KOBO_PREFIX="$WORKDIR/prefix"
SDK="$WORKDIR/libressl-sdk"
KOREL="$WORKDIR/koreader"

# Where KOReader keeps its CA bundle once installed on a Kobo. Only a fallback:
# the plugin calls ereol.ApiEnv.setCaBundle() with the path it actually found.
CA_BUNDLE="/mnt/onboard/.adds/koreader/data/ca-bundle.crt"

step() { printf '\n\033[1m=== %s\033[0m\n' "$1"; }
have() { [ -e "$1" ]; }

mkdir -p "$DL" "$WORKDIR"

step "toolchain"
if ! have "$KOBO_TC/bin/$TRIPLE-gcc"; then
    have "$DL/kobo.tar.gz" || curl -fSL -o "$DL/kobo.tar.gz" "$TC_URL"
    mkdir -p "$WORKDIR/tc"
    tar xf "$DL/kobo.tar.gz" -C "$WORKDIR/tc"
    # The tarball carries read-only directories, which makes `rm -rf work` fail.
    chmod -R u+w "$WORKDIR/tc"
fi
"$KOBO_TC/bin/$TRIPLE-gcc" --version | head -1

step "KOReader $KOREADER_VER (link target for LibreSSL, and its CA bundle)"
if ! have "$KOREL/koreader/libs/libssl.so.60"; then
    have "$DL/koreader-kobo.zip" || curl -fSL -o "$DL/koreader-kobo.zip" \
        "https://github.com/koreader/koreader/releases/download/$KOREADER_VER/koreader-kobo-$KOREADER_VER.zip"
    mkdir -p "$KOREL"
    unzip -q -o "$DL/koreader-kobo.zip" -d "$KOREL"
fi

# prefix/bin has to be on PATH for curl-config: CMake's FindCURL only learns
# which protocols libcurl supports from `curl-config --protocols`, and cpr asks
# for the HTTP component, so without it the cpr configure fails with
# "Could NOT find CURL (missing: HTTP)" despite having found the library.
export PATH="$KOBO_PREFIX/bin:$KOBO_TC/bin:$PATH"
export PKG_CONFIG_PATH="$KOBO_PREFIX/lib/pkgconfig"
mkdir -p "$KOBO_PREFIX/include" "$KOBO_PREFIX/lib/pkgconfig" "$KOBO_PREFIX/share/cmake" "$KOBO_PREFIX/bin"

step "LibreSSL $LIBRESSL_VER SDK (upstream headers + KOReader's own .so)"
if ! have "$SDK/lib/libssl.so"; then
    have "$DL/libressl-$LIBRESSL_VER.tar.gz" || curl -fSL -o "$DL/libressl-$LIBRESSL_VER.tar.gz" \
        "https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-$LIBRESSL_VER.tar.gz"
    tar xf "$DL/libressl-$LIBRESSL_VER.tar.gz" -C "$WORKDIR"
    mkdir -p "$SDK/include" "$SDK/lib"
    cp -r "$WORKDIR/libressl-$LIBRESSL_VER/include/openssl" "$SDK/include/"
    cp -L "$KOREL/koreader/libs/libssl.so.60" "$KOREL/koreader/libs/libcrypto.so.57" "$SDK/lib/"
    chmod -R u+w "$SDK"
    ln -sf libssl.so.60 "$SDK/lib/libssl.so"
    ln -sf libcrypto.so.57 "$SDK/lib/libcrypto.so"
fi
grep -h LIBRESSL_VERSION_TEXT "$SDK/include/openssl/opensslv.h" | head -1

step "header-only deps (Lua 5.1, nlohmann/json, LuaBridge)"
# Lua headers only -- see README. LuaJIT is Lua 5.1 ABI-compatible.
if ! have "$KOBO_PREFIX/include/lua.h"; then
    LUA=$(nix build --no-link --print-out-paths 'nixpkgs#lua5_1')
    cp -rL "$LUA"/include/* "$KOBO_PREFIX/include/"
fi
if ! have "$KOBO_PREFIX/include/nlohmann/json.hpp"; then
    JSON=$(nix build --no-link --print-out-paths 'nixpkgs#nlohmann_json')
    cp -rL "$JSON/include/nlohmann" "$KOBO_PREFIX/include/"
    cp -rL "$JSON/share/cmake/nlohmann_json" "$KOBO_PREFIX/share/cmake/"
fi
if ! have "$KOBO_PREFIX/include/LuaBridge/LuaBridge.h"; then
    LB=$(nix build --no-link --print-out-paths --impure \
        --expr "with import <nixpkgs> {}; callPackage $SRC/libs/luabridge {}")
    cp -rL "$LB/include/LuaBridge" "$KOBO_PREFIX/include/"
fi
chmod -R u+w "$KOBO_PREFIX/include" "$KOBO_PREFIX/share"

step "curl $CURL_VER (static, PIC, LibreSSL)"
if ! have "$KOBO_PREFIX/lib/libcurl.a"; then
    have "$DL/curl-$CURL_VER.tar.xz" || curl -fSL -o "$DL/curl-$CURL_VER.tar.xz" \
        "https://curl.se/download/curl-$CURL_VER.tar.xz"
    tar xf "$DL/curl-$CURL_VER.tar.xz" -C "$WORKDIR"
    (
        cd "$WORKDIR/curl-$CURL_VER"
        ./configure --host="$TRIPLE" --prefix="$KOBO_PREFIX" \
            --with-openssl="$SDK" --with-pic \
            --with-ca-bundle="$CA_BUNDLE" \
            --disable-shared --enable-static \
            --without-zlib --without-brotli --without-zstd --without-libpsl \
            --without-nghttp2 --without-libidn2 --without-librtmp \
            --disable-ldap --disable-ldaps --disable-manual --disable-docs \
            CFLAGS="-O2 -fPIC -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard"
        make -j"$(nproc)" -C lib
        make -C lib install
        make -C include install
        # `make -C lib install` installs neither of these.
        cp libcurl.pc "$KOBO_PREFIX/lib/pkgconfig/"
        install -m 755 curl-config "$KOBO_PREFIX/bin/"
    )
fi

step "cpr $CPR_VER (static)"
if ! have "$KOBO_PREFIX/lib/libcpr.a"; then
    have "$DL/cpr-$CPR_VER.tar.gz" || curl -fSL -o "$DL/cpr-$CPR_VER.tar.gz" \
        "https://github.com/libcpr/cpr/archive/refs/tags/$CPR_VER.tar.gz"
    tar xf "$DL/cpr-$CPR_VER.tar.gz" -C "$WORKDIR"
    cmake -S "$WORKDIR/cpr-$CPR_VER" -B "$WORKDIR/build-cpr" \
        -DCMAKE_TOOLCHAIN_FILE="$HERE/kobo.cmake" \
        -DCMAKE_INSTALL_PREFIX="$KOBO_PREFIX" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCPR_USE_SYSTEM_CURL=ON -DCPR_BUILD_TESTS=OFF -DCPR_ENABLE_SSL=OFF \
        -DBUILD_SHARED_LIBS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
        -DCMAKE_C_FLAGS=-DCURL_STATICLIB -DCMAKE_CXX_FLAGS=-DCURL_STATICLIB
    cmake --build "$WORKDIR/build-cpr" -j"$(nproc)"
    cmake --install "$WORKDIR/build-cpr"
fi

step "libereolenwrapper.so"
rm -rf "$WORKDIR/build-wrapper"
cmake -S "$SRC" -B "$WORKDIR/build-wrapper" \
    -DCMAKE_TOOLCHAIN_FILE="$HERE/kobo.cmake" \
    -DENABLE_LUA=ON -DENABLE_LUA_LINK=OFF \
    -DENABLE_TESTING=OFF -DENABLE_INSTALL=OFF \
    -DCMAKE_PREFIX_PATH="$KOBO_PREFIX" \
    -DLUA_INCLUDE_DIR="$KOBO_PREFIX/include" \
    -DLUABRIDGE_INCLUDE_DIRS="$KOBO_PREFIX/include" \
    -DCMAKE_CXX_FLAGS="-Wall -Wextra -DCURL_STATICLIB" \
    -DCMAKE_SHARED_LINKER_FLAGS="-L$SDK/lib -Wl,--no-as-needed -lssl -lcrypto"
cmake --build "$WORKDIR/build-wrapper" -j"$(nproc)"

OUT="$WORKDIR/libereolenwrapper.so"
cp "$WORKDIR/build-wrapper/src/main/libereolenwrapper.so" "$OUT"
"$KOBO_TC/bin/$TRIPLE-strip" "$OUT"

step "result"
ls -la "$OUT"
"$KOBO_TC/bin/$TRIPLE-readelf" -d "$OUT" | grep NEEDED
printf '\nHighest symbol version required per family. Available on a Libra H2O:\n'
printf 'GLIBC 2.19 (device), GLIBCXX 3.4.33 and CXXABI 1.3.15 (KOReader):\n'
for family in GLIBC GLIBCXX CXXABI; do
    printf '  %-8s %s\n' "$family" "$(
        "$KOBO_TC/bin/$TRIPLE-readelf" -V "$OUT" 2>/dev/null \
            | grep -oE "\b${family}_[0-9.]+" | sort -u -V | tail -1)"
done
# Note the lib/ -- pluginloader.lua puts "<plugin_root>/lib/?.so" on
# package.cpath and nothing else, so the plugin directory itself is not
# searched and require("libereolenwrapper") would fail from there.
printf '\nCopy to the device as:\n  %s\n' \
    "/mnt/onboard/.adds/koreader/plugins/ereolen.koplugin/lib/libereolenwrapper.so"
