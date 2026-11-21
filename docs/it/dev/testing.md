---
title: Test di integrazione
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Test di integrazione

Oltre agli [unit test](/it/dev/unit-tests), il firmware dispone di un **piano di test di integrazione manuale**: casi
di test passo per passo raggruppati per sottosistema, ciascuno con il risultato atteso. È scritto per i manutentori
del repository, ma è ugualmente utile se compili il tuo firmware e vuoi verificarlo prima di usarlo o condividerlo.

Questa pagina riassume il piano. Gli elenchi completi dei passaggi si trovano nel repository Unleashed sotto
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Cosa testare e quando

- **Testa ciò che è cambiato, più le possibili regressioni collegate.** Prova il nuovo comportamento e riesegui alcuni
  casi esistenti dello stesso sottosistema. Esempio: aggiungendo un protocollo Sub-GHz, prova quello e qualche
  protocollo esistente.
- **Salta i sottosistemi non interessati.** Non serve testare l'NFC se è cambiato solo il Sub-GHz.
- **Testa tutto per le modifiche che riguardano il core** — se è cambiato qualcosa di globale, esegui tutti i casi
  nell'ordine previsto.

Quando: **prima di accettare le pull request** e **prima di una release candidate**.

## Schema di test comune per chiavi e tessere

I casi relativi ai protocolli RFID, iButton e NFC riusano gli stessi "passaggi condivisi":

1. **Read** dell'originale — i dati corrispondono all'originale.
2. **Emulate** — leggi la chiave emulata con un secondo Flipper; i dati sono identici.
3. **Save** — salvata con il nome indicato; la scena passa alla directory *Saved*.
4. **Write** su una vergine — compare una schermata di successo.
5. **Read della vergine** scritta — i dati sono identici alla chiave salvata.

Molti casi richiedono quindi **un secondo Flipper**, lettori reali e supporti vergini (T5577, RW2004/RW1990 ecc.).

## Casi di test per sottosistema

### Generali (35 casi)

| Area | Cosa viene verificato |
|---|---|
| BLE | Bluetooth attivo dopo il riavvio; associazione con l'app mobile, nome del Flipper corretto; nuova associazione con un secondo telefono |
| U2F | Registrazione e autenticazione di una chiave sul sito dimostrativo WebAuthn di Yubico |
| Settings | Codice PIN, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive e browser dei file | Scheda SD con molti file: <kbd>↓</kbd> sul desktop apre l'Archive; ogni scheda (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) mostra i propri file; esecuzione, rinomina ed eliminazione delle chiavi |
| Tessere e protocolli | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Aggiornamento di fabbrica | Tramite qFlipper su macOS, Windows 11, Ubuntu; tramite le app Android e iOS; tramite Flipper Lab sul web |
| Provisioning della regione | Gli stessi sei canali dell'aggiornamento di fabbrica, più l'impostazione della regione stessa |
| App | App di base, script JS, il menu sul pulsante Su |
| Conformità | Tutte le schermate di conformità sono mostrate correttamente |

### CLI (3 casi)

