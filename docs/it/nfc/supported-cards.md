---
title: Carte supportate (parser)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Carte supportate (parser)

Per molte carte il Flipper non si limita a fare il dump della memoria, ma la **decodifica**: numero della carta, saldo,
corse residue, validità, dati della camera d'albergo, figura di un gioco… Lo fanno i **plugin parser**, piccoli file
`.fal` che l'app NFC carica dalla scheda SD dopo una lettura riuscita. Quando un parser riconosce la carta, la
schermata del risultato mostra i dati decodificati al posto del riepilogo grezzo; **More** porta al menu consueto.

Alcuni parser portano con sé anche le **chiavi** del sistema della carta (o una funzione di derivazione delle chiavi).
Per le carte MIFARE Classic questo significa che il Flipper legge la carta **completamente senza attacco a
dizionario**: il parser verifica prima che la carta appartenga al sistema, poi la legge con le chiavi giuste.

::: tip Unleashed
Unleashed include molti parser che non ci sono nel firmware di serie, in particolare per i sistemi russi e della CSI:
Umarsh, Zolotaya Korona (e Online), Kazan, Metromoney, Moscow Social Card, una Troika rielaborata, Plantain,
Troika+Plantain, i biglietti ferroviari suburbani PPK, oltre al filamento Bambu Lab, alle carte arcade
Banapass/Aime/AIC, alle testine Sonicare e ad altro (opera di @Leptopt1los, @assasinfil e di moltissimi contributori).
:::

## Elenco dei parser

Chiavi integrate = il parser può leggere la carta con le proprie chiavi (o con una derivazione), senza bisogno di
dizionario.

### Trasporti

| Carta (come mostrata) | Protocollo | Regione | Chiavi integrate | Mostra |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Mosca, Russia | sì | dati dell'applicazione trasporti |
| Plantain Card | MIFARE Classic | San Pietroburgo, Russia | sì | dati della carta, biglietto suburbano PPK |
| Troika+Plantain | MIFARE Classic | Russia | sì | entrambe le applicazioni su una sola carta |
| Social card (Moscow Social Card) | MIFARE Classic | Mosca, Russia | sì | numero della carta (OMC), validità |
| Kazan transport card | MIFARE Classic | Kazan, Russia | sì | tipo di biglietto, saldo |
| Umarsh | MIFARE Classic | Russia (sistemi regionali) | no (serve la chiave B per i settori 0, 8, 12) | dati della carta |
| Zolotaya korona | MIFARE Classic | Russia | no | dati della carta |
| Zolotaya korona (Online) | MIFARE Classic | Russia | no | dati della carta e della tariffa |
| SZPPK Accompany Card | MIFARE Classic | Russia, ferrovia suburbana (SZPPK) | sì | validità, stazione, entrata/uscita, contatore dei passaggi |
| SKPPK Transport Card | MIFARE Classic | Russia, ferrovia suburbana (SKPPK) | sì | stazione, ultimo passaggio, stato, contatore dei passaggi |
| SevPPK Transport Card | MIFARE Classic | Russia, ferrovia suburbana (SevPPK) | sì | stazione, ultimo passaggio, stato, contatore dei passaggi |
| Metromoney | MIFARE Classic | Tbilisi, Georgia | sì | dati del biglietto |
| CharlieCard | MIFARE Classic | Boston (MBTA), USA | sì | saldo, transazioni |
| Clipper | MIFARE DESFire | area della baia di San Francisco, USA | — | numero di serie, saldo, corse (azienda, tariffa, data) |
| Ventra | MIFARE Ultralight | Chicago (CTA), USA | — | corse residue, scadenza |
| Tarjeta Bip! | MIFARE Classic | Santiago, Cile | sì | numero della carta, saldo |
| SmartRider | MIFARE Classic | Perth, Australia | sì | saldo, agevolazione, numero di serie |
| Opal | MIFARE DESFire | Sydney, Australia | — | saldo, ultima entrata/uscita |
| myki | MIFARE DESFire | Melbourne, Australia | — | numero della carta |
| ITSO Card | MIFARE DESFire | Regno Unito | — | dati della carta |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, Cina | — | saldo, data di vendita |
| All-In-One | MIFARE Ultralight | biglietto per il trasporto | — | numero, corse residue |

