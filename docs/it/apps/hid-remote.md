---
title: Telecomando USB / Bluetooth (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# Telecomando USB / Bluetooth (HID)

L'app HID fa apparire il Flipper come una tastiera, un mouse o un telecomando multimediale (un **H**uman
**I**nterface **D**evice USB) agli occhi di un computer, di un telefono o di un tablet. La stessa app è compilata due
volte:

| App | Dove si trova sul Flipper | Connessione |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | cavo USB |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Come collegarlo è spiegato in [Associare il telecomando HID](/it/apps/controllers). Questa pagina descrive tutte le
modalità.

## Modalità

Il menu iniziale elenca:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

La versione Bluetooth ha inoltre `Bluetooth Remote Name` e `Bluetooth Unpairing`.

::: tip Unleashed
La documentazione ufficiale descrive Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler e Mouse Clicker. La build
Unleashed dell'app offre anche **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**,
**PushToTalk** e **Bluetooth Remote Name** per cambiare il nome con cui il telecomando si annuncia.
:::

In quasi tutte le modalità, **tieni premuto <kbd>Back</kbd> per uscire** e tornare all'elenco delle modalità; tutti i
tasti vengono rilasciati all'uscita.

### Keynote e Keynote Vertical

Un telecomando per presentazioni. Keynote Vertical è identico, ruotato per tenere il Flipper in verticale.

| Pulsante | Invia |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | tasti freccia (diapositiva successiva / precedente) |
| <kbd>OK</kbd> | Spazio |
| <kbd>Back</kbd> | Backspace + "AC Back" (esce dalla modalità presentazione nella maggior parte delle app) |
| <kbd>Back</kbd> tenuto premuto | esce |

### Keyboard

Una tastiera QWERTY a schermo con cifre, simboli, F1-F12, Esc, Tab, Enter, Backspace, Delete e i modificatori Ctrl,
Alt, Shift e Cmd (Win).

1. Spostati con le frecce, premi <kbd>OK</kbd> per digitare il tasto selezionato.
2. Seleziona il tasto ⬆ (Shift) per scrivere in maiuscolo e per la seconda fila di simboli.
3. Per una scorciatoia premi prima il modificatore (Ctrl, Alt o Cmd) e poi il tasto.
4. Tieni premuto <kbd>Back</kbd> per uscire.

### Numpad

Un tastierino numerico: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Invio del tastierino), `NL` (Num Lock) e Backspace. Le
frecce selezionano, <kbd>OK</kbd> preme il tasto, <kbd>Back</kbd> tenuto premuto esce.

### Media

| Pulsante | Invia |
|---|---|
| <kbd>OK</kbd> | Play / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | traccia precedente / successiva |
| <kbd>↑</kbd> / <kbd>↓</kbd> | alza / abbassa il volume |
| <kbd>Back</kbd> tenuto premuto | esce |

Sui telefoni i tasti del volume funzionano anche da pulsante di scatto: apri la fotocamera e premi <kbd>↑</kbd> o
<kbd>↓</kbd> per scattare una foto o avviare/fermare un video.

### Apple Music macOS

| Pulsante | Invia |
|---|---|
| <kbd>OK</kbd> | Play / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | traccia precedente / successiva |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (volume in Apple Music) |
| <kbd>Back</kbd> tenuto premuto | esce |

### Movie

| Pulsante | Invia |
|---|---|
| <kbd>OK</kbd> | Play / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | freccia sinistra / destra (avanzamento nella maggior parte dei player) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | alza / abbassa il volume |
| <kbd>Back</kbd> tenuto premuto | esce |

### Mouse

| Pulsante | Azione |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | muove il cursore; tenendo premuto accelera |
| <kbd>OK</kbd> | clic sinistro |
| <kbd>OK</kbd> tenuto premuto | mantiene premuto il pulsante sinistro (trascinamento, "Selecting...") |
| <kbd>Back</kbd> | clic destro |
| <kbd>Back</kbd> tenuto premuto | esce |

