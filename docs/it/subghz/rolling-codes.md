---
title: Codici rolling
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Codici rolling

I telecomandi Sub-GHz sono di due tipi:

- **Codice statico (fisso)** — ogni pressione invia esattamente lo stesso pacchetto (Princeton, CAME 12/24 bit,
  Nice Flo, Marantec, Roger, Gate TX…). Una copia è identica all'originale; entrambi continuano a funzionare per
  sempre, in qualsiasi ordine. Basta un [Read](/it/subghz/read) e salvare.
- **Codice rolling (dinamico)** — ogni pressione invia un nuovo pacchetto costruito a partire da un **contatore** che
  cresce di uno a ogni pressione (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+, Alutech AT-4N…). Il
  contatore è di solito cifrato, quindi il codice successivo si può calcolare solo se il firmware conosce la chiave
  del protocollo.

::: tip Unleashed
Unleashed può decodificare, salvare **e inviare** molti protocolli a codice rolling, creare nuovi telecomandi per essi
con [Add Manually](/it/subghz/add-manually), inviare gli altri tasti del telecomando con i tasti freccia
([tasti personalizzati](#custom-buttons)) e regolare l'incremento del contatore
([Counter Incr.](#counter-increment), [Modalità contatore](/it/subghz/counter-mode)). Il firmware di serie ne
decodifica la maggior parte ma non li trasmette.
:::

## Come il ricevitore controlla il contatore

Il ricevitore memorizza l'ultimo contatore accettato **per ogni telecomando** (un valore per telecomando, non per
tasto):

- contatore **uguale al successivo atteso / entro la finestra in avanti** → accettato, il cancello si apre;
- contatore **molto più avanti** → molti ricevitori si risincronizzano: la prima pressione viene memorizzata, la
  successiva consecutiva funziona;
- contatore **indietro** rispetto al valore memorizzato → ignorato. Alcuni ricevitori disaccoppiano un telecomando dopo
  ripetuti codici "vecchi".

## Il conflitto di contatore

*Perché non si può semplicemente catturare il proprio telecomando a codice rolling in Read e usarlo dal Flipper?*
(adattato da [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Immagina:

1. Premi il telecomando originale — invia il contatore `0002`.
2. Hai salvato quel segnale sul Flipper; quando lo invii, il Flipper invia `0003`.
3. Il ricevitore pensa che tu abbia semplicemente premuto di nuovo l'originale, e apre.
4. Ma il telecomando originale è ancora a `0002`; la sua pressione successiva è `0003` — un valore che il ricevitore ha
   già visto, quindi **non apre**.

Niente panico: il telecomando non è stato disaccoppiato. Premilo di nuovo: `0004` supera il Flipper e l'originale
funziona di nuovo. Ma queste "corse" possono allontanare i contatori di 100 pressioni o più, e a quel punto l'originale
non si recupera senza riaccoppiarlo al ricevitore.

Vie d'uscita:

- **La migliore: creare un nuovo telecomando** sul Flipper (`Sub-GHz → Add Manually`) e registrarlo nel ricevitore. Ha
  un seriale e un contatore propri e non entra mai in conflitto con gli originali. Vedi
  [programmazione del telecomando](/it/subghz/remote-prog).
- Decidi quale usare — il Flipper **o** l'originale — e usa solo quello.
- Usali entrambi, ma non lasciare mai che i contatori si allontanino troppo (premi qualche volta quello rimasto
  indietro).
- Sperimentale: per alcuni ricevitori particolari [modalità contatore](/it/subghz/counter-mode) permettono a un clone e
  all'originale di coesistere.

::: danger Automobili
Non clonare la radiochiave di un'auto. Riprodurla (anche tramite Read RAW) può desincronizzare la chiave o farla
finire in blacklist, e il riaccoppiamento richiede spesso gli strumenti di assistenza del concessionario.
:::

## Tasti personalizzati {#custom-buttons}

Quando un file a codice rolling supportato (o qualche file statico) è aperto in `Emulate`:

- <kbd>OK</kbd> (`Send`) invia il tasto che è stato registrato / generato;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> inviano **altri codici tasto** dello stesso telecomando, con un
  contatore incrementato correttamente, mentre sono tenuti premuti. Il codice tasto originale è mostrato come una
  piccola cifra esadecimale a destra dello schermo mentre si usa una freccia.

Quale freccia corrisponda a quale tasto dipende dal protocollo; anche i tasti nascosti / di programmazione (per
esempio `0xF` su BFT Mitto, `Prog` su Somfy) sono raggiungibili in questo modo — la tabella completa è in
[programmazione del telecomando](/it/subghz/remote-prog) (riferimento dei tasti nascosti).

Protocolli con tasti personalizzati nel firmware attuale (il numero indica quanti codici aggiuntivi possono inviare le
frecce):

| Protocollo | Extra | Protocollo | Extra |
|---|---|---|---|
| KeeLoq (tutti i produttori `KL:`) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (programmazione) |
| Somfy Keytis | 1 (`Prog`) | | |

## Incremento del contatore {#counter-increment}

`Sub-GHz → Radio Settings → Counter Incr.` imposta di quanto cresce il contatore a ogni trasmissione: `+1`
(predefinito), `+2`, `+3`. Con la **modalità Debug** abilitata (`Settings → System → Debug`) l'elenco si estende a
`+4`, `+5`, `+10`, `+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50` — strumenti per lo sviluppo dei protocolli; non usarli su
un'installazione reale. Vedi [Radio Settings](/it/subghz/settings).

## Programmare un nuovo telecomando nel ricevitore

Il modo normale e senza conflitti di usare il Flipper con un cancello a codice rolling:

1. Leggi il tuo telecomando originale (`Sub-GHz → Read`) per conoscere protocollo, frequenza e modulazione.
2. `Sub-GHz → Add Manually` → il tuo sistema → la stessa banda → salva.
3. Metti il ricevitore in modalità di apprendimento (tasto sulla scheda, oppure da un telecomando funzionante — il
   Flipper invia il tasto "programmazione" nascosto con un tasto freccia).
4. Apri il nuovo file e tieni premuto <kbd>OK</kbd>.

Procedure per singolo produttore: **[Il Flipper come nuovo telecomando](/it/subghz/remote-prog)**.

## Risoluzione dei problemi

- **Ha funzionato una volta, poi ha smesso** — stai usando un clone. Premi diverse volte di fila per
  risincronizzare, oppure crea un nuovo telecomando.
- **Il telecomando originale ha smesso di funzionare** — il Flipper è andato avanti. Premi l'originale diverse volte;
  se la distanza è troppo grande, registralo di nuovo al ricevitore.
- **Le frecce non fanno nulla** — il protocollo non ha tasti personalizzati, oppure il file è statico senza campo tasto.
- **`KL: Unknown` dopo un Read** — la chiave del produttore è sconosciuta; il segnale non può essere inviato. Vedi
  [KeeLoq](/it/subghz/keeloq).

::: warning
Usa queste funzioni solo con apparecchiature di tua proprietà o con il permesso del proprietario.
:::

## Pagine correlate

- [Add Manually](/it/subghz/add-manually) · [Il Flipper come nuovo telecomando](/it/subghz/remote-prog)
- [KeeLoq](/it/subghz/keeloq) · [Modalità contatore](/it/subghz/counter-mode)
- [Sistemi supportati](/it/subghz/supported-systems)
