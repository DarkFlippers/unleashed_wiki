---
title: Prilagođeni naziv Flippera
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Prilagođeni naziv Flippera

Svaki Flipper ima tvornički naziv. Prikazuje se u Passportu, u izborniku **About**, na popisima Bluetooth uređaja i u aplikaciji qFlipper. Unleashed vam omogućuje da ga zamijenite vlastitim nazivom.

::: tip Unleashed
Izvorni firmver nema izbornik za preimenovanje uređaja. U firmveru Unleashed nalazi se u **Settings → Desktop → Change Flipper Name**, a naziv **ostaje sačuvan nakon ažuriranja firmvera** jer se sprema na microSD karticu.
:::

## Postavljanje naziva

1. Otvorite **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Upišite novi naziv. Zaglavlje tipkovnice kaže `Leave empty for default`.
   - **2 do 8 znakova**;
   - **samo latinična slova i znamenke** (`A–Z`, `a–z`, `0–9`). Sve ostalo prikazuje *"Please only enter letters and numbers!"*.
3. Odaberite **Save**.
4. Pojavljuje se poruka **`Name is set!`** / *"Your Flipper will be restarted on exit."*
5. Napustite Settings tipkom <kbd>BACK</kbd>. Flipper se **automatski ponovno pokreće**.
6. Nakon ponovnog pokretanja novi se naziv prikazuje u Passportu, u **Settings → About** i putem Bluetootha.

## Vraćanje na tvornički naziv

1. Otvorite **Settings → Desktop → Change Flipper Name**.
2. Izbrišite sve znakove i ostavite polje **prazno**.
3. Odaberite **Save** i napustite Settings. Flipper se ponovno pokreće sa svojim izvornim nazivom.

## Kako to radi

- Naziv se sprema u **`/ext/dolphin/name.settings`** na SD kartici:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- Pri pokretanju sustava servis `namechanger` čeka SD karticu, čita tu datoteku i primjenjuje naziv ako je valjan: ispravno zaglavlje i inačica, 2–8 znakova, samo slova i znamenke. Zatim ponovno pokreće USB serijski i Bluetooth profil kako bi koristili novi naziv.
- Spremanje praznog naziva briše datoteku.
- Servis se pokreće samo pri uobičajenom pokretanju, ne u programu za ažuriranje ili u DFU načinu.

Budući da se naziv nalazi na kartici, ostaje nakon ažuriranja. Gubi se ako formatirate ili zamijenite karticu ili izbrišete datoteku.

## Rješavanje problema

| Problem | Rješenje |
|---|---|
| Naziv se nije promijenio | Jeste li napustili Settings (ponovno pokretanje ga primjenjuje)? Je li SD kartica umetnuta? Ima li naziv 2–8 slova/znamenki? Naziv od 1 znaka sprema se, ali se zanemaruje pri pokretanju |
| Mobilna aplikacija se više ne povezuje | Promijenio se Bluetooth naziv. Zaboravite Flipper u aplikaciji **i** u Bluetooth postavkama telefona, pokrenite **Settings → Bluetooth → Unpair All Devices** na Flipperu, a zatim ga ponovno uparite |
| Datoteka naziva kopirana s drugog mjesta se zanemaruje | Provjerite zaglavlje `Flipper Name File`, `Version: 1` i pravila za naziv |
