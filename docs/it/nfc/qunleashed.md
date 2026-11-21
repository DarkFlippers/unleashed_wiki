---
title: Recupero rapido delle chiavi con qUnleashed
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Recupero rapido delle chiavi MIFARE Classic con qUnleashed

Una guida pratica di **@gromovyna**: recuperare rapidamente le chiavi MIFARE Classic usando Unleashed e la sua app
companion **qUnleashed** (sviluppata e mantenuta dal team Unleashed; un grande grazie ad
[apfxtech](https://github.com/apfxtech), autore originale dell'app). È la continuazione di
[Attacchi nested e backdoor Fudan](/it/nfc/nested-fudan); leggere prima quella pagina è consigliato ma non
indispensabile.

Il recupero copre **tutti gli attacchi e tutti i tipi di nonce** noti al momento della stesura: *weak, hard, static,
static encrypted*. A differenza dell'[app MFKey](/it/nfc/mfkey-app), il calcolo pesante viene eseguito sul telefono o
sul computer, quindi di solito richiede **minuti**, non ore.

::: warning Ti serve il tag tra le mani
Il tag deve essere fisicamente presente per la lettura finale. "Ho fatto un dump per un amico e il tag non c'è più"
non funziona.
:::

## Versioni

La funzionalità può esistere in versioni leggermente precedenti, ma per i test sono state usate queste:

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

Vedi anche [App qUnleashed](/it/mobile/qunleashed-app) per l'installazione e le altre funzioni.

## Cosa ti serve

Un tag **MIFARE Classic** (oppure **MIFARE Plus in SL1**, solo SL1) con **almeno una chiave nota o una backdoor**.

![Un tag con una chiave sconosciuta](/img/remote/286db70e86cfa835.png)

![Un tag con backdoor: chiavi sconosciute, ma settori letti tramite la backdoor](/img/remote/59bd4aa5ae1242c1.png)

Se il tuo tag non ha backdoor e nemmeno una chiave nota, ricavane prima una dal lettore con
[MFKey32](/it/nfc/mfkey). qUnleashed può recuperare le chiavi anche dai nonce del lettore (vedi il passo 2).

## Passo 1. Raccogliere i nonce

1. Prima dell'attacco è una buona idea svuotare `/ext/nfc/.nested.log`, se ce l'hai (`/ext/` è la scheda SD). Dopo il
   recupero ha senso anche eliminarlo, così non cresce e non intralcia. Per qUnleashed non è critico, ma è buona
   pratica.
2. Leggi il tag: `Main Menu → NFC → Read`. Attendi mentre si svolgono le fasi; quali compaiono dipende dal tipo di
   nonce del tag: **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**, **Calibration**,
   **Nonce Collection**.

   ![Raccolta dei nonce](/img/remote/786d77b7b65b3fd0.png)

3. Quando compaiono le informazioni sul tag, **salva il dump incompleto**: ti servirà più tardi.
4. Facoltativamente verifica in qUnleashed che i nonce ci siano: collega il Flipper, apri
   `Archive → External → nfc`, abilita i file nascosti (il menu "burger"/tre puntini in alto a destra) e cerca
   `.nested.log`.

   ![.nested.log in qUnleashed](/img/remote/c4c534fbe93faa8a.png)

## Passo 2. Recuperare le chiavi

Tutto avviene in **qUnleashed**; il Flipper deve restare collegato (Bluetooth o cavo) per tutto il tempo.

1. Apri `Tools → Recover MIFARE Keys`.

   ![La voce di menu](/img/remote/1a255b9128f988ab.png)

2. Attendi la fine del recupero.

   ![Recupero delle chiavi in corso](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Abbi pazienza
   Può richiedere un po' di tempo, a seconda della dimensione di `.nested.log`, dei tipi di nonce, della potenza del
   dispositivo su cui gira qUnleashed e così via. Di solito si tratta di minuti. Attendi il completamento
   dell'operazione. I nonce static encrypted sono i più lenti.
   :::

3. Esamina il risultato. La fase di recupero lavora con **`.mfkey32.log`** (nonce del lettore) e **`.nested.log`**
   (nonce del tag). La schermata mostra da dove è arrivata ogni chiave, quante ne sono state aggiunte al dizionario
   utente o a quello delle candidate e così via.

   ![Risultato del recupero](/img/remote/1c5f56614caf4530.png)

Dove finiscono le chiavi dipende dal tipo di nonce:

| Nonce | Risultato |
|---|---|
| weak, hard, static | Le chiavi vengono aggiunte al **dizionario utente** `/ext/nfc/assets/mf_classic_dict_user.nfc`. |
| static encrypted | A questo stadio la chiave non può essere calcolata esattamente, quindi viene costruito un **dizionario di candidate** (detto anche **dizionario CUID**): `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, dove `{UID}` è l'ID del tuo tag. Può essere grande: nell'esempio dell'autore conteneva più di **1,2 milioni di candidate** per un solo tag. |

## Passo 3. Leggere di nuovo il tag

Appoggia il tag al Flipper e vai in `NFC → Read`, oppure apri il dump incompleto salvato e scegli
**Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

Con un **dizionario CUID**, questo viene caricato per primo. Il dizionario di candidate è grande, quindi ci vuole
tempo, e vedi una barra di avanzamento (*"CUID dictionary is loading"*). Qui il tempo di caricamento reale si misura in
**minuti**.

![Schermata di caricamento, build dev 1437 e successive](/img/remote/47427c58e2a34889.png)

::: tip Aggiornamento 22.09.2026
Nelle prime versioni del firmware questo momento mostrava solo una schermata vuota, cosa che confondeva molti utenti.
A partire dalla build dev **1437** (e dalla release **094**) la schermata ha una barra di avanzamento.
:::

Poi parte l'attacco a dizionario con le chiavi recuperate.

![Attacco a dizionario](/img/remote/f77ef58bda94b088.png)

Di nuovo, per i **nonce static encrypted (dizionario CUID)** lascia il Flipper sul tag durante la ricerca e vai a
farti un tè.

Una volta trovate tutte le chiavi puoi aggiornare il dump parziale salvato portandolo a uno completo, oppure salvarlo
con un nuovo nome.

![Tag letto completamente](/img/remote/9f9745d0d2ee0a4a.png)

Ora tutte le possibilità sono disponibili: emulazione, scrittura su carte vuote, condivisione con un amico ecc.

::: warning Prima di scrivere su una carta vuota
Conosci la differenza tra le carte vuote e il modo in cui i lettori possono filtrarle: vedi
[Magic card](/it/nfc/magic-cards).
:::

## Facoltativo: salvare nel dizionario utente le chiavi di un tag static encrypted

Per come funziona l'attacco, le chiavi recuperate dal dizionario di candidate sono memorizzate **solo in quel
dizionario e nel dump del tag**. È un problema se vuoi scrivere una carta vuota e poi azzerarla:
[NFC Magic](/it/nfc/nfc-magic) lavora solo con la cache di chiavi e con i dizionari utente e di sistema.

Per questo il team ha aggiunto al firmware il salvataggio automatico delle chiavi, con controllo dei duplicati. Apri il
menu del dump salvato (deve essere nota almeno una chiave) e scegli **Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

Il Flipper mostra *"Saving keys to user dictionary"* e poi *"New keys: N, Already known: M"*.

## Alternative

Esiste anche un [progetto CLI](https://github.com/phntm-lab/mfkey_desktop_cli) per il recupero. Sotto alcuni aspetti è
più rapido, ma la CLI è per smanettoni duri e puri. Per l'uso quotidiano l'autore preferisce la comoda app companion,
soprattutto considerando quante altre funzioni utili ha. Sul solo Flipper, usa l'[app MFKey](/it/nfc/mfkey-app).

Il processo può sembrare un po' complicato all'inizio, ma dopo un po' di pratica diventa routine.

## Pagine correlate

[Attacchi nested](/it/nfc/nested-fudan) · [MFKey32](/it/nfc/mfkey) · [App MFKey](/it/nfc/mfkey-app) ·
[MIFARE Classic](/it/nfc/mifare-classic) · [Magic card](/it/nfc/magic-cards) · [App qUnleashed](/it/mobile/qunleashed-app)