### Accessi, alberghi, pagamenti e servizi

| Carta (come mostrata) | Protocollo | Cosa è | Chiavi integrate | Mostra |
|---|---|---|---|---|
| HID Card | MIFARE Classic | credenziale HID memorizzata su una carta Classic | sì | lunghezza in bit e valore della credenziale |
| Gallagher NZ | MIFARE Classic | controllo accessi Gallagher (Nuova Zelanda) | — | credenziali (una carta può contenerne diverse) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | serrature alberghiere Saflok | sì (KDF) | numero della struttura, ID della chiave, record della chiave, livello di accesso |
| H World Card | MIFARE Classic | chiavi degli hotel H World (Cina continentale) | sì | numero della camera, date di check-in e di scadenza |
| CSC Service Works | MIFARE Classic | carta prepagata ricaricabile per lavanderie (USA) | — | saldo, ultima ricarica, utilizzi residui |
| WashCity | MIFARE Classic | carta per lavanderie WashCity / MarkItaly (Europa) | sì | saldo in EUR |
| MiZIP Card | MIFARE Classic | chiavi per distributori MiZIP | sì | UID, credito, credito precedente |
| Microel Card | MIFARE Classic | chiavi per distributori Microel | sì (derivate dall'UID) | UID, credito, credito precedente |
| HI! Card | MIFARE Classic | carta HI! | sì | UID |
| MyKey | ST25TB | chiavi per distributori MyKey | — | numero di serie, stato vuoto/bloccato, LockID |
| EMV | EMV | carte bancarie | — | vedi [Carte bancarie (EMV)](/it/nfc/emv) |

### Giochi, giocattoli e altro

| Carta (come mostrata) | Protocollo | Cosa è | Chiavi integrate |
|---|---|---|---|
| Aime Card | MIFARE Classic | carta arcade SEGA Aime (codice di accesso) | sì |
| Banapass | MIFARE Classic | Bandai Namco Passport (codice di accesso, valore) | sì |
| Amusement IC Card | FeliCa | carte arcade (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | figure Skylanders (nome del personaggio) | sì |
| Disney Infinity | MIFARE Classic | figure Disney Infinity | sì (derivate) |
| Bambu Lab Filament | MIFARE Classic 1K | tag delle bobine di filamento Bambu Lab (tipo, codice del filamento, materiale, colore…) | sì (derivate) |
| Philips Sonicare head | MIFARE Ultralight | testine degli spazzolini Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | messaggi NDEF: URI (anche telefono e mail), Text, MAC Bluetooth, Contact, Wi-Fi, SmartPoster | — |

Il codice sorgente di ogni parser si trova in
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Alcuni parser usano tabelle di consultazione in `/ext/nfc/assets/` (per esempio `skylanders.nfc`, `vendors.nfc`,
`sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` per i nomi delle stazioni, `aid.nfc`/`country_code.nfc`/`currency_code.nfc` per
EMV).

## Note

- Il parser di una carta con "chiavi integrate" verifica prima la carta; se la verifica fallisce (chiavi diverse,
  sistema diverso) parte il normale attacco a dizionario.
- Alcuni parser dicono cosa manca, per esempio *"Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A DICTIONARY ATTACK
  TO READ THE TICKET SECTORS"*.
- **"Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources."**: i file `.fal` sulla scheda
  SD non corrispondono al firmware. Reinstalla il firmware con la scheda SD inserita.
- Un parser si limita a mostrare i dati. Modificare un saldo in un dump ed emularlo è una frode nei sistemi di
  trasporto e di pagamento.

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [Carte bancarie (EMV)](/it/nfc/emv) · [MIFARE Classic](/it/nfc/mifare-classic) ·
[Carte Moskvyonok](/it/nfc/moskvyonok)
