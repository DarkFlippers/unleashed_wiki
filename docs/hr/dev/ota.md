---
title: OTA ažuriranja
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# Postupak OTA ažuriranja

Kako Flipper instalira paket za ažuriranje — što se događa u svakoj fazi, što sadrži manifest ažuriranja, što znače kodovi pogrešaka `[XX-YY]` i kako izraditi vlastite pakete.

Za korisničku stranu (instaliranje firmvera Unleashed putem qFlippera, web-instalatora ili sa SD kartice) pogledajte [Ažuriranje](/hr/start/updating). Ako ažuriranje ozbiljno ne uspije, pogledajte [Oporavak](/hr/start/recovery).

## Izvođenje koda iz RAM-a

Firmver ima poseban način pokretanja koji učitava posebno pripremljenu sliku sustava u **RAM** i skače na nju. Kôd koji se izvodi iz RAM-a ima puni pristup pisanju u cijelu flash memoriju — što je nemoguće dok se glavni firmver izvodi iz te iste flash memorije. Program za OTA ažuriranje koristi taj način rada, uključujući i za ažuriranje radijskog stoga na drugoj jezgri mikrokontrolera.

## Tri faze

### 1. Sigurnosno kopiranje unutarnje pohrane (`/int`)

`/int` je particija Flipperove flash memorije koja zauzima sav prostor koji ne koristi firmver. Novi firmver može biti drugačije veličine, pa bi njegova instalacija ponovno podijelila flash memoriju i obrisala podatke. Stoga se prije svega ostalog trenutačni sadržaj mape `/int` sprema kao sigurnosna kopija u običnu `.tar` arhivu na SD kartici.

### 2. Ažuriranje uređaja

Glavni firmver učitava **program za ažuriranje** (*updater*) — prilagođenu verziju firmvera — u RAM i pokreće ga. Program za ažuriranje radi na sistemskoj flash memoriji kako je opisano u manifestu ažuriranja:

1. Ako paket sadrži sliku **radijskog stoga**, njegova se verzija uspoređuje s instaliranom. Ako se razlikuju, stari se stog deinstalira, a novi zapisuje i instalira. Instalaciju obavlja ST-ov vlasnički **FUS** koji se izvodi na jezgri Core2 i uključuje nekoliko ponovnih pokretanja.
2. Provjeravaju se i ispravljaju **Option Bytes** (niskorazinska konfiguracija mikrokontrolera).
3. Učitava se `.dfu` datoteka firmvera, provjerava se njezina cjelovitost pomoću CRC32, zapisuje se u flash memoriju i provjerava.

### 3. Vraćanje unutarnje pohrane i ažuriranje resursa

Sustav se ponovno pokreće u novi firmver, vraća spremljeni sadržaj mape `/int` i — ako paket sadrži arhivu resursa — raspakirava je na SD karticu.

## Manifest ažuriranja

Svaki paket dolazi s manifestom (datoteka `.fuf`) u formatu Flipper File Format — običnoj tekstualnoj datoteci s parovima ključ-vrijednost.

### Obavezna polja (ovim redoslijedom)

| Ključ | Značenje |
|---|---|
| `Filetype` | Stalni niz `Flipper firmware upgrade configuration` |
| `Version` | Verzija manifesta, trenutačno `2` |
| `Info` | Slobodni opis paketa |
| `Target` | Revizija hardvera za koju je paket izrađen |
| `Loader` | Naziv datoteke učitavača 2. faze koji se izvodi iz RAM-a |
| `Loader CRC` | CRC32 datoteke učitavača, kao **little-endian** heksadekadska vrijednost |

### Neobavezna polja

Mogu biti prazna — program za ažuriranje tada preskače povezane radnje.

