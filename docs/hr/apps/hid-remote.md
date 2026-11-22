---
title: USB / Bluetooth daljinski upravljač (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# USB / Bluetooth daljinski upravljač (HID)

Aplikacija HID čini da Flipper računalu, telefonu ili tabletu izgleda kao tipkovnica, miš ili medijski daljinski upravljač (USB **H**uman **I**nterface **D**evice). Ista aplikacija ugrađena je dvaput:

| Aplikacija | Gdje na Flipperu | Povezivanje |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | USB kabel |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Upute za povezivanje nalaze se na stranici [Uparivanje HID daljinskog upravljača](/hr/apps/controllers). Ova stranica opisuje svaki način rada.

## Načini rada

Početni izbornik navodi:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

Bluetooth verzija također ima `Bluetooth Remote Name` i `Bluetooth Unpairing`.

::: tip Unleashed
Službena dokumentacija opisuje Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler i Mouse Clicker. Unleashed izdanje aplikacije dodatno sadrži **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**, **PushToTalk** te **Bluetooth Remote Name** za promjenu naziva kojim se daljinski upravljač oglašava.
:::

U gotovo svakom načinu rada **držite <kbd>Back</kbd> za izlaz** natrag na popis načina rada; sve tipke se otpuštaju pri izlasku.

### Keynote i Keynote Vertical

Daljinski upravljač za prezentacije. Keynote Vertical je isti način rada, zakrenut za držanje Flippera okomito.

| Tipka | Šalje |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | strelice (sljedeći / prethodni slajd) |
| <kbd>OK</kbd> | razmaknica (Space) |
| <kbd>Back</kbd> | Backspace + "AC Back" (napušta prikaz prezentacije u većini aplikacija) |
| držite <kbd>Back</kbd> | izlaz |

### Keyboard

Zaslonska QWERTY tipkovnica s znamenkama, simbolima, tipkama F1-F12, Esc, Tab, Enter, Backspace, Delete te modifikatorima Ctrl, Alt, Shift i Cmd (Win).

1. Krećite se strelicama i pritisnite <kbd>OK</kbd> za unos odabrane tipke.
2. Odaberite tipku ⬆ (Shift) za unos velikih slova i drugog reda simbola.
3. Za prečac prvo pritisnite modifikator (Ctrl, Alt ili Cmd), zatim tipku.
4. Držite <kbd>Back</kbd> za izlaz.

### Numpad

Numerička tipkovnica: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Enter na numeričkom dijelu), `NL` (Num Lock) i Backspace. Strelice služe za odabir, <kbd>OK</kbd> pritišće tipku, a držanje <kbd>Back</kbd> izlazi iz načina rada.

### Media

| Tipka | Šalje |
|---|---|
| <kbd>OK</kbd> | Reprodukcija / Pauza |
| <kbd>←</kbd> / <kbd>→</kbd> | prethodni / sljedeći zapis |
| <kbd>↑</kbd> / <kbd>↓</kbd> | pojačavanje / stišavanje glasnoće |
| držite <kbd>Back</kbd> | izlaz |

Na telefonima tipke za glasnoću služe i kao okidač kamere: otvorite kameru i pritisnite <kbd>↑</kbd> ili <kbd>↓</kbd> za fotografiranje ili pokretanje/zaustavljanje snimanja videa.

### Apple Music macOS

| Tipka | Šalje |
|---|---|
| <kbd>OK</kbd> | Reprodukcija / Pauza |
| <kbd>←</kbd> / <kbd>→</kbd> | prethodni / sljedeći zapis |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (glasnoća u Apple Musicu) |
| držite <kbd>Back</kbd> | izlaz |

### Movie

| Tipka | Šalje |
|---|---|
| <kbd>OK</kbd> | Reprodukcija / Pauza |
| <kbd>←</kbd> / <kbd>→</kbd> | Strelica lijevo / desno (premotavanje u većini reproduktora) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | pojačavanje / stišavanje glasnoće |
| držite <kbd>Back</kbd> | izlaz |

### Mouse

| Tipka | Radnja |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | pomicanje pokazivača; držanje ubrzava |
| <kbd>OK</kbd> | lijevi klik |
| držite <kbd>OK</kbd> | držanje lijeve tipke (povlačenje, "Selecting...") |
| <kbd>Back</kbd> | desni klik |
| držite <kbd>Back</kbd> | izlaz |

