---
title: Sbloccare le carte con password
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Sbloccare le carte con password e chiavi

Le carte organizzate in **pagine** (MIFARE Ultralight, NTAG) possono proteggere una parte della loro memoria. Se
`Read` mostra **"Some Pages Are Locked!"** / **"Password-protected pages!"** e `Pages Read: X/Y` con X < Y, la carta
richiede una password o una chiave. A seconda della carta:

| Carta | Protezione | Come la sblocca il Flipper |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | password da 4 byte (PWD) + PACK da 2 byte | cattura dal lettore, generazione dall'UID (amiibo, Xiaomi) oppure inserimento manuale |
| Ultralight C | chiave 3DES da 16 byte | attacco a dizionario (automatico) oppure inserimento manuale della chiave |
| Ultralight AES | chiave AES da 16 byte | attacco a dizionario (automatico) oppure inserimento manuale della chiave, vedi [Ultralight AES](/it/nfc/ultralight-aes) |
| ICODE SLIX-L | password da 4 byte | `Extra Actions → Unlock SLIX-L` |

::: danger Le password sbagliate possono bloccare la carta
Molte carte contano le autenticazioni fallite (`AUTHLIM`) e si bloccano in modo permanente quando sono troppe. Il
Flipper avverte con **"Risky action! Wrong password can block your card."** prima di provare una password. Non fare
bruteforce.
:::

## Catturare la password dal lettore

Se hai la carta e il lettore che la accetta: emula la carta, lascia che il lettore invii la sua password, catturala e
poi leggi la carta con quella.

1. [Leggi e salva](/it/nfc/read) la carta.
2. Vai in `Main Menu → NFC → Saved → <carta> → Unlock`.
3. Seleziona **Unlock With Reader**. La schermata dice *"Touch the reader to get password..."*. Avvicina il Flipper al
   lettore.
4. Quando la password è stata catturata vedi **Password Captured!** con il suo valore. Premi **Continue**.
5. Appoggia la carta al retro del Flipper (*"Hold card next to Flipper's back"*, poi *"Don't move"*).
6. Quando le pagine sono sbloccate (**"All Pages Are Unlocked!"**), vai in **More → Save**, dai un nome alla carta e
   salvala.

Se non viene catturato nulla (*"Password not captured."*), il lettore potrebbe non usare una password, oppure la carta
appartiene a un altro lettore.

`Unlock With Reader` non viene proposto per Ultralight C (usa un'autenticazione mutua 3DES, nessuna password viene
inviata in chiaro).

## Generare la password dall'UID

Per le figure **toys-to-life** (NTAG215 in stile amiibo) e per i filtri dei **purificatori d'aria Xiaomi**, la password
è derivata dall'UID della carta.

1. Vai in `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (oppure, per una carta salvata, `Saved → <carta> → Unlock`).
2. Seleziona **Auth As Ameebo** oppure **Auth As Xiaomi Air Purifier**.
3. Conferma l'avviso e appoggia la carta al Flipper.
4. Quando le pagine sono sbloccate, salva la carta con **Save**.

## Inserire la password manualmente

1. `Main Menu → NFC → Saved → <carta> → Unlock` (oppure `Extra Actions → Unlock NTAG/Ultralight` prima della lettura).
2. Seleziona **Enter Password Manually**.
3. **"Enter the password in hex"**: digita i 4 byte, conferma.
4. Conferma l'avviso *"Try to unlock the card with password: …"* e appoggia la carta al Flipper.
5. Salva la carta sbloccata con **Save**.

## Ultralight C: chiavi 3DES

Le carte Ultralight C usano una chiave 3DES da 16 byte. Il Flipper ha un dizionario integrato di chiavi note
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 chiavi, compresa la chiave di esempio NXP `BREAKMEIFYOUCAN!`) e un
dizionario utente (`mf_ultralight_c_dict_user.nfc`).

- Durante `Read`, se la carta non è completamente leggibile, l'attacco a dizionario parte da solo: intestazioni
  **"MFUL C User Dictionary"**, poi **"MFUL C System Dictionary"**, con `Key found: Yes/No` e `Pages read: X/Y`.
- Su una carta salvata e incompleta: **Unlock with Dictionary** riesegue l'attacco; **Unlock** chiede
  **"Enter key in hex"** (16 byte) e poi **"Risky Action! Unlock with key: … ?"** con **Unlock** / **Cancel**.
- Aggiungi le tue chiavi: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Un dump Ultralight C letto completamente offre **Write (Keep Key)** (mantiene la chiave 3DES della carta di
destinazione) e **Write (Copy Key)** (scrive anche le pagine della chiave prese dal dump) verso una carta dello stesso
tipo.

::: tip Unleashed
L'inserimento manuale delle chiavi 3DES/AES, la riscrittura Ultralight C/AES con Keep/Copy Key e il dizionario
Ultralight AES (`Extra Actions → MIFARE UL AES Keys`) sono funzioni di Unleashed.
:::

## ICODE SLIX-L

1. Vai in `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Scegli **Enter Password Manually** (4 byte in esadecimale) oppure **Auth As TommyBox** (la password nota dei tag
   TommyBox).
3. Appoggia il tag al Flipper (*"Unlocking — Hold card next to Flipper's back"*).
4. Su **SLIX Unlocked!** premi **More** per passare al risultato della lettura e salvarlo, oppure **Retry**.

## Se lo sblocco è fallito

- La carta potrebbe essere abbinata a un lettore diverso, oppure usare una chiave derivata per singola carta.
- La password è corretta ma alcune pagine restano bloccate: i lock bit o le impostazioni `AUTH0`/`PROT` possono rendere
  le pagine permanentemente di sola lettura o illeggibili senza autenticazione.
- Per Ultralight AES vedi la nota sull'ordine dei byte in [Ultralight AES](/it/nfc/ultralight-aes).

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [Ultralight AES](/it/nfc/ultralight-aes) ·
[Filtri dei lettori Vizit](/it/nfc/vizit-filters) · [Formato dei file NFC](/it/nfc/file-format)
