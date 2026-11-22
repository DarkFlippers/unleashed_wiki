---
title: "JavaScript: BadUSB"
sidebarTitle: "JS: badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Modul BadUSB

Modul `badusb` pretvara Flipper Zero u USB tipkovnicu (HID) kojom se upravlja iz JavaScripta. To je skriptabilna alternativa klasičnim [BadUSB DuckyScript datotekama](/hr/badusb/script-format): u istoj skripti dobivate varijable, petlje i ostale JS module (GUI, storage, serial).

```js
let badusb = require("badusb");
```

::: warning
Koristite samo na računalima koja posjedujete ili za koja imate dopuštenje za testiranje.
:::

Primjer skripte: `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Metode

### setup()
Pokreće USB HID, po želji s prilagođenim parametrima. Pozovite je **prije svih ostalih metoda**.

**Parametri:** opcionalni konfiguracijski objekt:

- `vid`, `pid` (number): VID i PID; ako se koriste, oba su obavezna;
- `mfrName` (string): naziv proizvođača (najviše 32 ASCII znaka), opcionalno;
- `prodName` (string): naziv proizvoda (najviše 32 ASCII znaka), opcionalno;
- `layoutPath` (string): putanja do datoteke rasporeda tipkovnice, opcionalno.

```js
// Pokreni USB HID sa zadanim parametrima
badusb.setup();
// Pokreni USB HID s prilagođenim vid:pid = AAAA:BBBB, naziv proizvođača i proizvoda nisu definirani
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Pokreni USB HID s prilagođenim vid:pid = AAAA:BBBB, naziv proizvođača = "Flipper Devices", naziv proizvoda = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Rasporedi tipkovnica su iste `.kl` datoteke koje koristi aplikacija BadUSB (u `/ext/badusb/assets/layouts/`), npr. `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Vraća stanje USB veze.

```js
if (badusb.isConnected()) {
    // Učini nešto
} else {
    // Prikaži grešku
}
```

### press()
Pritišće i otpušta tipku ili kombinaciju tipki.

**Parametri:** nazivi tipki ili modifikatora, ili kodovi tipki. Pogledajte [popis naziva tipki](#key-names).

```js
badusb.press("a"); // Pritisni tipku "a"
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // Kombinacija CTRL + SHIFT + ESC
badusb.press(98); // Pritisni tipku s HID kodom (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Pritisni tipku s HID kodom (hex) 0x47 (Scroll lock)
```

### hold()
Drži tipku pritisnutom. Istovremeno se može držati do 5 tipki (ne računajući modifikatore).

**Parametri:** isti kao kod `press()`.

```js
badusb.hold("a"); // Pritisni i drži tipku "a"
badusb.hold("CTRL", "v"); // Pritisni i drži kombinaciju CTRL + "v"
```

### release()
Otpušta prethodno držanu tipku. Ako se pozove **bez parametara**, otpušta sve tipke.

**Parametri:** isti kao kod `press()`.

```js
badusb.release(); // Otpusti sve tipke
badusb.release("a"); // Otpusti tipku "a"
```

### print()
Tipka zadani niz znakova.

**Parametri:** niz znakova; *(opcionalno)* kašnjenje između pritisaka tipki u ms.

```js
badusb.print("Hello, world!"); // ispiši "Hello, world!"
badusb.print("Hello, world!", 100); // Dodaj kašnjenje od 100 ms između pritisaka tipki
```

### println()
Isto kao `print()`, nakon čega slijedi pritisak tipke <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // ispiši "Hello, world!" i pritisni "ENTER"
```

### altPrint()
Tipka niz znakova metodom **Alt+Numpad**, koja radi neovisno o rasporedu tipkovnice postavljenom na računalu. **Samo za Windows.**

**Parametri:** niz znakova; *(opcionalno)* kašnjenje između pritisaka tipki u ms.

```js
badusb.altPrint("Hello, world!"); // ispiši "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Dodaj kašnjenje od 100 ms između pritisaka tipki
```

### altPrintln()
Isto kao `altPrint()`, nakon čega slijedi pritisak tipke <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // ispiši "Hello, world!" i pritisni "ENTER"
```

### quit() {#quit}
Otpušta USB. Opcionalno je, ali omogućuje skripti prelazak u drugi USB način rada, primjerice u modul `usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (emulacija USB uređaja za masovnu pohranu) je JS modul specifičan za Unleashed; pogledajte [Pregled JavaScripta](/hr/dev/js-about#unleashed-extras).
:::

## Nazivi tipki {#key-names}

### Modifikacijske tipke

| Naziv |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Posebne tipke

| Naziv | Napomene |
|---|---|
| DOWN | Strelica dolje |
| LEFT | Strelica lijevo |
| RIGHT | Strelica desno |
| UP | Strelica gore |
| ENTER | |
| DELETE | |
| BACKSPACE | |
| END | |
| HOME | |
| ESC | |
| INSERT | |
| PAGEUP | |
| PAGEDOWN | |
| CAPSLOCK | |
| NUMLOCK | |
| SCROLLLOCK | |
| PRINTSCREEN | |
| PAUSE | Tipka Pause/Break |
| SPACE | |
| TAB | |
| MENU | Tipka kontekstnog izbornika |
| Fx | Tipke F1-F24 |
| NUMx | Tipke NUM0-NUM9 |

## Povezano

- [Korištenje BadUSB-a](/hr/badusb/usage) i [format skripti](/hr/badusb/script-format)
- [Petlja događaja](/hr/dev/js-event-loop), [GUI](/hr/dev/js-gui) za interaktivne izbornike payloada
