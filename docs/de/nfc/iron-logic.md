---
title: Iron Logic Lesegeräte
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Iron Logic Lesegeräte (CP-Z-2 „3 Streifen" / „4 Streifen")

Iron-Logic-Lesegeräte („Stöpsel") sind in Türsprechanlagen und Zutrittssystemen in der ganzen Ex-UdSSR verbreitet. Diese Seite erklärt, wie sie MIFARE-Classic-Anhänger schützen, wie du erkennst, welche Variante du vor dir hast, und was die veröffentlichte Forschung zum Lesen, Emulieren und Kopieren **deines eigenen** Anhängers mit einem Flipper Zero sagt.

::: tip Geltungsbereich
Nur für deine eigenen Ausweise und für rechtmäßige Forschung. Nach dem Artikel von @gromovyna (13.03.2025).
:::

## Wie sich diese Systeme gegen Klonen wehren

Iron Logic setzt auf das günstige MIFARE Classic und legt Schutzschichten darüber:

- **Schlüsseldiversifizierung.** Die Sektorschlüssel werden pro Karte aus der Karten-UID und der „Objektkarte" des Lesegeräts abgeleitet (eine Konstante, die in das Lesegerät geladen wird). Ein Wörterbuchangriff findet in einem konfigurierten System deshalb meist nichts.
- **Filter** gegen Magic Cards und Emulatoren (zum Beispiel „nur IL-30", OTP1, OTP2), je nach Firmware des Lesegeräts.
- **Dynamischer Modus** („nur der erste", siehe [Iron Logic dynamische Anlernung](/de/nfc/iron-logic-enrollment)), in dem sich die Daten auf der Karte bei jedem Durchgang ändern.

Wer das versteht, weiß auch, warum ein einfaches „lesen, dann auf einen Rohling schreiben" oft scheitert — und was stattdessen zu tun ist.

## Welches Lesegerät hast du

| Variante | Hinweise |
|---|---|
| CP-Z-2 („3 Streifen") | Älter, abgekündigt, immer noch verbreitet. |
| CP-Z-2 (mod. MF-I) („4 Streifen") | Aktuelles Modell, von Firmware-Releases unterstützt. Der Artikel ist für dieses geschrieben, funktioniert aber auch für das ältere. |

Die Erkennung am Gehäuse ist nicht 100 % zuverlässig (ein Monteur kann neue Elektronik in ein altes Gehäuse setzen), funktioniert in der Praxis aber fast immer. Die Lesegeräte stecken auch in Panels anderer Hersteller (Eltis, Metakom und andere); das ist unwichtig, denn das Ziel ist, alle Sektoren der MIFARE-Classic-Karte zu bekommen.

## Prüfe, ob du Pech hast

### SmartMX-Karte (IL-30)

Wird ein „4 Streifen"-Lesegerät genutzt und zeigt der Flipper den Bildschirm im Stil „unsupported card", prüfe die Karte: **SAK = 28** und **ATQA = 0004** bedeutet eine **SmartMX**-Karte, und im Lesegerät ist möglicherweise der Filter **„nur IL-30"** aktiv. Du kannst die Schritte unten trotzdem versuchen, für den Fall, dass der Filter aus ist und das Lesegerät im Mischmodus läuft (neue SmartMX- und alte MIFARE-Classic-Schlüssel). Klappt nichts und du brauchst eine Kopie, empfiehlt der Autor eine Werkstatt mit iKey-Geräten, die die Daten über einen Logikfehler in Iron Logic auf Originalchips (iMF+) schreiben.

### Dynamische Türsprechanlagen („Sokol" von Petrunja)

Sokol-Anlagen (meist auf einem Eltis-5000-Panel aufgebaut) nutzen Iron-Logic-Lesegeräte **mit Dynamik**: die Daten im Schlüssel ändern sich bei jedem Durchgang, und alte Kopien werden ungültig. Emulieren oder einen Rohling beschreiben kann **dein Original beschädigen**. Details: [dynamische Anlernung](/de/nfc/iron-logic-enrollment).

## Schritt 1: alle Sektoren dumpen

Du brauchst alle Sektoren und alle Schlüssel der Karte. Warte nicht, bis der Wörterbuchangriff durchgelaufen ist: bei diversifizierten Schlüsseln ist er sinnlos.

1. Lies die Karte (`Main Menu → NFC → Read`). Siehe [Karten lesen](/de/nfc/read).
2. Lautet das Ergebnis **16/16 Sektoren gelesen, aber 0/32 Schlüssel gefunden**, hat die Karte eine Backdoor. Geh direkt zur [Anleitung zu Nested / Fudan-Backdoor](/de/nfc/nested-fudan).
3. Hast du überhaupt keine Schlüssel, sammle Nonces vom Lesegerät (siehe unten) und rechne die Schlüssel dann mit [MFKey](/de/nfc/mfkey) zurück.
4. Die restlichen Schlüssel holst du mit Nested ([Anleitung](/de/nfc/nested-fudan)).

### Nonces vom Lesegerät sammeln

Bis vor kurzem galt, dass der Flipper mit 4-Streifen-Lesegeräten überhaupt nicht arbeiten kann. Dank @blowtreez stellte sich heraus, dass es doch geht, auch wenn es Präzision und Übung braucht. Der Flipper sammelt Nonces von **allen** Versionen der Lesegeräte, unabhängig von der Zahl der Streifen oder der Firmware.

- Finde die Position, in der der Flipper mit dem Lesegerät interagiert. Empirisch: der Schriftzug **„FLI"** auf dem Flipper-Gehäuse sollte **über dem Lesegerät** liegen.
- Halte ihn so nah wie möglich, in Kontakt mit dem Lesegerät.
- Manchmal (wie beim Autor) funktioniert es in einer Hülle nicht; nimm den Flipper heraus und versuch es nackt.

Folge dann dem offiziellen Artikel [Recovering MIFARE Classic keys](https://docs.flipper.net/nfc/mfkey32).

::: tip Anmerkungen des Autors
- In den meisten Fällen genügen die Schlüssel und die vollständig gelesenen Sektoren **0, 1 und 14**, aber manche Systeme halten die Daten in eigenen Sektoren (zum Beispiel 8). Mach immer eine vollständige Kopie und entschlüssele alle Sektoren.
- Der Autor erwähnt eine private API, die den Schlüssel von Sektor 14 aus einer Karten-UID berechnet, um mit Nested weiterzumachen (angeboten im Unleashed-Community-Chat).
:::

## Schritt 2: Emulation

- Funktioniert an allen „3 Streifen"-Lesegeräten (seltene Ausnahmen) und an „4 Streifen"-Lesegeräten, sofern sie nicht die neueste Firmware laufen lassen (**7.28**, wie im Kanalbeitrag angegeben).
- Auf älteren Versionen wie **7.20** (der aktuellen Werksfirmware) funktioniert Emulation, aber du musst die exakte Position des Flippers relativ zum Lesegerät finden, wie beim Nonce-Sammeln.
- Die Filter OTP1 und OTP2 wirken **nicht** auf die Emulation.
- Chameleon Ultra verhält sich genauso.
- Mit aktivem Filter „nur IL-30" funktioniert Emulation nicht.

## Schritt 3: auf einen Rohling kopieren

Die universelle Wahl ist ein Rohling vom Typ **CUID static nonce (alias MF-3.2)** (siehe [Magic Cards](/de/nfc/magic-cards)). Zum Zeitpunkt des Schreibens funktionierte er bei beiden Lesegerätetypen auf allen Firmware-Versionen und Filtereinstellungen. Für „3 Streifen" reicht eine gewöhnliche **CUID**, und manchen gelang es sogar mit **Zero**.

Der Autor empfiehlt, nicht nach dem minimal funktionierenden Rohling zu jagen, es sei denn, du hast Freude an Experimenten: der Preisunterschied zwischen CUID static nonce und einfacher CUID ist klein, und du umgehst den „Kasinofaktor". Er fand außerdem mehrere einfache CUID-Chips (neuere Revisionen), die auf allen 4-Streifen-Firmware-Versionen funktionieren, sowie frühere Berichte aus der Community über Erfolge mit einfachen CUID-Rohlingen, die er bis vor kurzem nicht zuverlässig nachstellen konnte.

## Nicht behandelt

Der Autor nennt Themen, die außerhalb des Rahmens liegen oder noch untersucht werden: wie die Filter OTP1/OTP2 umgesetzt sind, die KDF für Schlüssel A von Sektor 14 aus der UID und die Rolle der Objektkarte bei der Verschlüsselung der Sektoren.

## Verwandte Seiten

- [Nested und Fudan-Backdoor](/de/nfc/nested-fudan) · [MFKey](/de/nfc/mfkey) · [Magic Cards](/de/nfc/magic-cards)
- [Iron Logic dynamische Anlernung](/de/nfc/iron-logic-enrollment) · [Vizit-Filter](/de/nfc/vizit-filters)
