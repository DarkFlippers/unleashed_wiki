---
title: Formato tarball heatshrink
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Formato de tarball comprimido con Heatshrink

El Flipper puede leer archivos `.tar` comprimidos con la biblioteca
[Heatshrink](https://github.com/atomicobject/heatshrink). Esto reduce el tamaño de los paquetes de actualización y
acelera las actualizaciones OTA — los recursos de la tarjeta SD de cada paquete de actualización
(`resources.ths`) usan este formato.

Heatshrink en sí no define ningún contenedor para sus parámetros de compresión, así que el Flipper añade una cabecera
pequeña.

## Estructura del archivo

| Desplazamiento | Tamaño | Campo | Valor |
|--:|--:|---|---|
| 0 | 4 bytes | Magic | `0x48 0x53 0x44 0x53` — en ASCII `HSDS` («HeatShrink DataStream») |
| 4 | 1 byte | Versión | `0x01` |
| 5 | 1 byte | Tamaño de ventana | Logaritmo en base 2 del tamaño de la ventana deslizante; igual que `-w` en la CLI de Heatshrink |
| 6 | 1 byte | Tamaño de lookahead | Logaritmo en base 2 del tamaño del búfer de lookahead; igual que `-l` en la CLI de Heatshrink |
| 7 | … | Datos | Flujo comprimido con Heatshrink |

La cabecera ocupa **7 bytes** en total. Dentro del flujo comprimido hay un archivo tar normal sin comprimir (USTAR).

## Cómo lo crean las herramientas del firmware

Según `scripts/flipper/assets/tarball.py` y `heatshrink_stream.py`:

- extensión: `.ths` («.Tar.HeatShrink»);
- parámetros por defecto: ventana `13`, lookahead `6`;
- la cabecera se empaqueta como `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (el magic es un entero de
  32 bits little-endian, lo que da los bytes `48 53 44 53` en disco);
- el tar es USTAR, con uid/gid `0`, mtime `0`, nombre de usuario y de grupo `furippa` y los archivos basura de macOS
  filtrados.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Usarlo en el dispositivo

La biblioteca tar del firmware abre los archivos `.ths` en un modo *heatshrink* de solo lectura, elegido
automáticamente según la extensión del archivo. Así, la [CLI](/es/dev/cli#storage) puede desempaquetarlos
directamente:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Páginas relacionadas

- [Actualizaciones OTA](/es/dev/ota)
- [Interfaz de línea de comandos](/es/dev/cli)
