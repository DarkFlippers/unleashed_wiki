---
title: Učenje i slanje signala
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Učenje i slanje IR signala

Flipper Zero može kopirati tipke IR daljinskog upravljača jednu po jednu i spremiti ih kao **virtualni daljinski upravljač**: datoteku `.ir` u mapi `/ext/infrared/`. Koristite ga kada je izvorni daljinski upravljač izgubljen, pokvaren ili u drugoj prostoriji, ili kada univerzalni daljinski upravljač ne pronalazi vaš uređaj.

Signali [poznatih protokola](/hr/infrared/protocols) dekodiraju se i spremaju u kompaktnom *raščlanjenom* obliku (protokol + adresa + naredba). Sve ostalo sprema se kao **RAW** vremenski intervali, što također radi za reprodukciju.

## Učenje novog daljinskog upravljača

1. Idite na `Main Menu → Infrared → Learn New Remote`.
2. Na zaslonu piše **"Point the remote at IR port and push the button"**. Držite daljinski upravljač nekoliko centimetara od gornjeg ruba Flippera, u izravnoj vidnoj liniji IR prozorčića.

   ![Learn New Remote čeka signal: "Point the remote at IR port and push the button"](/screens/infrared/learn.png)

3. Pritisnite tipku na daljinskom upravljaču **kratko**. Nemojte je držati: držanje tipke daje dugo snimanje puno ponavljanja.
4. Pojavljuje se zaslon snimanja:
   - dekodirani signal prikazuje naziv protokola i adresu/naredbu, npr. `NECext`, `A: 0x87EE`, `C: 0xA05D`;
   - nepoznati signal prikazuje **Unknown** i broj uzoraka, npr. `150 samples`.

   ![Zaslon snimanja: dekodirani protokol NEC s adresom i naredbom te Retry, Send i Save na dnu](/screens/infrared/learn_success.png)

5. Odaberite što želite učiniti:
   - <kbd>OK</kbd> **Send**: ponovno šalje snimljeni signal dok držite tipku, kako biste ga odmah isprobali;
   - <kbd>←</kbd> **Retry**: pita *"Retry Reading? All unsaved data will be lost!"*, zatim <kbd>←</kbd> Exit odbacuje snimku i ponovno sluša, a <kbd>→</kbd> Stay vraća natrag;
   - <kbd>→</kbd> **Save**: nastavak na imenovanje.
6. Unesite naziv tipke pod **"Name the button"** (najviše 23 znaka) i potvrdite. Zadani naziv stvara se iz signala: prva 4 slova protokola i naredba (npr. `NECe_A05D`), ili `RAW_<samples>` za RAW.
7. Prikazuje se **"Success!"** i otvara se novi daljinski upravljač. Prvi se sprema kao `/ext/infrared/Remote.ir`; ako je taj naziv zauzet, koriste se `Remote1.ir`, `Remote2.ir` i tako redom.

![Snimljeni signal na zaslonu](/img/remote/a62fc8f9d738534b.png)

::: tip Preimenujte daljinski upravljač
Novi daljinski upravljač uvijek se zove `Remote`. Odmah ga preimenujte putem `Edit → Rename Remote` (pogledajte ispod), inače ćete završiti s nazivima `Remote`, `Remote1`, `Remote2`…
:::

### Dodavanje više tipki

Na popisu tipki daljinskog upravljača pomaknite se na dno i odaberite **`+`**. Ponovno se otvara zaslon za učenje. Snimite signal, odaberite **Save**, imenujte tipku i dobit ćete **"Saved"**: tipka je dodana u istu datoteku.

Pritiskom tipke <kbd>Back</kbd> na zaslonu snimanja postavlja se pitanje *"Exit to Infrared Menu?"* (ili *"Exit to Remote Menu?"* pri dodavanju u postojeći daljinski upravljač): nespremljeni podaci gube se ako odaberete Exit.

## Slanje spremljene tipke {#send-a-saved-button}

1. Idite na `Main Menu → Infrared → Saved Remotes` i odaberite datoteku `.ir`.
2. Usmjerite gornji rub Flippera prema uređaju.
3. Odaberite tipku pomoću <kbd>↑</kbd> / <kbd>↓</kbd> i pritisnite <kbd>OK</kbd>.

Signal se šalje **sve dok držite** <kbd>OK</kbd>: jedan pritisak za pojedinačnu naredbu, a držanje za radnje „pritisni i drži” poput pojačavanja glasnoće. LED dioda treperi tijekom odašiljanja.

![Slanje spremljenog signala](/img/remote/d20ed673954c3711.png)

