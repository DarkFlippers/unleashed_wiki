---
title: "MFKey32: ključevi s čitača"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: dohvaćanje ključeva s čitača

**MFKey32** je napad na šifru Crypto-1 kartica MIFARE Classic. Flipper se predstavlja kao kartica; čitač se pokušava autentificirati svojim pravim ključem, a dva para nonce/odgovor koja pošalje dovoljna su za izračun tog ključa izvan mreže. Napad stoga zahtijeva **pristup čitaču**, a ne ključevima.

Koristite ga kada:

- je kartica pročitana samo djelomično, a ključevi koji nedostaju jesu oni koje koristi čitač (najčešći slučaj);
- uopće nemate karticu, ali želite saznati ključeve čitača i dodati ih u svoj rječnik;
- kartica nema stražnja vrata (backdoor) ni poznati ključ, pa se [nested napadi](/hr/nfc/nested-fudan) ne mogu pokrenuti.

## Uz karticu i čitač (preporučeno)

Posjedovanje kartice znači da nakon dohvaćanja ključeva čitača možete pročitati više sektora, što je obično ono što čitač zapravo provjerava.

1. Pročitajte karticu (`Main Menu → NFC → Read`). Ostat će djelomično pročitana.
2. U izborniku **More** odaberite **Extract MFC Keys**. Flipper pita *"Save the Key?"*: odaberite **Save** (trebat će vam dump kasnije) ili **Skip**.
   *Alternativno*, otvorite već spremljenu karticu: `Main Menu → NFC → Saved → <card> → Extract MFC Keys`.
3. Na zaslonu se prikazuje **"Emulating... MIFARE MFkey32"** s UID-om kartice i porukom *"Touch the reader"*.

   ![Emulacija MIFARE MFkey32 s UID-om kartice i uputom za prislanjanje na čitač](/screens/nfc/mfkey_start.png)

4. Prislonite stražnju stranu Flippera na čitač, odmaknite ga (*"Move the Flipper away"*) pa ponovno prislonite (*"Touch the reader again"*). Brojač **Nonce pairs: X/10** raste sa svakim uspješnim pokušajem.

   ![Prikupljanje parova nonce vrijednosti: prikupljeno 4 od 10, uputa za odmicanje Flippera](/screens/nfc/mfkey_collecting.png)

5. Kada se prikupi 10 parova, na zaslonu piše **Completed!**. Možete završiti i ranije tipkom <kbd>OK</kbd> **Done**.
6. Sljedeći zaslon prikazuje **Nonce pairs saved: N** i **Authenticated sectors** (za koji sektor i koju vrstu ključa je čitač pitao). Pritisnite <kbd>OK</kbd>.

   ![Spremljeno parova nonce vrijednosti: 5, uz popis autentificiranih sektora i vrsta ključeva](/screens/nfc/mfkey_nonces_info.png)

7. Flipper nudi opciju za dohvaćanje ključeva: **"Now run Mfkey32 to extract keys"** s gumbom **Run** (otvara [aplikaciju MFKey](/hr/nfc/mfkey-app)). Ako aplikacija nije instalirana, prikazuje QR kôd za `r.flipper.net/nfc-tools` i **Finish**.
8. Izračunajte ključeve jednim od alata u nastavku. Dodaju se u korisnički rječnik.
9. Ponovno pročitajte karticu (ili `Saved → <card> → Unlock with Dictionary`). Sada bi trebalo biti pronađeno više ključeva i sektora.
10. Emulirajte ili zapišite karticu.

Nonce vrijednosti pohranjuju se u `/ext/nfc/.mfkey32.log`, po jedan par u retku:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Brojač ne raste?
Čitač ne pokušava autentificirati emuliranu karticu. Neki čitači provjeravaju samo UID ili koriste drugi protokol; drugi u potpunosti odbijaju emulaciju. Pokušajte s različitim udaljenostima i kutovima; ponekad je potrebno nekoliko prislanjanja za jedan par.
:::

## Samo s čitačem

1. Idite na `Main Menu → NFC → Extract MFC Keys`. Flipper emulira generičku MIFARE Classic karticu.
2. Slijedite korake 3–8 kao iznad.
3. Dohvaćeni ključevi nalaze se u korisničkom rječniku i automatski će se isprobati kada kasnije budete čitali kartice tog sustava.

## Izračun ključeva iz nonce vrijednosti

| Alat | Gdje | Napomene |
|---|---|---|
| **Aplikacija MFKey** na Flipperu | `Main Menu → Apps → NFC → MFKey` | Ne zahtijeva telefon ni računalo. Obrađuje `.mfkey32.log` i `.nested.log`. Sporija. Pogledajte [Aplikacija MFKey](/hr/nfc/mfkey-app). |
| **qUnleashed** (prateća aplikacija za Unleashed) | `Tools → Recover MIFARE Keys` | Obrađuje `.mfkey32.log` i `.nested.log`, uključujući hard i static-encrypted nonce vrijednosti. Brz. Pogledajte [qUnleashed](/hr/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Službena aplikacija, samo nonce vrijednosti čitača. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Putem USB-a u pregledniku. |

::: tip Unleashed
U firmveru Unleashed stavka izbornika zove se **Extract MFC Keys** (izvorni firmver: *Extract MF Keys*), a prateća aplikacija **qUnleashed** može izračunati ključeve izravno na vašem telefonu ili računalu. Od verzije **MFKey 4.x** (Unleashed dev build 1251+) izračun na samom Flipperu višestruko je brži, pogledajte [Aplikacija MFKey](/hr/nfc/mfkey-app).
:::

## Ako izračun ne uspije

- **Nema pronađenih ključeva iz nonce vrijednosti**: čitač nije ispravno prihvatio Flipperovu emulaciju. Ponovno prikupite podatke i pokušajte s drugim dumpom kartice (spremljena stvarna kartica radi bolje od generičke emulacije).
- **MFKey prikazuje "No nonces found"**: ne postoji ni `.mfkey32.log` ni `.nested.log`.
- **MFKey se smrzne ili sruši**: ponovno pokrenite uređaj (držite <kbd>←</kbd> + <kbd>Back</kbd> 5 sekundi), obrišite `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log` i prikupite ponovno.
- **Krajnje rješenje**: izradite sigurnosnu kopiju i obrišite `/ext/nfc/assets/mf_classic_dict_user.nfc` (time uklanjate **sve** svoje korisničke ključeve).

## Povezano

[MIFARE Classic](/hr/nfc/mifare-classic) · [Nested napadi](/hr/nfc/nested-fudan) · [Aplikacija MFKey](/hr/nfc/mfkey-app) · [qUnleashed](/hr/nfc/qunleashed)
