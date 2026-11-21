---
title: ZKTeco CMP200 Schrankenfernbedienung
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — Princeton in chinesischer Verpackung

*Ein kurzer Bericht von @gromovyna über die Fernbedienung für ZKTeco-Schranken, dazu wie man sie unter Unleashed
behandelt.*

![ZKTeco-CMP200-Fernbedienung](/img/remote/a2cb668ab24d6625.png)

## Einleitung

Vor einiger Zeit eröffnete nahe bei gromovyna eine Privatklinik und installierte eine **ZKTeco**-Schranke. Er war neugierig, aber es war wenig Verkehr und es gab kaum einen Grund, sich reinzuhängen, also wanderte das auf den mentalen Stapel „später".

![ZKTeco-Schranke (Foto aus dem Internet)](/img/remote/4cfaf6cbf4b21db6.png)

Als er dann von einem Termin kam, sah er den Schlüsselanhänger auf dem Empfangstresen einer der oberen Etagen liegen, fotografierte ihn, bestimmte das Modell mit Google Lens und setzte es auf seine Einkaufsliste. Vor dem Kauf fragte er MMX (xMasterX) — und es stellte sich heraus, dass das Rätsel längst gelöst war.

## Wie die Chinesen Princeton verpackt haben

Es ist alles recht prosaisch, und in **Unleashed** wird es (dank MMX) schon seit über einem Jahr unterstützt. Unter der Haube ist es ein gewöhnliches **Princeton** mit 8-Bit-Tastencode — und die Tastencodes sind gut bekannt, **bei jeder Fernbedienung dieselben**:

| Parameter | Wert |
|---|---|
| Frequenz | **430.50 MHz** |
| Modulation | **AM650** |
| Taste UP | `0x30` |
| Taste STOP | `0x03` |
| Taste DOWN | `0x0C` |

Das Beste daran: in Unleashed sind diese Tastencodes **bereits auf die Pfeiltasten gelegt**, ein einzelnes gespeichertes Signal wirkt also schnell wie die ganze Fernbedienung.

::: tip Unleashed
ZKTeco steht in der Liste der unterstützten Systeme von Unleashed als `ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` und hat einen eigenen Eintrag in `Add Manually`. 430.50 MHz steht in der Standard-Frequenzliste.
:::

## So nutzt du sie mit dem Flipper

Weil der Code statisch ist, ist eine Kopie mit dem Original identisch — beide funktionieren weiter, in beliebiger Reihenfolge.

### Möglichkeit 1 — deine Fernbedienung lesen

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Zurück.
3. Drücke eine Taste auf der CMP200 nah am Flipper. Ein `Princeton`-Signal erscheint.
4. <kbd>OK</kbd> → `Save`, Datei benennen.
5. Öffne sie unter `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> sendet die mitgeschnittene Taste; die Pfeiltasten senden die anderen Tasten (UP / STOP / DOWN).

### Möglichkeit 2 — eine Fernbedienung anlegen

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Wähle das Band `430.50 AM650` (es steht bei diesem Eintrag zuerst).
3. Benennen und speichern. Der Flipper legt einen Princeton-24-Bit-Schlüssel mit zufälligem Code an, TE 357 µs, Taste `0x30` (UP).

Eine so angelegte Fernbedienung hat ihren eigenen Code — die Schranke reagiert erst, wenn sie in ihrem Empfänger angelernt ist (folge der Anleitung der Schranke). Um wie eine bestehende Fernbedienung zu wirken, lies sie stattdessen (Möglichkeit 1).

::: warning
Nur für Schranken, die dir gehören oder die du verwaltest.
:::

## Ist das alles?

Für den Moment — ja. Wie gromovyna anmerkt, kam diese Unterstützung ganz leise, weshalb der Großteil der Community sie nie mitbekommen hat; er hat sie getestet und die Ergebnisse geteilt.

## Fehlersuche

- **Es wird nichts empfangen** — stelle sicher, dass die Frequenz 430.50 ist und nicht 433.92; prüfe mit dem [Frequency Analyzer](/de/subghz/frequency-analyzer).
- **`Ignore Princeton` ist ON** in `Config` von Read — Princeton-basierte Fernbedienungen wie diese sind dann ausgeblendet; schalte es aus.
- **Die Pfeiltasten senden nichts** — öffne das Signal über `Saved → Emulate`; die eigenen Tasten funktionieren im Sendebildschirm.

## Verwandte Seiten

- [Read](/de/subghz/read) · [Add Manually](/de/subghz/add-manually) · [Unterstützte Systeme](/de/subghz/supported-systems)
- [Rolling Codes](/de/subghz/rolling-codes) — eigene Tasten erklärt
