---
title: Protocolli supportati
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Protocolli a 125 kHz supportati

La tabella è ricavata da `lib/lfrfid/protocols/` del firmware Unleashed. Tutti i protocolli possono essere **letti**,
**salvati**, **emulati** e **aggiunti manualmente**; le ultime colonne indicano quali chip vergini possono
contenerli (vedi [Scrittura](/it/rfid/write)).

- **Nome** — come appare sullo schermo e come viene memorizzato nei file `.rfid` nel campo `Key type`.
- **Lettura** — quale passata di lettura lo decodifica: ASK, PSK o entrambe.
- **Byte** — lunghezza del campo `Data:`.

| Nome | Produttore | Lettura | Byte | Campi mostrati | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | come sopra (bit rate RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | come sopra (bit rate RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (Wiegand a 26 bit) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, paese, temperatura, flag animale… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | lunghezza in bit; formati HID corrispondenti | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, verifica CRC | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT a n bit (FC, Card) o RKKTH in chiaro (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = i target 8265/H5, 8210 e H5.5. ² L'8268 (Hitag S) accetta solo EM4100 al bit rate RF/64 ed è
disattivato per impostazione predefinita.

::: tip Unleashed
Rispetto all'elenco della documentazione ufficiale, questo firmware aggiunge **Indala224** e una passata di lettura a
**134,2 kHz** per FDX-A/FDX-B. Alla documentazione ufficiale sul formato dei file mancano anche EM4100/32, EM4100/16,
Electra, Nexwatch, Radio Key, Noralsy e Indala224 — qui sono valori validi di `Key type`.
:::

## Note su alcuni protocolli

- **EM4100 / EM-Marin** — il tipo di portachiavi più diffuso nella CSI ("ЕМ-Марин"). ID a 40 bit; il FC è il terzo
  byte, il numero di tessera gli ultimi due. DEZ 8 / DEZ 10 sono le forme decimali stampate sui portachiavi.
- **Casi-Rusco C10106** — non è un protocollo a sé; è un frame EM4100 (di solito RF/32). Quando i dati corrispondono,
  la schermata informativa aggiunge una riga `or C10106: credential card`, e Add Manually lo propone come formato di
  inserimento.
- **HIDProx** — contenitore HID Prox generico da 26 a 37 bit. Il Flipper prova le strutture note (H10304, H10302,
  S10401, H10306, Corp1000-35) e stampa FC e numero di tessera per ogni corrispondenza.
- **Paradox** — la schermata informativa mostra il CRC e il messaggio *CRC Mismatch, Invalid Card!* se non
  corrisponde.
- **Vecchio nome di Indala26** — i file molto vecchi con `Key type: I40134` vengono convertiti in Indala26 al
  caricamento.

## Pagine correlate

- [Lettura](/it/rfid/read) · [Aggiunta manuale](/it/rfid/add-manually) · [Scrittura](/it/rfid/write) ·
  [Microchip per animali](/it/rfid/animal-microchips) · [Formato dei file](/it/rfid/file-format)
