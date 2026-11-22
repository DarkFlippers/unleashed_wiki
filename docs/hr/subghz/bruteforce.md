---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** jest aplikacija za isprobavanje statičkih kodova grubom silom (brute force) koju je izradio tim Unleashed. Prolazi kroz moguće kodove protokola s fiksnim kodom i odašilje ih jedan za drugim. Možete upotrijebiti unaprijed konfigurirani protokol s popisa ili učitati vlastitu `.sub` datoteku i odabrati koje bajtove želite prolaziti.

::: warning
Koristite je samo na vlastitoj opremi ili uz izričito dopuštenje. Pokušaj pogađanja koda tuđih vrata ili rampe protuzakonit je u većini država.
:::

::: tip Unleashed
Aplikacija nije dio slike firmvera i ne nalazi se u stablu izvornog koda firmvera. Isporučuje se kao vanjska aplikacija (`.fap`) u paketima aplikacija Unleashed, izrađenima iz repozitorija [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Instalirajte paket (pogledajte [Aplikacije na SD kartici](/hr/apps/sd-card-apps)) i potražite je pod `Apps → Sub-GHz`.
:::

## Kada ima smisla

- **Samo statički (fiksni) kôd.** Napad grubom silom radi samo kada prijamnik zauvijek prihvaća isti kôd, kao kod sustava CAME 12-bit, Nice Flo 12-bit, daljinskih upravljača tipa Princeton i sličnih daljinskih upravljača s DIP sklopkama. Prijamnik s promjenjivim kodom (KeeLoq, Nice Flor-S, CAME Atomo i drugi) nikada ne prihvaća pogođeni kôd, pa je ondje gruba sila beskorisna (pogledajte [Promjenjivi kodovi](/hr/subghz/rolling-codes)).
- **Izgubili ste daljinski upravljač vlastitog uređaja sa statičkim kodom** i ne znate njegov kôd, ili želite provjeriti koliko se brzo vaš vlastiti sustav s fiksnim kodom može pogoditi.

Ako još uvijek imate ispravan daljinski upravljač, daleko je brže jednostavno ga [očitati](/hr/subghz/read).

## Kako se koristi

### Unaprijed konfigurirani protokoli

1. Otvorite `Apps → Sub-GHz` i pokrenite aplikaciju Bruteforce.
2. Odaberite protokol s popisa.
3. Za promjenu broja ponavljanja svakog koda pritisnite <kbd>→</kbd> na odabranom protokolu.
4. Pokrenite napad i držite Flipper blizu prijamnika dok ne reagira.

### Vlastita datoteka

1. Najprije spremite signal ciljanog protokola, primjerice pomoću [Read](/hr/subghz/read) ili [Add Manually](/hr/subghz/add-manually).
2. U aplikaciji učitajte tu `.sub` datoteku.
3. Odaberite bajtove ključa koje želite pogađati grubom silom. Ostali bajtovi ostaju kakvi jesu u datoteci.
4. Pokrenite napad.

### Odgoda između signala

Vremenska odgoda između odaslanih kodova postavlja se na glavnom zaslonu aplikacije. **Držite <kbd>↑</kbd>** ondje (naznaka na zaslonu glasi "Up to Save") za spremanje. Kraća odgoda završava brže, ali neki prijamnici propuste kodove koji dolaze prebrzo jedan za drugim.

## Savjeti i česte pogreške

- **Pogrešna frekvencija ili modulacija**: prijamnik ne čuje ništa. Najprije provjerite pojas pomoću [Analizatora frekvencije](/hr/subghz/frequency-analyzer).
- **Premalo ponavljanja**: mnogi prijamnici traže da se kôd ponovi nekoliko puta prije nego što reagiraju. Povećajte broj ponavljanja tipkom <kbd>→</kbd> na protokolu.
- **Traje dugo**: broj kodova raste eksponencijalno s brojem bitova. 12-bitni kodovi brzi su, dok dulji ključevi mogu trajati nepraktično dugo. Suzite pretragu pogađanjem samo nepoznatih bajtova vlastite datoteke.
- **Odašiljanje je blokirano**: frekvencija je izvan dopuštenog raspona. Pogledajte [Frekvencije](/hr/subghz/frequencies).

## Povezane stranice

- [Podržani sustavi](/hr/subghz/supported-systems): koji su protokoli statički
- [Ručno dodavanje](/hr/subghz/add-manually)
- [Format .sub datoteke](/hr/subghz/file-format)
