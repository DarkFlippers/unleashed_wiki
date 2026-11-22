---
title: Oporavak uređaja
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Oporavak uređaja

Što učiniti kada se Flipper zamrzne, ne želi se ažurirati, ne prikazuje ništa ili ste zaboravili PIN. Prođite korake po
redu, od najblažeg do najdrastičnijeg.

## 1. Najprije ponovno pokrenite uređaj

- **Zamrznut:** držite <kbd>←</kbd> + <kbd>BACK</kbd> oko 5 sekundi.
- **I dalje zamrznut:** odspojite USB i držite <kbd>BACK</kbd> 30 sekundi (resetiranje napajanja).
- **Ispražnjena baterija:** punite nekoliko minuta (ili sat vremena) pa pokušajte ponovno.
- Na ispravnom Flipperu: **Settings → Power → Reboot → Reboot Flipper**.

Sve kombinacije tipki: [Kombinacije tipki](/hr/start/key-combos).

## 2. Oporavak firmvera iz DFU načina {#firmware-recovery}

Upotrijebite ovo kada je firmver oštećen: ažuriranje ne uspijeva, zaslon prikazuje nasumične znakove ili ništa, ili tipke ne reagiraju.
USB DFU pokretač (bootloader) flasha firmver bez vlastitog operacijskog sustava uređaja.

### Korak 1: prebacite Flipper u DFU (način oporavka)

**Ako Flipper još radi, ali se ne ažurira ispravno:**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Potvrdite `Reboot to DFU Mode?` tipkom <kbd>→</kbd> **Reboot**.

*ili:* držite <kbd>←</kbd> + <kbd>BACK</kbd> 5 s, otpustite <kbd>BACK</kbd> i nastavite držati <kbd>←</kbd> dok se ne upali
**plava LED dioda**.

**Ako zaslon ne prikazuje ništa i tipke ne reagiraju:**
1. **Odspojite USB kabel.**
2. Držite <kbd>OK</kbd> + <kbd>BACK</kbd> **30 sekundi**. Prazan zaslon ovdje je normalan.

Zatim USB kabelom povežite Flipper s računalom.

### Korak 2: provjerite vidi li računalo DFU uređaj

