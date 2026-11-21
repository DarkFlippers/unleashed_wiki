---
title: RFID 125 kHz
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# RFID 125 kHz

L'RFID a bassa frequenza (LF) è la tecnologia "di prossimità" usata nelle tessere e nei portachiavi di accesso
economici, nei tag dei citofoni, in alcuni sistemi per parcheggi e palestre e nei microchip per animali. Questi tag
di solito trasmettono soltanto un ID fisso, senza alcuna crittografia, ed è per questo che sono facili da leggere,
emulare e clonare.

Flipper Zero ha un'antenna a 125 kHz sul retro (sull'antenna dual-band, accanto alla bobina NFC a 13,56 MHz), pilotata
dal microcontrollore STM32WB55. Con essa il Flipper può **leggere**, **salvare**, **emulare** e **scrivere** tag LF.

::: tip Unleashed
L'app RFID 125 kHz è del firmware ufficiale. In più, la build Unleashed offre:
- un menu **Settings → Write Chips**: oltre al T5577 può scrivere **EM4305** e i cloni Hitag Micro (**8265**,
  **8210**, **H5.5**), più un target **8268** (Hitag S) attivabile a scelta. La schermata di scrittura mostra quale
  chip viene tentato e quale ha accettato la scrittura;
- **Write and set password** per le vergini T5577;
- formati aggiuntivi in **Add Manually** (inserimento di facility code / numero di tessera invece dell'esadecimale,
  HID H10304/H10302/S10401/H10306/Corp1000-35, Casi-Rusco), visualizzazione DEZ 8 / DEZ 10 per EM4100;
- una terza passata di lettura a **134,2 kHz** per i tag per animali e una modalità dedicata **Read FDX-B
  (Animals)**;
- l'app **T5577** integrata (lettura/modifica/ripristino dei blocchi, test, wipe, cancellazione e sniffing delle
  password).
:::

## Menu principale

`Main Menu → 125 kHz RFID` apre un menu con queste voci (etichette esatte prese dal firmware):

![Il menu 125 kHz RFID con Read, Saved, Add Manually ed Extra Actions](/screens/lfrfid/menu.png)

| Voce | Funzione | Pagina |
|---|---|---|
| **Read** | Rileva automaticamente e legge un tag (ciclo ASK → PSK → 134 kHz) | [Lettura dei tag](/it/rfid/read) |
| **Saved** | Sfoglia `/ext/lfrfid/` — emulare, scrivere, modificare, rinominare, eliminare le chiavi salvate | [Lettura dei tag](/it/rfid/read), [Scrittura](/it/rfid/write) |
| **Add Manually** | Crea una chiave dal suo protocollo e dal suo ID | [Aggiunta manuale](/it/rfid/add-manually) |
| **Extra Actions** | Lettura con modulazione fissa (ASK, PSK, FDX-B); lettura/emulazione RAW in modalità Debug | [Lettura dei tag](/it/rfid/read), [RAW](/it/rfid/raw) |
| **Settings** | **Write Chips** — quali tipi di vergine può usare una scrittura | [Scrittura](/it/rfid/write) |

## Pagine di questa sezione

- [Lettura dei tag](/it/rfid/read) — leggere, salvare ed emulare i tag LF; lettura con modulazione fissa.
- [Scrittura su vergini](/it/rfid/write) — quali vergini funzionano (T5577, EM4305, Hitag Micro, 8268),
  l'impostazione Write Chips, scrittura con password, messaggi di errore.
- [Aggiunta manuale](/it/rfid/add-manually) — tutti i protocolli di Add Manually e i formati di inserimento FC/ID.
- [Protocolli supportati](/it/rfid/protocols) — tabella completa dei protocolli: modulazione, dimensione dei dati,
  campi decodificati, supporto alla scrittura.
- [Microchip per animali](/it/rfid/animal-microchips) — chip FDX-B / FDX-A per animali domestici.
- [T5577 e Hitag Micro (di @gromovyna)](/it/rfid/t5577-hitag) — la storia di H5.5 / 8265 / 8210, l'esperienza di
  scrittura, il wipe del T5577.
- [App T5577](/it/rfid/t5577-app) — lettura, modifica, ripristino, test, wipe, cancellazione e sniffing della
  password a livello di blocco.
- [Registrazione RAW](/it/rfid/raw) — registrare il segnale ASK/PSK grezzo per la ricerca sui protocolli.
- [Fuzzer](/it/rfid/fuzzer) — cosa fornisce il firmware per l'app RFID Fuzzer.
- [Formati dei file](/it/rfid/file-format) — i file `.rfid`, `.t5577` e `.raw`.

## Dove si trovano i file

| Percorso | Contenuto |
|---|---|
| `/ext/lfrfid/*.rfid` | Chiavi salvate |
| `/ext/lfrfid/*.t5577` | Dump dei blocchi T5577 (aperti dall'app T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | Registrazioni RAW |
| `/ext/lfrfid/.lfrfid.settings` | Impostazione Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Dizionario di password T5577 (sovrascritto a ogni aggiornamento) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Le tue password T5577 |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Nomi dei paesi per i chip FDX-B |

::: warning
Clona ed emula soltanto tag di tua proprietà o che sei autorizzato a testare.
:::