### TikTok / YT Shorts

Za aplikacije s kratkim videozapisima na telefonu ili tabletu.

| Tipka | Radnja |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | pomicanje na prethodni / sljedeći video |
| <kbd>OK</kbd> | dvostruki dodir (lajk) |
| <kbd>←</kbd> / <kbd>→</kbd> | stišavanje / pojačavanje glasnoće |
| <kbd>Back</kbd> | jedan dodir (pauza) |
| držite <kbd>Back</kbd> | izlaz |

::: tip iPhone / iPad
Ako način TikTok ne radi ništa na sustavu iOS, uključite `Settings → Accessibility → Touch → AssistiveTouch`, a zatim u **Pointer Devices → Devices → Bluetooth Devices** odaberite svoj Flipper.
:::

### Mouse Clicker

Automatski klika zadanom brzinom.

| Tipka | Radnja |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | broj klikova u sekundi, do 100 (zadano 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | odabir tipke: lijeva, desna ili kotačić (srednja) |
| <kbd>Back</kbd> | izlaz |

### Mouse Jiggler

Malo pomiče pokazivač u fiksnom intervalu kako računalo ne bi otišlo u stanje mirovanja ili vas prikazalo kao „odsutne“.

1. Prije pokretanja odaberite interval tipkama <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 ili 60000 ms (zadano 5000 ms).
2. Pritisnite <kbd>OK</kbd> za **Start**, pa ponovno za **Stop**. Dok se računalo ne poveže, na zaslonu piše `Waiting for Connection...`.
3. <kbd>Back</kbd> izlazi.

### Mouse Jiggler Stealth

Slično načinu jiggler, ali pomiče pokazivač u nasumičnim intervalima između minimuma i maksimuma koji postavite u minutama (1 do 30), što izgleda manje strojno. Dok je zaustavljeno, <kbd>↑</kbd> / <kbd>↓</kbd> mijenjaju minimum, a <kbd>→</kbd> / <kbd>←</kbd> povećavaju / smanjuju maksimum; <kbd>OK</kbd> pokreće ili zaustavlja.

### PushToTalk

Tipka za utišavanje / push-to-talk za videopozive.

1. Odaberite popis za svoj OS (**macOS** ili **Win/Linux**), zatim aplikaciju: Google Meet, Google Meet Global, Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle, TeamSpeak, Teams, Webex, Zoom ili Zoom Global.
2. Dugo pritisnite <kbd>OK</kbd> na stavci popisa da biste pročitali njezinu pomoć (neke aplikacije zahtijevaju postavku ili proširenje, primjerice globalni prečac za Google Meet ili dodjelu tipki u TeamSpeaku).
3. U pozivu: <kbd>Back</kbd> uključuje/isključuje mikrofon, **držite <kbd>OK</kbd>** za push-to-talk (mikrofon se isključuje kad pustite tipku), držite <kbd>→</kbd> za promjenu statusa mikrofona na Flipperu ako se ne podudara s računalom. Za Zoom dugi pritisak na <kbd>←</kbd> šalje Enter.
4. Držite <kbd>Back</kbd> za izlaz.

### Bluetooth Remote Name i Bluetooth Unpairing (samo Bluetooth)

- **Bluetooth Remote Name**: upišite naziv u `Bluetooth Name`; daljinski upravljač oglašavat će se pod tim nazivom. Zadano se prikazuje kao `Control <Flipper name>`.
- **Bluetooth Unpairing**: prikazuje upit `Unpair All Devices? All previous pairings will be lost!`; pritisnite **Unpair** kako biste zaboravili sve uređaje uparene s daljinskim upravljačem. Daljinski upravljač čuva vlastite ključeve uparivanja (`/ext/apps_data/hid_ble/.bt_hid.keys`), odvojeno od glavnih Bluetooth uparivanja Flippera.

## Povezane stranice

- [Uparivanje HID daljinskog upravljača](/hr/apps/controllers)
- [Bad USB](/hr/badusb/usage)
- [Aplikacije uključene u Unleashed](/hr/apps/catalog)
