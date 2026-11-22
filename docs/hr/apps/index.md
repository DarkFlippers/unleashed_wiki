---
title: Aplikacije
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Aplikacije

Uz velike ugrađene alate (Sub-GHz, NFC, RFID, Infrared, iButton, Bad USB, GPIO), Flipper Zero pokreće i **aplikacije**: male programe zapakirane kao `.fap` datoteke koji se nalaze na microSD kartici. Unleashed sa svakom inačicom isporučuje skup vlastitih sistemskih aplikacija, nudi dva neobavezna paketa aplikacija (Base i Extra) te ostaje kompatibilan sa službenim katalogom aplikacija (Apps Catalog).

::: tip Unleashed
Unleashed ostaje API-kompatibilan sa službenim firmverom, pa aplikacije iz službenog kataloga (Flipper Lab ili mobilna aplikacija) u pravilu također rade. Osim toga, svako izdanje Unleasheda ima `e` inačicu koja unaprijed instalira paket **Extra Apps** s aplikacijama zajednice. Pogledajte [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog).
:::

## Preuzimanje i pokretanje aplikacija

- [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog): ugrađene aplikacije, paketi Base i Extra te što znače slova `e`, ` ` i `c` u oznaci inačice.
- [Aplikacije na SD kartici (.fap)](/hr/apps/sd-card-apps): gdje se aplikacije nalaze, kako ih instalirati ručno ili iz kataloga te kako učitavač provjerava verziju API-ja.
- [Archive (preglednik datoteka)](/hr/apps/archive): pregledavanje, pokretanje, prikvačivanje, preimenovanje, premještanje i brisanje spremljenih datoteka.
- [Rješavanje problema s aplikacijama](/hr/apps/troubleshoot): što znači pojedina pogreška učitavača i kako je otkloniti.

## Ugrađene aplikacije

- [Sigurnosni ključ U2F](/hr/apps/u2f): koristite Flipper kao FIDO U2F drugi čimbenik provjere autentičnosti.
- [Clock](/hr/apps/clock): noćni sat s regulacijom svjetline, štopericom i dnevnim alarmom.
- [USB / Bluetooth daljinski upravljač (HID)](/hr/apps/hid-remote): svi načini rada HID daljinskog upravljača, tipka po tipka.
- [Uparivanje HID daljinskog upravljača](/hr/apps/controllers): povezivanje daljinskog upravljača putem Bluetootha ili USB-a i rješavanje problema s uparivanjem.
- [FindMy Flipper](/hr/apps/find-my-flipper): učinite Flipper vidljivim u Apple Find My, Samsung SmartThings, Tile ili Google Find My Device.
- [Stilovi glavnog izbornika](/hr/apps/menu-styles): promijenite izgled glavnog izbornika (PS4, Wii, DSi, C64, CoverFlow, Grid i drugi).
- [Snake](/hr/apps/snake): klasična igra.

## Aplikacije iz paketa

- [Generator crtičnih kodova](/hr/apps/barcode)
- [Multi Converter](/hr/apps/multi-converter)
- [Sentry Safe](/hr/apps/sentry-safe)

Pomoćne aplikacije za Sub-GHz, NFC i RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 i druge) obrađene su u vlastitim odjeljcima, primjerice [Seed Capturer](/hr/subghz/seed-capturer), [aplikacija MFKey](/hr/nfc/mfkey-app) i [aplikacija T5577](/hr/rfid/t5577-app).
