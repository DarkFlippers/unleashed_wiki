---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** è un Ultralight con autenticazione mutua **AES-128** al posto di una password (NTAG21x) o
del 3DES (Ultralight C). Ha 60 pagine, tre contatori unidirezionali, una firma di originalità ECC da 48 byte, una
modalità **Random ID** opzionale e un **secure messaging** opzionale (ogni comando e ogni risposta protetti da un
CMAC).

::: tip Unleashed
Il supporto a Ultralight AES (lettura, attacco a dizionario, inserimento manuale della chiave, emulazione,
riscrittura, decodifica della configurazione, Random ID, secure messaging) è una funzione di Unleashed, validata su una
carta MF0AES20 reale confrontandola con i risultati di riferimento di Proxmark3.
:::

## Cosa ne fa il Flipper

| Funzione | Dettagli |
|---|---|
| Identificazione e lettura | Rilevato come `Mifare Ultralight AES`, ATQA `0044`, SAK `00`, `60/60` pagine su una carta aperta, contatori. |
| Firma di originalità | Salvata nel file `.nfc` come riga `AES signature:` (48 byte) e riprodotta durante l'emulazione, così il controllo della firma da parte di un lettore va a buon fine. |
| Autenticazione AES | Challenge-response AES a 3 passaggi, poi le pagine protette vengono lette. |
| Attacco a dizionario | Parte automaticamente su una lettura incompleta: **MFUL AES User Dictionary**, poi **MFUL AES System Dictionary**. |
| Chiave manuale | `Saved → <carta> → Unlock` → **"Enter key in hex"** (16 byte) → confermare con **Unlock**. |
| Gestione delle chiavi | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Riscrittura | **Write (Keep Key)** / **Write (Copy Key)** su un dump letto completamente. |
| Emulazione | Completa, compresa l'autenticazione AES come carta, il gate `AUTH0` e il secure messaging. |
| Decodifica della configurazione | `Info` mostra un blocco **UL-AES Config** (vedi sotto). |
| Random ID | Rilevato e mostrato (`Random ID: on`); **Reveal Real UID** tenta di recuperare l'UID reale. |

Dizionari: di sistema `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (chiave di fabbrica tutta a zero,
`BREAKMEIFYOUCAN!` riusato come AES e altri valori predefiniti comuni presi da Proxmark3), utente
`/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. Una carta di fabbrica usa la chiave tutta a zero
`00000000000000000000000000000000` sia per la DataProtKey sia per la UIDRetrKey.

## Leggere una carta protetta

1. `Main Menu → NFC → Read`, appoggia la carta.
2. Le pagine aperte vengono lette; se la carta ha una regione protetta da AES, l'attacco a dizionario parte da solo
   (prima il dizionario utente, poi quello di sistema).
3. Se una chiave funziona, tutte le pagine vengono lette e la chiave viene mostrata e salvata con il dump. In caso
   contrario ottieni una lettura parziale (per esempio `42/60` pagine) e **"AES-protected pages!"**, senza blocchi e
   senza consumare tentativi su una carta senza limiti.
4. Salva la carta. Più tardi puoi riprovare con **Unlock with Dictionary** (dopo aver aggiunto delle chiavi) oppure con
   **Unlock** (chiave manuale).

::: warning Ordine dei byte della chiave
Le scritture di pagina grezze (per esempio `hf mfu wrbl` di Proxmark3) memorizzano la chiave nell'**ordine della
memoria del tag**; il motore AES, l'inserimento manuale sul Flipper e `hf mfu aesauth --key` di PM3 usano l'ordine
**inverso**. Una carta le cui pagine `0x30–0x33` si leggono come
`A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` si autentica con `AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Inserisci una chiave
recuperata manualmente **nell'ordine AES**. Nel `.nfc` salvato le pagine della chiave (`Page 48`–`51`) sono memorizzate
nell'ordine della memoria del tag, così possono essere riscritte verbatim; la riga `DataProtKey:` a schermo è solo una
rappresentazione.
:::

## Memoria e configurazione

| Elemento | Posizione |
|---|---|
| DataProtKey | pagine `0x30`–`0x33` |
| UIDRetrKey | pagine `0x34`–`0x37` |
| CFG | pagina `0x29`: byte 0 bit0 = `RID_ACT`, bit1 = `SEC_MSG_ACT`; byte 3 = `AUTH0` |
| ACCESS | pagina `0x2A`: byte 0 bit2 = `CNT_RD_EN`, bit3 = `CNT_INC_EN`, bit6 = `CFGLCK`, bit7 = `PROT`; byte 2–3 = `AUTH_LIM` |
| LOCK_KEYS | pagina `0x2D`: byte 0 = bit di lock per chiave |

Il blocco **UL-AES Config** in `Info` li decodifica, per esempio:

- `Auth from: off (open)` oppure `Auth from: page 0x10 (r+w)` / `(write)`: `AUTH0` e `PROT`;
- `Auth limit: unlimited` oppure `Auth limit: N (locks!)`;
- `Counter 2: rd open / inc auth` e simili;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N`;
- `Real UID:` una volta rivelato.

