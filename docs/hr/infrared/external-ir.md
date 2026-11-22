---
title: Vanjski IR moduli
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Vanjski IR moduli (GPIO)

Tri ugrađene IR LED diode dovoljne su za dnevni boravak, ali im je domet ograničen. Za veću snagu možete na GPIO priključnicu spojiti **vanjski IR odašiljač** (pločicu sa snažnijim LED diodama i pogonskim tranzistorom). Aplikacija Infrared tada odašilje putem njega umjesto preko ugrađenih LED dioda. Univerzalni daljinski upravljači, spremljeni daljinski upravljači, mobilna aplikacija i gumb "Send" na zaslonu snimanja koriste odabrani izlaz.

::: tip Unleashed
Podrška za vanjski IR modul s automatskim otkrivanjem navedena je među značajkama Unleasheda; sama logika otkrivanja potječe iz službenog firmvera, pa je ovdje opisano ponašanje jednako na oba firmvera.
:::

## Ožičenje

| Pin modula | Flipper GPIO pin |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, napaja se kada je "5V on GPIO" na ON, ili 9 (3V3) za 3,3 V module |
| GND | 8, 11 ili 18 (GND) |

Pin 2 prenosi **isti modulirani signal** (s uključenim nosiocem, obično 38 kHz) koji inače pokreće unutarnje LED diode, pa modulu treba samo pogonski stupanj i LED diode, bez vlastitog modulatora. Pogledajte [Raspored GPIO pinova](/hr/gpio/pinout) za shemu priključnice.

::: warning
Učenje (primanje) signala uvijek koristi ugrađeni prijamnik. Vanjski modul služi isključivo za odašiljanje.
:::

## Postavke GPIO-a

Idite na `Main Menu → Infrared → GPIO Settings`. Postoje dvije opcije:

| Opcija | Vrijednosti | Značenje |
|---|---|---|
| **Signal Output** | `Flipper` | Ugrađene IR LED diode (zadano). |
| | `2 (A7)` | Uvijek odašilji na GPIO pinu 2. |
| | `Detect` | Automatski otkrij vanjski modul na pinu 2 pri svakom pokretanju aplikacije Infrared. |
| **5V on GPIO** | `OFF` / `ON` | Uključuje 5 V na GPIO pinu 1 za napajanje modula. Uz `Detect` prikazuje **`Auto`** i upravlja se automatski. |

Postavke se spremaju kada napustite zaslon, u datoteku `/ext/infrared/.infrared.settings`, i primjenjuju pri svakom pokretanju aplikacije Infrared. Kada izađete iz aplikacije Infrared, izlaz se vraća na ugrađene LED diode, a napajanje od 5 V ponovno se isključuje kako modul ne bi praznio bateriju u drugim aplikacijama.

### Korak po korak

1. Povežite modul (Signal → pin 2, VCC → pin 1, GND → pin 8/11/18).
2. Otvorite `Infrared → GPIO Settings`.
3. Postavite **Signal Output** na `Detect` (ili `2 (A7)` ako otkrivanje ne radi s vašim modulom).
4. Uz `2 (A7)` postavite **5V on GPIO** na `ON` ako se modul napaja s pina 1.
5. Pritisnite <kbd>Back</kbd>. Pošaljite bilo koju spremljenu tipku ili signal univerzalnog daljinskog upravljača; LED diode modula sada bi trebale odašiljati.

## Kako radi automatsko otkrivanje

Kada je odabrano `Detect`, firmver nakratko uključuje **slabi pull-up** na pinu 2 i očitava njegovo stanje:

- ako pin ostane na **niskoj razini (low)**, priključeno je nešto s pull-down otpornikom, pa se pretpostavlja da je spojen vanjski modul. Izlaz se prebacuje na pin 2 i **5V on GPIO se automatski uključuje**;
- ako pin očitava **visoku razinu (high)**, ništa nije spojeno i koriste se ugrađene LED diode.

To najbolje radi s modulima čiji je pogon LED dioda **MOSFET sa snažnim pull-down otpornikom** na gateu ili **BJT tranzistor** za pogon IR LED dioda. Modul **mora spustiti napon na pinu na 0,9 V ili niže** kako bi bio otkriven. Ako vaš modul nema pull-down, ručno odaberite `2 (A7)` i sami uključite 5 V.

Otkrivanje se odvija pri pokretanju aplikacije Infrared (i kada odaberete `Detect`). Ako priključite modul dok je aplikacija već otvorena, ponovno odaberite `Detect` ili ponovno pokrenite aplikaciju.

## Rješavanje problema

| Problem | Što pokušati |
|---|---|
| `Detect` uvijek koristi ugrađene LED diode | Modul ne spušta pin 2 dovoljno nisko (≤ 0,9 V). Koristite `2 (A7)` i ručno uključite `5V on GPIO` na ON. |
| LED dioda modula ne svijetli | Provjerite VCC: s `2 (A7)` napajanje od 5 V mora biti na ON. Provjerite GND. Pogledajte LED diode kroz kameru mobitela dok odašiljete. |
| Baterija se brzo prazni | Snažan modul troši mnogo struje s 5 V. Odspojite ga kada se ne koristi. |

## Povezane stranice

- [Raspored GPIO pinova](/hr/gpio/pinout)
- [GPIO moduli](/hr/gpio/external-modules)
- [Učenje i slanje signala](/hr/infrared/read)
- [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes)
