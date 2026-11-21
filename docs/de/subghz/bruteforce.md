---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** ist eine App des Unleashed-Teams für Brute-Force auf statische Codes. Sie durchläuft die möglichen Codes eines Protokolls mit festem Code und sendet sie einen nach dem anderen. Du kannst ein vorkonfiguriertes Protokoll aus ihrer Liste nehmen oder eine eigene `.sub`-Datei laden und auswählen, welche Bytes durchlaufen werden sollen.

::: warning
Nutze sie nur an deiner eigenen Technik oder mit ausdrücklicher Erlaubnis. Das Durchprobieren von Codes an einem fremden Tor oder einer fremden Schranke ist in den meisten Ländern illegal.
:::

::: tip Unleashed
Die App ist nicht Teil des Firmware-Images und steckt nicht im Firmware-Quellbaum. Sie wird als externe App (`.fap`) in den Unleashed-App-Paketen ausgeliefert, gebaut aus [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Installiere das Paket (siehe [Apps auf der SD-Karte](/de/apps/sd-card-apps)) und such sie unter `Apps → Sub-GHz`.
:::

## Wann das sinnvoll ist

- **Nur bei statischem (festem) Code.** Brute Force funktioniert nur, wenn der Empfänger denselben Code dauerhaft akzeptiert, wie bei CAME 12 Bit, Nice Flo 12 Bit, Princeton-artigen und ähnlichen Fernbedienungen mit DIP-Schaltern. Ein Rolling-Code-Empfänger (KeeLoq, Nice Flor-S, CAME Atomo und andere) akzeptiert nie einen erratenen Code, Brute Force ist dort also nutzlos (siehe [Rolling Codes](/de/subghz/rolling-codes)).
- **Du hast die Fernbedienung deines eigenen Geräts mit festem Code verloren** und kennst dessen Code nicht, oder du willst testen, wie schnell dein eigenes System mit festem Code erraten werden kann.

Hast du noch eine funktionierende Fernbedienung, ist es viel schneller, sie einfach [zu lesen](/de/subghz/read).

## So benutzt du sie

### Vorkonfigurierte Protokolle

1. Öffne `Apps → Sub-GHz` und starte die Bruteforce-App.
2. Wähle ein Protokoll aus der Liste.
3. Um zu ändern, wie oft jeder Code wiederholt wird, drücke <kbd>→</kbd> auf dem ausgewählten Protokoll.
4. Starte den Angriff und halte den Flipper nah am Empfänger, bis er reagiert.

### Eine eigene Datei

1. Speichere zuerst ein Signal des Zielprotokolls, zum Beispiel mit [Read](/de/subghz/read) oder [Add Manually](/de/subghz/add-manually).
2. Lade diese `.sub`-Datei in der App.
3. Wähle die Bytes des Keys aus, die du durchprobieren willst. Die übrigen Bytes bleiben so, wie sie in der Datei stehen.
4. Starte den Angriff.

### Verzögerung zwischen den Signalen

Die Zeitverzögerung zwischen den gesendeten Codes stellst du auf dem Hauptbildschirm der App ein. **Halte dort <kbd>↑</kbd>** (der Hinweis auf dem Bildschirm lautet „Up to Save"), um sie zu speichern. Eine kürzere Verzögerung ist schneller fertig, aber manche Empfänger verpassen Codes, die zu dicht aufeinander folgen.

## Tipps und häufige Fehler

- **Falsche Frequenz oder Modulation**: der Empfänger hört nichts. Prüfe das Band zuerst mit dem [Frequency Analyzer](/de/subghz/frequency-analyzer).
- **Zu wenige Wiederholungen**: viele Empfänger brauchen einen Code mehrmals, bevor sie reagieren. Erhöhe die Wiederholungen mit <kbd>→</kbd> auf dem Protokoll.
- **Es läuft sehr lange**: die Anzahl der Codes wächst exponentiell mit der Anzahl der Bits. 12-Bit-Codes sind schnell durch, während längere Keys unpraktikabel lange dauern können. Grenze die Suche ein, indem du nur die unbekannten Bytes deiner eigenen Datei durchprobierst.
- **Das Senden wird blockiert**: die Frequenz liegt außerhalb des erlaubten Bereichs. Siehe [Frequenzen](/de/subghz/frequencies).

## Verwandte Seiten

- [Unterstützte Systeme](/de/subghz/supported-systems): welche Protokolle statisch sind
- [Add Manually](/de/subghz/add-manually)
- [Das `.sub`-Dateiformat](/de/subghz/file-format)
