---
title: Kontrole
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Kontrole

Flipper Zero ima 5-smjerni navigacijski gumb i zaseban gumb <kbd>BACK</kbd>.

| Gumb | Što radi |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Kretanje po izbornicima i virtualnim tipkovnicama. <kbd>←</kbd>/<kbd>→</kbd> mijenjaju vrijednost odabrane opcije |
| <kbd>OK</kbd> | Pokretanje aplikacije, potvrda odabira. Dugi pritisak često otvara dodatne radnje |
| <kbd>BACK</kbd> | Povratak natrag ili izlaz iz aplikacije. Dugi pritisak na radnoj površini otvara zaslon za isključivanje |

Na popisu strelice pomiču okvir oko odabrane stavke, a <kbd>OK</kbd> je otvara:

![Glavni izbornik s okvirom na Sub-GHz](/screens/mainmenu/subghz.png)

U ovim uputama "držati" ili "dugi pritisak" znači pritisnuti gumb otprilike jednu sekundu. Savjeti za gumbe na dnu
zaslona (na primjer `◀ Cancel` ili `Save ▶`) pokazuju što <kbd>←</kbd>, <kbd>OK</kbd> i <kbd>→</kbd> rade na tom zaslonu.

## Način za ljevake

**Main Menu → Settings → System → Hand Orient → `Lefty`**

Zaslon se okreće za 180°, a tipke se preslikavaju kako biste Flipper mogli držati u lijevoj ruci.

## Tipkovni prečaci

| Radnja | Kako |
|---|---|
| Uključivanje | Držite <kbd>BACK</kbd> oko 3 s |
| Isključivanje | Držite <kbd>BACK</kbd> na radnoj površini → **Power Off** (<kbd>→</kbd>) |
| Ponovno pokretanje (zamrznut uređaj) | Držite <kbd>←</kbd> + <kbd>BACK</kbd> oko 5 s |
| Tvrdo ponovno pokretanje (resetiranje napajanja) | Odspojite USB, držite <kbd>BACK</kbd> oko 30 s |
| Ponovno pokretanje u DFU (oporavak) | Držite <kbd>←</kbd> + <kbd>BACK</kbd>, otpustite <kbd>BACK</kbd>, držite <kbd>←</kbd> dok ne zasvijetli plava LED dioda |

Sve kombinacije za resetiranje i DFU, kao i slučajevi kada pojedina ne radi, nalaze se u [Kombinacije tipki](/hr/start/key-combos).

## Prečaci na radnoj površini

| Gumb | Kratki pritisak | Dugi pritisak |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | Omiljena aplikacija (OK Long) |
| <kbd>↑</kbd> | Lock Menu | **Zaključavanje Flippera** (s PIN-om ako je postavljen) |
| <kbd>↓</kbd> | Archive | Zaslon s informacijama o uređaju / debug zaslon |
| <kbd>←</kbd> | Omiljena aplikacija (Left Short), zadano izbornik Apps | Omiljena aplikacija (Left Long) |
| <kbd>→</kbd> | Passport (ili dodijeljena aplikacija) | Omiljena aplikacija (Right Long) |
| <kbd>BACK</kbd> | — | Zaslon za isključivanje |

Aplikacije dodjeljujete u **Settings → Desktop → Favorite App - …**. Pojedinosti su na stranici [Radna površina](/hr/start/desktop).

::: tip Unleashed
Držanje <kbd>↑</kbd> na radnoj površini odmah zaključava uređaj (s PIN-om ako je postavljen). U tvorničkom firmveru
zaključavate iz izbornika Lock Menu.
:::

Kratki <kbd>↑</kbd> otvara Lock Menu:

![Lock Menu: odabrano Turn Bluetooth On, ispod toga Mute i Dummy Mode](/screens/desktop/lock_menu.png)

Ako je postavljen PIN, Flipper ga traži prije otključavanja. Strelice unose kôd, <kbd>BACK</kbd> ga briše, a
<kbd>OK</kbd> potvrđuje:

![Unos PIN-a: četiri unesene znamenke prikazane kao zvjezdice, prazno peto polje, oznaka za brisanje i gumb OK](/screens/desktop/pin_input.png)

Dugi <kbd>↓</kbd> otvara zaslon s informacijama o uređaju — vrijeme neprekidnog rada, reviziju hardvera, naziv Flippera, verziju i datum gradnje firmvera,
commit, verziju API-ja i zastavicu Debug. Dugi <kbd>OK</kbd> na tom zaslonu uključuje ili isključuje Debug:

![Zaslon s informacijama o uređaju: Uptime 1h23m45s, hardware 13.F7B9C6 R00, firmware unlshd-080 built 21-11-2026 i D:ON](/screens/desktop/debug.png)

## Odziv gumba

**Main Menu → Settings → Input**

| Stavka | Vrijednosti | Značenje |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Kratka vibracija pri svakom pritisku gumba. Veći brojevi vibriraju dulje |
| Vibro Trigger | `Press`, `Release`, `Both` | Kada se vibracija aktivira |

## Unos teksta

Na virtualnoj tipkovnici pomičite se strelicama i pritisnite <kbd>OK</kbd> za unos odabranog znaka. Držite
<kbd>OK</kbd> na slovu za unos velikog slova. Odaberite tipku `⏎` / **Save** za potvrdu. <kbd>BACK</kbd>
briše zadnji znak ili napušta tipkovnicu.

::: tip Unleashed
Unos teksta ima **kursor**, pa možete uređivati u sredini teksta. U heksadekadskom **unosu bajtova** (na primjer pri
ručnom dodavanju ključa), pritisnite <kbd>↑</kbd> nekoliko puta dok se ne pojavi **mini-uređivač polubajtova (nibble mini-editor)**. Omogućuje promjenu
jednog polubajta odjednom.
:::
