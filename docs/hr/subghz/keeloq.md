---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq je šifra koja stoji iza golemog broja daljinskih upravljača za kapije, garažna vrata i rampe (DoorHan, Nice Smilo, FAAC RC,
BFT, Came Space, Beninca, Hormann EcoStar…) te starijih autoalarma. Ova stranica objašnjava kako radi, što su
"proizvođački ključevi" (manufacturer keys) i "seed" vrijednosti te kako ih Unleashed obrađuje.

Teorijski dio temelji se na članku **"KeeLoq и с чем его едят"** autora [@li0ard](https://blog.li0ard.rest/wtfiskeeloq),
člana istraživačkog tima @gromovyna, preporučenom na [njegovom kanalu](https://t.me/gromovyna/24) svima koji
žele razumjeti ovu šifru.

## Što je KeeLoq

KeeLoq je blokovna šifra temeljena na NLFSR-u (nelinearni posmačni registar s povratnom vezom), koju je dizajnirala tvrtka Nanoteq Pty Ltd. i
prodala tvrtki Microchip Technology Inc. Kriptira **32-bitne blokove** pomoću **64-bitnog ključa** u **528 rundi**.
Primjenjuje *code hopping* (promjenjivi kôd): svaki prijenos je jedinstveni paket.

### Struktura paketa

64-bitni KeeLoq paket, npr. `239B3DEBF16C47A6`, sastoji se od:

- **Fix** (prva 4 bajta, `239B3DEB`) — šalje se nekriptirano: ID tipke (`2`) i 28-bitni serijski broj
  daljinskog upravljača (`39B3DEB`).
- **Hop** (zadnja 4 bajta, `F16C47A6`) — kriptirano proizvođačkim ključem. Dekriptirano izgleda ovako: `21EB000A`:
  ponovno ID tipke (`2`), 12 bitova diskriminacijskih podataka (često `serial & 0x3FF`) i **16-bitni brojač**
  (`000A`).

![Struktura KeeLoq paketa](/img/remote/167cc7293a53adb1.png)

To je ono što Flipper prikazuje nakon radnje [Read](/hr/subghz/read): `Fix`, `Hop`, `Btn`, `Cnt` i naziv proizvođača.

### Logika brojača

- Brojač jednak vrijednosti koju prijamnik očekuje → naredba se izvršava.
- Brojač je **veći** od pohranjene vrijednosti → prijamnik se ponovno sinkronizira na njega i od sljedećeg pritiska radi normalno.
- Brojač je **manji** → zanemaruje se; neki prijamnici odparuju daljinski upravljač nakon nekoliko "zastarjelih" vrijednosti. *To je stvarna
  opasnost pri eksperimentiranju s KeeLoqom.* Pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes).

## Načini učenja (izvođenje ključa)

Ključ koji stvarno kriptira hop dio izvodi se iz **proizvođačkog ključa** (64-bitni, jednak za sve daljinske upravljače
određene marke/serije modela). Standard definira tri načina:

| Način | Kako se stvara ključ po daljinskom upravljaču |
|---|---|
| **Simple learning** | proizvođački ključ koristi se izravno takav kakav jest (najslabiji) |
| **Normal learning** | proizvođački ključ miješa se sa serijskim brojem daljinskog upravljača |
| **Secure learning** | koristi dodatnu vrijednost — **seed** — jedinstvenu za svaki daljinski upravljač i poslanu samo pri uparivanju (najjači standardni način) |

Proizvođači također izmišljaju vlastite načine, npr. **Magic XOR Type-1** (Beninca: serijski broj XOR proizvođački ključ) ili
**FAAC SLH (SPA)** — niz bitovnih operacija i kriptiranja, po mišljenju li0arda najpromišljeniji među njima.

::: tip Unleashed
Unleashed implementira sve standardne načine i mnoge proizvođačke (`lib/subghz/protocols/keeloq_common.h`):
Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3, KingGates, Jarolift, Erreka, Pujol,
AERF, JCM, JCM Gen2, Stagnoli te Telcoma učenje temeljeno na tablici. Više od 100 proizvođača navedeno je u
[Podržani sustavi](/hr/subghz/supported-systems).
:::

## Proizvođački ključevi u Unleashed firmveru

Za dekodiranje KeeLoq signala Flipper mora poznavati proizvođački ključ. Unleashed ih isporučuje u
**kriptiranoj** bazi ključeva (keystore) na SD kartici:

| Datoteka | Namjena |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | ugrađeni ključevi, kriptirani (`Encryption: 1`), ažuriraju se s firmverom |
| `/ext/subghz/assets/keeloq_mfcodes_user` | **vaši vlastiti** ključevi, čisti tekst (stvorite je iz `keeloq_mfcodes_user.example`) |

Kada se signal dekodira, isprobava se svaki ključ; pri uspjehu naziv se prikazuje kao `KL: DoorHan`, `KL: Nice_Smilo` itd.
Daljinski upravljači za half-rate KeeLoq također prikazuju stvarni naziv proizvođača (umjesto `Crypt Key`), uz oznaku `KL HR` na popisu očitanih signala i `66b HR` u podacima o signalu. Ako nijedan ključ ne odgovara, signal se prikazuje kao **`KL: Unknown`**: može se spremiti, ali se ne može slati niti koristiti
za generiranje sljedećeg kôda. CLI naredbe `subghz` koje dekodiraju signale pri pokretanju ispisuju `Load_keystore keeloq_mfcodes OK` i
`Load_keystore keeloq_mfcodes_user OK` / `Absent` — brz način za provjeru učitavaju li se baze ključeva.

### Format datoteke korisničkih ključeva

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - proizvođački ključ, 64 bita
# X - vrsta učenja: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - prolazi kroz oba prethodna i proizvođački ključ u izravnom i obrnutom redoslijedu bajtova
# NAME - naziv (bez razmaka), maks. 64 znaka
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Ostavite prazan redak na kraju datoteke. Datoteka `_user` ne prepisuje se pri ažuriranjima.

### Polja `Manufacture` i `Seed`

Spremljena KeeLoq `.sub` datoteka pohranjuje proizvođača po nazivu:

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

Sustavi sa sigurnim učenjem (secure learning) također pohranjuju `Seed: XX XX XX XX`. Ručno dodavanje redaka `Seed` + `Manufacture` u datoteku koja se
očitava kao `KL: Unknown` omogućuje njezino dekodiranje (pogledajte BFT/Erreka dolje).

## Seed vrijednosti: BFT Mitto, Erreka, FAAC SLH, Genius

Ovi sustavi koriste **seed** jedinstven po daljinskom upravljaču (ili po instalaciji); bez njega se signal očitava kao `KL: Unknown` (ili
se ne dekodira) i nije moguće stvoriti prihvaćeni daljinski upravljač.

- **BFT Mitto** — noviji daljinski upravljači izvode seed iz serijskog broja i odmah se dekodiraju u Read (`KL: BFT`).
  Stariji imaju jedinstveni seed. Stavite izvornik u način programiranja (rupica za iglu na poleđini ili tipke 1+2): on
  šalje paket čiji `Fix` počinje sa slovom `F`; **`Hop` tog paketa jest seed** u nekriptiranom obliku.
- **Erreka IRIS** — kratko spojite pinove `1` i `5` 5-pinskog konektora sa strane: ponovno `Fix` počinje s `F`, a
  `Hop` je seed. Neke instalacije **svakom** daljinskom upravljaču daju isti seed — tada ga novi daljinski upravljač mora ponovno upotrijebiti.
- **FAAC SLH / Genius** — očitajte seed s **glavnog (master)** daljinskog upravljača u načinu programiranja; seed se razlikuje **po
  tipki**.
- Nemate gumb za programiranje? Koristite aplikaciju **[Seed Capturer](/hr/subghz/seed-capturer)**: ona prikuplja uzastopne
  parove Fix/Hop, a seed se zatim izvlači u pratećoj aplikaciji qUnleashed.

Sa seed vrijednošću stvorite daljinski upravljač u `Sub-GHz → Add Manually [Advanced]` (SERIAL → BUTTON → COUNTER → SEED), pogledajte
[Ručno dodavanje](/hr/subghz/add-manually) i [programiranje daljinskog upravljača](/hr/subghz/remote-prog).

## Poznati napadi (pregled)

Iz li0ardova članka, radi razumijevanja — ne kao upute.

**Teorijski:** slide napad (~2³² parova otvorenog teksta / šifriranog teksta, daje prva 32 bita ključa), korelacijski
pristup (iskorištava pristranost od 5/8 kod NLFSR-a), linearni korak (zadnjih 16 bitova ključa kada su ostali poznati). Ukupna
složenost ≈ 2⁵².

**Praktični** (zahvaljujući materijalima Dereka Jamisona, "SubGHz Rolling Flaws"):

| Napad | Zamisao |
|---|---|
| Replay | ponovno slanje uhvaćenog paketa; radi na statičkim kodovima i na prijamnicima koji ne provjeravaju brojač |
| Kloniranje daljinskog upravljača | s proizvođačkim ključem može se izraditi radna kopija — ali dolazi u sukob s brojačem izvornika i može ga odpariti |
| Future | slanje brojača daleko unaprijed (`0001` → `3E91`); prijamnik se ponovno sinkronizira, a izvornik gubi sinkronizaciju |
| Rollback | vraćanje brojača unatrag nakon nekoliko korištenja; rijetki prijamnici ponovno se sinkroniziraju na stare vrijednosti |
| RollJam | snimanje uz istodobno ometanje prijamnika, korištenje kasnije. **Ometanje (jamming) je nezakonito** u gotovo svim zemljama |
| Manufacturer-key (KGB) | prijamnik može prihvaćati nekoliko proizvođačkih ključeva; slanje izvornog fix dijela s brojačem kriptiranim drugim ključem |
| Enc00 | zamjena fix dijela fix dijelom drugog uparenog daljinskog upravljača uz korištenje izvornog hop dijela; drugi daljinski upravljač gubi sinkronizaciju |
| Unknown | kada prijamnik ne može dekodirati hop, koristi 0; univerzalni prijamnici mogu otvoriti na 0 |

Unatoč svemu tome, KeeLoq — kao i Mifare Classic sa svojim probijenim Crypto-1 — ostaje popularan u jeftinim sustavima
kontrole pristupa; neki su proizvođači (Beninca, Hormann) prešli na AES.

::: warning
Eksperimentirajte samo s vlastitim daljinskim upravljačima i prijamnicima. Daljinski upravljač koji je izgubio sinkronizaciju ili je odparen možda će trebati ponovno registrirati na
prijamniku.
:::

## Rješavanje problema

- **`KL: Unknown`** — nema odgovarajućeg ključa. Provjerite modulaciju, ažurirajte firmver (novi ključevi) ili dodajte ključ u
  `keeloq_mfcodes_user` ako ga zakonito posjedujete. Za sustave sa seedom, pronađite seed.
- **Dekodira se, ali prijamnik ignorira Flipper** — šaljete klon; pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes)
  i [Načini brojača](/hr/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** u Add Manually — nedostaje baza ključeva; ponovno instalirajte
  firmver s umetnutom SD karticom.

## Povezano

- [Podržani sustavi](/hr/subghz/supported-systems) · [Ručno dodavanje](/hr/subghz/add-manually)
- [Seed Capturer](/hr/subghz/seed-capturer) · [Programiranje daljinskog upravljača](/hr/subghz/remote-prog)
- [Načini brojača](/hr/subghz/counter-mode) · [Format .sub datoteka](/hr/subghz/file-format)
