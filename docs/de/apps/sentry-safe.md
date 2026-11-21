---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Das Plugin **Sentry Safe** von [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) öffnet
elektronische Tresore von Sentry Safe und Master Lock **ohne PIN-Code**, über eine bekannte Schwachstelle in der
Verbindung zu deren Tastenfeld. Die Schwachstelle und eine Demo sind in
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe) beschrieben.

::: warning
Verwende das Plugin nur an einem Tresor, der dir gehört. Den Tresor einer anderen Person zu öffnen ist illegal.
:::

::: tip Unleashed
Sentry Safe ist ein GPIO-Plugin aus den Community-[App-Packs](/de/apps/catalog#base-and-extra-packs), es ist nicht
Teil der Firmware selbst.
:::

## Verkabelung

Der Flipper wird mit zwei Adern des Tresors verbunden (schwarz und grün). Die
[Beschreibung der Schwachstelle](https://github.com/H4ckd4ddy/bypass-sentry-safe) zeigt, wo du sie erreichst.

| GPIO-Pin des Flipper | Ader des Tresors |
|---|---|
| 8 (GND) | schwarz |
| 15 (C1) | grün |

Die Pin-Nummern sind die auf der GPIO-Stiftleiste des Flipper aufgedruckten Nummern, siehe
[GPIO-Pinbelegung](/de/gpio/pinout).

## Verwendung

1. Öffne die App **Sentry Safe** über `Main Menu → Apps` (es ist ein GPIO-Plugin, sieh im GPIO-Ordner nach).
2. Verbinde die Adern wie auf dem App-Bildschirm und in der Tabelle oben beschrieben.
3. Drücke <kbd>OK</kbd> (enter).
4. Öffne den Tresor.

## Fehlerbehebung

- Es passiert nichts: prüfe, ob GND wirklich zur schwarzen Ader und C1 (Pin 15) zur grünen Ader führt und ob der
  Kontakt stabil ist.

## Verwandte Seiten

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
