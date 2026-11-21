---
title: "Devboard: debugging and logs"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: debugging and logs

With the [Devboard set up](/gpio/devboard), you can debug the firmware from VS Code and read the Flipper's logs over
UART.

## How it works

The Devboard is the debug probe between the debugger on your computer (over USB or Wi-Fi) and the Flipper's MCU. It
talks to the Flipper over **Serial Wire Debug**:

- **pin 10** — SWCLK (Serial Wire Clock);
- **pin 12** — SWDIO (Serial Wire Debug Data I/O).

![Devboard hardware](/img/remote/06e0a9eb98e4130d.jpg)

## Debug modes

| Connection | Available modes |
|---|---|
| Wi-Fi | Black Magic only |
| USB | Black Magic (default) or DAPLink |

Black Magic mode doesn't support RTOS thread awareness; everything else works.

### Switching the USB mode

Oddly enough, the USB mode is switched over Wi-Fi:

1. Open the board's web interface (<http://192.168.4.1> in access point mode or <http://blackmagic.local> in client
   mode, see [connection](/gpio/devboard)).
2. In the **WiFi** tab, set **USB mode** to **BlackMagicProbe** or **DapLink**.
3. Click **SAVE**, then **REBOOT**.
4. In VS Code select the matching debugger (below).

## Debugging the firmware in VS Code

### Prerequisites

1. Install [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Clone and build the firmware. For Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (The same steps work with the stock `flipperdevices/flipperzero-firmware` repository.) More on building:
   [Build the firmware](/dev/build), [FBT](/dev/fbt).

### Start a session

1. Flash the firmware you just built through the Devboard:

   ```bash
   ./fbt flash
   ```

2. Open the firmware folder in **VS Code** and install the recommended extensions (notification, or `@recommended` in
   the Extensions tab).
3. Generate the VS Code configuration:

   ```bash
   ./fbt vscode_dist
   ```

4. In **Run and Debug**, choose:
   - **Attach FW (blackmagic)** — over Wi-Fi or USB;
   - **Attach FW (DAP)** — USB only, board in DAPLink mode.

   Over USB the debugger must match the board's **USB mode** (check it in the web interface).
5. Click ▷ **Start Debugging**. The firmware halts when the session starts; click **Continue** in the toolbar to let it
   run.

![Debugging in VS Code](/img/remote/92c6a616e2e5f86f.jpg)

See also the [VS Code debugging guide](https://code.visualstudio.com/docs/editor/debugging) and [Debugging](/dev/debugging).

## Reading logs

The Devboard reads the Flipper's log output from its UART, independently of the Flipper's OS. So you see logs during
boot, updates and crashes, which the CLI `log` command can't show. Logs are available **over USB only**.

### Set the log level and device

1. Open `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: keep `USART` (pins 13/14), which is where the Devboard listens. `LPUART` sends logs to pins 15/16,
   `None` disables UART logging.

::: tip
If another module needs pins 13/14 (Wi-Fi board, SIM800, GPS), set `Log Device` to `LPUART` or `None` so log output
doesn't interfere with it.
:::

### macOS

1. Install [Homebrew](https://brew.sh/), then `brew install minicom`.
2. Power the Flipper off, plug in the Devboard, power on.
3. Run `ls /dev/cu.*`, connect the Devboard by USB, run it again. Two new devices appear, e.g.
   `/dev/cu.usbmodemblackmagic1` and `/dev/cu.usbmodemblackmagic3`.
4. Open the one with the **higher number**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Logs stream in the terminal. Quit via the minicom menu or close the window.

### Linux

1. Install minicom, e.g. `sudo apt install minicom`.
2. Power the Flipper off, plug in the Devboard, power on.
3. Run `ls /dev/tty*`, connect the Devboard by USB, run it again. Two new devices appear, e.g. `/dev/ttyACM0` and
   `/dev/ttyACM1`.
4. Open the one with the higher number:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. If nothing shows up, try the other device.

### Windows

1. Install [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Power the Flipper off, plug in the Devboard, power on, connect the Devboard by USB.
3. In **Device Manager → Ports (COM & LPT)** note the new COM port.
4. In PuTTY choose **Serial**, enter the port in **Serial line**, set **Speed** to **230400**, click **Open**.

![PuTTY settings](/img/remote/2bb43453a91a142e.jpg)

## Related

- [Devboard: getting started](/gpio/devboard)
- [Devboard: firmware update](/gpio/devboard-firmware)
- [CLI](/dev/cli)
