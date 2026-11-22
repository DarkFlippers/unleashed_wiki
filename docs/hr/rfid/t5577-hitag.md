---
title: T5577 i Hitag Micro (autor @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Pisanje Hitag Micro, UX pisanja i brisanje T5577

Na temelju članka autora @gromovyna *"Preview of the LF (RFID) features I prepared for Unleashed"* (lipanj 2026.), ažurirano prema tome kako funkcije izgledaju u trenutačnom firmveru.

![](/img/remote/2e30c69f7eded901.png)

## Uvod

Nakon duže stanke, @gromovyna se vratio istraživanju i proučio prazne privjeske **H5.5** koje prodaje *iKey*. S Icemanova Discorda već je bilo poznato da je H5.5 isti kineski klon **Hitag Micro**, na koji je iKey postavio vlastitu lozinku. Situacija s nazivima:

| Naziv | Što je to |
|---|---|
| **8265 / H5** | čip sa zadanom lozinkom |
| **H5.5** | isti čip s lozinkom **iKey** |
| **8210** | isti čip s lozinkom kineskog klonera **FURUI** |

Pronašao je lozinku iKey (drugog dana pokušaja), podijelio je sa zajednicom i [ažurirao Proxmark3 bilješke o magic karticama](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265). Zatim je implementirao funkcije za Flipper — kao pull requestove u **Unleashed**, nadajući se da će ih prenijeti i u OFW čim ponovno bude u aktivnom razvoju.

Lozinke koje firmver koristi za te tri varijante:

| Varijanta | Lozinka |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Podrška za Hitag Micro

Flipper sada može **pisati** klonove Hitag Micro — **8265/H5**, **H5.5** i **8210** — kao ključeve EM4100 (čip je konfiguriran da sam šalje EM4100 okvir, "transponder talks first").

Ograničenja trenutačne arhitekture:
- LF hardver Flippera tijekom pisanja samo **odašilje**, pa se uspjeh može provjeriti jedino **ponovnim čitanjem oznake**;
- mnogo je vremena uloženo u kalibraciju konstanti, ali pisanje ovih čipova i dalje zahtijeva **dobro pozicioniranje**.

### Zašto je pisanje postalo sporije

Dodavanje podrške pogoršalo je UX jer je logika pisanja sada petlja koja redom isprobava:

- **T5577**
- **EM4305**
- **Hitag Micro** — i ovdje tri varijante, po jednu za svaku poznatu tvorničku lozinku; te su operacije same po sebi sporije

Za Hitag Micro Flipper redom isprobava lozinku svake poznate varijante kako ne bi morao pitati korisnika — zapitkivanje bi uništilo jednu od glavnih ideja Flipper Zera, jednostavnost. Cijena je brzina pisanja. Pogrešnu lozinku čip jednostavno odbija i oznaka ostaje netaknuta; varijanta koja se ispravno pročita natrag jest ona koja je prisutna.

Korisniku je to izgledalo grozno — kao da se ništa ne događa — i nije bilo jasno kojim je protokolom oznaka zapisana. Otuda sljedeća funkcija.

## UX: čime pišemo / čime smo zapisali?

Tijekom pisanja zaslon sada prikazuje **koji se čip trenutačno isprobava**:

![Pisanje u tijeku](/img/remote/34b72cbd8417d74e.png)

Tehnički to nije protokol, već tržišni naziv varijante prazne oznake — ali shvaćate poantu. Nakon pisanja rezultat se prikazuje s istim pojedinostima:

![Rezultat pisanja](/img/remote/3ca59457a78dad5b.png)

::: tip U trenutačnom firmveru
- Čipovi koji se isprobavaju mogu se podesiti: `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210, H5.5 (svi ON) i **8268** (ID8268 / Hitag S magic čip, zadano OFF). Isključite ono što ne koristite kako biste ubrzali pisanje.
- Cilj 8268 piše samo EM4100 pri RF/64 i mora se ručno uključiti, jer bi na pravom Hitag S čipu prebrisao korisničke podatke.
- Format zaslona pri pisanju jest `[Protocol]`, naziv datoteke, `(čip)`; **Success!** prikazuje čip koji je prihvatio podatke. Pojedinosti: [Pisanje na prazne oznake](/hr/rfid/write).
:::

## Brisanje T5577 na tvorničko stanje

Funkcija koja je autoru @gromovyna dugo nedostajala na Flipperu: vraćanje T5577 u prazno stanje. Raniji pokušaj dodavanja u Unleashed bio je blokiran; kasnije su funkcije poput *clear T5577 password* spojene s istim arhitekturnim problemima, pa bi pravo rješenje moralo biti globalno.

Ponašanje (usklađeno s Proxmark3):

- prije pokretanja dobivate upozorenje da će **svi podaci biti izbrisani** te da oznaka **neće biti čitljiva putem Read** dok na nju ne zapišete nove podatke;
- brisanje **ne uklanja lozinku** — ako je oznaka zaštićena, prvo uklonite lozinku namjenskom funkcijom;
- prikazuje se traka napretka. Najviše vremena ne odlazi na samo brisanje, nego na **provjeru**: zbog LF API-ja Flipper provjerava je li oznaka čista pokušajem čitanja pri čemu očekuje da čitanje ne uspije;
- na kraju dobivate poruku o uspjehu ili neuspjehu.

![Upozorenje pri brisanju](/img/remote/f5ed0aa91bfcae98.png)

![Brisanje u tijeku](/img/remote/153b85d1fede96d9.png)

![Provjera](/img/remote/0f2f4e240a35940d.png)

![Uspjeh](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — gdje se sada nalazi
U članku je brisanje bilo u `125 kHz RFID → Extra Actions`. U trenutačnom firmveru ta funkcija (i Clear Password) premještena je u ugrađenu aplikaciju **T5577**: `Apps → RFID → T5577 → Wipe Tag`. Upozorenje glasi *Wipe T5577 — Erases all data. The tag stops working as a key. Hold still while running*; rezultat je **Wiped!** ili **Not wiped** (npr. *No answer. Protected? Try Clear Password*). Brisanje zapisuje nulirane blokove podataka i zadanu konfiguraciju, pa aplikacija T5577 i dalje može pročitati čip nakon toga. Pogledajte [Aplikacija T5577](/hr/rfid/t5577-app).
:::

## "Ovo si vibe-kodirao!"

Riječima autora, ovo je bio eksperiment može li se s pomoću LLM-a napisati kvalitetan kôd za takve sustave. Proces je bio temeljit: podatkovni listovi, kôd firmvera Unleashed za razumijevanje arhitekture, kôd alata Proxmark3. Svaki je korak provjeren, testiran na stvarnom hardveru i fino podešen. Tako su funkcije *napisane pomoću Claude Codea*, ali ih je *stvorio @gromovyna*.

## Pull requestovi

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

Više članaka i istraživanja: [@gromovyna](https://t.me/gromovyna).

## Povezano

- [Pisanje na prazne oznake](/hr/rfid/write) · [Aplikacija T5577](/hr/rfid/t5577-app) · [Protokoli](/hr/rfid/protocols)
