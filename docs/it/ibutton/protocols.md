---
title: Protocolli supportati
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Protocolli iButton supportati

Ricavato da `lib/ibutton/protocols/` del firmware Unleashed. Il firmware raggruppa i protocolli in **Dallas** (1-Wire)
e **misc** (Cyfral, Metakom).

| Protocollo (nome del file) | Voce di menu | Family code | Memoria | Emulazione | Write ID su | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 B EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | qualsiasi | — (solo ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | codice da 2 byte | ✓ | TM01x | — |
| `Metakom` | Metakom | — | codice da 4 byte | ✓ | TM01x | — |

## Dallas 1-Wire

La "touch memory" di Dallas Semiconductor (oggi Analog Devices). Ogni dispositivo ha una ROM da 8 byte: family code,
seriale a 48 bit e CRC-8. Il Flipper verifica il CRC e identifica il tipo in base al family code.

- **DS1990 (DS1990A)** — la classica chiave di solo ID usata dalla maggior parte dei citofoni.
- **DS1420** — pienamente compatibile con il DS1990, cambia solo il family code (`81` invece di `01`).
- **DS1992 / DS1996** — chiavi con memoria SRAM; DS1971 — con EEPROM. Il Flipper legge la memoria, può mostrarla
  (**Data Info**), emularla e copiarla su una chiave dello stesso tipo.
- **Dallas (non-specific)** — categoria generica per qualunque altro dispositivo 1-Wire: viene letta solo la ROM e non
  si verifica nulla. Utile anche per creare una chiave con family code o CRC intenzionalmente errati.

## Cyfral

Un protocollo per chiavi di citofono diffuso in Russia e nella CSI; non è 1-Wire. Il codice è memorizzato in 2 byte. Può essere emulato e scritto su una vergine TM01x.

## Metakom

Un altro protocollo per citofoni della CSI. Il codice è di 4 byte, ogni byte porta un bit di parità — una chiave con
parità errata viene segnalata come non valida e non viene scritta. Può essere emulata e scritta su una vergine TM01x.

## Vergini

| Vergine | Accetta | Comportamento |
|---|---|---|
| **RW1990.1** | ROM Dallas (8 byte) | Sblocco, scrittura (bit invertiti), blocco |
| **RW1990.2** | ROM Dallas (8 byte) | Sblocco, scrittura, blocco |
| **TM2004** | ROM Dallas (8 byte) | Scrive dall'indirizzo 0 con rilettura e verifica di ogni byte |
| **TM01x** | ROM Dallas, Cyfral, Metakom | Cyfral/Metakom vengono scritti come frame a 36 bit (prefisso di 4 bit + 32 bit di codice), verificati e poi **finalizzati** (operazione irreversibile). Gli ID Dallas non vengono finalizzati |

Per l'uso pratico vedi [Scrittura](/it/ibutton/write).

::: tip Unleashed
La documentazione ufficiale non menziona il DS1420, l'impostazione Write Blanks né la scrittura su TM01x per
Cyfral/Metakom.
:::

## Pagine correlate

- [Lettura](/it/ibutton/read) · [Scrittura](/it/ibutton/write) · [Formato dei file](/it/ibutton/file-format)
