---
title: Aplikacija Nice O-Code
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Aplikacija Nice O-Code

**Nice O-Code** (autor @xMasterX) pronalazi 16-bitni **instalacijski kôd (IC)** daljinskog upravljača Nice O-Code i sprema daljinski upravljač kao `.sub` datoteku — bilo kao običan klon, bilo kao **novi daljinski upravljač** iste instalacije koji možete registrirati u prijamniku.

## Pozadina

Nice O-Code zapravo je Nice FloR-S zaštićen instalacijskim kodom — jednom vrijednošću koju dijele svi daljinski upravljači jedne instalacije. Prijamnik prihvaća samo daljinski upravljač koji nosi njegov instalacijski kôd. Jedan snimljeni pritisak nije dovoljan da bi se kôd pronašao, ali **četiri ili više pritisaka** istog daljinskog upravljača jesu: samo ispravan kôd dekodira svaki pritisak na isti serijski broj. Aplikacija prikuplja pritiske i na samom Flipperu grubom silom isprobava svih 65 536 kodova.

Neki O-Code daljinski upravljači nose i **certifikat** prijamnika (dulji 112-bitni okvir signala koji se šalje samo tijekom prvih dvadeset korištenja daljinskog upravljača). Kada ga aplikacija uoči, skida masku čim je IC poznat i prikazuje ga kao `Cert`.

::: tip Unleashed
Nice O-Code ugrađena je sistemska aplikacija firmvera Unleashed, a aplikacija Sub-GHz može dekodirati i slati O-Code daljinske upravljače čim datoteka sadrži IC. `Add Manually` ima odgovarajuće stavke `Nice O-Code`, `Nice O-Code One` i `Nice O-Code+Crt` — pogledajte [Ručno dodavanje](/hr/subghz/add-manually) i [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).
:::

::: warning
Koristite samo na vlastitoj instalaciji. Klon dijeli brojač s izvornim daljinskim upravljačem pa će se međusobno ometati (pogledajte [Plivajući kodovi](/hr/subghz/rolling-codes)).
:::

## Preduvjeti

- Datoteka ključeva za Nice FloR-S `/ext/subghz/assets/nice_flor_s` na SD kartici (dolazi uz firmver). Bez nje aplikacija javlja `No rainbow table`.
- Ispravan O-Code daljinski upravljač dotične instalacije. Aplikacija sluša na **433,92 MHz AM650**, pomoću unutarnjeg ili [vanjskog](/hr/subghz/external-cc1101) radija (`Int` / `Ext` u zaglavlju).

## Snimanje daljinskog upravljača

1. Otvorite `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Odaberite `Capture remote`. Status prikazuje `Listening 433.92`.
3. Pritisnite tipku daljinskog upravljača **4 ili više puta — kratkim pritiscima, nemojte je držati pritisnutom**. Svaki novi pritisak prikazuje `Press N: …`; redak `Presses n/4  Xpkt` i traka napretka postupno se pune. Ako daljinski upravljač ima certifikat, redak završava s `+Crt`.
4. Kada se prikupe 4 pritiska, pojavljuje se `Solve` — pritisnite <kbd>OK</kbd>.
5. Zaslon prikazuje `Trying installer codes` s brojačem do 65536. <kbd>←</kbd> (`Cancel`) zaustavlja postupak.
6. Nakon uspjeha prikazuju se `IC XXXX`, `Serial XXXXXXX` i, ako je prisutan, `Cert XXXXXX`.

Statusi koje možete vidjeti tijekom snimanja:

| Status | Značenje |
|---|---|
| `Not O-Code, ignored` | okvir signala koji nije O-Code (npr. obični FloR-S daljinski upravljač) |
| `Same press, ignored` | ponavljanje već spremljenog pritiska |
| `Need 4+ packets` | nedovoljno pritisaka za izračun |
| `Ambiguous, capture more` | odgovara više kodova — pritisnite daljinski upravljač još nekoliko puta i ponovite izračun |
| `No code fits, not O-Code?` | nijedan instalacijski kôd ne odgovara — vjerojatno nije O-Code daljinski upravljač ili su pomiješani pritisci različitih daljinskih upravljača |

## Spremanje

Na zaslonu s rezultatom:

- <kbd>OK</kbd> (`Save`) — **klon** snimljenog daljinskog upravljača (zadani naziv `NiceO`). Korisno za testiranje, ali se s izvornim daljinskim upravljačem nadmeće oko brojača.
- <kbd>→</kbd> (`New`) — **novi daljinski upravljač**: isti instalacijski kôd, tipka i certifikat, ali vlastiti serijski broj i brojač (zadani naziv `NiceO_new`). Upravo ovaj treba registrirati u prijamniku. Brojač je postavljen blizu, i malo ispod, brojača vašeg postojećeg daljinskog upravljača.

Obje se datoteke spremaju u `/ext/subghz/` nakon što im date naziv (`Name the .sub file`). Otvorite ih u `Sub-GHz → Saved`.

Za registraciju novog daljinskog upravljača slijedite postupak za Nice FloR-S na stranici [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog). Daljinski upravljač s certifikatom upisuje se sam: pritisnite njegovu tipku otprilike jednom u sekundi, **10–15 puta zaredom** — vrata se otvaraju oko desetog pritiska.

## Dekodiranje RAW datoteke

`Decode RAW file` pokreće isti postupak pronalaska koda nad RAW `.sub` datotekom koju ste ranije snimili pomoću [Read RAW](/hr/subghz/read-raw) (snimite 4+ odvojena pritiska). Datoteka ključa odbija se porukom `Not a RAW capture`. Traka napretka prikazuje dokle je obrada datoteke stigla.

## Rješavanje problema

- **`No rainbow table`** — nedostaje `/ext/subghz/assets/nice_flor_s`; ponovno instalirajte firmver s umetnutom SD karticom ili vratite mapu `assets`.
- **Pritisci se ne broje** — napravite odvojene kratke pritiske; držanje tipke ponavlja isti pritisak.
- **Tvornički prazan prijamnik ignorira O-Code daljinski upravljač** — nekorišten prijamnik nema instalacijski kôd; umjesto toga registrirajte obični daljinski upravljač `Nice One` / `Nice FloR-S` tipkom na prijamniku (pogledajte [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog)).
- **Prijamnik odbija novi daljinski upravljač** — držite brojač blizu brojača vašeg ispravnog daljinskog upravljača; nemojte ga vraćati na nulu.

## Povezane stranice

- [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog) · [Ručno dodavanje](/hr/subghz/add-manually)
- [Plivajući kodovi](/hr/subghz/rolling-codes) · [Podržani sustavi](/hr/subghz/supported-systems)
