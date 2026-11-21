---
title: App
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# App

Oltre ai grandi strumenti integrati (Sub-GHz, NFC, RFID, Infrarossi, iButton, Bad USB, GPIO), Flipper Zero esegue
delle **app**: piccoli programmi distribuiti come file `.fap` che risiedono sulla scheda microSD. Unleashed include
una serie di app di sistema proprie in ogni build, offre due pacchetti di app opzionali (Base ed Extra) e resta
compatibile con l'Apps Catalog ufficiale.

::: tip Unleashed
Unleashed mantiene la compatibilità di API con il firmware ufficiale, quindi in genere funzionano anche le app del
catalogo ufficiale (Flipper Lab o app mobile). Inoltre ogni release di Unleashed ha una build `e` che preinstalla il
pacchetto **Extra Apps** di app della comunità. Vedi [App incluse in Unleashed](/it/apps/catalog).
:::

## Ottenere ed eseguire le app

- [App incluse in Unleashed](/it/apps/catalog): le app integrate, i pacchetti Base ed Extra e il significato delle lettere di build `e`, ` ` e `c`.
- [App sulla scheda SD (.fap)](/it/apps/sd-card-apps): dove risiedono le app, come installarle a mano o dal catalogo e come il loader verifica la versione delle API.
- [Archive (browser dei file)](/it/apps/archive): sfogliare, eseguire, aggiungere ai preferiti, rinominare, spostare ed eliminare i file salvati.
- [Risoluzione dei problemi con le app](/it/apps/troubleshoot): cosa significa ciascun errore del loader e come rimediare.

## App integrate

- [Chiave di sicurezza U2F](/it/apps/u2f): usare il Flipper come secondo fattore FIDO U2F.
- [Clock](/it/apps/clock): orologio notturno con regolazione della luminosità, cronometro e sveglia giornaliera.
- [Telecomando USB / Bluetooth (HID)](/it/apps/hid-remote): tutte le modalità dell'app telecomando HID, pulsante per pulsante.
- [Associare il telecomando HID](/it/apps/controllers): collegare il telecomando via Bluetooth o USB e risolvere i problemi di associazione.
- [FindMy Flipper](/it/apps/find-my-flipper): rendere il Flipper visibile in Apple Find My, Samsung SmartThings, Tile o Google Find My Device.
- [Stili del menu principale](/it/apps/menu-styles): cambiare l'aspetto del menu principale (PS4, Wii, DSi, C64, CoverFlow, Grid e altri).
- [Snake](/it/apps/snake): il gioco classico.

## App dei pacchetti

- [Barcode Generator](/it/apps/barcode)
- [Multi Converter](/it/apps/multi-converter)
- [Sentry Safe](/it/apps/sentry-safe)

Le app di supporto per Sub-GHz, NFC e RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 e altre) sono trattate nelle
rispettive sezioni, per esempio [Seed Capturer](/it/subghz/seed-capturer), [App MFKey](/it/nfc/mfkey-app) e
[App T5577](/it/rfid/t5577-app).
