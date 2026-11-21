---
title: Command-line interface (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Command-line interface (CLI)

The Flipper exposes a text console over USB serial. From it you can read and send signals, run apps, manage files,
watch logs, control GPIO and LEDs, chat with other Flippers over Sub-GHz and much more — handy for scripting,
debugging and app development.

## Connecting to the CLI

::: warning Close qFlipper first
Only one program can use the Flipper's serial port at a time. Quit **qFlipper** (and close Flipper Lab or other
terminals) before connecting.
:::

The serial speed is **230400** baud (for USB CDC the value is mostly ignored, but some terminals need it set).

### Option 1: Flipper Lab (browser)

Works in Chrome, Edge or another Chromium browser with Web Serial support.

1. Connect the Flipper via USB.
2. Open [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Option 2: Web serial terminal (browser)

1. Connect the Flipper via USB, open a Chromium browser.
2. Go to the [web serial terminal](https://googlechromelabs.github.io/serial-terminal/).
3. Set **Baud rate** to **230400**, click **Connect**, select your Flipper, click **Connect**.

### Option 3: Serial terminal — macOS

1. Find the port:

   ```sh
   ls /dev/cu.*
   ```

   The Flipper appears as `/dev/cu.usbmodemflip_NAME`, where `NAME` is your Flipper's name.
2. Connect with **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Quit: <kbd>Ctrl</kbd>+<kbd>A</kbd>, then <kbd>K</kbd>, then <kbd>Y</kbd>.
3. …or with **minicom** (install via [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Quit: <kbd>Esc</kbd>+<kbd>Z</kbd>, then <kbd>X</kbd>, then <kbd>Return</kbd>.

### Option 3: Serial terminal — Linux

1. Find the port:

   ```sh
   ls /dev/serial/by-id/
   ```

   Look for `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. If you only have one serial device it is usually
   also `/dev/ttyACM0`; qFlipper shows the port name too.
2. Connect:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   Quit screen: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Quit minicom: <kbd>Ctrl</kbd>+<kbd>A</kbd>,
   <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
If you get "permission denied" on Linux, add yourself to the `dialout` group (or `uucp` on some distributions) and
log in again.
:::

### Option 3: Serial terminal — Windows

1. Install [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Connect the Flipper; in **Device Manager → Ports (COM & LPT)** note its COM port (unplug/replug to see which
   one appears).
3. In PuTTY choose **Connection type: Serial**, **Serial line**: e.g. `COM3`, **Speed**: `230400`, click **Open**.

### From the firmware tree

If you have the firmware source, `./fbt cli` opens a CLI session directly; with uFBT use `ufbt cli`.

**Expected result:** a Flipper ASCII-art banner, "Welcome to Flipper Zero Command Line Interface!", the firmware
version line, and a `>:` prompt.

## Built-in and external commands

Run `help` or `?` to list the commands available on your device.

::: tip Unleashed / new CLI architecture
Most radio and peripheral commands (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`, `crypto`, `js`, `gpio`,
`led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) are **external CLI plugins** loaded from the SD card folder
`/ext/apps_data/cli/plugins` (files with the `cli_` prefix). Without an SD card — or with a damaged one — only the
core commands remain. After copying or updating plugins, run `reload_ext_cmds` instead of rebooting.
:::

### Command overview

| Command | Description |
|---|---|
| `!` | Alias for `info device` |
| `?`, `help` | List available commands |
| `bt` | Radio core (BLE) test tool — HCI version and, in debug mode, carrier/packet tests |
| `buzzer` | Play a tone or note on the piezo speaker |
| `crypto` | Secure-enclave key provisioning and AES encryption/decryption |
| `date` | Show / set date and time |
| `device_info` | Alias for `info device` (obsolete) |
| `echo` | Send received bytes back as-is (used for performance testing); stops on <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Exit the shell (useful in sub-shells like `nfc`) |
| `factory_reset` | Reset to factory settings; data on the microSD card is kept |
| `free` | Heap allocator info — general memory profiling |
| `free_blocks` | Free heap blocks and sizes — estimate fragmentation |
| `gpio` | Set mode / write / read GPIO pins |
| `i2c` | Scan the I2C bus for devices |
| `ikey` | Read, emulate and write iButton keys |
| `info` | Detailed device and power information |
| `input` | Show button events, inject button presses |
| `ir` | Receive, send, decode infrared signals; universal remotes |
| `js` | Run a JavaScript file, console output goes to the CLI |
| `led` | Control the RGB LED and the display backlight |
| `loader` | List, open and close apps |
| `log` | View the system log |
| `neofetch` | System info, like `neofetch` on Linux |
| `nfc` | NFC sub-shell: dump, emulate, raw, APDU, scanner |
| `onewire` | Scan the 1-Wire bus (iButton pins) |
| `power` | Power off, reboot, reboot to DFU, GPIO 5 V / 3.3 V |
| `reload_ext_cmds` | Reload the list of external commands from the SD card |
| `rfid` | Read, write, emulate 125 kHz cards; RAW tools |
| `sleep` | Wait for a given time, e.g. `sleep 5s` (useful in scripts) |
| `start_rpc_session` | Switch the CLI into protobuf RPC mode (used by qFlipper/apps; normally not needed) |
| `storage` | File system commands |
| `subghz` | Sub-GHz tools: rx/tx, RAW, decode, chat |
| `sysctl` | System settings: debug mode, heap tracking |
| `top` | Live list of threads (like Linux `top`); <kbd>Ctrl</kbd>+<kbd>C</kbd> to quit |
| `update` | Install an update package, back up / restore internal storage |
| `uptime` | Time since last boot |
| `vibro` | Turn the vibration motor on/off |
| `unit_tests` | Only in the `unit_tests` firmware build — see [Unit tests](/dev/unit-tests) |

## Reading logs

1. Connect to the CLI.
2. Start logging at the level you need:

   | Command | Shows |
   |---|---|
   | `log` | Current level from system settings |
   | `log error` | Only critical errors and important messages |
   | `log warn` | Warnings and non-critical errors, plus `error` |
   | `log info` | Non-critical information, plus `warn` |
   | `log default` | The default system level (= `info`) |
   | `log debug` | Debug information, plus `info` (impacts performance) |
   | `log trace` | System traces, plus `debug` (impacts performance) |

   `log ?` prints this list on the device.
3. Use the Flipper — messages appear in the terminal.
4. Stop with <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Chatting over Sub-GHz

Several Flippers on the same frequency can chat through the CLI.

1. Every participant connects to their Flipper's CLI.
2. Run `subghz chat <frequency_in_hz> <device>`, for example:

   ```
   subghz chat 868150000 0
   ```

   - frequency in Hz within 299999755–348000000, 386999938–464000000 or 778999847–928000000;
   - device `0` = internal CC1101, `1` = external CC1101 module.
3. Type a message and press <kbd>Enter</kbd>.
4. Quit with <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
Stock firmware only transmits on frequencies allowed in your region; Unleashed removes the regional TX restrictions.
Respect local radio rules.
:::

## Command reference

### bt

| Command | Description |
|---|---|
| `bt hci_info` | Bluetooth HCI information |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Debug mode only.* Start TX carrier test |
| `bt rx_carrier <channel:0-39>` | *Debug mode only.* Start RX carrier test |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Debug mode only.* Start TX packet test |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Debug mode only.* Start RX packet test |

### buzzer

| Command | Description |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Play a tone |
| `buzzer note <note> <duration>` | Play a note; `s` means sharp, e.g. `cs3` = C♯3; flats not supported |

Duration accepts `ms`, `s`, `m`, `h`, e.g. `buzzer note cs3 500ms`.

### crypto

Encrypts/decrypts with keys stored in the MCU's secure enclave.

| Command | Description |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Encrypt text with AES256-CBC, output hex |
| `crypto decrypt <key_slot> <iv_hex>` | Decrypt hex back to text |
| `crypto has_key <key_slot>` | Check whether a slot (1–100) holds a key |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Irreversible!** Store a key — it can't be removed |

- `key_slot`: slots 1–11 are pre-filled with keys used by the firmware.
- `iv_hex`: 16-byte initialisation vector in hex.
- `key_type`: `master`, `simple` or `encrypted`; `key_size`: `128` or `256`.

### gpio

| Command | Description |
|---|---|
| `gpio mode <pin_name> <0/1>` | Set pin to input (0) or output (1) |
| `gpio set <pin_name> <0/1>` | Set pin value |
| `gpio read <pin_name>` | Read pin value |

Pin names: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — see [GPIO pinout](/gpio/pinout).

### ikey

| Command | Description |
|---|---|
| `ikey read` | Read an iButton key |
| `ikey emulate <key_type> <key_data>` | Emulate a key |
| `ikey write Dallas <key_data>` | Write 8 bytes to a Dallas-compatible blank |

Key types and data length (hex): `Dallas` — 8 bytes, `Cyfral` — 2 bytes, `Metakom` — 4 bytes (must contain correct
parity).

### info

| Command | Description |
|---|---|
| `info device` | Device information (firmware, hardware, radio stack, …) |
| `info power` | Power system information |
| `info power_debug` | Detailed power information |

### input

| Command | Description |
|---|---|
| `input dump` | Print button events |
| `input send <key> <type>` | Inject an event; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

A complete short press is three commands, otherwise the input is discarded:

```
input send ok press
input send ok short
input send ok release
```

For a long press use `long` instead of `short`.

### ir

| Command | Description |
|---|---|
| `ir rx` | Receive and decode IR signals |
| `ir rx raw` | Receive in RAW format |
| `ir tx <protocol> <address> <command>` | Send a command; address and command in hex |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Send RAW data: frequency 10000–56000, duty cycle 0–100, max 512 samples |
| `ir decode <input_file> [<output_file>]` | Decode a file with RAW signals |
| `ir universal list <remote_name>` | List the signals of a universal remote |
| `ir universal <remote_name> <signal_name>` | Send a signal from a universal remote |

Protocols: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Universal remote names are taken from the files in `/ext/infrared/assets/`. Unleashed ships `tv`, `audio`, `ac`,
`projectors`, `fans` and `leds` (stock firmware has fewer). Run `ir universal list tv` to see valid signal names.
:::

### js

| Command | Description |
|---|---|
| `js <path>` | Run a JavaScript file and print its console output — see [JavaScript](/dev/js-about) |

### led

| Command | Description |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Brightness of the red / green / blue LED component |
| `led bl <0-255>` | Display backlight brightness (`128` ≈ 50%) |

For pure red: `led r 255`, `led g 0`, `led b 0`.

### loader

| Command | Description |
|---|---|
| `loader list` | List available apps |
| `loader open <Application Name> [args]` | Open an app by name, optionally with arguments |
| `loader info` | Show loader state |
| `loader close` | Close the running app |
| `loader signal <signal> [arg_hex]` | Send a signal with an optional hex argument |

Arguments that contain spaces can be quoted:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` opens a **sub-shell**. Inside it: `help` / `?` lists commands, `<command> -h` shows details, `exit` leaves.

| Command | Description |
|---|---|
| `dump -f <path>` | Dump a physical card to a `.nfc` file. Options: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Emulate a `.nfc` file |
| `field` | Turn on the 13.56 MHz field; <kbd>Ctrl</kbd>+<kbd>C</kbd> to stop |
| `scanner` | List all protocols a tag supports; `-t` shows the protocol tree |
| `raw -p <protocol> -d <data>` | Send raw bytes. Options: `-t <timeout>` (carrier cycles), `-k` keep field on, `-c` append CRC, `-s` do activation/anticollision first |
| `apdu -d <data> [<data2> ...]` | Send APDU(s) to ISO14443-4A/4B or ISO15693-3 tags; `-p 4a`/`4b`/`15` forces the protocol |
| `mfu info` | Basic info about a MIFARE Ultralight tag |
| `mfu rdbl -b <block>` | Read a block |
| `mfu wrbl -b <block> -d <data>` | Write a 4-byte block |

`dump -p` protocols: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`, `des`,
`slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
`raw -p` protocols: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Command | Description |
|---|---|
| `onewire search` | Search for 1-Wire devices |

### power

| Command | Description |
|---|---|
| `power off` | Power off |
| `power reboot` | Reboot |
| `power reboot2dfu` | Reboot into DFU mode |
| `power 5v <1/0>` | Enable/disable 5 V on GPIO pin 1 |
| `power 3v3 <1/0>` | Enable/disable 3.3 V on GPIO pin 9 (debug mode only) |

### rfid

| Command | Description |
|---|---|
| `rfid read [normal/indala/ask134]` | Read a card in ASK/PSK mode; the optional argument selects a read mode (`ask134` — 134 kHz animal tags) |
| `rfid write <key_type> <key_data>` | Write to a T5577 |
| `rfid emulate <key_type> <key_data>` | Emulate |
| `rfid raw_read <ask/ask134/psk> <filename>` | Save the raw signal to a file |
| `rfid raw_emulate <filename>` | Emulate a raw file (protocol debugging) |
| `rfid raw_analyze <filename>` | Print a raw file and try to decode it (protocol development) |

Key types and data length (hex bytes):

| Type | Bytes | Type | Bytes | Type | Bytes |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

Paths start with `/int` (internal flash) or `/ext` (SD card).

| Command | Description |
|---|---|
| `storage info /ext` | File system info and free space |
| `storage format /ext` | Format the SD card (asks for confirmation) |
| `storage list <path>` | List a directory |
| `storage tree <path>` | List recursively |
| `storage remove <path>` | Delete a file or an **empty** directory |
| `storage read <file>` | Print size and text content |
| `storage read_chunks <file> <1-512>` | Print content in blocks of the given size |
| `storage write <file>` | Append text typed in the CLI; <kbd>Ctrl</kbd>+<kbd>C</kbd> to finish |
| `storage write_chunk <file> <1-512>` | Append exactly N bytes from the CLI (input isn't echoed) |
| `storage copy <src> <dst>` | Copy a file |
| `storage rename <old> <new>` | Rename / move |
| `storage mkdir <path>` | Create a directory |
| `storage md5 <file>` | MD5 hash |
| `storage stat <path>` | File or directory info |
| `storage timestamp <file>` | Last modification time |
| `storage extract <archive.tar> <dir>` | Extract a `.tar` archive |

### subghz

| Command | Description |
|---|---|
| `subghz chat <frequency> <device>` | Chat with other Flippers |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Transmit a key (Princeton) |
| `subghz rx <frequency> <device>` | Receive and decode |
| `subghz rx_raw <frequency>` | Receive RAW |
| `subghz decode_raw <path_to_raw_file>` | Decode a `.sub` RAW file and print results |
| `subghz tx_from_file <path> <repeat> <device>` | Transmit a saved `.sub` file |

Debug mode only:

| Command | Description |
|---|---|
| `subghz tx_carrier <frequency>` | Transmit an unmodulated carrier |
| `subghz rx_carrier <frequency>` | Receive carrier (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Encrypt a KeeLoq manufacturer-key file |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Encrypt RAW data |

`device`: `0` — internal CC1101, `1` — external CC1101 ([external module](/subghz/external-cc1101)).
`te_us` — the base pulse length in µs.

Example — transmit a saved file 3 times through the internal radio:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Command | Description |
|---|---|
| `sysctl debug <0/1>` | Disable / enable system debug mode |
| `sysctl heap_track <none/main>` | Heap allocation tracking for the app's main thread; debug builds (`DEBUG=1`) also accept `tree` (main + child threads) and `all` |

### update

| Command | Description |
|---|---|
| `update install /ext/path/to/update.fuf` | Verify and install an update package (the `.fuf` manifest inside the unpacked package folder) |
| `update backup /ext/backup.tar` | Back up the internal storage |
| `update restore /ext/backup.tar` | Restore the internal storage from a backup |

See [OTA updates](/dev/ota).

### vibro

| Command | Description |
|---|---|
| `vibro <1/0>` | Turn the vibration motor on / off |

## Related pages

- [Debugging apps](/dev/debugging)
- [OTA updates](/dev/ota)
- [Unit tests](/dev/unit-tests)
- [qFlipper](/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire and ICODE are registered trademarks of NXP B.V. FeliCa is a
trademark of Sony Corporation.
