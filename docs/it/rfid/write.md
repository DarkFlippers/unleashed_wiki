---
title: Scrittura su vergini
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# Scrivere chiavi a 125 kHz su vergini

Tessere e portachiavi a 125 kHz originali sono quasi sempre di sola lettura. Per realizzare una copia fisica serve una
**vergine scrivibile** — un chip "magico" che può essere programmato per comportarsi come una tessera di un altro
protocollo. Flipper Zero può scrivere su una vergine di questo tipo qualunque chiave salvata, letta o aggiunta
manualmente.

## Quali vergini si possono scrivere

| Chip (come appare sullo schermo) | Nomi commerciali tipici | Scrive | Predefinito |
|---|---|---|---|
| **T5577** | T5577, ATA5577, tessere/portachiavi/adesivi "5577" | tutti i protocolli | ON |
| **EM4305** | vergini EM4305 / EM4205 | famiglia EM4100, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (clone Hitag Micro, password predefinita) | famiglia EM4100 | ON |
| **8210** | ID8210 (stesso chip, password del cloner FURUI) | famiglia EM4100 | ON |
| **H5.5** | iKey H5.5 (stesso chip, password iKey) | famiglia EM4100 | ON |
| **8268** | ID8268 (chip magico Hitag S) | solo EM4100 a RF/64 | **OFF** |

::: tip Unleashed
La documentazione ufficiale parla solo del T5577. Il supporto Hitag Micro per **8265/H5, H5.5 e 8210** è stato
aggiunto a Unleashed da **@gromovyna** — i chip differiscono solo per la password di login, quindi il Flipper prova a
turno ogni password conosciuta invece di chiedertela. Contesto e retroscena: [T5577 e Hitag Micro](/it/rfid/t5577-hitag).
:::

::: warning 8268 va abilitato a mano
Il target **8268** (Hitag S) è disattivato per impostazione predefinita. A differenza degli altri writer seleziona
qualunque tag Hitag S risponda e, su un Hitag S autentico, le pagine 4 e 5 contengono dati applicativi — il Flipper non
è in grado di distinguere un tag autentico da un clone. Abilitalo solo quando sei certo che sulla bobina ci sia una
vergine 8268.
:::

## Scrivere una chiave

1. Leggi un tag (`Read` → **More** → **Write**) oppure aprine uno salvato (`Saved` → chiave → **Write**).
2. Appoggia la vergine al retro del Flipper e **non muoverla**. Il LED lampeggia magenta.
3. Lo schermo mostra **Writing**, il protocollo tra parentesi quadre, il nome del file (o *Unsaved Tag*) e, tra
   parentesi tonde, il **chip attualmente in prova**, per esempio:

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Schermata di scrittura con il protocollo [EM4100], il nome della chiave e il chip in prova, (T5577), tra parentesi](/screens/lfrfid/write.png)

4. Il Flipper scrive a turno ogni tipo di chip abilitato e **rilegge il tag** dopo ciascun tentativo. Appena la
   rilettura corrisponde, si ferma.
5. In caso di successo compare **Success!** con il nome del chip che ha effettivamente accettato i dati (per esempio
   `T5577`, `EM4305`, `H5.5`) e l'app torna al menu della chiave.

![Scrittura in corso, con il chip in prova](/img/remote/34b72cbd8417d74e.png)

![Risultato della scrittura con il nome del chip](/img/remote/3ca59457a78dad5b.png)

