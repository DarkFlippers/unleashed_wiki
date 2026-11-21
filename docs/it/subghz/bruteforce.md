---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** è un'app di brute-force per codici statici realizzata dal team Unleashed. Scorre i codici possibili di un protocollo a codice fisso e li trasmette uno dopo l'altro. Puoi usare un protocollo preconfigurato dal suo elenco, oppure caricare un tuo file `.sub` e scegliere quali byte iterare.

::: warning
Usala solo su apparecchiature di tua proprietà o con un permesso esplicito. Fare brute-force sul cancello o sulla sbarra di qualcun altro è illegale nella maggior parte dei paesi.
:::

::: tip Unleashed
L'app non fa parte dell'immagine del firmware e non è nell'albero dei sorgenti del firmware. Viene distribuita come app esterna (`.fap`) nei pacchetti di app di Unleashed, compilata da [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Installa il pacchetto (vedi [App sulla scheda SD](/it/apps/sd-card-apps)) e cercala in `Apps → Sub-GHz`.
:::

## Quando ha senso

- **Solo codici statici (fissi).** Il brute-force funziona solo quando il ricevitore accetta per sempre lo stesso codice, come con i telecomandi CAME 12 bit, Nice Flo 12 bit, in stile Princeton e simili a dip switch. Un ricevitore a codice rolling (KeeLoq, Nice Flor-S, CAME Atomo e altri) non accetta mai un codice indovinato, quindi lì il brute-force è inutile (vedi [Codici rolling](/it/subghz/rolling-codes)).
- **Hai perso il telecomando del tuo dispositivo a codice statico** e non conosci il suo codice, oppure vuoi provare quanto rapidamente il tuo sistema a codice fisso può essere indovinato.

Se hai ancora un telecomando funzionante, è molto più rapido semplicemente [leggerlo](/it/subghz/read).

## Come si usa

### Protocolli preconfigurati

1. Apri `Apps → Sub-GHz` e avvia l'app Bruteforce.
2. Scegli un protocollo dall'elenco.
3. Per cambiare quante volte ogni codice viene ripetuto, premi <kbd>→</kbd> sul protocollo selezionato.
4. Avvia l'attacco e tieni il Flipper vicino al ricevitore finché non reagisce.

### Un tuo file

1. Salva prima un segnale del protocollo bersaglio, per esempio con [Read](/it/subghz/read) o
   [Add Manually](/it/subghz/add-manually).
2. Nell'app, carica quel file `.sub`.
3. Seleziona i byte della chiave su cui vuoi fare brute-force. Gli altri byte restano come sono nel file.
4. Avvia l'attacco.

### Ritardo tra i segnali

Il ritardo tra i codici trasmessi si imposta nella schermata principale dell'app. **Tieni premuto <kbd>↑</kbd>** lì (il suggerimento a schermo dice "Up to Save") per salvarlo. Un ritardo più breve finisce prima, ma alcuni ricevitori perdono i codici che arrivano troppo ravvicinati.

## Consigli ed errori comuni

- **Frequenza o modulazione sbagliate**: il ricevitore non sente nulla. Controlla prima la banda con il
  [Frequency Analyzer](/it/subghz/frequency-analyzer).
- **Troppo poche ripetizioni**: molti ricevitori hanno bisogno che un codice venga ripetuto diverse volte prima di
  agire. Aumenta le ripetizioni con <kbd>→</kbd> sul protocollo.
- **Va avanti a lungo**: il numero di codici cresce esponenzialmente con il numero di bit. I codici a 12 bit sono
  rapidi, mentre chiavi più lunghe possono richiedere tempi impraticabili. Restringi la ricerca facendo brute-force
  solo sui byte sconosciuti di un tuo file.
- **La trasmissione è bloccata**: la frequenza è fuori dall'intervallo consentito. Vedi
  [Frequenze e portata](/it/subghz/frequencies).

## Pagine correlate

- [Sistemi supportati](/it/subghz/supported-systems): quali protocolli sono statici
- [Add Manually](/it/subghz/add-manually)
- [Formato dei file .sub](/it/subghz/file-format)
