#!/usr/bin/env bash
# Build the host-side Flipper GUI renderer from real Unleashed firmware sources
# and render every screen spec into docs/public/screens/.
#
#   FW_SRC   path to an Unleashed firmware checkout (default: ./.firmware)
#   OUT_DIR  output directory for PNGs + manifest (default: docs/public/screens)
#   CC       C compiler (default: clang)
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
FW_SRC="${FW_SRC:-$ROOT/.firmware}"
OUT_DIR="${OUT_DIR:-$ROOT/docs/public/screens}"
BUILD="${BUILD_DIR:-$HERE/.build}"
CC="${CC:-clang}"
PYTHON="${PYTHON:-python3}"

if [ ! -f "$FW_SRC/applications/services/gui/canvas.c" ]; then
    echo "FW_SRC=$FW_SRC does not look like an Unleashed firmware checkout" >&2
    echo "See scripts/screens/README.md for how to fetch it." >&2
    exit 1
fi
for sub in lib/mlib/m-core.h lib/heatshrink/heatshrink_decoder.c lib/libusb_stm32/inc/usb.h; do
    if [ ! -f "$FW_SRC/$sub" ]; then
        echo "Missing $FW_SRC/$sub - run: git -C \"$FW_SRC\" submodule update --init lib/mlib lib/heatshrink lib/libusb_stm32" >&2
        exit 1
    fi
done

mkdir -p "$BUILD/obj" "$BUILD/icons"

# 1. Icons: compile assets/icons into assets_icons.c/.h with tools/icons.py
#    (bit-exact port of the firmware's scripts/assets.py, needs Pillow; a venv
#    with Pillow is created in .build/ if python3 has none). Desktop animation
#    frames listed in DOLPHIN_FRAMES (assets/dolphin/external) are compiled the
#    same way into assets_dolphin.c/.h as I_Dolphin_<name>.
DOLPHIN_FRAMES=(L1_Waves_128x50/frame_0.png)
ICON_STAMP="$BUILD/icons/.stamp"
if [ ! -f "$ICON_STAMP" ] || [ "$FW_SRC/assets/icons" -nt "$ICON_STAMP" ]; then
    echo "[icons] compiling $FW_SRC/assets/icons"
    if ! "$PYTHON" -c "import PIL" 2>/dev/null; then
        if [ ! -x "$BUILD/venv/bin/python" ]; then
            echo "[icons] Pillow not found, creating $BUILD/venv"
            python3 -m venv "$BUILD/venv"
            "$BUILD/venv/bin/pip" -q install pillow
        fi
        PYTHON="$BUILD/venv/bin/python"
    fi
    "$PYTHON" "$HERE/tools/icons.py" "$FW_SRC/assets/icons" "$BUILD/icons"
    rm -rf "$BUILD/dolphin_src" && mkdir -p "$BUILD/dolphin_src"
    for f in "${DOLPHIN_FRAMES[@]}"; do
        cp "$FW_SRC/assets/dolphin/external/$f" "$BUILD/dolphin_src/Dolphin_${f%%/*}.png"
    done
    "$PYTHON" "$HERE/tools/icons.py" "$BUILD/dolphin_src" "$BUILD/icons" assets_dolphin
    touch "$ICON_STAMP"
fi

G="$FW_SRC/applications/services/gui"
INC=(
    -include "$HERE/stubs/include/host_prelude.h"
    -I"$HERE/stubs/include"
    -I"$FW_SRC/furi"
    -I"$FW_SRC/lib/mlib"
    -I"$FW_SRC/lib/u8g2"
    -I"$FW_SRC/lib"
    -I"$FW_SRC"
    -I"$FW_SRC/lib/datetime"
    -I"$FW_SRC/lib/toolbox"
    -I"$FW_SRC/lib/bit_lib"
    -I"$FW_SRC/lib/flipper_format"
    -I"$FW_SRC/lib/flipper_application"
    -I"$FW_SRC/lib/flipper_application/elf"
    -I"$FW_SRC/lib/subghz"
    -I"$FW_SRC/lib/nfc"
    -I"$FW_SRC/lib/lfrfid"
    -I"$FW_SRC/lib/ibutton"
    -I"$FW_SRC/lib/one_wire"
    -I"$FW_SRC/lib/infrared/encoder_decoder"
    -I"$FW_SRC/lib/infrared/worker"
    -I"$FW_SRC/lib/infrared/signal"
    -I"$FW_SRC/lib/ble_profile"
    -I"$FW_SRC/lib/digital_signal"
    -I"$FW_SRC/lib/drivers"
    -I"$FW_SRC/lib/music_worker"
    -I"$FW_SRC/lib/pulse_reader"
    -I"$FW_SRC/lib/signal_reader"
    -I"$FW_SRC/targets/f7/furi_hal"
    -I"$FW_SRC/targets/furi_hal_include"
    -I"$FW_SRC/targets/f7/ble_glue"
    -I"$FW_SRC/lib/libusb_stm32/inc"
    -I"$FW_SRC/applications/services"
    -I"$FW_SRC/applications/main"
    -I"$FW_SRC/applications/settings"
    -I"$FW_SRC/applications/system"
    -I"$BUILD/icons"
    -I"$HERE/harness"
)
if [ "${1:-}" = "--print-cflags" ]; then printf "%s\n" "${INC[@]}"; exit 0; fi
# SRV_BT: only desktop_view_debug.c reads it among the compiled sources; with it
# the info screen prints the copro version the way a device with BLE does.
CFLAGS=(-std=gnu17 -O1 -g -w -DNDEBUG -DFURI_NDEBUG -D__HOST_RENDER__ -DSRV_BT -fno-common)

