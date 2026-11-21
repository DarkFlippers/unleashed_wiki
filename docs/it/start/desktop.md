---
title: Desktop
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Desktop

Il desktop è la schermata principale. Qui vive il tuo [delfino](/it/start/dolphin) e in alto corre una barra di stato.
Dal desktop, con una singola pressione dei pulsanti, si aprono il menu principale, l'Archive, il Lock Menu e le tue
app preferite.

## Barra di stato

La riga superiore mostra delle piccole icone:

| Icona | Significato |
|---|---|
| Batteria | Livello di carica. Mostra un fulmine durante la ricarica. Lo stile è definito da `Battery View` |
| Scheda SD | microSD montata. Un'icona barrata significa che il montaggio è fallito: vedi [Scheda microSD](/it/start/sd-card) |
| Bluetooth | Il BLE è attivo. Un'icona diversa indica che un dispositivo è connesso |
| Lucchetto | Il Flipper è bloccato |
| Altoparlante muto | Modalità stealth: suono e vibrazione disattivati (vedi [Lock Menu](#lock-menu)) |
| PC | Collegato a qFlipper / Flipper Lab via USB |
| Gamepad | La Dummy Mode è attiva |
| Modulo | È collegato un modulo di espansione |
| Beacon | Modalità beacon BLE (per esempio FindMy Flipper) |
| App in background | Un'app è in esecuzione in background |

::: tip Unleashed
- **Settings → Desktop → Battery View** seleziona lo stile della batteria: `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`,
  `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` mostra l'ora sul desktop. Il formato (24h/12h) dipende da
  **Settings → System → Time Format**.
:::

## Pulsanti del desktop

| Pulsante | Pressione breve | Pressione lunga |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Blocco** (con PIN se ne è impostato uno) |
| <kbd>↓</kbd> | **Archive** | Informazioni sul dispositivo / schermata di debug |
| <kbd>←</kbd> | Favorite App - Left Short (per impostazione predefinita il menu **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | **Passport** per impostazione predefinita (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Schermata di **spegnimento** |

### Schermata informativa del dispositivo {#info-screen}

Una pressione lunga di <kbd>↓</kbd> apre una schermata informativa: versione e data di build del firmware, versione
hardware, uptime, nome del Flipper e se Debug è `ON`/`OFF`.

![Schermata informativa: versione del firmware, versione hardware, uptime e stato di Debug](/screens/desktop/debug.png)

Su quella schermata una **pressione lunga di <kbd>OK</kbd> attiva o disattiva Debug**: è lo stesso interruttore di
`Settings → System → Debug` ([Impostazioni](/it/start/settings)), senza passare dai menu. Una pressione breve di
<kbd>BACK</kbd> riporta al desktop.

Con Debug `ON` compaiono voci altrimenti nascoste: la scheda **Internal** nell'[Archive](#archive) e
`Signal Settings` nel menu dei segnali salvati di Sub-GHz ([Signal Settings](/it/subghz/signal-settings)).
Disattivalo quando hai finito: le impostazioni di debug rallentano il Flipper e gli impediscono di dormire.

## Main Menu

Premi <kbd>OK</kbd>. Il menu principale si apre su **Apps** (tutte le app `.fap` dalla scheda SD, raggruppate per
categoria), seguito da **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**, **Bad USB**,
**U2F**, **Clock** e infine **Settings**. L'elenco è circolare, quindi premendo <kbd>↑</kbd> su **Apps** si salta
direttamente a **Settings**.

![Menu principale con Apps selezionato, Settings sopra e Sub-GHz sotto](/screens/mainmenu/main.png)

::: tip Stili del menu
**Settings → Desktop → Menu Style** cambia l'aspetto del menu principale. Gli stili sono plugin in
`/ext/apps_data/loader/plugins/` (file che iniziano con `menu_style_`). `Default` è l'elenco integrato.
:::

## Lock Menu {#lock-menu}

Premi <kbd>↑</kbd> sul desktop. Spostati con <kbd>↑</kbd>/<kbd>↓</kbd> e premi <kbd>OK</kbd>:

| Voce | Cosa fa |
|---|---|
| **Turn Bluetooth On / Off** | Attiva o disattiva il BLE senza passare dalle Settings |
| **Mute / Unmute** | Modalità stealth: nessun suono e nessuna vibrazione. Le impostazioni **Volume** e **Vibro** mostrano `Stealth` mentre è attiva |
| **Dummy Mode / Default Mode** | Entra o esce dalla [Dummy Mode](#dummy-mode) |

Premi <kbd>←</kbd> o <kbd>→</kbd> nel Lock Menu per aprire la seconda pagina, **Quick Settings**:

| Voce | Comando |
|---|---|
| Brightness | <kbd>OK</kbd> per modificare, poi <kbd>←</kbd>/<kbd>→</kbd> (o <kbd>↑</kbd>/<kbd>↓</kbd>), a passi del 5 % |
| Volume | Uguale. Viene riprodotto un breve beep per farti sentire il nuovo livello |
| Vibro | <kbd>OK</kbd> lo attiva o disattiva sul posto |

<kbd>BACK</kbd> esce dalla voce in modifica, e un secondo <kbd>BACK</kbd> esce dalla pagina. Le modifiche finiscono
nelle stesse impostazioni di **LCD and Notifications**.

::: tip Unleashed
In Unleashed il **blocco** si attiva con una pressione lunga di <kbd>↑</kbd> sul desktop: con il PIN se ne è impostato
uno, altrimenti come blocco normale.
:::

## Blocco e PIN

- **Blocco:** tieni premuto <kbd>↑</kbd> sul desktop. Senza PIN vengono bloccati i pulsanti. **Per sbloccare premi
  <kbd>BACK</kbd> tre volte** rapidamente.
- **Con un PIN:** impostalo in **Settings → Desktop → PIN Setup → Set PIN**. Un PIN è una sequenza di 4 a 10
  pressioni delle frecce. Il Flipper bloccato chiederà poi il PIN. Dopo tentativi errati mostra `Wrong PIN!` e un
  tempo di attesa prima del tentativo successivo.
- **Auto Lock:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) blocca il dispositivo dopo quel
  tempo di inattività. **Auto Lock disarm by active USB session** = `ON` impedisce il blocco automatico mentre il
  Flipper è collegato via USB.

::: warning PIN dimenticato
Un PIN dimenticato può essere azzerato solo insieme a tutte le impostazioni utente: vedi
[Ripristino → Azzerare un PIN dimenticato](/it/start/recovery#reset-pin). I file sulla scheda microSD vengono
conservati.
:::

## Dummy Mode {#dummy-mode}

La Dummy Mode trasforma il Flipper in un giocattolo. La maggior parte delle funzioni è nascosta e i pulsanti avviano
le app che scegli, per esempio dei giochi. Si attiva con **Lock Menu → Dummy Mode** e si disattiva con
**Lock Menu → Default Mode**.

In Dummy Mode ogni pulsante può avviare la propria app. Si impostano in **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`,
`- Ok Long`.

Un pulsante non assegnato apre il Passport. Una pressione breve di <kbd>↑</kbd> apre comunque il Lock Menu. Se
`DummyMode - Up Long` è impostato su `None`, una pressione lunga di <kbd>↑</kbd> blocca il dispositivo.

::: tip Unleashed
Il firmware stock ha 4 scorciatoie per la Dummy Mode. Unleashed ne ha 9 (pressione breve e lunga su ogni pulsante),
così puoi tenere diversi giochi a una pressione di distanza.
:::

## App preferite (accesso rapido)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Per ogni slot puoi scegliere:
- **Apps Menu (Default)** o **Passport (Default)**: il valore predefinito integrato per quello slot;
- **None (disable)**: il pulsante non fa nulla;
- **Lock Flipper**;
- qualsiasi app del menu principale;
- **[Select App]**: scegli un file `.fap` qualsiasi da `/ext/apps/`.

## Archive

Premi <kbd>↓</kbd>. L'Archive mostra i tuoi file salvati suddivisi in schede. Cambia scheda con
<kbd>←</kbd>/<kbd>→</kbd>:

| Scheda | Cartella / contenuto |
|---|---|
| Favorites | I file che hai fissato |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: mappature di Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` e dump T5577) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: rubrica del SIM800 (`.phone`) |
| U2F | Token U2F |
| Apps | `/ext/apps` (`.fap` e `.js`) |
| Internal | Memoria interna (solo con **Debug** = `ON`) |
| Browser | L'intera scheda microSD |

Premi <kbd>OK</kbd> su un file per aprirne il menu contestuale: esegui/emula, **Pin**/**Unpin** (aggiungi a
Favorites), **Rename**, **Delete**, e nel Browser anche **Cut**, **Copy**, **Paste** e **NewDir**. Nella scheda
Favorites tieni premuto <kbd>OK</kbd> per aprire il menu.

::: tip Fissare le impostazioni nei Favorites
In **Main Menu → Settings** tieni premuto <kbd>OK</kbd> su una voce delle impostazioni per fissarla nei Favorites.
Potrai poi aprirla dall'Archive senza passare dai menu.
:::

## Passport

Premi <kbd>→</kbd> sul desktop, oppure apri **Settings → Passport**. Mostra il nome del delfino (il nome del Flipper),
l'umore e il livello: vedi [Il delfino](/it/start/dolphin).
