---
title: Read RAW
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** snima demodulirani signal "onakav kakav jest", bez dekodiranja — poput diktafona. Snimka se može
reproducirati, spremiti, naknadno dekodirati ili urediti. Upotrijebite ga kada:

- **Read** ne prepoznaje daljinski upravljač (nepoznat protokol);
- želite snimiti signal radi analize ili prijave novog protokola razvojnim programerima;
- trebate točnu ponovnu reprodukciju statičkog signala čiji protokol Flipper ne poznaje.

Snimanje se i dalje obavlja na odabranoj **frekvenciji i modulaciji** — Flipper nije SDR. Pogrešna
modulacija daje snimku šuma.

::: warning Promjenjivi kodovi (rolling codes)
RAW reprodukcija daljinskog upravljača s promjenjivim kodom djeluje isto kao klon: pomiče brojač prijamnika i može desinkronizirati
vaš original. **Nikada to ne radite s ključem automobila** — ključ može završiti na crnoj listi. Pojedinosti: [Promjenjivi kodovi](/hr/subghz/rolling-codes).
:::

## Snimanje

1. Pronađite frekvenciju pomoću [Analizatora frekvencije](/hr/subghz/frequency-analyzer) ako je ne znate.
2. Otvorite `Main Menu → Sub-GHz → Read RAW`.
3. Pritisnite <kbd>←</kbd> **Config** i postavite `Frequency`, `Modulation` i `RSSI Threshold:` (pogledajte u nastavku).
   Pritisnite <kbd>Back</kbd> za povratak.

   ![Read RAW spreman za snimanje: prazan valni oblik, tipke Config i REC](/screens/subghz/read_raw.png)

4. Pritisnite <kbd>OK</kbd> **REC**. Valni oblik počinje kliziti, a RSSI je prikazan s desne strane.
5. Pritisnite tipku na daljinskom upravljaču (držite 1–2 s).

   ![Snimanje u Read RAW načinu: dva naleta signala na valnom obliku, brojač uzoraka i tipka Stop](/screens/subghz/read_raw_recording.png)

6. Pritisnite <kbd>OK</kbd> **Stop**.
7. Sada imate tri mogućnosti:
   - <kbd>←</kbd> **Erase** — odbacite snimku i počnite ispočetka;
   - <kbd>OK</kbd> **Send** — reproducirajte snimku (držite za ponavljanje);
   - <kbd>→</kbd> **Save** — unesite naziv (zadano `RAW_<date-time>`) i spremite u `/ext/subghz/`.

## Postavke u Read RAW načinu

Izbornik postavki u RAW načinu kraći je nego u načinu Read:

| Stavka | Vrijednosti | Značenje |
|---|---|---|
| `Frequency` | popis frekvencija | Frekvencija prijama |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + prilagođene | Predložak demodulacije |
| `Sound` | `OFF` / `ON` | Reproduciraj primljeni signal kroz zvučnik |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | Snima samo dok je signal iznad te razine. `-----` = snima sve |

::: tip Kada koristiti prag (threshold)
S postavljenim pragom datoteka sadrži samo nalete signala vašeg daljinskog upravljača, bez sekundi šuma između pritisaka — datoteke
su znatno manje i čišće. Za snimke koje šaljete razvojnim programerima ostavite vrijednost na `-----` (potpuna snimka).
:::

## Reprodukcija spremljene RAW datoteke {#playback}

1. `Main Menu → Sub-GHz → Saved` i odaberite RAW datoteku. Otvara se na zaslonu Read RAW.
2. <kbd>OK</kbd> **Send** — šalje cijelu snimku jednom; držite <kbd>OK</kbd> pritisnutim za ponavljanje (**Hold to repeat**).
3. <kbd>←</kbd> **New** — pokreće novo snimanje.
4. <kbd>→</kbd> **More**:
   - `Decode` — propušta snimku kroz sve dekodere Sub-GHz aplikacije; pronađeni signali mogu se spremiti kao obične datoteke
     ključeva;
   - `Edit` — otvara datoteku u aplikaciji [Sub-GHz RAW Edit](/hr/subghz/raw-editor) (prikazuje se samo ako je ta aplikacija instalirana
     u kompatibilnoj inačici); Sub-GHz se ponovno otvara kada izađete iz uređivača;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` i `More → Edit` dodaci su firmvera Unleashed. Pomoću `Edit` možete pronaći stvarni signal u šumovitoj
snimci, skratiti je, spojiti datoteke i dekodirati samo odabrani dio.
:::

Duge, guste RAW datoteke struje s microSD kartice tijekom slanja. Ako su uključeni vrlo kratki impulsi (ispod 10 µs), a
kartica je spora, prijenos se može zaustaviti prije kraja datoteke — koristite kvalitetnu karticu.

## Snimanje daljinskog upravljača za zahtjev za podršku protokola

Ovo je postupak koji razvojni programeri firmvera Unleashed traže kada želite podršku za novi protokol:

1. Pronađite frekvenciju pomoću analizatora. U načinu Read isprobajte `AM650`, `FM238`, `FM476`, `FM12K` — ako se ništa ne dekodira,
   nastavite.
2. U Read RAW postavite tu frekvenciju i **`RSSI Threshold: -----`**.
3. Napravite **po jedan RAW za svaku modulaciju**: `AM650`, `FM238`, `FM476`, `FM12K`.
4. Za svaku: pritisnite **REC**, zatim pritisnite jednu tipku daljinskog upravljača **5 puta držeći je 1–2 s**, pa **5 puta držeći je
   ~5 s**. Zaustavite i spremite.
5. Ako daljinski ima više tipki, snimite svaku tipku na isti način. Svaku datoteku nazovite prema tipki.
6. Kopirajte datoteke na računalo, zapakirajte ih u ZIP arhivu i otvorite issue u repozitoriju firmvera. Priložite kvalitetne fotografije daljinskog upravljača
   (po mogućnosti i unutrašnjosti), model i proizvođača.

## Rješavanje problema

- **Snimka je ravna crta / samo šum** — pogrešna frekvencija ili modulacija, ili je daljinski predaleko. Držite ga bliže.
- **Ogromne datoteke** — postavite `RSSI Threshold`.
- **Reprodukcija ne radi** — daljinski koristi promjenjivi kôd (prijamnik odbija stare brojače), modulacija je bila
  pogrešna ili snimka sadrži samo dio signala. Snimite dulje pritiske.
- **Prijenos staje na pola** — spora microSD kartica s dugom, gustom datotekom. Skratite datoteku pomoću
  [RAW Edit](/hr/subghz/raw-editor) ili upotrijebite bržu karticu.
- **`Edit` nedostaje u `More`** — aplikacija Sub-GHz RAW Edit nije instalirana ili je prestara.

## Povezano

- [Read](/hr/subghz/read) · [Sub-GHz RAW Edit](/hr/subghz/raw-editor) · [Remote Analyzer](/hr/subghz/remote-analyzer)
- [Formati datoteka (RAW, BinRAW)](/hr/subghz/file-format) · [Promjenjivi kodovi](/hr/subghz/rolling-codes)
