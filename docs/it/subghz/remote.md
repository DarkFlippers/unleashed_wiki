---
title: App Sub-GHz Remote
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** trasforma il Flipper in un telecomando a cinque tasti. Associ fino a cinque file `.sub` salvati a <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> e <kbd>OK</kbd>, dai a ciascuno un'etichetta e poi li invii con una sola pressione, senza navigare in `Sub-GHz → Saved`.

::: tip Unleashed
Sub-GHz Remote è integrata in Unleashed e sta nel **menu principale**: `Main Menu → Sub-GHz Remote`. L'hanno scritta @gid9798 e @xMasterX, e il suo codice vive in un repository separato, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), incluso nel firmware come submodule. Nel firmware di serie non c'è nel menu; per il firmware ufficiale esiste una build a parte nel catalogo delle app.
:::

## Quando usarla

- Usi continuamente alcuni segnali, per esempio un cancello, una porta di garage e una sbarra, e li vuoi a una pressione di distanza.
- Controlli più dispositivi (ventilatore, luci, campanello) e li vuoi su una sola schermata con etichette leggibili.

Ogni tasto invia un normale file `.sub`, quindi tutto ciò che funziona da `Sub-GHz → Saved → Emulate` funziona anche qui: chiavi statiche, telecomandi a codice rolling creati con [Add Manually](/it/subghz/add-manually), registrazioni RAW e BinRAW. I protocolli che il Flipper può solo ricevere non si possono associare.

## Il menu

L'app apre subito il browser dei file di mappa. Premi <kbd>Back</kbd> per arrivare al menu:

| Voce | Cosa fa |
|---|---|
| `Open Map File` | scegli una mappa e vai alla schermata del telecomando |
| `Edit Map File` | scegli una mappa e aprila nell'editor |
| `New Map File` | scrivi un nome e costruisci una nuova mappa |
| `Set Default` | scegli la mappa che d'ora in poi l'app apre da sé |
| `Clear Default` | dimentica di nuovo quella mappa (compare solo se ne è impostata una) |

Le mappe sono file `.txt` nella cartella `subghz_remote` della scheda SD. Il nome del file non conta e puoi tenere quante mappe vuoi. Se hai una vecchia cartella `unirf` dalle versioni precedenti, al primo avvio l'app la sposta in `subghz_remote`.

## Creare una mappa sul Flipper

L'app ha un editor integrato, quindi non serve un PC.

1. Salva prima i segnali che ti servono, con [Read](/it/subghz/read), [Read RAW](/it/subghz/read-raw) o [Add Manually](/it/subghz/add-manually).
2. Apri `Main Menu → Sub-GHz Remote`, premi <kbd>Back</kbd> e scegli `New Map File`.
3. Scrivi un nome, fino a 25 caratteri. La mappa diventa `/ext/subghz_remote/<name>.txt`.
4. L'editor si apre sullo slot `UP`.

| Tasto nell'editor | Cosa fa |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | spostati tra i cinque slot: `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — apre il menu dello slot |
| <kbd>→</kbd> | `Save` — va all'anteprima |
| <kbd>←</kbd> o <kbd>Back</kbd> | `Back` |

La barra in alto mostra il nome dello slot e la sua etichetta. Sotto vedi il percorso del file associato a quello slot, oppure `Button not set` se lo slot è vuoto, oppure `ERR:` con il motivo: `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

Il menu dello slot ha quattro voci:

- `Edit Label` — il testo mostrato per questo tasto. Fino a 25 caratteri, di cui sullo schermo del telecomando ne entrano circa 16. Un'etichetta vuota è ammessa, l'app chiede prima `Empty Label Name / Continue?`; senza etichetta mostra il nome del file.
- `Edit File` — un browser di file `.sub` che parte da `/ext/subghz`. Se il file non è utilizzabile compare un popup `ERROR` con `Bad frequency`, `Bad modulation` o `Unsupported protocol`, e lo slot resta com'era.
- `Button` — quale tasto del telecomando invia questo slot: `Default`, `Up`, `Down`, `Left`, `Right`. Vedi [Tasti personalizzati](#custom-buttons).
- `Clear Slot` — svuota lo slot.

Quando hai finito premi <kbd>→</kbd>. L'anteprima mostra il telecomando finito con `Back` a sinistra e `Save` a destra; <kbd>→</kbd> o <kbd>OK</kbd> scrive il file e appare una schermata `Saved!`. Uscire dall'editor con modifiche non salvate fa chiedere prima `Changes are not saved / do you want to exit?`.

Lasciare uno slot vuoto va benissimo. Una mappa con un solo tasto funziona.

## Inviare

Scegli `Open Map File` e la tua mappa. Questa schermata è disegnata di lato, quindi tieni il Flipper in verticale.

- **Tieni premuto** un tasto per trasmettere. Quella riga diventa nera e il LED lampeggia magenta.
- Rilascialo e il protocollo manda le ripetizioni che gli restano, poi si ferma. Un file RAW arriva alla fine della registrazione e riparte se stai ancora tenendo premuto.
- Sotto le cinque righe l'app mostra cosa sta inviando: nome del protocollo, frequenza e modulazione, `Key:` (solo per chiavi fino a 32 bit), `Sn:` o `Fix:`, `Cnt:`, `MF:`. Entrano al massimo cinque righe.
- L'icona in alto a sinistra dice se è in uso la radio interna o un [modulo esterno](/it/subghz/external-cc1101).
- <kbd>Back</kbd> ferma una trasmissione in corso. Premilo di nuovo per uscire dall'app.

Uno slot il cui file non si è caricato mostra `[X] Can't open file` o `[X] Error in .sub file` al posto dell'etichetta. Gli slot vuoti restano in bianco, e premendoli il LED lampeggia rosso.

