---
title: Infrarossi
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Infrarossi

Il Flipper Zero ha un modulo a infrarossi (IR) integrato. Può **apprendere** i pulsanti di quasi qualsiasi telecomando IR, **salvarli** come telecomando virtuale sulla scheda microSD, **rinviarli** e funzionare come **telecomando universale** scorrendo una libreria di codici noti per TV, impianti audio, proiettori, strisce LED, ventilatori e condizionatori.

![Infrarossi sul Flipper Zero](/img/remote/133011d2bd3dc44c.png)

## Hardware

- Una finestra in plastica trasparente agli infrarossi sul bordo superiore del Flipper.
- **Tre LED IR** per la trasmissione.
- Un **ricevitore IR** che demodula la portante (è tarato sulla portante comune da 38 kHz). L'apprendimento usa sempre
  questo ricevitore integrato.
- Facoltativamente un **trasmettitore IR esterno** sul pin GPIO 2 (A7) per una portata maggiore, vedi
  [Moduli IR esterni](/it/infrared/external-ir).

## Il menu Infrared

Apri `Main Menu → Infrared`. Le voci di menu arrivano direttamente dal firmware:

![Il menu Infrared con Universal Remotes, Learn New Remote, Saved Remotes e GPIO Settings](/screens/infrared/menu.png)

| Voce | Cosa fa |
|---|---|
| **Universal Remotes** | Invia un'intera libreria di codici per un singolo pulsante (Power, Vol+…) finché il tuo apparecchio reagisce. Vedi [Telecomandi universali](/it/infrared/universal-remotes). |
| **Learn New Remote** | Acquisisce i pulsanti da un telecomando fisico e li salva come nuovo telecomando. Vedi [Apprendere e inviare segnali](/it/infrared/read). |
| **Saved Remotes** | Apre il file browser in `/ext/infrared/` per inviare, modificare, rinominare o eliminare i tuoi telecomandi. |
| **GPIO Settings** | Sceglie il trasmettitore (integrato, pin 2 (A7) o rilevamento automatico) e i 5 V sul GPIO. Vedi [Moduli IR esterni](/it/infrared/external-ir). |
| **Learn New Remote RAW** | Solo con `Settings → System → Debug` attivo. Come Learn, ma con il decoder disattivato: ogni segnale viene salvato come RAW. |
| **Debug RX** | Solo con Debug attivo. Un "INFRARED monitor" dal vivo di ciò che riceve il ricevitore. |

::: tip Unleashed
L'app Infrared, i suoi decoder di protocollo e il meccanismo dei telecomandi universali sono del firmware
ufficiale. Unleashed aggiunge:
- il protocollo IR **RCA** (vedi [Protocolli](/it/infrared/protocols));
- librerie aggiuntive per i telecomandi universali (**LEDs**, **Fans**) e librerie molto più ampie e ricontrollate
  regolarmente per TV, audio, proiettori e condizionatori, mantenute dal team Unleashed (asset IR a cura di @amec0e).
  La libreria TV è ricompilata in modo che **tutti** i suoi pulsanti funzionino;
- il supporto ai moduli IR esterni con rilevamento automatico (ripreso dal firmware ufficiale).
:::

## Dove stanno i file

| Percorso | Contenuto |
|---|---|
| `/ext/infrared/*.ir` | I tuoi telecomandi salvati (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Librerie dei telecomandi universali: `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Vengono installate e aggiornate insieme al firmware. |
| `/ext/infrared/.infrared.settings` | Impostazioni GPIO (pin di uscita, 5 V). |

Il formato dei file `.ir` è descritto in [Formato dei file IR](/it/infrared/file-format).

## Riga di comando

Il comando `ir` è disponibile nella [CLI](/it/dev/cli) (per esempio tramite qFlipper o un terminale seriale):

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Pagine di questa sezione

| Pagina | Cosa impari |
|---|---|
| [Apprendere e inviare segnali](/it/infrared/read) | Apprendere un telecomando, salvarlo, inviare pulsanti, modificare / spostare / rinominare / eliminare pulsanti |
| [Telecomandi universali](/it/infrared/universal-remotes) | Tutte le categorie di telecomandi universali, i pulsanti, i comandi, come salvare un codice funzionante |
| [Telecomandi nell'app mobile](/it/infrared/mobile) | La Remotes Library nella Flipper Mobile App |
| [Contribuire con le acquisizioni](/it/infrared/captures) | Come registrare segnali puliti per le librerie universali |
| [Moduli IR esterni](/it/infrared/external-ir) | Uscita GPIO, rilevamento automatico, alimentazione a 5 V |
| [Protocolli](/it/infrared/protocols) | Tutti i protocolli che il decoder conosce, RCA compreso |
| [Formato dei file IR](/it/infrared/file-format) | I formati dei file `.ir` di telecomando, libreria e test |
