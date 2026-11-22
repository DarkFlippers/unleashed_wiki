---
title: Jedinični testovi
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Jedinični testovi

Jedinični testovi (unit tests) prosljeđuju poznate ulaze kodu značajki i provjeravaju jesu li rezultati ispravni. Ključni su za robustan
kod bez pogrešaka.

Firmver sadrži zasebnu aplikaciju, **`unit_tests`** (`applications/debug/unit_tests`), koja se izvodi **na
samom Flipperu** — stoga testovi koriste stvarni hardver i isključuju razlike među platformama.

Kada doprinosite firmveru, priložite jedinične testove uz nove značajke gdje god je moguće te pokrenite postojeće kako biste
bili sigurni da vaša promjena ne uvodi regresije.

## Pokretanje testova

1. **Izgradite firmver sa skupom testnih aplikacija:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` je obavezan
   `fbt_options.py` zadano koristi `DEBUG=1`, a debug slika više ne stane ispod flash područja radijskog stoga —
   pakiranje se zaustavlja uz `Firmware image overlaps C2 region and is not programmable!`. Od API-ja 88.23 debug slika je
   oko 7 KB prevelika za ovaj skup aplikacija (10 KB za zadani skup), pa skraćivanje testova neće pomoći.
   (`COMPACT=1` već je zadana vrijednost; naveden je radi podudarnosti s drugim naredbama.)

   Imajte na umu da `DEBUG=0` pri prevođenju izostavlja `furi_assert()`, pa se tvrdnje (assertions) u kodu koji se testira neće aktivirati.
   To ne utječe na `furi_check()` i minunit tvrdnje.
   :::

   Skup aplikacija `unit_tests` sadrži: `basic_services`, `updater_app`, `radio_device_cc1101_ext`, `unit_tests`,
   `infrared`, `archive`.

2. **Flashajte firmver uključujući resurse za SD karticu** (`build/latest/resources`) — npr. instalirajte generirani
   `.tgz` iz `dist/` pomoću qFlippera ili upotrijebite `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`.
   Testni resursi moraju završiti na SD kartici.
3. **Otvorite sesiju naredbenog retka ([CLI](/hr/dev/cli))** i pokrenite:

   ```
   unit_tests
   ```

**Očekivani rezultat:** skupovi testova izvode se jedan po jedan, a zatim slijedi izvještaj poput:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Ako vidite `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, resursi za SD karticu
nisu instalirani — ponovite 2. korak s resursima.

Za pokretanje **jednog** testa i preskakanje ostalih proslijedite njegov naziv:

```
unit_tests test_infrared
```

Ostali se skupovi preskaču (`Skipping …`); pogrešan naziv daje `No suite named …`. Nazivi testova odgovaraju ID-ovima aplikacija
(`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`, `test_lfrfid`, …) definiranima u
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Ovo je posebna inačica firmvera bez uobičajenih aplikacija. Kada završite, ponovno instalirajte normalnu inačicu.
:::

## Dodavanje jediničnih testova

### Ulazna točka

Svi testovi pokreću se iz „matične“ aplikacije `unit_tests`. Sami testni kod pakira se kao `PLUGIN` aplikacija u
podmapi mape `tests/` unutar `unit_tests` i referencira se u zajedničkoj datoteci `application.fam`. Kopirajte strukturu
postojećeg testa.

### Testni resursi

Nekim su testovima potrebni vanjski podaci („assets“). Oni se nalaze u
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
svaki u vlastitoj podmapi. Resursi mogu biti bilo koje vrste: običan tekst, Flipper Format (FFF), binarni itd.

### Primjer: infracrveni protokoli

Svaki infracrveni protokol ima skup jediničnih testova, pa ga dodajte kada dodajete novi protokol:

1. Stvorite `test_<your_protocol_name>.irtest` u
   [mapi resursa za infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Ispunite je testnim podacima (pogledajte u nastavku).
3. Dodajte kod testa u
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Izgradite i instalirajte firmver s resursima, zatim pokrenite testove i provjerite prolaze li.

#### Format testnih podataka

Svaki infrared test ima tri odjeljka:

| Odjeljak | Što radi |
|---|---|
| `decoder` | Uzima sirovi signal, ispisuje dekodirane poruke |
| `encoder` | Uzima dekodirane poruke, ispisuje sirovi signal |
| `encoder_decoder` | Kodira dekodirane poruke u sirovi signal, zatim ih ponovno dekodira |

Datoteke `.irtest` obične su [`.ir` datoteke](/hr/infrared/file-format) s nekoliko dodataka:

- ulazni signali dekodera zovu se `decoder_input_N` (N = redni broj testa), a očekivani izlaz `decoder_expected_N`;
- za testove enkodera ta su dva naziva zamijenjena;
- dekodirani podaci su **polje (array)**, jer se jedan sirovi signal može dekodirati u više poruka — jedna poruka je
  polje veličine 1.

Koristite postojeće `.irtest` datoteke kao primjere sintakse.

#### Snimanje sirovih signala

Otvorite CLI sesiju i pokrenite:

```
ir rx raw
```

Usmjerite daljinski upravljač prema Flipperu i pritisnite tipke. Sirovi podaci ispisuju se u formatu spremnom za upotrebu.

## Povezane stranice

- [Integracijsko testiranje](/hr/dev/testing)
- [Flipper Build Tool (fbt)](/hr/dev/fbt)
- [Sučelje naredbenog retka (CLI)](/hr/dev/cli)