| OS | Gdje pogledati | Naziv |
|---|---|---|
| Windows | Upravitelj uređaja (Device Manager) | **DFU in FS Mode** |
| macOS | Apple menu → About This Mac → System Report → Hardware → USB (ili `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

Nije prepoznat? Pokušajte drugi kabel. Uključite izravno u USB priključak na matičnoj ploči, ne preko čvorišta (huba) ili adaptera. Ili izvadite microSD
karticu, punite sat vremena i povežite bez kartice.

### Korak 3: popravak

Bilo koja od ove dvije aplikacije poslužit će svrsi. Obje u potpunosti ponovno flashaju Flipper putem USB-a.

**[qUnleashed](/hr/mobile/qunleashed-app)** — Android, Windows, macOS i Linux (iOS nema USB):

1. Povežite Flipper u DFU načinu putem USB-a.
2. Otvorite **Repair from DFU mode** i pokrenite ga.

**qFlipper** — Windows, macOS i Linux:

1. Pokrenite **qFlipper**. Prepoznat će DFU uređaj.
2. Kliknite **Repair**. qFlipper u potpunosti instalira **službeni** firmver.

Zatim ponovno instalirajte Unleashed: [Instalacija firmvera Unleashed](/hr/start/install).

::: tip Unleashed
Opcija **Repair** u alatu qFlipper uvijek vraća službeni firmver. To je u redu: daje vam čistu osnovu. Nakon popravka ponovno instalirajte
Unleashed pomoću aplikacije qUnleashed, Web Installera ili opcije **Install from file**. Datoteke na vašoj microSD kartici tijekom popravka ostaju netaknute.
:::

### Ako qFlipper ne može popraviti uređaj

- Provjerite je li qFlipper ispravno instaliran. Na sustavu Windows pogledajte qFlipperove upute za otklanjanje problema s upravljačkim programima.
- Odspojite USB, ponovno pokrenite kombinacijom <kbd>←</kbd> + <kbd>BACK</kbd> i ponovite postupak.
- Napravite resetiranje napajanja (<kbd>BACK</kbd> 30 s, odspojen USB) i ponovite.
- Pokrenite qFlipper kao administrator.
- Koristite USB priključak izravno na matičnoj ploči.
- Krajnje rješenje: flashajte putem SWD-a pomoću ST-Linka (pogledajte [Kombinacije tipki](/hr/start/key-combos#if-nothing-helps)).

## 3. Popravak interne pohrane / vraćanje na tvorničke postavke {#factory-reset}

Ako ažuriranja ne uspijevaju jer je interna pohrana puna ili oštećena, vratite Flipper na tvorničke postavke. Time se briše
**interna pohrana**: postavke, Bluetooth uparivanja, PIN, razina dupina. **Datoteke na microSD kartici ostaju.**

::: info Interna pohrana u trenutačnom firmveru
U trenutačnom firmveru interna pohrana (`/int`) je **virtualna** i nalazi se u skrivenoj mapi `/ext/.int/` na microSD
kartici. **Settings → Storage → About Internal Storage** prikazuje `Type: Virtual (/.int on SD)`.
:::

### Najprije izradite sigurnosnu kopiju (neobavezno)

qFlipper → **Advanced controls** → **BACKUP** → odaberite mapu → **BACKUP**. Time se interna pohrana sprema kao
`.tgz`. microSD kartica nije uključena, pa je kopirajte zasebno.

### Vraćanje na uređaju

1. **Main Menu → Settings → Storage → Factory Reset**.
2. Zaslon pita `Confirm Factory Reset?`: *"Internal storage will be erased, data and settings will be lost!"*
3. Pritisnite <kbd>→</kbd> **Erase** **5 puta**. Zaslon odbrojava preostale pritiske.
4. Flipper se ponovno pokreće i formatira internu pohranu.

### Vraćanje pomoću alata qFlipper

**Advanced controls** → **ERASE** → **ERASE** → **CONTINUE** po završetku.

### Vraćanje iz sigurnosne kopije

qFlipper → **Advanced controls** → **RESTORE** → odaberite `.tgz` sigurnosnu kopiju → **RESTORE** → **CONTINUE**.

Ako ažuriranje i dalje ne uspijeva nakon vraćanja na tvorničke postavke, ponovite resetiranje **bez** vraćanja sigurnosne kopije ili napravite
[oporavak firmvera](#firmware-recovery).

## 4. Resetiranje zaboravljenog PIN-a {#reset-pin}

Ako je Flipper zaključan PIN-om kojeg se ne sjećate:

1. **Odspojite USB kabel.**
2. Isključite Flipper: držite <kbd>BACK</kbd> → **Power Off**. Ako to ne možete, prijeđite na sljedeći korak, ali držite tipke
   30–40 sekundi.
3. Držite <kbd>↑</kbd> + <kbd>BACK</kbd> oko 5 sekundi. Flipper se pokreće s pritisnutim <kbd>↑</kbd> i prikazuje
   **zaslon za resetiranje PIN-a**.
4. **Držite <kbd>→</kbd>** dok se traka napretka ne ispuni kako biste potvrdili resetiranje. Umjesto toga pritisnite <kbd>↓</kbd> za izlaz bez
   resetiranja.
5. Flipper se ponovno pokreće.

Time se korisnička konfiguracija (RTC registri, interna pohrana s postavkama i PIN-om) vraća na tvorničke vrijednosti.
**Korisničke datoteke na microSD kartici ostaju.**

## 5. I dalje ne reagira?

- Punite sat vremena, zatim pokušajte ponovno.
- Odspojite i ponovno spojite bateriju (zahtijeva otvaranje kućišta).
- Flashajte putem SWD-a pomoću ST-Linka ili drugog programatora.

Ako ništa od toga ne pomogne, problem je hardverski, a ne softverski.

## Povezano

- [Kombinacije tipki](/hr/start/key-combos)
- [Instalacija firmvera Unleashed](/hr/start/install)
- [Popratna aplikacija qUnleashed](/hr/mobile/qunleashed-app)
- [qFlipper](/hr/mobile/qflipper)
