---
title: Comandi
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Comandi

Il Flipper Zero ha un pad direzionale a 5 direzioni e un pulsante <kbd>BACK</kbd> separato.

| Pulsante | Cosa fa |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Si spostano tra i menu e sulle tastiere virtuali. <kbd>←</kbd>/<kbd>→</kbd> cambiano il valore dell'opzione selezionata |
| <kbd>OK</kbd> | Avvia un'app, conferma una scelta. La pressione lunga apre spesso azioni aggiuntive |
| <kbd>BACK</kbd> | Torna indietro o esce dall'app. La pressione lunga sul desktop apre la schermata di spegnimento |

In un elenco le frecce spostano la cornice sulla voce selezionata e <kbd>OK</kbd> la apre:

![Menu principale con la cornice su Sub-GHz](/screens/mainmenu/subghz.png)

In questa wiki "tieni premuto" o "pressione lunga" significa premere un pulsante per circa un secondo. I suggerimenti
dei pulsanti in basso nelle schermate (per esempio `◀ Cancel` o `Save ▶`) indicano cosa fanno <kbd>←</kbd>,
<kbd>OK</kbd> e <kbd>→</kbd> in quella schermata.

## Modalità per mancini

**Main Menu → Settings → System → Hand Orient → `Lefty`**

Lo schermo ruota di 180° e il pad viene rimappato, così puoi tenere il Flipper nella mano sinistra.

## Scorciatoie

| Azione | Come |
|---|---|
| Accensione | Tieni premuto <kbd>BACK</kbd> per circa 3 s |
| Spegnimento | Tieni premuto <kbd>BACK</kbd> sul desktop → **Power Off** (<kbd>→</kbd>) |
| Riavvio (dispositivo bloccato) | Tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per circa 5 s |
| Riavvio forzato (reset dell'alimentazione) | Scollega l'USB, tieni premuto <kbd>BACK</kbd> per circa 30 s |
| Riavvio in DFU (ripristino) | Tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd>, rilascia <kbd>BACK</kbd>, mantieni <kbd>←</kbd> finché il LED blu non si accende |

Tutte le combinazioni di reset e DFU, e i casi in cui ciascuna non funziona, sono in
[Combinazioni di tasti](/it/start/key-combos).

## Scorciatoie del desktop

| Pulsante | Pressione breve | Pressione lunga |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | App preferita (OK Long) |
| <kbd>↑</kbd> | Lock Menu | **Blocca il Flipper** (con PIN se ne è impostato uno) |
| <kbd>↓</kbd> | Archive | Informazioni sul dispositivo / schermata di debug |
| <kbd>←</kbd> | App preferita (Left Short), per impostazione predefinita il menu Apps | App preferita (Left Long) |
| <kbd>→</kbd> | Passport (o l'app assegnata) | App preferita (Right Long) |
| <kbd>BACK</kbd> | — | Schermata di spegnimento |

Le app si assegnano in **Settings → Desktop → Favorite App - …**. I dettagli sono nella pagina
[Desktop](/it/start/desktop).

::: tip Unleashed
Tenendo premuto <kbd>↑</kbd> sul desktop il dispositivo si blocca immediatamente (con il PIN se ne è impostato uno).
Nel firmware stock il blocco si attiva dal Lock Menu.
:::

Una pressione breve di <kbd>↑</kbd> apre il Lock Menu:

![Lock Menu: Turn Bluetooth On selezionato, con Mute e Dummy Mode sotto](/screens/desktop/lock_menu.png)

Se è impostato un PIN, il Flipper lo chiede prima di sbloccarsi. Le frecce digitano il codice, <kbd>BACK</kbd> lo
cancella e <kbd>OK</kbd> conferma:

![Enter PIN: quattro cifre inserite mostrate come asterischi, una quinta cella vuota, il suggerimento per cancellare e il pulsante OK](/screens/desktop/pin_input.png)

Una pressione lunga di <kbd>↓</kbd> apre la schermata informativa del dispositivo: uptime, revisione hardware, nome
del Flipper, versione e data di build del firmware, commit, versione delle API e il flag Debug. Una pressione lunga
di <kbd>OK</kbd> su quella schermata attiva o disattiva Debug:

![Schermata informativa: Uptime 1h23m45s, hardware 13.F7B9C6 R00, firmware unlshd-080 del 21-11-2026 e D:ON](/screens/desktop/debug.png)

## Feedback dei pulsanti

**Main Menu → Settings → Input**

| Voce | Valori | Significato |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Breve vibrazione a ogni evento dei pulsanti. I numeri più alti vibrano più a lungo |
| Vibro Trigger | `Press`, `Release`, `Both` | Quando scatta la vibrazione |

## Inserimento di testo

Sulla tastiera virtuale muoviti con le frecce e premi <kbd>OK</kbd> per digitare il carattere selezionato. Tieni
premuto <kbd>OK</kbd> su una lettera per scriverla in maiuscolo. Seleziona il tasto `⏎` / **Save** per confermare.
<kbd>BACK</kbd> cancella l'ultimo carattere o esce dalla tastiera.

::: tip Unleashed
L'inserimento di testo ha un **cursore**, quindi puoi modificare il testo anche nel mezzo. Nell'inserimento
esadecimale dei **byte** (per esempio quando aggiungi una chiave manualmente) premi <kbd>↑</kbd> più volte finché non
compare il **mini-editor dei nibble**: permette di cambiare mezzo byte alla volta.
:::
