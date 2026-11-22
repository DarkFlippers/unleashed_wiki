---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** je NXP-ov nasljednik kartice MIFARE Classic. Može raditi u nekoliko **sigurnosnih razina (security levels)**:

| Razina | Ponašanje | Što Flipper radi |
|---|---|---|
| **SL0** | Tvorničko stanje / stanje personalizacije | Prepoznaje karticu, emulacija UID-a |
| **SL1** | **Kompatibilno s MIFARE Classic** (Crypto-1) | Čita **kao MIFARE Classic**: primjenjuju se rječnici, nested napadi, MFKey, qUnleashed |
| **SL2** | Podaci u stilu Classic s AES-om (nije prisutno na EV modelima) | Prepoznaje karticu, emulacija UID-a |
| **SL3** | ISO14443-4, AES-128 autentifikacija i sigurna razmjena poruka | Napad rječnikom AES ključeva, potpuni dump, potpuna emulacija, pisanje natrag na izvornu karticu |

Varijante proizvoda: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (i generički "Plus"); kapaciteti
1K (SE), 2K i 4K.

::: tip Unleashed
Prepoznavanje kartica MIFARE Plus prema proizvodu/razini/kapacitetu, **čitanje SL3 razine pomoću AES rječnika**, *Show Keys*, emulacija,
*Write to Initial Card* / *Update from Initial Card*, predmemorija ključeva po UID-u i generatori za MIFARE Plus u izborniku
*Add Manually* značajke su firmvera Unleashed.
:::

## Čitanje

1. `Main Menu → NFC → Read`, prislonite karticu.
2. Kartice u razini **SL1** čitaju se kao MIFARE Classic (pogledajte [MIFARE Classic](/hr/nfc/mifare-classic)). Oporavak ključeva za SL1 radi
   potpuno jednako kao za Classic; @gromovyna u [vodiču za qUnleashed](/hr/nfc/qunleashed) napominje da se on odnosi **samo** na MIFARE Plus
   **SL1**.
3. Kartice u razini **SL3**: napad AES rječnikom pokreće se automatski (zaglavlje **"MF Plus Dictionary"**). Prvo se isprobavaju korisnički ključevi,
   zatim sustavski rječnik; ključ spremljen u predmemoriju iz prethodnog spremanja istog UID-a isprobava se prije oba.
   Zaslon prikazuje *Keys Found* / *Sectors Read*. Ne postoji zasebna stavka "Unlock with Dictionary": taj je napad dio
   opcije `Read`.
4. Spremite karticu. Ključevi se spremaju u predmemoriju u `/ext/nfc/.cache/<UID>.mfpkeys`, pa se pri sljedećem čitanju iste kartice autentifikacija
   izvršava iz prvog pokušaja.

Rječnici: sustavski `/ext/nfc/assets/mf_plus_dict.nfc` (33 AES-128 ključa iz zadanih postavki alata Proxmark3), korisnički
`/ext/nfc/assets/mf_plus_dict_user.nfc`. Upravljajte njima u `NFC → Extra Actions → MIFARE Plus Keys` (**Add** za dodavanje 16-bajtnog
ključa, **List** za brisanje).

### Izbornici za SL3 karticu

- Nakon čitanja: **Save**, **Emulate**, **Show Keys** (*"Found MFP Keys"*: ključevi A/B po sektoru i administratorski ključevi poput
  Card Master Keyja, uz ukupne zbrojeve), **Info**.
- Spremljena kartica: **Emulate**, **Write to Initial Card** (zapisuje dump natrag na istu karticu), **Update from Initial
  Card** (ponovno čita izvornu karticu pomoću spremljenih ključeva; *"Use the source card only"* za ostale), **Show Keys**,
  **Rename**, **Delete**, **Info**.
- `Info → More` otvara izbornik sa stavkama **View Dump** (blokovi, administratorski ključevi, konfiguracijski blokovi, potpis) i
  **ISO14443-4 Data** (ATS itd.) → **More** (GetVersion polja: proizvođač hardvera/softvera, vrsta, inačica, kapacitet, serija,
  tjedan/godina proizvodnje).

Za ostale razine čuva se samo identitet i nudi se **Emulate UID**.

## Kako se prepoznaje MIFARE Plus

Firmver kombinira tri signala:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, ali i SL0 te DESFire).
2. **Povijesni bajtovi ATS-a** oblika `C1 05 …`: prepoznaju Plus S / X / SE bez ikakvog ključa.
3. **GetVersion** i proba sigurnosne razine na EV1/EV2 čipovima, što daje mjerodavnu vrstu i kapacitet.

Budući da se SAK `20` dijeli s karticama DESFire, kartica se označava kao Plus tek kada to potvrde proba ili ATS otisak.

### Referenca: kako to radi NXP TagInfo

Dokumentacija firmvera Unleashed uključuje analizu NXP-ove vlastite aplikacije **NFC TagInfo** (v6.2.0) korištene kao referenca. Njezin postupak
odlučivanja:

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → "Classic lane" (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, then DESELECT (C2)
│   │   match ATS historical bytes → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), status 90 → EV generation → EV1
│   ├─ security level = SL1 (answers Classic block auth)
│   └─ size = Plus AES First-Auth probe to increasing key-block addresses
└─ SAK == 20 → "ISO-DEP lane" (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) succeeds → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ storage size)
    └─ size = GET_VERSION storage byte (22 = 2K, 42 = 4K)
```

ATS otisci (povijesni bajtovi, točni do u bajt):

| Povijesni bajtovi ATS-a | Podvrsta | Šifra proizvoda |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (alt) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Inženjerski uzorak | — |
| bez podudaranja | Plus **X** (zadano) | `MF1PLUS` |

U obitelji `C1 05 2F 2F …` bajt 4 razlikuje S (`00`) od X (`01`). Modeli EV1/EV2 odgovaraju na **Read-Signature** (`3C`),
dok Plus S/X ne odgovaraju. U odgovoru GetVersion bajt proizvođača je `04` (NXP), a bajt kapaciteta `22` = 2K, `42` = 4K.

Tumačenje SAK-a koje koristi TagInfo:

| SAK | Značenje |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / varijanta Plus 2K |
| `28`, `38` | SmartMX s Classic 1K / 4K |
| `88` | NXP Classic 1K (bit 0x80) |
| `98`, `B8` | SmartMX / Pro varijante |
| `01` | naslijeđena oznaka / TNP marker |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

Veličina memorije na razini SL1 ispituje se pomoću Plus AES **First-Auth** okvira `70 XX 40 01 00` prema blokovima ključeva `0x4010`, `0x4020`,
`0x4040`, `0x4064`: najviši na koji kartica odgovori određuje broj sektora (osnovni / 2K / 4K / prošireni). Generirane šifre proizvoda:
`MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE), `MF1P2101` (EV1 2K).

## Ručno stvaranje kartice MIFARE Plus

`NFC → Add Manually` nudi Plus SE (4/7-bajtni UID), Plus S, X, EV1 i EV2 u kapacitetima 2K/4K sa 4- ili 7-bajtnim UID-om.
Stvorena kartica dobiva odgovarajuće povijesne bajtove ATS-a, pogledajte [Ručno dodavanje kartica](/hr/nfc/add-manually).

## Povezano

[MIFARE Classic](/hr/nfc/mifare-classic) · [Čitanje kartica](/hr/nfc/read) · [qUnleashed](/hr/nfc/qunleashed) ·
[Format NFC datoteka](/hr/nfc/file-format)
