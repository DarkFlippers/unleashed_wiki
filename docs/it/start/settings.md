---
title: Impostazioni
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Impostazioni

**Main Menu → Settings** contiene queste voci, nell'ordine in cui compaiono sul dispositivo:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

In elenchi come questi ti muovi con <kbd>↑</kbd>/<kbd>↓</kbd>, cambi un valore con <kbd>←</kbd>/<kbd>→</kbd> e apri
con <kbd>OK</kbd> una voce che ha una schermata propria.

![Menu Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Fissare un'impostazione nei Favorites
Tieni premuto <kbd>OK</kbd> su una voce dell'elenco Settings per fissarla nella scheda **Favorites** dell'Archive (o
per rimuoverla). Così avrai accesso rapido dal desktop con <kbd>↓</kbd>.
:::

::: info
La maggior parte delle app di impostazioni (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input,
LCD and Notifications, Passport) sono file `.fap` installati in `/ext/apps/assets/` dall'aggiornamento del firmware.
**Power**, **Storage** e **System** sono integrati nel firmware e funzionano anche senza scheda SD.
:::

## About

Schermate informative. Ci si muove tra loro con **Next** (<kbd>→</kbd>) e **Prev.** (<kbd>←</kbd>):

1. avviso **Unleashed Firmware**: solo per scopi sperimentali, non per usi illeciti;
2. licenza: il firmware è gratuito e open source, e *"If you paid any money for it - you got scammed."* ("se hai
   pagato per averlo, ti hanno truffato");
3. *"Community apps included in all builds except `c` build"* e un link a github.com/DarkFlippers;
4. prodotto, modello, FCC ID / IC;
5. link alla conformità e indirizzo del produttore;
6. **HW Version Info**: versione hardware, regione, nome del Flipper, numero di serie;
7. **FW Version Info**: versione e data di build, hash git, versione delle API, radio stack, target e branch.

## Bluetooth

| Voce | Valori / azione |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Mostra `Broken` se il radio stack è danneggiato ([Ripristino](/it/start/recovery)) |
| **Unpair All Devices** | Confermi con **Unpair**. Rimuove tutti gli accoppiamenti, comprese le chiavi di accoppiamento di Bad USB via Bluetooth (BadKB), Bluetooth Remote e Authenticator |

Usa **Unpair All Devices** se l'app mobile non si connette più dopo un'installazione o un cambio di nome. Vedi le
[FAQ](/it/start/faq).

## Clock & Alarm

Una sola schermata con tre righe: **Time** (hh:mm:ss), **Date** (gg.mm.aaaa) e **Alarm** (hh:mm, `On`/`Off`).

1. Seleziona una riga con <kbd>↑</kbd>/<kbd>↓</kbd> e un campo con <kbd>←</kbd>/<kbd>→</kbd>.
2. Premi <kbd>OK</kbd> per modificare e cambia il valore con <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Premi <kbd>OK</kbd> o <kbd>BACK</kbd> per terminare la modifica.

Quando la sveglia suona, <kbd>BACK</kbd> la **rimanda** di 9 minuti, mentre qualsiasi altro pulsante la ferma. Una
sveglia che nessuno ferma si spegne da sé dopo 10 minuti. L'app **Clock** nel menu principale mostra un orologio
grande e offre i controlli della luminosità, la sveglia e un timer.

## Desktop

| Voce | Valori | Descrizione |
|---|---|---|
| **PIN Setup** | → sottomenu | **Set PIN** / **Change PIN** / **Remove PIN**. Un PIN è una sequenza di 4–10 pressioni delle frecce |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Blocco dopo inattività |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Nessun blocco automatico mentre il dispositivo è collegato via USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Stile dell'icona della batteria |
| **Show Clock** | `OFF` / `ON` | Orologio sul desktop |
| **Menu Style** | `Default` + gli stili installati | Aspetto del menu principale. Gli stili sono plugin `menu_style_*` in `/ext/apps_data/loader/plugins/`. Mostra `Missing` se il file dello stile selezionato è stato eliminato |
| **Change Flipper Name** | testo | [Nome personalizzato del Flipper](/it/start/custom-name) |
| **Happy Mode** | Enable / Disable | Il delfino non si arrabbia mai ([Il delfino](/it/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | app | App ad accesso rapido dal desktop |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | app | App per la [Dummy Mode](/it/start/desktop#dummy-mode) |

Per ogni slot Favorite/Dummy puoi scegliere **Apps Menu (Default)** o **Passport (Default)**, **None (disable)**,
**Lock Flipper**, qualsiasi app del menu principale, oppure **[Select App]** per scegliere un `.fap` qualsiasi da
`/ext/apps/`.

::: warning PIN
La schermata di configurazione avverte: *"Forgotten PIN can only be reset with entire device."* ("un PIN dimenticato
può essere azzerato solo insieme a tutto il dispositivo"). L'azzeramento del PIN cancella anche le tue impostazioni (i
file sulla scheda SD vengono conservati): vedi [Ripristino](/it/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock e i 9 slot della Dummy Mode sono aggiunte di Unleashed.
:::

## Expansion Modules

| Voce | Valori | Descrizione |
|---|---|---|
| **Listen UART** | `USART` (pin 13, 14), `LPUART` (pin 15, 16), `None` | Quale UART resta in ascolto dei moduli che usano il protocollo di espansione (per esempio il [Video Game Module](/it/gpio/video-game-module)) |

Impostalo su `None` se non usi moduli di questo tipo: risparmia energia e permette al Flipper di andare in sleep.

## Input

| Voce | Valori | Descrizione |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Feedback vibrotattile sugli eventi dei pulsanti. I numeri più alti danno un impulso più lungo |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Quando scatta il feedback |

## LCD and Notifications

| Voce | Valori | Descrizione |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Contrasto del display |
| **LCD Backlight** | `0%` … `100%` (passo 5 %) | Luminosità della retroilluminazione |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Timeout della retroilluminazione |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Riduce la retroilluminazione di questa quantità nella fascia notturna |
| **. Start** | `17:00` … `23:30` | Inizio della fascia notturna (bloccato quando Night Shift è `OFF`) |
| **. End** | `05:00` … `11:30` | Fine della fascia notturna |
| **LED Brightness** | `0%` … `100%` | Luminosità del LED di stato |
| **Volume** | `0%` … `100%` | Volume dell'altoparlante (`Stealth` quando è silenziato dal Lock Menu) |
| **Vibro** | `OFF` / `ON` | Vibrazione (`Stealth` quando è silenziata) |
| **LCD Inversion** | `OFF` / `ON` | Inverte i colori del display |
| **RGB Mod Settings** | → sottomenu | Solo per i Flipper con la **mod hardware** della retroilluminazione RGB |

**RGB Mod Settings** (<kbd>OK</kbd> sulla voce): **RGB backlight installed** (`OFF`/`ON`). Le altre voci restano
bloccate (`RGB MOD OFF!`) finché questa non è `ON`: **LED 1 Color**, **LED 2 Color**, **LED 3 Color**, **Effects**
(`OFF`, `Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`), **. Saturation**,
**. Wave wide** (`1`–`3`).

::: danger Mod RGB
Attiva **RGB backlight installed** **soltanto** se il tuo Flipper ha la
[mod hardware della retroilluminazione RGB](https://github.com/quen0n/flipperzero-firmware-rgb#readme). Su un Flipper
stock la retroilluminazione smette di funzionare. Se è successo, torna qui e imposta `OFF` (vedi le
[FAQ](/it/start/faq#backlight-does-not-work)).
:::

## Passport

Il profilo del delfino: nome, umore e livello. Si apre anche con <kbd>→</kbd> dal desktop. Vedi
[Il delfino](/it/start/dolphin).

## Power

| Voce | Valori | Descrizione |
|---|---|---|
| **Battery Info** | — | Carica, tensione, corrente, temperatura, salute |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Riavvio in modalità DFU (`Reboot to DFU Mode?`) o riavvio normale |
| **Power OFF** | — | Spegne il dispositivo |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Spegnimento dopo inattività |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Interrompe la ricarica a questo livello |

Altro: [Alimentazione e batteria](/it/start/power).

## Storage

| Voce | Descrizione |
|---|---|
| **About Internal Storage** | Informazioni sulla memoria interna (`Virtual (/.int on SD)`) e flash libera |
| **About SD Card** | Etichetta, tipo, dimensione, spazio libero, produttore e numero di serie della scheda |
| **Unmount SD Card** / **Mount SD Card** | Rimozione sicura / nuovo montaggio |
| **Format SD Card** | Cancella e formatta la scheda |
| **Benchmark SD Card** | Test di velocità in SPI |
| **Factory Reset** | Premi **Erase** 5 volte. Cancella la memoria interna e riavvia |

Altro: [Scheda microSD](/it/start/sd-card), [Ripristino](/it/start/recovery#factory-reset).

## System

| Voce | Valori | Descrizione |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Modalità per mancini: ruota lo schermo e rimappa i pulsanti |
| **Units** | `Metric` / `Imperial` | Unità di misura (per esempio °C/°F in Battery Info) |
| **Time Format** | `24h` / `12h` | Formato dell'orologio |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Formato della data |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Quanto viene registrato nei log. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART usata per i log (USART = pin 13/14, LPUART = pin 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Velocità della UART dei log |
| **Debug** | `OFF` / `ON` | Modalità debug: funzioni di debug aggiuntive nelle app, scheda **Internal** nell'Archive, accesso SWD |
| **Heap Trace** | `None`, `Main` | Tracciamento delle allocazioni di memoria (per sviluppatori) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` consuma di più (~9 mA contro ~1,5 mA) ma può risultare più stabile |
| **File Naming** | `Default` / `Detailed` | `Detailed` inserisce tipo, data e ora nei nomi dei nuovi file |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

**Debug** ha una scorciatoia: tieni premuto <kbd>↓</kbd> sul desktop, poi tieni premuto <kbd>OK</kbd> sulla
schermata informativa ([Desktop → Schermata informativa del dispositivo](/it/start/desktop#info-screen)).

::: warning Flipper lento?
Per l'uso normale mantieni **Log Level** = `None` (o `Default`), **Debug** = `OFF` e **Heap Trace** = `None`. Le
impostazioni di debug rallentano il dispositivo e gli impediscono di andare in sleep.
:::

## Argomenti correlati

- [Desktop](/it/start/desktop): cosa fanno in pratica le impostazioni del desktop
- [Nome personalizzato del Flipper](/it/start/custom-name)
- [Impostazioni Sub-GHz](/it/subghz/settings): le impostazioni radio all'interno dell'app Sub-GHz
