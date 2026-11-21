---
title: Primo avvio
order: 10
original: [https://docs.flipper.net/zero/basics/first-start, https://docs.flipper.net/zero/basics/sd-card, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md]
sources: [flipper-docs, unleashed-docs]
---
# Primo avvio

Cosa fare nei primi dieci minuti con un Flipper Zero nuovo, prima di installare Unleashed.

## 1. Accensione

Tieni premuto <kbd>BACK</kbd> per circa 3 secondi. Compare il desktop, con il tuo delfino e la barra di stato:

![Il desktop del Flipper: l'animazione del delfino a riposo e la barra di stato con le icone della scheda SD e della batteria](/screens/desktop/idle.png)

::: details Il Flipper non si accende
- La batteria potrebbe essere completamente scarica. Collega il cavo USB-C: dopo poco il dispositivo si accende da sé.
- Se lo schermo resta spento, tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per 5 secondi (riavvio).
- Ancora niente: vedi [Combinazioni di tasti](/it/start/key-combos) e [Ripristino](/it/start/recovery).
:::

## 2. Inserire una scheda microSD

La scheda microSD è **indispensabile**. Contiene chiavi, card, telecomandi, database, le app che arrivano con il
firmware e anche la memoria "interna" (vedi [Scheda microSD](/it/start/sd-card)). La scheda non è inclusa con il
dispositivo.

1. Individua lo slot sul lato inferiore del Flipper.
2. Tieni la scheda **con i contatti rivolti verso l'alto** e spingila dentro fino allo scatto.
3. Quando la scheda è montata, la barra di stato mostra l'icona della SD.

Una scheda di marca da **16–32 GB** è più che sufficiente. Funzionano anche schede fino a 256 GB, ma quelle grandi
richiedono più tempo per il montaggio. Le schede no-name economiche possono rendere il dispositivo lento o instabile.

## 3. Aggiornare il firmware ufficiale (solo alla prima installazione)

La guida all'installazione di Unleashed chiede di **aggiornare prima all'ultima release ufficiale** se stai
installando Unleashed per la prima volta. In questo modo bootloader, radio stack e dati interni vengono portati
all'ultima versione.

- **qFlipper** (Windows/macOS/Linux): collega il dispositivo via USB, apri la scheda **Advanced controls**, imposta
  **Update Channel** su **Release** e clicca **Update**.
- **Flipper Mobile App** (iOS/Android): attiva il Bluetooth sul Flipper (**Main Menu → Settings → Bluetooth**),
  accoppia il dispositivo con l'app, poi tocca **Update**. Ci vogliono circa 10 minuti.

Altre informazioni su qFlipper e sull'app mobile: [qFlipper](/it/mobile/qflipper), [App mobile](/it/mobile/mobile-app).

## 4. Installare Unleashed

Usa l'**[Unleashed Web Installer](https://web.unleashedflip.com)**: è il metodo più semplice. Tutti i metodi sono
descritti in [Installare Unleashed](/it/start/install).

## 5. Configurazione di base

Dopo l'installazione apri **Main Menu → Settings** e controlla:

- **Clock & Alarm**: imposta data e ora;
- **System → Hand Orient**: `Lefty` se tieni il dispositivo nella mano sinistra;
- **Desktop**: PIN, orologio sul desktop (`Show Clock`), stile della batteria (`Battery View`), app ad accesso rapido;
- **Desktop → Change Flipper Name**: dai al tuo Flipper un nome tutto suo
  ([Nome personalizzato del Flipper](/it/start/custom-name)).

Ogni voce è descritta in [Impostazioni](/it/start/settings).

## Prossimi passi

- Impara i pulsanti e le scorciatoie: [Comandi](/it/start/controls)
- Esplora il desktop: [Desktop](/it/start/desktop)
- Scopri cosa aggiunge Unleashed: [Cosa aggiunge Unleashed](/it/start/unleashed-features)
