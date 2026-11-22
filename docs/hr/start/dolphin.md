---
title: Kućni ljubimac dupin
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# Kućni ljubimac dupin

Na radnoj površini Flippera živi digitalni dupin. Postaje sretniji i napreduje po razinama dok koristite alate uređaja, a njegove se animacije mijenjaju ovisno o raspoloženju i razini.

## Putovnica (Passport)

Pritisnite <kbd>→</kbd> na radnoj površini ili idite na **Main Menu → Settings → Passport**. Putovnica prikazuje:

- sliku dupina za trenutnu razinu;
- **naziv**: naziv uređaja Flipper ([možete ga promijeniti](/hr/start/custom-name));
- **Mood**: `Happy`, `Ok` ili `Angry`;
- **Level** i traku napretka do sljedeće razine.

![Passport: portret dupina, naziv Flippera, Mood: Happy, Level: 2 i traka napretka do razine 3](/screens/settings/passport.png)

## Raspoloženje

Dupin postaje tužniji kada ne koristite Flipper. Njegov brojač „nezadovoljstva“ (butthurt) raste za jedan otprilike **svakih 48 sati** bez aktivnosti. Korištenje aplikacija podiže raspoloženje natrag, uz dnevno ograničenje brzine oporavka.

**Happy Mode** održava dupina sretnim bez obzira na sve:

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. Dijalog kaže: *"I will never get angry at you for not spending time with me as long as this mode is enabled"*. Otvorite ga ponovno i odaberite **Disable** da biste ga isključili.

## Razine i XP

| Razina | Potreban XP |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Svaka aplikacija može dati najviše **20 XP dnevno**. Postoji 7 brojanih skupina (Sub-GHz, RFID, NFC, Infrared, iButton, Bad USB i „dodaci“, što uključuje U2F, GPIO i vanjske aplikacije), pa je maksimum **140 XP dnevno**. Ograničenja se poništavaju svakodnevno.

### XP po radnji

| Aplikacija | Radnja | XP |
|---|---|---|
| Sub-GHz | Primanje i pregled signala | 1 |
| | Spremanje signala | 3 |
| | Snimanje RAW | 1 |
| | Ručno dodavanje | 2 |
| | Slanje spremljenog signala | 2 |
| | Korištenje Frequency Analyzera | 1 |
| 125 kHz RFID | Ulazak u Read | 1 |
| | Uspješno čitanje | 3 |
| | Spremanje | 3 |
| | Emulacija | 2 |
| | Ručno dodavanje | 2 |
| NFC | Ulazak u Read | 1 |
| | Uspješno čitanje | 3 |
| | Spremanje | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emulacija | 2 |
| | Ručno dodavanje ključa | 2 |
| | Ručno dodavanje i spremanje / emulacija | 1 |
| Infrared | Slanje signala | 1 |
| | Uspješno učenje | 3 |
| | Spremanje | 3 |
| iButton | Ulazak u Read | 1 |
| | Uspješno čitanje | 3 |
| | Spremanje | 3 |
| | Emulacija | 2 |
| | Ručno dodavanje | 2 |
| Bad USB | Pokretanje skripte | 3 |
| U2F | Uspješna autorizacija | 3 |
| GPIO | Otvaranje USB-UART Bridge | 1 |
| Apps | Pokretanje vanjske aplikacije | 2 |
| | Pokretanje igre | 1 |
| | Pobjeda u igri | 10 |

Kada dupin dosegne novu razinu, Flipper prikazuje obavijest o prelasku na novu razinu i mijenjaju se animacije na radnoj površini.

## Gdje je pohranjeno stanje

Dupinov XP, razina i raspoloženje čuvaju se u datoteci `.dolphin.state` u unutarnjoj pohrani. [Vraćanje na tvorničke postavke](/hr/start/recovery#factory-reset) vraća dupina na razinu 1.