::: danger Non sperimentare con questi bit
`CFGLCK` blocca la configurazione in modo **permanente**, `AUTH_LIM` arma un blocco dopo autenticazioni fallite e i
byte di `LOCK_KEYS` / i lock statici possono brickare la carta. Non modificarli mai su una carta a cui tieni. Nota
inoltre che `hf mfu info` di PM3 etichetta le pagine `0x34`–`0x37` di MF0AES20 con un vecchio template Ultralight
(`cfg0/cfg1/PWD/PACK`); fidati della tabella qui sopra.
:::

## Riscrivere un dump

Proposto solo su un dump Ultralight AES **letto completamente**, come due voci:

- **Write (Keep Key)**: scrive le pagine dati `0x04`–`0x27`; la chiave della carta di destinazione resta.
- **Write (Copy Key)**: pagine dati più la **DataProtKey** (`0x30`–`0x33`) presa dal dump.

Regole integrate nel firmware:

- La scrittura **si autentica prima sulla destinazione** con una chiave di dizionario, quindi la chiave *attuale* della
  destinazione deve trovarsi in un dizionario (la chiave di fabbrica tutta a zero c'è).
- Le pagine di configurazione/lock `0x28`–`0x2F` non vengono **mai** scritte; la UIDRetrKey (`0x34`–`0x37`) non viene
  mai scritta.
- La destinazione deve essere dello stesso **tipo**; l'UID non deve necessariamente corrispondere.

## Emulazione

`Saved → <carta> → Emulate`. La carta emulata risponde a GET_VERSION, alla firma, ai contatori e alla configurazione
come quella reale, esegue l'autenticazione AES in veste di carta usando `reverse(pagine 0x30–0x33)` come chiave,
rifiuta le chiavi errate e applica `AUTH0`. Nota: le letture limitate senza autenticazione restituiscono dati delle
prime pagine per effetto del rollover anziché un NAK.

## Secure messaging (CMAC)

Con `SEC_MSG_ACT` impostato, una volta autenticati **ogni** comando e ogni risposta devono portare un CMAC. Il Flipper
gestisce la cosa in modo adattivo: dopo l'autenticazione la prima `READ`/`WRITE` in chiaro fallisce (il silicio reale
semplicemente non risponde, cosa che il lettore interpreta come un timeout), il firmware si riautentica e passa a
`READ`, `READ_CNT` e `WRITE` incapsulati con MAC. Il contatore dei comandi avanza di 2 per ogni scambio (il comando usa
`CmdCtr`, la risposta `CmdCtr+1`). Validato su hardware: una lettura completa 60/60 su CMAC senza mismatch di MAC,
contatori su CMAC, pagine della chiave `0x30`–`0x37` mascherate a zero nel dump e una riscrittura CMAC delle pagine
dati.

Anche l'emulatore parla il secure messaging: verifica il MAC del comando, incapsula con MAC ogni risposta, sostituisce
l'ACK della `WRITE` con un MAC e chiude la sessione in caso di MAC errato.

::: warning Possibilità di recupero
Una volta attivo `SEC_MSG_ACT`, le scritture di configurazione in una regione protetta richiedono una scrittura
autenticata con CMAC, cosa che Proxmark3 non può fare e che la Write del Flipper salta (le pagine di configurazione non
vengono mai scritte). Non impostare `AUTH0 ≤ 0x29` su una carta con secure messaging, altrimenti potresti non essere
più in grado di disattivarlo.
:::

### Marcatori di debug

Con `Settings → System → Log Level → Debug` puoi seguire nel log cosa accade, per esempio
`UL-AES: plain read failed post-auth, switching to secure messaging`, `UL-AES response MAC mismatch (ctr N)` (non
dovrebbe comparire in un'esecuzione sana), `UL-AES command MAC mismatch, dropping session` (lato emulatore).

## Pagine correlate

[Sbloccare le carte con password](/it/nfc/unlock-with-password) · [Leggere le carte](/it/nfc/read) ·
[Formato dei file NFC](/it/nfc/file-format) · [Aggiungere carte manualmente](/it/nfc/add-manually)