### TikTok / YT Shorts

Per le app di video brevi su telefono o tablet.

| Pulsante | Azione |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | scorre al video precedente / successivo |
| <kbd>OK</kbd> | doppio tocco (mi piace) |
| <kbd>←</kbd> / <kbd>→</kbd> | abbassa / alza il volume |
| <kbd>Back</kbd> | tocco singolo (pausa) |
| <kbd>Back</kbd> tenuto premuto | esce |

::: tip iPhone / iPad
Se su iOS la modalità TikTok non fa nulla, attiva
`Settings → Accessibility → Touch → AssistiveTouch`, poi in **Pointer Devices → Devices → Bluetooth Devices**
seleziona il tuo Flipper.
:::

### Mouse Clicker

Fa clic automaticamente a una cadenza impostata.

| Pulsante | Azione |
|---|---|
| <kbd>OK</kbd> | Avvia / Ferma |
| <kbd>↑</kbd> / <kbd>↓</kbd> | clic al secondo, fino a 100 (predefinito 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | quale pulsante: sinistro, destro o rotella (centrale) |
| <kbd>Back</kbd> | esce |

### Mouse Jiggler

Muove un poco il cursore a intervalli fissi, così il computer non va in sospensione e non ti mostra come "assente".

1. Prima di avviarlo, scegli l'intervallo con <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 o 60000 ms
   (predefinito 5000 ms).
2. Premi <kbd>OK</kbd> per **Start**, di nuovo per **Stop**. Finché l'host non si collega, lo schermo indica
   `Waiting for Connection...`.
3. <kbd>Back</kbd> esce.

### Mouse Jiggler Stealth

Come il jiggler, ma si muove a intervalli casuali tra un minimo e un massimo che imposti in minuti (da 1 a 30), il che
risulta meno riconoscibile come comportamento automatico. Mentre è fermo, <kbd>↑</kbd> / <kbd>↓</kbd> cambiano il
minimo e <kbd>→</kbd> / <kbd>←</kbd> aumentano / riducono il massimo; <kbd>OK</kbd> avvia o ferma.

### PushToTalk

Un pulsante di silenziamento / push-to-talk per le videochiamate.

1. Scegli l'elenco del tuo sistema operativo (**macOS** o **Win/Linux**), poi l'app: Google Meet, Google Meet Global,
   Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle, TeamSpeak, Teams,
   Webex, Zoom o Zoom Global.
2. Tieni premuto <kbd>OK</kbd> su una voce dell'elenco per leggerne la guida (alcune app richiedono un'impostazione o
   un'estensione, per esempio una scorciatoia globale per Google Meet o l'associazione dei tasti in TeamSpeak).
3. Durante la chiamata: <kbd>Back</kbd> commuta il microfono, **<kbd>OK</kbd> tenuto premuto** attiva il push-to-talk
   (il microfono si spegne al rilascio), <kbd>→</kbd> tenuto premuto cambia lo stato del microfono sul Flipper se si è
   desincronizzato da quello del computer. Per Zoom, una pressione prolungata di <kbd>←</kbd> invia Invio.
4. Tieni premuto <kbd>Back</kbd> per uscire.

### Bluetooth Remote Name e Bluetooth Unpairing (solo Bluetooth)

- **Bluetooth Remote Name**: digita un nome in `Bluetooth Name`; il telecomando si annuncia con quel nome. Per
  impostazione predefinita compare come `Control <nome del Flipper>`.
- **Bluetooth Unpairing**: chiede `Unpair All Devices? All previous pairings will be lost!`; premi **Unpair** per
  dimenticare ogni host associato al telecomando. Il telecomando mantiene le proprie chiavi di associazione
  (`/ext/apps_data/hid_ble/.bt_hid.keys`), separate dalle associazioni Bluetooth principali del Flipper.

## Pagine correlate

- [Associare il telecomando HID](/it/apps/controllers)
- [Bad USB](/it/badusb/usage)
- [App incluse in Unleashed](/it/apps/catalog)
