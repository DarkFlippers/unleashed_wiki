---
title: Plivajući kodovi
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Plivajući kodovi

Sub-GHz daljinski upravljači dolaze u dvije vrste:

- **Statički (fiksni) kôd** — svaki pritisak šalje potpuno isti paket (Princeton, CAME 12/24 bit, Nice Flo,
  Marantec, Roger, Gate TX…). Kopija je istovjetna izvorniku; oba nastavljaju raditi zauvijek, bilo kojim redoslijedom.
  [Očitajte](/hr/subghz/read) ga i spremite.
- **Plivajući (dinamički) kôd** — svaki pritisak šalje novi paket izgrađen od **brojača** koji se povećava za jedan pri svakom
  pritisku (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+, Alutech AT-4N…). Brojač je obično
  šifriran, pa se sljedeći kôd može izračunati samo ako firmver poznaje ključ protokola.

::: tip Unleashed
Unleashed može dekodirati, spremiti **i slati** mnoge protokole s plivajućim kodom, izrađivati nove daljinske upravljače za njih pomoću
[Add Manually](/hr/subghz/add-manually), slati ostale gumbe daljinskog upravljača tipkama sa strelicama
([prilagođeni gumbi](#custom-buttons)) te podešavati kako se brojač povećava ([Counter Incr.](#counter-increment),
[Načini brojača](/hr/subghz/counter-mode)). Tvornički firmver dekodira većinu njih, ali ih ne želi odašiljati.
:::

## Kako prijamnik provjerava brojač

Prijamnik pohranjuje zadnji brojač koji je prihvatio **za svaki daljinski upravljač** (jedna vrijednost po daljinskom upravljaču, ne po gumbu):

- brojač **jednak očekivanom sljedećem / unutar prednjeg prozora** → prihvaćen, vrata se otvaraju;
- brojač **daleko ispred** → mnogi se prijamnici resinkroniziraju: prvi pritisak se pohrani, sljedeći uzastopni radi;
- brojač **iza** pohranjene vrijednosti → zanemaren. Neki prijamnici brišu daljinski upravljač iz memorije nakon ponovljenih "starih" kodova.

## Sukob brojača

*Zašto ne možete uhvatiti vlastiti daljinski upravljač s plivajućim kodom u Readu i koristiti ga s Flippera?*
(prilagođeno iz [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Zamislite:

1. Pritisnete izvorni daljinski upravljač — on šalje brojač `0002`.
2. Spremili ste taj signal na Flipper; kada ga pošaljete, Flipper šalje `0003`.
3. Prijamnik misli da ste ponovno pritisnuli izvorni upravljač i otvara.
4. No izvorni daljinski upravljač je još uvijek na `0002`; njegov sljedeći pritisak je `0003` — vrijednost koju je prijamnik već vidio,
   pa se **ne otvara**.

Ne paničarite — daljinski upravljač nije odjavljen. Pritisnite ga ponovno: `0004` prestiže Flipper i izvorni upravljač ponovno
radi. Ali takve "utrke" mogu razmaknuti brojače za 100+ pritisaka, a tada se izvorni upravljač više ne može vratiti
bez ponovnog uparivanja na prijamniku.

Rješenja:

- **Najbolje: izradite novi daljinski upravljač** na Flipperu (`Sub-GHz → Add Manually`) i registrirajte ga u prijamniku. On
  ima vlastiti serijski broj i brojač te se nikada ne sukobljava s izvornicima. Pogledajte [programiranje daljinskog upravljača](/hr/subghz/remote-prog).
- Odlučite koji ćete koristiti — Flipper **ili** izvorni upravljač — i koristite samo taj.
- Koristite oba, ali nikada ne dopustite da se brojači jako razdvoje (pritisnite nekoliko puta onaj koji zaostaje).
- Eksperimentalno: posebni [načini brojača](/hr/subghz/counter-mode) za neke prijamnike omogućuju suživot klona i izvornika.

::: danger Automobili
Ne klonirajte ključ automobila. Ponovno odašiljanje (čak i putem Read RAW) može desinkronizirati ključ ili ga staviti na crnu listu,
a ponovno uparivanje često zahtijeva servisne alate ovlaštenog servisa.
:::

## Prilagođeni gumbi {#custom-buttons}

Kada je podržana datoteka s plivajućim kodom (ili nekim statičkim protokolom) otvorena u `Emulate`:

- <kbd>OK</kbd> (`Send`) šalje gumb koji je snimljen / generiran;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> šalju **druge kodove gumba** istog daljinskog upravljača, s
  ispravno povećanim brojačem, dok ih držite. Izvorni kôd gumba prikazan je kao mala heksadekadska znamenka s desne strane
  zaslona dok se koristi strelica.

Koja strelica odgovara kojem gumbu ovisi o protokolu; skriveni/programski gumbi (npr. `0xF` na BFT Mitto,
`Prog` na Somfyju) također su dostupni na ovaj način — potpuna tablica nalazi se u
[programiranju daljinskog upravljača](/hr/subghz/remote-prog) (referenca skrivenih gumba).

Protokoli s prilagođenim gumbima u trenutačnom firmveru (broj = koliko dodatnih kodova strelice mogu poslati):

| Protokol | Dodatnih | Protokol | Dodatnih |
|---|---|---|---|
| KeeLoq (svi `KL:` proizvođači) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (programiranje) |
| Somfy Keytis | 1 (`Prog`) | | |

## Povećanje brojača {#counter-increment}

`Sub-GHz → Radio Settings → Counter Incr.` određuje za koliko se brojač povećava po odašiljanju: `+1` (zadano),
`+2`, `+3`. Kada je uključen **Debug način** (`Settings → System → Debug`), popis se proširuje na `+4`, `+5`, `+10`,
`+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50` — alati za razvoj protokola; nemojte ih koristiti na stvarnoj instalaciji.
Pogledajte [Postavke](/hr/subghz/settings).

## Programiranje novog daljinskog upravljača u prijamnik

Uobičajen način korištenja Flippera bez sukoba s vratima s plivajućim kodom:

1. Očitajte izvorni daljinski upravljač (`Sub-GHz → Read`) kako biste saznali protokol, frekvenciju i modulaciju.
2. `Sub-GHz → Add Manually` → vaš sustav → isti pojas → spremite.
3. Prebacite prijamnik u način učenja (gumb na pločici ili s ispravnog daljinskog upravljača — Flipper šalje
   skriveni gumb za "programiranje" jednom tipkom sa strelicom).
4. Otvorite novu datoteku i držite <kbd>OK</kbd>.

Postupci po proizvođačima: **[Korištenje Flippera kao novog daljinskog upravljača](/hr/subghz/remote-prog)**.

## Rješavanje problema

- **Radilo je jednom, pa prestalo** — koristite klon. Pritisnite nekoliko puta zaredom radi resinkronizacije ili umjesto toga izradite novi
  daljinski upravljač.
- **Izvorni daljinski upravljač prestao je raditi** — Flipper je otišao previše unaprijed. Pritisnite izvorni upravljač nekoliko puta; ako je razlika
  prevelika, ponovno ga registrirajte na prijamniku.
- **Strelice ne rade ništa** — protokol nema prilagođene gumbe ili je datoteka statička bez polja za gumb.
- **`KL: Unknown` nakon Read** — ključ proizvođača je nepoznat; ne može se slati. Pogledajte [KeeLoq](/hr/subghz/keeloq).

::: warning
Ove značajke koristite samo na vlastitoj opremi ili uz dopuštenje vlasnika.
:::

## Povezano

- [Add Manually](/hr/subghz/add-manually) · [Programiranje daljinskog upravljača](/hr/subghz/remote-prog)
- [KeeLoq](/hr/subghz/keeloq) · [Načini brojača](/hr/subghz/counter-mode)
- [Podržani sustavi](/hr/subghz/supported-systems)
