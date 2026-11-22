---
title: Kombinacije tipki
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Kombinacije tipki

Ponekad Flipper prestane reagirati zbog softverskog problema. Ove kombinacije tipki ponovno ga pokreću na hardverskoj razini ili ga pokreću u DFU načinu (ažuriranje firmvera), bez pomoći smrznutog firmvera.

## Brzi pregled

| Cilj | Kombinacija | USB |
|---|---|---|
| Ponovno pokretanje smrznutog Flippera | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | bilo kako |
| Hardverski reset napajanja | <kbd>BACK</kbd>, 30 s | **odspojen** |
| DFU putem Flipper bootloadera (s indikacijom) | <kbd>←</kbd> + <kbd>BACK</kbd>, otpustite <kbd>BACK</kbd>, držite <kbd>←</kbd> do plave LED diode | bilo kako |
| DFU putem ST bootloadera (bez indikacije) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, otpustite <kbd>BACK</kbd> i <kbd>←</kbd> | bilo kako |
| Zaslon za poništavanje PIN-a / postavki | držite <kbd>↑</kbd> dok se Flipper pokreće | — |

## Osnovne kombinacije

### Hardverski reset

1. Pritisnite i držite <kbd>←</kbd> i <kbd>BACK</kbd> nekoliko sekundi.
2. Otpustite obje tipke.

Time se linija reseta mikrokontrolera povlači na nisku razinu. Put: tipke → DD8 (NC7SZ32M5X, OR vrata) → DD1 (STM32WB55, MCU).

**Ne radi ako:** je aktivan debug blok MCU-a koji iznutra drži liniju reseta.

### Hardverski reset napajanja

1. Odspojite USB kabel i svako vanjsko napajanje. Dobro provjerite je li USB doista odspojen.
2. Pritisnite i držite <kbd>BACK</kbd> **30 sekundi**. Ovo radi samo kada je USB odspojen.
3. Otpustite <kbd>BACK</kbd>.

Time se linija napajanja SYS isključuje i ponovno uključuje putem čipa za punjenje DD6 (bq25896).

**Ne radi ako:** je napajanje spojeno na USB ili 5V_ext.

### Softverski DFU

Držite <kbd>←</kbd> dok se Flipper pokreće. Uređaj ulazi u DFU način putem **Flipper bootloadera**.

**Ne radi ako:** je Flipper bootloader oštećen ili nedostaje.

### Hardverski DFU

Držite <kbd>OK</kbd> dok se Flipper pokreće. Uređaj ulazi u DFU način putem **ST bootloadera** ugrađenog u MCU.

**Ne radi ako:** su Option Bytes oštećeni ili postavljeni tako da zanemaruju tipku <kbd>OK</kbd>.

## DFU kombinacije

### Hardverski reset + softverski DFU

1. Držite <kbd>←</kbd> + <kbd>BACK</kbd> nekoliko sekundi.
2. Otpustite <kbd>BACK</kbd>.
3. Uređaj ulazi u DFU **s indikacijom**: plava LED dioda i DFU zaslon.
4. Otpustite <kbd>←</kbd>.

**Ne radi ako:** debug blok MCU-a drži liniju reseta ili je Flipper bootloader oštećen odnosno nedostaje.

### Hardverski reset + hardverski DFU

1. Držite <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> nekoliko sekundi.
2. Otpustite <kbd>BACK</kbd> i <kbd>←</kbd>.
3. Uređaj ulazi u DFU **bez indikacije**. Zaslon ostaje prazan. To je uobičajeno.

**Ne radi ako:** debug blok MCU-a drži liniju reseta ili su Option Bytes oštećeni odnosno postavljeni tako da zanemaruju <kbd>OK</kbd>.

### Hardverski reset napajanja + softverski DFU

1. Odspojite USB i svako vanjsko napajanje.
2. Držite <kbd>BACK</kbd> + <kbd>←</kbd> 30 sekundi.
3. Otpustite <kbd>BACK</kbd>.
4. Uređaj ulazi u DFU s indikacijom (plava LED dioda + DFU zaslon).
5. Otpustite <kbd>←</kbd>.
6. Priključite USB.

**Ne radi ako:** je napajanje spojeno na USB ili 5V_ext, ili je Flipper bootloader oštećen odnosno nedostaje.

### Hardverski reset napajanja + hardverski DFU

1. Odspojite USB i svako vanjsko napajanje.
2. Držite <kbd>BACK</kbd> + <kbd>OK</kbd> 30 sekundi.
3. Otpustite <kbd>BACK</kbd> i <kbd>OK</kbd>.
4. Uređaj ulazi u DFU bez indikacije.
5. Priključite USB.

**Ne radi ako:** je napajanje spojeno na USB ili 5V_ext, ili su Option Bytes oštećeni odnosno postavljeni tako da zanemaruju <kbd>OK</kbd>.

## Što učiniti u DFU načinu

Povežite Flipper s računalom. Pojavit će se kao **DFU in FS Mode** (Windows/macOS) ili **STMicroelectronics STM Device in DFU Mode** (`lsusb` na Linuxu). Zatim popravite firmver putem qFlippera: [Oporavak](/hr/start/recovery#firmware-recovery).

## Ako ništa ne pomaže {#if-nothing-helps}

- Provjerite je li baterija napunjena: ostavite uređaj na punjaču sat vremena.
- Odspojite bateriju pa je ponovno spojite (zahtijeva otvaranje kućišta).
- Snimite firmver pomoću ST-Linka ili drugog SWD programatora.

Ako uređaj ni nakon svega toga ne radi, problem **nije softverski**.
