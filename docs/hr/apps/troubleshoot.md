---
title: Rješavanje problema s aplikacijama
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Rješavanje problema s aplikacijama

Kada se aplikacija ne može pokrenuti, Flipper prikazuje `Error: <name>` uz kratki savjet i poveznicu `r.flipper.net/err_0X`.
U nastavku je objašnjeno što svaka poruka znači u firmveru Unleashed.

::: tip Unleashed
Unleashed ne blokira aplikacije izrađene za drugu inačicu API-ja. Umjesto tvorničkih pogrešaka **Outdated App** /
**Outdated Firmware**, prikazuje upozorenje i prepušta odluku vama, pogledajte [App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New {#app-too-old-app-too-new}

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

**Glavna inačica API-ja** aplikacije razlikuje se od inačice u firmveru: **App Too Old** znači da je aplikacija izrađena za stariji API,
a **App Too New** za noviji.

- Pritisnite **Continue** (<kbd>→</kbd>) ako želite svejedno pokušati. Mnoge aplikacije rade, ali aplikacija koja poziva promijenjenu funkciju može se srušiti.
- Pritisnite <kbd>Back</kbd> za odustajanje.
- Pravo rješenje: ažurirajte aplikaciju (preuzmite je iz trenutačnog paketa aplikacija Unleashed ili je ponovno prevedite za trenutačni SDK), odnosno za
  **App Too New** ažurirajte firmver.

## Error: App Not Found (err_01)

`Update firmware or app`

| Uzrok | Rješenje |
|---|---|
| datoteka aplikacije izbrisana je s microSD kartice | ponovno instalirajte aplikaciju ili ponovno instalirajte firmver (za sustavske aplikacije) |
| stara ili beta mobilna aplikacija otvorila je aplikaciju iz kataloga koje nema na kartici | instalirajte službenu mobilnu aplikaciju Flipper iz trgovine App Store / Google Play i ponovno instalirajte aplikaciju |

Povezana poruka, **SD card needed** / `Install SD card to run this app`, znači da se aplikacija iz izbornika nalazi na microSD kartici,
a kartica nije umetnuta. **Update needed** / `Update firmware to run this app` znači da je kartica umetnuta, ali datoteka aplikacije
nedostaje: ponovno instalirajte firmver dok je kartica umetnuta.

## Error: Invalid File (err_02)

`Update the app`. Datoteka `.fap` je oštećena: neispravno ELF zaglavlje, nepotpuna datoteka (prekinuto kopiranje) ili sekcije koje
se ne mogu učitati. Ponovno kopirajte ili instalirajte aplikaciju.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. Manifest (posebna ELF sekcija s inačicom API-ja i podacima o aplikaciji) ne može se pročitati.
Datoteka je oštećena ili su aplikacija i firmver previše različitih inačica. Ažurirajte aplikaciju; ako je novija od vašeg firmvera, ažurirajte
firmver.

## Error: Missing Imports (err_04)

`Update firmware or app`. Aplikacija poziva funkcije koje vaš firmver ne izvozi.

| Uzrok | Rješenje |
|---|---|
| aplikacija je izrađena za noviji firmver | ažurirajte Unleashed |
| aplikacija je izrađena za drugi fork (koristi vlastite funkcije tog forka) | pronađite inačicu aplikacije za Unleashed ili je prevedite pomoću Unleashed SDK-a |

## Error: HW Target Mismatch (err_05)

`App not supported`. Aplikacija je izrađena za drugi hardverski cilj Flippera i ne može se pokrenuti na ovom uređaju.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. FAP se učitava u RAM; ako je heap fragmentiran ili je pokrenuto
previše toga (primjerice pozadinski BLE beacon ili velika aplikacija), aplikacija ne stane u memoriju. Pritisnite **Reboot** i pokrenite
aplikaciju odmah nakon ponovnog pokretanja.

## I dalje ne radi

1. Ažurirajte na najnovije izdanje firmvera Unleashed, pogledajte [Ažuriranje](/hr/start/updating).
2. Ponovno instalirajte aplikaciju iz trenutačnog [paketa aplikacija](/hr/apps/catalog#base-and-extra-packs) ili iz kataloga
   ([Aplikacije na SD kartici](/hr/apps/sd-card-apps)).
3. Ako aplikacija sruši Flipper, ponovno ga pokrenite kombinacijom <kbd>←</kbd> + <kbd>Back</kbd>; pogledajte [Oporavak](/hr/start/recovery) ako se
   više ne pokreće.
4. Pitajte u grupama zajednice, pogledajte [Česta pitanja](/hr/start/faq).

## Povezane stranice

- [Aplikacije na SD kartici (.fap)](/hr/apps/sd-card-apps)
- [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog)
