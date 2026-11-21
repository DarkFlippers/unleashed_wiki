---
title: "MFKey32: chiavi dal lettore"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: recuperare le chiavi da un lettore

**MFKey32** è un attacco al cifrario Crypto-1 di MIFARE Classic. Il Flipper finge di essere la carta; il lettore prova
ad autenticarsi con la sua chiave reale, e le due coppie nonce/risposta che invia bastano a calcolare quella chiave
offline. L'attacco richiede quindi **accesso al lettore**, non alle chiavi.

Usalo quando:

- la carta viene letta solo in parte e le chiavi mancanti sono quelle che usa il lettore (il caso più comune);
- non hai la carta ma vuoi conoscere le chiavi di un lettore e aggiungerle al tuo dizionario;
- la carta non ha backdoor né chiavi note, quindi gli [attacchi nested](/it/nfc/nested-fudan) non possono partire.

## Con la carta e il lettore (consigliato)

Avere la carta significa che, dopo aver recuperato le chiavi del lettore, puoi leggere più settori, che di solito sono
proprio quelli che il lettore controlla davvero.

1. Leggi la carta (`Main Menu → NFC → Read`). Risulta letta solo in parte.
2. In **More** seleziona **Extract MFC Keys**. Il Flipper chiede *"Save the Key?"*: **Save** (il dump ti servirà più
   tardi) oppure **Skip**.
   *In alternativa*, apri una carta già salvata: `Main Menu → NFC → Saved → <carta> → Extract MFC Keys`.
3. La schermata mostra **"Emulating... MIFARE MFkey32"** con l'UID della carta e *"Touch the reader"*.

   ![Emulazione MIFARE MFkey32 con l'UID della carta e l'invito ad avvicinare il lettore](/screens/nfc/mfkey_start.png)

4. Appoggia il retro del Flipper al lettore, allontanalo (*"Move the Flipper away"*), appoggialo di nuovo
   (*"Touch the reader again"*). Il contatore **Nonce pairs: X/10** cresce a ogni tentativo riuscito.

   ![Raccolta di coppie di nonce: 4 su 10 raccolte, invito ad allontanare il Flipper](/screens/nfc/mfkey_collecting.png)

5. Quando sono state raccolte 10 coppie la schermata dice **Completed!**. Puoi fermarti prima con <kbd>OK</kbd>
   **Done**.
6. La schermata successiva elenca **Nonce pairs saved: N** e gli **Authenticated sectors** (quale settore e quale tipo
   di chiave ha richiesto il lettore). Premi <kbd>OK</kbd>.

   ![Nonce pairs saved: 5, con l'elenco dei settori autenticati e dei tipi di chiave](/screens/nfc/mfkey_nonces_info.png)

7. Il Flipper propone di recuperare le chiavi: **"Now run Mfkey32 to extract keys"** con **Run** (apre l'
   [app MFKey](/it/nfc/mfkey-app)). Se l'app è assente mostra un codice QR verso `r.flipper.net/nfc-tools` e
   **Finish**.
8. Recupera le chiavi con uno degli strumenti qui sotto. Vengono aggiunte al dizionario utente.
9. Rileggi la carta (oppure `Saved → <carta> → Unlock with Dictionary`). Ora dovrebbero essere trovate più chiavi e
   più settori.
10. Emula o scrivi la carta.

I nonce vengono salvati in `/ext/nfc/.mfkey32.log`, una riga per coppia:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Il contatore non cresce?
Il lettore non sta provando ad autenticare la carta emulata. Alcuni lettori controllano solo l'UID o usano un altro
protocollo; altri rifiutano del tutto l'emulazione. Prova distanze e angoli diversi; a volte servono diversi
avvicinamenti per una sola coppia.
:::

## Solo il lettore

1. Vai in `Main Menu → NFC → Extract MFC Keys`. Il Flipper emula una carta MIFARE Classic generica.
2. I passaggi 3–8 come sopra.
3. Le chiavi recuperate sono nel dizionario utente e verranno provate automaticamente quando in seguito leggerai carte
   di quel sistema.

## Recuperare le chiavi dai nonce

| Strumento | Dove | Note |
|---|---|---|
| **App MFKey** sul Flipper | `Main Menu → Apps → NFC → MFKey` | Non serve telefono o PC. Gestisce `.mfkey32.log` e `.nested.log`. Più lenta. Vedi [App MFKey](/it/nfc/mfkey-app). |
| **qUnleashed** (app companion di Unleashed) | `Tools → Recover MIFARE Keys` | Elabora `.mfkey32.log` e `.nested.log`, compresi i nonce hard e static encrypted. Veloce. Vedi [qUnleashed](/it/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | App ufficiale, solo nonce del lettore. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Via USB nel browser. |

::: tip Unleashed
In Unleashed la voce di menu si chiama **Extract MFC Keys** (nel firmware di serie: *Extract MF Keys*), e l'app
companion **qUnleashed** può recuperare le chiavi direttamente sul telefono o sul computer. Da **MFKey 4.x**
(build dev Unleashed 1251 e successive) il recupero sul Flipper stesso è diverse volte più rapido, vedi
[App MFKey](/it/nfc/mfkey-app).
:::

## Se il recupero non riesce

- **Nessuna chiave trovata dai nonce**: il lettore non ha accettato correttamente l'emulazione del Flipper. Raccogli di
  nuovo, prova con un altro dump di carta (una carta reale salvata funziona meglio di un'emulazione generica).
- **MFKey mostra "No nonces found"**: non esiste né `.mfkey32.log` né `.nested.log`.
- **MFKey si blocca o va in crash**: riavvia (tieni premuto <kbd>←</kbd> + <kbd>Back</kbd> per 5 secondi), elimina
  `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log`, raccogli di nuovo.
- **Ultima risorsa**: fai un backup ed elimina `/ext/nfc/assets/mf_classic_dict_user.nfc` (questo rimuove **tutte** le
  tue chiavi utente).

## Pagine correlate

[MIFARE Classic](/it/nfc/mifare-classic) · [Attacchi nested](/it/nfc/nested-fudan) · [App MFKey](/it/nfc/mfkey-app) ·
[qUnleashed](/it/nfc/qunleashed)
