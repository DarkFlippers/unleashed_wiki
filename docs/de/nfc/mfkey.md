---
title: "MFKey32: Schlüssel vom Lesegerät"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: Schlüssel von einem Lesegerät zurückrechnen

**MFKey32** ist ein Angriff auf die Crypto-1-Verschlüsselung von MIFARE Classic. Der Flipper gibt sich als Karte
aus; das Lesegerät versucht, sich mit seinem echten Schlüssel zu authentisieren, und die zwei Nonce-/Antwort-Paare,
die es sendet, genügen, um diesen Schlüssel offline zu berechnen. Der Angriff braucht also **Zugang zum Lesegerät**,
nicht zu den Schlüsseln.

Nimm ihn, wenn:

- die Karte nur teilweise gelesen wird und die fehlenden Schlüssel die sind, die das Lesegerät nutzt (der häufigste
  Fall);
- du überhaupt keine Karte hast, aber die Schlüssel eines Lesegeräts erfahren und in dein Wörterbuch aufnehmen
  willst;
- die Karte keine Backdoor und keinen bekannten Schlüssel hat, sodass [Nested-Angriffe](/de/nfc/nested-fudan) nicht
  anlaufen können.

## Mit Karte und Lesegerät (empfohlen)

Hast du die Karte, kannst du nach dem Zurückrechnen der Schlüssel des Lesegeräts mehr Sektoren lesen — und das sind
üblicherweise genau die, die das Lesegerät tatsächlich prüft.

1. Lies die Karte (`Main Menu → NFC → Read`). Sie wird nur teilweise gelesen.
2. Wähle in **More** den Punkt **Extract MFC Keys**. Der Flipper fragt *„Save the Key?"*: **Save** (du brauchst den
   Dump später) oder **Skip**.
   *Alternativ* öffne eine bereits gespeicherte Karte: `Main Menu → NFC → Saved → <Karte> → Extract MFC Keys`.
3. Der Bildschirm zeigt **„Emulating... MIFARE MFkey32"** mit der UID der Karte und *„Touch the reader"*.

   ![Emulating MIFARE MFkey32 mit der UID der Karte und der Aufforderung, das Lesegerät zu berühren](/screens/nfc/mfkey_start.png)

4. Berühre das Lesegerät mit der Rückseite des Flippers, zieh ihn weg (*„Move the Flipper away"*) und berühre es
   erneut (*„Touch the reader again"*). Der Zähler **Nonce pairs: X/10** wächst mit jedem erfolgreichen Versuch.

   ![Nonce-Paare werden gesammelt: 4 von 10 gesammelt, Aufforderung, den Flipper wegzuziehen](/screens/nfc/mfkey_collecting.png)

5. Sind 10 Paare gesammelt, zeigt der Bildschirm **Completed!**. Du kannst mit <kbd>OK</kbd> **Done** vorher
   abbrechen.
6. Der nächste Bildschirm führt **Nonce pairs saved: N** und die **Authenticated sectors** auf (welchen Sektor und
   welchen Schlüsseltyp das Lesegerät verlangt hat). Drücke <kbd>OK</kbd>.

   ![Nonce pairs saved: 5, mit der Liste der authentisierten Sektoren und Schlüsseltypen](/screens/nfc/mfkey_nonces_info.png)

7. Der Flipper bietet an, die Schlüssel zurückzurechnen: **„Now run Mfkey32 to extract keys"** mit **Run** (öffnet
   die [MFKey-App](/de/nfc/mfkey-app)). Fehlt die App, zeigt er einen QR-Code auf `r.flipper.net/nfc-tools` und
   **Finish**.
8. Rechne die Schlüssel mit einem der Werkzeuge unten zurück. Sie werden ins Benutzerwörterbuch aufgenommen.
9. Lies die Karte erneut (oder `Saved → <Karte> → Unlock with Dictionary`). Jetzt sollten mehr Schlüssel und
   Sektoren gefunden werden.
10. Emuliere die Karte oder schreibe sie.

Die Nonces liegen in `/ext/nfc/.mfkey32.log`, eine Zeile pro Paar:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Der Zähler wächst nicht?
Das Lesegerät versucht nicht, die emulierte Karte zu authentisieren. Manche Lesegeräte prüfen nur die UID oder
nutzen ein anderes Protokoll; andere weisen die Emulation von vornherein ab. Probiere verschiedene Abstände und
Winkel; manchmal braucht es mehrere Berührungen für ein Paar.
:::

## Nur das Lesegerät

1. Geh zu `Main Menu → NFC → Extract MFC Keys`. Der Flipper emuliert eine generische MIFARE-Classic-Karte.
2. Schritt 3–8 wie oben.
3. Die zurückgerechneten Schlüssel stehen im Benutzerwörterbuch und werden automatisch probiert, wenn du später
   Karten dieses Systems liest.

## Die Schlüssel aus den Nonces zurückrechnen

| Werkzeug | Wo | Hinweise |
|---|---|---|
| **MFKey-App** auf dem Flipper | `Main Menu → Apps → NFC → MFKey` | Kein Telefon / PC nötig. Verarbeitet `.mfkey32.log` und `.nested.log`. Langsamer. Siehe [MFKey-App](/de/nfc/mfkey-app). |
| **qUnleashed** (Begleit-App von Unleashed) | `Tools → Recover MIFARE Keys` | Verarbeitet `.mfkey32.log` und `.nested.log`, auch harte und static encrypted Nonces. Schnell. Siehe [qUnleashed](/de/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Offizielle App, nur Lesegerät-Nonces. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Über USB im Browser. |

::: tip Unleashed
In Unleashed heißt der Menüpunkt **Extract MFC Keys** (Stock: *Extract MF Keys*), und die Begleit-App
**qUnleashed** kann die Schlüssel direkt auf deinem Telefon oder Rechner zurückrechnen. Seit **MFKey 4.x**
(Unleashed-Dev-Build 1251+) ist die Rückrechnung auf dem Flipper selbst mehrfach schneller, siehe
[MFKey-App](/de/nfc/mfkey-app).
:::

## Wenn die Rückrechnung scheitert

- **Aus den Nonces werden keine Schlüssel gefunden**: das Lesegerät hat die Emulation des Flippers nicht richtig
  akzeptiert. Sammle neu und probiere einen anderen Kartendump (eine gespeicherte echte Karte funktioniert besser
  als eine generische Emulation).
- **MFKey zeigt „No nonces found"**: es existiert weder `.mfkey32.log` noch `.nested.log`.
- **MFKey hängt oder stürzt ab**: starte neu (<kbd>←</kbd> + <kbd>Back</kbd> 5 Sekunden halten), lösche
  `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log` und sammle neu.
- **Letzter Ausweg**: sichere `/ext/nfc/assets/mf_classic_dict_user.nfc` und lösche sie (das entfernt **alle** deine
  eigenen Schlüssel).

## Verwandte Seiten

[MIFARE Classic](/de/nfc/mifare-classic) · [Nested-Angriffe](/de/nfc/nested-fudan) · [MFKey-App](/de/nfc/mfkey-app) ·
[qUnleashed](/de/nfc/qunleashed)
