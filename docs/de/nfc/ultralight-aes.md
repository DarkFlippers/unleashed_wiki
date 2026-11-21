---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** ist ein Ultralight mit gegenseitiger **AES-128**-Authentisierung anstelle eines Passworts
(NTAG21x) oder von 3DES (Ultralight C). Es hat 60 Pages, drei Einwegzähler, eine 48 Byte lange
ECC-Originalitätssignatur, einen optionalen **Random ID**-Modus und optionales **Secure Messaging** (jeder Befehl und
jede Antwort durch ein CMAC geschützt).

::: tip Unleashed
Die Unterstützung für Ultralight AES (Lesen, Wörterbuchangriff, Schlüsseleingabe von Hand, Emulation,
Zurückschreiben, Dekodierung der Konfiguration, Random ID, Secure Messaging) ist eine Unleashed-Funktion, validiert
an einer echten MF0AES20-Karte gegen die Referenzdaten eines Proxmark3.
:::

## Was der Flipper damit macht

| Funktion | Details |
|---|---|
| Erkennen und lesen | Wird als `Mifare Ultralight AES` erkannt, ATQA `0044`, SAK `00`, `60/60` Pages bei einer offenen Karte, Zähler. |
| Originalitätssignatur | Wird in der `.nfc`-Datei als Zeile `AES signature:` gespeichert (48 Byte) und bei der Emulation wiedergegeben, sodass die Signaturprüfung eines Lesegeräts besteht. |
| AES-Authentisierung | Dreistufiges AES-Challenge-Response, danach werden die geschützten Pages gelesen. |
| Wörterbuchangriff | Läuft bei einem unvollständigen Lesen automatisch: **MFUL AES User Dictionary**, dann **MFUL AES System Dictionary**. |
| Schlüssel von Hand | `Saved → <Karte> → Unlock` → **„Enter key in hex"** (16 Byte) → mit **Unlock** bestätigen. |
| Schlüsselverwaltung | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Zurückschreiben | **Write (Keep Key)** / **Write (Copy Key)** an einem vollständig gelesenen Dump. |
| Emulation | Vollständig, einschließlich AES-Authentisierung als Karte, `AUTH0`-Sperre und Secure Messaging. |
| Konfiguration dekodieren | `Info` zeigt einen Block **UL-AES Config** (siehe unten). |
| Random ID | Wird erkannt und angezeigt (`Random ID: on`); **Reveal Real UID** versucht, die echte UID zu ermitteln. |

Wörterbücher: System `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (werkseitiger Nullschlüssel,
`BREAKMEIFYOUCAN!` als AES wiederverwendet und weitere gängige Standardwerte aus Proxmark3), Benutzer
`/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. Eine Werkskarte nutzt den Nullschlüssel
`00000000000000000000000000000000` sowohl für den DataProtKey als auch für den UIDRetrKey.

## Eine geschützte Karte lesen

1. `Main Menu → NFC → Read`, Karte anhalten.
2. Die offenen Pages werden gelesen; hat die Karte einen AES-geschützten Bereich, startet der Wörterbuchangriff von
   selbst (zuerst Benutzerwörterbuch, dann System).
3. Funktioniert ein Schlüssel, werden alle Pages gelesen und der Schlüssel wird angezeigt und mit dem Dump
   gespeichert. Wenn nicht, bekommst du ein Teilergebnis (z. B. `42/60` Pages) und **„AES-protected pages!"**, ohne
   hängenzubleiben und ohne bei einer Karte ohne Limit Versuche zu verbrauchen.
4. Speichere die Karte. Später kannst du es mit **Unlock with Dictionary** (nach dem Hinzufügen von Schlüsseln) oder
   **Unlock** (Schlüssel von Hand) erneut versuchen.

::: warning Bytefolge des Schlüssels
Rohe Page-Schreibvorgänge (z. B. Proxmark3 `hf mfu wrbl`) legen den Schlüssel in der **Reihenfolge des
Tag-Speichers** ab; die AES-Engine, die Eingabe von Hand am Flipper und PM3 `hf mfu aesauth --key` nutzen die
**umgekehrte** Reihenfolge. Eine Karte, deren Pages `0x30–0x33`
`A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` lauten, authentisiert sich mit
`AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Gib einen von Hand zurückgerechneten Schlüssel **in AES-Reihenfolge** ein. In der
gespeicherten `.nfc` liegen die Schlüssel-Pages (`Page 48`–`51`) in der Reihenfolge des Tag-Speichers, damit sie
unverändert zurückgeschrieben werden können; die Zeile `DataProtKey:` auf dem Bildschirm ist nur eine Darstellung.
:::

## Speicher und Konfiguration

| Element | Ort |
|---|---|
| DataProtKey | Pages `0x30`–`0x33` |
| UIDRetrKey | Pages `0x34`–`0x37` |
| CFG | Page `0x29`: Byte 0 Bit 0 = `RID_ACT`, Bit 1 = `SEC_MSG_ACT`; Byte 3 = `AUTH0` |
| ACCESS | Page `0x2A`: Byte 0 Bit 2 = `CNT_RD_EN`, Bit 3 = `CNT_INC_EN`, Bit 6 = `CFGLCK`, Bit 7 = `PROT`; Byte 2–3 = `AUTH_LIM` |
| LOCK_KEYS | Page `0x2D`: Byte 0 = Sperrbits pro Schlüssel |

Der Block **UL-AES Config** in `Info` dekodiert diese, zum Beispiel:

- `Auth from: off (open)` oder `Auth from: page 0x10 (r+w)` / `(write)`: `AUTH0` und `PROT`;
- `Auth limit: unlimited` oder `Auth limit: N (locks!)`;
- `Counter 2: rd open / inc auth` und Ähnliches;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N`;
- `Real UID:`, sobald sie ermittelt ist.

