---
title: Stromversorgung und Akku
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Stromversorgung und Akku

Im Flipper Zero steckt ein Li-Po-Akku mit **2100 mAh**. Im Standby hält er rund einen Monat, und über USB-C ist er in
etwa zwei Stunden geladen.

## Ein- und ausschalten

- **Einschalten:** halte <kbd>BACK</kbd> etwa 3 s gedrückt. Ein vollständig entladener Flipper schaltet sich von selbst
  ein, sobald du USB anschließt.
- **Ausschalten:** halte <kbd>BACK</kbd> auf dem Desktop gedrückt. Es erscheint der Bildschirm **Turn Off Device?**:
  <kbd>→</kbd> **Power Off** schaltet das Gerät aus, <kbd>←</kbd> **Battery** öffnet die Akku-Infos. Es geht auch über
  **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? mit dem weinenden Delfin, Battery auf der linken und Power Off auf der rechten Taste](/screens/settings/power_off.png)

## Laden

Steck das USB-C-Kabel an ein Ladegerät oder einen Computer. Während des Ladens zeigt das Akkusymbol einen Blitz. Der
Ladeeingang liefert 5 V / 1 A, eine volle Ladung dauert also etwa 2 Stunden.

::: warning Lange Lagerung
Wenn der Flipper längere Zeit nicht benutzt wird, lade ihn vor dem Ausschalten auf etwa **50 %**. Vollständig entladene
Lagerung schadet dem Akku. Halte das Gerät bei 0–40 °C.
:::

## Settings → Power

| Menüpunkt | Funktion |
|---|---|
| **Battery Info** | Ladezustand in %, Spannung, Strom, Akkutemperatur und Akkuzustand |
| **Reboot** | **Firmware Upgrade** (Neustart in den DFU-Modus) oder **Reboot Flipper** (normaler Neustart). Bestätigen mit <kbd>→</kbd> **Reboot** |
| **Power OFF** | Gerät ausschalten |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` — Abschalten nach dieser Zeit ohne Bedienung |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` — Laden auf diesem Stand beenden |

![Settings → Power: Battery Info, Reboot, Power OFF, Auto PowerOff OFF, Limit Charge OFF](/screens/settings/power.png)

::: tip Limit Charge
Limit Charge lohnt sich, wenn der Flipper fast den ganzen Tag am USB hängt, etwa als Schreibtisch-Gadget. Ein Akku, der
nicht dauernd auf 100 % gehalten wird, lebt länger.
:::

## Bildschirm Battery Info

Welche Meldung erscheint, hängt vom Zustand ab:

| Anzeige | Bedeutung |
|---|---|
| `Yummy!` / `Charging at` | Es wird geladen. Zeigt USB-Spannung und Ladestrom |
| `Om-nom-nom!` / `Consumption is` | Akkubetrieb mit der aktuellen Stromaufnahme. `Oh no!` und `mA!` stehen für hohen Verbrauch |
| `Charged!` | USB angeschlossen, kein Laden (Akku voll) |
| `Charged!` / `Limited to` | USB angeschlossen, und es ist eine abweichende Ladeschlussspannung gesetzt (in V angegeben) |
| `Napping...` | Akkubetrieb, praktisch keine Stromaufnahme |

Außerdem stehen dort Ladezustand in %, Spannung, Temperatur (°C oder °F, einstellbar über
**Settings → System → Units**) und der **Akkuzustand** in %.

![Battery Info: Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4,1 V, Zustand 100 %](/screens/settings/battery_info.png)

## Stromverbrauch

| Modus | Typischer Strom |
|---|---|
| Schlaf (Sleep Method `Default`) | ~1,5 mA |
| Schlaf (Sleep Method `Legacy`) | ~9 mA |
| Aktiv, Beleuchtung an | bis ~30 mA (bis ~50 mA mit einer schlechten SD-Karte) |
| Funk aktiv | bis ~400 mA |
| Funk + externes Modul | bis ~2 A |

**Sleep Method** steht in **Settings → System**. `Default` spart Energie. `Legacy` braucht mehr, kann aber helfen, wenn
das Gerät im Schlaf abstürzt.

Für den Schlafmodus müssen **Debug** = `OFF` (**Settings → System**) und **Listen UART** = `None`
(**Settings → Expansion Modules**) gesetzt sein. Sonst kann das Gerät nicht einschlafen und der Akku wird schneller leer.

## Tipps für längere Akkulaufzeit

- Halte die Firmware aktuell.
- Schalte Bluetooth aus, wenn du es nicht brauchst (Lock Menu → **Turn Bluetooth Off**).
- Reduziere **LCD Backlight** und **Backlight Time** unter **LCD and Notifications**.
- Verwende eine gute microSD-Karte eines Markenherstellers.
- Setze **Auto PowerOff**.
- Wird der Akku schnell leer, prüfe die Stromaufnahme unter **Battery Info**.

## Technische Daten zur Stromversorgung

| Parameter | Wert |
|---|---|
| Akkukapazität | 2100 mAh |
| Betriebsspannung des Akkus | 3,3–4,2 V |
| Ladezeit | ~2 Stunden |
| Ladespannung / Ladestrom | 5 V, 1 A |
| Anschluss | USB Type-C |
| Maximaler Strom aus USB einschließlich angeschlossener Geräte | 3 A |

## Siehe auch

- Neustart und Reset-Kombinationen: [Tastenkombinationen](/de/start/key-combos)
- Das Gerät schaltet sich nicht ein: [Wiederherstellung](/de/start/recovery)
