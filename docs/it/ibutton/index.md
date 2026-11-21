---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

Una chiave iButton ("touch memory", nei paesi della CSI spesso chiamata *таблетка*, "pastiglia") è una chiave
racchiusa in un piccolo involucro d'acciaio che si legge appoggiandola a un lettore. La maggior parte parla il
protocollo Dallas **1-Wire**; i citofoni usano anche chiavi **Cyfral** e **Metakom**. Flipper Zero è in grado di
leggere, salvare, emulare e scrivere queste chiavi.

## Hardware

Il modulo iButton è una piazzola di contatto con tre pogo pin a molla montati sul PCB iButton.

- I due pin esterni sono i dati (collegati al **pin GPIO 17**), quello centrale è la **massa**.
- **Lettura / scrittura di una chiave**: la chiave tocca la **parte piatta** della piazzola — pin dati di sinistra +
  pin di massa centrale.
- **Emulazione verso un lettore**: la **parte sporgente** della piazzola tocca il lettore — pin dati di destra +
  massa centrale.
- Se la massa non riesce a raggiungere la corona del lettore, usa due fili: GPIO **17** (dati) e GPIO **8, 11 o 18**
  (massa).

## Menu principale

`Main Menu → iButton`:

![Il menu iButton con Read, Saved, Add Manually e Settings](/screens/ibutton/menu.png)

| Voce | Funzione | Pagina |
|---|---|---|
| **Read** | Rileva il tipo di chiave e legge il suo ID (e la memoria per DS1992/1996/1971) | [Lettura](/it/ibutton/read) |
| **Saved** | Sfoglia `/ext/ibutton/` — emulare, scrivere, modificare, rinominare, eliminare | [Lettura](/it/ibutton/read), [Scrittura](/it/ibutton/write) |
| **Add Manually** | Crea una chiave da protocollo + ID esadecimale | [Aggiunta manuale](/it/ibutton/add-manually) |
| **Settings** | **Write Blanks** — quali tipi di chiavi vergini può usare una scrittura | [Scrittura](/it/ibutton/write) |

::: tip Unleashed
Rispetto alla documentazione ufficiale, Unleashed aggiunge una pagina **Settings → Write Blanks** (RW1990.1,
RW1990.2, TM2004, TM01x), mostra quale vergine viene tentata durante una scrittura e quale l'ha accettata, scrive
chiavi **Cyfral e Metakom** su vergini **TM01x** e supporta il **DS1420**. Il ReadMe elenca anche un plugin iButton
Fuzzer.
:::

## Pagine di questa sezione

- [Lettura delle chiavi](/it/ibutton/read) — leggere, salvare, emulare, errori di CRC.
- [Scrittura su chiavi vergini](/it/ibutton/write) — RW1990, TM2004, TM01x; Write ID contro Full Write on Same Type.
- [Aggiunta manuale](/it/ibutton/add-manually) — creare chiavi a partire da un ID.
- [Protocolli supportati](/it/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, 1-Wire generico, Cyfral,
  Metakom.
- [Fuzzer](/it/ibutton/fuzzer) — cosa fornisce il firmware per l'app iButton Fuzzer.
- [Formato dei file](/it/ibutton/file-format) — i file `.ibtn`.

## File

| Percorso | Contenuto |
|---|---|
| `/ext/ibutton/*.ibtn` | Chiavi salvate (prefisso di nome predefinito `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Impostazione Write Blanks |

::: warning
Copia ed emula soltanto chiavi di tua proprietà o che sei autorizzato a testare.
:::
