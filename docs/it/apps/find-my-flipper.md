---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (di @MatthewKuKanich) trasforma il Bluetooth del Flipper in un beacon da tracker. Il Flipper
trasmette lo stesso annuncio BLE di un tag, e i telefoni della rete di tracciamento nelle vicinanze ne segnalano la
posizione, così un Flipper smarrito si può ritrovare nell'app del proprietario del tag.

Tipi di tag supportati: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag** e
**Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper è distribuito con il firmware, e Unleashed installa anche un piccolo hook di avvio: se il beacon era
attivo quando il Flipper è stato spento, **riparte automaticamente dopo un riavvio**, senza aprire l'app. Il beacon
continua a funzionare in background mentre usi altre app.
:::

::: warning
Usalo solo con tag e dispositivi tuoi. Tracciare altre persone può essere illegale nel tuo paese.
:::

## Cosa ti serve

Il Flipper ha bisogno dell'**indirizzo MAC** e del **payload** del tag (oppure di un file di chiavi). Li puoi ottenere
in due modi:

- **Clonare un tag esistente** (il più semplice; la posizione compare poi nella normale app del proprietario del tag).
- **Generare chiavi proprie** con il metodo OpenHaystack (non serve un tag fisico, solo rete Apple; la posizione si
  consulta con OpenHaystack o con un'alternativa che non richiede un Mac).

### Opzione A: clonare un tag esistente

1. Associa l'AirTag o lo SmartTag al telefono come di consueto.
2. Portalo in stato "smarrito": tienilo lontano dal telefono su cui è registrato per circa 15 minuti.
3. Su un telefono Android installa **nRF Connect** (la versione iOS non mostra i dati grezzi).
4. In nRF Connect imposta il filtro sulla marca del tag (Apple o Samsung), porta l'RSSI al valore più basso ed esegui
   la scansione.
5. Quando il tag compare come dispositivo "FindMy", apri **Raw** / **View Raw** e annota il **payload** e
   l'**indirizzo MAC**. Puoi anche esportarlo come file `.txt`.
6. **Rimuovi immediatamente la batteria del tag**, altrimenti ruoterà la propria chiave e il proprio MAC e la tua
   copia smetterà di funzionare.

### Opzione B: chiavi OpenHaystack

1. Scarica `generate_keys.py` dal [repository FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper) ed
   eseguilo (richiede `python3 -m pip install cryptography`).
2. Fornisce una **Private Key**, una **Public Key**, un **Payload** e un **MAC Address**, oltre a un file `.keys`.
3. Conserva la Private Key: ti serve per ricevere le segnalazioni di posizione.
4. Consulta le posizioni in [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS inferiore a 14)
   oppure senza un Mac con [macless-haystack](https://github.com/dchristl/macless-haystack) o
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Configurare il Flipper

1. Copia il file `.txt` esportato da nRF Connect o il file `.keys` in `/ext/apps_data/findmy/` sulla scheda SD
   (oppure salta questo passaggio e inserisci i dati a mano).
2. Apri `Apps → Bluetooth → FindMy Flipper` e premi <kbd>→</kbd> (**Config**).
3. Scegli **Register Tag**, poi il tipo di tag: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` o
   `Google Find My`.
4. Scegli la modalità di importazione:
   - `nRF Connect (.txt)`: seleziona il file esportato;
   - `OpenHaystack (.keys)`: seleziona il file di chiavi;
   - `Register Tag Manually`: digita l'indirizzo MAC e poi il payload.
5. Torna alla schermata principale e premi <kbd>OK</kbd>. Passa a `Broadcast Active`.

## Schermata principale

| Pulsante | Azione |
|---|---|
| <kbd>OK</kbd> | avvia / ferma il beacon (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | cambia l'intervallo di trasmissione |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | esce dall'app lasciando il beacon attivo in background |
| <kbd>Back</kbd> | chiude l'app |

## Menu Config

| Voce | Valori | Note |
|---|---|---|
| Broadcast Interval | 1-10 s (Google: 1-2 s) | ogni quanto viene inviato il beacon; Google richiede almeno ogni 2 s |
| Transmit Power | 0-6 dBm | più potenza = più portata, più consumo di batteria |
| Register Tag | | tipo di tag e importazione (vedi sopra) |
| Show MAC | Yes / No | mostra il MAC nella schermata principale |

L'app salva il proprio stato in `/ext/apps_data/findmy/findmy_state.txt`; è questo che permette al beacon di
riprendere dopo un riavvio.

## Tracciamento

- **Clone di AirTag**: il Flipper compare come il tuo AirTag nell'app Dov'è (Find My).
- **Clone di SmartTag**: in SmartThings (SmartThings Find), su un telefono o nel browser.
- **Chiavi OpenHaystack**: in OpenHaystack o macless-haystack.

## Risoluzione dei problemi

- **La posizione non si aggiorna mai**: la chiave / il MAC del tag sono ruotati prima che tu ne rimuovessi la
  batteria; ricattura i dati.
- **Il beacon si ferma dopo un riavvio**: controlla che la scheda SD sia inserita (il file di stato è su di essa) e
  che il beacon fosse su `Broadcast Active` prima dello spegnimento.
- **La batteria si scarica più rapidamente**: aumenta l'intervallo di trasmissione e riduci la potenza di
  trasmissione.

## Pagine correlate

- [App incluse in Unleashed](/it/apps/catalog)
- [Impostazioni](/it/start/settings)
