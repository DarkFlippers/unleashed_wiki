---
title: Módulos y sus apps
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Módulos y sus apps

Lo que puedes conectar al GPIO y la app que lo maneja. Primero los módulos que tienen página propia; después, las
apps de la comunidad que vienen en los paquetes, cada una con enlace a su código y a su README.

La columna **Paquete** dice si la app ya está en tu Flipper:

| Paquete | En qué compilación está |
|---|---|
| Base | en la compilación `e` y en la que no lleva sufijo |
| Extra | solo en la compilación `e` |

La compilación `c` no trae apps. Cualquiera de los dos paquetes se puede añadir a mano desde las
[releases de los paquetes](https://github.com/xMasterX/all-the-plugins/releases/latest) — mira
[Catálogo de apps](/es/apps/catalog).

::: warning
Son apps de la comunidad. El contenido de los paquetes cambia de una release a otra, y una app puede desaparecer si
deja de compilar con la API actual. La etiqueta de compilación de los paquetes aparece al principio de cada changelog.
:::

::: tip Antes de conectar nada
En [Pinout del GPIO](/es/gpio/pinout) está el voltaje y la corriente que aguanta cada pin, y en
[Módulos externos](/es/gpio/external-modules#pin-conflicts), qué pines ya están ocupados. Dos módulos en el mismo bus
no funcionan a la vez.
:::

## Módulos que tienen página propia {#covered}

| Módulo | Lo maneja | Página |
|---|---|---|
| CC1101 externo (Sub-GHz) | la app Sub-GHz integrada | [CC1101 externo](/es/subghz/external-cc1101) |
| Placas Wi-Fi ESP32 / ESP8266 | las apps de abajo más el firmware de la placa | [ESP32 y Wi-Fi](/es/gpio/esp32) |
| Wi-Fi Developer Board | sonda de depuración y logs | [Dev board](/es/gpio/devboard) |
| nRF24L01 | las apps de abajo | [NRF24](/es/gpio/nrf24) |
| SIM800 GSM | la app SIM800 integrada | [SIM800](/es/gpio/sim800) |
| GPS (NMEA) | las apps de abajo | [GPS](/es/gpio/gps) |
| Video Game Module | el firmware más las apps de abajo | [Video Game Module](/es/gpio/video-game-module) |
| Módulos de expansión | `Settings → Expansion Modules` | [Módulos de expansión](/es/gpio/expansion-modules) |

## Wi-Fi y placas ESP {#esp}

| App | Paquete | Qué hace |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Interfaz para el firmware Marauder: escaneo de Wi-Fi y BLE, captura de paquetes, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Lista las redes Wi-Fi cercanas, para el firmware Scanner en ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Interfaz para el firmware DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Imagen en directo de una ESP32-CAM en la pantalla del Flipper, con captura de fotos |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Segunda app para ESP32-CAM: imagen en directo y fotos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Interfaz para el firmware Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Monta en el ESP32 un punto de acceso con portal cautivo |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Para el firmware Deauther v2 de @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Graba firmware en una placa ESP desde el Flipper, por UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Dispara un webhook de IFTTT a través de un ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Mapeo de redes Wi-Fi con un ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Muestra la cara y el estado de un Pwnagotchi en el Flipper, por UART |

## 2,4 GHz: nRF24L01 {#nrf}

| App | Paquete | Qué hace |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Recoge direcciones de teclados inalámbricos para Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Inyecta pulsaciones en el receptor vulnerable de un teclado o ratón inalámbrico |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Utilidad general para el nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Busca y decodifica paquetes nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Muestra qué canales de 2,4 GHz están ocupados |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Lee y escribe campos con nombre de un dispositivo nRF24 según un archivo de configuración |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Otra versión del Sniffer de arriba |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Otra versión del Mouse Jacker de arriba |

## Sensores {#sensors}

| App | Paquete | Qué hace |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: sensores de temperatura, humedad y presión (DHT, DS18B20, BMP/BME y más) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Fotómetro para fotografía, BH1750 por I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Distancia con un sensor de ultrasonidos HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Distancia con un sensor de ultrasonidos Parallax PING))) (3 cables) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Movimiento con un módulo de radar doppler RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 con un sensor MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Partículas en el aire con un sensor Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Alcoholímetro con sensor MQ-3, con calibración del cero |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Tensión y corriente de los sensores TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variómetro para parapente y senderismo, sensor de presión BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Lee un acelerómetro de dos ejes Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Contador de pasos sobre el mismo módulo Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Ratón manejado por un sensor de movimiento BMI160 o LSM6DS |

