---
title: Mobilna aplikacija Flipper
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Mobilna aplikacija Flipper

Službena aplikacija **Flipper Mobile App** ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) povezuje se s Flipperom putem
Bluetootha. Pomoću nje možete ažurirati firmver, pregledavati i dijeliti spremljene ključeve, instalirati aplikacije iz kataloga, upravljati
Flipperom na daljinu i izraditi sigurnosnu kopiju svojih podataka.

::: tip Unleashed
Službena mobilna aplikacija radi s Unleashed firmverom. Može instalirati Unleashed `.tgz` paket kao **Custom** ažuriranje (u nastavku). Ako
se aplikacija prestane povezivati nakon instalacije Unleashed firmvera ili promjene naziva Flippera, ponovno ga uparite, pogledajte
[Problemi s povezivanjem](#connection-problems).
:::

## Povezivanje s Flipperom

1. Na Flipperu: `Main Menu → Settings → Bluetooth`, postavite **Bluetooth** na **ON**.
2. U aplikaciji dodirnite **Connect**, zatim **Connect** pored naziva vašeg Flippera.
3. Unesite **kod za uparivanje** prikazan na zaslonu Flippera i dodirnite **Pair**.
4. Pričekajte dok aplikacija ne dovrši sinkronizaciju.

## Što se nalazi u aplikaciji

- **Main Menu** (kartica uređaja): ažuriranje putem Bluetootha, **Device Info** (podaci o hardveru i firmveru), **Options**
  (sigurnosna kopija, zapisnici, upravitelj datoteka, ponovno pokretanje, prijava pogreške; skup opcija ovisi o iOS-u/Androidu), ručna sinkronizacija, reprodukcija zvuka za pronalaženje
  Flippera.
- **Archive**: sve spremljene Sub-GHz, RFID 125, NFC, Infrared i iButton datoteke. Favoriti, pretraživanje i vraćanje obrisanih
  stavki. Dodirnite ključ za **Key Info**: emuliraj ili pošalji, dodaj u favorite, preimenuj, dodaj bilješku, prikaži pojedinosti, obriši,
  podijeli.
- **Apps**: službeni katalog aplikacija, instaliraju se putem Bluetooth LE veze, pogledajte [Aplikacije na SD kartici](/hr/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys) za izračun MIFARE Classic ključeva iz prikupljenih noncea te
  **Remotes Library** s infracrvenim daljinskim upravljačima (pogledajte [Infrared s telefona](/hr/infrared/mobile)).
- **Widget**: emulirajte spremljene daljinske upravljače i kartice s početnog zaslona telefona bez otvaranja aplikacije (iOS Today View
  → Edit → Add Widget → Flipper; na Androidu ga dodajte kao bilo koji widget i dodirnite za konfiguraciju).

## Instalacija Unleashed firmvera s telefona

::: tip Prije početka
Provjerite je li SD kartica umetnuta. Unleashed možete instalirati izravno preko tvorničkog firmvera ili preko starije verzije
Unleashed firmvera.
:::

### iOS

1. Otvorite [najnovije izdanje Unleashed firmvera](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) i
   preuzmite `flipper-z-f7-update-(version).tgz`.
2. U aplikaciji **Files** odaberite preuzetu `.tgz` datoteku, dodirnite **Share** i odaberite aplikaciju **Flipper**.
3. U aplikaciji Flipper provjerite prikazuje li Update Channel `Custom flipper-z-f7-update...`, zatim dodirnite zeleni gumb
   **Update**.
4. Pričekajte dok ažuriranje ne završi. iOS aplikacija može na kraju prikazati pogrešku, ali Flipper je ažuriran.

### Android, pomoću `.tgz` datoteke

1. Preuzmite `flipper-z-f7-update-(version).tgz` sa stranice izdanja.
2. U aplikaciji Flipper dodirnite **Update channel** → **Custom** i odaberite preuzetu datoteku.
3. Dodirnite **Update** i pričekajte.

### Android, putem poveznice web ažuriratelja

1. Na stranici izdanja dodirnite **Install via Web Updater**.
2. Kada Android pita čime otvoriti poveznicu, odaberite aplikaciju **Flipper**.
3. Nastavite instalaciju i pričekajte.

Ažuriranje putem Bluetootha može trajati oko 10 minuta. Drugi načini: [Instalacija Unleashed firmvera](/hr/start/install).

### Ako ažuriranje ne uspije

- Provjerite je li Flipper uključen i još uvijek povezan putem Bluetootha.
- Ponovno pokrenite Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) i ponovno pokrenite ažuriranje.
- Ako i dalje ne uspijeva, interna pohrana možda je puna ili oštećena: umjesto toga instalirajte pomoću [qFlippera](/hr/mobile/qflipper) ili
  [Web Installera](/hr/mobile/web-tools#unleashed-web-installer), pogledajte [Oporavak](/hr/start/recovery).

## Izrada sigurnosne kopije ključeva

1. Na kartici uređaja dodirnite **Options → Backup Keys**.
2. Odaberite kamo želite spremiti ili podijeliti `.zip` arhivu sa svojim ključevima, karticama i daljinskim upravljačima.

Za vraćanje raspakirajte arhivu i prenesite datoteke pomoću [qFlippera](/hr/mobile/qflipper). Za potpunu sigurnosnu kopiju SD kartice
preuzmite cijelu karticu u qFlipperovom **File manageru**.

## Problemi s povezivanjem {#connection-problems}

**Nakon instalacije Unleashed firmvera ili preimenovanja Flippera aplikacija se ne povezuje:**

1. U aplikaciji dodirnite **Forget flipper**.
2. U Bluetooth postavkama telefona pronađite Flipper, otvorite njegove opcije i odaberite **Forget device**.
3. Na Flipperu: `Settings → Bluetooth → Unpair All Devices` i potvrdite s **Unpair**.
4. Provjerite je li Bluetooth uključen na Flipperu, zatim ga ponovno uparite iz aplikacije.

**Flipper nije pronađen:** provjerite je li Bluetooth uključen na oba uređaja, odspojite Flipper od drugih uređaja (na
primjer od računala za [Bluetooth daljinski upravljač](/hr/apps/controllers)), ažurirajte aplikaciju i firmver te ponovno pokrenite Flipper.

**Sinkronizacija ne uspijeva:** rasparite i ponovno uparite uređaje, ponovno pokrenite oba uređaja i isprobajte
`Settings → System → Sleep Method → Legacy` na Flipperu.

## Prijava pogrešaka u aplikaciji

Pogreške u službenoj aplikaciji: **Options → Report Bug**, unesite naslov i korake za reprodukciju, ostavite zapisnike priložene,
dodirnite **Submit** i po želji objavite ID prijave na [forum.flipperzero.one](https://forum.flipperzero.one/) (odjeljak Mobile
App). Za prikupljanje zapisnika s Flippera za prijavu: postavite `Settings → System → Log Level` na **Debug**, povežite putem USB-a,
otvorite serijski terminal na **230400** bauda (ili [lab.flipper.net/cli](https://lab.flipper.net/cli)), pokrenite `info device`,
zatim `log`, reproducirajte pogrešku te prije objave uklonite retke `hardware.uid` i `hardware.name`.

## Povezane stranice

- [qFlipper](/hr/mobile/qflipper)
- [Prateća aplikacija qUnleashed](/hr/mobile/qunleashed-app)
- [Instalacija Unleashed firmvera](/hr/start/install)
