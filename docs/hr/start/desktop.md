---
title: Radna površina
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Radna površina

Radna površina (Desktop) je početni zaslon. Ovdje živi vaš [dupin](/hr/start/dolphin), a duž vrha proteže se statusna traka.
S radne površine pojedinačni pritisci tipki otvaraju glavni izbornik, Archive, Lock Menu i vaše omiljene aplikacije.

## Statusna traka

Gornji redak prikazuje male ikone:

| Ikona | Značenje |
|---|---|
| Baterija | Razina napunjenosti. Tijekom punjenja prikazuje munju. Stil se postavlja u `Battery View` |
| SD kartica | microSD kartica je montirana. Prekrižena ikona znači da se kartica nije uspjela montirati: pogledajte [microSD kartica](/hr/start/sd-card) |
| Bluetooth | BLE je uključen. Drugačija ikona znači da je uređaj povezan |
| Lokot | Flipper je zaključan |
| Utišani zvučnik | Nečujni način (Stealth): zvuk i vibracija su isključeni (pogledajte [Lock Menu](#lock-menu)) |
| Računalo | Povezan s qFlipperom / Flipper Labom putem USB-a |
| Gamepad | Dummy Mode je uključen |
| Modul | Povezan je modul za proširenje |
| Beacon | Način rada BLE beacon (na primjer FindMy Flipper) |
| Pozadinska aplikacija | Aplikacija radi u pozadini |

::: tip Unleashed
- **Settings → Desktop → Battery View** bira stil prikaza baterije: `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` prikazuje sat na radnoj površini. Format (24h/12h) preuzima se iz
  **Settings → System → Time Format**.
:::

## Tipke na radnoj površini

| Tipka | Kratki pritisak | Dugi pritisak |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Lock** (uz PIN ako je postavljen) |
| <kbd>↓</kbd> | **Archive** | Zaslon s informacijama o uređaju / debugiranjem |
| <kbd>←</kbd> | Favorite App - Left Short (zadano izbornik **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | Zadano **Passport** (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Zaslon za **Power off** |

### Zaslon s informacijama o uređaju {#info-screen}

Dugi pritisak tipke <kbd>↓</kbd> otvara zaslon s informacijama: inačica i datum izgradnje firmvera, inačica hardvera, vrijeme rada (uptime), naziv Flippera i je li Debug `ON`/`OFF`.

![Zaslon s informacijama o uređaju: inačica firmvera, inačica hardvera, vrijeme rada i stanje Debuga](/screens/desktop/debug.png)

Na tom zaslonu **dugi pritisak tipke <kbd>OK</kbd> uključuje ili isključuje Debug** — ista sklopka kao
`Settings → System → Debug` ([Postavke](/hr/start/settings)), bez prolaska kroz izbornike. Kratki pritisak <kbd>BACK</kbd>
vraća vas na radnu površinu.

`Debug` postavljen na `ON` dodaje stavke koje su inače skrivene: karticu **Internal** u [Archive](#archive) i
`Signal Settings` u izborniku spremljenih Sub-GHz signala ([Postavke signala](/hr/subghz/signal-settings)). Ponovno ga isključite
kada završite — postavke za debugiranje usporavaju Flipper i sprječavaju odlazak u stanje mirovanja.

## Main Menu

Pritisnite <kbd>OK</kbd>. Glavni izbornik otvara se na stavci **Apps** (sve `.fap` aplikacije sa SD kartice, grupirane po
kategorijama), nakon čega slijede **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock** i **Settings** na kraju. Popis je kružni, pa pritisak <kbd>↑</kbd> na stavci **Apps**
odmah skače na **Settings**.

![Glavni izbornik s odabranom stavkom Apps, Settings iznad i Sub-GHz ispod](/screens/mainmenu/main.png)

::: tip Stilovi izbornika
**Settings → Desktop → Menu Style** mijenja izgled glavnog izbornika. Stilovi su dodaci u mapi
`/ext/apps_data/loader/plugins/` (datoteke koje počinju s `menu_style_`). `Default` je ugrađeni popis.
:::

## Lock Menu {#lock-menu}

Pritisnite <kbd>↑</kbd> na radnoj površini. Pomičite se pomoću <kbd>↑</kbd>/<kbd>↓</kbd> i pritisnite <kbd>OK</kbd>:

| Stavka | Što radi |
|---|---|
| **Turn Bluetooth On / Off** | Uključuje ili isključuje BLE bez ulaska u Settings |
| **Mute / Unmute** | Nečujni način (Stealth): bez zvuka i bez vibracije. Postavke **Volume** i **Vibro** prikazuju `Stealth` dok je uključen |
| **Dummy Mode / Default Mode** | Ulazak ili izlazak iz načina [Dummy Mode](#dummy-mode) |

Pritisnite <kbd>←</kbd> ili <kbd>→</kbd> u izborniku Lock Menu za otvaranje druge stranice, **Quick Settings**:

| Stavka | Upravljanje |
|---|---|
| Brightness | <kbd>OK</kbd> za uređivanje, zatim <kbd>←</kbd>/<kbd>→</kbd> (ili <kbd>↑</kbd>/<kbd>↓</kbd>), u koracima od 5 % |
| Volume | Isto. Čuje se kratki zvučni signal kako biste čuli novu razinu |
| Vibro | <kbd>OK</kbd> odmah uključuje ili isključuje |

<kbd>BACK</kbd> napušta stavku koja se uređuje, a drugi <kbd>BACK</kbd> zatvara stranicu. Promjene se spremaju u iste
postavke kao **LCD and Notifications**.

::: tip Unleashed
U firmveru Unleashed, **samo zaključavanje** izvodi se dugim pritiskom tipke <kbd>↑</kbd> na radnoj površini: s PIN-om ako je postavljen, ili kao obično zaključavanje inače.
:::

## Zaključavanje i PIN

- **Zaključavanje:** držite <kbd>↑</kbd> na radnoj površini. Bez PIN-a, tipke su zaključane. **Za otključavanje brzo pritisnite
  <kbd>BACK</kbd> tri puta**.
- **S PIN-om:** postavite ga u **Settings → Desktop → PIN Setup → Set PIN**. PIN se sastoji od 4 do 10 pritisaka strelica. Zaključani
  Flipper tada traži PIN. Nakon pogrešnih pokušaja prikazuje `Wrong PIN!` i vrijeme čekanja prije sljedećeg pokušaja.
- **Automatsko zaključavanje:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) zaključava uređaj nakon toliko
  neaktivnosti. **Auto Lock disarm by active USB session** = `ON` sprječava automatsko zaključavanje dok je Flipper povezan putem USB-a.

::: warning Zaboravljeni PIN
Zaboravljeni PIN može se resetirati samo zajedno sa svim korisničkim postavkama: pogledajte [Oporavak → Resetiranje zaboravljenog PIN-a](/hr/start/recovery#reset-pin).
Datoteke na microSD kartici ostaju sačuvane.
:::

## Dummy Mode {#dummy-mode}

Dummy Mode pretvara Flipper u igračku. Većina funkcija je skrivena, a tipke pokreću aplikacije koje sami odaberete, poput igara. Uključite ga u **Lock Menu → Dummy Mode**, a isključite putem **Lock Menu → Default Mode**.

U načinu Dummy Mode svaka tipka može pokrenuti vlastitu aplikaciju. Postavite ih u **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

Nedodijeljena tipka otvara Passport. Kratki pritisak <kbd>↑</kbd> i dalje otvara Lock Menu. Ako je `DummyMode - Up Long` postavljen
na `None`, dugi pritisak <kbd>↑</kbd> zaključava uređaj.

::: tip Unleashed
Tvornički firmver ima 4 prečaca za Dummy Mode. Unleashed ih ima 9 (kratki i dugi pritisak na svakoj tipki), tako da
možete držati nekoliko igara na jedan pritisak od sebe.
:::

## Omiljene aplikacije (brzi pristup)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Za svako mjesto možete odabrati:
- **Apps Menu (Default)** ili **Passport (Default)**: ugrađena zadana radnja za to mjesto;
- **None (disable)**: tipka ne radi ništa;
- **Lock Flipper**;
- bilo koju aplikaciju iz glavnog izbornika;
- **[Select App]**: odaberite bilo koju `.fap` datoteku iz `/ext/apps/`.

## Arhiva {#archive}

Pritisnite <kbd>↓</kbd>. Archive prikazuje vaše spremljene datoteke razvrstane u kartice. Kartice mijenjajte pomoću <kbd>←</kbd>/<kbd>→</kbd>:

| Kartica | Mapa / sadržaj |
|---|---|
| Favorites | Datoteke koje ste prikvačili |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: mape aplikacije Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` i T5577 izvadci) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: SIM800 imenik (`.phone`) |
| U2F | U2F token |
| Apps | `/ext/apps` (`.fap` i `.js`) |
| Internal | Unutarnja memorija (samo uz **Debug** = `ON`) |
| Browser | Cijela microSD kartica |

Pritisnite <kbd>OK</kbd> na datoteci za otvaranje kontekstnog izbornika: pokretanje/emulacija, **Pin**/**Unpin** (dodavanje u Favorites),
**Rename**, **Delete**, a u kartici Browser i **Cut**, **Copy**, **Paste** te **NewDir**. U kartici Favorites
držite <kbd>OK</kbd> za otvaranje izbornika.

::: tip Prikvačivanje postavki u Favorites
U izborniku **Main Menu → Settings** držite <kbd>OK</kbd> na bilo kojoj stavci postavki da biste je prikvačili u Favorites. Tada je možete otvoriti iz
izbornika Archive bez prolaska kroz izbornike.
:::

## Passport

Pritisnite <kbd>→</kbd> na radnoj površini ili otvorite **Settings → Passport**. Prikazuje ime dupina (naziv Flippera), raspoloženje
i razinu: pogledajte [Kućni ljubimac dupin](/hr/start/dolphin).