| Ključ | Značenje |
|---|---|
| `Radio` | Naziv datoteke slike radijskog stoga (isporučuje ST) |
| `Radio address` | Adresa za instalaciju radijskog stoga (iz ST-ovih bilješki o izdanju) |
| `Radio version` | Glavna, sporedna i podverzija, grana, izdanje i vrsta stoga zapakirani u 6 heksadekadskih bajtova |
| `Radio CRC` | CRC32 radijske slike |
| `Resources` | Naziv datoteke arhive s resursima za SD karticu — `resources.ths`, tar-arhiva sažeta algoritmom heatshrink (pogledajte [Format heatshrink tarball](/hr/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Referentne vrijednosti za provjeru i ispravljanje bajtova opcija (*option bytes*) |

## Kodovi pogrešaka

Postupak je osmišljen da bude što sigurniji od kvarova: nijedna rizična radnja ne započinje prije nego što se provjere svi povezani podaci, tako da uređaj ne ostane napola ažuriran ili neupotrebljiv. Ako nešto pođe po zlu, program za ažuriranje omogućuje ponovni pokušaj i prikazuje kôd pogreške `[XX-YY]`: `XX` je neuspjela radnja, a `YY` napredak ili pojedinost pri kojoj je došlo do pogreške.

| Faza | XX | YY | Značenje |
|---|--:|---|---|
| Učitavanje manifesta ažuriranja | **1** | **13** | Program za ažuriranje prijavio je neusklađenost verzije hardvera |
| | | **20** | Neuspjelo dohvaćanje spremljene putanje manifesta |
| | | **30** | Neuspjelo učitavanje manifesta |
| | | **40** | Nepodržana verzija paketa ažuriranja |
| | | **50** | Paket ima neodgovarajući ciljni hardver |
| | | **60** | Nedostaje DFU datoteka |
| | | **80** | Nedostaje datoteka radijskog firmvera |
| Sigurnosno kopiranje konfiguracije | **2** | **0-100** | Pogreška čitanja/pisanja datotečnog sustava |
| Provjera radijskog firmvera | **3** | **0-99** | Pogreška čitanja datoteke radijskog firmvera |
| | | **100** | Nepodudaranje CRC-a |
| Deinstalacija radijskog firmvera | **4** | **0** | Pogreška naredbe SHCI Delete |
| | | **80** | Pogreška pri čekanju statusa naredbe |
| Pisanje radijskog firmvera | **5** | **0-100** | Pogreška čitanja/pisanja bloka |
| Instalacija radijskog firmvera | **6** | **10** | Pogreška naredbe SHCI Install |
| | | **80** | Pogreška pri čekanju statusa naredbe |
| Core2 je zauzet | **7** | **10** | Nije moguće pokrenuti C2 |
| | | **20** | Neuspjelo prebacivanje C2 u način FUS |
| | | **30** | Pogreška u FUS operaciji |
| | | **50** | Neuspjelo prebacivanje C2 u način stoga |
| Provjera bajtova opcija (*option bytes*) | **8** | **yy** | Kôd bajta opcija |
| Provjera DFU datoteke | **9** | **0** | Pogreška otvaranja DFU datoteke |
| | | **1-98** | Pogreška čitanja DFU datoteke |
| | | **99-100** | Oštećena DFU datoteka |
| Pisanje flash memorije | **10** | **0-100** | Pogreška čitanja/pisanja bloka |
| Provjera flash memorije | **11** | **0-100** | Pogreška čitanja/pisanja bloka |
| Vraćanje konfiguracije | **12** | **0-100** | Pogreška čitanja/pisanja datotečnog sustava |
| Ažuriranje resursa | **13-15** | **0-100** | Pogreška čitanja/pisanja SD kartice |

::: tip Što učiniti u slučaju pogreške
- **1-50 / 1-13** — paket je za drugi ciljni hardver: preuzmite odgovarajući.
- **2, 12, 13-15** — problem sa SD karticom: provjerite / ponovno formatirajte karticu i ponovno kopirajte paket.
- **3-100, 9-99/100** — oštećene datoteke: ponovno preuzmite paket.
- Prvo pokušajte ponovno — program za ažuriranje je za to predviđen. Ako se Flipper uopće ne želi pokrenuti, koristite [Oporavak](/hr/start/recovery).
:::

## Izrada paketa za ažuriranje

Obavezno proslijedite `DEBUG=0` — pogledajte [Prevođenje firmvera](/hr/dev/build).

**Puni paket** — firmver, radijski stog i resursi za SD karticu:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Minimalni paket** — samo firmver:

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

Rezultat se nalazi u `dist/<target>-<cfg>/` kao mapa `f7-update-<suffix>` i datoteka `flipper-z-f7-update-<suffix>.tgz`.

### Odabir drugog radijskog stoga

Paketi prema zadanim postavkama koriste stog **Bluetooth Light**. Ako vaš firmver podržava drugi stog, proslijedite njegovu vrstu i binarnu datoteku:

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` mora pokazivati na datoteku u `scripts/` s referentnim podacima Option Byte koji odgovaraju toj vrsti stoga. U nekim slučajevima morate potvrditi i parametrom `COPRO_DISCLAIMER=...` u naredbenom retku.

### Djelomični paketi

Pozovite `scripts/update.py` izravno za prilagođeni sadržaj. Na primjer, paket koji instalira samo stog BLE FULL:

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

Pogledajte `scripts/update.py generate --help` za sve opcije.

## Instalacija paketa iz CLI-ja

Kopirajte raspakiranu mapu paketa na SD karticu i pokrenite:

```
update install /ext/update/f7-update-local/update.fuf
```

[CLI](/hr/dev/cli#update) također nudi naredbe `update backup` i `update restore` za unutarnju pohranu.

## Povezane stranice

- [Ažuriranje firmvera](/hr/start/updating)
- [Oporavak](/hr/start/recovery)
- [Format heatshrink tarball](/hr/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/hr/dev/fbt)
