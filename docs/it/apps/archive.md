---
title: Archive (browser dei file)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (browser dei file)

**Archive** è il browser dei file del Flipper. Elenca le chiavi, le tessere, i telecomandi e gli script che hai
salvato, permette di eseguirli subito e si occupa della gestione di base dei file: aggiungere ai preferiti,
rinominare, copiare, spostare, creare cartelle ed eliminare.

**Come aprirlo:** dal desktop premi <kbd>↓</kbd>.

![Archive sulla scheda Sub-GHz: una cartella Garage e i segnali .sub salvati, con Barrier selezionato](/screens/apps/archive.png)

## Schede

Premi <kbd>←</kbd> / <kbd>→</kbd> per cambiare scheda. Ogni scheda mostra una cartella, filtrata per tipo di file:

| Scheda | Cartella | File mostrati |
|---|---|---|
| Favorites | i tuoi file preferiti | tutto ciò che hai aggiunto ai preferiti (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` (mappe di [Sub-GHz Remote](/it/subghz/remote)) |
| RFID LF | `/ext/lfrfid` | `.rfid` e dump T5577 |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` (rubrica di [SIM800](/it/gpio/sim800)) |
| U2F | interno | la voce dell'app U2F |
| Apps | `/ext/apps` | `.fap` e `.js` |
| Internal | memoria flash interna | tutto (solo con la modalità Debug attiva) |
| Browser | tutta la scheda SD | tutto |

L'Archive si apre su **Favorites**.

::: tip Unleashed
Unleashed aggiunge la scheda **SubRem** per le mappe di Sub-GHz Remote, la scheda **Phone** per la rubrica di SIM800
(una voce `.phone` si apre direttamente nell'app SIM800), mostra i dump T5577 accanto alle chiavi in **RFID LF** ed
elenca gli script `.js` in **Apps**.
:::

## Pulsanti nell'elenco

| Pulsante | Azione |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | scorre l'elenco (tieni premuto per scorrere più rapidamente) |
| <kbd>←</kbd> / <kbd>→</kbd> | scheda precedente / successiva |
| <kbd>OK</kbd> su un file | apre il suo menu |
| <kbd>OK</kbd> su una cartella | entra nella cartella |
| <kbd>OK</kbd> tenuto premuto su una cartella | apre il menu della cartella |
| <kbd>OK</kbd> in Favorites | esegue subito il file |
| <kbd>OK</kbd> tenuto premuto in Favorites | apre il menu |
| <kbd>OK</kbd> tenuto premuto in una cartella vuota | apre il menu (Paste / NewDir) |
| <kbd>Back</kbd> | sale di una cartella, oppure esce |

## Il menu del file: Actions e Manage

Il menu ha due pagine. Il titolo indica quale è aperta: **Actions** o **Manage**. Premi <kbd>←</kbd> o <kbd>→</kbd>
all'interno del menu per passare dall'una all'altra (non nella scheda Favorites). <kbd>↑</kbd> / <kbd>↓</kbd>
selezionano una voce, <kbd>OK</kbd> la esegue, <kbd>Back</kbd> chiude il menu.

**Actions** (per un file che il firmware sa aprire):

- **Run**: apre il file nella sua app (emula una chiave, invia un segnale, esegue uno script...).
- **Pin** / **Unpin**: aggiunge ai preferiti o li rimuove da essi.
- **Info**: nome e dimensione del file.
- **Show**: visualizza il file come testo (per i formati testuali).

Per un tipo di file sconosciuto, Actions propone solo **Info** e, per i file di testo, **Show**.

**Manage:**

- **Cut** / **Copy**, poi **Paste** nella cartella di destinazione.
- **NewDir**: crea una cartella.
- **Rename**: digita un nuovo nome.
- **Delete**: chiede prima una conferma.

Nella scheda **Favorites** il menu è composto da **Run**, **Unpin**, **Show** (se applicabile) e **Move**. Move
permette di riordinare i preferiti: premi <kbd>↑</kbd> / <kbd>↓</kbd> per spostare la voce e <kbd>OK</kbd> per salvare
la nuova posizione (<kbd>Back</kbd> annulla).

## Operazioni frequenti

### Aggiungere un file ai preferiti

1. Desktop → <kbd>↓</kbd> per aprire l'Archive.
2. Vai alla scheda giusta con <kbd>←</kbd> / <kbd>→</kbd> e seleziona il file.
3. Premi <kbd>OK</kbd> → **Pin**. Il file compare ora nella scheda Favorites.

### Rinominare una chiave o un segnale salvato

1. Seleziona il file e premi <kbd>OK</kbd>.
2. Premi <kbd>→</kbd> per passare al menu **Manage**.
3. Scegli **Rename**, digita il nome, confermalo.

### Eliminare file per liberare spazio

1. Seleziona il file, <kbd>OK</kbd>, <kbd>→</kbd> per andare a **Manage**.
2. Scegli **Delete** e conferma.

Per svuotare un'intera cartella usa la scheda **Browser**: seleziona la cartella, tieni premuto <kbd>OK</kbd>,
**Manage → Delete**.

### Spostare un file in un'altra cartella

1. Seleziona il file, <kbd>OK</kbd>, **Manage → Cut**.
2. Vai alla cartella di destinazione (la scheda **Browser** raggiunge ogni cartella della scheda SD).
3. Premi <kbd>OK</kbd> su qualunque file (o tieni premuto <kbd>OK</kbd> in una cartella vuota) → **Paste**.

## Risoluzione dei problemi

- **"Empty"** significa che la cartella non contiene file del tipo previsto da quella scheda. Controlla l'estensione:
  un file `.ir` in `/ext/nfc` non comparirà in nessuna delle due schede, ma la scheda Browser lo mostra.
- **La scheda Internal non c'è**: è visibile solo quando `Settings → System → Debug` è su ON.
- **Un preferito è sparito**: i preferiti il cui file non esiste più (spostato, rinominato o eliminato fuori
  dall'Archive) vengono tolti dall'elenco. Aggiungi di nuovo il file ai preferiti nella sua nuova posizione.
- **Delete** chiede sempre `Delete <name>?` con i pulsanti **Cancel** / **Delete**, così nulla viene rimosso per una
  pressione accidentale.

## Pagine correlate

- [Scheda microSD](/it/start/sd-card)
- [App sulla scheda SD](/it/apps/sd-card-apps)
- [Desktop](/it/start/desktop)
