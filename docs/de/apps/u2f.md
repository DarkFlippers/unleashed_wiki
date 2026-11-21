---
title: U2F-Sicherheitsschlüssel
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# U2F-Sicherheitsschlüssel

Die App **U2F** macht aus dem Flipper Zero einen USB-Sicherheitsschlüssel nach
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). Nachdem du dein Passwort auf
einer Website eingegeben hast, fragt die Seite nach dem Schlüssel, und du bestätigst die Anmeldung mit <kbd>OK</kbd>
auf dem Flipper. Google, GitHub, Facebook, X und viele weitere Seiten unterstützen U2F-Schlüssel;
[dongleauth.com](https://www.dongleauth.com/) führt eine Liste.

::: warning Rein softwarebasierter Schlüssel
U2F ist auf dem Flipper in Software umgesetzt. Nutze für Bankkonten und andere besonders wertvolle Zugänge einen
zertifizierten Hardware-Sicherheitsschlüssel. Halte immer einen zweiten Faktor als Reserve bereit
(Wiederherstellungscodes oder einen weiteren Schlüssel).
:::

## Bevor du beginnst

- Eine **microSD-Karte ist erforderlich**. Die U2F-Daten liegen in `/ext/u2f/`. Ohne sie zeigt die App
  `No SD card or app data found. This app will not work without required files.`
- Die Zertifikatsdateien `/ext/u2f/assets/cert.der` und `/ext/u2f/assets/cert_key.u2f` werden vom Firmware-Update
  installiert. Fehlen sie, aktualisiere die Firmware mit eingesteckter Karte erneut.
- **Schließe qFlipper** (und Flipper Lab): der Flipper muss seinen USB-Port frei in den U2F-Modus umschalten können.
  Ist eine Verbindung aktiv, zeigt die App `Connection Is Active! Disconnect from PC or phone to use this function.`

## Den Flipper auf einer Website registrieren

1. Verbinde den Flipper über ein USB-Kabel mit dem Computer.
2. Öffne `Main Menu → U2F`. Der Bildschirm zeigt `Connect me to computer` und dann `Connected!`, sobald der Computer
   den Schlüssel erkannt hat.

   ![U2F: Connect me to computer, der Flipper als USB-Stick gezeichnet](/screens/apps/u2f_not_connected.png)

3. Öffne auf der Website die Einstellungen zur Zwei-Faktor-Authentifizierung und wähle, einen
   **Sicherheitsschlüssel** hinzuzufügen (die Bezeichnung unterscheidet sich je nach Seite).
4. Der Flipper zeigt `Press OK to register`. Drücke <kbd>OK</kbd>.
5. Die Seite bestätigt, dass der Schlüssel hinzugefügt wurde.

## Anmelden

1. Verbinde den Flipper über USB und öffne `Main Menu → U2F` (`Connected!`).
2. Gib Benutzername und Passwort auf der Website ein.
3. Wenn die Seite nach dem Sicherheitsschlüssel fragt, zeigt der Flipper `Press OK to authenticate`. Drücke
   <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate, mit dem Hinweis auf die Taste OK](/screens/apps/u2f.png)

4. Der Flipper zeigt `Authentication successful!` und die Seite meldet dich an.

## Bewahre deine U2F-Dateien sicher auf

| Datei | Zweck |
|---|---|
| `/ext/u2f/key.u2f` | der U2F-Schlüssel dieses Geräts, verschlüsselt mit einem für diesen Flipper einzigartigen Schlüssel |
| `/ext/u2f/cnt.u2f` | Authentifizierungszähler |
| `/ext/u2f/assets/` | Attestierungszertifikat und dessen Schlüssel (`cert.der`, `cert_key.u2f`) |

::: danger Die U2F-Dateien nicht löschen, bearbeiten oder verschieben
- Jeder Flipper hat einen einzigartigen eingebauten Schlüssel, der die U2F-Dateien verschlüsselt. Eine Karte, deren
  U2F-Dateien auf einen **anderen Flipper** übertragen werden, funktioniert dort **nicht**.
- Wenn du die Dateien löschst oder bearbeitest oder eine neue Karte einsetzt, erzeugt der Flipper einen neuen Satz
  U2F-Dateien, und du musst ihn **auf jeder Website erneut registrieren**.
- Wenn du `u2f/assets` (oder den ganzen Ordner `u2f`) löschst, funktioniert die App nicht mehr (sie meldet
  `No SD card or app data found`), bis du den Ordner durch ein Firmware-Update wiederherstellst.
:::

## Fehlerbehebung

| Symptom | Lösung |
|---|---|
| bleibt bei `Connect me to computer` | ein Datenkabel verwenden (kein reines Ladekabel), qFlipper schließen, einen anderen USB-Port probieren |
| `Connection Is Active!` | qFlipper, Flipper Lab, die CLI oder die Sitzung der Mobil-App schließen und U2F erneut öffnen |
| `No SD card or app data found` | die Karte einsetzen; ist sie drin, `/ext/u2f/assets` durch eine Neuinstallation der Firmware wiederherstellen |
| `Certificate error` | die U2F-Engine konnte mit den Dateien auf der Karte nicht starten: die Firmware mit eingesteckter Karte neu installieren |
| die Seite akzeptiert den Schlüssel nicht mehr | die U2F-Dateien wurden neu erzeugt (neue Karte, gelöschte Dateien): melde dich mit deinem Reservefaktor an und registriere den Flipper erneut |

Der Tab **U2F** im [Archive](/de/apps/archive) startet die App ebenfalls.

## Verwandte Seiten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
- [Bad USB](/de/badusb/usage)
- [qFlipper](/de/mobile/qflipper)
