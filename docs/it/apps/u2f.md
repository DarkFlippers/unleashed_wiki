---
title: Chiave di sicurezza U2F
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# Chiave di sicurezza U2F

L'app **U2F** trasforma Flipper Zero in una chiave di sicurezza USB
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). Dopo aver inserito la password
su un sito, il sito richiede la chiave e tu confermi l'accesso premendo <kbd>OK</kbd> sul Flipper. Google, GitHub,
Facebook, X e molti altri siti supportano le chiavi U2F; [dongleauth.com](https://www.dongleauth.com/) ne tiene un
elenco.

::: warning Chiave solo software
L'U2F del Flipper è implementato in software. Per conti bancari e altri account di valore elevato usa una chiave di
sicurezza hardware certificata. Mantieni sempre un secondo fattore di riserva (codici di recupero o un'altra chiave).
:::

## Prima di iniziare

- Serve **una scheda microSD**. I dati U2F risiedono in `/ext/u2f/`. Senza di essa l'app mostra
  `No SD card or app data found. This app will not work without required files.`
- I file del certificato `/ext/u2f/assets/cert.der` e `/ext/u2f/assets/cert_key.u2f` vengono installati
  dall'aggiornamento del firmware. Se mancano, aggiorna di nuovo il firmware con la scheda inserita.
- **Chiudi qFlipper** (e Flipper Lab): il Flipper deve essere libero di commutare la propria porta USB in modalità
  U2F. Se una connessione è attiva, l'app mostra `Connection Is Active! Disconnect from PC or phone to use this
  function.`

## Registrare il Flipper su un sito

1. Collega il Flipper al computer con un cavo USB.
2. Apri `Main Menu → U2F`. Lo schermo mostra `Connect me to computer`, poi `Connected!` una volta che il computer ha
   riconosciuto la chiave.

   ![U2F: Connect me to computer, con il Flipper disegnato come una chiavetta USB](/screens/apps/u2f_not_connected.png)

3. Sul sito apri le impostazioni dell'autenticazione a due fattori e scegli di aggiungere una **chiave di sicurezza**
   (la terminologia varia da sito a sito).
4. Il Flipper mostra `Press OK to register`. Premi <kbd>OK</kbd>.
5. Il sito conferma che la chiave è stata aggiunta.

## Accedere

1. Collega il Flipper via USB e apri `Main Menu → U2F` (`Connected!`).
2. Inserisci nome utente e password sul sito.
3. Quando il sito richiede la chiave di sicurezza, il Flipper mostra `Press OK to authenticate`. Premi <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate, con il suggerimento del pulsante OK](/screens/apps/u2f.png)

4. Il Flipper mostra `Authentication successful!` e il sito ti fa accedere.

## Conserva al sicuro i tuoi file U2F

| File | Scopo |
|---|---|
| `/ext/u2f/key.u2f` | la chiave U2F di questo dispositivo, cifrata con una chiave univoca di questo Flipper |
| `/ext/u2f/cnt.u2f` | contatore delle autenticazioni |
| `/ext/u2f/assets/` | certificato di attestazione e la sua chiave (`cert.der`, `cert_key.u2f`) |

::: danger Non eliminare, modificare o spostare i file U2F
- Ogni Flipper ha una chiave interna univoca che cifra i file U2F. Una scheda con file U2F spostata su **un altro
  Flipper non funzionerà** lì.
- Se elimini o modifichi i file, oppure inserisci una nuova scheda, il Flipper crea un nuovo set di file U2F e devi
  **registrarlo di nuovo su ogni sito**.
- Se elimini `u2f/assets` (o l'intera cartella `u2f`), l'app smette di funzionare (segnala `No SD card or app data
  found`) finché non ripristini la cartella aggiornando il firmware.
:::

## Risoluzione dei problemi

| Sintomo | Rimedio |
|---|---|
| Resta su `Connect me to computer` | usa un cavo dati (non solo di ricarica), chiudi qFlipper, prova un'altra porta USB |
| `Connection Is Active!` | chiudi qFlipper, Flipper Lab, la CLI o la sessione dell'app mobile, poi riapri U2F |
| `No SD card or app data found` | inserisci la scheda; se è già inserita, ripristina `/ext/u2f/assets` reinstallando il firmware |
| `Certificate error` | il motore U2F non è riuscito ad avviarsi con i file presenti sulla scheda: reinstalla il firmware con la scheda inserita |
| Il sito non accetta più la chiave | i file U2F sono stati rigenerati (nuova scheda, file eliminati): accedi con il tuo fattore di riserva e registra di nuovo il Flipper |

Anche la scheda **U2F** dell'[Archive](/it/apps/archive) avvia l'app.

## Pagine correlate

- [App incluse in Unleashed](/it/apps/catalog)
- [Bad USB](/it/badusb/usage)
- [qFlipper](/it/mobile/qflipper)
