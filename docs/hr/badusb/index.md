---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

Aplikacija **Bad USB** pretvara Flipper u tipkovnicu (i miš) koja na računalo upisuje pripremljenu skriptu. Računalo ga vidi kao običan uređaj ljudskog sučelja (HID), pa nisu potrebni upravljački programi. Skripte se pišu u proširenom jeziku **DuckyScript** (jeziku uređaja USB Rubber Ducky) i pohranjuju kao obične `.txt` datoteke na microSD kartici.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Uobičajene legitimne primjene: automatizacija ponavljajućeg postavljanja na vlastitim računalima, upisivanje dugih lozinki ili konfiguracija, instaliranje softvera na novo računalo, demonstracije i edukacije o sigurnosnoj svijesti.

::: danger Pravna napomena
Uređaj za ubrizgavanje pritisaka tipki može učiniti sve što i osoba za tipkovnicom. Pokrećite skripte samo na računalima koja posjedujete ili za čije testiranje imate izričito odobrenje.
:::

Aplikacija radi putem **USB** kabela ili putem **Bluetootha (BLE)**, pri čemu se domaćinu predstavlja kao Bluetooth tipkovnica.

::: tip Unleashed
Unleashed integrira **BadKB** (autori Willy-JL, ClaraCrazy i suradnici XFW-a) izravno u aplikaciju Bad USB:
- **BLE način rada** s podesivim nazivom uređaja, MAC adresom, načinom uparivanja i trajnim uparivanjem, uz naredbe skripte `BLE_ID` / `BT_ID`;
- postavke **USB identiteta**: naziv proizvođača i proizvoda, VID/PID, nasumično mijenjanje;
- **rasporedi tipkovnice** za mnoge jezike ([autor rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- naredba **`DUCKY_LANG`**, koja skripti omogućuje odabir vlastitog rasporeda tipkovnice (novo u trenutačnom izdanju, PR #1224, autor @ANTONiO-eagle).
:::

## Datoteke

| Putanja | Sadržaj |
|---|---|
| `/ext/badusb/` | Vaše skripte (`.txt`). Preglednik datoteka aplikacije otvara se ovdje. |
| `/ext/badusb/examples/` | Pokazne skripte isporučene s firmverom (Windows, macOS, GNOME, ChromeOS, test miša, instalatori za qFlipper). |
| `/ext/badusb/assets/layouts/` | Datoteke rasporeda tipkovnice (`.kl`). Pogledajte [Rasporedi tipkovnice](/hr/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Postavke aplikacije: globalni raspored, USB/BLE način rada, USB i BLE identitet. |

Prenesite skripte putem programa [qFlipper](/hr/mobile/qflipper), [mobilne aplikacije](/hr/mobile/mobile-app) ili kopiranjem na SD karticu. Datoteka istog naziva prebrisuje se bez upozorenja.

## Stranice u ovom odjeljku

| Stranica | Što ćete naučiti |
|---|---|
| [Korištenje aplikacije Bad USB](/hr/badusb/usage) | Pokretanje skripti putem USB-a i BLE-a, izbornik Config, sve postavke |
| [Format skripte](/hr/badusb/script-format) | Potpuna referenca naredbi: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, miš, ID, DUCKY_LANG… |
| [Primjeri](/hr/badusb/examples) | Sigurne pokazne skripte za početak |
| [Rasporedi tipkovnice](/hr/badusb/layouts) | Koji rasporedi postoje, kako rade, odabir po skripti |
