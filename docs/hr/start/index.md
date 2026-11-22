---
title: Početak rada
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Početak rada

Od novog Flipper Zera do potpuno postavljenog uređaja s firmverom **Unleashed Firmware**: tipke, radna površina, napajanje, microSD
kartica, postavke i oporavak. Ostatak wikija pretpostavlja da to već znate.

## Što je Flipper Zero?

Flipper Zero je džepni višenamjenski alat za istraživanje radijske tehnologije i sustava kontrole pristupa. Njegov hardver uključuje:

- **CC1101 Sub-GHz primopredajnik** za daljinske upravljače garaža, rampi, senzore i druge uređaje ispod 1 GHz;
- **13,56 MHz NFC** modul i **125 kHz RFID** antenu za kartice, privjeske i oznake;
- **infracrveni** odašiljač i prijemnik za televizore, klima-uređaje i druge daljinske upravljače;
- **1-Wire (iButton)** kontaktnu podlogu za Dallas, Cyfral i Metakom ključeve;
- **USB** i **Bluetooth LE**, pa može raditi kao tipkovnica (Bad USB), U2F token ili daljinski upravljač;
- **GPIO** pinove za vanjske module (vanjski CC1101, NRF24, ESP32, SIM800 i druge);
- jednobojni zaslon 128×64, 5-smjerni upravljač s tipkom Back i bateriju od 2100 mAh.

Na radnoj površini živi digitalni ljubimac dupin. Napreduje kroz razine kako koristite uređaj.

## Što je Unleashed Firmware?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) je fork službenog firmvera (OFW). Ostaje
**potpuno kompatibilan s OFW API-jem i aplikacijama** te povrh toga dodaje nove mogućnosti. Glavni dodaci:

- **bez regionalnih Sub-GHz TX ograničenja**, dodatne frekvencije i neobavezni prošireni domet;
- **mnogo više Sub-GHz protokola**, uključujući mogućnost spremanja i slanja mnogih sustava s promjenjivim kodom (rolling-code), prilagođene tipke
  i `Add manually` za nove daljinske upravljače;
- podrška za **vanjski CC1101** modul;
- dodatni NFC parseri, EMV parser, više MIFARE Classic ključeva u sistemskom rječniku;
- RFID i iButton fuzzeri, alat za T5577 i druge ugrađene aplikacije;
- poboljšanja svakodnevne uporabe: prilagođeni naziv Flippera, sat na radnoj površini, postotak baterije, Night Shift, više igara za Dummy Mode,
  BadKB (Bad USB preko Bluetootha) i još mnogo toga.

Pogledajte [Što Unleashed dodaje](/hr/start/unleashed-features) za potpuni popis s poveznicama.

::: warning Samo službeni izvori
`DarkFlippers/unleashed-firmware` jedini je službeni dom projekta. Svaki build je besplatan i otvorenog koda.
Ne postoje plaćene, "premium" ili zatvorene verzije. Svatko tko vam takvu nudi je prevarant.
:::

## Release i dev buildovi

| Build | Što je to | Gdje ga preuzeti |
|---|---|---|
| **Release** (stabilni) | Testirana izdanja, preporučena za svakodnevnu uporabu | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (testni) | Automatski buildovi s grane `dev` za testiranje novih značajki | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), Discord kanal `unleashed-development` |

Novi dev build na web-stranici zamjenjuje prethodni; stari dev buildovi ostaju sačuvani samo kao datoteke u Telegram
kanalu. Dev buildovi prvi dobivaju nove značajke, ali **mogu sadržavati greške (bugove)**. Ako pronađete grešku, prijavite je na
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Svako izdanje dolazi u tri varijante: `E` (osnovne + dodatne aplikacije), bez sufiksa (osnovne aplikacije) i `C` (bez aplikacija zajednice).
Pogledajte [Instalacija Unleasheda](/hr/start/install#which-file-to-download) za pojedinosti.

## Kanali zajednice

- Telegram razgovori: [engleski](https://t.me/flipperzero_unofficial), [ruski](https://t.me/flipperzero_unofficial_ru), [ukrajinski](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Web-stranica Unleasheda: [flipperunleashed.com](https://flipperunleashed.com)

## Stranice u ovom odjeljku

**Prvi koraci**
- [Prvo pokretanje](/hr/start/first-start): uključivanje, umetanje microSD kartice, instalacija Unleasheda
- [Instalacija Unleasheda](/hr/start/install): Web Installer, qFlipper, mobilne aplikacije, izvanmrežno ažuriranje s SD kartice
- [Ažuriranje](/hr/start/updating): održavanje sustava ažurnim, release naspram dev, što preživljava ažuriranje
- [Što Unleashed dodaje](/hr/start/unleashed-features): svaka Unleashed značajka u usporedbi s izvornim firmverom

**Korištenje uređaja**
- [Kontrole](/hr/start/controls): tipke, način za ljevake, prečaci
- [Radna površina](/hr/start/desktop): statusna traka, prečaci, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Ljubimac dupin](/hr/start/dolphin): raspoloženje, razine i XP
- [Napajanje i baterija](/hr/start/power): punjenje, gašenje, Auto PowerOff, Limit Charge
- [microSD kartica](/hr/start/sd-card): odabir, formatiranje, struktura mapa
- [Postavke](/hr/start/settings): svaka stavka izbornika Settings, jedna po jedna
- [Prilagođeni naziv Flippera](/hr/start/custom-name)

**Kada nešto pođe po zlu**
- [Kombinacije tipki](/hr/start/key-combos): kombinacije tipki za resetiranje i DFU
- [Oporavak](/hr/start/recovery): oporavak firmvera, vraćanje na tvorničke postavke, resetiranje PIN-a
- [Opasne postavke](/hr/start/dangerous-settings): prošireni Sub-GHz raspon (pročitajte prije nego što dirate)
- [Česta pitanja (FAQ)](/hr/start/faq)

::: tip Pravno
Unleashed je namijenjen eksperimentima i zakonitom istraživanju. Koristite ga na vlastitim uređajima ili uz dopuštenje.
:::
