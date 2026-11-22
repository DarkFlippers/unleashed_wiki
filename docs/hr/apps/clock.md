---
title: Sat
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Sat

Noćni sat: veliki prikaz vremena, datum i razina baterije, upravljanje svjetlinom zaslona s crvenim LED noćnim svjetlom, štoperica i dnevni alarm. Temeljeno na aplikaciji FlipperNightStand autora @nymda, uz doprinos @Willy-JL, @mishamyte i @xMasterX (inačica aplikacije 1.3).

`Main Menu → Clock`

![Clock: datum iznad velikog prikaza vremena i razina baterije ispod njega](/screens/apps/clock.png)

::: tip Unleashed
U firmveru Unleashed, Clock je aplikacija u glavnom izborniku s alarmom i noćnim svjetlom. Ako želite prikazivati samo vrijeme na radnoj površini, umjesto toga uključite `Settings → Desktop → Show Clock`.
:::

## Tipke na zaslonu sata

| Tipka | Radnja |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | pojačavanje / smanjivanje svjetline zaslona (prikazuje se traka koja se skriva 3 s nakon zadnjeg pritiska) |
| <kbd>↓</kbd> pri svjetlini 0 | uključivanje / isključivanje prigušenog crvenog LED noćnog svjetla |
| <kbd>OK</kbd> | pokretanje / zaustavljanje štoperice |
| <kbd>←</kbd> | poništavanje štoperice |
| <kbd>→</kbd> | postavljanje alarma |
| <kbd>Back</kbd> | izlaz |

Vrijeme prati format sustava: 12-satni s AM/PM ili 24-satni, kako je postavljeno u `Settings → System → Time Format`.

## Štoperica

1. Pritisnite <kbd>OK</kbd> za pokretanje; proteklo vrijeme prikazuje se kao `MM:SS`.
2. Ponovno pritisnite <kbd>OK</kbd> za zaustavljanje, a još jednom za nastavak.
3. Pritisnite <kbd>←</kbd> (**Reset**) za brisanje.

## Dnevni alarm

1. Na zaslonu sata pritisnite <kbd>→</kbd>.
2. Postavite **Alarm** na **ON** pomoću <kbd>←</kbd> / <kbd>→</kbd>.
3. Odaberite **Set time** i pritisnite <kbd>OK</kbd>.
4. U izborniku `Alarm time`: <kbd>←</kbd> / <kbd>→</kbd> odabire sate, minute (i AM/PM u 12-satnom načinu), <kbd>↑</kbd> / <kbd>↓</kbd> mijenja vrijednost (držite za ponavljanje). <kbd>OK</kbd> ili <kbd>Back</kbd> sprema postavku.
5. Pritisnite <kbd>Back</kbd> za povratak na sat. Vrijeme alarma prikazano je na zaslonu sata.

Kada se alarm oglasi, na zaslonu treperi `! ALARM !` uz poruku `Press any key to stop`, svira melodija uz vibraciju i crvenu LED diodu. Pritisnite bilo koju tipku za zaustavljanje. Alarm ostaje aktivan i ponovno se oglašava sljedećeg dana u isto vrijeme.

::: warning
Alarm zvoni samo dok je aplikacija Clock otvorena. Ostavite Flipper na punjaču s otvorenom aplikacijom Clock preko noći.
:::

Postavke alarma i razine svjetline spremaju se u `/ext/apps_data/clock/` i vraćaju se pri sljedećem otvaranju aplikacije.

## Povezane stranice

- [Radna površina](/hr/start/desktop)
- [Postavke](/hr/start/settings)
- [Aplikacije uključene u Unleashed](/hr/apps/catalog)
