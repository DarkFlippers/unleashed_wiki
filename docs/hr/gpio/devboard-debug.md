---
title: "Devboard: otklanjanje pogrešaka i zapisnici"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: otklanjanje pogrešaka i zapisnici

Kad je [Devboard postavljen](/hr/gpio/devboard), možete otklanjati pogreške u firmveru iz programa VS Code i čitati zapisnike Flippera putem UART-a.

## Kako radi

Devboard je sonda za otklanjanje pogrešaka između alata na vašem računalu (putem USB-a ili Wi-Fi-ja) i mikrokontrolera Flippera. S Flipperom komunicira putem sučelja **Serial Wire Debug**:

- **pin 10** — SWCLK (Serial Wire Clock);
- **pin 12** — SWDIO (Serial Wire Debug Data I/O).

![Hardver Devboarda](/img/remote/06e0a9eb98e4130d.jpg)

## Načini otklanjanja pogrešaka

| Povezivanje | Dostupni načini |
|---|---|
| Wi-Fi | Samo Black Magic |
| USB | Black Magic (zadano) ili DAPLink |

Način Black Magic ne podržava prepoznavanje RTOS dretvi; sve ostalo radi.

### Promjena USB načina rada

Neobično je, ali USB način rada mijenja se putem Wi-Fi-ja:

1. Otvorite web-sučelje pločice (<http://192.168.4.1> u načinu pristupne točke ili <http://blackmagic.local> u načinu klijenta, pogledajte [povezivanje](/hr/gpio/devboard)).
2. Na kartici **WiFi** postavite **USB mode** na **BlackMagicProbe** ili **DapLink**.
3. Kliknite **SAVE**, zatim **REBOOT**.
4. U programu VS Code odaberite odgovarajući debugger (u nastavku).

## Otklanjanje pogrešaka u firmveru u programu VS Code

### Preduvjeti

1. Instalirajte [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Klonirajte i prevedite firmver. Za Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Isti koraci vrijede i za izvorni repozitorij `flipperdevices/flipperzero-firmware`.) Više o prevođenju: [Prevođenje firmvera](/hr/dev/build), [FBT](/hr/dev/fbt).

### Pokretanje sesije

1. Učitajte upravo prevedeni firmver putem Devboarda:

   ```bash
   ./fbt flash
   ```

2. Otvorite mapu firmvera u programu **VS Code** i instalirajte preporučena proširenja (obavijest ili `@recommended` na kartici Extensions).
3. Generirajte konfiguraciju za VS Code:

   ```bash
   ./fbt vscode_dist
   ```

4. U odjeljku **Run and Debug** odaberite:
   - **Attach FW (blackmagic)** — putem Wi-Fi-ja ili USB-a;
   - **Attach FW (DAP)** — samo USB, pločica u načinu DAPLink.

   Putem USB-a debugger mora odgovarati postavci **USB mode** na pločici (provjerite je u web-sučelju).
5. Kliknite ▷ **Start Debugging**. Firmver se zaustavlja na početku sesije; kliknite **Continue** na alatnoj traci da nastavi s radom.

![Otklanjanje pogrešaka u programu VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Pogledajte i [vodič za otklanjanje pogrešaka u VS Codeu](https://code.visualstudio.com/docs/editor/debugging) te [Otklanjanje pogrešaka](/hr/dev/debugging).

## Čitanje zapisnika

Devboard čita izlaz zapisnika Flippera s njegova UART-a, neovisno o OS-u Flippera. Zato vidite zapisnike tijekom pokretanja, ažuriranja i rušenja, što CLI naredba `log` ne može prikazati. Zapisnici su dostupni **samo putem USB-a**.

### Postavljanje razine i uređaja za zapisnike

1. Otvorite `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: ostavite `USART` (pinovi 13/14), gdje Devboard sluša. `LPUART` šalje zapisnike na pinove 15/16, a `None` onemogućuje UART zapisnike.

::: tip
Ako drugi modul treba pinove 13/14 (Wi-Fi pločica, SIM800, GPS), postavite `Log Device` na `LPUART` ili `None` kako mu izlaz zapisnika ne bi smetao.
:::

### macOS

1. Instalirajte [Homebrew](https://brew.sh/), zatim `brew install minicom`.
2. Isključite Flipper, priključite Devboard, uključite Flipper.
3. Pokrenite `ls /dev/cu.*`, povežite Devboard putem USB-a i pokrenite naredbu ponovno. Pojavljuju se dva nova uređaja, npr. `/dev/cu.usbmodemblackmagic1` i `/dev/cu.usbmodemblackmagic3`.
4. Otvorite onaj s **većim brojem**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Zapisnici se ispisuju u terminalu. Izađite putem izbornika programa minicom ili zatvorite prozor.

### Linux

1. Instalirajte minicom, npr. `sudo apt install minicom`.
2. Isključite Flipper, priključite Devboard, uključite Flipper.
3. Pokrenite `ls /dev/tty*`, povežite Devboard putem USB-a i pokrenite naredbu ponovno. Pojavljuju se dva nova uređaja, npr. `/dev/ttyACM0` i `/dev/ttyACM1`.
4. Otvorite onaj s većim brojem:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Ako se ništa ne pojavi, pokušajte s drugim uređajem.

### Windows

1. Instalirajte [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Isključite Flipper, priključite Devboard, uključite Flipper i povežite Devboard putem USB-a.
3. U **Device Manager → Ports (COM & LPT)** zabilježite novi COM port.
4. U programu PuTTY odaberite **Serial**, unesite port u **Serial line**, postavite **Speed** na **230400** i kliknite **Open**.

![Postavke programa PuTTY](/img/remote/2bb43453a91a142e.jpg)

## Povezano

- [Devboard: početak rada](/hr/gpio/devboard)
- [Devboard: ažuriranje firmvera](/hr/gpio/devboard-firmware)
- [CLI](/hr/dev/cli)
