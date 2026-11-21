---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

L'app **Bad USB** trasforma il Flipper in una tastiera (e in un mouse) che digita su un computer uno script
preparato in precedenza. Il computer vede un normale Human Interface Device (HID), quindi non serve alcun driver. Gli
script si scrivono in un **DuckyScript** esteso (il linguaggio dell'USB Rubber Ducky) e sono memorizzati come file
`.txt` in testo semplice sulla scheda microSD.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Usi legittimi tipici: automatizzare configurazioni ripetitive sulle tue macchine, digitare password o configurazioni
lunghe, installare software su un PC appena preparato, dimostrazioni e formazione sulla consapevolezza della
sicurezza.

::: danger Aspetti legali
Un dispositivo di keystroke injection può fare tutto ciò che può fare una persona alla tastiera. Esegui gli script
solo su computer di tua proprietà o che ti è espressamente consentito testare.
:::

L'app funziona via cavo **USB** o via **Bluetooth (BLE)**; in quest'ultimo caso appare all'host come una tastiera
Bluetooth.

::: tip Unleashed
Unleashed integra **BadKB** (di Willy-JL, ClaraCrazy e dei contributori XFW) direttamente nell'app Bad USB:
- **modalità BLE** con nome del dispositivo, indirizzo MAC, modalità di pairing e pairing persistente configurabili,
  più i comandi di script `BLE_ID` / `BT_ID`;
- impostazioni dell'**identità USB**: nome del produttore e del prodotto, VID/PID, randomizzazione;
- **layout di tastiera** per molte lingue ([a cura di rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- il comando **`DUCKY_LANG`**, con cui uno script può scegliere il proprio layout di tastiera (nuovo nella release
  attuale, PR #1224 di @ANTONiO-eagle).
:::

## File

| Percorso | Contenuto |
|---|---|
| `/ext/badusb/` | I tuoi script (`.txt`). Il file browser dell'app si apre qui. |
| `/ext/badusb/examples/` | Script dimostrativi inclusi nel firmware (Windows, macOS, GNOME, ChromeOS, test del mouse, installer di qFlipper). |
| `/ext/badusb/assets/layouts/` | File dei layout di tastiera (`.kl`). Vedi [Layout di tastiera](/it/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Impostazioni dell'app: layout globale, modalità USB/BLE, identità USB e BLE. |

Carica gli script con [qFlipper](/it/mobile/qflipper), con l'[app mobile](/it/mobile/mobile-app) oppure copiandoli
sulla scheda SD. Un file con lo stesso nome viene sovrascritto senza avvisi.

## Pagine di questa sezione

| Pagina | Cosa impari |
|---|---|
| [Usare Bad USB](/it/badusb/usage) | Eseguire gli script via USB e BLE, il menu Config, tutte le impostazioni |
| [Formato degli script](/it/badusb/script-format) | Riferimento completo dei comandi: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, mouse, ID, DUCKY_LANG… |
| [Esempi](/it/badusb/examples) | Script di esempio sicuri da cui partire |
| [Layout di tastiera](/it/badusb/layouts) | Quali layout esistono, come funzionano, come scegliere uno per script |
