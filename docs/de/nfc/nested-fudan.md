---
title: Nested-Angriffe und Fudan-Backdoors
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Nested-Angriffe und Fudan-Backdoors

Eine praktische „Was drücke ich"-Anleitung von **@gromovyna** zu den Angriffen auf MIFARE Classic, die nur die Karte
brauchen und in `NFC → Read` eingebaut sind. Sie kamen mit der offiziellen Firmware **1.1.2** (Arbeit von
[@noproto](https://github.com/noproto)) und sind Teil von Unleashed. Während sie entwickelt wurden, machte ein
Forscher aus der Community zwei wichtige Entdeckungen: einen Angriff auf **static encrypted Nonces** und
**Backdoor-Schlüssel** in Chips von **Fudan** (und anderen), mit denen sich die Sektoren eines
MIFARE-Classic-Tags lesen lassen, ohne seine Schlüssel zu kennen. Beides fand seinen Weg in die Firmware und in
**MFKey 3** (heute [MFKey 4.1](/de/nfc/mfkey-app)). Das Forschungspapier:
[eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Schnellerer Weg (Stand September 2026)
Willst du MIFARE-Classic-Schlüssel einfach nur schnell zurückrechnen, nimm die Begleit-App **qUnleashed**, die all
diese Angriffe — auch HardNested — auf deinem Telefon oder PC ausführt: siehe
[Schnelle Schlüsselsuche mit qUnleashed](/de/nfc/qunleashed).
:::

## Die Idee in Kurzform

**Nested-Angriffe** sind *card-only*-Angriffe (kein Lesegerät nötig): kennt man mindestens einen Schlüssel einer
Karte, rechnen sie die unbekannten zurück. Begrifflich fallen Tags in vier Gruppen (streng genommen gibt es Nested
und HardNested, aber diese Aufteilung ist leichter zu verstehen):

| Tag ist anfällig für | Nonce-Typ | Wo der Schlüssel berechnet wird |
|---|---|---|
| **Nested** | schwacher PRNG | MFKey auf dem Flipper, qUnleashed |
| **HardNested** | harter PRNG | qUnleashed oder ein PC (nicht auf dem Flipper) |
| **Static Nested** | statische Nonce | MFKey auf dem Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | static encrypted Nonce | MFKey auf dem Flipper (am langsamsten), qUnleashed |

**Backdoor-Schlüssel** sind Schlüssel, die die Daten eines Tags **ohne** seine echten Schlüssel öffnen.

Für die Beispiele nutzte der Autor Tags jedes Typs, mit Sektor 0 verschlüsselt durch ein erzeugtes Schlüsselpaar:
Key A `A3F92C8E7D3A`, Key B `4F6D91C5BA7E` (Access Bits auf Standard gelassen). Auf einem Proxmark3 zeigte die
Prüfung der Standardschlüssel diese Schlüssel als unbekannt:

![Prüfung der Standardschlüssel auf dem Proxmark3](/img/remote/86130b06142278a1.png)

## Schritt 1. Den Tag lesen

Geh zu `Main Menu → NFC → Read` und halte den Tag still.

### 1.1 Der Tag hat eine Backdoor

Du siehst Bildschirme mit **Backdoor Read** und danach einige weitere mit **(Backdoor)** in der Kopfzeile:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Lesen über die Backdoor](/img/remote/e9be977d84486794.png)

Das bedeutet, der Chip hat eine Backdoor: der Flipper liest die Sektordaten darüber und sammelt Nonces, damit die
Schlüssel zurückgerechnet werden können. Das typische Ergebnis ist **alle Sektoren gelesen, aber weniger Schlüssel
als nötig**:

![Alle Sektoren, aber nur 30 Schlüssel](/img/remote/9e7db33e51594779.png)

### 1.2 Der Tag hat keine Backdoor

Dann läuft die klassische Schlüsselsuche: zuerst das **Benutzer**-, dann das **System**-Wörterbuch.

![Benutzerwörterbuch](/img/remote/fff8f5662df941b9.png)

![Systemwörterbuch](/img/remote/0da64f609fc2c770.png)

Wurde mindestens ein Schlüssel gefunden, wechselt der Flipper zur **PRNG Analysis** und geht dann das
**Nested Dictionary** durch:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

danach **Calibration** und **Nonce Collection**:

![Calibration und Nonce Collection](/img/remote/f5b036a96f5a0869.png)

Ist der Tag **nur für HardNested** anfällig, dauert das Sammeln der Nonces länger und die Kopfzeile bekommt den
Zusatz **(Hard)**:

![Nonce Collection bei einem Tag mit hartem PRNG](/img/remote/fca9f1b2e4475631.png)

> In diesem Fall geh direkt zu [Punkt 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Hier sieht das Ergebnis vertrauter aus: die Zahl der gefundenen Schlüssel liegt nah an der Zahl der gelesenen
Sektoren (je nach Access Bits).

![Ergebnis nach der Nested-Phase](/img/remote/d15656101dfafcc4.png)

Alle gesammelten Nonces werden an `/ext/nfc/.nested.log` angehängt.

## Schritt 2. Die Schlüssel zurückrechnen

Geh zu `Main Menu → Apps → NFC → MFKey`.

::: warning Prüfe die Version der App
Stelle sicher, dass die MFKey-App die zu deiner Firmware passende ist und nicht von einer alten Kopie überschrieben
wurde, falls du Apps separat installiert hast. Unleashed liefert **MFKey 4.1** mit.
:::

![Startbildschirm von MFKey](/img/remote/195a1b6a411e7bf3.png)

Drücke <kbd>OK</kbd> **Start** und …

### 2.1 Der Tag ist anfällig für Nested, Static Nested oder Static Encrypted Nested

Das Knacken beginnt. Du kannst den Flipper in Ruhe lassen und etwas anderes tun:

![Das Knacken läuft](/img/remote/a514db67a986ae2c.png)

Es bleibt nur zu warten. Auf der Hardware des Flippers ist das nicht schnell (hallo, SPI) und hängt ab von:

- der Angriffsart: Nested < Static Nested < Static Encrypted Nested (SEN ist am langsamsten);
- der Anzahl unbekannter Schlüssel (weniger ist schneller);
- davon, wie einmalig die Schlüssel sind: ein überall wiederverwendeter Schlüssel wird schneller gefunden als bei
  einem teilweise diversifizierten Tag (z. B. Iron Logic), der wiederum schneller ist als ein vollständig
  diversifizierter Tag (z. B. Filamentspulen von Bambu Lab).

Die Oberfläche reagiert nicht immer und „denkt" manchmal. Gelegentlich kann der Flipper wie eingefroren aussehen;
starte ihn nicht gleich neu. Die Zeile **RAM** oben verändert sich weiter, solange die Arbeit läuft.

::: warning Static encrypted Nonces
Bei static encrypted Nonces werden die Nonces aufgrund der Funktionsweise des Angriffs nicht als „gelöst" markiert;
MFKey baut nur **Kandidaten** (Schlüssel, die später am Tag geprüft werden müssen), und die App kann beim letzten
(oder einem früheren) Schritt festzuhängen scheinen. Ist genug Zeit vergangen, beende sie und prüfe das Ergebnis
(Schritt 3). Seit MFKey 4.x werden die Kandidaten in ein **CUID-Wörterbuch** pro Karte gespeichert,
`/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, das `Read` zuerst probiert.
:::

Ist die Entschlüsselung fertig, bekommst du eine Zusammenfassung mit der Zahl der ins Benutzerwörterbuch
aufgenommenen Schlüssel (**Keys added to user dict: N**, und bei SEN-Tags **SEN key candidates: N**):

![MFKey fertig](/img/remote/c9ef77139b74cc89.png)

Mach weiter mit Schritt 3.

### 2.2 Der Tag ist anfällig für HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

Das konntest du am Bildschirm **(Hard)** während des Nonce-Sammelns erkennen, oder MFKey zeigt einen Fehler, dass
keine Nonces gefunden wurden:

![MFKey: no nonces found](/img/remote/2519c7dce0b881c9.png)

HardNested ist der einzige Angriff, der sich nicht auf dem Flipper ausführen lässt. Möglichkeiten:

- **qUnleashed** (empfohlen, Telefon oder PC): `Tools → Recover MIFARE Keys`, siehe
  [qUnleashed](/de/nfc/qunleashed). Die Schlüssel landen direkt im Benutzerwörterbuch.
- **Ein PC mit HardnestedRecovery**, wie in der ursprünglichen Anleitung:
  1. Kopiere `/ext/nfc/.nested.log` von der SD-Karte des Flippers auf den Rechner.
  2. Klone und baue [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) mit
     `make build` (nutze unter Windows WSL oder Docker).
  3. Starte es mit dem Protokoll als Argument:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. Der Schlüssel erscheint in der Ausgabe:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Füge die Schlüssel von Hand hinzu
Anders als in 2.1 werden Schlüssel, die HardnestedRecovery an einem PC gefunden hat, **nicht** automatisch
aufgenommen. Füge sie selbst ins Benutzerwörterbuch ein:
`NFC → Extra Actions → MIFARE Classic Keys → Add`, oder hänge sie an
`/ext/nfc/assets/mf_classic_dict_user.nfc` an.
:::

## Schritt 3. Den Tag erneut lesen

Sind die Schlüssel zurückgerechnet, lies den Tag erneut über `NFC → Read`.

::: tip Profitipp
Hast du den Tag nach dem ersten Lesen gespeichert, kannst du ihn direkt aus dem Menü der gespeicherten Karte
entsperren: `Saved → <Karte> → Unlock with Dictionary`.
:::

![Unlock with Dictionary aus einer gespeicherten Karte](/img/remote/8232d690446c70b6.png)

::: tip Profitipp
Für bessere Leistung beim nächsten Mal: räume `/ext/nfc/.nested.log` auf, sobald du die Schlüssel eines Tags
geknackt hast.
:::

## Verwandte Seiten

[MIFARE Classic](/de/nfc/mifare-classic) · [MFKey-App](/de/nfc/mfkey-app) · [qUnleashed](/de/nfc/qunleashed) ·
[MFKey32](/de/nfc/mfkey) · [Iron Logic Lesegeräte](/de/nfc/iron-logic) · weitere Artikel im Kanal des Autors
[@gromovyna](https://t.me/gromovyna)
