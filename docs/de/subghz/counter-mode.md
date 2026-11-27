---
title: Zählermodi
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Zählermodi (experimentell)

**Counter Mode** ändert, wie der rollierende Zähler weiterläuft, wenn der Flipper ein gespeichertes
Rolling-Code-Signal sendet. Das Ziel: ein Klon deiner Originalfernbedienung, der **nicht mit ihr kollidiert**,
sodass Flipper und Original ohne Desynchronisation am selben Empfänger genutzt werden können. (Hintergrund:
[Rolling Codes](/de/subghz/rolling-codes).)

::: tip Unleashed
Die Zählermodi gibt es nur in Unleashed. Unterstützte Protokolle: **Nice FloR-S, CAME Atomo, Alutech AT-4N,
KeeLoq, V2 Phoenix**.
:::

::: danger Vor dem Benutzen lesen
Experimentiere nicht mit Technik, zu der du keinen Zugang hast. Wenn du nicht sicher bist, welcher Modus bei
deinem System funktioniert, und deine Originalfernbedienung **nicht neu in den Empfänger programmieren kannst** —
nutze diese Modi nicht. Sie können deine Fernbedienung desynchronisieren oder aussperren. Kannst du an deinem
eigenen Empfänger testen, teile dem Unleashed-Team mit, was funktioniert (GitHub-Issues / Community-Chats).
:::

## So setzt du einen Modus

### Möglichkeit 1 — die `.sub`-Datei bearbeiten

1. Kopiere die Datei aus `/ext/subghz/` auf einen PC (qFlipper, Mobile-App oder Kartenleser).
2. Füge am Ende eine Zeile hinzu:
   ```text
   CounterMode: X
   ```
   wobei `X` die Modusnummer ist. Beachte das Leerzeichen nach dem Doppelpunkt.
3. Kopiere die Datei zurück.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### Möglichkeit 2 — Signal Settings auf dem Flipper

Mit aktivem **Debug** bekommt das Menü eines gespeicherten Signals einen zusätzlichen Punkt:
`Sub-GHz → Saved → <Datei> → Signal Settings`. Dessen Zeile `Counter Mode` bietet `System` (Modus 0) und
`Mode 1` … bis zum letzten Modus, den das Protokoll hat, und schreibt deine Wahl sofort in die Datei. Auf dem
gleichen Bildschirm lassen sich auch der Zähler und der Tastencode ändern:
siehe [Signal Settings](/de/subghz/signal-settings).

## Modi je Protokoll {#modes-by-protocol}

Modus 0 ist immer der Standard: verhält sich wie eine normale Fernbedienung, der Zähler wächst um den globalen
Wert [Counter Incr.](/de/subghz/settings) (Standard +1) und springt nach `0xFFFF` zurück auf 0.

### Nice FloR-S

| Modus | Zähler | Hinweise |
|---|---|---|
| 0 | +Multiplikator | Standard |
| 1 | `0x0001 / 0xFFFE` | Empfänger **floxi2r** |
| 2 | `0x0000 / 0x0001` | Empfänger **ox2** |

### CAME Atomo

| Modus | Zähler | Hinweise |
|---|---|---|
| 0 | +Multiplikator | Standard |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | funktioniert mit dem externen CAME **RE432**, vielleicht auch anderen |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | funktioniert mit dem externen CAME **RE432**, vielleicht auch anderen |
| 3 | eingefroren | der Zähler wird nicht erhöht |

### Alutech AT-4N

| Modus | Zähler | Hinweise |
|---|---|---|
| 0 | +Multiplikator | Standard |
| 1 | 3-Druck-Zyklus: `0x0000` (×4), `0x0001` (×4), dann `0xFFFE` (×4) + `0xFFFF` (×4) in einem Druck (~0,85 s) | Empfänger **MCSW-3.3M** (Druck 3 synchronisiert über den Überlauf hinweg neu) |
| 2 | Einzel-Druck-Resync-Paket (~1,5 s): `0x0000`–`0x0003` (je ×2) + `0x0004`–`0x0005` (je ×3) | andere Empfängerplatinen; der Dateizähler bleibt unverändert, sodass jeder Druck dasselbe Paket sendet |

### KeeLoq

| Modus | Zähler | Hinweise |
|---|---|---|
| 0 | +Multiplikator | Standard |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | funktioniert vielleicht mit manchen Systemen |
| 2 | `+0x3333` pro Sendung (13107) | z. B. DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | z. B. Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | z. B. Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | wechselt zwischen 0 und 65535 |
| 6 | eingefroren | der Zähler wird nicht erhöht |
| 7–10 | Pakete zur erzwungenen Resynchronisation | DoorHan, Phantom / Hiland, siehe unten |

#### Modi 7–10: Pakete zur erzwungenen Resynchronisation (DoorHan, Phantom / Hiland)

