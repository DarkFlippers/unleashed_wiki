---
title: Lettura dei tag
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# Leggere, salvare ed emulare tag a 125 kHz

Un tag a 125 kHz è un transponder che, alimentato dal campo di un lettore, invia un ID fisso. Se il tag usa uno dei
[protocolli supportati](/it/rfid/protocols), Flipper Zero decodifica l'ID, lo mostra e può salvarlo sulla scheda SD,
emularlo verso un lettore oppure [scriverlo su una vergine](/it/rfid/write).

**Da usare quando** vuoi una copia della tua tessera o del tuo portachiavi di accesso sul Flipper, quando vuoi
capire che tipo di tag hai in mano o quando ti serve l'ID per un sistema di controllo accessi che gestisci tu.

::: tip Inserisci una scheda SD
Chiavi salvate, dizionari e impostazioni risiedono sulla scheda microSD (`/ext/lfrfid/`). Installa il firmware con la
scheda SD inserita, così le risorse dell'app saranno presenti.
:::

## Leggere un tag

1. Vai su `Main Menu → 125 kHz RFID → Read`.
2. Appoggia il tag al **retro** del Flipper, verso il centro, e tienilo fermo. Lo schermo indica *Don't move card*.
3. Il Flipper esegue a rotazione tre passate di lettura di circa 2 secondi ciascuna e mostra quella attiva come
   **Reading 1/3 … 3/3**: **ASK** (125 kHz), **PSK** (125 kHz) e **134kHz** (ASK a 134,2 kHz, per i chip per
   animali).

   ![Reading 1/3 con la passata ASK attiva, PSK e 134 kHz sotto di essa e "Don't move card" in basso](/screens/lfrfid/read.png)

4. Osserva il LED: lampeggia **ciano** durante la lettura, passa al **giallo** quando percepisce qualcosa e al
   **verde** quando i frame di un tag iniziano a essere decodificati — utile per trovare la posizione migliore.
5. Quando un tag viene decodificato, il Flipper emette un bip e mostra la schermata dei risultati:
   - intestazione: produttore e protocollo, per esempio **EM-Micro EM4100**;
   - `Hex:` — i dati grezzi della chiave (i primi 7 byte; le chiavi più lunghe terminano con `...`);
   - campi decodificati (facility code, numero di tessera, ecc. — vedi [protocolli](/it/rfid/protocols)).

   ![Risultato della lettura: EM-Micro EM4100 con i dati esadecimali, facility code, numero di tessera, DEZ 8 e DEZ 10, Retry e More in basso](/screens/lfrfid/read_success.png)