## Tasti personalizzati {#custom-buttons}

Un telecomando a codice rolling ha più tasti, e un file `.sub` ne contiene uno. `Button` nel menu dello slot sceglie quale tasto invia questo slot. `Default` tiene il tasto che sta nel file; `Up`, `Down`, `Left` e `Right` inviano gli altri tasti dello stesso telecomando, gli stessi che ottieni da quei tasti in `Sub-GHz → Saved → Emulate`. L'editor aggiunge poi `(Btn. Up)` dopo il percorso.

Il contatore avanza di uno a ogni pressione, e l'app rimette il tasto originale quando la trasmissione finisce.

È così che dai a un tasto nascosto o di programmazione uno slot tutto suo. Quale freccia corrisponda a quale tasto dipende dal protocollo, vedi [Il Flipper come nuovo telecomando](/it/subghz/remote-prog).

## Il file di mappa

L'editor scrive un file di testo semplice nel formato del Flipper:

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` sono i percorsi completi dei file `.sub` associati a ciascuna direzione del D-pad.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` sono i testi mostrati a schermo per quei tasti.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` sono il tasto personalizzato, in esadecimale: `00` default, `01` su, `02` giù, `03` sinistra, `04` destra. L'editor omette la riga quando lo slot usa `Default`.

Una mappa la puoi scrivere anche su un PC. In quel caso:

- Separa la chiave dal valore con i due punti e **uno** spazio, esattamente come sopra.
- L'ordine delle righe non conta, l'app cerca ogni chiave per nome. Una chiave che ometti conta come vuota.
- Il **nome del file** di un `.sub` deve essere ASCII stampabile e non può contenere `\ < > * | " : ?`. Un nome in cirillico o un'emoji fa fallire il caricamento di quello slot.
- Tieni le etichette intorno ai 16 caratteri. Quelle più lunghe vengono tagliate sullo schermo stretto del telecomando.

L'editor integrato non può produrre una mappa rotta, quindi è meglio usare quello.

## Aprire una mappa all'avvio

`Set Default` salva la mappa scelta in `/ext/subghz_remote/.config`. Da quel momento l'app va dritta alla schermata del telecomando quando la apri, e <kbd>Back</kbd> ti porta al menu. `Clear Default` cancella quel file.

L'app accetta anche il percorso di un file di mappa come argomento di avvio, così un'altra app può aprire direttamente un telecomando preciso.

## Risoluzione dei problemi

- **`[X] Can't open file`**: il file `.sub` a cui punta quello slot è stato spostato, rinominato o cancellato. Riselezionalo con `Edit File`, oppure correggi il percorso nella mappa.
- **`[X] Error in .sub file`**: il file si carica ma non si può inviare. L'editor dice perché: `Bad frequency` (la frequenza del segnale non è supportata dalla radio che hai selezionato, vedi [Frequenze e portata](/it/subghz/frequencies)), `Bad modulation`, oppure `Unsupported protocol` (il protocollo è di sola ricezione).
- **Un tasto non fa nulla** e il LED lampeggia rosso: quello slot è vuoto o il suo file non si è caricato.
- **Un telecomando a codice rolling ha smesso di funzionare** dopo che hai usato sia il Flipper sia l'originale: è un conflitto di contatori, non un difetto dell'app. Vedi [Codici rolling](/it/subghz/rolling-codes) e crea un nuovo telecomando con [Il Flipper come nuovo telecomando](/it/subghz/remote-prog).
- **Avviso `Not official FW` all'avvio**: hai installato la build del catalogo pensata per il firmware ufficiale. Usa la Sub-GHz Remote che è già nel menu principale di Unleashed.
- Le guide più vecchie citano una schermata `Config is incorrect. Please configure map.`. L'app attuale non la mostra; segnala invece i tasti rotti nella schermata del telecomando.

## Pagine correlate

- [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw) · [Add Manually](/it/subghz/add-manually)
- [Il Flipper come nuovo telecomando](/it/subghz/remote-prog)
- [Formato dei file .sub](/it/subghz/file-format)
