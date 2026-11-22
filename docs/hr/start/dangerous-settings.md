---
title: Opasne postavke
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Opasne postavke: prošireni Sub-GHz raspon

Unleashed može omogućiti rad radijskog čipa CC1101 **izvan njegova službenog frekvencijskog raspona**. Gotovo sigurno vam to neće trebati, a uključivanje vas može koštati radijskog čipa.

::: danger Najprije pročitajte ovo
1. Nemojte to raditi ako niste potpuno sigurni što radite.
2. Prošireni raspon nije vam potreban gotovo ni za kakvu primjenu.
3. Odašiljanje izvan hardverskih specifikacija **može oštetiti vaš hardver**.
4. Ni tim Flipper Devices ni programeri Unleasheda nisu odgovorni za bilo kakvu štetu uzrokovanu prilagođenim firmverom ili proširivanjem frekvencijskog raspona.
:::

## Vjerojatno vam ne treba: nema regionalnog zaključavanja

::: tip Unleashed
U firmveru Unleashed **sva regionalna ograničenja odašiljanja (TX) uklonjena su po zadanim postavkama**. Svaka frekvencija unutar podržanog raspona čipa odašilje bez ikakvih dodatnih koraka. Nemojte koristiti opasne postavke za „otključavanje regije“. Za to nisu potrebne.
:::

Ako je odašiljanje blokirano na nekoj frekvenciji, najprije provjerite je li ta frekvencija unutar uobičajenog TX raspona u nastavku. Izvan njega firmver bilježi `Frequency blocked - outside default range`.

## Frekvencijski rasponi

| | Rasponi |
|---|---|
| Specifikacija čipa CC1101 | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Zadani **TX** raspon Unleasheda | ≈ 300–350 MHz, 387–467,75 MHz, 779–928 MHz (proširen kako bi uključio 350 MHz i 467 MHz) |
| TX s omogućenim `dangerous_settings` | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

Prošireni raspon podudara se s proširenim rasponom uređaja YARD Stick One (prema izvornom kôdu firmvera). Izvan raspona iz specifikacije čip radi izvan deklariranih granica i odašiljanje na tim frekvencijama može ga oštetiti.

## Kako ih omogućiti

1. Izvadite microSD karticu ili se povežite putem qFlippera / upravitelja datoteka po izboru.
2. Otvorite datoteku **`/ext/subghz/assets/dangerous_settings`**. Izgleda ovako:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Pročitajte komentare, zatim promijenite `false` u `true`:
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Spremite datoteku i ponovno pokrenite Flipper. Postavka se učitava pri pokretanju.

Za povratak na staro postavite vrijednost na `false` i ponovno pokrenite uređaj.

::: warning Ažuriranja
Ova datoteka dio je resursa firmvera. Ažuriranje je može prepisati zadanom vrijednošću `false`. Provjerite je nakon ažuriranja ako se oslanjate na tu postavku.
:::

## Povezano

- Sub-GHz frekvencije i predlošci (presets), dodavanje vlastitih frekvencija: [Frekvencije](/hr/subghz/frequencies)
- Sub-GHz postavke unutar aplikacije: [Sub-GHz postavke](/hr/subghz/settings)
- Vanjski CC1101 modul: [Vanjski CC1101](/hr/subghz/external-cc1101)

Koristite radio samo na vlastitim uređajima i u skladu s lokalnim propisima o radijskim komunikacijama.