- **Comandi di controllo:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1` accende
  un LED sulla devboard), `led b 255`, `vibro 1` / `vibro 0`.
- **Comandi informativi:** collegati con `minicom -D /dev/ttyACM0 -b 230400` oppure con PuTTY; `log debug` mentre usi
  il dispositivo, interrompi con <kbd>Ctrl</kbd>+<kbd>C</kbd>; confronta `device_info` / `!` con la schermata delle
  informazioni sul firmware (tieni premuto <kbd>↓</kbd> sul desktop per 3 s); `bt hci_info`; `date`; `help` / `?`;
  `free`; `free_blocks`.
- **Comandi di storage:** `storage info /ext`, `storage format /ext` (rifiuta, poi conferma), informazioni con e senza
  la scheda; `factory_reset` — rispondendo `n` non accade nulla, con `y` le impostazioni vengono cancellate ma i
  **dati sulla scheda SD e l'ora vengono conservati**.

Valori di riferimento per `bt hci_info` indicati nel piano:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 casi)

| Caso | Verifiche principali |
|---|---|
| Read RAW | Registrazione su 315, 433, 868 MHz, incluso un telecomando cifrato (rolling code) come Came Atomo; riproduzione verso i ricevitori del banco di prova |
| Frequency Analyzer | Mostra la frequenza corretta di diversi telecomandi |
| Modulo esterno | CC1101 esterno (modulo a 433,92 MHz): l'icona passa a esterno, il segnale di Read RAW è più forte di quello interno; il ritorno all'interno funziona. Non scollegare mai il modulo mentre è in uso — il Flipper può bloccarsi |
| File salvati | Salvataggio di segnali decodificati e RAW, aggiunta ai preferiti e invio da lì, rinomina (resta nei preferiti), eliminazione |
| Ricezione / trasmissione | Lettura su 315,000, 433,920 e 868,350 MHz, poi con il salto di frequenza attivo; invio delle chiavi salvate — i relè del banco (o un secondo Flipper) reagiscono |
| Add Manually | Creazione manuale dei segnali |

### NFC (7 casi)

| Caso | Verifiche principali |
|---|---|
| Unlock NTAG/Ultralight | *Auth as* per entrambi i tipi, avviso per tipo di tessera errato, inserimento manuale della password; le tessere salvate compaiono in *Saved* dopo circa 1,5 s |
| Detect Reader | Raccolta di nonce da un lettore (per esempio un altro Flipper), poi la schermata con il codice QR su <kbd>OK</kbd> è leggibile |
| Emulazione | Leggibile da diversi lettori, compreso un Flipper a 10 mm e un Proxmark |
| Lettura | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, carte bancarie EMV |
| Temporizzazione | Confronto delle temporizzazioni di emulazione di Ultralight e Classic con un riferimento, usando un Proxmark 3 |
| Add Manually | Creazione e salvataggio di tessere di tutti i tipi, poi emulazione |
| Azioni aggiuntive | *Read Specific Card Type*, *MIFARE Classic Keys* (aggiunta/eliminazione di chiavi, il pulsante *List*), *Unlock SLIX* con password |

Comandi Proxmark usati per il test di temporizzazione:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### RFID 125 kHz (9 casi)

Casi relativi ai protocolli con i passaggi condivisi per **EM-Marine EM4100, Motorola Indala26, HID H10301
(Picopass), Indala26, Troyka/Podorozhnik**, più Lettura, scrittura su **T5577**, Add Manually ed Emulazione.

### iButton (9 casi)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: lettura, salvataggio, Add Manually, emulazione
(letta da dispositivi diversi), scrittura su una vergine **RW2004** e rilettura, modifica ed eliminazione delle
chiavi.

### Infrarossi (3 casi)

- **Libreria universale** — telecomandi di TV, audio, climatizzatori: l'accensione e le altre funzioni funzionano.
- **Learn new remote** — aggiunta/eliminazione di telecomandi e pulsanti, rinomina, trasmissione dei pulsanti
  modificati.
- **Telecomandi salvati** — aggiunta di pulsanti a un telecomando esistente, controllo dei dispositivi da **almeno
  5 m**, eliminazione di tutti i pulsanti e telecomandi.

### Bad USB (2 casi)

Su macOS e Windows: l'elenco degli script compare; lo script dimostrativo viene eseguito con il layout EN e anche
dopo il cambio di layout; lo script "qFlipper download" apre un terminale e scarica qFlipper; passando alla modalità
**BLE** (Bluetooth attivo) l'associazione con il computer avviene e lo script viene eseguito di nuovo.

### GPIO (1 caso)

`GPIO → Manual Control` con la devboard ST-Link inserita: i LED seguono i pin; abilitando i 5 V si accendono i LED di
alimentazione.

### GoodFAPs — app ufficiali (10 casi)

| App | Verifiche principali |
|---|---|
| PicoPass | Lettura della tessera, salvataggio, avvio di *Elite Dictionary Attack* |
| Weather Station | Legge una stazione meteo simulata da un secondo Flipper su frequenze diverse |
| App dal catalogo | Installazione tramite app mobile o web, icona e nome corretti, avvio/uscita, aggiornamento, disinstallazione (dall'app, dal web, dal browser dei file) |
| AVR Flasher | Dump AVR, Flash AVR, programmatore ISP con `avrdude` |
| Video Game Module | Inserimento del modulo → messaggio di inizializzazione e icona nella barra di stato; l'HDMI rispecchia lo schermo; "Air Arkanoid" usa l'accelerometro |
| Tools | Clock (a schermo intero, formato dalle impostazioni); NFC/RFID Detector rileva entrambi i tipi di campo |
| Signal Generator | Generatori PWM e Clock su pin, frequenze e divisori diversi |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (con avviso sui rischi), *Wipe* |
| SPI Mem Manager | Lettura, scrittura e cancellazione di un chip di flash SPI |
| Flashing del VGM | App VGM Tool: *Install official firmware*, installazione da un file sulla SD e la via manuale (pulsante Boot + archiviazione di massa USB) |

Collegamenti di AVR Flasher usati nel piano:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Verifica della lettura dei fuse (sostituisci `m2560` con il tuo chip, per esempio `m328p`, e la porta COM):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
Il piano proviene dal firmware ufficiale. Su Unleashed metti alla prova anche le aggiunte esclusive di Unleashed nel
sottosistema che hai modificato — per esempio i protocolli Sub-GHz aggiuntivi e la
[modalità contatore](/it/subghz/counter-mode), oppure le app aggiuntive in `applications/system/` (Remote Analyzer,
Nice-O-Code, Sec+ PIN, Seed Capturer, editor RAW Sub-GHz, T5577, SIM800…).
:::

## Pagine correlate

- [Unit test](/it/dev/unit-tests)
- [Interfaccia a riga di comando](/it/dev/cli)
- [Compilare il firmware](/it/dev/build)
