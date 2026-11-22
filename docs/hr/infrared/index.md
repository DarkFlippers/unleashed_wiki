---
title: Infracrveno (Infrared)
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Infracrveno (Infrared)

Flipper Zero ima ugrađeni infracrveni (IR) modul. Može **naučiti** tipke gotovo svakog IR daljinskog upravljača, **spremiti** ih kao
virtualni daljinski upravljač na microSD karticu, **slati** ih natrag te raditi kao **univerzalni daljinski upravljač** koji prolazi kroz
biblioteku poznatih kodova za televizore, audiosustave, projektore, LED trake, ventilatore i klima-uređaje.

![Infracrveno na Flipper Zeru](/img/remote/133011d2bd3dc44c.png)

## Hardver

- Plastični prozorčić propustan za IR na gornjem rubu Flippera.
- **Tri IR LED diode** za odašiljanje.
- **IR prijemnik** koji demodulira nosivi val (ugođen je za uobičajenih 38 kHz). Učenje uvijek koristi
  taj ugrađeni prijemnik.
- Po izboru **vanjski IR odašiljač** na GPIO pinu 2 (A7) za veći domet, pogledajte
  [Vanjski IR moduli](/hr/infrared/external-ir).

## Izbornik Infrared

Otvorite `Main Menu → Infrared`. Stavke izbornika dolaze izravno iz firmvera:

![Izbornik Infrared sa stavkama Universal Remotes, Learn New Remote, Saved Remotes i GPIO Settings](/screens/infrared/menu.png)

| Stavka | Što radi |
|---|---|
| **Universal Remotes** | Šalje cijelu biblioteku kodova za jednu tipku (Power, Vol+…) dok uređaj ne reagira. Vidi [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes). |
| **Learn New Remote** | Snima tipke s fizičkog daljinskog upravljača i sprema ih kao novi daljinski upravljač. Vidi [Učenje i slanje signala](/hr/infrared/read). |
| **Saved Remotes** | Otvara preglednik datoteka u `/ext/infrared/` za slanje, uređivanje, preimenovanje ili brisanje vaših daljinskih upravljača. |
| **GPIO Settings** | Odabire odašiljač (ugrađeni, pin 2 (A7) ili automatsko prepoznavanje) i 5 V na GPIO-u. Vidi [Vanjski IR moduli](/hr/infrared/external-ir). |
| **Learn New Remote RAW** | Samo kada je uključeno `Settings → System → Debug`. Kao Learn, ali je dekoder isključen: svaki se signal sprema kao RAW. |
| **Debug RX** | Samo kada je uključen Debug. Prikaz uživo "INFRARED monitor" onoga što prijemnik prima. |

::: tip Unleashed
Aplikacija Infrared, njezini dekoderi protokola i mehanizam univerzalnih daljinskih upravljača potječu iz službenog firmvera.
Unleashed dodaje:
- **RCA** IR protokol (vidi [Protokoli](/hr/infrared/protocols));
- dodatne biblioteke univerzalnih daljinskih upravljača (**LEDs**, **Fans**) te znatno veće, redovito provjeravane biblioteke za televizore,
  audiouređaje, projektore i klima-uređaje koje održava Unleashed tim (IR resurse održava @amec0e). Biblioteka za televizore
  ponovno je prevedena tako da rade **sve** njezine tipke;
- podršku za vanjske IR module s automatskim prepoznavanjem (preuzeto iz službenog firmvera).
:::

## Gdje se nalaze datoteke

| Putanja | Sadržaj |
|---|---|
| `/ext/infrared/*.ir` | Vaši spremljeni daljinski upravljači (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Biblioteke univerzalnih daljinskih upravljača: `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Instaliraju se i ažuriraju zajedno s firmverom. |
| `/ext/infrared/.infrared.settings` | GPIO postavke (izlazni pin, 5 V). |

Format `.ir` datoteka opisan je u [Format IR datoteka](/hr/infrared/file-format).

## Naredbeni redak

Naredba `ir` dostupna je u [CLI-ju](/hr/dev/cli) (primjerice putem qFlippera ili serijskog terminala):

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Stranice u ovom odjeljku

| Stranica | Što ćete naučiti |
|---|---|
| [Učenje i slanje signala](/hr/infrared/read) | Učenje daljinskog upravljača, spremanje, slanje tipki, uređivanje / premještanje / preimenovanje / brisanje tipki |
| [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes) | Sve kategorije univerzalnih daljinskih upravljača, tipke, kontrole, spremanje koda koji radi |
| [Daljinski upravljači u mobilnoj aplikaciji](/hr/infrared/mobile) | Biblioteka daljinskih upravljača u aplikaciji Flipper Mobile App |
| [Doprinos snimkama](/hr/infrared/captures) | Kako snimiti čiste signale za univerzalne biblioteke |
| [Vanjski IR moduli](/hr/infrared/external-ir) | GPIO izlaz, automatsko prepoznavanje, napajanje 5 V |
| [Protokoli](/hr/infrared/protocols) | Svaki protokol koji dekoder poznaje, uključujući RCA |
| [Format IR datoteka](/hr/infrared/file-format) | Formati `.ir` datoteka za daljinske upravljače, biblioteke i testove |
