---
title: Schnelle Schlüsselsuche mit qUnleashed
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Schnelle Rückrechnung von MIFARE-Classic-Schlüsseln mit qUnleashed

Eine Anleitung aus der Praxis von **@gromovyna**: MIFARE-Classic-Schlüssel schnell zurückrechnen, mit Unleashed und
seiner Begleit-App **qUnleashed** (entwickelt und gepflegt vom Unleashed-Team; großen Dank an
[apfxtech](https://github.com/apfxtech), den ursprünglichen Autor der App). Es ist die Fortsetzung von
[Nested-Angriffe und Fudan-Backdoors](/de/nfc/nested-fudan); diese Seite vorher zu lesen ist empfehlenswert, aber
nicht nötig.

Die Rückrechnung deckt **alle Angriffe und Nonce-Typen** ab, die zum Zeitpunkt des Schreibens bekannt sind: *weak,
hard, static, static encrypted*. Anders als bei der [MFKey-App](/de/nfc/mfkey-app) läuft die schwere Rechenarbeit
auf deinem Telefon oder Rechner, es dauert also meist **Minuten**, nicht Stunden.

::: warning Du brauchst den Tag in der Hand
Der Tag muss für das abschließende Lesen physisch vorhanden sein. „Ich habe für einen Freund einen Dump gemacht und
der Tag ist weg" funktioniert nicht.
:::

## Versionen

Die Funktionalität gibt es möglicherweise auch in etwas älteren Versionen, aber getestet wurde mit diesen:

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

Siehe auch [Die qUnleashed-App](/de/mobile/qunleashed-app) zur Installation und zu weiteren Funktionen.

## Was du brauchst

Einen **MIFARE Classic**-Tag (oder **MIFARE Plus in SL1**, nur SL1) mit **mindestens einem bekannten Schlüssel oder
einer Backdoor**.

![Ein Tag mit einem unbekannten Schlüssel](/img/remote/286db70e86cfa835.png)

![Ein Tag mit Backdoor: Schlüssel unbekannt, Sektoren aber über die Backdoor gelesen](/img/remote/59bd4aa5ae1242c1.png)

Hat dein Tag keine Backdoor und nicht einen bekannten Schlüssel, hol dir zuerst einen mit
[MFKey32](/de/nfc/mfkey) vom Lesegerät. qUnleashed kann Schlüssel auch aus Lesegerät-Nonces zurückrechnen (siehe
Schritt 2).

## Schritt 1. Nonces sammeln

1. Vor dem Angriff ist es eine gute Idee, `/ext/nfc/.nested.log` zu löschen, falls du eine hast (`/ext/` ist die
   SD-Karte). Nach der Rückrechnung ist es ebenfalls sinnvoll, sie zu löschen, damit sie nicht wächst und Unordnung
   schafft. Für qUnleashed ist das nicht entscheidend, aber gute Praxis.
2. Lies den Tag: `Main Menu → NFC → Read`. Warte, während die Phasen laufen; welche erscheinen, hängt vom
   Nonce-Typ des Tags ab: **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**, **Calibration**,
   **Nonce Collection**.

   ![Nonce Collection](/img/remote/786d77b7b65b3fd0.png)

3. Erscheinen die Tag-Informationen, **speichere den unvollständigen Dump**: du brauchst ihn später.
4. Prüfe optional in qUnleashed, dass die Nonces da sind: verbinde den Flipper, öffne `Archive → External → nfc`,
   aktiviere versteckte Dateien (das „Burger"- bzw. Drei-Punkte-Menü oben rechts) und such nach `.nested.log`.

   ![.nested.log in qUnleashed](/img/remote/c4c534fbe93faa8a.png)

## Schritt 2. Die Schlüssel zurückrechnen

Alles passiert in **qUnleashed**; der Flipper muss die ganze Zeit verbunden bleiben (Bluetooth oder Kabel).

1. Öffne `Tools → Recover MIFARE Keys`.

   ![Der Menüeintrag](/img/remote/1a255b9128f988ab.png)

2. Warte, bis die Rückrechnung fertig ist.

   ![Schlüssel werden zurückgerechnet](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Hab Geduld
   Es kann eine Weile dauern, je nach Größe von `.nested.log`, den Nonce-Typen, der Leistung des Geräts, auf dem
   qUnleashed läuft, und so weiter. Meist sind es Minuten. Warte, bis der Vorgang abgeschlossen ist. Static
   encrypted Nonces dauern am längsten.
   :::

3. Schau dir das Ergebnis an. Die Rückrechnungsphase arbeitet mit **`.mfkey32.log`** (Lesegerät-Nonces) und
   **`.nested.log`** (Tag-Nonces). Der Bildschirm zeigt, woher jeder Schlüssel kam, wie viele ins
   Benutzerwörterbuch oder ins Kandidatenwörterbuch aufgenommen wurden und so weiter.

   ![Ergebnis der Rückrechnung](/img/remote/1c5f56614caf4530.png)

Wohin die Schlüssel gehen, hängt vom Nonce-Typ ab:

| Nonces | Ergebnis |
|---|---|
| weak, hard, static | Die Schlüssel werden ins **Benutzerwörterbuch** `/ext/nfc/assets/mf_classic_dict_user.nfc` aufgenommen. |
| static encrypted | Der Schlüssel lässt sich in dieser Phase nicht exakt berechnen, deshalb wird ein **Kandidatenwörterbuch** (auch **CUID-Wörterbuch**) aufgebaut: `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, wobei `{UID}` die ID deines Tags ist. Es kann groß sein: im Beispiel des Autors waren es für einen Tag mehr als **1,2 Millionen Kandidaten**. |

## Schritt 3. Den Tag erneut lesen

Lege den Tag auf den Flipper und geh entweder zu `NFC → Read` oder öffne den gespeicherten unvollständigen Dump und
wähle **Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

Gibt es ein **CUID-Wörterbuch**, wird es zuerst geladen. Das Kandidatenwörterbuch ist groß, das dauert also, und du
siehst einen Fortschrittsbalken (*„CUID dictionary is loading"*). **Minuten** ist hier die realistische Ladezeit.

![Ladebildschirm, Dev-Build 1437+](/img/remote/47427c58e2a34889.png)

::: tip Update 22.09.2026
In frühen Firmware-Versionen zeigte dieser Moment nur einen leeren Bildschirm, was viele Nutzer verwirrt hat. Ab
Dev-Build **1437** (und Release **094**) hat der Bildschirm einen Fortschrittsbalken.
:::

Dann läuft der Wörterbuchangriff mit den zurückgerechneten Schlüsseln.

![Wörterbuchangriff](/img/remote/f77ef58bda94b088.png)

Auch hier gilt für **static encrypted Nonces (CUID-Wörterbuch)**: lass den Flipper während der Suche auf dem Tag
liegen und geh einen Tee kochen.

Sind alle Schlüssel gefunden, kannst du den gespeicherten Teildump zu einem vollständigen aktualisieren oder ihn
unter einem neuen Namen speichern.

![Vollständig gelesener Tag](/img/remote/9f9745d0d2ee0a4a.png)

Jetzt stehen alle Möglichkeiten offen: Emulation, Schreiben auf Rohlinge, Weitergeben an einen Freund usw.

::: warning Bevor du auf einen Rohling schreibst
Kenne die Unterschiede zwischen Rohlingen und wie Lesegeräte sie filtern können: siehe
[Magic Cards](/de/nfc/magic-cards).
:::

## Optional: die Schlüssel eines Static-Encrypted-Tags ins Benutzerwörterbuch speichern

Aufgrund der Funktionsweise des Angriffs liegen Schlüssel, die aus dem Kandidatenwörterbuch zurückgerechnet wurden,
**nur in diesem Wörterbuch und im Dump des Tags**. Das ist ein Problem, wenn du einen Rohling beschreiben und ihn
später löschen willst: [NFC Magic](/de/nfc/nfc-magic) arbeitet nur mit dem Schlüsselcache und dem Benutzer- bzw.
Systemwörterbuch.

Deshalb hat das Team das automatische Speichern von Schlüsseln mit Duplikatsprüfung in die Firmware eingebaut. Öffne
das Menü des gespeicherten Dumps (mindestens ein Schlüssel muss bekannt sein) und wähle
**Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

Der Flipper zeigt *„Saving keys to user dictionary"* und dann *„New keys: N, Already known: M"*.

## Alternativen

Für die Rückrechnung gibt es außerdem ein [CLI-Projekt](https://github.com/phntm-lab/mfkey_desktop_cli). In
manchen Punkten ist es schneller, aber CLI ist etwas für Hardcore-Geeks. Für den Alltag bevorzugt der Autor die
bequeme Begleit-App, besonders angesichts der vielen anderen nützlichen Funktionen, die sie hat. Nur mit dem
Flipper nimm die [MFKey-App](/de/nfc/mfkey-app).

Der Ablauf wirkt zunächst vielleicht etwas kompliziert, nach etwas Übung wird er aber zur Routine.

## Verwandte Seiten

[Nested-Angriffe](/de/nfc/nested-fudan) · [MFKey32](/de/nfc/mfkey) · [MFKey-App](/de/nfc/mfkey-app) ·
[MIFARE Classic](/de/nfc/mifare-classic) · [Magic Cards](/de/nfc/magic-cards) · [Die qUnleashed-App](/de/mobile/qunleashed-app)
