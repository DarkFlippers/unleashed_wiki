---
title: Daljinski upravljači u mobilnoj aplikaciji
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# IR daljinski upravljači u mobilnoj aplikaciji Flipper

Flipper Mobile App (iOS / Android) ima **Remotes Library**: internetsku bazu podataka IR daljinskih upravljača. Odaberete vrstu
uređaja i marku, aplikacija pronalazi pravi daljinski upravljač testiranjem nekoliko signala, preuzima ga na Flipper i zatim
prikazuje prikladan raspored tipki na zaslonu telefona. Stvarno odašiljanje obavlja sam Flipper.

U usporedbi s [Univerzalnim daljinskim upravljačima](/hr/infrared/universal-remotes), koji pri svakom pritisku šalju cijelu biblioteku,
daljinski upravljač iz biblioteke Remotes Library pronalazi se **jednom** i nakon toga radi trenutačno. Također ima više tipki i
pokriva više vrsta uređaja.

## Što možete pronaći

Biblioteka uključuje daljinske upravljače za, među ostalim: televizore, projektore, TV prijamnike, ventilatore, pročišćivače zraka,
DVD reproduktore, kamere i AV prijamnike. Baza podataka je otvorenog kôda: [flipperdevices/IRDB](https://github.com/flipperdevices/IRDB);
svoj daljinski upravljač možete dodati prateći njihove
[upute za doprinos](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md).

::: tip Unleashed
Mobilna aplikacija radi s Unleashed firmverom jednako kao i s tvorničkim firmverom: komunicira s aplikacijom Infrared putem RPC-a.
Dok telefon upravlja njime, zaslon Flippera prikazuje **"Infrared – RPC mode"**. Daljinski upravljači preuzeti iz aplikacije
obične su `.ir` datoteke u `/ext/infrared/` i mogu se koristiti, uređivati i preimenovati na Flipperu kao svaki naučeni daljinski upravljač.
Više o samoj aplikaciji: [Flipper Mobile App](/hr/mobile/mobile-app).
:::

## Pronađite daljinski upravljač za svoj uređaj

1. Povežite Flipper s aplikacijom putem Bluetootha.
2. U aplikaciji idite na `Tools → Remotes Library`.
3. Odaberite **vrstu uređaja**, zatim **marku**.
4. Mnoge marke imaju više daljinskih upravljača, pa aplikacija testira signale jedan po jedan: usmjerite Flipper prema uređaju,
   dodirnite gumb za slanje signala i odgovorite je li uređaj reagirao.
5. Kada pronađete pravi daljinski upravljač, aplikacija prikazuje njegov raspored. Možete ga koristiti odmah.
6. Dodirnite **Save** (gore desno) i dajte daljinskom upravljaču naziv. Zapisat će se na Flipper.
7. *(Opcionalno)* Dodirnite **⋯ → Add to Favorites** kako bi vam bio na kartici Archive za brzi pristup.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Korištenje spremljenog daljinskog upravljača

**S telefona.** U aplikaciji otvorite `Archive → Infrared` (ili Favorites), odaberite daljinski upravljač, usmjerite Flipper
prema uređaju i dodirujte gumbe na telefonu. Aplikacija govori Flipperu koji signal treba poslati.

![Raspored daljinskog upravljača u aplikaciji](/img/remote/7387cb59433e202d.jpg)

**Samo s Flippera.** Idite na `Main Menu → Infrared → Saved Remotes`, otvorite daljinski upravljač, odaberite tipku pomoću
<kbd>↑</kbd> / <kbd>↓</kbd> i pritisnite <kbd>OK</kbd>. Pogledajte [Učenje i slanje signala](/hr/infrared/read#send-a-saved-button).

## Rješavanje problema

| Problem | Što pokušati |
|---|---|
| Aplikacija ne može slati / ništa se ne događa | Provjerite je li Flipper povezan i nije zauzet u drugoj aplikaciji. Zatvorite bilo koju pokrenutu aplikaciju na Flipperu i pokušajte ponovno. |
| Nije pronađen daljinski upravljač za vašu marku | Naučite izvorni daljinski upravljač na Flipperu ([kako](/hr/infrared/read)) ili isprobajte [Univerzalne daljinske upravljače](/hr/infrared/universal-remotes). |
| Uređaj reagira samo iz velike blizine | Koristite [vanjski IR modul](/hr/infrared/external-ir); aplikacija koristi odašiljač odabran u postavkama Infrared GPIO Settings. |

## Povezane stranice

- [Flipper Mobile App](/hr/mobile/mobile-app)
- [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes)
- [Format IR datoteka](/hr/infrared/file-format)
