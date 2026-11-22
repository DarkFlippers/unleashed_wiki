---
title: Instalacija Unleashed firmvera
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Instalacija Unleashed firmvera

Svaka metoda u nastavku instalira isti paket ažuriranja: firmver, alat za ažuriranje (updater) i sve resurse (aplikacije, IR biblioteke,
Sub-GHz postavke i tako dalje).

::: tip Prije nego što počnete
- **Nisu potrebna međuažuriranja:** instalirajte Unleashed izravno preko tvorničkog firmvera ili preko starije verzije Unleasheda.
- Provjerite je li **umetnuta microSD kartica**. Ažuriranje se raspakirava na karticu, a aplikacije se nalaze na njoj.
- Napunite bateriju. Potpuno ažuriranje traje nekoliko minuta.
:::

## Koju datoteku preuzeti {#which-file-to-download}

Datoteke izdanja nazivaju se `flipper-z-f7-update-(version)(e / c).tgz`:

| Dio | Značenje |
|---|---|
| `flipper-z` | Za uređaj Flipper Zero |
| `f7` | Hardverski cilj. Isti za svaki Flipper Zero |
| `update` | Paket za samostalno ažuriranje: updater, firmver i svi resursi |
| `(version)` | Verzija firmvera |
| suffix | Inačica paketa aplikacija, pogledajte dolje |

| Sufiks | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(nema)* | ✅ | — |
| `c` | — | — |

- **`e`**: sve. Osnovni paket plus dodatni paket aplikacija zajednice. Odaberite ovo ako niste sigurni.
- **Bez sufiksa**: samo osnovni paket aplikacija zajednice.
- **`c`** ("clean"): bez aplikacija zajednice.

