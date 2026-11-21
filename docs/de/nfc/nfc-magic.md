---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0: Magic-Rohlinge beschreiben und löschen

**NFC Magic** ist die App, um [Magic-Rohlinge](/de/nfc/magic-cards) direkt vom Flipper aus zu beschreiben, zu klonen
und zu löschen. Sie begann als offizielle Flipper-Zero-App; die hier beschriebene Fassung liegt im Paket
[all-the-plugins](https://github.com/xMasterX/all-the-plugins) von **xMasterX** und wird vom **Unleashed**-Team
gepflegt (es hat sie geforkt und entwickelt sie weiter). Version **2.0** wurde von **@gromovyna** geschrieben: der
ganze Zyklus von der Transportforschung bis zum letzten Knopf in der Oberfläche.

Vor 2.0 beherrschte die App Magic-**MIFARE Classic** (Gen1a, Gen2) und das universelle **Gen4** (UMC/GTU), einen
konfigurierbaren Chip, der nicht an MFC gebunden ist. 2.0 ergänzt **Ultralight/NTAG**-Magic-Rohlinge und ehrliche
Ergebnisse.

![Neue Version, neues Icon](/img/remote/dafa43486592335f.png)

::: tip Woher bekommst du sie
NFC Magic ist **nicht Teil der Firmware-Binary**: es ist eine externe App aus dem Extra-Apps-Paket. 2.0 ist in
Unleashed-**Dev-Builds ab 1307** verfügbar. Aktualisiere die App über den Katalog oder die Firmware auf einen
frischen Dev-Build (mit dem Extra-Apps-Paket). Pfad auf dem Gerät: `Main Menu → Apps → NFC → NFC Magic`.
:::

## Bevor du anfängst

1. [Lies](/de/nfc/read) die Originalkarte und **speichere** sie. Stelle sicher, dass **alle** Sektoren (MIFARE
   Classic) bzw. Pages (Ultralight/NTAG) gelesen wurden: ein Teildump gibt eine Teilkopie.
2. Bei MIFARE-Classic-Rohlingen authentisiert sich NFC Magic mit Schlüsseln aus dem **Schlüsselcache** und dem
   **Benutzer- und Systemwörterbuch**, mit nichts anderem. Kamen die Schlüssel deiner Karte aus einem
   CUID-Wörterbuch, führe am Dump zuerst **Save Keys to Dictionary** aus (siehe
   [MIFARE Classic](/de/nfc/mifare-classic#save-keys-to-dictionary)).

## Schritt 1. Erkennung

Alles beginnt damit, dass du den Rohling auf den Flipper legst (`Check Magic Tag`). Die erste große Änderung: die App
ist nicht mehr auf MIFARE Classic fixiert. Der Scanner arbeitet **familienweise**: er bestimmt zuerst die Familie
(**MFC** oder **Ultralight/NTAG**) und gräbt erst dann nach der genauen Variante.

Für **USCUID-UL** (Magic-Rohlinge der Ultralight-Familie) wird der ganze Hauptzoo erkannt, plus ein wenig lokaler
russischer Zirkus: **UL11**, **UL21** (einschließlich dem, was auf dem Ex-UdSSR-Markt als **„Ultra"** verkauft wird),
**NTAG213/215/216**, **UL-C**, **UL-5** und Tags, die schon im **Backdoor**-Modus sind (beide Wakeup-Sequenzen werden
geprüft).

![Erkanntes USCUID-UL](/img/remote/557fa5d47ebeb0a6.png)

Hast du ein Preset, das die App nicht kennt, gibt sie nicht auf: sie zeigt die **Rohkonfiguration**, damit du sie
selbst sehen und analysieren kannst. Praktisch für Forscher.

![Rohkonfiguration 1](/img/remote/7c3f38df0079d8fa.png)

![Rohkonfiguration 2](/img/remote/c16eb844763ef4fa.png)

![Rohkonfiguration 3](/img/remote/30f2a4b10d4be98a.png)

Bei einer passwortgeschützten **Gen4**-Karte: `Gen4 Actions → Auth with password`, Passwort eingeben, dann den Tag
prüfen.

## Schritt 2. Ultralight / NTAG beschreiben

Ist der Tag erkannt, kannst du **UL/NTAG** beschreiben und vollständig klonen. Worüber du **nicht** nachdenken
musst, ist der Transport: die App wählt ihn nach dem Erkennungsergebnis.

- **Direct**: ein normales ISO14443-3-Schreiben mit dem Befehl **`A2`**, für Tags, die Schreibzugriffe frontal
  annehmen (z. B. werkseitige **USCUID-UL**-Konfigurationen, dasselbe **UL21**, alias **„Ultra"**).
- **Backdoor**: hat der Chip eine offene Backdoor, nutzt die App sie (Raw Wakeup plus Backdoor-Befehle). Einfache
  Logik: offene Backdoor → nutzen; keine → direkt schreiben.

Deine Entscheidungen:

- **Auf einen Tag ohne Backdoor schreiben, dessen Passwort du kennst?** Gib es per **PWD-AUTH** mit: die App
  authentisiert sich vor dem Schreiben oder Löschen am Tag.
- **Der Tag wurde nicht als Magic bestätigt, aber du weißt, dass er es ist?** Drücke **Write anyway** und trage die
  Verantwortung.

Der Schreibvorgang wurde so wenig beängstigend wie möglich gemacht:

- **Live-Fortschritt „Writing X/N"** auf dem Bildschirm, damit du nicht auf einen scheinbar eingefrorenen Bildschirm
  starrst und dich fragst, ob überhaupt etwas passiert.

  ![Schreibfortschritt (schnell: für den Screenshot war ein NTAG216 nötig)](/img/remote/9914d55ba866082e.png)

- Die **Page-Reihenfolge** ist pro Tag-Typ abgestimmt (z. B. **UL-5**) und **für Schreiben und Löschen
  unterschiedlich**, wegen der Lock-Bits. Beim Schreiben kommen die Service-Pages (einschließlich der UID) **zuletzt**:
  schreibt man Lock/Protection zu früh, sperrt der Tag, bevor der Dump vollständig ist. Ein Löschvorgang läuft
  aufsteigend, um zuerst den statischen Lock zu entfernen und erst dann den Rest zu säubern.
- Geschrieben wird **ACK-only mit Continue-on-Error**: die App bleibt nicht bei der ersten fehlgeschlagenen Page
  stehen, sie schiebt durch, was sie kann.
- Hat etwas nicht geklappt, bekommst du **Partial Write** mit einer **Details**-Liste genau der Pages, die
  fehlgeschlagen sind, nicht ein fröhliches „done". Den Tag unterwegs von der Antenne gezogen? Lege ihn zurück, und
  das Schreiben läuft an derselben Stelle weiter.

![Teilweise geschrieben](/img/remote/a50fa90dff60cdd8.png)

![Details](/img/remote/71b6fa77e1914b76.png)

Und **Wipe** setzt den Tag mit einem Druck in den Werkszustand zurück.

## Schritt 3. MIFARE Classic beschreiben

1. Wähle in NFC Magic **Check Magic Tag** und halte den Rohling an die Rückseite des Flippers.
2. Ist der Rohling erkannt (Gen1a, Gen2, Gen4 …), geh zu **More** für die Optionen dieses Rohlingstyps.
3. **Write**: wähle die Originalkarte im Dateibrowser, halte den Rohling an den Flipper.
4. **Wipe** formatiert den Rohling: UID zurück auf Standard, Daten in Sektoren/Pages gelöscht.

### Ehrliche Rückmeldung: Success / Partial / Fail

Hier geht es um das gute alte **MIFARE Classic (Gen2)**, und es ist dem Autor genauso wichtig wie die neuen
Funktionen.

Früher meldeten Löschen und Klonen von MFC **immer** „Success". Immer, selbst wenn kein einziges Byte geschrieben
wurde. Das ist nicht nur ein Bug, das ist eine Lüge: du gehst in der Gewissheit weg, dass deine Kopie funktioniert,
und sie tut es nicht.

Jetzt werden Vorgänge **Block für Block** verfolgt, und du bekommst ein ehrliches Urteil:
**Success / Partial / Fail**. Bei **Partial** siehst du **Details**: welche Blöcke nicht geschrieben oder gelöscht
wurden. Der nur lesbare Block 0 lässt im Bericht nicht mehr den ganzen Sektor 0 scheitern (wie im ursprünglichen
Entwurf), was auch praktisch ist, wenn der Tag durch **Access Bits** geschlossen ist.

![Ergebnis](/img/remote/9e9d84e664f7da06.png)

![Details eines teilweisen Ergebnisses](/img/remote/525faf18552333d1.png)

Dinge, die das Leben ruhiger machen:

- Beim Löschen **behält Block 0 die echten SAK/ATQA** des Tags. Klassischer Fall: **Perfect CUID** (beantwortet RATS
  / hat ATS). Die Firmware erkannte sie als 4K, und das Löschen stempelte Block 0 als 4K. Behoben: eine 1K bleibt
  1K, und die UID wird genullt.
- Kein funktionierender Schlüssel für das Löschen? Statt eines von Anfang an aussichtslosen Schreibversuchs siehst
  du sofort **„No keys found"**.
- Jeder Fehlerbildschirm (Wipe / Write / Dump) hat **Exit → menu**, damit du dich nicht gefangen fühlst.
- Ein hässlicher Bug ist weg: Schlüssel vom vorherigen Tag werden **nicht mehr mitgenommen** in den nächsten
  Vorgang. Der Wörterbuchangriff liest den Tag jetzt jedes Mal neu, statt die Schlüssel des letzten Tags
  wiederzuverwenden (was ein falsches Erfolgsgefühl und vorgetäuschte Geschwindigkeit erzeugen konnte).

## Schutz vor Fehlgriffen

Schon im vorherigen Release bekam die App einen Schutz rund um Magic-MFC-Tags und verschiedene **UID**-Längen. 2.0
prüft, ob der Dump sich überhaupt auf die gegebene **USCUID-UL**-Variante schreiben lässt:

![Prüfung der Kompatibilität von Dump und Rohling](/img/remote/a4dc82f2b66b73b5.png)

und blockiert, für die besonders Begabten, Versuche, **verschiedene Familien** zu paaren (einen MFC-Dump auf einen
Ultralight-Rohling und umgekehrt; solche Fälle tauchen in Foren und Chats regelmäßig auf):

![Familie passt nicht](/img/remote/83e6e6cf1f0d9da6.png)

## Es ist weniger trivial, als es aussieht

Hinter der Funktionsliste stehen fast **3.000 Zeilen** Änderungen: ein von Grund auf neu geschriebener
USCUID-UL-Poller, die neu geschriebene Gen2-Logik und ein Haufen behobener Bugs. Alles wurde **an echter Hardware
validiert**, mit einer **QA-Matrix von fast 100 Fällen**:

- **~15 Test-Tags**: gekaufte oder selbst gebastelte USCUID-UL-Varianten (UL11, UL21 (NXP und Mikron „Ultra"),
  NTAG213/215/216, UL-C, UL-5, mehrere UL-Y-Varianten für Randfälle), Tags im Backdoor-Modus (beide Wakeups), dazu
  echte Nicht-Magic- und vollständig gesperrte Tags für ehrliche Fails und ein Haufen Tags für die Regression;
- **Kategorien**: Erkennung (17 Fälle), Direct-/Backdoor-Transport, Datenintegrität und Page-Reihenfolge,
  UX-Szenarien, PWD-AUTH, Wipe, ein dicker Block für Gen2-/MFC-Wipe (19 Fälle) und Regression aller alten Protokolle
  (Gen1a 4/7 Byte, Gen2, Gen4, einfache MFC).

Dieser Durchlauf brachte viele Bugs zutage und erledigte sie: falsche „Success", tote Knöpfe, ein Speicherleck, ein
Spinner, der an einem echten Ultralight endlos drehte. Bekannte Einschränkungen (darunter eine Feinheit bei der
1K-/4K-Erkennung auf Firmware-Ebene) sind dokumentiert.

Als nächstes auf der Liste: **UL-C**-Schreibunterstützung für USCUID-UL und möglicherweise regionsspezifische Exoten.

## Fehlersuche

- **Tag nicht erkannt**: es ist vielleicht kein Magic-Tag, oder es ist ein unbekanntes Preset: prüfe die
  Rohkonfiguration. Bei einem Gen4 mit Passwort authentisiere dich zuerst.
- **„No keys found"** beim Löschen einer MFC: die aktuellen Schlüssel des Rohlings sind nicht in deinen
  Wörterbüchern. Füge sie hinzu (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Partial Write**: lege den Tag zurück und fahre fort; prüfe **Details**. Lock-Bits/Access Bits im Quelldump können
  manche Blöcke/Pages unbeschreibbar machen.
- **Das Lesegerät weist die Kopie ab**: das Lesegerät filtert möglicherweise deinen Rohlingstyp. Siehe
  [Magic Cards](/de/nfc/magic-cards), [Iron Logic](/de/nfc/iron-logic),
  [Vizit-Filter](/de/nfc/vizit-filters).

## Verwandte Seiten

[Magic Cards](/de/nfc/magic-cards) · [MIFARE Classic](/de/nfc/mifare-classic) · [qUnleashed](/de/nfc/qunleashed) ·
[Karten entsperren](/de/nfc/unlock-with-password)
