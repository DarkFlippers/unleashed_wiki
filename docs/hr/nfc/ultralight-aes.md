---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** jest Ultralight s obostranom autentifikacijom **AES-128** umjesto lozinke (NTAG21x) ili 3DES-a (Ultralight C). Ima 60 stranica, tri jednosmjerna brojača, 48-bajtni ECC potpis izvornosti, opcionalni način **Random ID** i opcionalnu **sigurnu razmjenu poruka (secure messaging)** (svaka naredba i odgovor zaštićeni su CMAC-om).

::: tip Unleashed
Podrška za Ultralight AES (čitanje, napad rječnikom, ručni unos ključa, emulacija, povratno pisanje, dekodiranje konfiguracije, Random ID, sigurna razmjena poruka) značajka je firmvera Unleashed, provjerena na stvarnoj kartici MF0AES20 u odnosu na referentne rezultate s Proxmark3.
:::

## Što Flipper radi s njom

| Značajka | Detalji |
|---|---|
| Prepoznavanje i čitanje | Prepoznaje se kao `Mifare Ultralight AES`, ATQA `0044`, SAK `00`, `60/60` stranica na otvorenoj kartici, brojači. |
| Potpis izvornosti | Sprema se u datoteku `.nfc` kao redak `AES signature:` (48 bajtova) i ponavlja tijekom emulacije kako bi prošla provjera potpisa na čitaču. |
| AES autentifikacija | 3-stupanjski AES izazov-odgovor, nakon čega se čitaju zaštićene stranice. |
| Napad rječnikom | Pokreće se automatski pri nepotpunom čitanju: najprije **MFUL AES User Dictionary**, zatim **MFUL AES System Dictionary**. |
| Ručni ključ | `Saved → <card> → Unlock` → **„Enter key in hex“** (16 bajtova) → potvrdite **Unlock**. |
| Upravljanje ključevima | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Povratno pisanje | **Write (Keep Key)** / **Write (Copy Key)** na potpuno pročitanom dumpu. |
| Emulacija | Potpuna, uključujući AES autentifikaciju u ulozi kartice, prag `AUTH0` i sigurnu razmjenu poruka. |
| Dekodiranje konfiguracije | `Info` prikazuje blok **UL-AES Config** (pogledajte u nastavku). |
| Random ID | Otkriva se i prikazuje (`Random ID: on`); **Reveal Real UID** pokušava dohvatiti stvarni UID. |

Rječnici: sistemski `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (tvornički ključ od samih nula, `BREAKMEIFYOUCAN!` ponovno korišten kao AES i druge uobičajene zadane vrijednosti iz Proxmark3) i korisnički `/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. Tvornička kartica koristi ključ od samih nula `00000000000000000000000000000000` za DataProtKey i za UIDRetrKey.

## Čitanje zaštićene kartice

1. `Main Menu → NFC → Read`, prislonite karticu.
2. Otvorene stranice se očitaju; ako kartica ima područje zaštićeno AES-om, napad rječnikom pokreće se sam (najprije korisnički rječnik, zatim sistemski).
3. Ako neki ključ odgovara, sve stranice se pročitaju, a ključ se prikazuje i sprema uz dump. Ako ne odgovara, dobivate djelomično čitanje (npr. `42/60` stranica) i **„AES-protected pages!“**, bez blokiranja ili trošenja pokušaja na kartici s neograničenim brojem pokušaja.
4. Spremite karticu. Kasnije možete pokušati ponovno putem **Unlock with Dictionary** (nakon dodavanja ključeva) ili **Unlock** (ručni unos ključa).

::: warning Redoslijed bajtova ključa
Sirovo pisanje stranica (npr. Proxmark3 `hf mfu wrbl`) pohranjuje ključ u **redoslijedu memorije oznake**; AES mehanizam, ručni unos na Flipperu i PM3 `hf mfu aesauth --key` koriste **obrnuti** redoslijed. Kartica čije stranice `0x30–0x33` glase `A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` autentificira se s `AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Ručno otkriveni ključ unesite **u AES redoslijedu**. U spremljenoj datoteci `.nfc` stranice ključa (`Page 48`–`51`) pohranjene su u redoslijedu memorije oznake kako bi se mogle doslovno zapisati natrag; redak `DataProtKey:` na zaslonu samo je prikaz.
:::

## Memorija i konfiguracija

| Stavka | Lokacija |
|---|---|
| DataProtKey | stranice `0x30`–`0x33` |
| UIDRetrKey | stranice `0x34`–`0x37` |
| CFG | stranica `0x29`: bajt 0 bit0 = `RID_ACT`, bit1 = `SEC_MSG_ACT`; bajt 3 = `AUTH0` |
| ACCESS | stranica `0x2A`: bajt 0 bit2 = `CNT_RD_EN`, bit3 = `CNT_INC_EN`, bit6 = `CFGLCK`, bit7 = `PROT`; bajtovi 2–3 = `AUTH_LIM` |
| LOCK_KEYS | stranica `0x2D`: bajt 0 = bitovi zaključavanja po ključu |

Blok **UL-AES Config** u `Info` dekodira te vrijednosti, npr.:

- `Auth from: off (open)` ili `Auth from: page 0x10 (r+w)` / `(write)`: `AUTH0` i `PROT`;
- `Auth limit: unlimited` ili `Auth limit: N (locks!)`;
- `Counter 2: rd open / inc auth` i slično;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N`;
- `Real UID:` nakon što se otkrije.

