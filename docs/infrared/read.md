---
title: Learning and sending signals
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Learning and sending IR signals

Flipper Zero can copy the buttons of an IR remote one by one and keep them as a **virtual remote**: a `.ir` file
in `/ext/infrared/`. Use it when the original remote is lost, broken or in another room, or when a universal
remote does not find your device.

Signals of [known protocols](/infrared/protocols) are decoded and saved in a compact *parsed* form (protocol +
address + command). Anything else is saved as **RAW** timings, which also works for playback.

## Learn a new remote

1. Go to `Main Menu → Infrared → Learn New Remote`.
2. The screen says **"Point the remote at IR port and push the button"**. Hold the remote a few centimetres from
   the top edge of the Flipper, in line of sight of the IR window.

   ![Learn New Remote waiting for a signal: "Point the remote at IR port and push the button"](/screens/infrared/learn.png)

3. Press the button on the remote **briefly**. Don't hold it: a held button gives a long capture full of repeats.
4. The capture screen appears:
   - a decoded signal shows the protocol name and the address/command, e.g. `NECext`, `A: 0x87EE`, `C: 0xA05D`;
   - an unknown signal shows **Unknown** and the number of samples, e.g. `150 samples`.

   ![Capture screen: the decoded protocol NEC with its address and command, and Retry, Send and Save at the bottom](/screens/infrared/learn_success.png)

5. Choose what to do:
   - <kbd>OK</kbd> **Send**: replays the captured signal while you hold the button, to test it right away;
   - <kbd>←</kbd> **Retry**: asks *"Retry Reading? All unsaved data will be lost!"*, then <kbd>←</kbd> Exit
     throws the capture away and listens again, <kbd>→</kbd> Stay goes back;
   - <kbd>→</kbd> **Save**: continue to naming.
6. Enter a button name in **"Name the button"** (max. 23 characters) and confirm. The default name is generated from
   the signal: the first 4 letters of the protocol and the command (e.g. `NECe_A05D`), or `RAW_<samples>` for RAW.
7. **"Success!"** is shown and the new remote opens. The first remote is saved as `/ext/infrared/Remote.ir`; if that
   name is taken, `Remote1.ir`, `Remote2.ir` and so on.

![Captured signal on the screen](/img/remote/a62fc8f9d738534b.png)

::: tip Rename the remote
A fresh remote is always called `Remote`. Rename it right away via `Edit → Rename Remote` (see below), otherwise
you'll end up with `Remote`, `Remote1`, `Remote2`…
:::

### Add more buttons

In the remote's button list, scroll to the bottom and select **`+`**. The learning screen opens again. Capture,
**Save**, name the button, and you get **"Saved"**: the button is appended to the same file.

Pressing <kbd>Back</kbd> on the capture screen asks *"Exit to Infrared Menu?"* (or *"Exit to Remote Menu?"* when
adding to an existing remote): unsaved data is lost if you choose Exit.

## Send a saved button

1. Go to `Main Menu → Infrared → Saved Remotes` and pick a `.ir` file.
2. Point the Flipper's top edge at the device.
3. Select a button with <kbd>↑</kbd> / <kbd>↓</kbd> and press <kbd>OK</kbd>.

The signal is sent **for as long as you hold** <kbd>OK</kbd>: one press for a single command, hold it for "press and
hold" actions such as volume ramping. The LED blinks while transmitting.

![Sending a saved signal](/img/remote/d20ed673954c3711.png)

::: tip Favorites and Archive
Saved remotes also show up in the **Archive** (`Main Menu → Archive → Infrared`) and can be added to favorites
there. In Flipper Mobile App they appear under **Archive → Infrared**, see [Remotes in the mobile app](/infrared/mobile).
:::

## Edit a remote

Open a remote and select **Edit** at the very bottom of the button list. The Edit menu has:

| Item | What it does |
|---|---|
| **Add Button** | Learn one more button (same as `+`). |
| **Rename Button** | Pick a button, enter a new name. |
| **Move Button** | Screen *"Select a Button to Move"*: select a button, press <kbd>OK</kbd> to pick it up (it shifts right), move it with <kbd>↑</kbd> / <kbd>↓</kbd>, press <kbd>OK</kbd> again to drop it. |
| **Delete Button** | Pick a button. Confirmation *"Delete Button?"* shows its name and protocol / address / command (or `RAW`, sample count). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Renames the remote and the file. If the name exists, a number is added. |
| **Delete Remote** | Confirmation *"Delete Remote?"* with the number of buttons. Deletes the `.ir` file. |

Names are limited to **23 characters** both for buttons and remotes. Larger edits (merging files, removing many
buttons) are easier on a PC: download the file with [qFlipper](/mobile/qflipper) and edit it as text, see the
[IR file format](/infrared/file-format).

::: warning Library files are not remotes
If you try to open a file from `/ext/infrared/assets/` via Saved Remotes, you get *"Library file … can't be opened as a
remote"*. Library files (`Filetype: IR library file`) are only used by [Universal remotes](/infrared/universal-remotes).
:::

## Debug mode extras

With `Settings → System → Debug` ON, the Infrared menu shows two more items:

- **Learn New Remote RAW**: the same flow as Learn, but the decoder is disabled and every signal is stored as RAW.
  Useful when the decoder recognises a protocol but the decoded playback doesn't work on your device.
- **Debug RX**: the *"INFRARED monitor"* screen that shows what the receiver gets in real time.

## Troubleshooting

| Problem | What to try |
|---|---|
| Nothing happens when pressing the remote | Check the remote's batteries (look at its LED through a phone camera). Get closer and point straight at the top edge. Avoid direct sunlight and fluorescent / LED lamps nearby. |
| Signal is captured as **Unknown / RAW** although the remote is common | Interference can force RAW. Use **Retry** a few times until you get a decoded signal. If it really is an unknown protocol, RAW is fine. |
| Huge RAW captures (hundreds of samples) | You held the button. Do a quick press; around 100 samples is typical for a single press. Very long captures play back slowly. A RAW signal can hold at most 1024 timings. |
| Device doesn't react to the saved button | Get closer, point directly at the device's IR window. Try sending it a few times or holding <kbd>OK</kbd> longer. For long distances use an [external IR module](/infrared/external-ir). |
| AC reacts wrongly | AC remotes send the full state (mode, temperature, fan) in every press. Record each state you need as its own button, see [Contributing captures](/infrared/captures#air-conditioners). |
| "Failed to load …" when sending | The `.ir` file is damaged or was edited by hand incorrectly. Check it against the [file format](/infrared/file-format). |

## Related pages

- [Universal remotes](/infrared/universal-remotes)
- [Remotes in the mobile app](/infrared/mobile)
- [IR file format](/infrared/file-format)
- [External IR modules](/infrared/external-ir)
