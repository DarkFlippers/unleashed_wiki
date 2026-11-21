#!/usr/bin/env python3
"""Compile firmware assets/icons/** into assets_icons.c/.h.

Bit-exact port of the firmware's scripts/assets.py `icons` command
(PIL convert("1") -> invert -> XBM bit order), except that frames are always
stored uncompressed (header byte 0x00) so heatshrink2 is not required.
The firmware's icon decoder accepts both forms, so rendering is identical.
"""
import os
import sys

from PIL import Image, ImageOps


def frame_bytes(path):
    with Image.open(path) as im:
        bw = ImageOps.invert(im.convert("1"))
        w, h = bw.size
        px = bw.load()
        out = bytearray()
        for y in range(h):
            for xb in range(0, w, 8):
                b = 0
                for bit in range(8):
                    x = xb + bit
                    if x < w and px[x, y]:
                        b |= 1 << bit
                out.append(b)
        return w, h, b"\x00" + bytes(out)


def carray(data):
    return "{" + "".join("0x{:02x},".format(b) for b in data) + "}"


def is_junk(name):
    return name.startswith("._") or name == ".DS_Store"


def main(src, dst, base="assets_icons"):
    c = open(os.path.join(dst, base + ".c"), "w", newline="\n")
    c.write('#include "%s.h"\n\n#include <gui/icon_i.h>\n\n' % base)
    icons = []
    for dirpath, dirnames, filenames in os.walk(src):
        dirnames.sort()
        filenames.sort()
        if not filenames:
            continue
        if "frame_rate" in filenames:
            name = "A_" + os.path.split(dirpath)[1].replace("-", "_")
            frames, w, h, rate = [], None, None, 0
            for fn in sorted(filenames):
                full = os.path.join(dirpath, fn)
                if fn == "frame_rate":
                    rate = int(open(full).read().strip())
                    continue
                if is_junk(fn) or not fn.lower().endswith(".png"):
                    continue
                w, h, data = frame_bytes(full)
                fname = "_%s_%d" % (name, len(frames))
                frames.append(fname)
                c.write("const uint8_t %s[] = %s;\n" % (fname, carray(data)))
            c.write("const uint8_t* const _%s[] = {%s};\n\n" % (name, ",".join(frames)))
            icons.append((name, w, h, rate, len(frames)))
        else:
            for fn in filenames:
                if is_junk(fn) or not fn.lower().endswith(".png"):
                    continue
                name = "I_" + "_".join(fn.split(".")[:-1]).replace("-", "_")
                w, h, data = frame_bytes(os.path.join(dirpath, fn))
                c.write("const uint8_t _%s_0[] = %s;\n" % (name, carray(data)))
                c.write("const uint8_t* const _%s[] = {_%s_0};\n\n" % (name, name))
                icons.append((name, w, h, 0, 1))
    for name, w, h, rate, count in icons:
        c.write(
            "const Icon %s = {.width=%d,.height=%d,.frame_count=%d,.frame_rate=%d,.frames=_%s};\n"
            % (name, w, h, count, rate, name)
        )
    c.close()
    with open(os.path.join(dst, base + ".h"), "w", newline="\n") as hf:
        hf.write("#pragma once\n\n#include <gui/icon.h>\n\n")
        for name, *_ in icons:
            hf.write("extern const Icon %s;\n" % name)


if __name__ == "__main__":
    main(*sys.argv[1:4])
