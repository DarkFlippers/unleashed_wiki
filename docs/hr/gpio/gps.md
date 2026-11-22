---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Postoje dva načina kako Flipperu osigurati lokaciju:

| Opcija | Hardver | Kako radi |
|---|---|---|
| **GPS servis (lokacija s popratnog uređaja)** | Nema: telefon ili računalo povezani putem USB-a ili Bluetootha | Aplikacije putem RPC-a pitaju povezanu popratnu aplikaciju za njezinu lokaciju |
| **NMEA GPS modul** | Serijski GPS prijamnik na GPIO UART-u | Dodatak `[NMEA] GPS` čita NMEA rečenice s modula |

## GPS servis (lokacija s popratnog uređaja)

::: tip Unleashed
Unleashed firmver sadrži sistemski servis `gps` (zapis `gps`, pokreće se pri uključivanju). Ne koristi nikakve GPIO pinove: zahtjeve za lokacijom prosljeđuje putem aktivne **RPC sesije** (USB ili Bluetooth) popratnoj aplikaciji, koja odgovara položajem telefona ili računala.
:::

Što aplikacija dobiva od njega:

| Polje | Jedinica |
|---|---|
| Zemljopisna širina, dužina | stupnjevi × 10⁷ |
| Smjer kretanja (heading) | stupnjevi × 100 (0…36000) |
| Brzina | mm/s |
| Nadmorska visina | cm |
| Točnost | mm |
| Sateliti | broj |

Aplikacije mogu zatražiti jednokratno određivanje položaja (`gps_request_location()`), kontinuirani tok podataka na **1–10 Hz** (`gps_request_stream()` / `gps_stop_stream()`), a također mogu poslati lokaciju natrag popratnoj aplikaciji (`gps_report_location()`). Popratna aplikacija može odgovoriti pogreškom: nije podržano, nema dopuštenja, lokacija je onemogućena, nepoznata pogreška.

### Isprobavanje

Izvorni kod uključuje dvije ogledne aplikacije autora @apfxtech (kategorija `Examples`, grade se kao FAP-ovi):

- **`[RPC] GPS Click`** — jednokratni zahtjev: pritisnite <kbd>OK</kbd> za dohvat lokacije; prikazuje zemljopisnu širinu, dužinu, smjer, brzinu, nadmorsku visinu, satelite i točnost. <kbd>BACK</kbd> izlazi iz aplikacije.
- **`[RPC] GPS Stream`** — neprekidan tok istih podataka.

Poruke koje se mogu pojaviti:

| Poruka | Značenje |
|---|---|
| `No USB/BLE connection` | Nema RPC sesije: povežite popratnu aplikaciju putem USB-a ili Bluetootha |
| `GPS not available` | Popratna aplikacija ne podržava lokaciju |
| `Permission denied` | Popratnoj aplikaciji nije odobreno dopuštenje za lokaciju |
| `Location disabled` | Lokacijske usluge su isključene na telefonu / računalu |
| `No response` | Popratna aplikacija nije odgovorila na vrijeme |
| `Waiting for data...` | Tok podataka je pokrenut, položaj još nije određen |

Popratna aplikacija mora podržavati ove RPC GPS zahtjeve; provjerite svoju popratnu aplikaciju (pogledajte [Mobilne aplikacije](/hr/mobile/)).

Za razvojne programere aplikacija: uključite `<gps/gps.h>` i otvorite zapis pomoću `furi_record_open(RECORD_GPS)`; zaglavlje također sadrži pomoćne funkcije za formatiranje koordinata, smjera, brzine, nadmorske visine i točnosti.

## NMEA GPS modul na UART-u

Za lokaciju bez telefona povežite serijski GPS prijamnik (većina modula koji ispisuju NMEA rečenice na logičkoj razini od 3,3 V).

Ožičenje (USART):

| Flipper pin | GPS modul |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) ili 1 (5V) | VCC (provjerite raspon napajanja modula) |
| 8, 11 ili 18 (GND) | GND |

Zatim otvorite dodatak `[NMEA] GPS` iz paketa dodatnih aplikacija. Postavke, brzina prijenosa (baud rate) i podržani moduli opisani su u njegovoj datoteci [README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
GPS modul i ostali korisnici UART-a (Wi-Fi ploče, SIM800, moduli za proširenje, ispis zapisnika) dijele pinove 13/14. Ako dodatak ne prima podatke, provjerite `Settings → Expansion Modules → Listen UART` i `Settings → System → Log Device`.
:::

## Aplikacije

Aplikacije koje rade s GPS modulom, sve iz paketa aplikacija:

| Aplikacija | Paket | Čemu služi |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Položaj s bilo kojeg NMEA GPS modula na UART-u |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Prikazuje i zapisuje podatke s u-blox GPS modula putem I2C-a |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA uređaj za praćenje s navigacijom po točkama (breadcrumb) |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Preglednik datoteka koji razvrstava vaše datoteke prema udaljenosti od vaše trenutačne lokacije |

Potpun popis aplikacija za module: [Moduli i njihove aplikacije](/hr/gpio/module-apps).

## Povezano

- [ESP32 i Wi-Fi](/hr/gpio/esp32) — karta wardrivinga
- [Vanjski moduli](/hr/gpio/external-modules)
- [Raspored GPIO pinova](/hr/gpio/pinout)
