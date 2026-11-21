---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

Das **Video Game Module** (VGM) ist eine offizielle Erweiterung rund um den **Raspberry Pi RP2040**. Es steckt auf der
GPIO-Stiftleiste und ergänzt:

- **Video Out** — spiegelt das Flipper-Display auf einen Fernseher oder Monitor (DVI-D-Signal, 640×480);
- einen **6-Achsen-Bewegungssensor** (TDK ICM-42688-P: 3-Achsen-Gyroskop + Beschleunigungssensor) für
  Gyro-Steuerung;
- einen **USB-C-Port**, der am RP2040 hängt (zum Flashen oder zur Nutzung durch eigene Firmware);
- ein **14-poliges GPIO-Breakout** des RP2040;
- **BOOT-/RESET-Taster** (mit einer Büroklammer zu drücken) für den UF2-Flash-Modus und einen Reset;
- eine RGB-LED auf der Oberseite.

Es kann auch als eigenständiges RP2040-Board arbeiten und ist mit Raspberry-Pi-Pico-Projekten kompatibel.

![Taster und Anschlüsse des Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Anbringen und an einen Fernseher anschließen

1. **Modul anbringen.** Es kommt mit einem Silikonrahmen, der für einen Flipper *ohne* Hülle gedacht ist. Steckt dein
   Flipper in einer Silikonhülle, nimm den Rahmen vom Modul ab (oder die Hülle vom Flipper).
2. **Firmware.** Das Modul braucht Flipper-Firmware 0.98.3 oder neuer; aktuelle Unleashed-Releases erfüllen das.
3. **UART-Einstellung prüfen:** `Main Menu → Settings → Expansion Modules → Listen UART` muss auf **`USART`** stehen.
   Bei jedem anderen Wert wird das Modul nicht erkannt. (Siehe [Expansion-Module](/de/gpio/expansion-modules).)
4. Modul einstecken (Flipper aus), einschalten. Der Flipper erkennt das Modul und richtet es automatisch ein.
5. Verbinde das Fernsehkabel mit dem **Video Out**-Anschluss des Moduls und wähle diesen Eingang am Fernseher.

### „Video Game Module not initialized“

Dieser Text auf dem Fernseher bedeutet, dass das Modul nicht mit einem Flipper spricht: Die Firmware ist zu alt,
`Listen UART` steht nicht auf `USART`, oder das Modul wird versorgt (z. B. über USB), ohne dass ein Flipper angesteckt
ist.

## Spiele und Apps

Den Bewegungssensor nutzen Apps aus dem Flipper Apps Catalog, zum Beispiel
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) und [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(Gyro-Maus für einen Computer).

::: tip Unleashed
Die JavaScript-Engine von Unleashed enthält ein Modul `vgm` (JS-Feature `vgm`): `getPitch()`, `getRoll()`, `getYaw()`
und `deltaYaw(angle, timeout)` lesen die Ausrichtung des Moduls aus einem Skript und geben `undefined` zurück, wenn
kein VGM vorhanden ist. Zu JavaScript-Apps siehe den Abschnitt [Entwicklung](/de/dev/).
:::

## Die Modul-Firmware aktualisieren

Updates werden mit der App **Video Game Module Tool** installiert (aus dem Flipper Apps Catalog). Ihr Menü:

- `Install Official Firmware` — die neueste offizielle Modul-Firmware, der App beigelegt;
- `Install Firmware from File` — eine eigene `.uf2` von der SD-Karte.

So aktualisierst du:

1. Installiere (oder **aktualisiere zuerst**) Video Game Module Tool: Gehe in der mobilen Flipper-App auf **Apps**,
   suche *Video Game Module Tool* und tippe auf **INSTALL** / **UPDATE**. Eine neue Modul-Firmware kommt mit einer
   neuen Version der App, aktualisiere also immer erst die App und dann das Modul.
2. Verbinde das Modul mit dem Flipper.
3. Öffne `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Wähle `Install Official Firmware` und bestätige mit `Install` (<kbd>→</kbd>).
5. Warte auf **Video Game Module Updated**.

## Eigene Firmware

Das Modul kann deine eigene RP2040-Firmware ausführen.

### Vom Flipper Zero aus

So kannst du mehrere Modul-Firmwares auf der SD-Karte halten und ohne Computer wechseln.

1. Kopiere die `.uf2`-Datei auf die SD-Karte des Flippers (z. B. mit [qFlipper](/de/mobile/qflipper):
   `File manager → SD Card`, einen Ordner anlegen, die Datei hochladen).
2. Verbinde das Modul und öffne `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Wähle die Datei und bestätige mit `Install` (<kbd>→</kbd>). Warte auf **Video Game Module Updated**.

::: warning Einschränkungen von UF2 bei der Installation über den Flipper
- Blöcke, die nicht in den Flash gehen, werden nicht unterstützt.
- Block-Payloads müssen genau 256 Byte groß sein.
- Die Zieladressen der Payloads müssen auf 256 Byte ausgerichtet sein, ohne Lücken.
- Datei-Container und Extension-Tags werden nicht unterstützt.
:::

### Von einem Computer aus

1. Trenne das Modul vom Flipper und von USB.
2. Halte den **BOOT**-Taster des Moduls mit einer Büroklammer gedrückt.
3. Verbinde das Modul per USB-C mit dem Computer. Es wird als USB-Laufwerk namens **RPI-RP2** eingebunden. Lass
   **BOOT** los.
4. Zieh die `.uf2`-Datei auf **RPI-RP2**. Das Modul startet neu und wird von selbst ausgeworfen.

## Hardware-Details (für den eigenständigen Betrieb)

### RP2040-GPIO

- GPIO **8–15** und **18–20** werden für den Videoausgang verwendet und sind an den Anschlüssen nicht verfügbar.
- GPIO **0–7, 16, 17, 21, 22, 26–28** liegen an den Anschlüssen (wie bei einem Raspberry Pi Pico). GPIO **2–7** sind
  zusätzlich mit dem Bewegungssensor verbunden.
- GPIO **23–25 und 29** (auf einem Pico intern verwendet) sind auf dem VGM frei und am 14-poligen Breakout
  herausgeführt.

![Pinbelegung des 14-poligen Breakouts des Video Game Module](/img/remote/b030c6a0375c6254.png)

![Pinbelegungen von Video Game Module und Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Peripherie, die dem RP2040 zur Verfügung steht

- **Video Out:** Bild und Ton an einen Fernseher/Monitor, dazu Datenaustausch über den
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** USB-Device oder -Host (kein USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **GPIO-Breakout:** 11 GPIO-Pins mit ESD-Schutz.
- **Anschluss zum Flipper Zero:** Die Flipper-Pins 13 und 14 voll funktionsfähig; die Pins 2–7 mit eingeschränkter
  Funktion (gemeinsam mit der IMU). ESD-geschützt.
- **RGB-LED**, gesteuert über GPIO des RP2040.

### Stromversorgung

- 5 V über USB-C im eigenständigen Betrieb;
- 3,3 V (Pin 9) oder 5 V (Pin 1) vom Flipper.

Die gleichzeitige Versorgung über USB-C und den Flipper ist für das Modul und für beide Quellen unproblematisch.

Schaltpläne, Bestückungszeichnungen und PDF-Pinbelegungen stehen auf der offiziellen Seite
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Siehe auch

- [Expansion-Module](/de/gpio/expansion-modules)
- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Externe Module](/de/gpio/external-modules)
