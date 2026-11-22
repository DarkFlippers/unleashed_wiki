---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (autor @MatthewKuKanich) pretvara Flipperov Bluetooth u beacon za praćenje. Flipper odašilje
isti BLE oglasni paket kao i oznaka (tag), a telefoni iz mreže za praćenje u blizini dojavljuju njegovu lokaciju, pa se
izgubljeni Flipper može pronaći u aplikaciji vlasnika oznake.

Podržane vrste oznaka: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag** i
**Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper dolazi ugrađen u firmver, a Unleashed također instalira malu kuku za pokretanje: ako je beacon bio
aktivan kada je Flipper isključen, **ponovno se automatski pokreće nakon ponovnog pokretanja uređaja**, bez otvaranja
aplikacije. Beacon nastavlja raditi u pozadini dok koristite druge aplikacije.
:::

::: warning
Koristite ovu funkciju samo s vlastitim oznakama i uređajima. Praćenje drugih osoba može biti nezakonito u vašoj državi.
:::

## Što vam je potrebno

Flipper treba **MAC adresu** i **payload** oznake (ili datoteku s ključevima). Možete ih dobiti na jedan od dva načina:

- **Kloniranje postojeće oznake** (najjednostavnije; lokacija se tada prikazuje u uobičajenoj aplikaciji vlasnika oznake).
- **Generiranje vlastitih ključeva** metodom OpenHaystack (nije potrebna fizička oznaka, samo za Apple mrežu; lokaciju
  pregledavate putem alata OpenHaystack ili alternativom bez Maca).

### Opcija A: kloniranje postojeće oznake

1. Uparite AirTag ili SmartTag sa svojim telefonom kao i obično.
2. Prebacite ga u način rada „izgubljeno”: držite ga podalje od telefona na koji je registriran oko 15 minuta.
3. Na Android telefonu instalirajte **nRF Connect** (iOS inačica ne prikazuje sirove podatke).
4. U aplikaciji nRF Connect postavite filtar na marku oznake (Apple ili Samsung), postavite RSSI na najnižu vrijednost
   i skenirajte.
5. Kada se oznaka pojavi kao uređaj „FindMy”, otvorite **Raw** / **View Raw** i zabilježite **payload** i **MAC
   adresu**. Podatke možete i izvesti kao `.txt` datoteku.
6. **Odmah izvadite bateriju iz oznake**, inače će rotirati svoj ključ i MAC adresu pa vaša kopija više neće raditi.

### Opcija B: ključevi OpenHaystack

1. Preuzmite `generate_keys.py` iz [repozitorija FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper)
   i pokrenite skriptu (zahtijeva `python3 -m pip install cryptography`).
2. Skripta vam daje **Private Key**, **Public Key**, **Payload**, **MAC Address** te `.keys` datoteku.
3. Sačuvajte Private Key: potreban vam je za primanje izvješća o lokaciji.
4. Lokacije pregledavajte u aplikaciji [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS stariji od
   14) ili bez Maca pomoću [macless-haystack](https://github.com/dchristl/macless-haystack) ili
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Postavljanje Flippera

1. Kopirajte izvezenu `.txt` datoteku iz aplikacije nRF Connect ili `.keys` datoteku u `/ext/apps_data/findmy/` na SD
   kartici (ili preskočite ovaj korak i unesite podatke ručno).
2. Otvorite `Apps → Bluetooth → FindMy Flipper` i pritisnite <kbd>→</kbd> (**Config**).
3. Odaberite **Register Tag**, a zatim vrstu oznake: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` ili
   `Google Find My`.
4. Odaberite način uvoza:
   - `nRF Connect (.txt)`: odaberite izvezenu datoteku;
   - `OpenHaystack (.keys)`: odaberite datoteku s ključem;
   - `Register Tag Manually`: upišite MAC adresu, a zatim payload.
5. Vratite se na glavni zaslon i pritisnite <kbd>OK</kbd>. Status se mijenja u `Broadcast Active`.

## Glavni zaslon

| Tipka | Radnja |
|---|---|
| <kbd>OK</kbd> | pokreni / zaustavi beacon (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | promjena intervala odašiljanja |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | izlaz iz aplikacije dok beacon nastavlja raditi u pozadini |
| <kbd>Back</kbd> | zatvaranje aplikacije |

## Izbornik Config

| Stavka | Vrijednosti | Napomene |
|---|---|---|
| Broadcast Interval | 1-10 s (Google: 1-2 s) | koliko se često odašilje beacon; Google zahtijeva najmanje svake 2 s |
| Transmit Power | 0-6 dBm | veća snaga = veći domet, veća potrošnja baterije |
| Register Tag | | vrsta oznake i uvoz (opisano iznad) |
| Show MAC | Yes / No | prikaz MAC adrese na glavnom zaslonu |

Aplikacija sprema svoje stanje u `/ext/apps_data/findmy/findmy_state.txt`; zahvaljujući tome beacon može nastaviti s
radom nakon ponovnog pokretanja.

## Praćenje

- **Klon AirTaga**: Flipper se prikazuje kao vaš AirTag u aplikaciji Find My.
- **Klon SmartTaga**: u aplikaciji SmartThings (SmartThings Find), na telefonu ili u pregledniku.
- **Ključevi OpenHaystack**: u aplikaciji OpenHaystack ili macless-haystack.

## Rješavanje problema

- **Lokacija se nikada ne ažurira**: ključ/MAC oznake rotirao se prije nego što ste izvadili bateriju; ponovno uhvatite podatke.
- **Beacon se zaustavlja nakon ponovnog pokretanja**: provjerite je li umetnuta SD kartica (datoteka stanja nalazi se na njoj) i je li beacon bio u stanju `Broadcast Active` prije isključivanja.
- **Baterija se brže prazni**: povećajte interval odašiljanja i smanjite snagu odašiljanja.

## Povezane stranice

- [Aplikacije uključene u Unleashed](/hr/apps/catalog)
- [Postavke](/hr/start/settings)
