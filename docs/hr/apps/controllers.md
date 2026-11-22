---
title: Uparivanje HID daljinskog upravljača
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Uparivanje HID daljinskog upravljača

Aplikacija HID daljinskog upravljača omogućuje Flipperu upravljanje prezentacijama, unos teksta, pomicanje pokazivača miša i upravljanje multimedijom na računalu ili telefonu. Ova stranica pokriva **povezivanje**; što svaki način rada radi opisano je na stranici [USB / Bluetooth daljinski upravljač (HID)](/hr/apps/hid-remote).

Možete se povezati na dva načina:

| | USB | Bluetooth LE |
|---|---|---|
| Aplikacija | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Uparivanje | nije potrebno, samo priključite | jednom po uređaju |
| Radi s | računalima, telefonima s USB-C/OTG podrškom | računalima, uređajima Android, iPhone/iPad |

::: tip Unleashed
U firmveru Unleashed te se dvije varijante zovu **USB Keyboard & Mouse** i **Bluetooth Remote**, a nalaze se u mapama aplikacija `USB` i `Bluetooth` (službena dokumentacija obje naziva „Remote“).
:::

## Putem USB-a

1. Povežite Flipper s računalom pomoću USB podatkovnog kabela. Najprije zatvorite qFlipper jer daljinski upravljač treba USB priključak.
2. Otvorite `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Odaberite način rada (Keynote, Keyboard, Mouse...). Računalo prepoznaje novu tipkovnicu ili miša i upravljački program nije potreban.

Kada izađete iz aplikacije, USB na Flipperu vraća se u uobičajeni (serijski) način rada.

## Putem Bluetootha

1. Uključite Bluetooth na računalu ili telefonu.
2. Na Flipperu otvorite `Main Menu → Settings → Bluetooth` i postavite **Bluetooth** na **ON**.
3. Otvorite `Main Menu → Apps → Bluetooth → Bluetooth Remote` i odaberite način rada.
4. Na računalu ili telefonu otvorite postavke Bluetootha i povežite se s uređajem **Control &lt;naziv Flippera&gt;** (na telefonu dodirnite **Pair**).
5. Ako Flipper prikaže potvrdu uparivanja, pritisnite <kbd>OK</kbd>.

Sljedeći put računalo ili telefon automatski se ponovno povezuje kada otvorite Bluetooth Remote.

::: tip Prilagođeni naziv
`Bluetooth Remote → Bluetooth Remote Name` mijenja oglašeni naziv, što je korisno ako imate više Flipper daljinskih upravljača ili želite da izgleda kao obična tipkovnica.
:::

### Ako uparivanje ne uspije

- Provjerite je li Bluetooth uključen (`ON`) u `Settings → Bluetooth`.
- Uklonite stari unos „Control ...“ u postavkama Bluetootha na računalu ili telefonu, zatim na Flipperu pokrenite `Bluetooth Remote → Bluetooth Unpairing → Unpair` i pokušajte ponovno upariti.
- Odspojite Flipper s drugih uređaja (primjerice s mobilne aplikacije).
- Ponovno pokrenite Flipper: držite <kbd>←</kbd> + <kbd>Back</kbd> oko 5 sekundi.
- Ažurirajte firmver.

Daljinski upravljač sprema vlastita uparivanja (`/ext/apps_data/hid_ble/.bt_hid.keys`), odvojeno od glavnog Bluetootha Flippera koji koristi mobilna aplikacija. **Bluetooth Unpairing** unutar daljinskog upravljača briše samo uređaje uparene s daljinskim upravljačem. Globalna opcija `Settings → Bluetooth → Unpair All Devices` briše sve: uparivanje mobilne aplikacije, kao i uparivanja daljinskog upravljača (i BadKB-a).

### iPhone / iPad: način TikTok ne reagira

1. Na iPhoneu otvorite `Settings → Accessibility → Touch → AssistiveTouch`.
2. Uključite **AssistiveTouch**.
3. Pod **Pointer Devices** idite na **Devices → Bluetooth Devices** i odaberite svoj Flipper.

## Povezane stranice

- [USB / Bluetooth daljinski upravljač (HID)](/hr/apps/hid-remote)
- [Postavke](/hr/start/settings)
- [Mobilna aplikacija Flipper](/hr/mobile/mobile-app)
