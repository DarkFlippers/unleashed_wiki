---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq è il cifrario che sta dietro a un numero enorme di telecomandi per cancelli, porte di garage e sbarre
(DoorHan, Nice Smilo, FAAC RC, BFT, Came Space, Beninca, Hormann EcoStar…) e ad alcuni vecchi antifurti per auto.
Questa pagina spiega come funziona, cosa sono le "chiavi del produttore" e i "seed" e come li gestisce Unleashed.

La parte teorica è basata sull'articolo **"KeeLoq и с чем его едят"** di
[@li0ard](https://blog.li0ard.rest/wtfiskeeloq), membro del team di ricerca di @gromovyna, consigliato nel
[suo canale](https://t.me/gromovyna/24) a chiunque voglia capire questo cifrario.

## Che cos'è KeeLoq

KeeLoq è un cifrario a blocchi basato su un NLFSR (registro a scorrimento con retroazione non lineare), progettato da
Nanoteq Pty Ltd. e venduto a Microchip Technology Inc. Cifra **blocchi da 32 bit** con una **chiave da 64 bit** in
**528 round**. Implementa il *code hopping*: ogni trasmissione è un pacchetto unico.

### Struttura del pacchetto

Un pacchetto KeeLoq da 64 bit, per esempio `239B3DEBF16C47A6`, è composto da:

- **Fix** (primi 4 byte, `239B3DEB`) — inviati in chiaro: l'ID del tasto (`2`) e il numero di serie a 28 bit del
  telecomando (`39B3DEB`).
- **Hop** (ultimi 4 byte, `F16C47A6`) — cifrati con la chiave del produttore. Decifrati si presentano come
  `21EB000A`: di nuovo l'ID del tasto (`2`), 12 bit di dati di discriminazione (spesso `serial & 0x3FF`) e il
  **contatore a 16 bit** (`000A`).

![Struttura del pacchetto KeeLoq](/img/remote/167cc7293a53adb1.png)

È quello che il Flipper mostra dopo un [Read](/it/subghz/read): `Fix`, `Hop`, `Btn`, `Cnt` e il nome del produttore.

### Logica del contatore

- Il contatore è uguale al valore che il ricevitore si aspetta → comando eseguito.
- Il contatore è **più alto** di quello memorizzato → il ricevitore si risincronizza su di esso e funziona
  normalmente dalla pressione successiva.
- Il contatore è **più basso** → ignorato; alcuni ricevitori disaccoppiano il telecomando dopo diversi valori
  "scaduti". *È questo il vero pericolo quando si fanno esperimenti con KeeLoq.* Vedi
  [Codici rolling](/it/subghz/rolling-codes).

## Modalità di apprendimento (derivazione della chiave)

La chiave che cifra effettivamente l'hop è derivata da una **chiave del produttore** (64 bit, la stessa per tutti i
telecomandi di una marca/linea di modelli). Lo standard definisce tre modalità:

| Modalità | Come viene creata la chiave del singolo telecomando |
|---|---|
| **Simple learning** | la chiave del produttore viene usata così com'è (la più debole) |
| **Normal learning** | la chiave del produttore viene mescolata con il numero di serie del telecomando |
| **Secure learning** | usa un valore aggiuntivo — il **seed** — unico per telecomando e trasmesso solo durante l'accoppiamento (la modalità standard più robusta) |

I produttori inventano anche modalità proprie, per esempio **Magic XOR Type-1** (Beninca: seriale XOR chiave del
produttore) oppure **FAAC SLH (SPA)** — una sequenza di operazioni sui bit e cifrature, la più ragionata di tutte
secondo li0ard.

::: tip Unleashed
Unleashed implementa tutte le modalità standard più molte modalità dei costruttori
(`lib/subghz/protocols/keeloq_common.h`): Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3,
KingGates, Jarolift, Erreka, Pujol, AERF, JCM, JCM Gen2, Stagnoli e l'apprendimento Telcoma basato su tabella. Più di
100 produttori sono elencati in [Sistemi supportati](/it/subghz/supported-systems).
:::

## Le chiavi dei produttori in Unleashed

Per decodificare un segnale KeeLoq il Flipper deve conoscere la chiave del produttore. Unleashed le distribuisce in un
keystore **cifrato** sulla scheda SD:

| File | Scopo |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | chiavi integrate, cifrate (`Encryption: 1`), aggiornate con il firmware |
| `/ext/subghz/assets/keeloq_mfcodes_user` | le **tue** chiavi, in chiaro (crealo da `keeloq_mfcodes_user.example`) |

Quando un segnale viene decodificato, vengono provate tutte le chiavi; in caso di successo il nome compare come
`KL: DoorHan`, `KL: Nice_Smilo` ecc. Se nessuna chiave corrisponde, il segnale viene mostrato come **`KL: Unknown`**:
può essere salvato, ma non inviato né usato per generare il codice successivo. I comandi CLI `subghz` che decodificano
segnali stampano all'avvio `Load_keystore keeloq_mfcodes OK` e `Load_keystore keeloq_mfcodes_user OK` / `Absent` — un
modo rapido per verificare che i keystore vengano caricati.

### Formato del file di chiavi utente

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - manufacture key, 64 bit
# X - learning type: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - iterates over both previous and man in direct and reverse byte sequence
# NAME - name (no spaces), max 64 characters
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Lascia una riga vuota alla fine del file. Il file `_user` non viene sovrascritto dagli aggiornamenti.

### I campi `Manufacture` e `Seed`

Un `.sub` KeeLoq salvato memorizza il produttore per nome:

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

I sistemi con secure learning memorizzano anche `Seed: XX XX XX XX`. Aggiungere a mano le righe `Seed` +
`Manufacture` a un file che viene letto come `KL: Unknown` lo rende decodificabile (vedi BFT/Erreka più sotto).

## Seed: BFT Mitto, Erreka, FAAC SLH, Genius

Questi sistemi usano un **seed** per telecomando (o per installazione); senza di esso il segnale viene letto come
`KL: Unknown` (o non viene decodificato) e non è possibile costruire un telecomando accettato.

- **BFT Mitto** — i telecomandi più recenti derivano il seed dal seriale e vengono decodificati subito in Read
  (`KL: BFT`). Quelli più vecchi hanno un seed unico. Metti l'originale in modalità di programmazione (foro con pin
  sul retro oppure tasti 1+2): invia un pacchetto il cui `Fix` inizia con `F`; l'**`Hop` di quel pacchetto è il seed**
  in chiaro.