::: tip Perché il nome del chip?
Con diversi tipi di chip da provare (e tre password per Hitag Micro) una scrittura può richiedere molto più tempo, e
non era chiaro cosa fosse stato scritto. Mostrare il chip in prova e quello finale è stata la correzione di UX di
@gromovyna: tecnicamente si tratta del nome commerciale della variante di vergine, non di un protocollo.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` elenca tutti i target: **T5577**, **EM4305**, **8265**, **8210**,
**H5.5**, **8268**, ciascuno su **ON** / **OFF**.

- <kbd>OK</kbd>, <kbd>←</kbd> o <kbd>→</kbd> commuta il chip evidenziato.
- La scelta viene salvata in `/ext/lfrfid/.lfrfid.settings` quando esci dalla pagina (<kbd>Back</kbd>).
- Disattivare i chip che non usi mai rende le scritture più rapide (ogni chip abilitato che non corrisponde costa una
  scrittura più una verifica).
- Il comando CLI `rfid write` rispetta la stessa impostazione.

Se la pagina non si apre compare *Settings plugin failed to load* — aggiorna le risorse sulla scheda SD (la pagina è
un file plugin separato). Le scritture continuano comunque a usare quanto memorizzato nel file delle impostazioni.

## Write and set password

`Saved` → chiave → **Write and set password** scrive la chiave su un **T5577** e ne attiva la protezione con
password, così nessuno può riscrivere il tag senza conoscerla.

1. Inserisci la password di 4 byte in esadecimale. Se non ne è stata ancora impostata una, il campo è precompilato con
   una parola casuale presa dal dizionario T5577.
2. Tieni ferma la vergine. Lo schermo mostra **Writing with password**, `[Protocol]` e il passo corrente.
3. Prima la chiave viene scritta e riletta, poi la password viene inviata al blocco 7 e riletta, e solo allora viene
   impostato il bit della password nel blocco 0. **Annota la password** — un T5577 bloccato con una password
   sconosciuta non può essere riutilizzato.

Risultati possibili:

| Schermata | Significato |
|---|---|
| **Success!** | Chiave scritta, password memorizzata e protezione attiva |
| **Error** — *This protocol cannot be written with a password* | Il protocollo richiede tutti e 7 i blocchi di dati, il blocco 7 non può contenere una password |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | Il tag è già protetto |
| **Cannot read it** | Sulla bobina c'è qualcosa, ma i suoi blocchi non si riescono a leggere — eseguine il wipe o cancellane prima la password |
| **Not written** | Un blocco ha rifiutato la chiave; il tag ne contiene una parte e nessuna password |
| **Not protected** | La password non è arrivata nel blocco 7, oppure il tag ha rifiutato di attivare la protezione |
| **Not confirmed** | La password è sul tag, ma non è stato possibile rileggere se la protezione è attiva |
| **Still trying to write...** | Nessun tag risponde — verifica che sia un T5577 scrivibile |

## Messaggi di errore di una scrittura normale

| Messaggio | Cosa fare |
|---|---|
| *This protocol cannot be written* | Non esiste alcuna codifica su chip per questo protocollo |
| *No write chips enabled. Enable one in Settings* | Tutti i target sono su OFF |
| *No enabled chip can write this protocol* | Per esempio solo EM4305 abilitato per una chiave HID — abilita il T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Compare dopo circa 10 s o dopo diverse verifiche fallite. Il tag è di sola lettura, protetto da password, di un tipo di chip non supportato o mal posizionato. Il Flipper continua a provare finché non premi <kbd>Back</kbd>. |

## Risoluzione dei problemi

- **La vergine ha una password.** Molti cloner economici bloccano le vergini T5577. Usa l'[app T5577](/it/rfid/t5577-app) →
  **Clear Password** (prova la tua password, poi il dizionario).
- **Un T5577 ha preso una configurazione inutilizzabile** (non viene più letto come nulla). Usa l'app T5577 →
  **Wipe Tag**.
- **Hitag Micro (8265/8210/H5.5) richiede un buon posizionamento.** Scriverli richiede più tempo ed è sensibile alla
  posizione; il Flipper dispone solo della trasmissione in LF, quindi il successo è confermato unicamente dalla
  rilettura del tag.
- **"Success" su una tessera di sola lettura.** Se un tag non scrivibile contiene già lo stesso ID, la rilettura
  corrisponde e la scrittura viene riportata come riuscita.
- **Portachiavi con metallo / involucri spessi.** Prova punti diversi; nei portachiavi la bobina è spesso
  decentrata.

## Pagine correlate

- [T5577 e Hitag Micro](/it/rfid/t5577-hitag) · [App T5577](/it/rfid/t5577-app) ·
  [Protocolli](/it/rfid/protocols) · [Lettura](/it/rfid/read)
