---
title: Web-alati
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Web-alati

Nekoliko alata za Flipper radi izravno u pregledniku, bez ikakve instalacije. Alati koji komuniciraju s Flipperom preko USB-a trebaju
**Web Serial API**, stoga koristite **Chrome, Edge ili drugi preglednik temeljen na Chromiumu**.

::: warning Prvo zatvorite qFlipper
Alat u pregledniku ne može se povezati dok qFlipper (ili druga kartica Flipper Laba) drži Flipperov serijski priključak. To je
najčešći razlog zašto "Chrome ne vidi Flipper".
:::

## Alati za Unleashed

| Alat | Adresa | Što radi |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | instalacija ili ažuriranje firmvera Unleashed (Release ili Dev) preko USB-a |
| Dev izdanja | [dev.unleashedflip.com](https://dev.unleashedflip.com) | automatska testna izdanja iz grane dev s novim značajkama |
| Karta Sub-GHz i koordinata | [map.unleashedflip.com](https://map.unleashedflip.com) | pregled Sub-GHz wardriving datoteka i svih drugih datoteka s koordinatama na karti |
| Karta Wi-Fi wardrivinga | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | spajanje i prikaz više snimki u WiGLE formatu (ESP32 Marauder i drugi) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | programiranje popularnih ESP32 modula iz preglednika |

### Unleashed Web Installer {#unleashed-web-installer}

Preporučeni način za instalaciju firmvera Unleashed.

1. Provjerite je li umetnuta **microSD kartica**.
2. Zatvorite qFlipper. Povežite Flipper USB podatkovnim kabelom.
3. Otvorite [web.unleashedflip.com](https://web.unleashedflip.com) u pregledniku temeljenom na Chromiumu.
4. Pritisnite **Connect** i odaberite svoj Flipper u skočnom prozoru preglednika.
5. Odaberite granu **Release** ili **Dev**.
6. Pritisnite **Install** i pričekajte. Kada završi, svi su resursi instalirani i Flipper se pokreće u Unleashed.

Alternativno, svako [GitHub izdanje](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) ima poveznicu
**Install via Web Updater** koja otvara izdanje u web-ažuriraču Flipper Laba: pritisnite **Connect**, zatim
**Install**. Potpune upute: [Instalacija firmvera Unleashed](/hr/start/install).

### Karta Sub-GHz i koordinata

[map.unleashedflip.com](https://map.unleashedflip.com) prikazuje vaše Sub-GHz snimke s koordinatama (na primjer iz
Sub-GHz wardrivinga s GPS modulom) i sve druge datoteke koje sadrže koordinate na karti.

### Karta Wi-Fi wardrivinga

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) spaja više snimki u **WiGLE formatu**, iz alata
ESP32 Marauder i sličnih, te prikazuje pristupne točke na jednoj karti. Pogledajte [ESP32 i Wi-Fi moduli](/hr/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) programira popularne ESP32 module iz preglednika,
bez instaliranja dodatnih alata za programiranje. Pogledajte [ESP32](/hr/gpio/esp32) i [Dev board](/hr/gpio/devboard).

## Flipper Lab (službeni)

[lab.flipper.net](https://lab.flipper.net) je službeni paket web-alata. Radi s firmverom Unleashed:

- [Apps](https://lab.flipper.net/apps): službeni katalog aplikacija, instalacija / ažuriranje / brisanje aplikacija preko USB-a, pogledajte
  [Aplikacije na SD kartici](/hr/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): terminal za naredbeni redak Flippera, pogledajte [CLI](/hr/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): vizualizacija Sub-GHz RAW signala, korisno za analizu nepoznatog
  daljinskog upravljača.
- **Web updater** koji koriste poveznice "Install via Web Updater".

## Ostale poveznice

- Početna stranica Unleasheda: [flipperunleashed.com](https://flipperunleashed.com)
- Izravne `.tgz` poveznice za ažuriranje: [unleashedflip.com](https://unleashedflip.com)
- JSON direktorij za uFBT gradnje: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Čuvajte se lažnih stranica
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) jedina je službena stranica
projekta. Ne postoje plaćene, premium ni verzije zatvorenog koda; svatko tko nudi takvo što je prevarant.
:::

## Povezane stranice

- [Instalacija firmvera Unleashed](/hr/start/install)
- [qFlipper](/hr/mobile/qflipper)
- [Prateća aplikacija qUnleashed](/hr/mobile/qunleashed-app)
