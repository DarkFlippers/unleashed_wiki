---
title: Format skripte
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Format skripte za Bad USB (DuckyScript)

Bad USB izvršava tekstualne skripte u **proširenoj DuckyScript** sintaksi. Klasične USB Rubber Ducky 1.0 skripte rade
izravno bez izmjena; povrh toga Flipper dodaje prilagođeni USB/BLE identitet, unos pomoću `ALT`+numerička tipkovnica, `SYSRQ`, medijske tipke, upravljanje
mišem, čekanje na pritisak gumba i još mnogo toga. Ova je referenca provjerena prema tablici naredbi u firmveru
(`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## Pravila datoteke

- Običan tekst, nastavak **`.txt`**, bez prevođenja (kompilacije). Završeci redaka `\n` ili `\r\n`.
- Jedna naredba po retku. Prazni retci se preskaču; retci mogu biti uvučeni razmacima ili tabulatorima.
- Naredbe se pišu **VELIKIM SLOVIMA i razlikuju velika i mala slova**: `STRING`, a ne `string`.
- Naredba i argument odvojeni su jednim razmakom.
- Komentari su cijeli retci koji počinju s `REM`. Ne postoje komentari na kraju retka.
- Tekst koji se tipka (`STRING`, `STRINGLN`) mora biti **ASCII**. Znakovi koji nisu ASCII zaustavljaju skriptu s porukom
  *"Native .kl supports ASCII, not UTF-8"*.
- U slučaju pogreške skripta se zaustavlja, a zaslon prikazuje *ERROR:*, broj retka i razlog.

## Brza referenca

| Naredba | Argument | Učinak |
|---|---|---|
| `REM` | tekst | Komentar, zanemaruje se. |
| `ID` | `VID:PID [Manufacturer:Product]` | USB identitet, **samo prvi redak**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Bluetooth identitet, **samo prvi redak**. |
| `DELAY` | ms | Jednokratno čekanje. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Čekanje prije svake sljedeće naredbe. |
| `STRING` | tekst | Tipkanje teksta. |
| `STRINGLN` | tekst | Tipkanje teksta i pritisak tipke Enter. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Odgoda između pritisaka tipki samo za **sljedeći** `STRING`. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Odgoda između pritisaka tipki za **svaki** `STRING`. |
| `REPEAT` | n | Ponavljanje prethodne naredbe još n puta. |
| `DUCKY_LANG` | naziv rasporeda | Promjena rasporeda tipkovnice za ostatak skripte (Unleashed). |
| `HOLD` | tipka / gumb miša | Pritisak i zadržavanje. |
| `RELEASE` | tipka / gumb miša | Otpuštanje zadržane tipke. |
| `ALTCHAR` | kôd | Tipkanje jednog znaka pomoću `ALT`+numeričke tipkovnice. |
| `ALTSTRING` / `ALTCODE` | tekst | Tipkanje teksta pomoću `ALT`+numeričke tipkovnice. |
| `SYSRQ` | znak | Kombinacija tipki Magic SysRq. |
| `MEDIA` | medijska tipka | Tipka za upravljanje medijima (glasnoća, reprodukcija…). |
| `GLOBE` | tipka | Fn/Globe + tipka (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | nema | Pauza dok se na Flipperu ne pritisne <kbd>OK</kbd>. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | nema | Klikovi mišem. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Pomicanje miša. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Pomicanje kotačića miša. |
| kombinacija tipki | npr. `CTRL-ALT DELETE` | Istovremeni pritisak i otpuštanje tipki. |

## Komentari

```text
REM This line is ignored
```

## Odgode

| Naredba | Parametar | Napomene |
|---|---|---|
| `DELAY` | ms | Jednokratna pauza. |
| `DEFAULT_DELAY` | ms | Dodaje se prije svake sljedeće naredbe. Isto kao `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Odgode su glavni alat za pouzdanost: računalu je potrebno vrijeme da otvori prozore, pa dodajte `DELAY` nakon `GUI r`,
`ENTER` u pokretaču itd. Duge odgode prikazuju se na zaslonu kao `Delay Ns`.

## Tipkanje teksta

| Naredba | Parametar | Napomene |
|---|---|---|
| `STRING` | tekst | Tipka tekst točno kako je napisan, koristeći aktivni raspored tipkovnice. |
| `STRINGLN` | tekst | Isto, zatim pritisne Enter. |
| `STRING_DELAY` | ms | Pauza između pritisaka tipki samo za sljedeći `STRING`/`STRINGLN`. Isto kao `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pauza između pritisaka tipki za sve sljedeće nizove znakova. Isto kao `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Bez odgode između znakova tekst se šalje što je brže moguće; neka računala ili aplikacije tada znaju ispustiti znakove.
Ugrađene demo skripte koriste `DEFAULT_STRING_DELAY 10`.

::: warning Raspored je važan
`STRING` šalje *položaje tipki*, prevedene kroz odabrani [raspored tipkovnice](/hr/badusb/layouts). Ako računalo koristi
drugi raspored od aplikacije, dobit ćete pogrešne znakove. Tekst mora biti ASCII.
:::

## Tipke i kombinacije

Redak koji nije naredba čita se kao pritisak tipke: nula ili više **modifikatora**, zatim jedna **tipka**. Modifikatori su
povezani razmacima ili crticama. Tipka je naziv posebne tipke ili pojedinačni znak.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modifikatori

| Naziv | Napomene |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Tipka Windows / Command / Super |

### Posebne tipke

| Naziv | Napomene |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Strelice |
| `ENTER` | |
| `DELETE` | Brisanje unaprijed |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Break |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Tipka kontekstnog izbornika |
| `F1` … `F24` | Funkcijske tipke (firmver poznaje i F13–F24) |

## Ponavljanje

```text
DOWN
REPEAT 9
```

`REPEAT n` izvršava **prethodnu naredbu** još n puta (primjer pritišće tipku Dolje 10 puta). `n` mora biti ≥ 1.

## Zadržavanje i otpuštanje

| Naredba | Parametar | Napomene |
|---|---|---|
| `HOLD` | posebna tipka, modifikator, pojedinačni znak ili gumb miša | Pritišće i drži do naredbe `RELEASE`. |
| `RELEASE` | isto | Otpušta tu tipku. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Istovremeno se može držati najviše **6** tipki/gumba (veličina HID izvještaja tipkovnice); više od toga daje poruku *"Too many keys are
held"*. `RELEASE` bez ijedne zadržane tipke daje *"No keys are held"*. Službena dokumentacija navodi 5; provjera u firmveru
dopušta 6.

## Unos putem ALT + numeričke tipkovnice

Na sustavu Windows (i nekim Linux postavkama) bilo koji se znak može upisati držanjem tipke `ALT` i unosom njegova koda na numeričkoj
tipkovnici. Ovo **ne ovisi o rasporedu tipkovnice**, što je praktično na nepoznatim računalima.

| Naredba | Parametar | Napomene |
|---|---|---|
| `ALTCHAR` | kôd znaka | Tipka jedan znak: drži ALT, tipka znamenke na numeričkoj tipkovnici. |
| `ALTSTRING` | tekst | Tipka svaki ispisivi ASCII znak (32–126) iz teksta pomoću njegova ALT koda. |
| `ALTCODE` | tekst | Isto kao `ALTSTRING` (naziv koji koriste neke implementacije DuckyScripta). |

NumLock se automatski uključuje prije ALT unosa.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Šalje `ALT`+`PRINTSCREEN`+tipku, Linux kombinaciju [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key). Budite oprezni:
neke SysRq tipke odmah ponovno pokreću ili zaustavljaju sustav.

## Medijske tipke

`MEDIA <key>` pritišće tipku za upravljanje medijima:

| Tipka | Napomene |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | Sustav |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Navigacija u pregledniku / aplikaciji |
| `SNAPSHOT` | Snimanje fotografije u aplikaciji kamere |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Reprodukcija |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Glasnoća |
| `FN` | Tipka Fn/Globe na Mac tipkovnicama |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Svjetlina zaslona |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Tipka Fn / Globe (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` drži Fn/Globe, pritisne tipku i otpusti obje (posebnu tipku ili pojedinačni znak).

## Čekanje na pritisak gumba

```text
WAIT_FOR_BUTTON_PRESS
```

Skripta se pauzira na neodređeno vrijeme; Flipper prikazuje **Press to continue**. Pritisnite <kbd>OK</kbd> za nastavak. Korisno za
sinkronizaciju s radnjom koju obavljate ručno (prijava, otključavanje zaslona…).

## Miš

| Naredba | Parametar | Napomene |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | nema | Lijevi klik |
| `RIGHTCLICK` / `RIGHT_CLICK` | nema | Desni klik |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | nema | Srednji klik (kotačić) |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (cijeli brojevi) | Relativni pomak; negativno = lijevo / gore |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (cijeli broj) | Kotačić miša; predznak određuje smjer |

Gumbi miša rade s `HOLD`/`RELEASE`, npr. za povlačenje i ispuštanje (drag and drop):

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## ID uređaja {#device-id}

Možete postaviti identitet kojim se Flipper predstavlja računalu. Naredba mora biti u **prvom retku**; primjenjuje se
kada se skripta otvori, prije pokretanja, a aplikacija se **prebacuje u odgovarajući način povezivanja** (i dalje se možete
ručno prebaciti natrag). U ostalim retcima ove se naredbe zanemaruju.

| Naredba | Parametri | Primjer | Način |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | isto kao `BLE_ID` |

- `ID`: VID i PID (heksadekadski) su obvezni; nazivi proizvođača i proizvoda nisu obvezni (maks. 31 znak svaki).
- `BLE_ID` / `BT_ID`: 6-bajtni MAC i naziv uređaja su obvezni.

## Raspored tipkovnice po skripti: `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` je novost u firmveru Unleashed (PR #1224 autora @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Učitava `/ext/badusb/assets/layouts/<name>.kl` i koristi ga od tog retka nadalje, umjesto globalnog rasporeda postavljenog u
  Configu. Kratki nadimci: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- Naziv smije sadržavati slova, znamenke, `-` i `_`, a nakon njega u retku ne smije stajati ništa drugo.
- Datoteka koja nedostaje ili neispravan naziv **ne zaustavljaju skriptu**: tiho se vraća na ugrađeni `en-US`.
- Svako novo pokretanje ponovno počinje s globalnim rasporedom, stoga stavite `DUCKY_LANG` pri vrh skripte.

Popis naziva rasporeda nalazi se na stranici [Rasporedi tipkovnice](/hr/badusb/layouts).

## Povezane stranice

- [Primjeri](/hr/badusb/examples)
- [Rasporedi tipkovnice](/hr/badusb/layouts)
- [Korištenje Bad USB-a](/hr/badusb/usage)
