---
title: Iron Logic dynamische Anlernung
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# Iron Logic „Dynamik" und der Logikfehler beim Anlernen

Eine Forschungsnotiz dazu, wie Iron-Logic-Lesegeräte die Anti-Klon-„Dynamik" umsetzen (den Modus „ТП" / „nur der erste"), und zu einem Logikfehler in der Lesegerät-Firmware 7.29, der **in 7.30 behoben** wurde. Lesestoff zur Weiterbildung für Besitzer und Forscher.

::: tip Geltungsbereich
Nur für deine eigenen Ausweise und für rechtmäßige Forschung. Der hier beschriebene Fehler ist in der aktuellen Firmware (7.30) behoben. Nach dem Artikel von @gromovyna (05.06.2025) und Kanalbeiträgen.
:::

## Wie sich diese Systeme gegen Klonen wehren

Ein statischer MIFARE-Classic-Anhänger kann von jedem kopiert werden, der die Schlüssel hat. Die Hersteller antworten auf zwei Weisen:

1. **Filter**, die Magic-Rohlinge und Emulatoren erkennen (siehe [Iron Logic Lesegeräte](/de/nfc/iron-logic), [Vizit-Filter](/de/nfc/vizit-filters)).
2. **Dynamik**: ein Teil der Daten auf der Karte wird bei jedem Durchgang mit dem Speicher des Lesegeräts synchronisiert (ein „Zähler"). Eine früher gemachte Kopie passt nicht mehr und wird abgewiesen. Varianten davon nutzen Intratone, Hexact, Comelit, Noralsy und Urmet in Frankreich, Belgien und Luxemburg (wo eine erkannte Desynchronisierung alle Tags eines Nutzers abschalten kann); gesehen wurde es auch an manchen Eltis-Türsprechanlagen in Russland.

## Der Modus „ТП" („Только первый" / „nur der erste")

Aus der im Kanal zitierten Herstellerankündigung (Beitrag 20): bei jedem Zutritt schreibt das Lesegerät ein **neues Passwort** auf die Karte. Beim nächsten Zutritt werden Kartennummer und Passwort gegen das geprüft, was das Lesegerät gespeichert hat; stimmen sie überein, wird die Karte akzeptiert und ein neues Passwort geschrieben. Ergebnis: wie viele Kopien es auch gibt, nur eine Karte funktioniert weiter. Zunächst nur von **CP-Z2 MF-I** unterstützt, mit Firmware 7.29 (angekündigt als nicht vollständig getestet). Der Hersteller warnt, dass nun jeder Durchgang **auf die Karte schreibt**, du solltest also die Schreibfestigkeit deiner Karten prüfen, bevor du umstellst.

Warum das Kopfschmerzen macht: der Markt ist voll gefälschter chinesischer MIFARE-Classic-Tags, die die Zahl der Neuschreibvorgänge möglicherweise nicht überleben, und ein abgebrochener Schreibvorgang (schlechte Position, Stromverlust) kann die Karte aus dem Takt bringen. Auch deshalb kann Emulieren oder Klonen in solchen Systemen **dein Original ruinieren**.

## Firmware 7.29: keine Filter, Dynamik als Hauptmodus

Firmware 7.29 (offener Test) schaltete alle Filter ab und machte die Dynamik zum Hauptmodus. Das Forschungsteam fand in diesem Release Schwachstellen; ein Logikfehler wurde in **7.30** behoben, woraufhin der Autor die Beschreibung veröffentlichte.

## Anlernen: wie eine Karte dynamisch wird

Um Tausende bestehender statischer Karten auf Dynamik umzustellen, ohne dass die Nutzer sie neu ausstellen lassen müssen, führte Iron Logic das **Anlernen** (Enrollment) ein. Metadaten werden in **Sektor 14** der Karte geschrieben. Vereinfachte Logik des Lesegeräts:

1. Das Lesegerät prüft die Metadaten der Karte.
2. Ist die Karte **noch nicht im dynamischen Modus**, lernt das Lesegerät sie an und speichert einen Zählerwert. Es prüft **nicht**, ob diese Karten-ID in seinem Speicher schon vorhanden ist.
3. Ist die Karte schon angelernt, gelten strenge Zählerprüfungen.

Die ID-/Zähler-Paare liegen im nichtflüchtigen Speicher des Lesegeräts.

## Der Fehler (behoben in 7.30)

Die Schwäche folgt aus Schritt 2: ein Lesegerät, dem eine Karte vorgehalten wird, die noch „statisch" aussieht, lernt sie einfach erneut an. Die einzige Hürde für einen Angreifer ist, einen Dump der Karte von **vor** ihrem ersten Anlernen zu haben. Karten, die alt genug sind, um keine Metadaten zu haben, akzeptiert das Lesegerät nicht, deshalb wurde die Rückführung dynamischer Daten in einen „statischen" Zustand nur oberflächlich untersucht.

Der Autor beschreibt zwei praktische Wege, jedes Mal eine „statische" Karte vorzuzeigen:

- **GDM-(GDMIC-)Tags**, eine USCUID-Variante mit Shadow-Modus: die Daten werden in einen temporären Speicher geschrieben und fallen beim Abschalten des Lesegerätfelds auf den dauerhaften Speicher zurück, sodass das Original (schon angelernt) und unbegrenzt viele Kopien nebeneinander existieren können. Der Autor weist darauf hin, dass das einfach, für die meisten Schlüsseldienste aber zu viel ist, und sich mit den früheren Filtern oder einer klügeren Behandlung des HF-Felds kontern lässt.
- **Flipper Zero, von Hand**: die statische Karte lesen, emulieren, `Return to Initial State` nutzen, wiederholen. Für Tests in Ordnung, im Alltag unpraktisch.

Das Team hat weitere theoretische und praktische Angriffe und hat einige Ideen mit iKey geteilt.

## Was Besitzer tun sollten

- Aktualisiere die Lesegeräte auf **7.30 oder neuer**.
- Prüfe die Schreibfestigkeit deiner Karten, bevor du die Dynamik aktivierst.
- Bevorzuge, wo du kannst, moderne Kartenfamilien (MIFARE Plus, DESFire und ähnliche); MIFARE Classic gilt beim eigenen Hersteller als veraltet.

## Verwandte Seiten

- [Iron Logic Lesegeräte](/de/nfc/iron-logic) · [Magic Cards](/de/nfc/magic-cards) · [Vizit-Filter](/de/nfc/vizit-filters)