FW_SOURCES=(
    "$G/canvas.c" "$G/elements.c" "$G/icon.c" "$G/icon_animation.c" "$G/view.c" "$G/view_port.c"
    $(ls "$G"/modules/*.c | grep -v -e '/menu\.c$' -e '/file_browser')
    "$G"/modules/widget_elements/*.c
    "$FW_SRC"/lib/u8g2/*.c
    "$FW_SRC/lib/toolbox/compress.c"
    "$FW_SRC/lib/toolbox/path.c"
    "$FW_SRC/lib/toolbox/strint.c"
    "$FW_SRC/lib/datetime/datetime.c"
    "$FW_SRC/lib/heatshrink/heatshrink_decoder.c"
    "$FW_SRC/lib/heatshrink/heatshrink_encoder.c"
    "$FW_SRC/furi/core/string.c"
    "$BUILD/icons/assets_icons.c"
    "$BUILD/icons/assets_dolphin.c"
)
# extra firmware files (app-specific views) listed by the harness
while IFS= read -r line; do
    [ -z "$line" ] && continue
    case "$line" in \#*) continue ;; esac
    FW_SOURCES+=("$FW_SRC/$line")
done < "$HERE/fw_sources.txt"

LOCAL_SOURCES=("$HERE"/stubs/*.c "$HERE"/harness/*.c "$HERE"/specs/*.c)

# Firmware files that need a tiny host patch (copied to $BUILD/patched):
#  - gui/modules/menu.c: drop static_assert()s that pin the 32-bit plugin ABI
#    (pointer offsets differ on a 64-bit host; drawing code is untouched).
mkdir -p "$BUILD/patched"
awk 'BEGIN{skip=0} /^static_assert\(/{skip=1} { if(!skip) print; else print "" } skip && /\);[[:space:]]*$/{skip=0}' \
    "$G/modules/menu.c" > "$BUILD/patched/menu.c.tmp"
cmp -s "$BUILD/patched/menu.c.tmp" "$BUILD/patched/menu.c" 2>/dev/null || mv "$BUILD/patched/menu.c.tmp" "$BUILD/patched/menu.c"
rm -f "$BUILD/patched/menu.c.tmp"
FW_SOURCES+=("$BUILD/patched/menu.c")
INC+=(-I"$G/modules")

OBJS=()
compile() {
    local src="$1"
    # path hash in the object name avoids basename clashes
    local obj="$BUILD/obj/$(printf '%s' "$src" | shasum | cut -c1-8)_$(basename "$src" .c).o"
    if [ ! -f "$obj" ] || [ "$src" -nt "$obj" ] || [ "$HERE/build.sh" -nt "$obj" ] \
        || [ -n "$(find "$HERE/stubs/include" "$HERE/harness" -name '*.h' -newer "$obj" 2>/dev/null | head -1)" ]; then
        "$CC" "${CFLAGS[@]}" "${INC[@]}" -c "$src" -o "$obj"
    fi
    OBJS+=("$obj")
}

echo "[cc] compiling firmware GUI + harness"
for s in "${FW_SOURCES[@]}"; do compile "$s"; done
for s in "${LOCAL_SOURCES[@]}"; do compile "$s"; done

# Unresolved symbols only come from firmware code paths that are never executed
# while drawing (workers, storage, notifications); allow them to stay unbound.
"$CC" -o "$BUILD/flipper_screens" "${OBJS[@]}" -Wl,-dead_strip -Wl,-undefined,dynamic_lookup -lz -lm
echo "[run] rendering to $OUT_DIR"
mkdir -p "$OUT_DIR"
"$BUILD/flipper_screens" "$OUT_DIR" "$@"
