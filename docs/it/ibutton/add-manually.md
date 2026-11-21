---
title: Aggiungere chiavi manualmente
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Aggiungere chiavi iButton manualmente

Puoi creare una chiave virtuale partendo dal suo ID senza avere la chiave fisica — per esempio da un numero inciso
sulla chiave o annotato in precedenza. La chiave può essere emulata e, per i protocolli scrivibili,
[scritta su una vergine](/it/ibutton/write).

## Procedura

1. Vai su `Main Menu → iButton → Add Manually`.
2. Scegli il protocollo:

   | Voce di menu | ID da inserire |
   |---|---|
   | **Dallas DS1990** | 8 byte di ROM |
   | **Dallas DS1992** | 8 byte di ROM |
   | **Dallas DS1996** | 8 byte di ROM |
   | **Dallas DS1971** | 8 byte di ROM |
   | **Dallas DS1420** | 8 byte di ROM |
   | **Dallas (non-specific)** | 8 byte di ROM — qualunque dispositivo 1-Wire, nessun controllo |
   | **Cyfral** | 2 byte |
   | **Metakom** | 4 byte (ogni byte deve avere la parità corretta) |

   ![Elenco dei tipi di chiave in Add Manually: Dallas DS1990, DS1992, DS1996 e DS1971](/screens/ibutton/add_manually.png)

3. La schermata **Enter the key** apre un editor esadecimale. Digita i byte e premi **Save**.
4. Inserisci un nome (prefisso predefinito `iBtn`) e salva. La chiave viene memorizzata in
   `/ext/ibutton/<name>.ibtn`.

## Modificare una chiave salvata

`Main Menu → iButton → Saved` → chiave → **Edit** → modifica l'esadecimale → **Save** → nome → **Save**.

## Note sugli ID Dallas

Una ROM Dallas è composta da `family code` (1 byte) + `serial` (6 byte) + `CRC` (1 byte):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- La maggior parte delle chiavi dei citofoni sono DS1990 con family code `01`.
- Se il CRC è errato, un lettore può rifiutare la chiave e il Flipper segnala un errore di CRC quando la rilegge.
- Ti serve una chiave con family code o CRC deliberatamente non validi? Usa **Dallas (non-specific)** — non esegue
  alcun controllo.
- Una chiave aggiunta manualmente **non ha dati di memoria**; Full Write on Same Type richiede una lettura reale.

::: tip Editor di byte
In Unleashed, premendo ripetutamente <kbd>↑</kbd> nell'input dei byte si apre un mini editor di nibble — comodo per
gli ID lunghi.
:::

## Pagine correlate

- [Lettura](/it/ibutton/read) · [Scrittura](/it/ibutton/write) · [Protocolli](/it/ibutton/protocols) ·
  [Formato dei file](/it/ibutton/file-format)
