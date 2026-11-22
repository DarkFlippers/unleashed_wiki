---
title: U2F sigurnosni ključ
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# U2F sigurnosni ključ

Aplikacija **U2F** pretvara Flipper Zero u USB sigurnosni ključ [Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor)
(FIDO U2F). Nakon što na web-stranici unesete lozinku, stranica zatraži ključ, a vi prijavu potvrđujete pritiskom na
<kbd>OK</kbd> na Flipperu. Google, GitHub, Facebook, X i mnoge druge stranice podržavaju U2F ključeve; popis održava
[dongleauth.com](https://www.dongleauth.com/).

::: warning Softverski ključ
U2F na Flipperu implementiran je softverski. Za bankarstvo i druge račune visoke važnosti koristite certificirani
hardverski sigurnosni ključ. Uvijek čuvajte i rezervni drugi faktor (kodove za oporavak ili drugi ključ).
:::

## Prije početka

- **Obavezna je microSD kartica**. U2F podaci nalaze se u mapi `/ext/u2f/`. Bez nje aplikacija prikazuje poruku
  `No SD card or app data found. This app will not work without required files.`
- Datoteke certifikata `/ext/u2f/assets/cert.der` i `/ext/u2f/assets/cert_key.u2f` instaliraju se prilikom ažuriranja
  firmvera. Ako nedostaju, ponovno ažurirajte firmver s umetnutom karticom.
- **Zatvorite qFlipper** (i Flipper Lab): Flipper mora moći slobodno prebaciti svoj USB priključak u U2F način rada. Ako je
  veza aktivna, aplikacija prikazuje `Connection Is Active! Disconnect from PC or phone to use this function.`

## Registracija Flippera na web-stranici

1. Povežite Flipper s računalom putem USB kabela.
2. Otvorite `Main Menu → U2F`. Zaslon prikazuje `Connect me to computer`, a zatim `Connected!` čim računalo prepozna ključ.

   ![U2F: Connect me to computer, s Flipperom prikazanim kao USB stick](/screens/apps/u2f_not_connected.png)

3. Na web-stranici otvorite postavke dvofaktorske autentifikacije i odaberite dodavanje **sigurnosnog ključa** (naziv se razlikuje od stranice do stranice).
4. Flipper prikazuje `Press OK to register`. Pritisnite <kbd>OK</kbd>.
5. Stranica potvrđuje da je ključ dodan.

## Prijava

1. Povežite Flipper putem USB-a i otvorite `Main Menu → U2F` (`Connected!`).
2. Unesite korisničko ime i lozinku na web-stranici.
3. Kada stranica zatraži sigurnosni ključ, Flipper prikazuje `Press OK to authenticate`. Pritisnite <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate, s oznakom tipke OK](/screens/apps/u2f.png)

4. Flipper prikazuje `Authentication successful!`, a stranica vas prijavljuje.

## Čuvajte svoje U2F datoteke

| Datoteka | Namjena |
|---|---|
| `/ext/u2f/key.u2f` | U2F ključ ovog uređaja, kriptiran ključem jedinstvenim za ovaj Flipper |
| `/ext/u2f/cnt.u2f` | brojač autentifikacija |
| `/ext/u2f/assets/` | atestacijski certifikat i njegov ključ (`cert.der`, `cert_key.u2f`) |

::: danger Nemojte brisati, uređivati niti premještati U2F datoteke
- Svaki Flipper ima jedinstveni ugrađeni ključ kojim kriptira U2F datoteke. Kartica s U2F datotekama premještena u
  **drugi Flipper neće raditi** na njemu.
- Ako izbrišete ili uredite datoteke, ili umetnete novu karticu, Flipper stvara novi skup U2F datoteka i morat ćete
  **ponovno registrirati ključ na svakoj web-stranici**.
- Ako izbrišete `u2f/assets` (ili cijelu mapu `u2f`), aplikacija prestaje raditi (prijavljuje `No SD card or app data found`)
  dok mapu ne vratite ažuriranjem firmvera.
:::

## Rješavanje problema

| Simptom | Rješenje |
|---|---|
| Ostaje na `Connect me to computer` | upotrijebite podatkovni kabel (ne samo za punjenje), zatvorite qFlipper, pokušajte drugi USB priključak |
| `Connection Is Active!` | zatvorite qFlipper, Flipper Lab, CLI ili sesiju mobilne aplikacije, pa ponovno otvorite U2F |
| `No SD card or app data found` | umetnite karticu; ako je već unutra, vratite `/ext/u2f/assets` ponovnom instalacijom firmvera |
| `Certificate error` | U2F mehanizam se nije mogao pokrenuti s datotekama na kartici: ponovno instalirajte firmver s umetnutom karticom |
| Stranica više ne prihvaća ključ | U2F datoteke su ponovno generirane (nova kartica, izbrisane datoteke): prijavite se rezervnim faktorom i ponovno registrirajte Flipper |

Kartica **U2F** u aplikaciji [Archive](/hr/apps/archive) također pokreće ovu aplikaciju.

## Povezane stranice

- [Aplikacije uključene u Unleashed](/hr/apps/catalog)
- [Bad USB](/hr/badusb/usage)
- [qFlipper](/hr/mobile/qflipper)
