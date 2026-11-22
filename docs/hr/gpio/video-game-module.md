---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

**Video Game Module** (VGM) službeni je dodatak izgrađen oko mikrokontrolera **Raspberry Pi RP2040**. Uključuje se u GPIO
priključak i dodaje:

- **Video Out** — zrcali zaslon Flippera na TV ili monitor (DVI-D signal, 640×480);
- **6-osni senzor pokreta** (TDK ICM-42688-P: 3-osni žiroskop + akcelerometar) za upravljanje pokretom;
- **USB-C priključak** spojen na RP2040 (za flashanje ili korištenje s prilagođenim firmverom);
- **14-pinski GPIO izvod** mikrokontrolera RP2040;
- **tipke BOOT / RESET** (pritisnite spajalicom) za UF2 način flashanja i resetiranje;
- RGB LED diodu na vrhu.

Može raditi i kao samostalna RP2040 pločica, kompatibilna s projektima za Raspberry Pi Pico.

![Tipke i priključci modula Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Postavljanje i povezivanje s TV-om

1. **Namjestite modul.** Dolazi sa silikonskim odbojnikom oblikovanim za Flipper *bez* zaštitne maske. Ako je vaš Flipper u
   silikonskoj maski, skinite odbojnik s modula (ili masku s Flippera).
2. **Firmver.** Modulu je potreban firmver Flippera 0.98.3 ili noviji; trenutačna izdanja Unleashed zadovoljavaju taj uvjet.
3. **Provjerite UART postavku:** `Main Menu → Settings → Expansion Modules → Listen UART` mora biti **`USART`**. Uz bilo koju
   drugu vrijednost modul neće biti prepoznat. (Pogledajte [Moduli proširenja](/hr/gpio/expansion-modules).)
4. Priključite modul (dok je Flipper isključen) i uključite uređaj. Flipper automatski prepoznaje i priprema modul.
5. Spojite TV kabel u **Video Out** priključak modula i odaberite taj ulaz na TV-u.

### "Video Game Module not initialized"

Ovaj tekst na TV-u znači da modul ne komunicira s Flipperom: firmver je prestar, `Listen UART` nije postavljen na `USART`
ili se modul napaja (npr. putem USB-a) bez priključenog Flippera.

## Igre i aplikacije

Senzor pokreta koriste aplikacije iz kataloga Flipper Apps Catalog, primjerice
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) i [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(žiroskopski miš za računalo).

::: tip Unleashed
JavaScript pokretač u firmveru Unleashed uključuje modul `vgm` (JS značajka `vgm`): `getPitch()`, `getRoll()`, `getYaw()` i
`deltaYaw(angle, timeout)` čitaju orijentaciju modula iz skripte, a vraćaju `undefined` ako VGM nije priključen.
Za JavaScript aplikacije pogledajte odjeljak [Razvoj](/hr/dev/).
:::

## Ažuriranje firmvera modula

Ažuriranja se instaliraju pomoću aplikacije **Video Game Module Tool** (iz kataloga Flipper Apps Catalog). Njezin izbornik:

- `Install Official Firmware` — najnoviji službeni firmver modula, priložen uz aplikaciju;
- `Install Firmware from File` — prilagođena `.uf2` datoteka s microSD kartice.

Postupak ažuriranja:

1. Instalirajte (ili **najprije ažurirajte**) Video Game Module Tool: u mobilnoj aplikaciji Flipper idite na **Apps**, potražite
   *Video Game Module Tool* i dodirnite **INSTALL** / **UPDATE**. Novi firmver modula dolazi s novom inačicom aplikacije,
   stoga uvijek ažurirajte aplikaciju prije ažuriranja modula.
2. Spojite modul na Flipper.
3. Otvorite `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Odaberite `Install Official Firmware`, potvrdite s `Install` (<kbd>→</kbd>).
5. Pričekajte poruku **Video Game Module Updated**.

## Prilagođeni firmver

Modul može pokretati vaš vlastiti RP2040 firmver.

### Putem uređaja Flipper Zero

Omogućuje držanje više firmvera modula na microSD kartici i njihovu zamjenu bez računala.

1. Kopirajte `.uf2` datoteku na microSD karticu Flippera (npr. pomoću alata [qFlipper](/hr/mobile/qflipper): `File manager → SD Card`,
   stvorite mapu i prenesite datoteku).
2. Spojite modul, otvorite `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Odaberite datoteku i potvrdite s `Install` (<kbd>→</kbd>). Pričekajte poruku **Video Game Module Updated**.

::: warning UF2 ograničenja pri instalaciji putem Flippera
- Blokovi koji nisu namijenjeni flash memoriji nisu podržani.
- Korisni teret bloka mora imati točno 256 bajtova.
- Ciljne adrese korisnog tereta moraju biti poravnate na 256 bajtova, bez praznina.
- Datotečni spremnici i oznake proširenja nisu podržani.
:::

### Putem računala

1. Odspojite modul od Flippera i od USB-a.
2. Spajalicom držite pritisnutu tipku **BOOT** na modulu.
3. Spojite modul s računalom putem USB-C kabela. Pojavit će se kao USB pogon naziva **RPI-RP2**. Otpustite **BOOT**.
4. Povucite `.uf2` datoteku na pogon **RPI-RP2**. Modul će se sam ponovno pokrenuti i odspojiti.

## Hardverske pojedinosti (za samostalnu upotrebu)

### RP2040 GPIO

- GPIO **8–15** i **18–20** koriste se za video izlaz i nisu dostupni na priključcima.
- GPIO **0–7, 16, 17, 21, 22, 26–28** nalaze se na priključcima (kao na pločici Raspberry Pi Pico). GPIO **2–7** također su spojeni
  na senzor pokreta.
- GPIO **23–25 i 29** (koji se na Picu koriste interno) slobodni su na VGM-u i izvedeni na 14-pinski izvod.

![Raspored pinova 14-pinskog izvoda modula Video Game Module](/img/remote/b030c6a0375c6254.png)

![Usporedba rasporeda pinova modula Video Game Module i Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Periferija dostupna mikrokontroleru RP2040

- **Video Out:** slika i zvuk prema TV-u/monitoru, uz razmjenu podataka putem protokola
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** USB uređaj ili host (bez USB Power Deliveryja).
- **IMU:** TDK ICM-42688-P.
- **GPIO izvod:** 11 GPIO pinova sa zaštitom od elektrostatičkog pražnjenja (ESD).
- **Priključak prema Flipper Zeru:** Flipperovi pinovi 13 i 14 potpuno su funkcionalni; pinovi 2–7 s ograničenom funkcionalnošću (dijeljeni
  sa senzorom pokreta IMU). Zaštićeno od ESD-a.
- **RGB LED dioda**, upravljana putem RP2040 GPIO-a.

### Napajanje

- 5 V putem USB-C priključka pri samostalnom radu;
- 3,3 V (pin 9) ili 5 V (pin 1) s Flippera.

Istodobno napajanje putem USB-C priključka i Flippera sigurno je za modul i za oba izvora.

Sheme, nacrti sastavljanja PCB-a i PDF rasporedi pinova nalaze se na službenoj stranici
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Povezano

- [Moduli proširenja](/hr/gpio/expansion-modules)
- [Raspored GPIO pinova](/hr/gpio/pinout)
- [Vanjski moduli](/hr/gpio/external-modules)
