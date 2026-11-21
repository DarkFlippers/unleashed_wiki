---
title: Impostazioni pericolose
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Impostazioni pericolose: range Sub-GHz esteso

Unleashed può far lavorare la radio CC1101 **fuori dal suo range di frequenza ufficiale**. Questa pagina spiega cosa
fa l'impostazione, perché quasi certamente non ti serve e come attivarla se ti serve davvero.

::: danger Leggi prima questo
1. Non farlo se non sai esattamente cosa stai facendo.
2. Il range esteso non serve praticamente per nessun caso d'uso.
3. Trasmettere fuori dalle specifiche hardware **può danneggiare l'hardware**.
4. Né il team di Flipper Devices né gli sviluppatori di Unleashed sono responsabili per eventuali danni causati da
   firmware personalizzati o dall'estensione del range di frequenza.
:::

## Probabilmente non ti serve: non esiste nessun blocco regionale

::: tip Unleashed
In Unleashed **tutte le restrizioni regionali sulla trasmissione sono rimosse per impostazione predefinita**. Ogni
frequenza all'interno del range supportato dal chip trasmette senza passaggi aggiuntivi. Non usare l'impostazione
pericolosa per "sbloccare la tua regione": per quello non serve.
:::

Se la trasmissione è bloccata su una frequenza, controlla prima che la frequenza sia all'interno del normale range di
trasmissione indicato qui sotto. Al di fuori, il firmware registra `Frequency blocked - outside default range`.

## Range di frequenza

| | Range |
|---|---|
| Datasheet del CC1101 | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Range di **trasmissione** predefinito di Unleashed | ≈ 300–350 MHz, 387–467.75 MHz, 779–928 MHz (allargato per includere 350 MHz e 467 MHz) |
| Trasmissione con `dangerous_settings` attivo | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

Il range esteso corrisponde al range esteso dello YARD Stick One (secondo il sorgente del firmware). Fuori dai range
del datasheet il chip lavora fuori specifica, e trasmettere lì può danneggiarlo.

## Come attivarla

1. Estrai la scheda microSD, oppure collegati con qFlipper o con il file manager che preferisci.
2. Apri il file **`/ext/subghz/assets/dangerous_settings`**. Si presenta così:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Leggi i commenti, poi cambia `false` in `true`:
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Salva il file e riavvia il Flipper. L'impostazione viene letta all'avvio.

Per tornare indietro, riporta il valore a `false` e riavvia.

::: warning Aggiornamenti
Il file fa parte delle risorse del firmware. Un aggiornamento può sovrascriverlo con il valore predefinito `false`.
Controllalo dopo un aggiornamento se dipendi da questa impostazione.
:::

## Argomenti correlati

- Frequenze e preset Sub-GHz, aggiungere frequenze proprie: [Frequenze](/it/subghz/frequencies)
- Impostazioni Sub-GHz all'interno dell'app: [Impostazioni Sub-GHz](/it/subghz/settings)
- Modulo CC1101 esterno: [CC1101 esterno](/it/subghz/external-cc1101)

Usa la radio solo sui tuoi dispositivi e nel rispetto delle normative radio locali.
