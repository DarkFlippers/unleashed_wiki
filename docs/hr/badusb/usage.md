---
title: Korištenje Bad USB-a
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Korištenje Bad USB-a

Nazivi izbornika i poruke u nastavku navedeni su točno onako kako se pojavljuju u firmveru.

::: warning
Skripte pokrećite samo na računalima u vašem vlasništvu ili na onima za koja imate dopuštenje za testiranje. Pročitajte skriptu prije pokretanja: ona će izvršiti sve što u njoj piše, s ovlastima vašeg korisnika.
:::

## Prije početka

- Potrebna je microSD kartica s resursima firmvera. Bez nje aplikacija prikazuje *"No SD card or app data found. This app will not work without required files."*
- Stavite svoju skriptu (`.txt`) u `/ext/badusb/` (podmape su podržane).
- **USB način preuzima USB priključak Flippera.** Ako su qFlipper ili [CLI](/hr/dev/cli) povezani putem USB-a, aplikacija prikazuje *"Connection Is Active! Disconnect from PC or phone to use this function."* Prvo zatvorite qFlipper.

## Glavni zaslon

1. Otvorite `Main Menu → Bad USB`.
2. Odaberite skriptu u pregledniku datoteka. Otvara se zaslon skripte.

Gornji redak prikazuje naziv skripte, ispod njega raspored tipkovnice u zagradama, `(default)` ili npr. `(de-DE)`, te proteklo vrijeme ili u BLE načinu PIN za uparivanje. Slika u sredini prikazuje USB utikač ili Bluetooth simbol.

![Zaslon Bad USB skripte: učitan demo_windows, 0/34 redaka, naznake Config / Run / BLE](/screens/badusb/script_ready.png)

| Stanje | Tekst na zaslonu | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Mirovanje / Gotovo / nije povezano | napredak ili *Connect to device* | **Run** | **Config** | prebacivanje na **BLE** / **USB** |
| Čekanje veze nakon Run | *Will run on connect* | **Cancel** | | |
| Izvršavanje ili u naredbi `DELAY` | `line/total`, postotak, `Delay Ns` | **Stop** | | **Pause** |
| Pauzirano | *Paused* | **End** | | **Resume** |
| Čekanje na `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Pogreška | *ERROR:* + `line N` + poruka | | | |

Ako pritisnete **Run** prije nego što glavno računalo prepozna Flipper, aplikacija čeka (*"Will run on connect"*) i automatski pokreće skriptu **1,5 s nakon uspostave veze**, kako bi računalo imalo vremena instalirati tipkovnicu.

Dok glavno računalo nije povezano, pješčani sat i *Connect to device* zamjenjuju prikaz napretka:

![Bad USB čeka USB glavno računalo, zaslon prikazuje Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> napušta zaslon skripte i vraća se u preglednik datoteka.

## Pokretanje putem USB-a

1. Zatvorite qFlipper na računalu.
2. `Main Menu → Bad USB` → odaberite skriptu.
3. Provjerite prikazuje li zaslon sliku **USB**; ako ne, pritisnite <kbd>→</kbd> **USB**.
4. Neobavezno: <kbd>←</kbd> **Config → Keyboard Layout (global)** za usklađivanje s rasporedom na računalu (zadano `en-US`).
5. Povežite Flipper s računalom USB kabelom.
6. Pritisnite <kbd>OK</kbd> **Run**. Napredak `line/total` teče do 100 %.

![Bad USB izvršava skriptu: 32 %, redak 12 od 34, naznake Stop i Pause](/screens/badusb/script_running.png)

![Bad USB u USB načinu](/img/remote/d49323518c0b4b18.jpg)

## Pokretanje putem Bluetootha (BLE)

1. Provjerite je li Bluetooth uključen na Flipperu (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → odaberite skriptu.
3. Pritisnite <kbd>→</kbd> **BLE**; pojavljuje se Bluetooth slika. Flipper se počinje oglašavati kao tipkovnica.
4. Na računalu ili telefonu otvorite Bluetooth postavke i povežite se s **`BadUSB <ime vašeg Flippera>`** (zadani naziv).
5. Potvrdite uparivanje na oba uređaja. Uz zadani način uparivanja isti se PIN prikazuje na oba zaslona; potvrdite da se podudara. PIN se također prikazuje na zaslonu skripte.
6. Pritisnite <kbd>OK</kbd> **Run**.
7. Za kasnije uklanjanje uparivanja: <kbd>←</kbd> **Config → Remove BLE Pairing**, a zatim zaboravite uređaj i na glavnom uređaju.

![Bad USB u BLE načinu](/img/remote/083420027c3f836c.jpg)

::: tip Odvojeni identitet i uparivanje
U BLE načinu Flipper koristi **vlastitu MAC adresu** (izvedenu iz Flipperove MAC adrese) i vlastitu pohranu uparivanja, odvojenu od uobičajenog Bluetooth profila. Uparivanje računala s Bad USB-om stoga ne prekida uparivanje s aplikacijom Flipper Mobile App. Kada izađete iz aplikacije, vraća se uobičajeni Bluetooth profil.
:::

## Skripte koje same mijenjaju način rada

Ako je **prvi redak** skripte naredba `ID` (USB) ili `BLE_ID` / `BT_ID` (Bluetooth), aplikacija se pri otvaranju skripte automatski prebacuje na taj način rada i primjenjuje zadani identitet. I dalje možete ručno prebacivati pomoću <kbd>→</kbd>. Pogledajte [Format skripte → ID uređaja](/hr/badusb/script-format#device-id).

## Izbornik Config

<kbd>←</kbd> **Config** dostupan je samo dok se skripta ne izvršava. Sadržaj ovisi o trenutačnom načinu povezivanja.

### Zajedničke postavke

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| **Keyboard Layout (global)** | preglednik datoteka | Odabire `.kl` datoteku iz `/ext/badusb/assets/layouts/`. Primjenjuje se na svaku skriptu koja ne postavlja vlastiti raspored pomoću `DUCKY_LANG`. Pogledajte [Rasporedi tipkovnice](/hr/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Isto kao <kbd>→</kbd> na glavnom zaslonu. Popis u nastavku mijenja se sukladno tome. |

### BLE način

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | ON (zadano): povezuje se s glavnim uređajem i pamti ga kako bi se ponovno spojio bez novog uparivanja. OFF: uparivanje pri svakom povezivanju. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo`: uparivanje bez PIN-a. `PIN Type`: Flipper prikazuje PIN koji upisujete na glavnom uređaju. `PIN Y/N` (zadano): oba uređaja prikazuju PIN; potvrdite podudaranje. |
| **Set Device Name** | tekst | Bluetooth naziv (*"Set BLE device name"*). Prazno = `BadUSB <ime Flippera>`. |
| **Set MAC Address** | 6 bajtova | *"Set BLE MAC address"*. |
| **Randomize MAC Address** | radnja | Generira nasumičnu statičnu MAC adresu, prikazuje **Done**. Korisno da se uređaj prikaže kao „nova” tipkovnica. |
| **Restore BLE Defaults** | radnja | Briše naziv i MAC adresu, postavlja Persist Pairing na ON i Pairing Mode na `PIN Y/N`. |
| **Remove BLE Pairing** | radnja | *"Unpair the Device?"* → **Unpair** zaboravlja sve uređaje uparene s Bad USB-om. |

