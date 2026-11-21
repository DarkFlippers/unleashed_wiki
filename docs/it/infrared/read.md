---
title: Apprendere e inviare segnali
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Apprendere e inviare segnali IR

Il Flipper Zero può copiare i pulsanti di un telecomando IR uno per uno e conservarli come **telecomando virtuale**:
un file `.ir` in `/ext/infrared/`. Usalo quando il telecomando originale è perso, rotto o semplicemente in un'altra
stanza, oppure quando un telecomando universale non trova il tuo apparecchio.

I segnali dei [protocolli noti](/it/infrared/protocols) vengono decodificati e salvati in una forma *parsed* compatta
(protocollo + indirizzo + comando). Tutto il resto viene salvato come temporizzazioni **RAW**, che funzionano
comunque per la riproduzione.

## Apprendere un nuovo telecomando

1. Vai in `Main Menu → Infrared → Learn New Remote`.
2. La schermata dice **"Point the remote at IR port and push the button"**. Tieni il telecomando a qualche centimetro
   dal bordo superiore del Flipper, in linea di vista con la finestra IR.

   ![Learn New Remote in attesa di un segnale: "Point the remote at IR port and push the button"](/screens/infrared/learn.png)

3. Premi il pulsante sul telecomando **brevemente**. Non tenerlo premuto: un pulsante tenuto premuto produce una
   acquisizione lunga e piena di ripetizioni.
4. Compare la schermata di acquisizione:
   - un segnale decodificato mostra il nome del protocollo e l'indirizzo/comando, per esempio `NECext`, `A: 0x87EE`,
     `C: 0xA05D`;
   - un segnale sconosciuto mostra **Unknown** e il numero di campioni, per esempio `150 samples`.

   ![Schermata di acquisizione: il protocollo decodificato NEC con il suo indirizzo e comando, e in basso Retry, Send e Save](/screens/infrared/learn_success.png)

5. Scegli cosa fare:
   - <kbd>OK</kbd> **Send**: riproduce il segnale acquisito mentre tieni premuto il pulsante, per provarlo subito;
   - <kbd>←</kbd> **Retry**: chiede *"Retry Reading? All unsaved data will be lost!"*, poi <kbd>←</kbd> Exit butta via
     l'acquisizione e torna in ascolto, <kbd>→</kbd> Stay torna indietro;
   - <kbd>→</kbd> **Save**: prosegue con l'assegnazione del nome.
6. Inserisci un nome per il pulsante in **"Name the button"** (max. 23 caratteri) e conferma. Il nome predefinito è
   generato dal segnale: le prime 4 lettere del protocollo e il comando (per esempio `NECe_A05D`), oppure
   `RAW_<samples>` per i RAW.
7. Viene mostrato **"Success!"** e si apre il nuovo telecomando. Il primo telecomando viene salvato come
   `/ext/infrared/Remote.ir`; se quel nome è occupato, `Remote1.ir`, `Remote2.ir` e così via.

![Segnale acquisito sullo schermo](/img/remote/a62fc8f9d738534b.png)

::: tip Rinomina il telecomando
Un telecomando nuovo si chiama sempre `Remote`. Rinominalo subito con `Edit → Rename Remote` (vedi sotto), altrimenti
ti ritroverai con `Remote`, `Remote1`, `Remote2`…
:::

### Aggiungere altri pulsanti

Nell'elenco dei pulsanti del telecomando, scorri in fondo e seleziona **`+`**. Si riapre la schermata di
apprendimento. Acquisisci, **Save**, dai un nome al pulsante e ottieni **"Saved"**: il pulsante viene aggiunto allo
stesso file.