6. Pulsanti: <kbd>←</kbd> **Retry** (chiede *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More**;
   <kbd>Back</kbd> chiede se uscire perdendo la lettura non salvata.

::: tip Unleashed
La documentazione ufficiale descrive solo il passaggio tra ASK e PSK. Unleashed aggiunge la terza passata a
**134 kHz** (i tag FDX-A/FDX-B sono accordati su 134,2 kHz e quelli deboli rispondono soltanto lì) e, per EM4100,
mostra anche **DEZ 8** e **DEZ 10** — le forme decimali stampate su molti portachiavi. Un EM4100 che viene decodificato
come badge Casi-Rusco C10106 riceve una riga aggiuntiva `or C10106: …`, mentre una chiave Generic HIDProx viene
confrontata con i formati HID noti (H10304, H10302, S10401, H10306, Corp1000-35) mostrandone facility code e numero
di tessera.
:::

## Dopo la lettura: More

<kbd>→</kbd> **More** apre:

| Voce | Azione |
|---|---|
| **Save** | Inserisci un nome (prefisso predefinito `RFID`), salvato come `/ext/lfrfid/<name>.rfid` |
| **Emulate** | Emula subito la chiave, senza salvarla |
| **Write** | Scrive la chiave su una vergine — vedi [Scrittura](/it/rfid/write) |

## Leggere con una modulazione fissa

Alcuni tag richiedono più tempo di una singola passata di 2 secondi per essere decodificati, oppure si trovano in modo
affidabile solo con un demodulatore specifico. `Main Menu → 125 kHz RFID → Extra Actions` propone:

| Voce | Cosa legge |
|---|---|
| **Read ASK (Regular)** | solo ASK a 125 kHz, fino a trovare un tag: EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | solo PSK: Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | solo ASK a 134,2 kHz — chip per animali, vedi [Microchip per animali](/it/rfid/animal-microchips) |

In modalità Debug lo stesso menu contiene anche **Read RAW RFID data** ed **Emulate RAW RFID data** — vedi
[RAW](/it/rfid/raw).

## Chiavi salvate

`Main Menu → 125 kHz RFID → Saved` apre il browser dei file in `/ext/lfrfid/`. Selezionando una chiave `.rfid` si
apre:

![Menu del tag salvato con Emulate, Write, Write and set password ed Edit](/screens/lfrfid/saved_menu.png)

| Voce | Azione |
|---|---|
| **Emulate** | Si comporta come questa chiave verso un lettore |
| **Write** | La scrive su una vergine ([Scrittura](/it/rfid/write)) |
| **Write and set password** | Scrive su un T5577 e lo protegge con una password ([Scrittura](/it/rfid/write#write-and-set-password)) |
| **Edit** | Modifica i dati della chiave in esadecimale; salvati con lo stesso nome |
| **Rename** | Cambia il nome del file |
| **Delete** | Elimina il file (con conferma) |
| **Info** | Nome, protocollo, dati esadecimali completi e tutti i campi decodificati |

::: tip Unleashed
Il browser elenca anche i dump dei blocchi **`.t5577`** (contrassegnati dall'icona T5577). Selezionandone uno si avvia
l'[app T5577](/it/rfid/t5577-app) con quel dump. Se l'app non è presente compare *No T5577 app — It comes with the
firmware - install its resources to get it*.
:::

## Emulazione

1. Apri una chiave salvata (o una lettura appena fatta tramite **More**) e scegli **Emulate**.
2. Lo schermo mostra *Emulating*, `[Protocol]` e il nome della chiave (o *Unsaved Tag*); il LED lampeggia magenta.

   ![Schermata di emulazione con "Emulating", il protocollo [EM4100] e il nome della chiave](/screens/lfrfid/emulate.png)

3. Tieni il retro del Flipper appoggiato in piano contro il lettore. Premi <kbd>Back</kbd> per fermarti.

## CLI

Dalla CLI su USB/seriale (comando `rfid`):

```text
rfid read <optional: normal | indala | ask134>   - read in ASK/PSK mode
rfid <write | emulate> <key_type> <key_data>      - write or emulate a card
rfid raw_read <ask | ask134 | psk> <filename>     - read and save raw data to a file
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` è il nome del protocollo così come viene memorizzato nei file `.rfid` (per esempio `EM4100`, `H10301`),
`key_data` è in esadecimale.

## Risoluzione dei problemi

- **Non viene trovato nulla.** La tessera potrebbe essere a 13,56 MHz — prova con [NFC](/it/nfc/read). Molte tessere
  "dual" contengono entrambe le tecnologie.
- **La lettura continua a ciclare.** Prova una modalità fissa in **Extra Actions** — una passata di 2 s può essere
  troppo breve per alcuni tag.
- **Tag deboli / portachiavi piccoli.** Muovi il tag lentamente sul retro; osserva il LED giallo/verde. Non tenerlo
  in mano sopra superfici metalliche.
- **Protocollo sconosciuto.** Registra una cattura [RAW](/it/rfid/raw) e segnalala agli sviluppatori.
- **Emulazione non accettata.** Alcuni lettori sono esigenti su distanza e orientamento — tieni il Flipper in piano e
  prova diverse posizioni. I lettori che verificano qualcosa oltre all'ID (per esempio le tessere crittografiche) non
  possono essere ingannati dall'emulazione.

## Pagine correlate

- [Scrittura su vergini](/it/rfid/write) · [Aggiunta manuale](/it/rfid/add-manually) ·
  [Protocolli](/it/rfid/protocols) · [Formato dei file](/it/rfid/file-format)
