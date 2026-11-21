---
title: Karten mit Passwort entsperren
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Karten mit Passwörtern und Schlüsseln entsperren

Karten, die in **Pages** organisiert sind (MIFARE Ultralight, NTAG), können einen Teil ihres Speichers schützen.
Zeigt `Read` **„Some Pages Are Locked!"** / **„Password-protected pages!"** und `Pages Read: X/Y` mit X < Y, braucht
die Karte ein Passwort oder einen Schlüssel. Je nach Karte:

| Karte | Schutz | Wie der Flipper sie entsperrt |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | 4 Byte Passwort (PWD) + 2 Byte PACK | vom Lesegerät mitschneiden, aus der UID erzeugen (amiibo, Xiaomi) oder von Hand eingeben |
| Ultralight C | 16 Byte 3DES-Schlüssel | Wörterbuchangriff (automatisch) oder Schlüssel von Hand eingeben |
| Ultralight AES | 16 Byte AES-Schlüssel | Wörterbuchangriff (automatisch) oder Schlüssel von Hand eingeben, siehe [Ultralight AES](/de/nfc/ultralight-aes) |
| ICODE SLIX-L | 4 Byte Passwort | `Extra Actions → Unlock SLIX-L` |

::: danger Falsche Passwörter können die Karte sperren
Viele Karten zählen fehlgeschlagene Authentisierungen (`AUTHLIM`) und sperren sich nach zu vielen dauerhaft selbst.
Der Flipper warnt mit **„Risky action! Wrong password can block your card."**, bevor er ein Passwort probiert.
Probiere nicht per Brute Force.
:::

## Das Passwort vom Lesegerät mitschneiden

Hast du die Karte und das Lesegerät, das sie akzeptiert: emuliere die Karte, lass das Lesegerät sein Passwort
senden, schneide es mit und lies die Karte dann damit.

1. [Lies und speichere](/de/nfc/read) die Karte.
2. Geh zu `Main Menu → NFC → Saved → <Karte> → Unlock`.
3. Wähle **Unlock With Reader**. Auf dem Bildschirm steht *„Touch the reader to get password..."*. Berühre das
   Lesegerät mit dem Flipper.
4. Ist das Passwort mitgeschnitten, siehst du **Password Captured!** samt Wert. Drücke **Continue**.
5. Halte die Karte an die Rückseite des Flippers (*„Hold card next to Flipper's back"*, dann *„Don't move"*).
6. Sind die Pages entsperrt (**„All Pages Are Unlocked!"**), geh zu **More → Save**, benenne die Karte und speichere
   sie.

Wird nichts mitgeschnitten (*„Password not captured."*), nutzt das Lesegerät vielleicht kein Passwort, oder die Karte
gehört zu einem anderen Lesegerät.

`Unlock With Reader` wird für Ultralight C nicht angeboten (sie nutzt gegenseitige 3DES-Authentisierung, es wird kein
Passwort im Klartext gesendet).

## Das Passwort aus der UID erzeugen

Bei **Toys-to-Life**-Figuren (NTAG215 im amiibo-Stil) und Filtern von **Xiaomi Air Purifier** wird das Passwort aus
der UID der Karte abgeleitet.

1. Geh zu `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (oder, bei einer gespeicherten Karte, `Saved → <Karte> → Unlock`).
2. Wähle **Auth As Ameebo** oder **Auth As Xiaomi Air Purifier**.
3. Bestätige die Warnung und halte die Karte an den Flipper.
4. Sind die Pages entsperrt, **Save** die Karte.

## Das Passwort von Hand eingeben

1. `Main Menu → NFC → Saved → <Karte> → Unlock` (oder `Extra Actions → Unlock NTAG/Ultralight` vor dem Lesen).
2. Wähle **Enter Password Manually**.
3. **„Enter the password in hex"**: die 4 Byte eingeben, bestätigen.
4. Bestätige die Warnung *„Try to unlock the card with password: …"* und halte die Karte an den Flipper.
5. **Save** die entsperrte Karte.

## Ultralight C: 3DES-Schlüssel

Ultralight-C-Karten nutzen einen 16 Byte langen 3DES-Schlüssel. Der Flipper hat ein eingebautes Wörterbuch bekannter
Schlüssel (`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 Schlüssel, darunter den NXP-Beispielschlüssel
`BREAKMEIFYOUCAN!`) und ein Benutzerwörterbuch (`mf_ultralight_c_dict_user.nfc`).

- Ist die Karte bei `Read` nicht vollständig lesbar, läuft der Wörterbuchangriff von selbst: Kopfzeilen
  **„MFUL C User Dictionary"**, dann **„MFUL C System Dictionary"**, mit `Key found: Yes/No` und
  `Pages read: X/Y`.
- Bei einer gespeicherten, unvollständigen Karte: **Unlock with Dictionary** führt den Angriff erneut aus;
  **Unlock** fragt **„Enter key in hex"** (16 Byte) und dann **„Risky Action! Unlock with key: … ?"** mit
  **Unlock** / **Cancel**.
- Eigene Schlüssel ergänzen: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Ein vollständig gelesener Ultralight-C-Dump bietet **Write (Keep Key)** (behält den 3DES-Schlüssel der Zielkarte) und
**Write (Copy Key)** (schreibt auch die Schlüssel-Pages aus dem Dump) auf eine Karte desselben Typs.

::: tip Unleashed
Die Eingabe von 3DES-/AES-Schlüsseln von Hand, das Zurückschreiben von Ultralight C/AES mit Keep/Copy Key und das
Ultralight-AES-Wörterbuch (`Extra Actions → MIFARE UL AES Keys`) sind Unleashed-Funktionen.
:::

## ICODE SLIX-L

1. Geh zu `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Wähle **Enter Password Manually** (4 Byte in Hex) oder **Auth As TommyBox** (das bekannte Passwort von
   TommyBox-Tags).
3. Halte den Tag an den Flipper (*„Unlocking — Hold card next to Flipper's back"*).
4. Drücke bei **SLIX Unlocked!** auf **More**, um zum Leseergebnis weiterzugehen und es zu speichern, oder auf
   **Retry**.

## Wenn das Entsperren gescheitert ist

- Die Karte ist vielleicht mit einem anderen Lesegerät gepaart oder nutzt einen pro Karte abgeleiteten Schlüssel.
- Das Passwort ist richtig, aber manche Pages bleiben gesperrt: Lock-Bits oder die Einstellungen `AUTH0`/`PROT`
  können Pages dauerhaft nur lesbar oder ohne Authentisierung unlesbar machen.
- Zu Ultralight AES siehe den Hinweis zur Bytefolge auf [Ultralight AES](/de/nfc/ultralight-aes).

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [Ultralight AES](/de/nfc/ultralight-aes) · [Vizit Leser-Filter](/de/nfc/vizit-filters) ·
[NFC-Dateiformat](/de/nfc/file-format)
