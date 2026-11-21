---
title: Radio Settings (impostazioni radio)
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings

`Main Menu → Sub-GHz → Radio Settings` contiene le impostazioni che valgono per l'intera app Sub-GHz: quale radio
viene usata, la potenza di trasmissione, la denominazione dei file e il comportamento del contatore rolling. Le
impostazioni di ricezione (frequenza, modulazione, hopping, filtri) si trovano in `Read → Config` — vedi
[Read](/it/subghz/read#config).

::: tip Unleashed
Nel firmware di serie questo menu permette solo di passare dal modulo interno a quello esterno. Unleashed aggiunge
**TX Power**, **Protocol Names**, **Counter Incr.** e, in modalità Debug, **Ext Amp & LEDs** e **Debug Pin**.
:::

## Voci di menu

![Radio Settings: Module, TX Power, Protocol Names e Counter Incr.](/screens/subghz/radio_settings.png)

| Voce | Valori | Cosa fa |
|---|---|---|
| `Module` | `Internal`, `External` | Radio usata per ricezione e trasmissione. `External` è proposto solo quando viene rilevato un CC1101 esterno sul GPIO; se non risponde, il Flipper torna a `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Potenza di trasmissione. `Preset` = quella definita dal preset di modulazione (predefinito). I valori più bassi sono comodi per prove a breve distanza |
| `Protocol Names` | `OFF` / `ON` | Con `ON`, i nomi di file generati automaticamente contengono il nome del protocollo + timestamp invece del solo timestamp/nome casuale |
| `Counter Incr.` | `+1`, `+2`, `+3` (normale) | Di quanto viene incrementato il contatore rolling a ogni trasmissione per i protocolli dinamici. Predefinito `+1` |

Voci aggiuntive in **modalità Debug** (`Settings → System → Debug → ON`):

| Voce | Valori | Cosa fa |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Elenco completo dei passi del contatore per esperimenti: salti ampi, `OVFL` (passo 65535), `OFEX` (modalità speciale), `No` (contatore non modificato) e passi negativi |
| `Ext Amp & LEDs` | `ON` / `OFF` | Controlla il pin dell'amplificatore / dei LED dei moduli esterni (GPIO PC3, come sui moduli E07). Predefinito `ON`. Disattivalo se il tuo modulo usa quel pin per altro |
| `Debug Pin` | `OFF` / `17(1W)` | Replica il segnale dati della radio sul pin GPIO 17 (1-Wire) — per lo sviluppo di protocolli con un analizzatore logico |

`TX Power`, `Protocol Names` e `Ext Amp & LEDs` vengono salvati immediatamente (in
`/ext/subghz/assets/last_subghz.settings`). `Counter Incr.` non viene salvato: resta attivo fino al riavvio del
Flipper, poi torna a `+1`.

::: warning Incremento del contatore
I passi di contatore ampi o negativi sono per esperimenti **su ricevitori di tua proprietà**. Portare un contatore
molto avanti sposta in modo permanente il contatore memorizzato dal ricevitore oltre quello del tuo telecomando
originale; tornare indietro fa sì che il ricevitore ti ignori. Per convivere con il telecomando originale usa le
[Modalità contatore](/it/subghz/counter-mode) oppure crea un nuovo telecomando con
[Add Manually](/it/subghz/add-manually). Contesto: [Codici rolling](/it/subghz/rolling-codes).
:::

## Altre impostazioni che vivono sulla scheda SD

| File | Scopo | Dettagli |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Frequenze aggiuntive, elenco dell'hopper, frequenza predefinita, preset di modulazione personalizzati | [Frequenze e portata](/it/subghz/frequencies#adding-frequencies), [Formati dei file](/it/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Gamma di frequenze estesa (fuori specifica) | [Frequenze e portata](/it/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Le tue chiavi del produttore KeeLoq | [Formati dei file](/it/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/it/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Ultima frequenza, modulazione, filtri e trigger dell'analizzatore usati — scritto dall'app | non modificarlo a mano |

I file che terminano con `.example` sono modelli: rinominali in `…_user` per attivarli. I file `_user` non vengono
sovrascritti dagli aggiornamenti del firmware.

## Risoluzione dei problemi

- **`Module` mostra solo `Internal`** — nessun CC1101 esterno rilevato. Controlla i collegamenti e l'alimentazione,
  poi rientra nel menu. Vedi [Modulo CC1101 esterno](/it/subghz/external-cc1101).
- **I segnali sono deboli in trasmissione** — verifica che `TX Power` non sia impostato su un valore negativo.
- **I nomi dei file sono solo date** — attiva `Protocol Names`.
- **Mancano le voci `Ext Amp & LEDs` / `Debug Pin`** — compaiono solo in modalità Debug.

## Pagine correlate

- [Read → Config](/it/subghz/read#config) · [Frequenze e portata](/it/subghz/frequencies) · [Modulo CC1101 esterno](/it/subghz/external-cc1101)
- [Modalità contatore](/it/subghz/counter-mode) · [Formati dei file](/it/subghz/file-format) · [Impostazioni pericolose](/it/start/dangerous-settings)
