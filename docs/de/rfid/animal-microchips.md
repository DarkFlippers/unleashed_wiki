---
title: Tierchips
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Tierchips (FDX-B, FDX-A)

Haustierchips sind reiskorngroße RFID-Transponder, die unter die Haut implantiert werden. Versorgt sie ein Lesegerät
mit Energie, senden sie eine ID, die man in Haustierregistern nachschlagen kann. Flipper Zero liest die zwei
verbreiteten LF-Typen:

| Typ | Name im Flipper | Beschreibung |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, 15-stellige ID; der häufigste Typ; manche Chips melden außerdem die Körpertemperatur |
| **FDX-A** | `FDX-A` (FECAVA) | ältere, 10-stellige Chips außerhalb der ISO-Norm |

Die meisten Tierchips arbeiten bei **134,2 kHz**, während die Antenne des Flippers auf 125 kHz abgestimmt ist —
deshalb ist die Lesereichweite kurz, etwa **1 cm**. Chips im Bereich 110–140 kHz lassen sich lesen, aber nur näher
dran.

::: tip Unleashed
Die offizielle Dokumentation empfiehlt *Read ASK*. Unleashed erzeugt für diese Chips ein echtes
**134,2-kHz**-Feld:
- **Read** läuft nach ASK und PSK jetzt einen dritten Durchgang, **134kHz**;
- `Extra Actions → Read FDX-B (Animals)` bleibt die ganze Zeit auf 134,2 kHz — die beste Wahl für schwache Chips;
- der Ländername für FDX-B wird in `/ext/lfrfid/assets/iso3166.lfrfid` nachgeschlagen.
:::

## Den Chip eines Haustiers lesen

1. Öffne `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. Auf dem Display steht *Reading FDX-B*.
2. Finde den Chip:
   - bei Hunden und Katzen meist unter der Haut **zwischen den Schulterblättern**; in Kontinentaleuropa oft
     **mittig an der linken Halsseite**. Chips können etwas wandern;
   - taste mit den Fingerspitzen vorsichtig nach einem festen, reiskorngroßen Körper und setze dann die Mitte der
     Flipper-Rückseite genau darüber.
3. Halte den Flipper an jeder Stelle etwa **3 Sekunden** still. Passiert nichts, bewege ihn in kleinen Schritten über
   die Fläche, drehe ihn dann um 90° und wiederhole das.
4. Achte auf die LED: Gelb/Grün heißt, dass ein Signal ankommt — bleib dort.
5. Ist der Chip dekodiert, erscheint der Ergebnisbildschirm. <kbd>→</kbd> **More → Save** speichert ihn.

## Was der Flipper bei FDX-B anzeigt

| Feld | Bedeutung |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | 3-stelliger Ländercode (ISO 3166-1 numerisch) oder Herstellercode + 12-stellige nationale ID — die 15-stellige Nummer zum Nachschlagen |
| Country Code / Country | der Code und sein Name aus der ISO-3166-Tabelle |
| Temperature | bei Thermo-Chips in °C und °F; `---`, wenn nicht vorhanden |
| Animal | Anwendungs-Flag „Tier" |
| Visual Start Digit, Replacement Number, User Info, RFU | Header-Felder des ISO-Frames |
| Data Block | Present / Absent — zusätzlicher Datenblock (z. B. Temperatur) |
| RUDI Bit | Yes / No |

Bei FDX-A werden eine 10-stellige Hex-`ID` und `Parity` angezeigt.

::: warning
Die Chiptemperatur ersetzt kein richtiges Thermometer.
:::

## Die ID nachschlagen

Gib die 15-stellige ID in einem Haustierregister ein, zum Beispiel:
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — USA und Kanada
- [Europetnet](https://www.europetnet.com/) — Europa
- [PETMAXX](http://www.petmaxx.com/) — weltweit

Oder frage deine Tierarztpraxis bzw. das örtliche Register.

## Wenn der Chip nicht gefunden wird

- Außer Reichweite — kleinere Schritte und an jedem Punkt länger halten.
- Der Chip ist gewandert — eine größere Fläche abtasten.
- Metall oder Elektronik in der Nähe — Abstand suchen.
- Das Tier könnte einen 13,56-MHz-Chip haben — probiere [NFC](/de/nfc/read).
- Nicht unterstützter Chip — lass ihn in der Tierarztpraxis auslesen.

FDX-B-Schlüssel lassen sich auch [emulieren oder schreiben](/de/rfid/write) (T5577- und EM4305-Rohlinge, die es auch
als Glasröhrchen gibt), etwa um eine Katzenklappe zu testen.

## Verwandte Seiten

- [Lesen](/de/rfid/read) · [Protokolle](/de/rfid/protocols) · [Schreiben](/de/rfid/write)
