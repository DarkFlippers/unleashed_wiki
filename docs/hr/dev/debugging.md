---
title: Otklanjanje pogrešaka u aplikacijama
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Otklanjanje pogrešaka u aplikacijama

Otklanjanje pogrešaka u stvarnom vremenu (*in-circuit debugging*) omogućuje pokretanje aplikacije, njezino zaustavljanje na bilo kojem mjestu, prolazak kroz kôd liniju po liniju te praćenje varijabli i stoga poziva. Time se pronalazi daleko više pogrešaka nego pristupom „dodaj zapis u dnevnik i pokušaj ponovno”.

::: info
Otklanjanje pogrešaka unutar kruga nije obavezno. Pogreške uvijek možete otklanjati i učitavanjem aplikacija putem USB-a te čitanjem [dnevnika](/hr/dev/cli#reading-logs).
:::

## Što vam je potrebno

- Flipper Zero (*ciljni uređaj*).
- Računalo sa sustavom Windows, Linux ili macOS s alatom [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (za aplikacije) ili cjelovitim stablom firmvera s alatom [fbt](/hr/dev/fbt).
- Podržana **SWD sonda**.

### Podržane SWD sonde

| Sonda | Napomene |
|---|---|
| **Drugi Flipper Zero** | Pokrenite aplikaciju [DAP Link](https://lab.flipper.net/apps/dap_link) na njemu kako biste ga pretvorili u SWD sondu |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Sa standardnim (Blackmagic) firmverom; povezuje se putem USB-a ili Wi-Fi mreže — pogledajte [Razvojna ploča](/hr/gpio/devboard) |
| CMSIS-DAP sonde | npr. [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Sonde kompatibilne s Blackmagic](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), [razvojna ploča ST-Link V3](/hr/dev/hardware#st-link-v3-developer-board) |
| J-Link | Upisivanje i otklanjanje pogrešaka samo iz VS Codea; sami instalirajte SEGGER alate |

## Pripremite Flipper

Omogućite način za otklanjanje pogrešaka na ciljnom uređaju: `Main Menu → Settings → System → Debug` → **ON**.

## Korak po korak (VS Code)

1. **Povežite sondu na GPIO priključnicu Flippera.** Sonde izrađene za Flipper jednostavno se priključe. Za generičku sondu povežite tri žice:

   | Signal | Pin na Flipperu |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 ili 18 |

   Ako sonda ima i UART, povežite ga na Flipperov USART (pinovi **13** TX i **14** RX). Taj priključak ispisuje zapise dnevnika i podatke o rušenju sustava, što uvelike pomaže.
2. **Povežite sondu s računalom** — obično putem USB-a; Wi-Fi Devboard radi i putem Wi-Fi mreže.
3. **Pripremite projekt:** jednom pokrenite `ufbt vscode_dist` (aplikacija) ili `./fbt vscode_dist` (firmver) pa otvorite mapu u VS Codeu.
4. **Prebacite VS Code na Run and Debug:** kliknite ikonu za otklanjanje pogrešaka u bočnoj traci ili pritisnite <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> na macOS-u). Odaberite konfiguraciju za svoju sondu i pritisnite **Play**.

   ::: info
   Pokretanje sesije otklanjanja pogrešaka **zaustavlja** firmver. Kliknite **Continue** na alatnoj traci za nastavak.
   :::
5. **Koristite kontrole za otklanjanje pogrešaka:** ponovno pokretanje, pauza, nastavak, korak u funkciju (*step in*), korak iz funkcije (*step out*), prekid veze.
6. **Postavite prijelomne točke** klikom lijevo od broja linije. Izvođenje se zaustavlja kada dođe do te linije.
7. **Pregledajte stog poziva** u ploči *Call Stack* dok je izvođenje pauzirano.
8. **Pregledajte varijable** u pločama *Variables*, *Watch* ili *Live Watch*.

Videoprikaz tvrtke Flipper Devices: [Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Otklanjanje pogrešaka iz naredbenog retka pomoću fbt

S cjelovitim stablom firmvera možete otklanjati pogreške i bez VS Codea:

| Naredba | Što radi |
|---|---|
| `./fbt debug` | Gradi i upisuje firmver, zatim priključuje GDB s učitanom `.elf` datotekom firmvera |
| `./fbt blackmagic` | Otklanja pogreške pomoću sonde Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Priključuje GDB bez učitavanja `.elf` datoteke; dodajte `.elf` datoteku svoje aplikacije pomoću `add-symbol-file` |
| `./fbt updater_debug` | Priključuje GDB s učitanom `.elf` datotekom programa za ažuriranje |
| `./fbt openocd ARGS="..."` | Pokreće samo OpenOCD |
| `./fbt get_stlink` | Ispisuje serijske brojeve ST-Linka za `SWD_TRANSPORT_SERIAL=...` |

## Signali za otklanjanje pogrešaka Furi HAL

Neki podsustavi Furi mogu izložiti unutarnje stanje na GPIO pinovima radi praćenja logičkim analizatorom ili osciloskopom. Omogućite ih dodavanjem definicije prilikom prevođenja, na primjer:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — raspoređivač i spavanje

Izlaže sistemski takt (*tick*), potiskivanje takta, mirovanje i tijek vremena:

| Signal | Pin | Značenje |
|---|---|---|
| `AWAKE` | `PA7` | Visoko dok je sustav zauzet računanjem, nisko dok spava — prati prijelaze u stanje spavanja |
| `TICK` | `PA6` | Mijenja stanje na svaki sistemski takt (samo kada nije aktivno potiskivanje takta) — otkriva odstupanja takta i neuobičajeno raspoređivanje |
| `SECOND` | `PA4` | Mijenja stanje svake sekunde — poremećaji u vremenu znače da sustav ne zadovoljava strogi rad u stvarnom vremenu |

### `FURI_HAL_POWER_DEBUG` — načini napajanja

Prati prijelaze načina napajanja:

| Signal | Pin | Značenje |
|---|---|---|
| `WFI` | `PB2` | Lagano spavanje (*wait for interrupt*). Najlakši način uštede energije koji ne prekida rad — sve, uključujući otklanjanje pogrešaka, radi normalno |
| `STOP` | `PC3` | Način STOP, duboko spavanje platforme. Većina čipa je isključena ili neupotrebljiva; otklanjanje pogrešaka mikrokontrolera u ovom načinu gotovo je nemoguće |

### `FURI_HAL_SD_SPI_DEBUG` — SD kartica

Bilježi promet SPI sabirnice SD kartice.

## Rješavanje problema

| Problem | Rješenje |
|---|---|
| Sonda se poveže, ali se ništa ne događa | Firmver je zaustavljen — pritisnite **Continue** |
| Prijelomne točke u aplikaciji se zanemaruju | Provjerite jesu li učitani `.elf` simboli aplikacije (VS Code konfiguracija iz `vscode_dist` to radi automatski; kod `debug_other` koristite `add-symbol-file`) |
| Program za otklanjanje pogrešaka gubi ciljni uređaj | Mikrokontroler je možda u načinu STOP; pogledajte `FURI_HAL_POWER_DEBUG`. Način Debug na Flipperu mora biti **ON** |
| Varijable se prikazuju kao optimizirane (*optimised out*) | Prevedite s `DEBUG=1` (napomena: takav firmver može biti prevelik za pakiranje — pogledajte [Prevođenje firmvera](/hr/dev/build)) |

## Povezane stranice

- [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c)
- [Flipper Build Tool (fbt)](/hr/dev/fbt)
- [Razvojna ploča](/hr/gpio/devboard)
- [Hardver](/hr/dev/hardware) — crteži rasporeda pinova i sheme razvojne ploče
