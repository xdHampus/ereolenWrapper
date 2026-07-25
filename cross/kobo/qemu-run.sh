#!/usr/bin/env bash
#
# Run a Lua script against the cross-built libereolenwrapper.so on the build
# machine, using qemu-arm and the ARM LuaJIT from the KOReader release that
# build.sh already downloaded. Enough to catch load failures and to exercise
# live HTTPS without touching a device.
#
#   ./cross/kobo/qemu-run.sh cross/kobo/smoke.lua
#
# Needs build.sh to have run first. On a Nix box this pulls qemu and an ARM
# glibc itself.
set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
WORKDIR="${WORKDIR:-$HERE/work}"
SCRIPT="${1:?usage: qemu-run.sh <script.lua> [args...]}"
shift || true

KOREL="$WORKDIR/koreader/koreader"
QROOT="$WORKDIR/qroot"
SO="$WORKDIR/libereolenwrapper.so"

[ -e "$SO" ] || { echo "no $SO -- run build.sh first" >&2; exit 1; }

if ! [ -e "$QROOT/lib/ld-linux-armhf.so.3" ]; then
    # The toolchain sysroot's own glibc 2.15 loader cannot run the KOReader
    # release binaries -- ld.so asserts in elf_dynamic_do_Rel -- so host the
    # test on a newer ARM glibc. Purely a qemu concern: the device's real 2.19
    # loader is fine. ^out matters, or you get the -bin output with no lib/.
    GLIBC=$(nix build --no-link --print-out-paths \
        'nixpkgs#pkgsCross.armv7l-hf-multiplatform.glibc^out')
    mkdir -p "$QROOT/lib"
    cp -L "$GLIBC"/lib/*.so* "$QROOT/lib/"
    cp -L "$KOREL/libs/libstdc++.so.6" "$KOREL/libs/libssl.so.60" \
          "$KOREL/libs/libcrypto.so.57" "$QROOT/lib/"
    cp -L "$WORKDIR/tc/x-tools/arm-kobo-linux-gnueabihf/arm-kobo-linux-gnueabihf/lib/libgcc_s.so.1" \
          "$QROOT/lib/"
    chmod -R u+w "$QROOT"
fi

# EREOL_CA_BUNDLE is for the script to pass to ereol.ApiEnv.setCaBundle():
# curl's compiled-in path only exists on the device.
exec nix shell nixpkgs#qemu --command env \
    EREOL_CA_BUNDLE="$KOREL/data/ca-bundle.crt" \
    LD_LIBRARY_PATH="$QROOT/lib" \
    LUA_CPATH="$WORKDIR/?.so" \
    qemu-arm -L "$QROOT" "$KOREL/luajit" "$SCRIPT" "$@"
