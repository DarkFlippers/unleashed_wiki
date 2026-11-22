---
title: Pisanje na prazne ključeve
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# Pisanje iButton ključeva na prazne ključeve

Originalni iButton ključevi imaju tvornički ID koji se ne može mijenjati. Za izradu kopije potreban vam je **prazan ključ (blank)** — ključ s mogućnošću ponovnog upisa čiji se ID može programirati. Flipper Zero ima dva načina pisanja:

- **Write ID** — zapisuje ID (ROM / kôd) na prazan ključ. Ovo je uobičajeno „napravi kopiju mog ključa od portafona“.
- **Full Write on Same Type** — samo za DS1992, DS1996 i DS1971: kopira sadržaj **memorije** na drugi originalni ključ iste vrste (DS1992 → DS1992). Ciljni ključ zadržava vlastiti ID.

## Podržani prazni ključevi

| Prazan ključ (kao u postavkama) | Zapisuje | Napomene |
|---|---|---|
| **RW1990.1** | ID-ove za DS1990, DS1420 | Prazni ključevi tipa RW1990; ova varijanta zapisuje bitove invertirano |
| **RW1990.2** | ID-ove za DS1990, DS1420 | Prazni ključevi tipa RW1990, neinvertirana varijanta |
| **TM2004** | ID-ove za DS1990, DS1420, DS1992, DS1996, DS1971 i generički 1-Wire | Prazni ključevi RW2004/TM2004; zapisuje se samo ID, iako prazan ključ ima memoriju |
| **TM01x** | ID za DS1990, **Cyfral**, **Metakom** | Prazni ključevi TM01/TM01x |

Prazni ključevi koji se prodaju kao RW1990, TM1990 ili TM08v2 obrađuju se varijantama RW1990; Flipper isprobava obje, pa ne morate znati koju točno imate.

::: tip Unleashed
- **Settings → Write Blanks** omogućuje uključivanje i isključivanje pojedinih vrsta praznih ključeva (svi su zadano uključeni — ON).
- Zaslon pisanja prikazuje koji se prazan ključ isprobava, a zaslon uspjeha ispisuje *Written to TM2004!* itd.
- **Cyfral i Metakom** mogu se zapisivati na prazne ključeve **TM01x**.
:::

::: warning TM01x za Cyfral / Metakom je jednosmjeran
Za Cyfral i Metakom prazan ključ TM01x se zapisuje, ponovno očitava i uspoređuje, a zatim **finalizira** u način rada Cyfral ili Metakom. Finalizacija se ne može poništiti: prazan ključ više se ne odaziva kao 1-Wire uređaj i ne može se ponovno zapisati — čak ni kao Dallas ključ. Ako provjera ne uspije, prazan ključ se ne finalizira i ostaje dostupan za pisanje. Dallas ID zapisan na TM01x ne finalizira se.

Metakom ključevi s neispravnom parnošću odbijaju se (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Otvorite ključ: `Saved` → ključ → **Write ID** (ili **More → Write ID** nakon čitanja).

   ![Izbornik spremljenog ključa s opcijama Emulate, Write ID, Edit i Rename](/screens/ibutton/saved_menu.png)

2. Zaslon prikazuje **Writing ID**, `[Protocol]`, naziv ključa (ili *Unsaved Key*) i u zagradama vrstu praznog ključa koja se isprobava — npr. `(RW1990.1)`.

   ![Zaslon Writing ID s protokolom [DS1990], nazivom ključa i praznim ključem koji se isprobava, (RW1990.1)](/screens/ibutton/write.png)

3. Prislonite prazan ključ na **ravni dio** kontakta (lijevi pin za podatke + srednja masa), baš kao pri čitanju. Držite mirno.
4. Flipper isprobava svaki omogućeni prazan ključ koji može nositi taj protokol i zatim ponovno očitava rezultat.
5. **Written to RW1990.2!** (ili *Successfully written!*) — gotovo.

## Full Write on Same Type

1. `Saved` → ključ DS1992 / DS1996 / DS1971 → **Full Write on Same Type**.
2. Zaslon prikazuje **Full Writing**. Prislonite originalni ključ **iste** vrste.
3. Memorija se zapisuje; ciljni ključ zadržava vlastiti ID. Ovaj način ne koristi postavku Write Blanks.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` navodi **RW1990.1**, **RW1990.2**, **TM2004**, **TM01x** sa stanjem **ON**/**OFF**. Prebacujte pomoću <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd>; postavka se sprema pri izlasku u `/ext/ibutton/.ibutton.settings`. CLI naredba `ikey write` koristi istu postavku.

Ako stranica javi *Settings page missing. Update the SD resources*, ponovno instalirajte firmver s umetnutom SD karticom.

## Pogreške

| Zaslon | Značenje |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | Sve vrste praznih ključeva su isključene (OFF) |
| **Cannot Write** — *No enabled blank can write this key* | Npr. omogućen je samo RW1990 za ključ Metakom |
| **Cannot Write** — *This key cannot be written* (ili razlog protokola) | Podaci ključa nisu valjani za pisanje |
| Zaslon pisanja ostaje otvoren, LED treperi | Prazan ključ još nije otkriven — provjerite kontakt ili ta vrsta praznog ključa nije podržana |

## Rješavanje problema

- **Kontakt.** Središte praznog ključa mora dodirivati pin za podatke, a njegov rub pin za masu.
- **Nepoznata vrsta praznog ključa.** Pokušajte uključiti sve vrste. Neki jeftini prazni ključevi pripadaju vrstama koje Flipper ne može programirati.
- **„Success“, ali čitač odbija kopiju.** Neki čitači filtriraju prazne ključeve (provjeravaju ponašanje praznog ključa za pisanje) — tu Flipper ne može ništa učiniti.
- **Potrošen TM01x.** TM01x finaliziran kao Cyfral/Metakom ne može se ponovno upotrijebiti.

## Povezano

- [Čitanje](/hr/ibutton/read) · [Protokoli](/hr/ibutton/protocols) · [Ručno dodavanje](/hr/ibutton/add-manually)