## Radiación {#rad}

| App | Paquete | Qué hace |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Cuentas de un tubo Geiger J305 en una placa externa |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Dados tirados con la misma placa Geiger; sin la placa no funciona |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Funciona con el módulo RadSens |

## Pantallas, LED y radio {#disp}

| App | Paquete | Qué hace |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Maneja un display de 7 segmentos desde los pines GPIO |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Herramienta de diagnóstico para pantallas OLED SSD1306 por I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Comprueba que los LED direccionables WS2812B funcionan |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Controla un módulo de radio FM TEA5767 |

## Chips de memoria {#mem}

| App | Paquete | Qué hace |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Lee y escribe chips de flash SPI de la serie 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Gestión del bloqueo de tarjetas SD por SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | EEPROM 24Cxx por I2C: leer, escribir, borrar, volcar y restaurar |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Lee y escribe la EEPROM de algunas cafeteras |

## Depuración y programación {#probe}

| App | Paquete | Qué hace |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Convierte el Flipper en una sonda de depuración CMSIS-DAP para ARM |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | Sonda ARM Single Wire Debug |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Emula un FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Graba microcontroladores AVR por ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Depurador y grabador para el WCH CH32V003 |

## Buses, red y terminales {#bus}

| App | Paquete | Qué hace |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Escanea el bus I2C y lee o escribe registros |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminal para hablar con un dispositivo SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminal para cualquier dispositivo en UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Herramientas para el bus CAN, necesita una placa CAN |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Conjunto de herramientas para el bus CAN de Tesla, necesita la misma placa CAN |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Comprueba una conexión Ethernet a través de un módulo W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | Probador de LAN en el mismo módulo: ARP, ping, DHCP, escaneo de puertos, SNMP y más |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminal para un módulo LoRa |

## Medición y señales {#meas}

| App | Paquete | Qué hace |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper como Openbench Logic Sniffer, para PulseView en el ordenador |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Osciloscopio en el pin 16 (PC0), de 0 a 2,5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Genera señales digitales en los pines GPIO |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | PWM de servo en el pin A7, con modos Manual, Center y Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Un segundo probador de servos, también en el pin A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervalómetro: dispara una cámara a través de los pines GPIO |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Decodifica señales horarias de onda larga (DCF77 y similares) |

## Control de acceso, banda magnética y UHF RFID {#access}

| App | Paquete | Qué hace |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Lee formatos Wiegand de W4 a W48 desde un lector o un teclado, los guarda y los reproduce |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Transmite datos de banda magnética por el aire mediante una bobina |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID a través de un módulo YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Para lectores M6E Nano, M7E Hecto y YRM1000; lee muchas etiquetas a la vez |

## GPS {#gps}

| App | Paquete | Qué hace |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Posición de cualquier módulo GPS NMEA en UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Muestra y registra datos de módulos GPS u-blox por I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Rastreador NMEA con navegación por puntos |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Explorador que ordena tus archivos por distancia desde donde estás |

## Hardware de juego y retro {#game}

| App | Paquete | Qué hace |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Instala y actualiza el firmware del Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Ratón por aire con el sensor de movimiento del Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Imagen del juego y reenvío de los controles a través del módulo |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Intercambia Pokémon con una Game Boy, generaciones I y II, juegos no japoneses |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper como mando de ColecoVision, con un módulo RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analiza el protocolo de los mandos de expansión de Wii |

## Sin módulo: solo pines {#bare}

| App | Paquete | Qué hace |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Control visual de los pines de uso general |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Muestra en pantalla el estado de cada pin |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Una segunda app para leer el estado de los pines |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Pita cuando un cable tiene continuidad |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Pone 3,3 V en el pin 7 (C3) y los deja puestos al salir |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Abre cajas fuertes electrónicas Sentry Safe y Master Lock con dos cables |

## Ver también {#related}

- [Pinout del GPIO](/es/gpio/pinout) — qué puede hacer cada pin y cuánta corriente da
- [Módulos externos](/es/gpio/external-modules) — buses, conflictos de pines e IR externo
- [App GPIO](/es/gpio/gpio-app) — el control de pines integrado, el puente UART y el comando `i2c`
- [Catálogo de apps](/es/apps/catalog) — los paquetes y cómo instalar uno a mano
- [Apps en la tarjeta SD](/es/apps/sd-card-apps) — instalar un `.fap` suelto y hacer coincidir las versiones de API
