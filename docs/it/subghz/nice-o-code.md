---
title: App Nice O-Code
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# App Nice O-Code

**Nice O-Code** (di @xMasterX) recupera il **codice installatore (IC)** a 16 bit di un telecomando Nice O-Code e salva il telecomando come file `.sub` — sia come semplice clone, sia come **nuovo telecomando** della stessa installazione, che puoi registrare nel ricevitore.

## Contesto

Nice O-Code è un Nice FloR-S cifrato con un codice installatore: un valore condiviso da tutti i telecomandi di un'installazione. Il ricevitore accetta solo un telecomando che porti il suo codice installatore. Una sola pressione catturata non basta a trovarlo, ma **quattro o più pressioni** dello stesso telecomando sì: solo il codice corretto fa sì che ogni pressione decodifichi sullo stesso seriale. L'app raccoglie le pressioni e prova in forza bruta tutti i 65 536 codici direttamente sul Flipper.

Alcuni telecomandi O-Code portano anche il **certificato** del ricevitore (un pacchetto più lungo, da 112 bit, inviato solo durante i primi venti utilizzi del telecomando). Quando l'app ne vede uno, lo smaschera una volta noto l'IC e lo mostra come `Cert`.

::: tip Unleashed
Nice O-Code è un'app di sistema integrata di Unleashed, e l'app Sub-GHz può decodificare e inviare telecomandi O-Code una volta che un file contiene l'IC. `Add Manually` ha le voci corrispondenti `Nice O-Code`, `Nice O-Code One` e `Nice O-Code+Crt` — vedi [Add Manually](/it/subghz/add-manually) e [Il Flipper come nuovo telecomando](/it/subghz/remote-prog).
:::

::: warning
Usala solo con la tua installazione. Un clone condivide il contatore con il telecomando originale e i due entreranno in conflitto (vedi [Codici rolling](/it/subghz/rolling-codes)).
:::

## Requisiti

- Il file di chiavi Nice FloR-S `/ext/subghz/assets/nice_flor_s` sulla scheda SD (viene distribuito con il firmware).
  Senza di esso l'app segnala `No rainbow table`.
- Un telecomando O-Code funzionante dell'installazione. L'app ascolta su **433.92 MHz AM650**, con la radio interna o
  con una [esterna](/it/subghz/external-cc1101) (`Int` / `Ext` nell'intestazione).

## Acquisire un telecomando

1. Apri `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Scegli `Capture remote`. Lo stato mostra `Listening 433.92`.
3. Premi il tasto del telecomando **4 o più volte — pressioni brevi, non tenerlo premuto**. Ogni nuova pressione
   mostra `Press N: …`; la riga `Presses n/4  Xpkt` e la barra di avanzamento si riempiono. Se il telecomando ha un
   certificato, la riga termina con `+Crt`.
4. Quando sono state raccolte 4 pressioni compare `Solve` — premi <kbd>OK</kbd>.
5. La schermata mostra `Trying installer codes` con un contatore fino a 65536. <kbd>←</kbd> (`Cancel`) lo ferma.
6. In caso di successo vedi `IC XXXX`, `Serial XXXXXXX` e, se presente, `Cert XXXXXX`.

Stati che possono comparire durante l'acquisizione:

| Stato | Significato |
|---|---|
| `Not O-Code, ignored` | un pacchetto che non è O-Code (per esempio un normale telecomando FloR-S) |
| `Same press, ignored` | la ripetizione di una pressione già memorizzata |
| `Need 4+ packets` | pressioni insufficienti per risolvere |
| `Ambiguous, capture more` | più codici sono compatibili — premi il telecomando qualche altra volta e risolvi di nuovo |
| `No code fits, not O-Code?` | nessun codice installatore corrisponde — probabilmente non è un telecomando O-Code, oppure sono state mescolate pressioni di telecomandi diversi |

## Salvataggio

Nella schermata del risultato:

- <kbd>OK</kbd> (`Save`) — un **clone** del telecomando acquisito (nome predefinito `NiceO`). Utile per i test, ma
  entra in conflitto con l'originale per il contatore.
- <kbd>→</kbd> (`New`) — un **nuovo telecomando**: lo stesso codice installatore, tasto e certificato, ma con seriale
  e contatore propri (nome predefinito `NiceO_new`). È questo quello da registrare nel ricevitore. Il contatore viene
  impostato vicino, e un po' sotto, al conteggio del tuo telecomando funzionante.

Entrambi vengono scritti in `/ext/subghz/` dopo che li hai nominati (`Name the .sub file`). Aprili in
`Sub-GHz → Saved`.

Per registrare il nuovo telecomando, segui la procedura Nice FloR-S in
[Il Flipper come nuovo telecomando](/it/subghz/remote-prog). Un telecomando con certificato si registra da sé: premi
il suo tasto circa una volta al secondo, **10–15 volte di seguito** — il cancello si apre intorno alla decima
pressione.

## Decode RAW file

`Decode RAW file` esegue lo stesso recupero su un `.sub` RAW registrato in precedenza con
[Read RAW](/it/subghz/read-raw) (registra 4 o più pressioni separate). Un file chiave viene rifiutato con
`Not a RAW capture`. La barra di avanzamento mostra a che punto è nel file.

## Risoluzione dei problemi

- **`No rainbow table`** — manca `/ext/subghz/assets/nice_flor_s`; reinstalla il firmware con la scheda SD inserita,
  oppure ripristina la cartella assets.
- **Le pressioni non vengono contate** — fai pressioni brevi e separate; tenere premuto il tasto ripete la stessa
  pressione.
- **Un ricevitore appena uscito di fabbrica ignora il telecomando O-Code** — un ricevitore intonso non ha codice
  installatore; registra invece un normale telecomando `Nice One` / `Nice FloR-S` tramite il tasto (vedi
  [Il Flipper come nuovo telecomando](/it/subghz/remote-prog)).
- **Il ricevitore rifiuta il nuovo telecomando** — mantieni il contatore vicino a quello del tuo telecomando
  funzionante; non azzerarlo.

## Pagine correlate

- [Il Flipper come nuovo telecomando](/it/subghz/remote-prog) · [Add Manually](/it/subghz/add-manually)
- [Codici rolling](/it/subghz/rolling-codes) · [Sistemi supportati](/it/subghz/supported-systems)