::: danger Experimentiere nicht mit diesen Bits
`CFGLCK` sperrt die Konfiguration **dauerhaft**, `AUTH_LIM` aktiviert eine Sperre nach fehlgeschlagenen
Authentisierungen, und die `LOCK_KEYS`- bzw. statischen Lock-Bytes können die Karte zerstören. Ändere sie niemals an
einer Karte, die dir wichtig ist. Beachte außerdem, dass `hf mfu info` des PM3 die Pages `0x34`–`0x37` eines
MF0AES20 mit einer alten Ultralight-Vorlage beschriftet (`cfg0/cfg1/PWD/PACK`); verlass dich auf die Tabelle oben.
:::

## Einen Dump zurückschreiben

Wird nur an einem **vollständig gelesenen** Ultralight-AES-Dump angeboten, als zwei Einträge:

- **Write (Keep Key)**: schreibt die Daten-Pages `0x04`–`0x27`; der Schlüssel des Ziels bleibt.
- **Write (Copy Key)**: Daten-Pages plus den **DataProtKey** (`0x30`–`0x33`) aus dem Dump.

In der Firmware eingebaute Regeln:

- Der Schreibvorgang **authentisiert sich zuerst am Ziel** mit einem Wörterbuchschlüssel, der *aktuelle* Schlüssel
  des Ziels muss also in einem Wörterbuch stehen (der werkseitige Nullschlüssel steht drin).
- Konfigurations-/Lock-Pages `0x28`–`0x2F` werden **nie** geschrieben; der UIDRetrKey (`0x34`–`0x37`) wird nie
  geschrieben.
- Das Ziel muss vom gleichen **Typ** sein; die UID muss nicht übereinstimmen.

## Emulation

`Saved → <Karte> → Emulate`. Die emulierte Karte antwortet auf GET_VERSION, gibt die Signatur, die Zähler und die
Konfiguration wie die echte zurück, führt als Karte die AES-Authentisierung mit
`reverse(Pages 0x30–0x33)` als Schlüssel durch, weist falsche Schlüssel ab und setzt `AUTH0` durch. Hinweis:
eingeschränkte Lesezugriffe ohne Authentisierung liefern übergelaufene Daten früherer Pages statt eines NAK.

## Random ID

Ist `RID_ACT` gesetzt, zeigt die Karte bei jeder Auswahl eine **zufällige 4-Byte-UID, die mit `08` beginnt**; die
echte 7-Byte-UID bleibt verborgen, bis authentisiert gelesen wird. Der Flipper zeigt die zufällige UID und
`Random ID: on`. Für solche Karten hat das Menü **Reveal Real UID**: es bestätigt mit einer Warnung, liest die Karte
erneut und versucht sich zu authentisieren (standardmäßig mit dem Null-UIDRetrKey), um die statische UID
offenzulegen, angezeigt als `Real UID:` in der Konfigurationsansicht.

## Secure Messaging (CMAC)

Ist `SEC_MSG_ACT` gesetzt, muss nach der Authentisierung **jeder** Befehl und jede Antwort ein CMAC tragen. Der
Flipper behandelt das adaptiv: nach der Authentisierung scheitert das erste einfache `READ`/`WRITE` (echtes Silizium
verstummt einfach, was das Lesegerät als Timeout sieht), die Firmware authentisiert sich erneut und schaltet auf
MAC-umhülltes `READ`, `READ_CNT` und `WRITE` um. Der Befehlszähler wächst pro Austausch um 2 (der Befehl nutzt
`CmdCtr`, die Antwort `CmdCtr+1`). An Hardware validiert: ein vollständiges 60/60-Lesen über CMAC ohne
MAC-Abweichungen, Zähler über CMAC, Schlüssel-Pages `0x30`–`0x37` im Dump auf Null maskiert und ein
CMAC-Zurückschreiben der Daten-Pages.

Der Emulator spricht ebenfalls Secure Messaging: er prüft das MAC des Befehls, umhüllt jede Antwort mit einem MAC,
ersetzt das `WRITE`-ACK durch ein MAC und verwirft die Sitzung bei einem falschen MAC.

::: warning Umkehrbarkeit
Ist `SEC_MSG_ACT` einmal an, brauchen Konfigurationsschreibvorgänge in einem geschützten Bereich einen
CMAC-authentisierten Schreibzugriff, den der Proxmark3 nicht kann und den das Write des Flippers überspringt
(Konfigurations-Pages werden nie geschrieben). Setze `AUTH0 ≤ 0x29` nicht an einer Karte mit Secure Messaging, sonst
kannst du es möglicherweise nicht mehr abschalten.
:::

### Debug-Markierungen

Mit `Settings → System → Log Level → Debug` kannst du im Protokoll verfolgen, was passiert, zum Beispiel
`UL-AES: plain read failed post-auth, switching to secure messaging`, `UL-AES response MAC mismatch (ctr N)` (sollte
in einem gesunden Durchlauf nicht erscheinen), `UL-AES command MAC mismatch, dropping session` (auf Emulatorseite).

## Verwandte Seiten

[Karten entsperren](/de/nfc/unlock-with-password) · [Karten lesen](/de/nfc/read) · [NFC-Dateiformat](/de/nfc/file-format) ·
[Karten manuell anlegen](/de/nfc/add-manually)
