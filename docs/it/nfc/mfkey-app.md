---
title: L'app MFKey
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# L'app MFKey (MFKey 4.1)

**MFKey** (di [@noproto](https://github.com/noproto)) recupera le chiavi MIFARE Classic **direttamente sul Flipper** a
partire dai nonce raccolti dall'app NFC: nonce del lettore (MFKey32) e nonce della carta provenienti dagli attacchi
nested. È lo strumento per quando non hai né telefono né PC a portata di mano; è più lenta di
[qUnleashed](/it/nfc/qunleashed), ma funziona dappertutto, anche in tasca.

| | |
|---|---|
| Posizione | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Versione in Unleashed | **4.1** |
| Ingressi | `/ext/nfc/.mfkey32.log` (nonce del lettore), `/ext/nfc/.nested.log` (nonce della carta) |
| Uscita | `/ext/nfc/assets/mf_classic_dict_user.nfc` (chiavi), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (candidate SEN) |

## Utilizzo

1. Raccogli prima i nonce:
   - da un lettore: [MFKey32](/it/nfc/mfkey) (`Extract MFC Keys`);
   - dalla carta: [attacchi nested](/it/nfc/nested-fudan) durante `NFC → Read`.
2. Apri `Main Menu → Apps → NFC → MFKey`, oppure premi **Run** nella schermata *"Now run Mfkey32 to extract keys"*
   dell'app NFC (compare dopo `Extract MFC Keys` e dopo `Crack nonces in MFKey32`).
3. La schermata dice **Ready**. <kbd>→</kbd> **Help** mostra *"Collect nonces by reading tag or reader in NFC app"*.
   Premi <kbd>OK</kbd> **Start**.
4. Prima MFKey confronta i nonce con i dizionari esistenti: **Dict solves: N (in progress)**, **Keys in dict: N**. I
   nonce la cui chiave è già nota vengono saltati.
5. Poi l'attacco procede con tre barre di avanzamento: **Cracking: X/Y**, **Round: X/Y – ETA NN Sec** e
   **Total ETA NNN Sec**. La riga **RAM** in alto mostra l'heap libero.
6. Al termine senti un segnale acustico e vedi **Complete**, **Keys added to user dict: N** e, per i nonce static
   encrypted, **SEN key candidates: N**.
7. Torna all'app NFC e rileggi la carta (oppure `Saved → <carta> → Unlock with Dictionary`).

<kbd>←</kbd> interrompe il lavoro ed esce (il thread viene fermato in modo pulito; le chiavi trovate fino a quel
momento vengono comunque scritte).

### Errori

| Schermata | Significato |
|---|---|
| **No nonces found** | Non esiste né `.mfkey32.log` né `.nested.log`. Raccogli prima i nonce. Compare anche per i tag che richiedono solo HardNested: i loro nonce non possono essere elaborati sul Flipper. |
| **Nonces already cracked** | Ogni nonce nei log è già risolto da una chiave presente nei tuoi dizionari. |
| **No free RAM** | Memoria insufficiente. Riavvia il Flipper e riprova; chiudi le altre app. |

## Cosa ha cambiato MFKey 4.x

Dall'articolo di @gromovyna "MFKey 4.1 — più veloce, più in alto, più forte": la nuova versione maggiore è arrivata
piuttosto in silenzio, e tuttavia porta un grosso aumento di velocità. È disponibile nelle **build dev di Unleashed
dalla 1251**. (All'epoca dell'articolo le modifiche all'app erano state integrate anche nel firmware ufficiale, ma non
le modifiche lato firmware di cui ha bisogno.) Grazie a @noproto e al suo team.

Qui sotto, **SEN** = static encrypted nonce (vedi [Attacchi nested](/it/nfc/nested-fudan)).

**4.0**

- Supporto del nuovo formato del dizionario SEN: il recupero delle chiavi è **10 volte più rapido**.
- Il vecchio formato del dizionario SEN non è più supportato.

**4.1**

- Recupero delle chiavi un altro **40% più rapido**; migliore efficienza di memoria.
- Il file monolitico `mfkey.c` è stato suddiviso in moduli: `mfkey_batch_prelude`, `mfkey_state_expansion`,
  `mfkey_bs_verify`, `mfkey_recovery`, `mfkey_dedup`.
- 32 candidate verificate in parallelo tramite SWAR (operazioni sui bit invece di controlli uno alla volta).
- Una "Super-LUT" precalcolata da 2 KB per i round 0–3: un solo accesso indicizzato per round invece del calcolo.
- Radix sort O(n) invece di quicksort; deduplicazione tramite hashing di Fibonacci invece di una scansione ingenua.
- I registri della FPU dell'M4 vengono usati come spazio di appoggio aggiuntivo (`vmov`), riducendo la pressione sui
  registri.
- Un ciclo in stile dispositivo di Duff srotolato 8 volte durante la ricerca dei duplicati.

### Tempi reali

L'autore ha provato il caso più difficile: un tag con **nonce static encrypted**. Per questi tag le chiavi calcolate
non vengono verificate al volo e non finiscono direttamente nel dizionario utente; viene invece costruito un dizionario
di **candidate** che va poi verificato sul tag. Quindi vengono estratte **tutte** le chiavi che potrebbero produrre un
nonce: il dizionario più grande, lo scenario più lungo. Nessun *Out Of Memory* durante i test.

| Test | Configurazione | Risultato |
|---|---|---|
| Chiave Iron Logic | Tag cifrato con una carta oggetto [Iron Logic](/it/nfc/iron-logic); nessuna chiave nel dizionario, attaccato tramite la backdoor; **18 chiavi uniche su 32 settori** | Ciclo completo **6 h 8 min**, più di **1,2 milioni di candidate**; poi diverse ore in più per verificare le candidate sul tag. |
| 1 settore, 2 chiavi | Lo stesso tag (azzerato), settore 0 cifrato con chiavi A e B casuali e diverse | **17 minuti**; anche la verifica delle candidate su un solo settore è stata rapida. |

Per confronto, recuperare il primo test su un Proxmark3 con un computer ha richiesto 24 secondi, quindi il Flipper non
potrà mai competere. Ma se sei in viaggio o hai semplicemente tempo per un lavoro in background, il Flipper in tasca
può recuperare le chiavi ed emulare il tag. E dato che per lo più sono i sistemi in stile Iron Logic ad amare la
diversificazione delle chiavi, la probabilità di incappare nello scenario più lungo è relativamente bassa.

::: tip Unleashed
Unleashed include MFKey 4.1 con le modifiche lato firmware di cui ha bisogno (il dizionario CUID in `Read`, con una
barra di avanzamento durante il caricamento). Dopo che MFKey ha finito su un tag SEN, usa **Save Keys to Dictionary**
sul dump letto completamente per copiare le chiavi recuperate nel tuo dizionario utente, vedi
[MIFARE Classic](/it/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Consigli

- Pulisci `/ext/nfc/.nested.log` e `/ext/nfc/.mfkey32.log` dopo un recupero riuscito: i nonce vecchi vengono
  riverificati a ogni avvio.
- Se hai installato le app separatamente, assicurati che un vecchio `mfkey.fap` non abbia sovrascritto quello del
  firmware.
- Alternative molto più rapide: [qUnleashed](/it/nfc/qunleashed) su telefono/PC, oppure il progetto
  [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli).

## Pagine correlate

[MFKey32](/it/nfc/mfkey) · [Attacchi nested](/it/nfc/nested-fudan) · [qUnleashed](/it/nfc/qunleashed) ·
[MIFARE Classic](/it/nfc/mifare-classic)