- **Erreka IRIS** — ponticella i pin `1` e `5` del connettore a 5 vie sul fianco: di nuovo il `Fix` inizia con `F` e
  l'`Hop` è il seed. Alcune installazioni assegnano lo stesso seed a **tutti** i telecomandi — in quel caso un nuovo
  telecomando deve riutilizzarlo.
- **FAAC SLH / Genius** — leggi il seed da un telecomando **master** in modalità di programmazione; il seed è diverso
  **per ogni tasto**.
- Nessun tasto di programmazione disponibile? Usa l'app **[Seed Capturer](/it/subghz/seed-capturer)**: raccoglie
  coppie Fix/Hop consecutive e il seed viene recuperato nell'app companion qUnleashed.

Con il seed, crea il telecomando in `Sub-GHz → Add Manually [Advanced]` (SERIAL → BUTTON → COUNTER → SEED), vedi
[Add Manually](/it/subghz/add-manually) e [programmazione del telecomando](/it/subghz/remote-prog).

## Attacchi noti (panoramica)

Dall'articolo di li0ard, per capire — non come istruzioni.

**Teorici:** slide attack (~2³² coppie testo in chiaro/testo cifrato, restituisce i primi 32 bit della chiave),
approccio per correlazione (sfrutta uno sbilanciamento di 5/8 dell'NLFSR), passo lineare (gli ultimi 16 bit della
chiave una volta noto il resto). Complessità totale ≈ 2⁵².

**Pratici** (grazie ai materiali di Derek Jamison, "SubGHz Rolling Flaws"):

| Attacco | Idea |
|---|---|
| Replay | rinviare un pacchetto catturato; funziona sui codici statici e sui ricevitori che non controllano il contatore |
| Clonazione del telecomando | con la chiave del produttore si può creare una copia funzionante — ma entra in conflitto con il contatore dell'originale e può portare al suo disaccoppiamento |
| Future | inviare un contatore molto avanti (`0001` → `3E91`); il ricevitore si risincronizza, l'originale resta desincronizzato |
| Rollback | riportare indietro il contatore dopo qualche uso; rari ricevitori si risincronizzano su valori vecchi |
| RollJam | registrare mentre si disturba il ricevitore e usare il codice più tardi. **Il jamming è illegale** in quasi tutti i paesi |
| Chiave del produttore (KGB) | il ricevitore può accettare più chiavi del produttore; si invia il fix originale con un contatore cifrato da un'altra chiave |
| Enc00 | scambiare il fix con quello di un altro telecomando accoppiato e usare l'hop originale; l'altro telecomando si desincronizza |
| Unknown | quando un ricevitore non riesce a decodificare l'hop usa 0; i ricevitori universali possono aprire su 0 |

Nonostante tutto questo KeeLoq — come Mifare Classic con il suo Crypto-1 compromesso — resta popolare nei sistemi di
accesso economici; alcuni costruttori (Beninca, Hormann) sono passati ad AES.

::: warning
Sperimenta solo con telecomandi e ricevitori di tua proprietà. Un telecomando desincronizzato o disaccoppiato può
richiedere una nuova registrazione al ricevitore.
:::

## Risoluzione dei problemi

- **`KL: Unknown`** — nessuna chiave corrispondente. Controlla la modulazione, aggiorna il firmware (nuove chiavi),
  oppure aggiungi una chiave a `keeloq_mfcodes_user` se la possiedi legittimamente. Per i sistemi con seed, recupera
  il seed.
- **Decodifica ma il ricevitore ignora il Flipper** — stai inviando un clone; vedi
  [Codici rolling](/it/subghz/rolling-codes) e [Modalità contatore](/it/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** in Add Manually — il keystore è assente; reinstalla il
  firmware con la scheda SD inserita.

## Pagine correlate

- [Sistemi supportati](/it/subghz/supported-systems) · [Add Manually](/it/subghz/add-manually)
- [Seed Capturer](/it/subghz/seed-capturer) · [Il Flipper come nuovo telecomando](/it/subghz/remote-prog)
- [Modalità contatore](/it/subghz/counter-mode) · [Formato dei file .sub](/it/subghz/file-format)
