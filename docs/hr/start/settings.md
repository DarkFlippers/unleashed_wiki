---
title: Postavke
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Postavke

**Main Menu → Settings** sadrži ove stavke, redoslijedom kojim se pojavljuju na uređaju:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

Na ovakvim popisima krećete se pomoću <kbd>↑</kbd>/<kbd>↓</kbd>, mijenjate vrijednost pomoću <kbd>←</kbd>/<kbd>→</kbd> i otvarate
stavku koja ima podzaslon pomoću <kbd>OK</kbd>.

![Izbornik Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Prikvačite postavku u Favorites
Zadržite <kbd>OK</kbd> na bilo kojoj stavci na popisu Settings da biste je prikvačili (ili otkvačili) na karticu **Favorites** u Archiveu.
To vam omogućuje brzi pristup s radne površine pomoću <kbd>↓</kbd>.
:::

::: info
Većina aplikacija postavki (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input, LCD and Notifications, Passport)
su `.fap` datoteke koje ažuriranje firmvera instalira u `/ext/apps/assets/`. **Power**, **Storage** i **System**
ugrađeni su u firmver i rade čak i bez SD kartice.
:::

## About

Informativni zasloni. Krećite se između njih pomoću **Next** (<kbd>→</kbd>) i **Prev.** (<kbd>←</kbd>):

1. obavijest **Unleashed Firmware**: samo u eksperimentalne svrhe, nije za nezakonitu upotrebu;
2. licenca: firmver je besplatan i otvorenog koda te *"If you paid any money for it - you got scammed."*;
3. *"Community apps included in all builds except `c` build"* i poveznica na github.com/DarkFlippers;
4. proizvod, model, FCC ID / IC;
5. poveznica o usklađenosti i adresa proizvođača;
6. **HW Version Info**: verzija hardvera, regija, naziv Flippera, serijski broj;
7. **FW Version Info**: verzija i datum izgradnje, git hash, verzija API-ja, radijski stog, cilj (target) i grana (branch).

## Bluetooth

| Stavka | Vrijednosti / radnja |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Prikazuje `Broken` ako je radijski stog oštećen ([Oporavak](/hr/start/recovery)) |
| **Unpair All Devices** | Potvrdite s **Unpair**. Uklanja sva uparivanja, uključujući ključeve uparivanja za Bad USB preko Bluetootha (BadKB), Bluetooth Remote i Authenticator |

Koristite **Unpair All Devices** ako se mobilna aplikacija više ne povezuje nakon instalacije ili promjene naziva. Pogledajte [Česta pitanja (FAQ)](/hr/start/faq).

## Clock & Alarm

Jedan zaslon s tri retka: **Time** (hh:mm:ss), **Date** (dd.mm.yyyy) i **Alarm** (hh:mm, `On`/`Off`).

1. Odaberite redak pomoću <kbd>↑</kbd>/<kbd>↓</kbd> i polje pomoću <kbd>←</kbd>/<kbd>→</kbd>.
2. Pritisnite <kbd>OK</kbd> za uređivanje i promijenite vrijednost pomoću <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Pritisnite <kbd>OK</kbd> ili <kbd>BACK</kbd> za završetak uređivanja.

Kada alarm zvoni, <kbd>BACK</kbd> ga **odgađa (snooze)** na 9 minuta, a bilo koja druga tipka ga zaustavlja. Alarm koji nitko
ne zaustavi isključuje se sam nakon 10 minuta. Aplikacija **Clock** u glavnom izborniku prikazuje veliki sat i ima kontrole
svjetline, alarm i odbrojavanje (timer).

## Desktop

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **PIN Setup** | → podizbornik | **Set PIN** / **Change PIN** / **Remove PIN**. PIN se sastoji od 4–10 pritisaka strelica |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Zaključavanje nakon neaktivnosti |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Bez automatskog zaključavanja dok je spojen putem USB-a |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Stil ikone baterije |
| **Show Clock** | `OFF` / `ON` | Sat na radnoj površini |
| **Menu Style** | `Default` + instalirani stilovi | Izgled glavnog izbornika. Stilovi su dodaci `menu_style_*` u `/ext/apps_data/loader/plugins/`. Prikazuje `Missing` ako je odabrana datoteka stila obrisana |
| **Change Flipper Name** | tekst | [Prilagođeni naziv Flippera](/hr/start/custom-name) |
| **Happy Mode** | Enable / Disable | Dupin se nikada ne ljuti ([Ljubimac dupin](/hr/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | aplikacija | Aplikacije za brzi pristup s radne površine |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | aplikacija | Aplikacije za [Dummy Mode](/hr/start/desktop#dummy-mode) |

Za svaki Favorite/Dummy utor možete odabrati **Apps Menu (Default)** ili **Passport (Default)**, **None (disable)**,
**Lock Flipper**, bilo koju aplikaciju iz glavnog izbornika ili **[Select App]** za odabir bilo kojeg `.fap` programa iz `/ext/apps/`.

::: warning PIN
Zaslon za postavljanje upozorava: *"Forgotten PIN can only be reset with entire device."* Resetiranje PIN-a ujedno briše vaše postavke
(datoteke na SD kartici ostaju sačuvane): pogledajte [Oporavak](/hr/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock i 9 Dummy Mode utora dodaci su Unleashed firmvera.
:::

## Expansion Modules

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **Listen UART** | `USART` (pinovi 13, 14), `LPUART` (pinovi 15, 16), `None` | Koji UART sluša module koji koriste protokol proširenja (na primjer [Video Game Module](/hr/gpio/video-game-module)) |

Postavite na `None` ako ne koristite takve module. Time štedite energiju i omogućujete Flipperu da ode u stanje mirovanja.

## Input

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Povratna vibracija na događaje tipki. Veći brojevi daju dulji impuls |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Kada se vibracija aktivira |

## LCD and Notifications

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Kontrast zaslona |
| **LCD Backlight** | `0%` … `100%` (korak 5 %) | Svjetlina pozadinskog osvjetljenja |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Vrijeme gašenja pozadinskog osvjetljenja |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Prigušuje pozadinsko osvjetljenje za ovu vrijednost tijekom noćnog prozora |
| **. Start** | `17:00` … `23:30` | Početak noćnog prozora (zaključano dok je Night Shift `OFF`) |
| **. End** | `05:00` … `11:30` | Kraj noćnog prozora |
| **LED Brightness** | `0%` … `100%` | Svjetlina statusne LED diode |
| **Volume** | `0%` … `100%` | Glasnoća zvučnika (`Stealth` kada je utišan iz Lock Menua) |
| **Vibro** | `OFF` / `ON` | Vibracija (`Stealth` kada je utišana) |
| **LCD Inversion** | `OFF` / `ON` | Invertira boje zaslona |
| **RGB Mod Settings** | → podizbornik | Samo za Flippere s **hardverskom preinakom** RGB pozadinskog osvjetljenja |

**RGB Mod Settings** (<kbd>OK</kbd> na stavci): **RGB backlight installed** (`OFF`/`ON`). Ostale stavke ostaju zaključane
(`RGB MOD OFF!`) dok ovo nije postavljeno na `ON`: **LED 1 Color**, **LED 2 Color**, **LED 3 Color**, **Effects** (`OFF`, `Rainbow`,
`Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`), **. Saturation**, **. Wave wide** (`1`–`3`).

::: danger RGB mod
Uključite **RGB backlight installed** **samo** ako vaš Flipper ima
[hardversku preinaku RGB pozadinskog osvjetljenja](https://github.com/quen0n/flipperzero-firmware-rgb#readme). Na tvorničkom Flipperu
pozadinsko osvjetljenje prestaje raditi. Ako se to dogodilo, vratite se ovamo i postavite ga na `OFF` (pogledajte [FAQ](/hr/start/faq#backlight-does-not-work)).
:::

## Passport

Profil dupina: ime, raspoloženje i razina. Otvara se i tipkom <kbd>→</kbd> na radnoj površini. Pogledajte [Ljubimac dupin](/hr/start/dolphin).

## Power

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **Battery Info** | — | Napunjenost, napon, struja, temperatura, zdravlje |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Ponovno pokretanje u DFU način rada (`Reboot to DFU Mode?`) ili obično ponovno pokretanje |
| **Power OFF** | — | Isključivanje |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Isključivanje nakon neaktivnosti |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Zaustavljanje punjenja na ovoj razini |

Više: [Napajanje i baterija](/hr/start/power).

## Storage

| Stavka | Opis |
|---|---|
| **About Internal Storage** | Podaci o internoj pohrani (`Virtual (/.int on SD)`) i slobodnoj flash memoriji |
| **About SD Card** | Oznaka kartice, vrsta, veličina, slobodni prostor, proizvođač i serijski broj |
| **Unmount SD Card** / **Mount SD Card** | Sigurno uklanjanje / ponovno montiranje |
| **Format SD Card** | Brisanje i formatiranje kartice |
| **Benchmark SD Card** | Test brzine SPI sučelja |
| **Factory Reset** | Pritisnite **Erase** 5 puta. Briše internu pohranu i ponovno pokreće uređaj |

Više: [microSD kartica](/hr/start/sd-card), [Oporavak](/hr/start/recovery#factory-reset).

## System

| Stavka | Vrijednosti | Opis |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Način za ljevake: rotira zaslon i preslikava tipke |
| **Units** | `Metric` / `Imperial` | Mjerne jedinice (na primjer °C/°F u Battery Info) |
| **Time Format** | `24h` / `12h` | Format sata |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Format datuma |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Koliko se zapisuje u dnevnik. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART koji se koristi za zapisnike (USART = pinovi 13/14, LPUART = pinovi 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Brzina UART-a za zapisnike |
| **Debug** | `OFF` / `ON` | Način za otklanjanje pogrešaka: dodatne debug značajke u aplikacijama, kartica **Internal** u Archiveu, SWD pristup |
| **Heap Trace** | `None`, `Main` | Praćenje dodjele memorije (za razvojne programere) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` troši više energije (~9 mA u odnosu na ~1,5 mA), ali može biti stabilniji |
| **File Naming** | `Default` / `Detailed` | `Detailed` dodaje vrstu, datum i vrijeme u nazive novih datoteka |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

**Debug** ima prečac: zadržite <kbd>↓</kbd> na radnoj površini, zatim zadržite <kbd>OK</kbd> na zaslonu s informacijama
([Radna površina → Zaslon s informacijama o uređaju](/hr/start/desktop#info-screen)).

::: warning Spor Flipper?
Za uobičajenu upotrebu ostavite **Log Level** = `None` (ili `Default`), **Debug** = `OFF` i **Heap Trace** = `None`. Debug
postavke usporavaju uređaj i sprječavaju odlazak u stanje mirovanja.
:::

## Povezano

- [Radna površina](/hr/start/desktop): što postavke radne površine čine u praksi
- [Prilagođeni naziv Flippera](/hr/start/custom-name)
- [Postavke za Sub-GHz](/hr/subghz/settings): radijske postavke unutar aplikacije Sub-GHz
