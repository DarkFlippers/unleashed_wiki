---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

El Flipper Zero lleva integrado un transceptor **CC1101** y una antena para las bandas por debajo de 1 GHz. Con él
puedes leer, guardar y reproducir las señales de mandos de garaje y de cancela, barreras, persianas enrollables,
timbres, sensores inalámbricos y otros aparatos que funcionan en los rangos de **300–348 MHz, 387–464 MHz y
779–928 MHz**. La mayoría de los mandos que te encontrarás usan **315 MHz**, **433.92 MHz** o **868.35 MHz**.

La aplicación está en `Main Menu → Sub-GHz`. Su menú principal en Unleashed:

![Menú principal de Sub-GHz: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Elemento de menú | Qué hace | Página |
|---|---|---|
| `Read` | Decodifica mandos de protocolos conocidos, los guarda y los envía | [Read](/es/subghz/read) |
| `Read RAW` | Graba la señal en bruto de cualquier mando y la reproduce | [Read RAW](/es/subghz/read-raw) |
| `Saved` | Ficheros `.sub` guardados: Emulate, Rename, Delete y Signal Settings con Debug activado | [Read](/es/subghz/read) |
| `Add Manually` | Crea un mando completamente nuevo con un número de serie aleatorio | [Add Manually](/es/subghz/add-manually) |
| `Add Manually [Advanced]` | Lo mismo, pero escribes tú el serial, el botón, el contador y la semilla | [Add Manually](/es/subghz/add-manually) |
| `Frequency Analyzer` | Averigua en qué frecuencia transmite un mando | [Frequency Analyzer](/es/subghz/frequency-analyzer) |
| `Radio Settings` | Módulo interno / externo, potencia de TX, nombres de fichero, paso del contador | [Ajustes](/es/subghz/settings) |

::: tip Unleashed
La app Sub-GHz, su biblioteca de protocolos y el Frequency Analyzer vienen del firmware oficial. Unleashed elimina
las restricciones regionales de transmisión, añade frecuencias adicionales y más protocolos, permite guardar y enviar numerosos protocolos de código rodante, crea mandos de
código rodante nuevos que puedes registrar en tu receptor (`Add Manually`), usa las teclas de flecha como botones
adicionales del mando, admite un módulo CC1101 externo e incluye aplicaciones Sub-GHz extra (Remote Analyzer, Seed
Capturer, Nice O-Code, Security+ PIN, Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Usa estas funciones únicamente con tus propios equipos o para investigación lícita.
:::

## Primeros pasos

1. Averigua la frecuencia de tu mando — [Frequency Analyzer](/es/subghz/frequency-analyzer).
2. Intenta decodificarla — [Read](/es/subghz/read). Si se decodifica y el protocolo es **estático**, guárdala y ya
   has terminado.
3. Si es un mando de **código rodante**, no lo clones: lee [Códigos rodantes](/es/subghz/rolling-codes) y crea un
   mando nuevo con [Add Manually](/es/subghz/add-manually) + [Programar un mando nuevo](/es/subghz/remote-prog).
4. Si no se decodifica nada, grábala con [Read RAW](/es/subghz/read-raw).

## Todas las páginas

**Fundamentos**
- [Frecuencias](/es/subghz/frequencies) — bandas, listas por defecto, bloqueos regionales y rango ampliado
- [Frequency Analyzer](/es/subghz/frequency-analyzer) — localizar la frecuencia de un mando
- [Read](/es/subghz/read) — decodificar, guardar y enviar señales
- [Read RAW](/es/subghz/read-raw) — grabar señales en bruto

**Códigos rodantes y mandos nuevos**
- [Add Manually](/es/subghz/add-manually) — todos los protocolos del menú
- [Códigos rodantes](/es/subghz/rolling-codes) — conflictos de contador, botones personalizados
- [KeeLoq](/es/subghz/keeloq) — cómo funciona KeeLoq, claves de fabricante y semillas
- [Programar un mando nuevo](/es/subghz/remote-prog) — paso a paso para cada sistema
- [Modos de contador](/es/subghz/counter-mode) — el `CounterMode` experimental para clones
- [Signal Settings](/es/subghz/signal-settings) — modo de contador, contador y botón de una señal guardada
- [Sistemas compatibles](/es/subghz/supported-systems) — tabla completa de protocolos

**Configuración y hardware**
- [Ajustes](/es/subghz/settings) — Radio Settings, configuración de Read, frecuencias de usuario
- [Formato de fichero](/es/subghz/file-format) — `.sub`, presets, ficheros de ajustes de usuario
- [CC1101 externo](/es/subghz/external-cc1101) — módulos externos y amplificadores

**Aplicaciones**
- [Sub-GHz Remote](/es/subghz/remote) — hasta 5 señales en la cruceta
- [Sub-GHz Bruteforce](/es/subghz/bruteforce) — fuerza bruta de códigos estáticos
- [Remote Analyzer](/es/subghz/remote-analyzer) — decodificar un mando, protocolos adicionales
- [Nice O-Code](/es/subghz/nice-o-code) — recuperar el código de instalador
- [Security+ PIN](/es/subghz/secplus-pin) — el PIN del teclado de Security+ 2.0
- [Seed Capturer](/es/subghz/seed-capturer) — recopilar saltos para recuperar la semilla
- [Sub-GHz RAW Edit](/es/subghz/raw-editor) — recortar, unir y decodificar ficheros RAW

**Notas de campo**
- [ZKTeco CMP200](/es/subghz/zkteco-cmp200) — un mando Princeton camuflado

## Dónde se guardan los ficheros

| Ruta | Contenido |
|---|---|
| `/ext/subghz/` | Señales guardadas (`.sub`), grabaciones RAW |
| `/ext/subghz/assets/setting_user` | Tus propias frecuencias, lista del hopper, presets personalizados |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Tus propias claves de fabricante KeeLoq |
| `/ext/subghz/assets/dangerous_settings` | Interruptor del rango de frecuencias ampliado |
| `/ext/subghz_remote/` | Ficheros de mapa de la aplicación Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Capturas de Seed Capturer |
