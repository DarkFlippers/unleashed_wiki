---
title: Scrittura su chiavi vergini
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# Scrivere chiavi iButton su vergini

Le chiavi iButton originali hanno un ID di fabbrica che non può essere modificato. Per copiarne una serve una
**vergine** (*blank*) — una chiave riscrivibile il cui ID può essere programmato. Flipper Zero offre due modalità di
scrittura:

- **Write ID** — scrive l'ID (ROM / codice) su una vergine. È il classico "fammi una copia della chiave del citofono".
- **Full Write on Same Type** — solo per DS1992, DS1996 e DS1971: copia il contenuto della **memoria** su un'altra
  chiave autentica dello stesso tipo (DS1992 → DS1992). La chiave di destinazione conserva il proprio ID.

## Vergini supportate

| Vergine (come in Settings) | Scrive | Note |
|---|---|---|
| **RW1990.1** | ID di DS1990, DS1420 | Vergini di tipo RW1990; questa variante scrive i bit invertiti |
| **RW1990.2** | ID di DS1990, DS1420 | Vergini di tipo RW1990, variante non invertita |
| **TM2004** | ID di DS1990, DS1420, DS1992, DS1996, DS1971 e 1-Wire generico | Vergini RW2004/TM2004; viene scritto solo l'ID, anche se la vergine ha memoria |
| **TM01x** | ID DS1990, **Cyfral**, **Metakom** | Vergini TM01/TM01x |

Le vergini vendute come RW1990, TM1990 o TM08v2 sono gestite dalle varianti RW1990; il Flipper le prova entrambe,
quindi non è necessario sapere quale hai in mano.

::: tip Unleashed
- **Settings → Write Blanks** permette di attivare e disattivare i tipi di vergine (tutti sono su ON per impostazione
  predefinita).
- La schermata di scrittura mostra quale vergine viene tentata, e la schermata di successo indica *Written to TM2004!*
  e simili.
- Le chiavi **Cyfral e Metakom** possono essere scritte su vergini **TM01x**.
:::

::: warning TM01x per Cyfral / Metakom è un'operazione irreversibile
Per Cyfral e Metakom la vergine TM01x viene scritta, riletta e confrontata, e poi **finalizzata** in modalità Cyfral o
Metakom. La finalizzazione non si può annullare: la vergine non risponde più come dispositivo 1-Wire e non può essere
riscritta — nemmeno come chiave Dallas. Se la verifica non va a buon fine, la vergine non viene finalizzata e resta
scrivibile. Un ID Dallas scritto su una TM01x non comporta la finalizzazione.

Le chiavi Metakom con parità errata vengono rifiutate (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Apri la chiave: `Saved` → chiave → **Write ID** (oppure **More → Write ID** dopo la lettura).

   ![Menu della chiave salvata con Emulate, Write ID, Edit e Rename](/screens/ibutton/saved_menu.png)

2. Lo schermo mostra **Writing ID**, `[Protocol]`, il nome della chiave (o *Unsaved Key*) e, tra parentesi, il tipo di
   vergine in prova — per esempio `(RW1990.1)`.

   ![Schermata Writing ID con il protocollo [DS1990], il nome della chiave e la vergine in prova, (RW1990.1)](/screens/ibutton/write.png)

3. Appoggia la vergine alla **parte piatta** della piazzola (pin dati di sinistra + massa centrale), come in lettura.
   Tienila ferma.
4. Il Flipper prova ogni vergine abilitata in grado di contenere questo protocollo e rilegge il risultato.
5. **Written to RW1990.2!** (oppure *Successfully written!*) — operazione completata.

## Full Write on Same Type

1. `Saved` → chiave DS1992 / DS1996 / DS1971 → **Full Write on Same Type**.
2. Lo schermo mostra **Full Writing**. Appoggia una chiave autentica dello **stesso** tipo.
3. La memoria viene scritta; l'ID della chiave di destinazione resta il suo. Questa modalità non usa l'impostazione
   Write Blanks.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` elenca **RW1990.1**, **RW1990.2**, **TM2004**, **TM01x** con
**ON**/**OFF**. Si commutano con <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd>; l'impostazione viene salvata all'uscita in
`/ext/ibutton/.ibutton.settings`. Il comando CLI `ikey write` usa la stessa impostazione.

Se la pagina segnala *Settings page missing. Update the SD resources*, reinstalla il firmware con la scheda SD
inserita.

## Errori

| Schermata | Significato |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | Tutti i tipi di vergine sono su OFF |
| **Cannot Write** — *No enabled blank can write this key* | Per esempio solo RW1990 abilitata per una chiave Metakom |
| **Cannot Write** — *This key cannot be written* (o il motivo indicato dal protocollo) | I dati della chiave non sono validi per la scrittura |
| La schermata di scrittura resta attiva, il LED lampeggia | Nessuna vergine rilevata — controlla il contatto, oppure il tipo di vergine non è supportato |

## Risoluzione dei problemi

- **Contatto.** Il centro della vergine deve toccare il pin dati e la sua corona il pin di massa.
- **Tipo di vergine sconosciuto.** Prova ad abilitare tutti i tipi. Alcune vergini economiche sono di tipi che il
  Flipper non riesce a programmare.
- **"Successo" ma il lettore rifiuta la copia.** Alcuni lettori filtrano le vergini (ne riconoscono il
  comportamento) — su questo il Flipper non può fare nulla.
- **TM01x esaurita.** Una TM01x finalizzata come Cyfral/Metakom non può essere riutilizzata.

## Pagine correlate

- [Lettura](/it/ibutton/read) · [Protocolli](/it/ibutton/protocols) · [Aggiunta manuale](/it/ibutton/add-manually)
