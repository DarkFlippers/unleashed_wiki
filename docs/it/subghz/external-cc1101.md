---
title: Modulo CC1101 esterno
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# Modulo CC1101 esterno

La radio Sub-GHz interna del Flipper è un chip CC1101 con una piccola antenna integrata. Puoi collegare una seconda scheda CC1101 al connettore GPIO e fare in modo che l'app Sub-GHz (e le app di sistema Sub-GHz) usino quella. Le schede esterne hanno di solito una vera antenna SMA e spesso un amplificatore di potenza, quindi arrivano molto più lontano, sia in ricezione sia in trasmissione.

**Quando usarlo:** il telecomando o il ricevitore sono lontani, l'antenna interna non riesce a captare un telecomando debole, oppure ti serve più portata in trasmissione. Per trovare la frequenza di un telecomando continua a usare la radio interna (vedi [Frequency Analyzer](/it/subghz/frequency-analyzer)).

::: tip Funziona su qualsiasi firmware
I moduli radio esterni funzionano su qualsiasi firmware, anche su quello di serie. La prima implementazione l'ha scritta @quen0n per Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)); quella in uso oggi l'ha scritta **Skorp** nel firmware ufficiale, ed è quella che usa Unleashed.
:::

## Collegamenti

Il modulo comunica tramite il bus SPI esterno del Flipper. Il collegamento standard è:

| Pin CC1101 | GPIO Flipper | Pin del connettore |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 o 18 |
| Controllo amplificatore / LED (moduli E07) | PC3 | 7 |

Per schede già pronte, schemi e foto vedi la guida di quen0n: [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (linkata dalla FAQ di Unleashed). La numerazione del connettore si trova nella pagina [Pinout GPIO](/it/gpio/pinout); le altre schede aggiuntive sono in [Moduli esterni](/it/gpio/external-modules).

::: warning
Alimenta il modulo solo a **3.3 V**. Il CC1101 non è un chip a 5 V.
:::

## Passare al modulo esterno

1. Collega il modulo con il Flipper spento, o almeno senza che l'app Sub-GHz sia in esecuzione.
2. Apri `Main Menu → Sub-GHz → Radio Settings`.
3. Sulla riga **Module** premi <kbd>→</kbd> per cambiare `Internal` in `External`.
4. Premi <kbd>←</kbd> (Back) e usa `Read`, `Read RAW`, `Saved` ecc. come al solito.

Cosa aspettarsi:

- La riga **Module** propone `External` solo quando un modulo viene effettivamente rilevato. Se non c'è nulla collegato, la riga ha un unico valore, `Internal`.
- Il firmware interroga il modulo quando lo selezioni. Se l'interrogazione non riesce, torna alla radio interna e la riga mostra di nuovo `Internal` — quindi ciò che vedi è ciò che è realmente in uso.
- Nella schermata di trasmissione di un segnale salvato, la riga in basso mostra `R: Int` oppure `R: Ext` — la radio che trasmetterà.
- Le app di sistema Sub-GHz ([Nice O-Code](/it/subghz/nice-o-code), [Seed Capturer](/it/subghz/seed-capturer), [Security+ PIN](/it/subghz/secplus-pin)) mostrano `Int` o `Ext` nella propria intestazione e usano automaticamente un modulo esterno quando ne è collegato uno.

## Le altre voci di Radio Settings

`Sub-GHz → Radio Settings` contiene:

| Voce | Valori | Cosa fa |
|---|---|---|
| Module | `Internal` / `External` | radio usata dall'app Sub-GHz |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | sovrascrive la potenza di trasmissione del preset; `Preset` mantiene la potenza definita dal preset di modulazione |
| Protocol Names | `OFF` / `ON` | vedi [Radio Settings](/it/subghz/settings) |
| Counter Incr. | `+1`… | vedi [Radio Settings](/it/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **solo in modalità debug** — pilota il pin di controllo dell'amplificatore / dei LED (PC3, pin 7 del connettore) dei moduli in stile E07 |
| Debug Pin | `OFF` / `17(1W)` | **solo in modalità debug** — replica il segnale sul pin 17 per lo sviluppo dei protocolli |

`Ext Amp & LEDs` è **ON per impostazione predefinita**. Con questa opzione attiva, il firmware attiva l'amplificatore del modulo su PC3 solo mentre il chip sta effettivamente trasmettendo. Disattivala solo se il tuo modulo usa il pin 7 per altro; la voce di menu compare quando la modalità debug è abilitata in `Settings → System`.

## Modulo da 1 W ad alta potenza (in fase di test)

All'inizio del 2025 @gromovyna ha condiviso i suoi test di un nuovo modulo Sub-GHz molto più potente realizzato da quen0n (membro del team Unleashed):

- All'epoca dei post era l'unico esemplare esistente, con potenza di trasmissione **fino a 1 W**.
- È costruito su un chip diverso dal CC1101 — nessuno aveva mai realizzato nulla su quel chip prima.
- Il supporto nel firmware **non era ancora completato**; veniva sviluppato per Unleashed insieme a Flipper Market, e gromovyna faceva da tester.

![Modulo ad alta potenza accanto a una scheda CC1101](/img/remote/29279ff04df77e30.jpg)

I suoi risultati empirici (senza misure di potenza):

- Il modulo è molto più potente di qualsiasi cosa avesse visto basata sul CC1101.
- In città, trasmettendo da un appartamento con un altro edificio di mezzo, ha inviato un segnale **Hollarm** a **600 m** in orizzontale.
- La stessa distanza è stata raggiunta sia con l'antenna in dotazione sia con un'antenna da walkie-talkie consigliata da MMX e quen0n — anche se con l'antenna da walkie-talkie l'insieme è "assolutamente non portatile".
- Un eventuale vantaggio in *ricezione* rispetto al CC1101 non era ancora chiaro.

![Il modulo con un'antenna da walkie-talkie](/img/remote/0998ad639bb38e82.jpg)

Questo descrive un dispositivo in fase di test; controlla le note di rilascio attuali di Unleashed per lo stato del suo supporto.

::: warning
Trasmetti solo su frequenze e a potenze legali dove ti trovi, e solo verso apparecchiature di tua proprietà.
:::

## Risoluzione dei problemi

- **Non si può selezionare `External`** — il modulo non viene rilevato: controlla 3.3 V, GND e le quattro linee SPI (CSN, SCK, MOSI, MISO). Un filo CSN o MISO sbagliato è l'errore più comune.
- **Torna da solo a `Internal`** — l'interrogazione è fallita quando il modulo è stato selezionato; ricollega bene il modulo e riprova.
- **Riceve ma la portata in trasmissione è scarsa** — sui moduli E07 l'amplificatore richiede il pin 7 (PC3) collegato e `Ext Amp & LEDs` su ON.
- **Il Frequency Analyzer mostra rilevamenti casuali** — il modulo esterno è molto più sensibile al rumore; usa la radio interna per l'analisi di frequenza.
- **Trasmissione bloccata** — la frequenza è fuori dall'intervallo del CC1101; vedi [Frequenze e portata](/it/subghz/frequencies).

## Pagine correlate

- [Radio Settings](/it/subghz/settings)
- [Frequenze e portata](/it/subghz/frequencies)
- [Pinout GPIO](/it/gpio/pinout) · [Moduli esterni](/it/gpio/external-modules)
