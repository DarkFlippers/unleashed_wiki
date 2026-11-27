---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** creates a brand new virtual remote and saves it as a `.sub` file. You don't need an original
remote for it: the Flipper generates a random serial number (and a counter, seed etc. where the protocol needs
them). The new remote can then be **registered in a receiver** as an extra remote, the same way you'd register a
spare remote bought in a shop.

**Add Manually [Advanced]** does the same, but asks you to type every value in hex instead of generating it.

::: tip Unleashed
Stock firmware has only a handful of static protocols in Add Manually. Unleashed lists **more than 100 systems**,
including rolling-code ones (KeeLoq manufacturers, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code, CAME Atomo, Somfy,
Security+ 2.0, …), lets you pick any of 15 frequency/modulation bands for each, and adds the **[Advanced]** entry.
:::

## When to use it

| Situation | Use |
|---|---|
| You have a **static** (fixed code) remote and want a copy | [Read](/subghz/read) and save it — no need for Add Manually |
| You have a **rolling code** remote and want the Flipper to work *alongside* it | **Add Manually** → register the new remote in the receiver ([how](/subghz/remote-prog)) |
| You need a remote with known values (recovered seed, installer code, a specific serial) | **Add Manually [Advanced]** |
| You lost the original static remote but know its DIP switches / code | **Add Manually [Advanced]** with the key typed in |

Why not clone a rolling-code remote instead? See [Rolling codes](/subghz/rolling-codes): the clone and the
original fight over the counter.

## Creating a remote

1. `Main Menu → Sub-GHz → Add Manually`.
2. Scroll the list and pick the system, e.g. `BFT Mitto` or `KL: DoorHan`. Entries starting with `KL:` are
   KeeLoq manufacturers.

   ![Add Manually: alphabetical list of systems with KL: Allmatic selected](/screens/subghz/add_manually.png)

3. A **band picker** opens, with the system name as header. Bands are labelled `frequency modulation`, e.g.
   `433.92 AM650`. The system's own default band is first, then the other bands that system is known to use, then
   every remaining band (for installations on an unusual frequency). Press <kbd>OK</kbd> on the band you need.
