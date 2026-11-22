---
title: Otključavanje kartica lozinkama
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Otključavanje kartica lozinkama i ključevima

Kartice organizirane u **stranice** (MIFARE Ultralight, NTAG) mogu zaštititi dio svoje memorije. Ako `Read` prikaže
**"Some Pages Are Locked!"** / **"Password-protected pages!"** i `Pages Read: X/Y` gdje je X < Y, kartica zahtijeva
lozinku ili ključ. Ovisno o kartici:

| Kartica | Zaštita | Kako je Flipper otključava |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | 4-bajtna lozinka (PWD) + 2-bajtni PACK | hvatanje s čitača, generiranje iz UID-a (amiibo, Xiaomi) ili ručni unos |
| Ultralight C | 16-bajtni 3DES ključ | napad rječnikom (automatski) ili ručni unos ključa |
| Ultralight AES | 16-bajtni AES ključ | napad rječnikom (automatski) ili ručni unos ključa, pogledajte [Ultralight AES](/hr/nfc/ultralight-aes) |
| ICODE SLIX-L | 4-bajtna lozinka | `Extra Actions → Unlock SLIX-L` |

::: danger Pogrešne lozinke mogu zaključati karticu
Mnoge kartice broje neuspjele autentifikacije (`AUTHLIM`) i trajno se zaključavaju nakon previše pokušaja. Flipper upozorava porukom **"Risky action! Wrong password can block your card."** prije nego što isproba lozinku. Nemojte koristiti brute-force.
:::

## Hvatanje lozinke s čitača

Ako imate i karticu i čitač koji je prihvaća: emulirajte karticu, pustite da čitač pošalje svoju lozinku, uhvatite je, a zatim njome pročitajte karticu.

1. [Pročitajte i spremite](/hr/nfc/read) karticu.
2. Idite na `Main Menu → NFC → Saved → <card> → Unlock`.
3. Odaberite **Unlock With Reader**. Na zaslonu se prikazuje *"Touch the reader to get password..."*. Prislonite Flipper na čitač.
4. Kada je lozinka uhvaćena, prikazuje se **Password Captured!** s njezinom vrijednošću. Pritisnite **Continue**.
5. Prislonite karticu na stražnju stranu Flippera (*"Hold card next to Flipper's back"*, zatim *"Don't move"*).
6. Kada su stranice otključane (**"All Pages Are Unlocked!"**), idite na **More → Save**, imenujte karticu i spremite je.

Ako ništa nije uhvaćeno (*"Password not captured."*), čitač možda ne koristi lozinku ili kartica pripada drugom čitaču.

`Unlock With Reader` nije dostupan za Ultralight C (koristi uzajamnu 3DES autentifikaciju, lozinka se ne šalje u otvorenom tekstu).

## Generiranje lozinke iz UID-a

Za figurice **toys-to-life** (NTAG215 u stilu amiibo) i filtre **Xiaomi Air Purifier**, lozinka se izvodi iz UID-a kartice.

1. Idite na `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (ili, za spremljenu karticu, `Saved → <card> → Unlock`).
2. Odaberite **Auth As Ameebo** ili **Auth As Xiaomi Air Purifier**.
3. Potvrdite upozorenje i prislonite karticu na Flipper.
4. Kada su stranice otključane, pritisnite **Save** za spremanje kartice.

## Ručni unos lozinke

1. `Main Menu → NFC → Saved → <card> → Unlock` (ili `Extra Actions → Unlock NTAG/Ultralight` prije čitanja).
2. Odaberite **Enter Password Manually**.
3. **"Enter the password in hex"**: upišite 4 bajta i potvrdite.
4. Potvrdite upozorenje *"Try to unlock the card with password: …"* i prislonite karticu na Flipper.
5. Pritisnite **Save** za spremanje otključane kartice.

## Ultralight C: 3DES ključevi

Kartice Ultralight C koriste 16-bajtni 3DES ključ. Flipper ima ugrađeni rječnik poznatih ključeva
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 ključeva, uključujući NXP-ov ogledni ključ `BREAKMEIFYOUCAN!`) i korisnički
rječnik (`mf_ultralight_c_dict_user.nfc`).

- Prilikom `Read`, ako kartica nije potpuno čitljiva, napad rječnikom pokreće se sam: zaglavlja
  **"MFUL C User Dictionary"**, zatim **"MFUL C System Dictionary"**, s prikazom `Key found: Yes/No` i `Pages read: X/Y`.
- Na spremljenoj, nepotpunoj kartici: **Unlock with Dictionary** ponovno pokreće napad; **Unlock** pita **"Enter key in hex"**
  (16 bajtova), a zatim **"Risky Action! Unlock with key: … ?"** uz opcije **Unlock** / **Cancel**.
- Dodavanje vlastitih ključeva: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Potpuno pročitani izvadak Ultralight C kartice nudi opcije **Write (Keep Key)** (zadržava 3DES ključ ciljne kartice) i **Write (Copy Key)**
(zapisuje i stranice ključa iz izvatka) na karticu iste vrste.

::: tip Unleashed
Ručni unos 3DES/AES ključa, pisanje natrag na Ultralight C/AES kartice uz Keep/Copy Key te rječnik za Ultralight AES
(`Extra Actions → MIFARE UL AES Keys`) značajke su firmvera Unleashed.
:::

## ICODE SLIX-L

1. Idite na `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Odaberite **Enter Password Manually** (4 bajta u heksadekadskom obliku) ili **Auth As TommyBox** (poznata lozinka oznaka TommyBox).
3. Prislonite oznaku na Flipper (*"Unlocking — Hold card next to Flipper's back"*).
4. Na zaslonu **SLIX Unlocked!** pritisnite **More** za nastavak na rezultat čitanja i spremanje ili **Retry**.

## Ako otključavanje nije uspjelo

- Kartica je možda uparena s drugim čitačem ili koristi ključ izveden posebno za svaku karticu.
- Lozinka je ispravna, ali neke stranice ostaju zaključane: bitovi zaključavanja ili postavke `AUTH0`/`PROT` mogu učiniti stranice trajno samo za čitanje ili nečitljivima bez autentifikacije.
- Za Ultralight AES pogledajte napomenu o redoslijedu bajtova na stranici [Ultralight AES](/hr/nfc/ultralight-aes).

## Povezano

[Čitanje kartica](/hr/nfc/read) · [Ultralight AES](/hr/nfc/ultralight-aes) · [Filtri čitača Vizit](/hr/nfc/vizit-filters) ·
[NFC format datoteke](/hr/nfc/file-format)
