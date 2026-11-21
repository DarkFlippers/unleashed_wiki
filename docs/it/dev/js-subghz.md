---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Modulo Sub-GHz

Un extra di Unleashed, assente nel firmware di serie. Dà allo script la radio Sub-GHz: passaggio tra ricezione e riposo, lettura del livello del segnale, cambio di frequenza, trasmissione di un file `.sub` salvato.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` cerca prima un modulo CC1101 esterno e, se non lo trova, usa la radio interna. Finché non è stato eseguito, ogni altro metodo genera l'errore `Radio is not setup`.

Script di esempio: `/ext/apps/Scripts/js_examples/subghz.js`.

## Metodi

### setup()
Inizializza la radio e sceglie il dispositivo. Parte a 433920000 Hz nello stato `IDLE`. Genera un errore se la radio è già inizializzata.

### end()
Mette la radio in sleep e rilascia il dispositivo. Avviene da sé alla fine dello script. Chiamare `setup()` dopo di esso fa cercare di nuovo un modulo esterno.

### setRx()
Porta la radio in ricezione.

### setIdle()
Porta la radio a riposo. La frequenza si può cambiare solo in questo stato.

### getRssi()
Livello del segnale sulla frequenza corrente, in dBm.

- **Restituisce:** `number`, oppure `undefined` se la radio non è in RX.

### getState()
- **Restituisce:** `"RX"`, `"TX"` o `"IDLE"`.

### getFrequency()
- **Restituisce:** la frequenza corrente in Hz, come numero.

### setFrequency()
Sintonizza la radio. Genera un errore se la radio non è in `IDLE` o se la frequenza è fuori dalle bande supportate dal dispositivo.

- **Parametri:** `frequency`, un numero in Hz — per esempio `433920000`.
- **Restituisce:** la frequenza su cui la radio si è davvero sintonizzata. Un CC1101 non può centrare qualunque valore, quindi prende il più vicino che riesce a ottenere.

### isExternal()
- **Restituisce:** booleano — `true` quando è in uso un CC1101 esterno, `false` per la radio interna.

### transmitFile()
Invia un file `.sub`. Frequenza e modulazione arrivano dal file, non da `setFrequency()`. Restituisce `true`; a ogni problema (file mancante, intestazione errata, frequenza non supportata, preset sconosciuto) genera un errore. Alla fine la radio resta in `IDLE`.

- **Parametri:**
  - `path`: percorso completo del file, per esempio `"/ext/subghz/0.sub"`;
  - `repeat` (facoltativo): quante volte inviarlo.

Senza `repeat`, i file RAW partono una volta e quelli con protocollo 10 volte, il che imita la pressione prolungata del tasto su un telecomando vero. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` e `Power Smart` inviano già più pacchetti per ripetizione, quindi per loro il valore predefinito è 1.

## Esempio

Ascolta su 433.92 MHz, poi invia una chiave salvata:

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## Pagine correlate

- [Formato dei file Sub-GHz](/it/subghz/file-format) — cosa c'è dentro un `.sub`
- [Moduli CC1101 esterni](/it/subghz/external-cc1101)
- [Panoramica su JavaScript](/it/dev/js-about)