::: danger Nemojte eksperimentirati s ovim bitovima
`CFGLCK` zaključava konfiguraciju **trajno**, `AUTH_LIM` aktivira zaključavanje nakon neuspjelih autentifikacija, a `LOCK_KEYS` / statični bitovi zaključavanja mogu trajno onesposobiti karticu. Nikada ih nemojte mijenjati na kartici do koje vam je stalo. Imajte na umu i da PM3-ov `hf mfu info` označava stranice `0x34`–`0x37` kartice MF0AES20 starim predloškom za Ultralight (`cfg0/cfg1/PWD/PACK`); oslonite se na gornju tablicu.
:::

## Povratno pisanje dumpa

Nudi se samo na **potpuno pročitanom** dumpu Ultralight AES, kao dvije stavke:

- **Write (Keep Key)**: zapisuje podatkovne stranice `0x04`–`0x27`; ključ ciljne kartice ostaje netaknut.
- **Write (Copy Key)**: podatkovne stranice plus **DataProtKey** (`0x30`–`0x33`) iz dumpa.

Pravila ugrađena u firmver:

- Pisanje se **najprije autentificira prema ciljnoj kartici** ključem iz rječnika, pa *trenutačni* ključ ciljne kartice mora biti u rječniku (tvornički ključ od samih nula jest u njemu).
- Konfiguracijske/zaključavajuće stranice `0x28`–`0x2F` **nikada** se ne zapisuju; `UIDRetrKey` (`0x34`–`0x37`) nikada se ne zapisuje.
- Ciljna kartica mora biti iste **vrste**; UID se ne mora podudarati.

## Emulacija

`Saved → <card> → Emulate`. Emulirana kartica odgovara na `GET_VERSION`, potpis, brojače i konfiguraciju poput prave kartice, obavlja AES autentifikaciju kao kartica koristeći `reverse(pages 0x30–0x33)` kao ključ, odbija pogrešne ključeve i provodi `AUTH0`. Napomena: ograničena čitanja bez autentifikacije vraćaju preliveni sadržaj ranih stranica umjesto odgovora NAK.

## Random ID

Kad je uključen `RID_ACT`, kartica pri svakom odabiru prikazuje **nasumični 4-bajtni UID koji započinje s `08`**; stvarni 7-bajtni UID skriven je do autentificiranog čitanja. Flipper prikazuje nasumični UID i `Random ID: on`. Za takve kartice izbornik ima opciju **Reveal Real UID**: potvrđuje uz upozorenje, ponovno očitava karticu i pokušava se autentificirati (zadani `UIDRetrKey` od samih nula) kako bi otkrio statični UID, prikazan kao `Real UID:` u prikazu konfiguracije.

## Sigurna razmjena poruka (CMAC)

Kad je uključen `SEC_MSG_ACT`, nakon autentifikacije **svaka** naredba i odgovor moraju sadržavati CMAC. Flipper se tomu prilagođava automatski: nakon autentifikacije prvo obično `READ`/`WRITE` ne uspije (pravi čip jednostavno zašuti, što čitač vidi kao istek vremena), firmver se ponovno autentificira i prebacuje na MAC-om zaštićene naredbe `READ`, `READ_CNT` i `WRITE`. Brojač naredbi uvećava se za 2 po razmjeni (naredba koristi `CmdCtr`, odgovor `CmdCtr+1`). Provjereno na hardveru: potpuno čitanje 60/60 preko CMAC-a bez nepodudaranja MAC-a, brojači preko CMAC-a, stranice ključeva `0x30`–`0x37` maskirane nulama u dumpu i CMAC povratno pisanje podatkovnih stranica.

Emulator također podržava sigurnu razmjenu poruka: provjerava MAC naredbe, dodaje MAC svakom odgovoru, zamjenjuje `WRITE` ACK MAC-om i prekida sesiju pri pogrešnom MAC-u.

::: warning Mogućnost oporavka
Jednom kad je `SEC_MSG_ACT` uključen, pisanje konfiguracije u zaštićenom području zahtijeva CMAC-autentificirano pisanje, što Proxmark3 ne može izvesti, a Flipperovo pisanje preskače (konfiguracijske stranice nikada se ne zapisuju). Nemojte postavljati `AUTH0 ≤ 0x29` na kartici sa sigurnom razmjenom poruka jer je možda više nećete moći isključiti.
:::

### Oznake za otklanjanje pogrešaka

Uz `Settings → System → Log Level → Debug` možete pratiti što se događa u zapisniku, primjerice `UL-AES: plain read failed post-auth, switching to secure messaging`, `UL-AES response MAC mismatch (ctr N)` (ne bi se smjelo pojaviti u ispravnom radu) i `UL-AES command MAC mismatch, dropping session` (na strani emulatora).

## Povezano

[Otključavanje kartica](/hr/nfc/unlock-with-password) · [Čitanje kartica](/hr/nfc/read) · [Format NFC datoteka](/hr/nfc/file-format) · [Ručno dodavanje kartica](/hr/nfc/add-manually)
