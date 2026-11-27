---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq ist die Verschlüsselung hinter einer riesigen Zahl von Tor-, Garagentor- und Schrankenfernbedienungen
(DoorHan, Nice Smilo, FAAC RC, BFT, Came Space, Beninca, Hormann EcoStar …) und älteren Autoalarmanlagen. Diese
Seite erklärt, wie sie funktioniert, was „Herstellerschlüssel" und „Seeds" sind und wie Unleashed damit umgeht.

Der Theorieteil beruht auf dem Artikel **„KeeLoq и с чем его едят"** von
[@li0ard](https://blog.li0ard.rest/wtfiskeeloq), einem Mitglied des Forschungsteams von @gromovyna, der ihn in
[seinem Kanal](https://t.me/gromovyna/24) allen empfiehlt, die diese Verschlüsselung verstehen wollen.

## Was KeeLoq ist

KeeLoq ist eine Blockverschlüsselung auf Basis eines NLFSR (nichtlinear rückgekoppeltes Schieberegister),
entworfen von Nanoteq Pty Ltd. und an Microchip Technology Inc. verkauft. Sie verschlüsselt **32-Bit-Blöcke** mit
einem **64-Bit-Schlüssel** in **528 Runden**. Sie setzt *Code Hopping* um: jede Sendung ist ein eigenes Paket.

### Aufbau eines Pakets

Ein 64-Bit-KeeLoq-Paket, z. B. `239B3DEBF16C47A6`, besteht aus:

- **Fix** (die ersten 4 Byte, `239B3DEB`) — unverschlüsselt gesendet: die Tasten-ID (`2`) und die 28-Bit-
  Seriennummer der Fernbedienung (`39B3DEB`).
- **Hop** (die letzten 4 Byte, `F16C47A6`) — mit dem Herstellerschlüssel verschlüsselt. Entschlüsselt sieht er aus
  wie `21EB000A`: wieder die Tasten-ID (`2`), 12 Bit Diskriminierungsdaten (oft `serial & 0x3FF`) und der
  **16-Bit-Zähler** (`000A`).

![Aufbau eines KeeLoq-Pakets](/img/remote/167cc7293a53adb1.png)

Genau das zeigt der Flipper nach einem [Read](/de/subghz/read): `Fix`, `Hop`, `Btn`, `Cnt` und den Herstellernamen.

### Die Zählerlogik

- Zähler gleich dem Wert, den der Empfänger erwartet → Befehl ausgeführt.
- Zähler **höher** als der gespeicherte → der Empfänger synchronisiert sich darauf neu und arbeitet ab dem nächsten
  Druck normal.
- Zähler **niedriger** → ignoriert; manche Empfänger entkoppeln die Fernbedienung nach mehreren „alten" Werten.
  *Das ist die eigentliche Gefahr beim Experimentieren mit KeeLoq.* Siehe
  [Rolling Codes](/de/subghz/rolling-codes).

## Anlernverfahren (Schlüsselableitung)

Der Schlüssel, der den Hop tatsächlich verschlüsselt, wird aus einem **Herstellerschlüssel** abgeleitet (64 Bit,
für alle Fernbedienungen einer Marke bzw. Modellreihe derselbe). Der Standard definiert drei Verfahren:

| Verfahren | Wie der Schlüssel pro Fernbedienung entsteht |
|---|---|
| **Simple learning** | der Herstellerschlüssel wird unverändert genutzt (am schwächsten) |
| **Normal learning** | der Herstellerschlüssel wird mit der Seriennummer der Fernbedienung vermischt |
| **Secure learning** | nutzt einen zusätzlichen Wert — den **Seed** — der pro Fernbedienung einmalig ist und nur beim Anlernen gesendet wird (das stärkste Standardverfahren) |

Hersteller erfinden auch eigene Varianten, z. B. **Magic XOR Type-1** (Beninca: Seriennummer XOR
Herstellerschlüssel) oder **FAAC SLH (SPA)** — eine Folge von Bitoperationen und Verschlüsselungen, nach li0ards
Meinung die durchdachteste davon.

::: tip Unleashed
Unleashed setzt alle Standardverfahren plus viele herstellereigene um (`lib/subghz/protocols/keeloq_common.h`):
Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3, KingGates, Jarolift, Erreka, Pujol,
AERF, JCM, JCM Gen2, Stagnoli und das tabellenbasierte Telcoma-Verfahren. Über 100 Hersteller sind unter
[Unterstützte Systeme](/de/subghz/supported-systems) aufgeführt.
:::

## Herstellerschlüssel in Unleashed

Um ein KeeLoq-Signal zu dekodieren, muss der Flipper den Herstellerschlüssel kennen. Unleashed liefert sie in
einem **verschlüsselten** Keystore auf der SD-Karte mit:

| Datei | Zweck |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | eingebaute Schlüssel, verschlüsselt (`Encryption: 1`), wird mit der Firmware aktualisiert |
| `/ext/subghz/assets/keeloq_mfcodes_user` | **deine eigenen** Schlüssel, im Klartext (lege sie aus `keeloq_mfcodes_user.example` an) |

Wird ein Signal dekodiert, probiert der Flipper jeden Schlüssel durch; bei Erfolg erscheint der Name als
`KL: DoorHan`, `KL: Nice_Smilo` usw. Auch Half-Rate-KeeLoq-Fernbedienungen zeigen ihren echten Herstellernamen an
(statt `Crypt Key`), in der Read-Liste als `KL HR` und in der Signalinfo als `66b HR` markiert. Passt kein Schlüssel,
zeigt sich das Signal als **`KL: Unknown`**: es lässt sich speichern, aber nicht senden und nicht nutzen, um den
nächsten Code zu erzeugen. Die `subghz`-CLI-Befehle, die Signale dekodieren, geben beim Start
`Load_keystore keeloq_mfcodes OK` und `Load_keystore keeloq_mfcodes_user OK` / `Absent` aus — ein schneller Weg zu
prüfen, ob die Keystores geladen werden.

### Format der eigenen Schlüsseldatei

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - manufacture key, 64 bit
# X - learning type: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - iterates over both previous and man in direct and reverse byte sequence
# NAME - name (no spaces), max 64 characters
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Lass am Ende der Datei eine leere Zeile stehen. Die `_user`-Datei wird von Updates nicht überschrieben.

### Die Felder `Manufacture` und `Seed`

Eine gespeicherte KeeLoq-`.sub` speichert den Hersteller mit Namen:

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

Systeme mit Secure learning speichern außerdem `Seed: XX XX XX XX`. Fügt man die Zeilen `Seed` + `Manufacture` von
Hand in eine Datei ein, die als `KL: Unknown` gelesen wird, lässt sie sich dekodieren (siehe BFT/Erreka unten).

## Seeds: BFT Mitto, Erreka, FAAC SLH, Genius

Diese Systeme nutzen einen **Seed** pro Fernbedienung (oder pro Anlage); ohne ihn wird das Signal als
`KL: Unknown` gelesen (oder gar nicht dekodiert) und es lässt sich keine akzeptierte Fernbedienung bauen.

- **BFT Mitto** — neuere Fernbedienungen leiten den Seed aus der Seriennummer ab und werden in Read direkt
  dekodiert (`KL: BFT`). Ältere haben einen einmaligen Seed. Versetze das Original in den Programmiermodus
  (Nadelöffnung auf der Rückseite oder Tasten 1+2): es sendet ein Paket, dessen `Fix` mit `F` beginnt; der `Hop`
  dieses Pakets **ist der Seed** im Klartext.
- **Erreka IRIS** — überbrücke die Pins `1` und `5` des fünfpoligen Steckers an der Seite: wieder beginnt `Fix`
  mit `F` und `Hop` ist der Seed. Manche Anlagen geben **jeder** Fernbedienung denselben Seed — dann muss eine neue
  Fernbedienung ihn übernehmen.
- **FAAC SLH / Genius** — lies den Seed von einer **Master**-Fernbedienung im Programmiermodus; der Seed ist
  **pro Taste** unterschiedlich.
- Keine Programmiertaste verfügbar? Nimm die App **[Seed Capturer](/de/subghz/seed-capturer)**: sie sammelt
  aufeinanderfolgende Fix/Hop-Paare, und der Seed wird in der Begleit-App qUnleashed zurückgerechnet.

Mit dem Seed legst du die Fernbedienung unter `Sub-GHz → Add Manually [Advanced]` an (SERIAL → BUTTON → COUNTER →
SEED), siehe [Add Manually](/de/subghz/add-manually) und
[Fernbedienung anlernen](/de/subghz/remote-prog).

## Bekannte Angriffe (Überblick)

Aus li0ards Artikel, zum Verständnis — keine Anleitung.

**Theoretisch:** Slide-Angriff (~2³² Klartext-/Geheimtextpaare, liefert die ersten 32 Schlüsselbits),
Korrelationsansatz (nutzt eine 5/8-Verzerrung des NLFSR), linearer Schritt (die letzten 16 Schlüsselbits, sobald
der Rest bekannt ist). Gesamtkomplexität ≈ 2⁵².

**Praktisch** (dank der Materialien von Derek Jamison, „SubGHz Rolling Flaws"):

| Angriff | Idee |
|---|---|
| Replay | ein mitgeschnittenes Paket erneut senden; funktioniert bei statischen Codes und bei Empfängern, die den Zähler nicht prüfen |
| Fernbedienung klonen | mit dem Herstellerschlüssel lässt sich eine funktionierende Kopie bauen — sie streitet sich aber mit dem Zähler des Originals und kann es entkoppeln |
| Future | einen weit vorausliegenden Zähler senden (`0001` → `3E91`); der Empfänger synchronisiert neu, das Original ist desynchronisiert |
| Rollback | den Zähler nach einigen Nutzungen zurückdrehen; seltene Empfänger synchronisieren sich auf alte Werte |
| RollJam | mitschneiden, während der Empfänger gestört wird, später nutzen. **Störsenden ist** in fast allen Ländern **illegal** |
| Herstellerschlüssel (KGB) | der Empfänger akzeptiert vielleicht mehrere Herstellerschlüssel; sende den originalen Fix mit einem Zähler, der mit einem anderen Schlüssel verschlüsselt ist |
| Enc00 | den Fix gegen den Fix einer anderen angelernten Fernbedienung tauschen und den originalen Hop nutzen; die andere Fernbedienung wird dadurch desynchronisiert |
| Unknown | kann ein Empfänger den Hop nicht entschlüsseln, nutzt er 0; Universalempfänger öffnen womöglich bei 0 |

Trotz allem bleibt KeeLoq — wie Mifare Classic mit seinem gebrochenen Crypto-1 — in günstigen Zutrittssystemen
beliebt; einige Hersteller (Beninca, Hormann) sind auf AES umgestiegen.

::: warning
Experimentiere nur mit deinen eigenen Fernbedienungen und Empfängern. Eine desynchronisierte oder entkoppelte
Fernbedienung muss vielleicht am Empfänger neu angelernt werden.
:::

## Fehlersuche

- **`KL: Unknown`** — kein passender Schlüssel. Prüfe die Modulation, aktualisiere die Firmware (neue Schlüssel)
  oder füge einen Schlüssel in `keeloq_mfcodes_user` ein, wenn er rechtmäßig dir gehört. Bei Seed-Systemen: den
  Seed zurückrechnen.
- **Wird dekodiert, aber der Empfänger ignoriert den Flipper** — du sendest einen Klon; siehe
  [Rolling Codes](/de/subghz/rolling-codes) und [Zählermodi](/de/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** in Add Manually — der Keystore fehlt; installiere die
  Firmware mit eingelegter SD-Karte neu.

## Verwandte Seiten

- [Unterstützte Systeme](/de/subghz/supported-systems) · [Add Manually](/de/subghz/add-manually)
- [Seed Capturer](/de/subghz/seed-capturer) · [Fernbedienung anlernen](/de/subghz/remote-prog)
- [Zählermodi](/de/subghz/counter-mode) · [Das `.sub`-Dateiformat](/de/subghz/file-format)
