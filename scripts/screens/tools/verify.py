#!/usr/bin/env python3
"""Pixel-diff a rendered screen against a real Flipper screenshot.

The reference may be a raw qFlipper PNG (512x256) or a screenshot that was
pasted (scaled, any colour scheme) into a documentation illustration. Give the
crop box around the LCD area; the script searches the scale/origin of the
128x64 pixel grid that best fits, samples the centre of every cell, and
compares it with our framebuffer. Requires Pillow + numpy.

usage: verify.py <reference.png> <x0,y0,x1,y1|full> <rendered.png> [diff_out.png]
"""
import sys

from PIL import Image


def load_rendered(path):
    im = Image.open(path).convert("RGB")
    w, h = im.size
    s = w // 128
    px = im.load()
    return [[px[x * s + s // 2, y * s + s // 2] == (0, 0, 0) for x in range(128)] for y in range(64)]


def main():
    ref_path, box, ours_path = sys.argv[1:4]
    diff_out = sys.argv[4] if len(sys.argv) > 4 else None
    ref = Image.open(ref_path).convert("RGBA")
    bg = Image.new("RGBA", ref.size, (255, 255, 255, 255))
    ref = Image.alpha_composite(bg, ref).convert("L")
    if box != "full":
        ref = ref.crop(tuple(int(v) for v in box.split(",")))
    rw, rh = ref.size
    lo, hi = ref.getextrema()
    thr = (lo + hi) / 2

    ours = load_rendered(ours_path)
    import numpy as np

    R = np.array(ref, dtype=np.float32) < thr  # dark mask, [rh, rw]
    O = np.array(ours, dtype=bool)
    gx = np.arange(128) + 0.5
    gy = np.arange(64) + 0.5

    def score(s, ox, oy):
        cx = (ox + gx * s).astype(int)
        cy = (oy + gy * s).astype(int)
        if cx[0] < 0 or cy[0] < 0 or cx[-1] >= rw or cy[-1] >= rh:
            return -1, None
        smp = R[np.ix_(cy, cx)]
        return int((smp == O).sum()), smp

    # Pixels are square; search scale and origin of the 128x64 grid that best
    # explains the reference (coarse grid search, then refine).
    s_max = min(rw / 128, rh / 64)
    best = (-1, 0, 0, 0, None)
    for s in np.arange(max(1.0, s_max * 0.75), s_max + 1e-9, 0.01):
        for ox in np.arange(0, rw - 128 * s + 1e-9, max(0.5, s / 4)):
            for oy in np.arange(0, rh - 64 * s + 1e-9, max(0.5, s / 4)):
                sc, smp = score(s, ox, oy)
                if sc > best[0]:
                    best = (sc, s, ox, oy, smp)
    for _ in range(3):
        _, s0, ox0, oy0, _ = best
        for s in np.arange(s0 - 0.01, s0 + 0.01, 0.001):
            for ox in np.arange(ox0 - s0 / 4, ox0 + s0 / 4, 0.25):
                for oy in np.arange(oy0 - s0 / 4, oy0 + s0 / 4, 0.25):
                    sc, smp = score(s, ox, oy)
                    if sc > best[0]:
                        best = (sc, s, ox, oy, smp)
    _, sx, ox, oy, smp = best
    sy = sx
    sampled = smp.tolist()

    diff = [(x, y) for y in range(64) for x in range(128) if sampled[y][x] != ours[y][x]]
    lit = sum(map(sum, ours))
    print(
        f"grid: scale {sx:.3f}x{sy:.3f} px/pixel, origin ({ox:.1f},{oy:.1f}); "
        f"lit pixels ours={lit} ref={sum(map(sum, sampled))}; "
        f"differing pixels: {len(diff)} / 8192"
    )
    if diff_out:
        s = 4
        out = Image.new("RGB", (128 * s, 64 * s))
        op = out.load()
        for y in range(64):
            for x in range(128):
                a, b = ours[y][x], sampled[y][x]
                c = (0, 0, 0) if a and b else (254, 138, 44) if not a and not b else (
                    (255, 0, 0) if a else (0, 90, 255))
                for dy in range(s):
                    for dx in range(s):
                        op[x * s + dx, y * s + dy] = c
        out.save(diff_out)
    return 0 if not diff else 1


if __name__ == "__main__":
    sys.exit(main())
