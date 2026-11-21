---
title: Rolling codes
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Rolling codes

Sub-GHz remotes come in two kinds:

- **Static (fixed) code** — every press sends exactly the same packet (Princeton, CAME 12/24 bit, Nice Flo,
  Marantec, Roger, Gate TX…). A copy is identical to the original; both keep working forever, in any order.
  [Read](/subghz/read) it and save.
- **Rolling (dynamic) code** — every press sends a new packet built from a **counter** that grows by one on each
  press (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+, Alutech AT-4N…). The counter is usually
  encrypted, so the next code can only be computed if the firmware knows the protocol's key.

::: tip Unleashed
Unleashed can decode, save **and send** many rolling-code protocols, create new remotes for them with
[Add Manually](/subghz/add-manually), send the remote's other buttons with the arrow keys
([custom buttons](#custom-buttons)), and tune how the counter increments ([Counter Incr.](#counter-increment),
[Counter modes](/subghz/counter-mode)). Stock firmware decodes most of these but won't transmit them.
:::

## How the receiver checks the counter

The receiver stores the last counter it accepted **for each remote** (one value per remote, not per button):

- counter **equal to the expected next / within the forward window** → accepted, gate opens;
- counter **far ahead** → many receivers resync: the first press is stored, the next consecutive one works;
- counter **behind** the stored value → ignored. Some receivers unpair a remote after repeated "old" codes.

## The counter conflict

*Why can't you catch your own rolling-code remote in Read and use it from the Flipper?*
(adapted from [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Imagine:

1. You press the original remote — it sends counter `0002`.
2. You saved that signal on the Flipper; when you send it, the Flipper sends `0003`.
3. The receiver thinks you pressed the original again, and opens.
4. But the original remote is still at `0002`; its next press is `0003` — a value the receiver has already seen,
   so **it doesn't open**.

Don't panic — the remote is not unpaired. Press it again: `0004` overtakes the Flipper and the original works
again. But such "races" can push the counters 100+ presses apart, and then the original can't be brought back
without re-pairing it at the receiver.

Ways out:

- **Best: create a new remote** on the Flipper (`Sub-GHz → Add Manually`) and register it in the receiver. It
  has its own serial and counter and never conflicts with the originals. See [remote programming](/subghz/remote-prog).
- Decide which one you'll use — the Flipper **or** the original — and use only that one.
- Use both, but never let the counters drift far apart (press a few times on whichever is behind).
- Experimental: special [counter modes](/subghz/counter-mode) for some receivers let a clone and the original
  coexist.

::: danger Cars
Don't clone the key fob of a car. Replaying it (even via Read RAW) can desync the key or get it blacklisted,
and re-pairing often requires dealer service tools.
:::

## Custom buttons

When a supported rolling-code (or some static) file is open in `Emulate`:

- <kbd>OK</kbd> (`Send`) sends the button that was recorded / generated;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> send **other button codes** of the same remote, with a
  correctly incremented counter, while held. The original button code is shown as a small hex digit on the right
  of the screen while an arrow is used.

Which arrow maps to which button depends on the protocol; hidden/programming buttons (e.g. `0xF` on BFT Mitto,
`Prog` on Somfy) are also reachable this way — the full table is in
[remote programming](/subghz/remote-prog) (hidden button reference).

Protocols with custom buttons in the current firmware (number = how many extra codes the arrows can send):

| Protocol | Extra | Protocol | Extra |
|---|---|---|---|
| KeeLoq (all `KL:` manufacturers) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (programming) |
| Somfy Keytis | 1 (`Prog`) | | |

## Counter increment

`Sub-GHz → Radio Settings → Counter Incr.` sets how much the counter grows per transmission: `+1` (default),
`+2`, `+3`. With **Debug mode** enabled (`Settings → System → Debug`) the list grows to `+4`, `+5`, `+10`,
`+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50` — protocol-development tools; don't use them on a real installation.
See [Settings](/subghz/settings).

## Programming a new remote into the receiver

The normal, conflict-free way to use the Flipper with a rolling-code gate:

1. Read your original remote (`Sub-GHz → Read`) to learn the protocol, frequency and modulation.
2. `Sub-GHz → Add Manually` → your system → the same band → save.
3. Put the receiver into learning mode (button on the board, or from a working remote — the Flipper sends the
   hidden "programming" button with one arrow key).
4. Open the new file and hold <kbd>OK</kbd>.

Per-manufacturer procedures: **[Using the Flipper as a new remote](/subghz/remote-prog)**.

## Troubleshooting

- **Worked once, then stopped** — you're using a clone. Press several times in a row to resync, or make a new
  remote instead.
- **Original remote stopped working** — the Flipper ran ahead. Press the original several times; if the gap is
  too large, re-register it at the receiver.
- **Arrows do nothing** — the protocol has no custom buttons, or the file is static without a button field.
- **`KL: Unknown` after Read** — the manufacturer key is unknown; it can't be sent. See [KeeLoq](/subghz/keeloq).

::: warning
Use these features only with your own equipment or with the owner's permission.
:::

## Related

- [Add Manually](/subghz/add-manually) · [Remote programming](/subghz/remote-prog)
- [KeeLoq](/subghz/keeloq) · [Counter modes](/subghz/counter-mode)
- [Supported systems](/subghz/supported-systems)
