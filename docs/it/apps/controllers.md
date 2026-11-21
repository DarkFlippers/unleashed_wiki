---
title: Associare il telecomando HID
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Associare il telecomando HID

L'app telecomando HID consente al Flipper di controllare presentazioni, digitare testo, muovere il mouse e gestire la
riproduzione multimediale su un computer o un telefono. Questa pagina riguarda la **connessione**; le singole modalità
sono descritte in [Telecomando USB / Bluetooth (HID)](/it/apps/hid-remote).

Puoi collegarlo in due modi:

| | USB | Bluetooth LE |
|---|---|---|
| App | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Associazione | nessuna, basta collegarlo | una volta per host |
| Funziona con | computer, telefoni con USB-C/OTG | computer, Android, iPhone/iPad |

::: tip Unleashed
In Unleashed le due varianti si chiamano **USB Keyboard & Mouse** e **Bluetooth Remote**, e si trovano nelle cartelle
di app `USB` e `Bluetooth` (la documentazione ufficiale chiama entrambe "Remote").
:::

## Via USB

1. Collega il Flipper al computer con un cavo dati USB. Chiudi prima qFlipper: il telecomando ha bisogno della porta
   USB.
2. Apri `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Scegli una modalità (Keynote, Keyboard, Mouse...). Il computer vede una nuova tastiera/mouse, non serve alcun
   driver.

Quando esci dall'app, l'USB del Flipper torna alla modalità normale (seriale).

## Via Bluetooth

1. Attiva il Bluetooth sul computer o sul telefono.
2. Sul Flipper: `Main Menu → Settings → Bluetooth` e imposta **Bluetooth** su **ON**.
3. Apri `Main Menu → Apps → Bluetooth → Bluetooth Remote` e scegli una modalità.
4. Sul computer o sul telefono apri le impostazioni Bluetooth e collegati a **Control &lt;nome del Flipper&gt;** (su
   un telefono tocca **Pair**).
5. Se il Flipper mostra una richiesta di conferma dell'associazione, premi <kbd>OK</kbd>.

Dalla volta successiva l'host si riconnette automaticamente quando apri Bluetooth Remote.

::: tip Nome personalizzato
`Bluetooth Remote → Bluetooth Remote Name` cambia il nome annunciato, utile se hai più telecomandi Flipper o se vuoi
che appaia come una comune tastiera.
:::

### Se l'associazione non riesce

- Verifica che il Bluetooth sia su ON in `Settings → Bluetooth`.
- Rimuovi la vecchia voce "Control ..." dalle impostazioni Bluetooth dell'host, poi sul Flipper esegui
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` e ripeti l'associazione.
- Scollega il Flipper dagli altri dispositivi (per esempio dall'app mobile).
- Riavvia il Flipper: tieni premuti <kbd>←</kbd> + <kbd>Back</kbd> per circa 5 secondi.
- Aggiorna il firmware.

Il telecomando mantiene le proprie associazioni (`/ext/apps_data/hid_ble/.bt_hid.keys`), separate dal Bluetooth
principale del Flipper usato dall'app mobile. **Bluetooth Unpairing** all'interno del telecomando cancella soltanto
gli host del telecomando. L'opzione globale `Settings → Bluetooth → Unpair All Devices` cancella tutto:
l'associazione dell'app mobile e anche quelle del telecomando (e di BadKB).

### iPhone / iPad: la modalità TikTok non reagisce

1. Sull'iPhone apri `Settings → Accessibility → Touch → AssistiveTouch`.
2. Attiva **AssistiveTouch**.
3. In **Pointer Devices** vai su **Devices → Bluetooth Devices** e seleziona il tuo Flipper.

## Pagine correlate

- [Telecomando USB / Bluetooth (HID)](/it/apps/hid-remote)
- [Impostazioni](/it/start/settings)
- [App mobile Flipper](/it/mobile/mobile-app)