Premendo <kbd>Back</kbd> nella schermata di acquisizione viene chiesto *"Exit to Infrared Menu?"* (oppure *"Exit to
Remote Menu?"* quando stai aggiungendo a un telecomando esistente): i dati non salvati vengono perduti se scegli Exit.

## Inviare un pulsante salvato {#send-a-saved-button}

1. Vai in `Main Menu → Infrared → Saved Remotes` e scegli un file `.ir`.
2. Punta il bordo superiore del Flipper verso l'apparecchio.
3. Seleziona un pulsante con <kbd>↑</kbd> / <kbd>↓</kbd> e premi <kbd>OK</kbd>.

Il segnale viene inviato **per tutto il tempo in cui tieni premuto** <kbd>OK</kbd>: una pressione per un comando
singolo, tenuto premuto per le azioni "premi e tieni" come la regolazione progressiva del volume. Il LED lampeggia
durante la trasmissione.

![Invio di un segnale salvato](/img/remote/d20ed673954c3711.png)

::: tip Preferiti e Archive
I telecomandi salvati compaiono anche nell'**Archive** (`Main Menu → Archive → Infrared`) e là possono essere aggiunti
ai preferiti. Nella Flipper Mobile App si trovano sotto **Archive → Infrared**, vedi
[Telecomandi nell'app mobile](/it/infrared/mobile).
:::

## Modificare un telecomando

Apri un telecomando e seleziona **Edit** proprio in fondo all'elenco dei pulsanti. Il menu Edit contiene:

| Voce | Cosa fa |
|---|---|
| **Add Button** | Apprende un altro pulsante (come `+`). |
| **Rename Button** | Scegli un pulsante, inserisci un nuovo nome. |
| **Move Button** | Schermata *"Select a Button to Move"*: seleziona un pulsante, premi <kbd>OK</kbd> per prenderlo (si sposta a destra), muovilo con <kbd>↑</kbd> / <kbd>↓</kbd>, premi di nuovo <kbd>OK</kbd> per rilasciarlo. |
| **Delete Button** | Scegli un pulsante. La conferma *"Delete Button?"* mostra il suo nome e protocollo / indirizzo / comando (oppure `RAW` e il numero di campioni). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Rinomina il telecomando e il file. Se il nome esiste già, viene aggiunto un numero. |
| **Delete Remote** | La conferma *"Delete Remote?"* indica il numero di pulsanti. Elimina il file `.ir`. |

I nomi sono limitati a **23 caratteri** sia per i pulsanti sia per i telecomandi. Le modifiche più consistenti (unire
file, rimuovere molti pulsanti) sono più comode su un PC: scarica il file con [qFlipper](/it/mobile/qflipper) e
modificalo come testo, vedi il [formato dei file IR](/it/infrared/file-format).

::: warning I file di libreria non sono telecomandi
Se provi ad aprire un file di `/ext/infrared/assets/` tramite Saved Remotes, ottieni *"Library file … can't be opened
as a remote"*. I file di libreria (`Filetype: IR library file`) sono usati solo dai
[Telecomandi universali](/it/infrared/universal-remotes).
:::

## Extra della modalità debug {#debug-mode-extras}

Con `Settings → System → Debug` attivo, il menu Infrared mostra due voci in più:

- **Learn New Remote RAW**: lo stesso flusso di Learn, ma con il decoder disattivato e ogni segnale memorizzato come
  RAW. Utile quando il decoder riconosce un protocollo ma la riproduzione decodificata non funziona sul tuo
  apparecchio.
- **Debug RX**: la schermata *"INFRARED monitor"* che mostra in tempo reale ciò che riceve il ricevitore.

## Risoluzione dei problemi

| Problema | Cosa provare |
|---|---|
| Non accade nulla quando premi il telecomando | Controlla le batterie del telecomando (guarda il suo LED attraverso la fotocamera di un telefono). Avvicinati e punta direttamente verso il bordo superiore. Evita la luce solare diretta e le lampade fluorescenti / LED vicine. |
| Il segnale viene acquisito come **Unknown / RAW** anche se il telecomando è comune | Le interferenze possono forzare il RAW. Usa **Retry** qualche volta finché ottieni un segnale decodificato. Se si tratta davvero di un protocollo sconosciuto, il RAW va bene. |
| Acquisizioni RAW enormi (centinaia di campioni) | Hai tenuto premuto il pulsante. Fai una pressione rapida; circa 100 campioni sono tipici per una singola pressione. Le acquisizioni molto lunghe si riproducono lentamente. Un segnale RAW può contenere al massimo 1024 temporizzazioni. |
| L'apparecchio non reagisce al pulsante salvato | Avvicinati, punta direttamente verso la finestra IR dell'apparecchio. Prova a inviarlo qualche volta o a tenere premuto <kbd>OK</kbd> più a lungo. Per le lunghe distanze usa un [modulo IR esterno](/it/infrared/external-ir). |
| Il condizionatore reagisce in modo sbagliato | I telecomandi dei condizionatori inviano l'intero stato (modalità, temperatura, ventola) a ogni pressione. Registra ogni stato che ti serve come pulsante a sé, vedi [Contribuire con le acquisizioni](/it/infrared/captures#air-conditioners). |
| "Failed to load …" durante l'invio | Il file `.ir` è danneggiato o è stato modificato a mano in modo errato. Controllalo rispetto al [formato dei file](/it/infrared/file-format). |

## Pagine correlate

- [Telecomandi universali](/it/infrared/universal-remotes)
- [Telecomandi nell'app mobile](/it/infrared/mobile)
- [Formato dei file IR](/it/infrared/file-format)
- [Moduli IR esterni](/it/infrared/external-ir)
