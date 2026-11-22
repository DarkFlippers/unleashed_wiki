---
title: Razvoj
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Razvoj

Ovaj odjeljak namijenjen je onima koji žele ići korak dalje od samog korištenja Flippera: izgraditi firmver Unleashed iz izvornog kôda, napisati vlastite aplikacije u jeziku C ili JavaScript, otklanjati pogreške na stvarnom hardveru, komunicirati s uređajem putem naredbenog retka ili razumjeti kako ažuriranja i hardver rade ispod haube.

::: tip Unleashed
Unleashed je račvanje (fork) službenog firmvera koje ostaje **u potpunosti kompatibilno sa službenim API-jem i aplikacijama**. Gotovo sve iz službene dokumentacije za programere vrijedi bez izmjena. Glavne stvari koje treba zapamtiti:

- klonirajte `https://github.com/DarkFlippers/unleashed-firmware` umjesto službenog repozitorija;
- kada gradite aplikacije alatom **uFBT**, usmjerite ga na Unleashed SDK (`--index-url=https://up.unleashedflip.com/directory.json`), inače će se aplikacija izgraditi za službeni SDK i možda se neće htjeti učitati ([detalji](/hr/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- podrijetlo firmvera prijavljuje se kao `Unleashed`, a trenutačna inačica API-ja na grani `dev` jest **88.27**.
:::

## Izgradnja firmvera

| Stranica | Što dobivate |
|---|---|
| [Izgradnja firmvera](/hr/dev/build) | Kloniranje, izgradnja i snimanje firmvera Unleashed na Linuxu, macOS-u i Windowsima |
| [Flipper Build Tool (fbt)](/hr/dev/fbt) | Svaki `fbt` cilj, opcija i varijabla okruženja |
| [Hardverski ciljevi](/hr/dev/hardware-targets) | Kako `targets/` i `target.json` opisuju varijante hardvera (f7, f18) |
| [Izgradnja aplikacija na Androidu](/hr/dev/android-build) | Prevođenje `.fap` aplikacija na telefonu putem Termuxa + uFBT-a, bez računala |

## Pisanje aplikacija

| Stranica | Što dobivate |
|---|---|
| [Vaša prva aplikacija u C-u](/hr/dev/first-app-c) | uFBT, predložak aplikacije, „Hello world“ s dijalogom, izgradnja i pokretanje |
| [Manifesti aplikacija (.fam)](/hr/dev/app-manifests) | Sva polja datoteke `application.fam`, opcije vanjskih aplikacija, privatne biblioteke |
| [Furi API](/hr/dev/furi-api) | Hardverska i softverska arhitektura, Furi jezgra, `furi_assert` / `furi_check` |
| [GUI u aplikacijama](/hr/dev/gui) | Dijalozi, ViewPort, prikazi i scene, moduli prikaza |
| [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging) | SWD sonde, otklanjanje pogrešaka u VS Codeu, Furi HAL signali za debugiranje |
| [FuriHalBus API](/hr/dev/furi-hal-bus) | Pravilno uključivanje/isključivanje MCU periferije, mapa DMA kanala |
| [JavaScript na Flipperu](/hr/dev/js-about) | Pisanje skripti u JavaScriptu umjesto u C-u (zasebna skupina stranica) |
| JS moduli dostupni samo u Unleashedu | [subghz](/hr/dev/js-subghz), [infrared](/hr/dev/js-infrared), [blebeacon](/hr/dev/js-blebeacon), [usbdisk](/hr/dev/js-usbdisk), [i2c](/hr/dev/js-i2c), [spi](/hr/dev/js-spi), [vgm](/hr/dev/js-vgm) — nisu u službenom firmveru ni u službenoj dokumentaciji |

## Rad s uređajem

| Stranica | Što dobivate |
|---|---|
| [Sučelje naredbenog retka (CLI)](/hr/dev/cli) | Povezivanje putem USB serijske veze; svaka CLI naredba s argumentima |
| [OTA ažuriranja](/hr/dev/ota) | Kako radi alat za ažuriranje, polja manifesta, kodovi pogrešaka `[XX-YY]`, izrada paketa |
| [Format Heatshrink tarball](/hr/dev/tar-heatshrink) | Spremnik `.tar.hs` koji se koristi za resurse u paketima ažuriranja |
| [Hardver](/hr/dev/hardware) | Tehničke specifikacije, sheme, 3D modeli, nacrti modula i razvojnih ploča |

## Testiranje

| Stranica | Što dobivate |
|---|---|
| [Jedinični testovi](/hr/dev/unit-tests) | Izgradnja i pokretanje aplikacije `unit_tests` na uređaju, dodavanje vlastitih testova |
| [Integracijsko testiranje](/hr/dev/testing) | Ručni plan testiranja koji se koristi prije spajanja PR-ova i objava |

## Ostali korisni resursi

- Službena dokumentacija za programere (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — mjesto za pretraživanje API-ja firmvera koje ovaj wiki ne pokriva, s odjeljcima o sistemskom programiranju, razvoju aplikacija, JavaScriptu, modulima za proširenje i formatima datoteka
- Postavljanje radnog prostora u CLionu — [vodič Savelyja Krasovskog](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Vodiči za „Hello world!“ dodatak: [engleski (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial), [ruski (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [Kako napisati vlastitu aplikaciju](https://flipper.atmanos.com/docs/overview/intro)

### Struktura projekta u repozitoriju firmvera

| Mapa | Sadržaj |
|---|---|
| `applications` | Aplikacije i servisi korišteni u firmveru |
| `assets` | Resursi koje koriste aplikacije i servisi |
| `furi` | Furi Core: osnovni primitivni elementi i pomoćne funkcije na razini OS-a |
| `debug` | Alati za otklanjanje pogrešaka: GDB dodaci, SVD datoteka itd. |
| `documentation` | Izvori dokumentacije i konfiguracije generatora |
| `firmware` | Izvorni kôd firmvera |
| `lib` | Vlastite i biblioteke trećih strana, upravljački programi |
| `site_scons` | Pomoćni alati za izgradnju |
| `scripts` | Dodatne skripte i Python biblioteke |
| `targets` | Definicije hardverskih ciljeva (`f7`, `f18`) |

Mnoge od ovih mapa imaju vlastitu datoteku `ReadMe.md` — vrijedi ih pročitati.