::: tip Favoriti i Archive
Spremljeni daljinski upravljači pojavljuju se i u aplikaciji **Archive** (`Main Menu → Archive → Infrared`) te se ondje mogu dodati u favorite. U aplikaciji Flipper Mobile App nalaze se pod **Archive → Infrared**, pogledajte [Daljinski upravljači u mobilnoj aplikaciji](/hr/infrared/mobile).
:::

## Uređivanje daljinskog upravljača

Otvorite daljinski upravljač i odaberite **Edit** na samom dnu popisa tipki. Izbornik Edit sadrži:

| Stavka | Što radi |
|---|---|
| **Add Button** | Uči još jednu tipku (isto kao `+`). |
| **Rename Button** | Odaberite tipku i unesite novi naziv. |
| **Move Button** | Zaslon *"Select a Button to Move"*: odaberite tipku, pritisnite <kbd>OK</kbd> za podizanje (pomiče se udesno), pomaknite je pomoću <kbd>↑</kbd> / <kbd>↓</kbd> i ponovno pritisnite <kbd>OK</kbd> da biste je spustili. |
| **Delete Button** | Odaberite tipku. Potvrda *"Delete Button?"* prikazuje njezin naziv i protokol / adresu / naredbu (ili `RAW`, broj uzoraka). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Preimenuje daljinski upravljač i datoteku. Ako naziv već postoji, dodaje se broj. |
| **Delete Remote** | Potvrda *"Delete Remote?"* s brojem tipki. Briše datoteku `.ir`. |

Nazivi su ograničeni na **23 znaka** i za tipke i za daljinske upravljače. Veća uređivanja (spajanje datoteka, brisanje većeg broja tipki) lakša su na računalu: preuzmite datoteku pomoću [qFlippera](/hr/mobile/qflipper) i uredite je kao tekst, pogledajte [format IR datoteke](/hr/infrared/file-format).

::: warning Datoteke biblioteke nisu daljinski upravljači
Ako pokušate otvoriti datoteku iz `/ext/infrared/assets/` putem Saved Remotes, dobit ćete poruku *"Library file … can't be opened as a remote"*. Datoteke biblioteke (`Filetype: IR library file`) koriste isključivo [univerzalni daljinski upravljači](/hr/infrared/universal-remotes).
:::

## Dodatne mogućnosti u načinu Debug {#debug-mode-extras}

Kada je uključeno `Settings → System → Debug` (ON), izbornik Infrared prikazuje još dvije stavke:

- **Learn New Remote RAW**: isti postupak kao Learn, ali je dekoder isključen i svaki se signal sprema kao RAW. Korisno kada dekoder prepozna protokol, ali dekodirana reprodukcija ne radi na vašem uređaju.
- **Debug RX**: zaslon *"INFRARED monitor"* koji u stvarnom vremenu prikazuje što prijamnik prima.

## Rješavanje problema

| Problem | Što pokušati |
|---|---|
| Ništa se ne događa pri pritisku tipke na daljinskom upravljaču | Provjerite baterije daljinskog upravljača (pogledajte njegovu LED diodu kroz kameru mobitela). Priđite bliže i usmjerite ravno prema gornjem rubu. Izbjegavajte izravno sunce te obližnje fluorescentne i LED žarulje. |
| Signal se snima kao **Unknown / RAW** iako je daljinski upravljač uobičajen | Smetnje mogu uzrokovati RAW zapis. Upotrijebite **Retry** nekoliko puta dok ne dobijete dekodirani signal. Ako se zaista radi o nepoznatom protokolu, RAW je sasvim u redu. |
| Ogromne RAW snimke (stotine uzoraka) | Držali ste tipku. Pritisnite kratko; oko 100 uzoraka uobičajeno je za jedan pritisak. Vrlo dugačke snimke reproduciraju se sporo. RAW signal može sadržavati najviše 1024 vremenska intervala. |
| Uređaj ne reagira na spremljenu tipku | Priđite bliže i usmjerite izravno u IR prozorčić uređaja. Pokušajte poslati nekoliko puta ili držati <kbd>OK</kbd> dulje. Za veće udaljenosti koristite [vanjski IR modul](/hr/infrared/external-ir). |
| Klima-uređaj reagira pogrešno | Daljinski upravljači za klima-uređaje pri svakom pritisku šalju cijelo stanje (način rada, temperaturu, ventilator). Snimite svako željeno stanje kao zasebnu tipku, pogledajte [Doprinos snimkama](/hr/infrared/captures#air-conditioners). |
| "Failed to load …" pri slanju | Datoteka `.ir` je oštećena ili je neispravno uređena ručno. Provjerite je prema [formatu datoteke](/hr/infrared/file-format). |

## Povezane stranice

- [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes)
- [Daljinski upravljači u mobilnoj aplikaciji](/hr/infrared/mobile)
- [Format IR datoteke](/hr/infrared/file-format)
- [Vanjski IR moduli](/hr/infrared/external-ir)