4. Enter a file name (a name is suggested) and confirm.
5. The remote is saved to `/ext/subghz/` and appears in `Sub-GHz → Saved`.

   ![Menu of a saved signal: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Open it: `Sub-GHz → Saved → <your file> → Emulate`. Hold <kbd>OK</kbd> (`Send`) to transmit; on protocols with
   [custom buttons](/subghz/rolling-codes#custom-buttons) the arrows send the other buttons.

   ![Transmit screen of a saved signal with R: Int and the Send button](/screens/subghz/emulate.png)


Nothing is transmitted until you open the file and press a key.

::: warning Outdated names
Older guides (including older versions of `SubGHzRemoteProg.md`) name entries like `BFT Mitto 433MHz` or
`KL: DoorHan 315MHz`. Current firmware splits this into two steps: system (`BFT Mitto`) → band (`433.92 AM650`).
:::

### The 15 bands

All of them are offered for every system:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → system → band, then a series of hex input screens. Which screens
you get depends on the protocol family:

| Family | Screens (in order) |
|---|---|
| Static protocols (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; protocols that store a timing also ask `Enter TE in us` (and `Enter GT in TE`) |
| KeeLoq (`KL:` entries, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq with seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (hop discriminator, stored in the `Seed` field) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 bit) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N / AT4L, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (installer code) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (asked even from plain Add Manually) |
| Security+1.0 | nothing to enter, generated directly |

Values are big-endian hex. `BUTTON` and `SERIAL` together form the `Fix` you see after a [Read](/subghz/read):
on KeeLoq the button is the **first** hex digit of `Fix` (serial = `Fix` with that digit replaced by `0`), on FAAC
SLH / Genius it's the **last** digit.

::: tip Byte input
Unleashed's byte input has a mini nibble editor: press <kbd>↑</kbd> repeatedly until it appears.
:::

## Every entry in the list

Order and labels exactly as in the firmware menu. "Default" is the band listed first; "Also" are the system's
alternative bands listed right after it.

| Menu entry | Default | Also | Type |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (Beninca key) |
| `Alutech AT4L` | 433.92 AM650 | | Dynamic (Alutech AT-4N, `0x1Dxxxxxx` prefix) |
| `Alutech AT4N` | 433.92 AM650 | | Dynamic (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dynamic (plain counter) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dynamic (AES-128) |
| `BETT` | 433.92 AM650 | | Static |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Static |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Static |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dynamic |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Static (pseudo-dynamic) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + discriminator |
| `Ditec GOL4` | 433.92 AM650 | | Dynamic |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + discriminator |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Static (12 DIP switches) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Static (bike alarm) |
| `Gate TX` | 433.92 AM650 | | Static |
| `Genius` | 433.92 AM650 | 868.35 AM650 | FAAC SLH frame, Genius key |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | KeeLoq-like |
| `Hollarm` | 433.92 AM650 | | Static (bike alarm) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dynamic (KeeLoq based) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dynamic (KeeLoq based) |
| `Linear` | **300.00 AM650** | | Static (10 bit) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Static |
| `Marantec24` | **868.35 AM650** | | Static |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + discriminator |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Static |
| `Nice Flo 24bit` | 433.92 AM650 | | Static |
| `Nice FloR-S` | 433.92 AM650 | | Dynamic |
| `Nice O-Code` | 433.92 AM650 | | Dynamic, installer code |
| `Nice O-Code One` | 433.92 AM650 | | Dynamic, installer code (Nice One frame) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dynamic, installer code + certificate |
| `Nice One` | 433.92 AM650 | | Dynamic |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Static |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + discriminator |
| `Prastel` | 433.92 AM650 | | Dynamic (42 bit) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Static (24 bit) |
| `Proteco` | 433.92 AM650 | | Static |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Static |
| `Roger` | 433.92 AM650 | | Static |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dynamic |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dynamic |
| `Somfy Keytis` | **433.42 AM650** | | Dynamic |
| `Somfy Telis` | **433.42 AM650** | | Dynamic (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Static |
| `V2 Phoenix` | 433.92 AM650 | | Dynamic |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Static (Princeton, see [ZKTeco CMP200](/subghz/zkteco-cmp200)) |

For `KL: Sommer`, the FM476 bands generate the remote with Sommer's other modulation variant, so one menu row
covers both kinds of Sommer remote.

## Programming the new remote into a receiver

A freshly created rolling-code remote is unknown to the receiver. Register it like any spare remote — with the
receiver's learn button or from an already working remote. Hidden/programming buttons of the original remote are
sent with a single arrow key on the Flipper. Step-by-step procedures per manufacturer:
**[Using the Flipper as a new remote](/subghz/remote-prog)**.

## Troubleshooting

- **`Function requires an SD card with fresh databases.`** — the manufacturer key databases in
  `/ext/subghz/assets/` are missing or outdated. Reinstall/update the firmware with the SD card inserted.
- **Receiver doesn't react at all** — wrong band. Read your original remote first (`Sub-GHz → Read`) and pick the
  same frequency and modulation. DoorHan exists on 315 and 433.92 MHz; FAAC, Genius, Erreka on 433.92 and 868.35.
- **Receiver reacts but never stores the remote** — you missed the learning window, or for another reason (for example,
  interference) the receiver did not get a clean signal from the Flipper.
- **Erreka/BFT new remote refused** — some installations share one Seed across all remotes; recover it
  ([Seed Capturer](/subghz/seed-capturer)) and use Add Manually [Advanced]. See [KeeLoq](/subghz/keeloq).
- **Nice O-Code remote ignored** — a factory receiver has no installer code; use `Nice One` or `Nice FloR-S` there.
  For an installed system see [Nice O-Code](/subghz/nice-o-code).

::: warning
Only register remotes in receivers you own or are authorised to manage.
:::

## Related

- [Rolling codes and custom buttons](/subghz/rolling-codes)
- [Programming a new remote into a receiver](/subghz/remote-prog)
- [KeeLoq](/subghz/keeloq) · [Supported systems](/subghz/supported-systems)
- [Counter modes](/subghz/counter-mode) · [.sub file format](/subghz/file-format)
