---
title: Pinout GPIO
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# Pinout GPIO

Il Flipper Zero ha un connettore a 18 pin con passo 2,54 mm sul bordo superiore. Porta le uscite di alimentazione, la
massa, 13 pin di I/O collegati al microcontrollore STM32WB55, le linee di debug SWD e la linea 1-Wire condivisa con
l'iButton.

![Funzioni dei pin GPIO del Flipper Zero](/img/remote/b75cf29833cf8de8.jpg)

## Tabella dei pin

La numerazione parte dal **pin 1 (+5 V)**. I nomi delle porte (`PA7`, `PC0`, …) sono quelli che il firmware usa sullo
schermo e nella CLI.

| Pin | Nome | Funzioni principali | Note |
|---|---|---|---|
| 1 | +5V | Uscita di alimentazione a 5 V | Spenta a batteria finché non viene attivata, vedi sotto |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | MOSI del CC1101 / NRF24 esterno |
| 3 | PA6 | SPI MISO, ADC | MISO del CC1101 / NRF24 esterno |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | CS del CC1101 / NRF24 esterno; pin DE/RE per USB-UART |
| 5 | PB3 | SPI SCK | SCK del CC1101 / NRF24 esterno |
| 6 | PB2 | GPIO | GDO0 del CC1101 esterno, CE dell'NRF24 |
| 7 | PC3 | GPIO, ADC | Controllo dell'amplificatore del CC1101 esterno |
| 8 | GND | Massa | |
| 9 | 3V3 | Uscita di alimentazione a 3,3 V | Attiva per impostazione predefinita |
| 10 | PA14 | SWCLK | Debug (SWD) |
| 11 | GND | Massa | |
| 12 | PA13 | SWDIO | Debug (SWD) |
| 13 | PB6 | USART TX | UART predefinita per il bridge USB-UART, i log e i moduli di espansione |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Seconda UART; dati I2C esterni |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Seconda UART; clock I2C esterno |
| 17 | PB14 | 1-Wire | Linea iButton |
| 18 | GND | Massa | |

Il firmware marca i pin 10, 12, 13, 14 e 17 come **pin di debug**: sono nascosti in `GPIO Manual Control`, e il
comando CLI `gpio` li elenca solo con la modalità Debug attiva (chiedendo conferma prima di modificarli).

![Pinout GPIO dettagliato del Flipper Zero](/img/remote/e77df2d4499cbbbc.jpg)

Un PDF stampabile del pinout è disponibile sulla
[pagina GPIO ufficiale](https://docs.flipper.net/zero/gpio-and-modules).

## Limiti elettrici

- **Livello logico:** 3,3 V CMOS. Ogni pin di I/O raggiunge l'MCU attraverso una resistenza da 51 Ω ed è protetto
  dalle scariche elettrostatiche.
- **Corrente per pin:** fino a 20 mA.
- **Totale dai pin di I/O:** resta sotto i 5 W, altrimenti la protezione della batteria può scattare e il Flipper si
  spegne.
- **Tolleranza a 5 V:** valida solo per un pin configurato come **ingresso**. Un pin impostato come uscita non è
  tollerante a 5 V. Evita periferiche con logica a 5 V se non usi un level shifter. Dettagli nella application note ST
  [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3,3 V (pin 9)

- Attiva per impostazione predefinita, carico massimo **1,2 A**.
- La scheda microSD è alimentata dalla stessa linea. Il pin 9 viene disattivato brevemente durante gli aggiornamenti
  del firmware e quando la scheda viene montata.

::: warning
Collega moduli con un grande carico capacitivo solo con il Flipper spento, altrimenti rischi di corrompere i dati
sulla scheda microSD.
:::

### +5 V (pin 1)

- Da USB: quando un cavo è collegato, il pin 1 è alimentato direttamente dall'USB. Non assorbire mai più di
  **1,2 A**.
- Da batteria: l'uscita è **disattivata per impostazione predefinita**. Il convertitore boost (OTG) fornisce fino a
  **1,2 A** quando è attivo.

Per attivare i 5 V mentre il dispositivo è alimentato a batteria:

1. Apri `Main Menu → GPIO`.
2. Seleziona `5V on GPIO` e portalo su `ON` con <kbd>→</kbd>.

Altri modi per attivarli:

- CLI: `power 5v 1` / `power 5v 0` (vedi [CLI](/it/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` per i moduli IR esterni.
- App come Sub-GHz (CC1101 esterno) e [SIM800](/it/gpio/sim800) li richiedono automaticamente, e un
  [modulo di espansione](/it/gpio/expansion-modules) può chiederli attraverso il proprio protocollo.

::: tip Come il firmware gestisce i 5 V
Se richiedi i 5 V mentre è presente l'alimentazione USB, il servizio di alimentazione rinvia l'attivazione del
convertitore boost e lo accende da sé appena l'USB viene scollegata. Se il chip di ricarica segnala un errore OTG
(sovraccarico o cortocircuito), i 5 V vengono disattivati e la richiesta viene annullata, quindi devi riattivarli.
:::

## I pin in modalità DFU

In modalità DFU (bootloader) i pin di I/O, tranne il pin 17, cambiano stato secondo la application note
STMicroelectronics
[AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf)
(tabella "STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode"). Tienilo presente se un modulo reagisce
ai livelli dei pin mentre esegui il [ripristino](/it/start/recovery) del Flipper.

## Inserire un modulo

- **Senza custodia in silicone:** spingi il modulo a fondo, così che tra il Flipper e il modulo non si veda nessun
  pin. Potrebbe servire un po' di forza.
- **Con la custodia in silicone:** spingilo dentro finché non resta nessuno spazio al centro tra la custodia e il
  modulo.

![Modulo inserito a fondo](/img/remote/52e7045a797ed1c4.png)

## Argomenti correlati

- [App GPIO](/it/gpio/gpio-app)
- [Moduli esterni](/it/gpio/external-modules)
- [Schemi del Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)