**Ugrađene sistemske aplikacije** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit,
SIM800, FindMy Flipper, USB/BT daljinski upravljači, Snake…) isporučuju se **sa samim firmverom** i prisutne su u **svakoj** inačici,
uključujući `c`. Pogledajte [Što dodaje Unleashed](/hr/start/unleashed-features#built-in-apps).

Ostale datoteke izdanja:
- `flipper-z-any-scripts-(version).tgz`: mapa `scripts` za razvoj firmvera i aplikacija;
- `flipper-z-f7-sdk-(version).zip`: SDK za razvoj aplikacija i uFBT.

## Metoda 1: qUnleashed (preporučeno)

[qUnleashed](/hr/mobile/qunleashed-app) je prateća aplikacija samog Unleashed tima. Ona sama preuzima i instalira
firmver, pa ne morate birati datoteku. Radi na sustavima **Android, iOS, Windows, macOS i Linux** — putem USB-a
na svima osim iOS-a, koji se povezuje putem Bluetootha.

1. Instalirajte qUnleashed za svoj sustav s njegove
   [stranice izdanja](https://github.com/DarkFlippers/qUnleashed/releases).
2. Povežite Flipper putem USB-a ili ga uparite putem Bluetootha (na iOS-u je Bluetooth jedini način).
3. Otvorite **firmware updater** u aplikaciji.
4. Odaberite kanal **Unleashed**, **Release** ili **Dev**.
5. Odaberite inačicu: **base**, **extra apps** ili **compact** ([što sadrže](#which-file-to-download)).
6. Pokrenite instalaciju i pričekajte. Flipper se ponovno pokreće u updater i prolazi kroz sve faze.

Ako se Flipper više ne pokreće, upotrijebite **Repair from DFU mode** u istoj aplikaciji kako biste ga ponovno zapisali putem USB-a. Pogledajte
[Oporavak](/hr/start/recovery#firmware-recovery).

Metode u nastavku jesu alternative. Upotrijebite neku od njih ako qUnleashed ne odgovara vašem sustavu.

## Metoda 2: Unleashed Web Installer

Potreban vam je **preglednik temeljen na Chromiumu** (Chrome, Edge, Opera, Brave, Vivaldi) i USB kabel.

1. Zatvorite **qFlipper** i sve druge Flipper web stranice. One drže serijski priključak zauzetim.
2. Povežite Flipper putem USB-a.
3. Otvorite **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Pritisnite **Connect** i odaberite svoj Flipper u skočnom prozoru preglednika.
5. Odaberite granu **Release** ili **Dev**.
6. Pritisnite **Install** i pričekajte. Flipper se ponovno pokreće u updater i prolazi kroz sve faze.
7. Gotovo. Svi resursi su instalirani.

## Metoda 3: Flipper Lab web updater

1. Otvorite [stranicu najnovijeg izdanja](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Povežite Flipper i kliknite poveznicu **Install via Web Updater**.
3. Na stranici web updatera pritisnite **Connect**, zatim **Install**.
4. Pričekajte da ažuriranje završi.

![Web updater](/img/remote/b803c9d8ec0350d6.png)

## Metoda 4: qFlipper (1.2.0 ili noviji)

1. Instalirajte [qFlipper](https://flipperzero.one/update) 1.2.0+ (starije verzije ne mogu instalirati `.tgz` datoteke).
2. Preuzmite `flipper-z-f7-update-(version).tgz` sa [stranice izdanja](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Pokrenite qFlipper i povežite Flipper.
4. Kliknite **Install from file** i odaberite preuzetu `.tgz` datoteku.
5. Ažuriranje počinje. Pričekajte dok ne završi.

![qFlipper install from file](/img/remote/f1a3ede83085d040.png)

::: warning
**Nemojte** koristiti gumb **Update** u qFlipperu nakon instalacije Unleasheda. On instalira **službeni** firmver preko
Unleasheda. Umjesto toga koristite **Install from file**.
:::

## Metoda 5: Flipper Mobile App

### Android, s `.tgz` datotekom
1. Preuzmite `flipper-z-f7-update-(version).tgz` na telefon.
2. U aplikaciji Flipper dodirnite **Update channel** i odaberite **Custom**.
3. Odaberite preuzetu `.tgz` datoteku i dodirnite **Update**.
4. Pričekajte dok ažuriranje ne završi.

### Android, s poveznicom web updatera
1. Na stranici izdanja dodirnite **Install via Web Updater**.
2. Kada vas upita želite li otvoriti preglednikom ili aplikacijom Flipper, odaberite **Flipper App**.
3. Nastavite instalaciju i pričekajte.

### iOS
1. Preuzmite `flipper-z-f7-update-(version).tgz`.
2. Otvorite je u aplikaciji **Files**. Dodirnite **Share** i odaberite **Flipper App**.
3. U aplikaciji Flipper dodirnite zeleni gumb **Update**. Provjerite prikazuje li kanal ažuriranja
   `Custom flipper-z-f7-update...`.
4. Pričekajte. **Aplikacija za iOS može na kraju prikazati pogrešku, ali Flipper je uspješno ažuriran.**

## Metoda 6: Izvanmrežno ažuriranje s microSD kartice

Računalni program nije potreban. Radi s računala ili telefona.

1. Raspakirajte `flipper-z-f7-update-(version).tgz` (ili `.zip`). Unutra se nalazi mapa `f7-update-(version)` koja sadrži
   `update.fuf`, `resources.tar` i druge datoteke.
2. Umetnite karticu u računalo ili telefon, ili prenesite datoteke pomoću programa qFlipper.
3. Napravite mapu `update` u **korijenskom direktoriju** kartice i premjestite `f7-update-(version)` u nju:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Provjerite jesu li **sve** datoteke tamo. Zadana iOS aplikacija Files može prikazati samo 3 od 6 datoteka. Koristite drugu aplikaciju za raspakiravanje, računalo ili Android.
5. Vratite karticu u Flipper.
6. Otvorite **Archive** (<kbd>↓</kbd> na početnom zaslonu), idite na karticu **Browser**, dođite do
   `update/f7-update-(version)/` i otvorite `update.fuf`.
7. Ažuriranje počinje. Pričekajte da sve faze završe.

![Izvanmrežno ažuriranje](/img/remote/92717373349f3b7c.png)

## Nakon instalacije

- Zaslon s podacima (**Settings → About**) prikazuje Unleashed firmver i podatke o verziji.
- Pri prvom pokretanju nakon ažuriranja Flipper raspakirava resurse na karticu. To je normalno.
- Pročitajte [Što dodaje Unleashed](/hr/start/unleashed-features) i podesite uređaj u [Postavkama](/hr/start/settings).

## Rješavanje problema

| Problem | Rješenje |
|---|---|
| Preglednik se ne može povezati | Zatvorite qFlipper i druge kartice Flipper Laba. Koristite Chromium preglednik. Pokušajte drugi kabel ili priključak |
| Ažuriranje ne uspijeva ili zastaje | Ponovno pokrenite pomoću <kbd>←</kbd> + <kbd>BACK</kbd>, provjerite SD karticu, pokušajte drugu metodu |
| Mobilna aplikacija se ne povezuje nakon instalacije | Zaboravite Flipper u aplikaciji i u Bluetooth postavkama telefona. Zatim na Flipperu otvorite **Settings → Bluetooth → Unpair All Devices** i ponovno uparite |
| Pozadinsko osvjetljenje ne radi nakon instalacije | Pogledajte [Česta pitanja](/hr/start/faq#backlight-does-not-work) (postavka RGB modifikacije) |
| Uređaj je mrtav / "bricked" | [Oporavak](/hr/start/recovery) |
