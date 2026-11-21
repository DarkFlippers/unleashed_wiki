---
title: Remotes in the mobile app
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# IR remotes in Flipper Mobile App

Flipper Mobile App (iOS / Android) has a **Remotes Library**: an online database of IR remotes. You pick your device
type and brand, the app finds the right remote by testing a few signals, downloads it to the Flipper, and then shows
a proper remote layout on your phone screen. The Flipper does the actual transmitting.

Compared to [Universal remotes](/infrared/universal-remotes), which send the whole library on every press, a remote
from the Remotes Library is found **once** and then works instantly. It also has more buttons and covers more device
types.

## What you can find

The library includes remotes for, among others: TVs, projectors, TV boxes, fans, air purifiers, DVD players, cameras
and AV receivers. The database is open source: [flipperdevices/IRDB](https://github.com/flipperdevices/IRDB); you can
contribute your remote following its
[contribution guide](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md).

::: tip Unleashed
The mobile app works with Unleashed the same way as with stock firmware: it talks to the Infrared app over RPC.
While the phone controls it, the Flipper screen shows **"Infrared – RPC mode"**. Remotes downloaded from the app are
regular `.ir` files in `/ext/infrared/` and can be used, edited and renamed on the Flipper like any learned remote.
More on the app itself: [Flipper Mobile App](/mobile/mobile-app).
:::

## Find the remote for your device

1. Connect the Flipper to the app over Bluetooth.
2. In the app go to `Tools → Remotes Library`.
3. Select the **device type**, then the **brand**.
4. Many brands have several remotes, so the app tests signals one by one: point the Flipper at the device, tap the
   button to send the signal and answer whether the device reacted.
5. When the right remote is found, the app shows its layout. You can use it right away.
6. Tap **Save** (top right) and give the remote a name. It is written to the Flipper.
7. *(Optional)* Tap **⋯ → Add to Favorites** to have it in the Archive tab for quick access.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Use a saved remote

**From the phone.** In the app open `Archive → Infrared` (or Favorites), select the remote, point the Flipper at the
device and tap the buttons on the phone. The app tells the Flipper which signal to send.

![Remote layout in the app](/img/remote/7387cb59433e202d.jpg)

**From the Flipper only.** Go to `Main Menu → Infrared → Saved Remotes`, open the remote, choose a button with
<kbd>↑</kbd> / <kbd>↓</kbd> and press <kbd>OK</kbd>. See [Learning and sending signals](/infrared/read#send-a-saved-button).

## Troubleshooting

| Problem | What to try |
|---|---|
| The app can't send / nothing happens | Make sure the Flipper is connected and not busy in another app. Close any running app on the Flipper and try again. |
| No remote found for your brand | Learn the original remote on the Flipper ([how](/infrared/read)) or try [Universal remotes](/infrared/universal-remotes). |
| Device reacts only from very close | Use an [external IR module](/infrared/external-ir); the app uses the transmitter selected in the Infrared GPIO Settings. |

## Related pages

- [Flipper Mobile App](/mobile/mobile-app)
- [Universal remotes](/infrared/universal-remotes)
- [IR file format](/infrared/file-format)
