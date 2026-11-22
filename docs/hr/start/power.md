---
title: Napajanje i baterija
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Napajanje i baterija

Flipper Zero ima ugrađenu Li-Po bateriju od **2100 mAh**. U stanju pripravnosti može trajati do otprilike mjesec dana, a putem USB-C priključka puni se za oko dva sata.

## Uključivanje i isključivanje

- **Uključivanje:** držite <kbd>BACK</kbd> oko 3 s. Potpuno ispražnjeni Flipper uključuje se sam kada priključite USB.
- **Isključivanje:** držite <kbd>BACK</kbd> na radnoj površini. Pojavljuje se zaslon **Turn Off Device?**: <kbd>→</kbd> **Power Off** ga isključuje, a <kbd>←</kbd> **Battery** otvara podatke o bateriji. Možete upotrijebiti i **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? s uplakanim dupinom, Battery na lijevoj tipki i Power Off na desnoj](/screens/settings/power_off.png)

## Punjenje

Priključite USB-C kabel u punjač ili računalo. Ikona baterije prikazuje munju dok se puni. Ulaz za punjenje iznosi 5 V / 1 A, pa puno punjenje traje oko 2 sata.

::: warning Dugotrajna pohrana
Ako Flipper nećete koristiti dulje vrijeme, napunite ga na oko **50 %** prije isključivanja. Pohranjivanje potpuno ispražnjene baterije šteti bateriji. Čuvajte uređaj na temperaturi između 0 i 40 °C.
:::

## Settings → Power

| Stavka | Što radi |
|---|---|
| **Battery Info** | Postotak napunjenosti, napon, struja, temperatura baterije i zdravlje |
| **Reboot** | **Firmware Upgrade** (ponovno pokretanje u DFU način) ili **Reboot Flipper** (uobičajeno ponovno pokretanje). Potvrdite s <kbd>→</kbd> **Reboot** |
| **Power OFF** | Isključivanje uređaja |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min`: isključivanje nakon toliko vremena neaktivnosti |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%`: prekid punjenja na ovoj razini |

![Settings → Power: Battery Info, Reboot, Power OFF, Auto PowerOff OFF, Limit Charge OFF](/screens/settings/power.png)

::: tip Limit Charge
Limit Charge je koristan ako je Flipper većinu dana priključen na USB, primjerice kao stolni uređaj. Održavanje baterije ispod 100 % produljuje njezin životni vijek.
:::

## Zaslon Battery Info

Zaslon prikazuje drugačiju poruku ovisno o stanju:

| Zaglavlje | Značenje |
|---|---|
| `Yummy!` / `Charging at` | Punjenje. Prikazuje USB napon i struju punjenja |
| `Om-nom-nom!` / `Consumption is` | Rad na bateriji, s trenutačnom potrošnjom. `Oh no!` i `mA!` znače veliku potrošnju |
| `Charged!` | USB priključen, ne puni se (baterija puna) |
| `Charged!` / `Limited to` | USB priključen i postavljeno je nezadano ograničenje napona punjenja (prikazano u V) |
| `Napping...` | Na bateriji, gotovo nikakva potrošnja struje |

Također prikazuje postotak baterije, napon, temperaturu (°C ili °F, postavljeno u **Settings → System → Units**) i postotak **zdravlja** baterije.

![Battery Info: Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4.1 V, health 100 %](/screens/settings/battery_info.png)

## Potrošnja energije

| Način rada | Tipična struja |
|---|---|
| Spavanje (zadana metoda spavanja) | ~1,5 mA |
| Spavanje (naslijeđena metoda spavanja) | ~9 mA |
| Aktivan rad, uključeno pozadinsko osvjetljenje | do ~30 mA (do ~50 mA s lošom SD karticom) |
| Aktivan radio | do ~400 mA |
| Radio + vanjski modul | do ~2 A |

**Sleep Method** nalazi se u **Settings → System**. `Default` štedi energiju. `Legacy` troši više, ali može pomoći ako primijetite rušenja sustava tijekom spavanja.

Za spavanje moraju biti postavljeni **Debug** = `OFF` (**Settings → System**) i **Listen UART** = `None` (**Settings → Expansion Modules**). U suprotnom uređaj ne može prijeći u stanje spavanja i baterija se brže prazni.

## Savjeti za dulje trajanje baterije

- Redovito ažurirajte firmver.
- Isključite Bluetooth kada ga ne trebate (Lock Menu → **Turn Bluetooth Off**).
- Smanjite **LCD Backlight** i **Backlight Time** u **LCD and Notifications**.
- Koristite kvalitetnu microSD karticu poznate marke.
- Postavite **Auto PowerOff**.
- Ako se baterija brzo prazni, provjerite potrošnju u **Battery Info**.

## Specifikacije napajanja

| Parametar | Vrijednost |
|---|---|
| Kapacitet baterije | 2100 mAh |
| Radni napon baterije | 3,3–4,2 V |
| Vrijeme punjenja | ~2 sata |
| Napon / struja punjenja | 5 V, 1 A |
| Priključak | USB Type-C |
| Maks. struja s USB-a uključujući povezane uređaje | 3 A |

## Povezano

- Kombinacije za ponovno pokretanje i resetiranje: [Kombinacije tipki](/hr/start/key-combos)
- Uređaj se ne uključuje: [Oporavak](/hr/start/recovery)
