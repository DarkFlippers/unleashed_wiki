---
title: Ažuriranje
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Ažuriranje

Unleashed se često ažurira. Ažuriranje funkcionira potpuno jednako kao instalacija: postavite novu inačicu **preko** trenutačne.
Ne trebate se vraćati na službeni firmver niti instalirati išta između.

## Kako ažurirati

**Preporučeno: [qUnleashed](/hr/mobile/qunleashed-app)**, prateća aplikacija za Unleashed za **Android, iOS, Windows,
macOS i Linux** (USB na svima osim na iOS-u, koji koristi Bluetooth). Sama preuzima novi firmver.

1. Instalirajte ili ažurirajte qUnleashed sa [stranice izdanja](https://github.com/DarkFlippers/qUnleashed/releases).
2. Povežite Flipper putem USB-a ili Bluetootha.
3. Otvorite **firmware updater**, odaberite kanal **Unleashed** (**Release** ili **Dev**) i izdanje koje koristite:
   **base**, **extra apps** ili **compact**.
4. Pokrenite instalaciju i pričekajte dok Flipper ne završi sve faze.

Ako se Flipper prestao pokretati, **Repair from DFU mode** u istoj aplikaciji ponovno ga snima (flasha) putem USB-a
([Oporavak](/hr/start/recovery#firmware-recovery)).

Alternative, sve opisane na stranici [Načini instalacije](/hr/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → odaberite Release ili Dev → Install.
2. **qFlipper**: **Install from file** s novom datotekom `flipper-z-f7-update-(version).tgz`.
3. **Mobilna aplikacija**: prilagođeni kanal ažuriranja (custom update channel) s `.tgz` datotekom.
4. **Izvanmrežno (offline)**: kopirajte `f7-update-(version)` u `/ext/update/` i otvorite `update.fuf` u aplikaciji Archive.

::: warning Ne pritišćite „Update” u qFlipperu / službenoj aplikaciji
Ugrađeni gumb **Update** u qFlipperu i aplikaciji Flipper Mobile App koristi **službeni** poslužitelj za ažuriranje. On zamjenjuje
Unleashed tvorničkim firmverom. Za Unleashed koristite alat za ažuriranje u qUnleashu, **Install from file**, prilagođeni kanal
ili Web Installer.
:::

## Release ili dev?

| | Release | Dev |
|---|---|---|
| Stabilnost | Testirano | Može sadržavati greške (bugove) |
| Nove značajke | Sa svakim izdanjem | Čim se spoje u kôd |
| Gdje preuzeti | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Dev izdanja grade se automatski iz najnovijih commitova. Prethodno dev izdanje briše se sa stranice kad se učita novo.
Greške prijavite na [GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Što preživljava ažuriranje

- **Vaše datoteke na microSD kartici**: spremljeni ključevi, kartice, daljinski upravljači i skripte ostaju netaknuti.
- **Vaš prilagođeni naziv**: pohranjen na kartici u `/ext/dolphin/name.settings` ([Prilagođeni naziv Flippera](/hr/start/custom-name)).
- **Postavke**: obično se čuvaju. **Iznimka:** kad izdanje promijeni strukturu datoteke postavki, ta se datoteka jednom vraća na
  zadane vrijednosti. To se događa samo u određenim izdanjima. Ako se vaše postavke radne površine (PIN, favoriti…) resetiraju nakon
  ažuriranja, postavite ih ponovno i provjerite popis promjena (changelog).
- **Ugrađene aplikacije** u `/ext/apps/` zamjenjuju se samo inačicama iz novog firmvera. Paketi dodatnih aplikacija nikad ih ne mogu
  prebrisati niti vratiti na stariju inačicu.

## Provjera vaše inačice

- **Main Menu → Settings → About**: inačica firmvera, datum gradnje, grana i commit;
- ili držite <kbd>↓</kbd> na radnoj površini za zaslon za otklanjanje pogrešaka / informacije.

## Gdje pročitati što se promijenilo

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases): popis promjena za svako izdanje;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) na grani dev: što
  dolazi u sljedećem izdanju;
- ažuriranja aplikacija: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Poslužitelj za ažuriranje firmvera Unleashed

Unleashed vodi vlastiti poslužitelj za ažuriranje u istom formatu kao službeni:
`https://up.unleashedflip.com/directory.json`. Službene aplikacije ne mogu se usmjeriti na njega bez ponovnog prevođenja. **uFBT**
prihvaća ovaj URL kao argument za gradnju aplikacija prema Unleashed SDK-u (pogledajte [Gradnja firmvera](/hr/dev/build)).

## Ako ažuriranje ne uspije

1. Ponovno pokrenite uređaj kombinacijom <kbd>←</kbd> + <kbd>BACK</kbd> i pokušajte ponovno.
2. Isprobajte drugi način (qUnleashed ↔ Web Installer ↔ qFlipper ↔ izvanmrežno).
3. Provjerite SD karticu (**Settings → Storage → About SD Card**) ili je formatirajte nakon izrade sigurnosne kopije.
4. Ako i dalje ne uspijeva: [Oporavak](/hr/start/recovery).
