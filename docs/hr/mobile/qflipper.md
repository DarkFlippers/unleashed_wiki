---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** je službena stolna aplikacija za Flipper Zero: ažurira firmver i baze podataka, upravlja datotekama na microSD kartici, izrađuje sigurnosne kopije i vraća uređaj, popravlja oštećeni firmver i zrcali zaslon. Radi na sustavima Windows, macOS i Linux.

::: tip Unleashed
Kanali ažuriranja u programu qFlipper (Release / RC / Dev) instaliraju **službeni** firmver. Za instalaciju firmvera Unleashed upotrijebite **Install from file** s Unleashed `.tgz` paketom (qFlipper 1.2.0 ili noviji), pogledajte u nastavku, ili upotrijebite [Web Installer](/hr/mobile/web-tools#unleashed-web-installer).
:::

## Instalacija programa qFlipper

Preuzmite ga sa stranice [flipperzero.one/update](https://flipperzero.one/update) i pokrenite instalacijski program.

- **Windows**: samo Windows 10 i 11. Instalacijski program ujedno instalira upravljačke programe.
- **macOS**: 10.14 ili noviji, optimizirano za Apple Silicon.
- **Linux**: AppImage datoteka. Učinite je izvršnom i postavite udev pravila:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # pokretanje
./qFlipper-x86_64.AppImage rules install   # udev pravila za korištenje kao običan korisnik
```

(U upravitelju datoteka: Svojstva → Dozvole → "Allow executing file as program" / "Is executable".)

## Pregled

Povežite Flipper s umetnutom SD karticom putem USB-a i pokrenite qFlipper.

- **Device information**: podaci o hardveru i firmveru, gumb za ažuriranje, daljinsko upravljanje.
- **Advanced controls**: sigurnosna kopija, vraćanje, tvorničko resetiranje, kanal ažuriranja, **Install from file**.
- **File manager**: pregledavanje, prijenos, preuzimanje, preimenovanje i brisanje datoteka na SD kartici i u internoj pohrani.

## Instalacija firmvera Unleashed pomoću programa qFlipper

1. Provjerite je li umetnuta **microSD kartica**.
2. Preuzmite `flipper-z-f7-update-(version).tgz` sa stranice [izdanja firmvera Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (odaberite željeno slovo izdanja, pogledajte [varijante izdanja](/hr/apps/catalog#build-variants)).
3. Pokrenite qFlipper i povežite Flipper.
4. Kliknite **Install from file** i odaberite `.tgz` datoteku.
5. Pričekajte završetak svih faza. Flipper se ponovno pokreće u Unleashed sa svim instaliranim resursima.

Već ste na firmveru Unleashed? Instalirajte novu verziju preko postojeće; ne morate se vraćati na službeni firmver.
Više mogućnosti: [Instalacija firmvera Unleashed](/hr/start/install), [Ažuriranje](/hr/start/updating).

## Prijenos i preuzimanje datoteka

U odjeljku **File manager** povucite datoteke u mapu ili kliknite desnom tipkom miša na mapu → **Upload here**. Desni klik na datoteku ili mapu → **Download** kopira ih na računalo (jednostavan način za izradu sigurnosne kopije cijele SD kartice).

| Naredba | Windows / Linux | macOS |
|---|---|---|
| Ulaz u mapu | Return | Return |
| Natrag | Backspace | Backspace |
| Prijenos (Upload) | Ctrl+L | Cmd+L |
| Preuzimanje (Download) | Ctrl+D | Cmd+D |
| Brisanje | Delete | Fn+Backspace |
| Trenutačno brisanje | Shift+Delete | Shift+Fn+Backspace |
| Nova mapa | Ctrl+N | Cmd+N |
| Preimenovanje | Ctrl+E | Cmd+E |
| Osvježavanje | Ctrl+G | Cmd+G |

## Daljinsko upravljanje i snimke zaslona

U odjeljku **Device information** kliknite sliku Flippera, zatim klikajte gumbe na zaslonu ili koristite tipkovnicu (ℹ️ prikazuje raspored tipki). **SAVE SCREENSHOT** sprema trenutačni zaslon kao sliku.

## Zapisnici i prijave pogrešaka

- **LOGS → OPEN FULL LOG** prikazuje zapisnik trenutačne sesije; spremite ga kao `.txt`.
- qFlipper čuva zapisnike posljednjih 100 sesija: u odjeljku **LOGS** kliknite desnom tipkom na područje zapisnika → **Browse all logs**.
- Probleme sa službenim programom qFlipper prijavite na [forum.flipperzero.one](https://forum.flipperzero.one/) (odjeljak Firmware update / qFlipper). Probleme sa samim firmverom Unleashed prijavite u Unleashed razgovorima ili putem GitHub Issues.

## Rješavanje problema

### qFlipper ne vidi Flipper / Chrome se ne može povezati

Serijski port može koristiti samo jedan program istodobno. Ako je qFlipper otvoren, Flipper Lab, Web Installer i drugi web-alati ne mogu se povezati, i obrnuto. Zatvorite qFlipper (i višak kartica alata Flipper Lab) prije korištenja alata u pregledniku.

### Upravljački programi za Windows

1. Instalirajte qFlipper isključivo sa službenih izvora; on instalira ispravne upravljačke programe. Provjerite ažuriranja u **Advanced controls → CHECK APP UPDATES**.
2. **Normalni način** (Flipper radi): Flipper je **USB Serial Device** u `Device Manager → Ports (COM & LPT)`, hardverski ID **VID 0483, PID 5740**, upravljački program tvrtke **Microsoft**. Ako je instaliran drugi upravljački program, deinstalirajte ga i ponovno povežite uređaj.
3. **Sukob COM portova**: dva serijska uređaja na istom COM broju. Otvorite jedan od njih → **Port Settings → Advanced** i dodijelite nekorišteni **COM Port Number**.
4. **Recovery (DFU) način**: držite <kbd>←</kbd> + <kbd>Back</kbd>, otpustite <kbd>Back</kbd> i nastavite držati <kbd>←</kbd> dok LED ne zasvijetli plavo. Flipper se mora pojaviti kao **DFU in FS Mode** pod `Universal Serial Bus devices`, **VID 0483, PID DF11**, upravljački program **STMicroelectronics**.
5. Ako vidite **STM Device in DFU mode** pod `Universal Serial Bus controllers`, instaliran je pogrešan upravljački program: deinstalirajte qFlipper, ponovno ga instalirajte sa službene stranice i provjerite ponovno.
6. Ako se **DFU in FS Mode** nalazi pod `Other devices` s uskličnikom: desni klik → **Update driver → Browse my computer → Let me pick** → **Universal serial bus devices** → **WinUsb Device**.

Ako se Flipper uopće ne pokreće, pogledajte [Oporavak](/hr/start/recovery).

## Povezane stranice

- [Instalacija firmvera Unleashed](/hr/start/install)
- [Mobilna aplikacija Flipper](/hr/mobile/mobile-app)
- [Web-alati](/hr/mobile/web-tools)
