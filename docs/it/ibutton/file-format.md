---
title: Formato dei file
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Formato dei file delle chiavi iButton (`.ibtn`)

Le chiavi salvate sono memorizzate in `/ext/ibutton/` con estensione `.ibtn`. Un file contiene una chiave con tutti i
dati richiesti dal suo protocollo.

## Esempio

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Una chiave DS1990 (i byte sono un esempio; una ROM reale termina con un CRC valido):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Una chiave Cyfral:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Versione 2 (attuale)

I campi che seguono `Protocol` dipendono dal protocollo.

| Campo | Tipo | Descrizione |
|---|---|---|
| `Protocol` | stringa | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | ROM da 8 byte (solo protocolli Dallas) |
| `Sram Data` | hex | Contenuto della SRAM (DS1992: 128 byte, DS1996: 8192 byte) |
| `Eeprom Data` | hex | Contenuto della EEPROM (DS1971: 32 byte) |
| `Data` | hex | Codice della chiave (Cyfral: 2 byte, Metakom: 4 byte) |

Note:
- **(non-specific)** è la categoria generica per i dispositivi 1-Wire sconosciuti (voce di menu *Dallas
  (non-specific)*). Contiene solo la ROM e non esegue alcun controllo — usala per chiavi con family code o CRC
  deliberatamente non validi. Il firmware la salva come `Protocol: (non-specific)`; il nome `DSGeneric` usato dalla
  documentazione ufficiale e dai file più vecchi è ancora accettato.
- **DS1420** è pienamente compatibile con il DS1990; cambia solo il family code (`0x81` invece di `0x01`).
- I nuovi protocolli non richiedono un aumento della versione del formato — ogni protocollo definisce i propri campi.

## Versione 1 (obsoleta)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Campo | Tipo | Descrizione |
|---|---|---|
| `Key type` | stringa | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Dati della chiave |

I file in versione 1 vengono ancora caricati (`Dallas` viene interpretato come DS1990) e sono convertiti alla
versione 2 quando li salvi.

## Pagine correlate

- [Protocolli](/it/ibutton/protocols) · [Aggiunta manuale](/it/ibutton/add-manually) ·
  [Lettura](/it/ibutton/read)
