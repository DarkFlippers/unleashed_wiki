---
title: "JavaScript: pregled"
sidebarTitle: "JS: pregled"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript na Flipper Zeru

Pisanje aplikacije za Flipper Zero nekada je značilo pisanje u C-u, postavljanje cijelog lanca alata za prevođenje i mnogo
čitanja izvornog koda drugih aplikacija. Firmver sada dolazi s **ugrađenim JavaScript engineom**, tako da možete napisati
običnu `.js` datoteku, kopirati je na SD karticu i pokrenuti izravno na uređaju. Nije potrebno prevođenje na računalu, a
skripte je lako dijeliti.

- Skripte se nalaze u `/ext/apps/Scripts/` i pokreću se iz `Main Menu → Apps → Scripts` ili iz CLI-ja naredbom `js <path>`.
- Engine se temelji na [mJS-u](https://github.com/cesanta/mjs), JavaScript interpreteru osmišljenom za mikrokontrolere: zahtijeva manje od 50 KB flash memorije i oko 2 KB RAM-a. Flipper zadržava jezgru mJS-a i dodaje proširenja poput kompaktnih binarnih polja (`ArrayBuffer`, tipizirana polja).
- Skripte mogu koristiti grafičko sučelje, tipke, USB HID (BadUSB), GPIO, UART, datotečni sustav i još mnogo toga putem **modula** koji se učitavaju pomoću `require()`.

::: warning mJS nije engine web-preglednika
mJS podržava podskup JavaScripta. Najvažnije razlike su da **nema zatvaranja (closures)** (funkcija ne može koristiti varijable iz okolnog opsega; pogledajte [Petlja događaja](/hr/dev/js-event-loop) za zaobilazno rješenje), nizovi znakova su jednobajtni bez podrške za UTF-8 i nedostaju mnogi objekti standardne biblioteke. Cjeloviti popis ograničenja potražite u [mJS README-u](https://github.com/cesanta/mjs).
:::

## Početak rada

1. [Vaša prva JS aplikacija](/hr/dev/js-first-app): napišite skriptu, kopirajte je na Flipper i pokrenite je iz izbornika ili CLI-ja.
2. [JavaScript SDK](/hr/dev/js-sdk): TypeScript, dovršavanje koda i prijenos jednom naredbom pomoću `npm start`.
3. [Korištenje JS modula](/hr/dev/js-modules): kako radi `require()`.

## Referenca jezika

- [Tipovi podataka](/hr/dev/js-data-types)
- [Ugrađene funkcije](/hr/dev/js-builtin): `print`, `delay`, `require`, `load`, metode za nizove znakova i polja, provjere kompatibilnosti SDK-a.

## Referenca modula

| Modul | Naziv za `require()` | Stranica |
|---|---|---|
| Petlja događaja | `event_loop` | [Petlja događaja](/hr/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/hr/dev/js-gui), [GUI prikazi](/hr/dev/js-gui-views) |
| BadUSB (USB HID tipkovnica) | `badusb` | [BadUSB](/hr/dev/js-badusb) |
| Podaci o uređaju | `flipper` | [Flipper](/hr/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/hr/dev/js-gpio) |
| Matematika | `math` | [Matematika](/hr/dev/js-math) |
| LED / vibro / zvučne obavijesti | `notification` | [Obavijesti](/hr/dev/js-notification) |
| UART | `serial` | [Serijska komunikacija](/hr/dev/js-serial) |
| Datoteke i mape | `storage` | [Pohrana](/hr/dev/js-storage) |

Primjeri skripti za svaki modul instalirani su s firmverom u `/ext/apps/Scripts/js_examples/` (na primjer `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Čitanje tih primjera najbrži je način za učenje API-ja.

## Dodaci firmvera Unleashed: moduli bez službene dokumentacije {#unleashed-extras}

::: tip Unleashed
Unleashed prijavljuje `flipper.firmwareVendor === "unleashed"` i sadrži **dodatne JS module** koje tvornički firmver nema. Službena JS dokumentacija ih ne pokriva, pa su stranice u nastavku napisane iz izvornog koda firmvera (`applications/system/js_app/modules/`) i TypeScript definicija tipova u `packages/fz-sdk/`. Svaki modul ujedno je i SDK „značajka” (feature), pa provjerite postoji li pomoću `doesSdkSupport([...])` ili `checkSdkFeatures([...])` (pogledajte [Ugrađene funkcije](/hr/dev/js-builtin#sdk-compatibility)) kako bi vaša skripta radila i na drugim firmverima.
:::

Cjelovit popis dodatnih značajki koje Unleashed prijavljuje glasi: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Modul | Naziv značajke | Što radi | Stranica |
|---|---|---|---|
| `subghz` | `subghz` | Upravljanje Sub-GHz radiom (unutarnji ili vanjski CC1101): RX, RSSI, frekvencija, odašiljanje `.sub` datoteka | [JS: subghz](/hr/dev/js-subghz) |
| `infrared` | `infrared-send` | Slanje IR signala prema protokolu ili kao sirovih trajanja | [JS: infrared](/hr/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Odašiljanje prilagođenih BLE oglasnih paketa (dodatni beacon) | [JS: blebeacon](/hr/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Emulacija USB uređaja za pohranu iz slike diska | [JS: usbdisk](/hr/dev/js-usbdisk) |
| `i2c` | `i2c` | Komunikacija s I2C uređajima na GPIO priključku | [JS: i2c](/hr/dev/js-i2c) |
| `spi` | `spi` | Komunikacija sa SPI uređajima na vanjskoj SPI sabirnici | [JS: spi](/hr/dev/js-spi) |
| `vgm` | `vgm` | Čitanje IMU senzora (pitch/roll/yaw) modula Video Game Module | [JS: vgm](/hr/dev/js-vgm) |

Modul GUI također ima prikaze koji nedostaju u službenoj dokumentaciji: `button_menu`, `button_panel`, `menu`, `number_input`, `popup`, `vi_list`. Oni su opisani na stranici [GUI prikazi](/hr/dev/js-gui-views).

API-ji firmvera koje ovaj wiki ne pokriva navedeni su u službenoj [Doxygen API referenci](https://developer.flipper.net/flipperzero/doxygen/).

## Povezano

- [Pisanje aplikacija u C-u](/hr/dev/first-app-c), kada JS nije dovoljno brz ili fleksibilan.
- [Format BadUSB skripti](/hr/badusb/script-format), klasična DuckyScript alternativa JS modulu `badusb`.
