---
title: Protocolli
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Protocolli IR supportati

La libreria infrarossi (`lib/infrared/encoder_decoder/`) contiene un decoder e un encoder per ciascun protocollo
elencato qui sotto. Un segnale che corrisponde a uno di essi viene salvato come `type: parsed` (protocollo +
indirizzo + comando); tutto il resto viene salvato come `type: raw` e riprodotto come temporizzazioni. L'elenco e i
numeri di questa pagina sono presi dal codice sorgente del firmware.

::: tip Unleashed
**RCA** è un'aggiunta di Unleashed. Gli altri protocolli sono in comune con il firmware ufficiale.
:::

## Tabella dei protocolli

| Protocollo (valore di `protocol:`) | Famiglia | Bit di indirizzo | Bit di comando | Portante |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (esteso, senza byte invertiti) | 16 | 16 | 38 kHz |
| `NEC42` | NEC 42 bit | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC 42 bit esteso | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 esteso | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC 12 bit | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC 15 bit | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC 20 bit | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon…) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

Il duty cycle di tutti gli encoder integrati è il 33 %. Gli stessi nomi sono accettati dal comando CLI `ir tx`
(per esempio `ir tx NEC 0x04 0x08`) e sono ciò che `protocol:` deve contenere in un file `.ir`.

::: info Pioneer
Il protocollo `Pioneer` è implementato nel firmware (e usato nelle librerie Audio e TV) anche se l'elenco nel
documento ufficiale *InfraredFileFormats* non lo menziona ancora.
:::

## Riferimento delle temporizzazioni

Temporizzazioni di impulso/pausa dei protocolli principali, come definite negli encoder (µs). La tolleranza in
decodifica è di ±200 µs sul preambolo e di ±120 µs sui bit.

| Protocollo | Preambolo mark / space | Bit 1 mark / space | Bit 0 mark / space |
|---|---|---|---|
| NEC (tutte le varianti) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 unità da 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | nessuno (Manchester) | mezzo bit da 888 µs | |
| RC6 | 2666 / 889 | mezzo bit da 444 µs (Manchester) | |

## Cosa significano per te questi numeri

- **Apprendimento:** il ricevitore integrato è tarato su 38 kHz, ma i decoder per i protocolli a 36 kHz (RC5, RC6) e a
  40 kHz (Sony SIRC, Pioneer) ci sono, quindi anche quei telecomandi vengono appresi come segnali parsed.
- **Salvataggio:** un segnale parsed è minuscolo e robusto. Se un segnale decodificato non funziona sul tuo
  apparecchio, apprendilo come RAW (modalità debug `Learn New Remote RAW`, vedi
  [Apprendimento](/it/infrared/read#debug-mode-extras)).
- **I telecomandi sconosciuti** (la maggior parte dei telecomandi dei condizionatori: 181 dei 182 segnali di `ac.ir`
  sono RAW) non vengono interpretati affatto e sono sempre memorizzati come RAW. I segnali RAW possono contenere fino a
  1024 temporizzazioni; le acquisizioni RAW apprese sono normalmente memorizzate con `frequency: 38000` e
  `duty_cycle: 0.330000`.

## Pagine correlate

- [Formato dei file IR](/it/infrared/file-format)
- [Apprendere e inviare segnali](/it/infrared/read)
- [Telecomandi universali](/it/infrared/universal-remotes)