### USB način

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| **Set Manufacturer Name** | tekst | USB naziv proizvođača (*"Set USB manufacturer name"*). |
| **Set Product Name** | tekst | USB naziv proizvoda (*"Set USB product name"*). |
| **Set VID and PID** | 4 bajta | *"Set USB VID:PID"*. Omogućuje da se Flipper predstavi zadanim ID-om proizvođača i proizvoda. |
| **Randomize VID and PID** | radnja | Nasumični VID i PID, prikazuje **Done**. |
| **Restore USB Defaults** | radnja | Briše VID/PID i nazive: koristi se zadani identitet tipkovnice Flippera. |

Sve navedeno, uz odabrani raspored i način rada, sprema se u `/ext/badusb/.badusb.settings`. Redak `ID` / `BLE_ID` u skripti nadjačava identitet samo za tu skriptu.

## Rješavanje problema

| Problem | Što pokušati |
|---|---|
| Upisani tekst je besmislen (zamijenjeni `z` i `y`, pogrešni simboli) | Raspored tipkovnice glavnog računala ne odgovara onom u aplikaciji. Odaberite pravi raspored u Configu ili dodajte `DUCKY_LANG` u skriptu. Na računalu s više jezika unosa prebacite glavno računalo na jezik rasporeda prije pokretanja (npr. engleski, a ne ruski). |
| Nedostaju znakovi | Glavno računalo je presporo. Dodajte `DEFAULT_STRING_DELAY 10` (ili više) i dulje naredbe `DELAY` nakon otvaranja prozora. |
| Skripta počinje prije nego što se prozor otvori | Povećajte `DELAY` nakon `GUI r`, `ENTER` i sličnih naredbi. |
| *ERROR: line N* | Redak sadrži nepoznatu naredbu, tipfeler, neispravan broj ili ne-ASCII tekst. Naredbe su **osjetljive na veličinu slova** (`STRING`, ne `string`). Pogledajte [Format skripte](/hr/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` sadrži ne-ASCII znakove (dijakritike, ćirilicu…). Koristite `ALTSTRING`/`ALTCHAR` na sustavu Windows ili takav tekst unesite na drugi način. |
| *Connection Is Active!* | Odspojite qFlipper / CLI s USB priključka. |
| macOS otvara *Keyboard Setup Assistant* | Upotrijebite redak `ID` s VID/PID vrijednostima Apple tipkovnice (pogledajte primjer `demo_macos.txt`) ili zatvorite pomoćnika. |
| BLE glavni uređaj ne pronalazi Flipper | Uključite Bluetooth na Flipperu, ostanite na zaslonu skripte u BLE načinu, uklonite stara uparivanja na obje strane (`Remove BLE Pairing`). |

## Povezane stranice

- [Format skripte](/hr/badusb/script-format)
- [Primjeri](/hr/badusb/examples)
- [Rasporedi tipkovnice](/hr/badusb/layouts)
