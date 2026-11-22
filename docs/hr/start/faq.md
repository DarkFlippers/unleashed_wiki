---
title: Česta pitanja (FAQ)
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# Česta pitanja (FAQ)

## Općenito

### Upravo sam kupio Flipper Zero. Odakle da počnem?

Pročitajte [Prvo pokretanje](/hr/start/first-start), a zatim [Instalacija Unleasheda](/hr/start/install). Službena stranica [flipperzero.one](https://flipperzero.one/) i [docs.flipper.net](https://docs.flipper.net/) pokrivaju osnove tvorničkog firmvera.

### Službeni firmver, Unleashed ili drugi fork?

Ako niste sigurni, počnite sa službenim firmverom. Ako želite više značajki ili Sub-GHz bez regionalnih zaključavanja, instalirajte **Unleashed**: fork službenog firmvera s mnoštvom novih značajki i unaprijed instaliranim aplikacijama (isprobajte `e` inačicu). Postoje i drugi forkovi temeljeni na Unleashedu za one koji žele više eksperimentirati s korisničkim sučeljem. Također možete napraviti vlastiti fork.

**Prije prijave greške provjerite koji firmver koristite.** Nemojte prijavljivati probleme iz drugih forkova ili tvorničkog firmvera u Unleashed repozitoriju ili Unleashed kanalima.

### Gdje mogu vidjeti razlike u odnosu na službeni firmver?

[Što Unleashed dodaje](/hr/start/unleashed-features).

### Koju inačicu trebam instalirati? Što znače `e` i `c`?

`e` = base + extra aplikacije zajednice, bez sufiksa = base aplikacije, `c` = bez aplikacija zajednice. Ugrađene sistemske aplikacije nalaze se u svima. Pojedinosti: [Instalacija Unleasheda](/hr/start/install#which-file-to-download).

### Što su razvojne inačice (dev builds)?

Automatski izrađene inačice najnovijih commitova na grani `dev` koje još nisu objavljene kao izdanje. **Mogu sadržavati greške.** Preuzmite ih u Web Installeru (Dev), na [dev.unleashedflip.com](https://dev.unleashedflip.com), na Telegramu [@kotnehleb](https://t.me/kotnehleb) ili na Discord kanalu `unleashed-development`. Prethodna inačica briše se pri učitavanju nove, a stare ostaju samo kao datoteke na Telegram kanalu. Pronašli ste grešku? [Prijavite je](https://github.com/DarkFlippers/unleashed-firmware/issues).

### Koji je poslužitelj za ažuriranje Unleasheda?

`https://up.unleashedflip.com/directory.json`. Koristi isti format kao službeni, ali službene aplikacije ne mogu se prebaciti na njega bez ponovne kompilacije. Možete ga proslijediti alatu **uFBT** za izradu aplikacija za Unleashed SDK. Stalno je aktivan i automatski se ažurira.

### Koje su aplikacije uključene?

Ugrađene sistemske aplikacije te paket base (i paket extra za `e`) iz repozitorija [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Pogledajte [Što Unleashed dodaje](/hr/start/unleashed-features#built-in-apps).

### Kako mogu podržati projekt?

Pogledajte [odjeljak za podršku](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project) u datoteci ReadMe. I obično "hvala" puno znači. Svaka inačica jest i ostat će besplatna i otvorenog izvornog koda.

## Nakon instalacije

### Pozadinsko osvjetljenje ne radi nakon instalacije Unleasheda {#backlight-does-not-work}

Uključili ste postavku **RGB backlight mod**, koja je namijenjena samo Flipperima s hardverskom RGB modifikacijom. Idite na **Settings → LCD and Notifications → RGB Mod Settings** i postavite **RGB backlight installed** na `OFF`. Ako *imate* tu modifikaciju, umjesto toga je tamo uključite.

### Mobilna aplikacija se ne povezuje (nakon instalacije Unleasheda ili promjene imena)

1. U mobilnoj aplikaciji dodirnite **Forget Flipper**.
2. U postavkama telefona **Settings → Bluetooth** pronađite Flipper i odaberite **Forget this device**.
3. Na Flipperu: **Settings → Bluetooth → Unpair All Devices**, zatim potvrdite.
4. Provjerite je li Bluetooth na Flipperu postavljen na `ON`, zatim ga ponovno uparite iz aplikacije.

### Postavke (PIN, favoriti, radna površina…) su se resetirale nakon ažuriranja

Postavite ih ponovno. Datoteka s postavkama resetira se samo kada izdanje promijeni njezinu strukturu, što se događa u određenim izdanjima, ne svaki put. Provjerite zapise promjena (changelog) za izdanja od vaše prethodne verzije.

### Flipper se ne povezuje s Chromeom / Web Installerom

Najčešće je **otvoren qFlipper**, ili je povezan drugi Flipper Lab / web-stranica. Samo jedan program može koristiti serijski port. Zatvorite ostale i pokušajte ponovno. Koristite preglednik temeljen na Chromiumu.

## Problemi

### Flipper se srušio, zamrznuo ili zablokirao

Držite <kbd>←</kbd> + <kbd>BACK</kbd> za ponovno pokretanje. Više: [Kombinacije tipki](/hr/start/key-combos).

### Flipper uopće ne radi. Kako da vratim firmver?

[Oporavak → Oporavak firmvera](/hr/start/recovery#firmware-recovery).

### Zaboravio sam svoj PIN

Odspojite USB, isključite Flipper, držite <kbd>↑</kbd> + <kbd>BACK</kbd> oko 5 s dok se ne pojavi zaslon za resetiranje, zatim držite <kbd>→</kbd>. Postavke i PIN se resetiraju, ali datoteke na SD kartici ostaju sačuvane. Pojedinosti: [Oporavak → Resetiranje zaboravljenog PIN-a](/hr/start/recovery#reset-pin).

### Flipper je spor i slabo reagira

1. Koristite kvalitetnu microSD karticu poznate marke. Flipper koristi SPI i ne podnosi svaka kartica taj način rada jednako dobro.
2. U **Settings → System** provjerite:
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Napunite bateriju. Slaba baterija također utječe na performanse.

### Kako mogu promijeniti ime Flippera ili ga vratiti na zadano?

**Settings → Desktop → Change Flipper Name**: unesite ime, odaberite **Save**, napustite Settings i Flipper će se ponovno pokrenuti. Spremite prazno ime za povratak na zadano. Pogledajte [Prilagođeno ime Flippera](/hr/start/custom-name).

## Sub-GHz

### Postoji li regionalno zaključavanje? Kako da otključam Sub-GHz?

U Unleashedu **nema regionalnog zaključavanja**: svaka frekvencija koju čip podržava radi odmah po instalaciji. Izlazak **izvan specifikacija čipa** moguć je, ali može oštetiti hardver: [Opasne postavke](/hr/start/dangerous-settings).

### Koji su protokoli podržani i s kojom frekvencijom i modulacijom?

[Podržani sustavi](/hr/subghz/supported-systems).

### Kako da dodam dodatne frekvencije?

[Frekvencije i predlošci](/hr/subghz/frequencies).

### Mogu li klonirati ključ vlastitog automobila da bih Flipper koristio kao ključ?

**Ne.** Ključevi automobila i većina daljinskih upravljača za garažna vrata koriste **promjenjive kodove (rolling codes)**. Ponovno slanje snimljenog signala (primjerice iz Read RAW) desinkronizira brojač. U najgorem slučaju izvorni se ključ odspoji ili stavi na crnu listu, a ponovno uparivanje zahtijeva servisne alate.

**Zašto:** prijamnik pamti zadnju vrijednost brojača koju je primio od daljinskog upravljača (koliko je puta pritisnuta bilo koja tipka). Recimo da je izvorni daljinski upravljač poslao brojač `0002`, a vi ste s Flippera poslali isti signal s `0003`. Prijamnik ga prihvaća. No izvorni daljinski upravljač je još na `0002`, pa njegov sljedeći pritisak šalje `0003`, što je prijamnik već vidio i zato ne reagira. To još nije odspajanje: pritisnite izvornik još nekoliko puta kako biste "prestigli" Flipper (`0004`) i ponovno će raditi. Međutim, ako se ova utrka nastavi, razmak može narasti na **100+ pritisaka**, i izvorni daljinski upravljač više se ne može vratiti u rad bez ponovnog uparivanja s prijamnikom.

**Što učiniti umjesto toga:**
- koristite samo **jedan** daljinski upravljač: ili Flipper ili izvornik;
- **najbolje:** izradite **novi daljinski upravljač** na Flipperu pomoću **Add manually** i uparite ga s prijamnikom kao zaseban daljinski upravljač ([Ručno dodavanje](/hr/subghz/add-manually), [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog));
- ako morate koristiti oba, koristite ih naizmjence kako se brojači nikada ne bi previše razišli.

Više: [Promjenjivi kodovi](/hr/subghz/rolling-codes), [Način brojača](/hr/subghz/counter-mode).

### Kako koristiti Flipper kao novi daljinski upravljač (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors…)?

[Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).

### Kako koristiti aplikaciju Sub-GHz Remote?

1. Otvorite aplikaciju, pritisnite <kbd>BACK</kbd> i odaberite **New map file**.
2. Odaberite datoteku signala i oznaku za svaku tipku. Tipke možete ostaviti praznima.
3. Spremite kartu.
4. Otvorite datoteku karte koju ste stvorili.
5. Pritišćite tipke za slanje dodijeljenih signala.

Pojedinosti: [Sub-GHz Remote](/hr/subghz/remote).

### Moj daljinski upravljač nije podržan (nije ključ automobila). Kako da ga snimim za programere?

1. **Pronađite frekvenciju.** **Sub-GHz → Frequency Analyzer**: držite tipku daljinskog upravljača blizu Flippera (antena je kod IR prozorčića na lijevoj strani). Pustite je i frekvencija odlazi u povijest. Držite <kbd>OK</kbd> za skok u **Read** i pritisnite daljinski upravljač nekoliko puta, držeći svaki pritisak najmanje 2 s. Isprobajte `AM650`, `FM238`, `FM476`, `FM12K`.
2. **Ništa se ne dekodira? Snimite RAW.** Otvorite **Read RAW**, u postavkama postavite frekvenciju i **RSSI Threshold** na `----`. Napravite po jednu snimku za **svaku** modulaciju (`AM650`/`FM238`/`FM476`/`FM12K`). Pritisnite **REC**, zatim pritisnite jednu tipku 5 puta držeći je 1–2 s, pa 5 puta držeći je ~5 s. Snimite svaku tipku na isti način i svaku datoteku nazovite po tipki.
3. **Prijavite to.** Zapakirajte RAW datoteke u ZIP i otvorite issue u repozitoriju firmvera. Priložite dobre fotografije daljinskog upravljača (po mogućnosti i iznutra), model i proizvođača te fotografiju pločice prijamnika ako možete.

Ako daljinski upravljač nije šifriran i dovoljno je jedinstven, podrška može biti dodana. Za samostalnu analizu signala isprobajte [lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter).

### Kako povezati vanjski modul CC1101?

[Vanjski CC1101](/hr/subghz/external-cc1101).

## NFC i RFID

### MIFARE Ultralight

Očitajte karticu, prislonite Flipper uz čitač kako biste uhvatili lozinku koja otključava preostale stranice, a zatim ponovno očitajte karticu: [Otključavanje lozinkom](/hr/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

Trenutačno na Flipperu ne postoje napadi za ove kartice.

### Bankovne kartice

Bankovne kartice ne možete klonirati, Flipper ih ne može emulirati niti može raditi kao terminal za plaćanje. Može čitati samo javne podatke: [Bankovne kartice (EMV)](/hr/nfc/emv).

### Amiibo

Amiibo su `NTAG215`. Ne mogu ići na MIFARE Classic i trenutačno ne možete zapisati Amiibo na nove fizičke oznake.

### HID / iClass (Picopass)

- Očitajte iClass pomoću aplikacije **Picopass**. Emulacija je podržana u aktualnim Unleashed inačicama s aplikacijama.
- 26-bitni Picopass može se spustiti (downgrade) na H10301 LF RFID pristupne podatke. To radi samo ako je čitač konfiguriran za LF. Neki iClass čitači rade samo na HF-u.
- Pisanje je moguće pomoću aplikacije za kartice u načinu personalizacije.
- Aplikacija **Seader** sa SAM pločicom za proširenje čita sigurnije HID kartice.

### Kloniranje 125 kHz RFID-a

Da biste kopirali LF privjesak, zapišite ga na **T5577**. Čipovi koje Flipper čita samo su za čitanje i "prazni" primjerci takvih čipova ne postoje. T5577 je višenamjenski čip za emulaciju koji se može programirati da se ponaša kao drugi privjesci: [Pisanje RFID-a](/hr/rfid/write), [aplikacija T5577](/hr/rfid/t5577-app).

### Nepoznata kartica ili privjesak

Ako NFC, RFID i Picopass redom ne uspiju, fotografirajte prednju i stražnju stranu kartice/privjeska te čitač. Za karticu, držite je ispred jakog izvora svjetlosti i fotografirajte antenu. Objavite fotografije u razgovorima zajednice radi identifikacije.

## Infrared

### Postoji li ispravan način za snimanje IR signala (osobito klima-uređaja)?

Da: [IR zapisi](/hr/infrared/captures).

## Datoteke i računala

### Gdje mogu pronaći datoteke (Sub-GHz, IR, NFC…) za svoj Flipper?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) i [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) pokrivaju većinu potreba.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero): gotovo svaka poveznica koja vam može zatrebati.

### Kako kopirati datoteke s GitHuba na Flipper?

Preuzmite datoteke na računalo i kopirajte ih na SD karticu (putem čitača kartica ili upravitelja datoteka u qFlipperu). Postoji i detaljan [vodič zajednice](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf).

### Kako očistiti `.DS_Store` i datoteke s točkom koje ostavlja macOS, ili razvrstati datoteke?

Pogledajte [microSD kartica → macOS](/hr/start/sd-card#macos-hidden-files-and-sorting).

### Kako otvoriti CLI ili pregledati zapisnike (logs)?

Prvo zatvorite qFlipper. Samo jedan program može držati serijski port.

- **Preglednik (Chromium):** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → odaberite USB serijski uređaj → **CLI** na bočnoj traci.
- **Windows:** pronađite COM port u qFlipperu, zatvorite qFlipper, zatim u programu PuTTY odaberite **Serial**, unesite COM port i brzinu `115200` pa kliknite **Open**. "Access Denied" znači da je qFlipper još pokrenut.
- **macOS/Linux:** pronađite putanju uređaja u qFlipperu (počinje s `/dev/tty`) ili naredbom `ls /dev/tty.*`, zatvorite qFlipper, zatim pokrenite (zamijenite `PATH`):
  ```bash
  screen PATH 115200
  ```
- **Android:** aplikacija *Serial USB Terminal*, povezana putem USB OTG-a.
- **iPhone:** nema USB serijskog porta. Koristite drugu metodu.

Za prikaz zapisnika postavite **Settings → System → Log Level** na `Debug` i upišite `log` u CLI. <kbd>Ctrl</kbd>+<kbd>C</kbd> izlazi. Više: [CLI](/hr/dev/cli).

### Kako samostalno kompilirati firmver?

[Kompilacija firmvera](/hr/dev/build).

## Zajednica

- Izdanja: Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Razvojne inačice: Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Više poveznica: [Poveznice](/hr/community/links)