Diese Modi zählen den Zähler nicht weiter; jeder Tastendruck sendet ein **festes Paket** von Codes. Ein Empfänger
synchronisiert sich nur neu, wenn er zwei Sendungen mit **aufeinanderfolgenden** Zählern hört. Deshalb ist das
Paket aus aufeinanderfolgenden Paaren aufgebaut, so verteilt, dass jeder Hop im Resync-Fenster des Empfängers
bleibt und die Paare zusammen den ganzen Zählerraum abdecken. Das holt den Empfänger aus jedem Zustand zurück. Der
Zähler in deiner Datei wird nicht geändert, jeder Druck sendet also dasselbe Paket und die Datei bleibt nutzbar.

Jedes Paket gibt Code für Code wieder, was eine Klon-Fernbedienung für diese Platinenfamilie sendet. Modi 7–9 =
DoorHan-Smart-Klon, Modus 10 = Phantom-/Hiland-Klon. `X` = der Zähler in deiner Datei.

| Modus | Für | Paket | Zeit pro Druck |
|---|---|---|---|
| 7 | die ältesten DoorHan-Platinen | 12 Codes: `X / X+1`, vier Paare, die in Schritten von 15998 vorwärtslaufen (Taste 0), dann `X-2 / X-1`; das erste und letzte Paar tragen deine Taste | ca. 1,3 s |
| 8 | DHRE, die meisten neueren Platinen, Klone für Drehtore | 12 Codes: `X / X+1`, vier Paare mit Abstand `+0x3334`, dann zurück zu deinem Zähler, wo `X+1` mit deiner Taste landet | ca. 1,3 s |
| 9 | CV01-Rollladenplatinen, andere alte Platinen | 3 Codes mit deiner Taste: `X + 0x8000`, `X-1`, `X+1`, jeder zweimal gesendet | ca. 0,65 s |
| 10 | Phantom / Hiland | 2 Codes mit deiner Taste: absolut `0xFFFE`, `0xFFFF`, jeder dreimal gesendet | ca. 0,4 s |

::: warning Modus 7 hat sich geändert
Modus 8 ist genau das, was `CounterMode: 7` in früheren Versionen gemacht hat. Hast du eine Datei mit
`CounterMode: 7`, die funktioniert hat, ändere sie auf `CounterMode: 8`.
:::

Details:

- In den langen Paketen (7 und 8) geht jeder Code **einmal** hinaus (die originale Klon-Fernbedienung sendet jeden
  zwei- oder dreimal) — das ganze Paket wird im Speicher aufgebaut, und es zu verdreifachen bräuchte 20 KB statt
  8 KB. Das Paket erneut zu senden ist kein Ersatz: ein Empfänger, der sich schon neu synchronisiert hat, liest
  einen zweiten Durchlauf als neuen Durchgang und betätigt das Tor noch einmal, während eine unmittelbare
  Wiederholung eines einzelnen Codes als Duplikat ignoriert wird.
- Modus 10 ignoriert den Zähler in deiner Datei. Ohne Durchlauf synchronisiert ein Druck einen Empfänger neu, der
  irgendeinen der 32768 Werte unterhalb von `0xFFFE` hält — genau dort sitzt ein Empfänger, der deiner
  Fernbedienung vorausgelaufen ist. Greift es nicht, sende noch einmal.
- **Hält** man Send gedrückt, wiederholt sich das Paket, solange du hältst; ein Empfänger, der sich beim ersten
  Durchlauf neu synchronisiert hat, liest das als weiteren Tastendruck. Send noch einmal zu drücken, während ein
  Paket hinausgeht, **bricht es ab**.

### V2 Phoenix (Phox)

| Modus | Zähler | Hinweise |
|---|---|---|
| 0 | +Multiplikator | Standard |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` („ofex like") | nachgewiesen funktionierend |
| 2 | `0x0000 … 0x0004` | funktioniert vielleicht |

## Beispiel: KeeLoq DoorHan mit +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Fehlersuche und FAQ

- **Die Datei funktioniert nach dem Hinzufügen von `CounterMode` nicht** — prüfe die Schreibweise
  `CounterMode: X` (Leerzeichen nach dem Doppelpunkt) und ob die Nummer für das Protokoll gültig ist.
- **Ungültige Modusnummer?** Dann wird der letzte Modus aus der Liste des Protokolls genutzt.
- **Brauche ich das in jeder Datei?** Nein. Ohne `CounterMode` wird Modus 0 genutzt.
- **Kann das meine Fernbedienung / meinen Empfänger beschädigen?** Es kann deine Fernbedienung
  desynchronisieren, je nach Empfänger. Nutze es nicht, wenn du das Original nicht neu anlernen kannst.
- **Welchen Modus soll ich nehmen?** Wenn du unsicher bist — keinen. Nimm lieber eine
  [neue Fernbedienung](/de/subghz/add-manually).

## Verwandte Seiten

- [Signal Settings](/de/subghz/signal-settings) — Modus, Zähler und Taste auf dem Flipper setzen
- [Rolling Codes](/de/subghz/rolling-codes) · [KeeLoq](/de/subghz/keeloq)
- [Radio Settings: Counter Incr.](/de/subghz/settings) · [Das `.sub`-Dateiformat](/de/subghz/file-format)
