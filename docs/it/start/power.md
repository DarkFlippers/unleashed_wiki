---
title: Alimentazione e batteria
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Alimentazione e batteria

Il Flipper Zero ha una batteria Li-Po integrata da **2100 mAh**. Può durare fino a circa un mese in standby e si
ricarica via USB-C in circa due ore.

## Accensione e spegnimento

- **Accensione:** tieni premuto <kbd>BACK</kbd> per circa 3 s. Un Flipper completamente scarico si accende da sé
  appena colleghi l'USB.
- **Spegnimento:** tieni premuto <kbd>BACK</kbd> sul desktop. Compare la schermata **Turn Off Device?**:
  <kbd>→</kbd> **Power Off** lo spegne, <kbd>←</kbd> **Battery** apre le informazioni sulla batteria. Puoi anche usare
  **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? con il delfino che piange, Battery sul pulsante di sinistra e Power Off su quello di destra](/screens/settings/power_off.png)

## Ricarica

Collega il cavo USB-C a un caricatore o a un computer. L'icona della batteria mostra un fulmine durante la ricarica.
L'ingresso di ricarica è 5 V / 1 A, quindi una carica completa richiede circa 2 ore.

::: warning Lunghi periodi di inutilizzo
Se non userai il Flipper per molto tempo, caricalo a circa il **50 %** prima di spegnerlo. Conservarlo completamente
scarico danneggia la batteria. Mantienilo tra 0 e 40 °C.
:::

## Settings → Power

| Voce | Cosa fa |
|---|---|
| **Battery Info** | Percentuale di carica, tensione, corrente, temperatura e salute della batteria |
| **Reboot** | **Firmware Upgrade** (riavvio in modalità DFU) o **Reboot Flipper** (riavvio normale). Confermi con <kbd>→</kbd> **Reboot** |
| **Power OFF** | Spegne il dispositivo |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min`: spegne dopo questo tempo di inattività |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%`: interrompe la ricarica a questo livello |

![Settings → Power: Battery Info, Reboot, Power OFF, Auto PowerOff OFF, Limit Charge OFF](/screens/settings/power.png)

::: tip Limit Charge
Limit Charge è utile se il Flipper resta collegato all'USB per la maggior parte della giornata, per esempio come
gadget da scrivania. Tenere la batteria sotto il 100 % ne allunga la vita.
:::

## Schermata Battery Info

La schermata mostra un messaggio diverso a seconda dello stato:

| Intestazione | Significato |
|---|---|
| `Yummy!` / `Charging at` | In carica. Mostra la tensione USB e la corrente di carica |
| `Om-nom-nom!` / `Consumption is` | Alimentato a batteria, con l'assorbimento attuale. `Oh no!` e `mA!` indicano un consumo elevato |
| `Charged!` | USB collegata, carica non in corso (batteria piena) |
| `Charged!` / `Limited to` | USB collegata e impostato un limite di tensione di carica diverso da quello predefinito (indicato in V) |
| `Napping...` | A batteria, assorbimento di corrente quasi nullo |

Mostra anche la percentuale della batteria, la tensione, la temperatura (°C o °F, secondo
**Settings → System → Units**) e la **salute** della batteria in percentuale.

![Battery Info: Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4.1 V, salute 100 %](/screens/settings/battery_info.png)

## Consumo energetico

| Modalità | Corrente tipica |
|---|---|
| Sleep (metodo di sleep Default) | ~1,5 mA |
| Sleep (metodo di sleep Legacy) | ~9 mA |
| Attivo, retroilluminazione accesa | fino a ~30 mA (fino a ~50 mA con una scheda SD scadente) |
| Radio attiva | fino a ~400 mA |
| Radio + modulo esterno | fino a ~2 A |

**Sleep Method** si trova in **Settings → System**. `Default` consuma meno. `Legacy` consuma di più, ma può aiutare se
noti crash durante lo sleep.

Lo sleep richiede **Debug** = `OFF` (**Settings → System**) e **Listen UART** = `None`
(**Settings → Expansion Modules**). In caso contrario il dispositivo non riesce ad andare in sleep e la batteria si
scarica più in fretta.

## Consigli per una maggiore autonomia

- Tieni il firmware aggiornato.
- Disattiva il Bluetooth quando non ti serve (Lock Menu → **Turn Bluetooth Off**).
- Abbassa **LCD Backlight** e **Backlight Time** in **LCD and Notifications**.
- Usa una scheda microSD di marca e di buona qualità.
- Imposta **Auto PowerOff**.
- Se la batteria si scarica rapidamente, controlla la corrente in **Battery Info**.

## Specifiche di alimentazione

| Parametro | Valore |
|---|---|
| Capacità della batteria | 2100 mAh |
| Tensione di esercizio della batteria | 3,3–4,2 V |
| Tempo di ricarica | ~2 ore |
| Tensione / corrente di ricarica | 5 V, 1 A |
| Connettore | USB Type-C |
| Corrente massima dall'USB, dispositivi collegati compresi | 3 A |

## Argomenti correlati

- Riavvio e combinazioni di reset: [Combinazioni di tasti](/it/start/key-combos)
- Il dispositivo non si accende: [Ripristino](/it/start/recovery)
