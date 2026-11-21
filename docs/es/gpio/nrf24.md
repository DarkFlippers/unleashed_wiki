---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 GHz)

El **nRF24L01(+)** de Nordic Semiconductor es un transceptor de 2,4 GHz muy barato que se usa en muchos ratones y
teclados inalámbricos y en proyectos de aficionado. Se conecta al Flipper por SPI.

## Apps

El paquete Base trae el Sniffer y el Mouse Jacker, que son los que usa la guía de abajo. El paquete Extra añade seis más:

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

Driver, Sniffer y Mouse Jacker de [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Todas estas apps están en los
[paquetes de apps](https://github.com/xMasterX/all-the-plugins/releases/latest) — mira [Módulos y sus apps](/es/gpio/module-apps).

::: warning Aspectos legales
Solo para formación y para tu propio equipo. Inyectar pulsaciones de teclado en el ordenador de otra persona es
ilegal.
:::

## Cableado

| Pin del Flipper | Pin del nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8): déjalo sin conectar |

![Cableado del nRF24L01 al Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Patillaje de UberGuidoZ.*

El nRF24 usa los mismos pines SPI (2–5) que un [CC1101 externo](/es/subghz/external-cc1101). Conecta solo uno de
los dos a la vez, salvo que uses una placa combo diseñada para ambos (y entonces sigue su documentación).

## Uso

1. Apaga el Flipper, conecta el módulo y enciéndelo.
2. Abre **NRF24: Sniffer** (`Apps → GPIO`). Empieza el escaneo; usa los botones para cambiar de modo y de canal como
   se indica en la pantalla.
3. Espera a que el sniffer encuentre una **dirección**.
4. Abre **NRF24: Mouse Jacker**.
5. Selecciona la dirección y después abre el script de Bad USB que quieras enviar.
6. Las pulsaciones se transmiten al receptor USB objetivo.

Vídeo de demostración: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). La sintaxis de los scripts es la
misma que en [Bad USB](/es/badusb/script-format).

## Si el módulo va inestable

El nRF24 consume corriente a ráfagas cortas. Si solo funciona a veces, añade un condensador entre **VCC y GND**
justo en el módulo:

- Uno electrolítico de 3,3 µF a 10 µF (cuidado con la polaridad: el negativo a GND). Normalmente basta con uno de
  10 µF.
- Opcionalmente, uno cerámico de 0,1 µF en paralelo: el grande absorbe los cambios lentos y el pequeño los picos de
  conmutación rápida.

Las versiones «plus» (nRF24L01+PA+LNA) con amplificador lo necesitan aún más.

![Condensador en el módulo nRF24](/img/remote/218b238eb91c9e38.jpg)

## Créditos

- Técnica de sniffing: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Vulnerabilidades MouseJack: Marc Newlin, [investigación de Bastille](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- El driver está inspirado en [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html); el
  código de MouseJack, en [JackIt](https://github.com/insecurityofthings/jackit).

## Relacionado

- [Módulos externos](/es/gpio/external-modules)
- [Bad USB](/es/badusb/usage)
- [Patillaje GPIO](/es/gpio/pinout)
