---
title: Aggiungere chiavi manualmente
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Aggiungere chiavi a 125 kHz manualmente

Puoi creare una chiave senza avere il tag fisico: scegli il protocollo e digita i suoi dati. Il risultato viene
salvato come una chiave letta e può essere emulato o [scritto su una vergine](/it/rfid/write).

**Da usare quando** conosci il numero stampato su una tessera o presente in un database di controllo accessi, quando
vuoi ricostruire una chiave partendo da appunti o quando devi provare un lettore con un ID specifico.

## Procedura

1. Vai su `Main Menu → 125 kHz RFID → Add Manually`.
2. Scegli il protocollo / formato dall'elenco (vedi sotto).

   ![Elenco dei tipi di tag in Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 e Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Per i formati che prevedono una struttura con facility code / numero di tessera ti viene proposta una scelta:
   - **Enter FC/ID** — digita i campi decimali uno per uno. L'intestazione mostra il nome del campo e l'intervallo
     ammesso, per esempio `Facility Code (0-255)`. <kbd>Back</kbd> torna al campo precedente.
   - **Enter Hex Data** — digita i byte grezzi.

   Gli altri protocolli passano direttamente all'editor esadecimale *Enter the data in hex*.

   ![L'editor "Enter the data in hex" con i byte del tag sopra una tastiera esadecimale a schermo](/screens/lfrfid/add_manually_data.png)

4. Inserisci un nome e salva. La chiave viene memorizzata come `/ext/lfrfid/<name>.rfid`.

Per modificare in seguito una chiave salvata: `Saved` → chiave → **Edit** (editor esadecimale, stesso nome di file).

::: tip Unleashed
L'inserimento di **facility code / numero di tessera** invece dell'esadecimale, i formati **HID** aggiuntivi e
**Casi-Rusco** sono aggiunte di Unleashed. Il firmware di serie accetta solo l'esadecimale. I checksum e la parità
Wiegand vengono calcolati automaticamente.
:::

## L'elenco, nell'ordine del dispositivo

| Voce di menu | Salvato come (`Key type`) | Inserimento | Byte esadecimali |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID o hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID o hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID o hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID o hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID o hex | 4 |
| AWID | AWID | FC/ID o hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID o hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID o hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Intervalli dei campi per "Enter FC/ID"

| Formato | Campi (decimali) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (memorizzati negli ultimi 3 byte, i primi 2 byte a zero) |
| HID H10301 (Wiegand a 26 bit) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (formato a 26 bit, parità aggiunta) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 bit, parità e CRC aggiunti) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (checksum aggiunto) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (come li stampa il sistema di accesso; salvato come EM4100/32) |
| HID H10304 (37 bit) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 bit) | solo Card Number (35 bit) |
| HID S10401 (37 bit) | Facility Code 0–63, Card Number (29 bit) |
| HID H10306 (34 bit) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 bit) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Numeri di tessera molto grandi
L'input numerico contiene un valore a 32 bit con segno, quindi la parte più alta di un campo più ampio di 31 bit (per
esempio il numero di tessera a 35 bit di H10302) può essere inserita solo tramite **Enter Hex Data** / **Edit**.
:::

## Suggerimenti

- Un numero EM4100 stampato come `0001234567` è di solito la forma **DEZ 10**; dopo il salvataggio confrontalo nella
  schermata **Info** (che mostra FC/Card, DEZ 8 e DEZ 10) per essere sicuro di aver digitato il valore giusto.

  ![Schermata Info di un tag salvato: nome del file, EM-Micro EM4100, dati esadecimali, FC/Card, DEZ 8 e DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 e EM4100/16 sono lo stesso frame a bit rate RF/32 e RF/16; scegli quello con cui l'originale viene letto.
- Per i protocolli con solo inserimento esadecimale, il modo più semplice per ottenere byte corretti è leggere una
  volta il tag reale e copiare il valore `Hex:`.

## Pagine correlate

- [Protocolli](/it/rfid/protocols) · [Formato dei file](/it/rfid/file-format) · [Scrittura](/it/rfid/write) ·
  [Lettura](/it/rfid/read)
