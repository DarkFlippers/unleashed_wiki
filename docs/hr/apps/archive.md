---
title: Archive (preglednik datoteka)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (preglednik datoteka)

**Archive** je preglednik datoteka na Flipperu. Prikazuje spremljene ključeve, kartice, daljinske upravljače i skripte, omogućuje njihovo izravno pokretanje te osnovno upravljanje datotekama: prikvačivanje u favorite, preimenovanje, kopiranje, premještanje, stvaranje mapa i brisanje.

**Otvaranje:** na radnoj površini pritisnite <kbd>↓</kbd>.

![Archive na kartici Sub-GHz: mapa Garage i spremljeni .sub signali, s odabranim Barrier](/screens/apps/archive.png)

## Kartice

Pritisnite <kbd>←</kbd> / <kbd>→</kbd> za prebacivanje između kartica. Svaka kartica prikazuje jednu mapu, filtriranu prema vrsti datoteke:

| Kartica | Mapa | Prikazane datoteke |
|---|---|---|
| Favorites | vaše prikvačene datoteke | sve što ste prikvačili (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` (mape za [Sub-GHz Remote](/hr/subghz/remote)) |
| RFID LF | `/ext/lfrfid` | `.rfid` i T5577 ispisi |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` ([SIM800](/hr/gpio/sim800) imenik) |
| U2F | interna memorija | unos aplikacije U2F |
| Apps | `/ext/apps` | `.fap` i `.js` |
| Internal | interna flash memorija | sve (samo kad je uključen način Debug) |
| Browser | cijela SD kartica | sve |

Archive se otvara na kartici **Favorites**.

::: tip Unleashed
Unleashed dodaje karticu **SubRem** za mape aplikacije Sub-GHz Remote, karticu **Phone** za imenik SIM800 (unos `.phone` otvara se izravno u aplikaciji SIM800), prikazuje T5577 ispise uz ključeve u kartici **RFID LF** te navodi `.js` skripte u kartici **Apps**.
:::

## Tipke na popisu

| Tipka | Radnja |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | kretanje po popisu (držite za brže pomicanje) |
| <kbd>←</kbd> / <kbd>→</kbd> | prethodna / sljedeća kartica |
| <kbd>OK</kbd> na datoteci | otvaranje izbornika datoteke |
| <kbd>OK</kbd> na mapi | ulazak u mapu |
| držanje <kbd>OK</kbd> na mapi | otvaranje izbornika mape |
| <kbd>OK</kbd> u Favorites | trenutačno pokretanje datoteke |
| držanje <kbd>OK</kbd> u Favorites | otvaranje izbornika |
| držanje <kbd>OK</kbd> u praznoj mapi | otvaranje izbornika (Paste / NewDir) |
| <kbd>Back</kbd> | razinu više ili izlaz |

## Izbornik datoteke: Actions i Manage

Izbornik ima dvije stranice. Naslov prikazuje koja je otvorena: **Actions** ili **Manage**. Pritisnite <kbd>←</kbd> ili <kbd>→</kbd> unutar izbornika za prebacivanje između njih (nije dostupno na kartici Favorites). Tipkama <kbd>↑</kbd> / <kbd>↓</kbd> odabirete stavku, <kbd>OK</kbd> je pokreće, a <kbd>Back</kbd> zatvara izbornik.

**Actions** (datoteka koju firmver zna otvoriti):

- **Run**: otvaranje datoteke u pripadajućoj aplikaciji (emulacija ključa, slanje signala, pokretanje skripte…).
- **Pin** / **Unpin**: dodavanje u Favorites ili uklanjanje iz njih.
- **Info**: naziv i veličina datoteke.
- **Show**: prikaz datoteke kao teksta (za tekstualne formate).

Za nepoznatu vrstu datoteke Actions nudi samo **Info**, a za tekstualne datoteke i **Show**.

**Manage:**

- **Cut** / **Copy**, zatim **Paste** u odredišnoj mapi.
- **NewDir**: stvaranje mape.
- **Rename**: unos novog naziva.
- **Delete**: prvo traži potvrdu.

Na kartici **Favorites** izbornik sadrži **Run**, **Unpin**, **Show** (ako je primjenjivo) i **Move**. Move omogućuje promjenu redoslijeda favorita: pritisnite <kbd>↑</kbd> / <kbd>↓</kbd> za pomicanje stavke i <kbd>OK</kbd> za spremanje novog položaja (<kbd>Back</kbd> poništava).

## Uobičajeni zadaci

### Prikvačivanje datoteke u Favorites

1. Radna površina → <kbd>↓</kbd> za otvaranje aplikacije Archive.
2. Prijeđite na odgovarajuću karticu pomoću <kbd>←</kbd> / <kbd>→</kbd> i odaberite datoteku.
3. Pritisnite <kbd>OK</kbd> → **Pin**. Datoteka se sada pojavljuje na kartici Favorites.

### Preimenovanje spremljenog ključa ili signala

1. Odaberite datoteku i pritisnite <kbd>OK</kbd>.
2. Pritisnite <kbd>→</kbd> za prebacivanje izbornika na **Manage**.
3. Odaberite **Rename**, upišite naziv i potvrdite.

### Brisanje datoteka radi oslobađanja prostora

1. Odaberite datoteku, <kbd>OK</kbd>, <kbd>→</kbd> do **Manage**.
2. Odaberite **Delete** i potvrdite.

Za brisanje cijele mape upotrijebite karticu **Browser**: odaberite mapu, držite <kbd>OK</kbd>, **Manage → Delete**.

### Premještanje datoteke u drugu mapu

1. Odaberite datoteku, <kbd>OK</kbd>, **Manage → Cut**.
2. Otvorite odredišnu mapu (kartica **Browser** pristupa svakoj mapi na kartici).
3. Pritisnite <kbd>OK</kbd> na bilo kojoj datoteci (ili držite <kbd>OK</kbd> u praznoj mapi) → **Paste**.

## Rješavanje problema

- **"Empty"** znači da u mapi nema datoteka vrste za tu karticu. Provjerite datotečni nastavak: `.ir` datoteka u `/ext/nfc` neće se prikazati ni na jednoj od tih kartica, ali će biti vidljiva na kartici Browser.
- **Nedostaje kartica Internal**: vidljiva je samo kada je `Settings → System → Debug` uključeno (ON).
- **Nestao je favorit**: favoriti čija datoteka više ne postoji (premještena, preimenovana ili izbrisana izvan aplikacije Archive) uklanjaju se s popisa. Ponovno prikvačite datoteku na novoj lokaciji.
- **Delete** uvijek pita `Delete <name>?` uz gumbe **Cancel** / **Delete**, pa ništa nije moguće izbrisati jednim slučajnim pritiskom.

## Povezane stranice

- [microSD kartica](/hr/start/sd-card)
- [Aplikacije na SD kartici](/hr/apps/sd-card-apps)
- [Radna površina](/hr/start/desktop)
