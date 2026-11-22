---
title: Mobilne i desktop aplikacije
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Mobilne i desktop aplikacije

Flipper radi samostalno, ali računalo ili pametni telefon znatno olakšavaju pojedine radnje: instaliranje i ažuriranje
firmvera, kopiranje datoteka, instaliranje aplikacija, izradu sigurnosne kopije ključeva i daljinskih upravljača te daljinsko upravljanje Flipperom.

| Alat | Radi na | Čemu služi |
|---|---|---|
| [qFlipper](/hr/mobile/qflipper) | Windows, macOS, Linux | instalacija Unleasheda iz `.tgz` arhive, upravitelj datoteka, sigurnosna kopija / vraćanje, oporavak |
| [Flipper mobilna aplikacija](/hr/mobile/mobile-app) | iOS, Android | ažuriranje putem Bluetootha (i prilagođeni `.tgz`), arhiva ključeva, katalog aplikacija, daljinsko upravljanje |
| [qUnleashed](/hr/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | vlastita aplikacija Unleasheda: ažuriranja firmvera putem BLE-a ili USB-a, arhiva, katalog aplikacija, udaljeni zaslon, CLI, oporavak Seed vrijednosti |
| [Web alati](/hr/mobile/web-tools) | preglednik | Web Installer, Sub-GHz karta i karta koordinata, Wi-Fi wardriving karta, ESP32 flasher, Flipper Lab |

::: tip Unleashed
Unleashed je u potpunosti kompatibilan sa službenim qFlipperom i službenom Flipper mobilnom aplikacijom. Najbrži način za
instalaciju ili ažuriranje Unleasheda je [Web Installer](/hr/mobile/web-tools#unleashed-web-installer) u pregledniku temeljenom na Chromiumu.
:::

::: warning Jedna veza istovremeno
Samo jedan program može koristiti USB serijski priključak Flippera. Zatvorite qFlipper prije korištenja Flipper Laba, Web Installera,
CLI terminala ili U2F-a te držite otvorenom samo jednu karticu Flipper Laba.
:::

## Stranice

- [qFlipper](/hr/mobile/qflipper)
- [Flipper mobilna aplikacija](/hr/mobile/mobile-app)
- [Prateća aplikacija qUnleashed](/hr/mobile/qunleashed-app)
- [Web alati](/hr/mobile/web-tools)
