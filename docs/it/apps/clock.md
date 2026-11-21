---
title: Clock
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Clock

Un orologio da comodino: ora in caratteri grandi, data e livello della batteria, regolazione della luminosità dello
schermo con luce notturna a LED rosso, un cronometro e una sveglia giornaliera. Basato su FlipperNightStand di
@nymda, con @Willy-JL, @mishamyte e @xMasterX (versione dell'app 1.3).

`Main Menu → Clock`

![Clock: la data sopra il grande display dell'ora e il livello della batteria sotto](/screens/apps/clock.png)

::: tip Unleashed
In Unleashed Clock è un'app del menu principale con sveglia e luce notturna. Se vuoi soltanto l'ora sul desktop,
attiva invece `Settings → Desktop → Show Clock`.
:::

## Pulsanti nella schermata dell'orologio

| Pulsante | Azione |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | aumenta / riduce la luminosità dello schermo (compare una barra che si nasconde 3 s dopo l'ultima pressione) |
| <kbd>↓</kbd> con luminosità a 0 | accende / spegne la luce notturna a LED rosso tenue |
| <kbd>OK</kbd> | avvia / ferma il cronometro |
| <kbd>←</kbd> | azzera il cronometro |
| <kbd>→</kbd> | configurazione della sveglia |
| <kbd>Back</kbd> | esce |

L'ora segue il formato di sistema: 12 ore con AM/PM oppure 24 ore, come impostato in
`Settings → System → Time Format`.

## Cronometro

1. Premi <kbd>OK</kbd> per avviarlo; il tempo in corso compare come `MM:SS`.
2. Premi di nuovo <kbd>OK</kbd> per fermarlo, un'altra volta per continuare.
3. Premi <kbd>←</kbd> (**Reset**) per azzerarlo.

## Sveglia giornaliera

1. Nella schermata dell'orologio premi <kbd>→</kbd>.
2. Imposta **Alarm** su **ON** con <kbd>←</kbd> / <kbd>→</kbd>.
3. Seleziona **Set time** e premi <kbd>OK</kbd>.
4. Nel selettore `Alarm time`: <kbd>←</kbd> / <kbd>→</kbd> scelgono ore, minuti (e AM/PM in modalità 12 ore),
   <kbd>↑</kbd> / <kbd>↓</kbd> cambiano il valore (tieni premuto per la ripetizione). <kbd>OK</kbd> o <kbd>Back</kbd>
   salvano.
5. Premi <kbd>Back</kbd> per tornare all'orologio. L'ora della sveglia è mostrata nella schermata dell'orologio.

Quando la sveglia suona, lo schermo lampeggia con `! ALARM !` e `Press any key to stop`, viene riprodotta una melodia
con vibrazione e LED rosso. Premi un tasto qualsiasi per fermarla. La sveglia resta attiva e suona di nuovo il giorno
successivo alla stessa ora.

::: warning
La sveglia suona solo con l'app Clock aperta. Lascia il Flipper sul caricatore con Clock in esecuzione per la notte.
:::

La sveglia e il livello di luminosità sono salvati in `/ext/apps_data/clock/` e ripristinati alla successiva apertura
dell'app.

## Pagine correlate

- [Desktop](/it/start/desktop)
- [Impostazioni](/it/start/settings)
- [App incluse in Unleashed](/it/apps/catalog)
