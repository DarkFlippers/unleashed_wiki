---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** e **BFT Mitto** costruiscono il loro codice rolling a partire da un **Seed** segreto. Senza di esso il Flipper non può decodificare questi telecomandi (vengono letti come `KL: Unknown` oppure non vengono letti affatto) e non può costruire un telecomando che il ricevitore accetti. **Seed Capturer** (di @xMasterX) raccoglie il materiale grezzo per recuperare il Seed: il `Fix` del telecomando e una serie di valori `Hop` consecutivi.

**Non** recupera il Seed da sé e **non trasmette mai**: si limita ad ascoltare e a scrivere un file. La ricerca viene eseguita nell'app companion [qUnleashed](/it/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer è un'app di sistema integrata di Unleashed, e qUnleashed legge le sue acquisizioni direttamente dal Flipper. Una volta noto il Seed, Unleashed può decodificare il telecomando e crearne di nuovi tramite `Add Manually [Advanced]`.
:::

## Quando serve

- La programmazione via radio del ricevitore è disabilitata, quindi l'unica strada è un clone di un telecomando noto —
  e un clone richiede il Seed.
- Il tuo telecomando FAAC / Genius è uno **slave**, che non può inviare il codice di programmazione.
- Non riesci a raggiungere il ricevitore.
- Installazioni **Erreka** in cui tutti i telecomandi condividono un unico Seed.
- Telecomandi **BFT Mitto più vecchi** con un Seed unico, quando la strada del tasto di programmazione non funziona (i
  telecomandi BFT più recenti derivano il Seed dal seriale e si decodificano con un normale Read).

Se il telecomando può essere messo in modalità di programmazione, spesso il Seed viene inviato in chiaro — quella strada è più rapida; vedi [Il Flipper come nuovo telecomando](/it/subghz/remote-prog).

## Acquisizione

1. Apri `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Scegli `New capture`.
3. **Tipo di telecomando:** `FAAC SLH`, `Genius`, `Erreka` o `BFT Mitto`.
4. **Frequenza:** `433.92 MHz  AM650` oppure `868.35 MHz  AM650` (`BFT Mitto` propone solo 433.92 MHz).
5. Premi **lo stesso tasto dello stesso telecomando** ripetutamente, circa una volta al secondo, con il telecomando
   appoggiato al Flipper.
6. Osserva lo schermo:
   - `Fix XXXXXXXX` — la parte fissa del telecomando; l'app si aggancia alla prima che sente;
   - `Hops n/10  Xpkt` — quanti hop **diversi** sono stati raccolti, e il conteggio dei pacchetti grezzi;
   - lo stato `Hop n: XXXXXXXX` ogni volta che ne arriva uno nuovo.
7. Da **2 hop** in poi compare `Save` su <kbd>OK</kbd>. Premilo; l'app mostra `Saved N hops` e il nome del file.

<kbd>←</kbd> (`Reset`) scarta l'acquisizione, così puoi agganciarti a un altro telecomando o tasto.

| Stato | Significato |
|---|---|
| `Hop n: XXXXXXXX` | nuova parte rolling memorizzata — continua a premere |
| `Other remote XXXXXXXX` | un altro telecomando o un altro tasto — ignorato |
| `Same hop, ignored` | la ripetizione dell'ultima pressione |
| `Have 10, enough` | completo — premi `Save` |

**Quante pressioni:** 2 è il minimo, 5–10 è meglio. Conta altrettanto il fatto che le pressioni siano **consecutive e senza salti**: controlla che `Hops` aumenti a ogni pressione. Se ne manca una, premi `Reset` e ricomincia.

::: warning
Su **FAAC SLH e Genius il Seed è diverso per ogni tasto** — acquisisci il tasto che intendi davvero usare. Su Erreka il Seed è per telecomando (a volte per installazione), su BFT Mitto per telecomando.
:::

## Le altre voci di menu

- `Decode RAW file` — ricava Fix/Hop da un `.sub` RAW (da `/ext/subghz`) registrato in precedenza con
  [Read RAW](/it/subghz/read-raw); la frequenza viene presa dal file. Un file chiave viene rifiutato con
  `Not a RAW capture`. Qui <kbd>←</kbd> è `Back` invece di `Reset`.
- `Delete all captures` — chiede `Delete every capture file in subghz_seed_captures?`, poi li elimina.
- `Exit`.

## Il file di acquisizione

I file finiscono in `/ext/apps_data/subghz_seed_captures/`, con nome `<Type>_<Fix>_<date-time>.txt`, per esempio `Erreka_F00F1C9B_261008-142233.txt`. È un file di testo, **non un `.sub` riproducibile**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Recuperare il Seed in qUnleashed

1. Collega il Flipper a **qUnleashed** e apri il suo strumento di recupero del Seed. Preleva da sé le acquisizioni da
   `subghz_seed_captures` — senza copiare né rinominare nulla.
2. Scegli l'acquisizione e avvia la ricerca (una ricerca in forza bruta, ed è per questo che non viene eseguita sul
   Flipper).
3. Se il Seed viene trovato, qUnleashed può comporre il `.sub` del clone già pronto (seriale e tasto da `Fix`, più
   Seed e contatore) e caricarlo sul Flipper.
4. Se non viene trovato nulla, è molto probabile che l'acquisizione avesse un salto — riacquisisci con attenzione.

Con il Seed puoi anche costruire telecomandi a mano in `Sub-GHz → Add Manually [Advanced]`: un tuo `SERIAL` + il `SEED` per un nuovo telecomando, oppure il `SERIAL`/`BUTTON` dell'originale + `SEED` + un `COUNTER` leggermente più alto per un clone. Un clone entra in conflitto con l'originale per il contatore — vedi [Codici rolling](/it/subghz/rolling-codes).

::: warning
Solo per telecomandi e ricevitori di tua proprietà.
:::

## Pagine correlate

- [Il Flipper come nuovo telecomando](/it/subghz/remote-prog) · [KeeLoq](/it/subghz/keeloq) · [Add Manually](/it/subghz/add-manually)
- [App qUnleashed](/it/mobile/qunleashed-app)
