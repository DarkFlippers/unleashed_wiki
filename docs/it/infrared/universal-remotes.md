---
title: Telecomandi universali
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Telecomandi universali

Un telecomando universale ti permette di comandare un apparecchio **senza aver prima appreso il suo telecomando**.
Quando premi, per esempio, *Power*, il Flipper invia il codice Power di ogni modello presente nella sua libreria, uno
dopo l'altro. Quando azzecca il codice che il tuo apparecchio capisce, l'apparecchio reagisce. È per questo che un
pulsante universale richiede qualche secondo invece di essere istantaneo.

Apri `Main Menu → Infrared → Universal Remotes`.

![L'elenco delle categorie di Universal Remotes: TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
Il firmware ufficiale include le librerie TV, Audio, Projector e AC. Unleashed aggiunge **LEDs** e **Fans** e mantiene
tutte le librerie molto più ampie e ricontrollate regolarmente dal team (asset IR a cura di @amec0e). La libreria TV è
ricompilata in modo che **tutti** i suoi pulsanti funzionino, non solo Power.
:::

## Categorie

Le voci di menu e i nomi dei pulsanti qui sotto sono presi dal firmware; il numero di segnali si riferisce alle
librerie incluse nella build `dev` attuale (`/ext/infrared/assets/`, ultimo aggiornamento ottobre 2024 / febbraio 2024
per AC).

| Voce di menu | File di libreria | Pulsanti | Segnali nella libreria |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (295 dei quali Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

"Audio" copre sound bar, amplificatori AV, impianti stereo e simili. "LEDs" indica strisce e lampadine LED comandate
a infrarossi.

### Condizionatori

I telecomandi dei condizionatori mantengono loro stessi lo stato dell'apparecchio e inviano l'intero stato a ogni
pressione, quindi la libreria AC contiene "scene" complete anziché singoli pulsanti:

| Pulsante | Significato |
|---|---|
| **Off** | Spegne il condizionatore. È l'*unico* pulsante che lo spegne. |
| **Dh** | Modalità deumidificazione (dry). |
| **Cool_hi** | Raffreddamento alla temperatura più bassa consentita dal telecomando (raffreddamento massimo). |
| **Cool_lo** | Raffreddamento a 23 °C. |
| **Heat_hi** | Riscaldamento alla temperatura più alta consentita dal telecomando (riscaldamento massimo). |
| **Heat_lo** | Riscaldamento a 23 °C. |

Per **accendere** un condizionatore, premi qualsiasi pulsante diverso da Off. I pulsanti della temperatura mostrano
°C o °F a seconda di `Settings → System → Units`.

## Come si usa

1. Vai in `Main Menu → Infrared → Universal Remotes` e seleziona una categoria.
2. Punta il bordo superiore del Flipper verso l'apparecchio. Resta vicino e in linea di vista.
3. Seleziona un pulsante con le frecce e premi <kbd>OK</kbd>.

   ![Il telecomando universale per TV, mostrato sullo schermo verticale: Power e Mute in alto, Channel e Volume su/giù sotto](/screens/infrared/universal_tv.png)

4. La finestra **"Sending..."** mostra l'avanzamento come `current/total` e una barra di avanzamento. Continua a
   puntare verso l'apparecchio.
5. Quando l'apparecchio reagisce, premi <kbd>OK</kbd> per **mettere in pausa**, oppure lascia che la libreria arrivi
   alla fine.

![Telecomando universale in azione](/img/remote/bdb3541a3f2e88fe.png)

### Comandi durante l'invio

| Stato | Pulsante | Azione |
|---|---|---|
| Invio in corso | <kbd>OK</kbd> | **pausa** |
| Invio in corso | <kbd>Back</kbd> | **stop** |
| In pausa | <kbd>Back</kbd> | **riprende** l'invio dal punto in cui si era fermato |
| In pausa | <kbd>OK</kbd> | **send 1**: invia solo il segnale attualmente selezionato |
| In pausa | <kbd>←</kbd> / <kbd>→</kbd> (frecce) | **seleziona** il segnale precedente / successivo della libreria |
| In pausa | <kbd>↓</kbd> | **salva** il segnale selezionato |

## Trovare il codice esatto e salvarlo

Il vero punto di forza della schermata di pausa: puoi trovare l'unico codice che funziona e conservarlo, così la volta
successiva il pulsante è istantaneo.

1. Avvia un pulsante universale. Appena l'apparecchio reagisce, premi <kbd>OK</kbd> (pausa). Il contatore ora punta
   all'ultimo segnale inviato.
2. Dato che non sei mai perfettamente rapido, torna indietro con la freccia sinistra e usa **send 1** (<kbd>OK</kbd>)
   su ciascun segnale finché trovi quello che fa reagire l'apparecchio. Usa la freccia destra per andare di nuovo
   avanti.
3. Premi <kbd>↓</kbd> **save**. L'intestazione del menu mostra il nome del pulsante (per esempio `Power`), che è anche
   il nome con cui il segnale viene salvato:
   - **Save as New Remote**: inserisci un nome per il telecomando in **"Name the remote"**; viene creato un nuovo file
     `.ir` in `/ext/infrared/`;
   - **Add to Existing Remote**: scegli un file `.ir` esistente; il segnale viene aggiunto a quello.
4. **"Saved"** lo conferma. Il telecomando si trova ora in `Infrared → Saved Remotes`.

Ripeti per Vol_up, Mute e così via, aggiungendo ciascuno allo stesso telecomando: ottieni un telecomando personale e
istantaneo costruito a partire dalla libreria universale.

![Un telecomando salvato sullo schermo verticale: l'elenco dei pulsanti Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## Dalla riga di comando

Le stesse librerie possono essere riprodotte dalla [CLI](/it/dev/cli):

```text
ir universal list tv        # list the signal names in tv.ir
ir universal tv Power       # send every "Power" signal from tv.ir
```

`ir universal` senza argomenti elenca le librerie disponibili (tutti i file `.ir` in `/ext/infrared/assets/`).
Premi <kbd>Ctrl</kbd>+<kbd>C</kbd> nel terminale per fermarti.

## Risoluzione dei problemi

| Problema | Cosa provare |
|---|---|
| *"Function requires SD card with fresh databases."* | I file di libreria mancano. Inserisci la scheda microSD e reinstalla / aggiorna il firmware con la scheda inserita, vedi [Aggiornamento](/it/start/updating). |
| Nessuna reazione dopo tutta la libreria | Il tuo modello non è nella libreria. [Apprendi](/it/infrared/read) il telecomando originale, prova la [Remotes Library dell'app mobile](/it/infrared/mobile) e considera di [contribuire con le acquisizioni](/it/infrared/captures). |
| L'apparecchio reagisce, ma troppo tardi per mettere in pausa | Usa la freccia sinistra + **send 1** per tornare al segnale giusto, vedi sopra. |
| Funziona solo a distanza molto breve | I LED integrati sono deboli per le stanze grandi. Usa un [modulo IR esterno](/it/infrared/external-ir). |
| Il condizionatore non si accende con Off | È previsto: Off serve solo a spegnerlo. Usa Cool/Heat/Dh per accenderlo. |

## Pagine correlate

- [Contribuire con le acquisizioni](/it/infrared/captures): aggiungi il tuo apparecchio alle librerie
- [Formato dei file IR](/it/infrared/file-format): formato dei file di libreria
- [Apprendere e inviare segnali](/it/infrared/read)
