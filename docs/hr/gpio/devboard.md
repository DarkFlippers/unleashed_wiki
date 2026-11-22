---
title: "Devboard: prvi koraci"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: prvi koraci

Službena **Wi-Fi Developer Board** pločica jest ESP32-S2 (ESP32-S2-WROVER-N4R2) modul za GPIO priključak. Iz kutije
pokreće firmver **Black Magic Probe** i služi kao **sonda za ispravljanje pogrešaka (debug probe)**: povezuje program za ispravljanje pogrešaka na vašem računalu sa
STM32 čipom u Flipperu preko SWD sučelja, putem USB-a ili Wi-Fi mreže. Također može prosljeđivati UART zapise Flippera.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Ne treba vam za instalaciju firmvera
Ažuriranje, gradnja i učitavanje vlastitog firmvera rade preko običnog USB kabela. Devboard je potreban samo za praćenje pogrešaka
uživo (GDB, prijelomne točke) i za čitanje zapisa neovisno o operacijskom sustavu Flippera. Za korištenje iste pločice kao
Wi-Fi alata (Marauder), pogledajte [ESP32 i Wi-Fi](/hr/gpio/esp32).
:::

## Korak 1. Omogućite način Debug na Flipperu

1. Otvorite `Main Menu → Settings → System`.
2. Postavite `Debug` na `ON`.

Način Debug potreban je za ispravljanje pogrešaka u aplikacijama te otključava opcije za otklanjanje pogrešaka u aplikacijama i u [CLI-ju](/hr/dev/cli). Ponovno ga uključite
nakon svakog ažuriranja firmvera.

## Korak 2. Ažurirajte firmver pločice

Pločica se isporučuje sa starijim firmverom. Prvo ga ažurirajte: [Devboard: ažuriranje firmvera](/hr/gpio/devboard-firmware).

## Korak 3. Spojite Devboard na Flipper

1. **Prvo isključite Flipper.** Pločica i microSD kartica dijele Flipperov vod napajanja od 3,3 V; spajanje velikog kapacitivnog
   opterećenja pod naponom može oštetiti karticu.
2. **Umetnite je do kraja.** Bez maskice: bez razmaka između Flippera i pločice (može biti potrebna mala sila). U silikonskoj
   maskici: bez razmaka u sredini između maskice i pločice.
3. Držite <kbd>BACK</kbd> kako biste uključili Flipper.

![Umetnuti Devboard, Flipper bez maskice](/img/remote/4eb1e40120ff42bb.jpg)

## Korak 4. Povezivanje s računalom

### Preko USB-a

Koristite USB za otklanjanje pogrešaka u načinu **Black Magic** ili **DAPLink** te za čitanje zapisa.

1. Prikažite serijske uređaje na računalu:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Upravitelj uređaja (Device Manager) → **Ports (COM & LPT)**
2. Spojite USB-C priključak **Devboarda** na računalo.
3. Ponovno prikažite uređaje: pojavit će se **dva nova porta**, oba pripadaju Devboardu.

Ako se ništa ne pojavi, isprobajte drugi kabel (mora prenositi podatke), drugi USB priključak ili drugo računalo.

### Preko Wi-Fi mreže: način pristupne točke (zadano)

Pločica stvara vlastitu mrežu. Vaše računalo gubi uobičajenu Wi-Fi vezu dok je povezano s njom.

1. Na računalu ili mobitelu povežite se na Wi-Fi mrežu:
   - Naziv: `blackmagic`
   - Lozinka: `iamwitcher`
2. Otvorite <http://192.168.4.1> ili <http://blackmagic.local> za web-sučelje pločice.

Ako se mreža `blackmagic` ne prikazuje:

- ponovno pokrenite Wi-Fi vezu na računalu;
- pločica je možda postavljena kao klijent (STA). Držite gumb **BOOT** na pločici **10 sekundi** kako biste poništili njezine
  postavke; nakon ponovnog pokretanja ponovno je pristupna točka.

### Preko Wi-Fi mreže: klijentski način (STA)

Pločica se spaja na vašu postojeću 2,4 GHz mrežu, tako da zadržavate pristup internetu.

1. Povežite se s pločicom u načinu pristupne točke (gore) i otvorite <http://192.168.4.1>.
2. Odaberite način **STA**, unesite **SSID** i **lozinku** svoje mreže. Gumb **+** prikazuje obližnje 2,4 GHz mreže
   (5 GHz nije podržano).
3. Spremite i ponovno pokrenite pločicu.
4. Od sada otvarajte <http://blackmagic.local> preko svoje uobičajene mreže.

Preko Wi-Fi mreže dostupno je samo **Black Magic** otklanjanje pogrešaka.

## Hardver

- MCU: ESP32-S2-WROVER-N4R2.
- SWD prema Flipperu na **pinu 10 (SWCLK)** i **pinu 12 (SWDIO)**; UART zapisi na Flipperovim USART pinovima 13/14.
- Sheme (PCB, ESP32-S2, napajanje, priključci) i crtež sklopa:
  [Sheme Wi-Fi Developer Board pločice](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Sljedeći koraci

- [Devboard: otklanjanje pogrešaka i zapisi](/hr/gpio/devboard-debug)
- [Devboard: ažuriranje firmvera](/hr/gpio/devboard-firmware)
- Zajednica: [Discord](https://discord.com/invite/flipper) (kanal #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
