---
title: "ESP32 & Wi-Fi"
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 i Wi-Fi

Flipper Zero nema vlastiti Wi-Fi. Wi-Fi alati dolaze s ploče **ESP32** (ili ESP8266) na GPIO letvici, koja obavlja radijski dio posla i komunicira s aplikacijom na Flipperu putem UART-a.

## Koja ploča

| Ploča | Tipična upotreba |
|---|---|
| **Official Wi-Fi Developer Board** (ESP32-S2) | Dolazi s firmverom za otklanjanje pogrešaka Black Magic za [otklanjanje pogrešaka](/hr/gpio/devboard). Može se ponovno fleširati firmverom Marauder |
| **ESP32 Marauder ploče** (razne ploče ESP32 / ESP32-S2 / ESP32-S3, kombinirane ploče) | Wi-Fi i BLE skeniranje, hvatanje paketa, wardriving |
| **ESP8266 ploče** | Firmver Wi-Fi Scanner i Deauther |
| **ESP32-CAM** | Camera Suite (slika kamere na zaslonu Flippera) |

## Aplikacije

Svaka od ovih aplikacija samo je dio na strani Flippera: na ploči najprije mora biti odgovarajući firmver.

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Sučelje za firmver Marauder: Wi-Fi i BLE skeniranje, hvatanje paketa, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Prikazuje obližnje Wi-Fi mreže, za firmver ESP8266 Scanner |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Sučelje za firmver DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Slika uživo s modula ESP32-CAM na zaslonu Flippera, uz snimanje fotografija |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Druga aplikacija za ESP32-CAM: prijenos uživo i snimanje fotografija |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Sučelje za firmver Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Pokreće pristupnu točku s lažnim portalom (captive portal) na ESP32 |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Za firmver Deauther v2 autora @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Učitava firmver na ESP ploču s Flippera putem UART-a |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Pokreće IFTTT webhook putem modula ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Kartiranje Wi-Fi mreža s modulom ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Prikazuje lice i status Pwnagotchija na Flipperu putem UART-a |

Potpuni popis aplikacija za module: [Moduli i njihove aplikacije](/hr/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) autora justcallmekoko jest firmver za ESP32 ploče. Na Flipperu se koristi putem aplikacije **WiFi Marauder** iz paketa dodatnih aplikacija, koja šalje naredbe ploči i prikazuje njezin izlaz.

Uobičajeni tijek rada:

1. **Učitajte Marauder** na ESP32 ploču (pogledajte alat za učitavanje u nastavku).
2. Isključite Flipper, priključite ploču u GPIO letvicu i uključite uređaj.
3. Otvorite aplikaciju Marauder pod `Apps → GPIO` i odaberite naredbu (skeniranje pristupnih točaka, osluškivanje, wardriving itd.).
4. Rezultati se prikazuju u aplikaciji; zapisi hvatanja i wardriving zapisnici spremaju se ovisno o postavkama ploče i aplikacije (pogledajte dokumentaciju za Marauder za vašu ploču).

Potpune upute za korištenje Wi-Fi Devboarda s firmverom Marauder (autor UberGuidoZ): [UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Pravno upozorenje
Skeniranje je pasivno, ali napadi deautentifikacijom i drugi aktivni Wi-Fi napadi protuzakoniti su na mrežama koje nisu vaše ili za koje nemate dopuštenje za testiranje.
:::

## ESP32 Web Flasher

::: tip Unleashed
Tim Unleashed održava alat za učitavanje firmvera u pregledniku za popularne ESP32 module: **[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Radi u potpunosti u pregledniku pa ne morate instalirati esptool. Koristite preglednik s podrškom za Web Serial (preglednici temeljeni na Chromiumu).
:::

Opći koraci:

1. Odspojite ESP32 ploču s Flippera i povežite je s računalom putem USB-a.
2. Ako ploča sama ne uđe u način za učitavanje firmvera, držite **BOOT**, kratko pritisnite **RESET**, pa pustite **BOOT**.
3. Otvorite web alat, odaberite ploču i firmver, kliknite povezivanje i odaberite serijski priključak ploče.
4. Pričekajte da učitavanje završi, resetirajte ploču i vratite je u Flipper (dok je Flipper isključen).

Drugi načini učitavanja firmvera na ESP ploču:

- Aplikacija **ESP flasher** na Flipperu — učitava `.bin` s Flipperove SD kartice putem GPIO UART-a: [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Windows upute za esptool / Flash Download Tool: [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- [USB-UART Bridge u aplikaciji GPIO](/hr/gpio/gpio-app) s opcijom `RTS/DTR Pins` može poslužiti kao USB adapter za ploče bez vlastitog USB priključka.

::: tip Povratak na firmver za otklanjanje pogrešaka
Ako ste na službenu Wi-Fi Devboard ploču učitali Marauder i želite vratiti Black Magic debugger, ponovno ga učitajte naredbom `ufbt devboard_flash` kako je opisano u [Devboard: ažuriranje firmvera](/hr/gpio/devboard-firmware).
:::

## Karta za Wi-Fi wardriving

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** spaja i prikazuje više wardriving zapisa u WiGLE formatu iz aplikacije ESP32 Marauder i drugih alata na jednoj karti.
:::

1. Pokrenite wardriving pomoću Maraudera (za wardriving je potreban GPS modul spojen na ESP32 ploču).
2. Kopirajte CSV zapisnike u WiGLE formatu na svoje računalo.
3. Otvorite kartu i učitajte jednu ili više datoteka; mreže će se prikazati zajedno.

Za Sub-GHz zapise i druge datoteke s koordinatama postoji zasebna karta, [map.unleashedflip.com](https://map.unleashedflip.com).

## Ostali ESP firmver

| Firmver | Ploča | Poveznice |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Kako koristiti](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Kako koristiti](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Kako koristiti](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Odgovarajuće aplikacije za Flipper nalaze se u paketima Base/Extra: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Rješavanje problema

- **Aplikacija ne dobiva odgovor od ploče:** na ploči nije učitan firmver koji aplikacija očekuje, TX/RX su na pogrešnom UART-u ili ploča nije do kraja umetnuta.
- **Neobično ponašanje na UART-u:** druga značajka osluškuje na istim pinovima. Provjerite `Settings → Expansion Modules → Listen UART` (pogledajte [Moduli proširenja](/hr/gpio/expansion-modules)) i `Settings → System → Log Device`.
- **Web flasher ne pronalazi ploču:** koristite USB kabel koji prenosi podatke, ručno uđite u bootloader način, pokušajte drugi USB priključak ili preglednik.

## Povezano

- [Wi-Fi Devboard](/hr/gpio/devboard)
- [Vanjski moduli](/hr/gpio/external-modules)
- [GPS](/hr/gpio/gps)
