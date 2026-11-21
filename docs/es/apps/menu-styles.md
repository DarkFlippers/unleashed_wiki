---
title: Estilos del menú principal
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Estilos del menú principal

::: tip Unleashed
Unleashed permite cambiar cómo se dibuja el **menú principal** (la lista que aparece al pulsar <kbd>OK</kbd> en el
escritorio). Cada aspecto es un pequeño plugin incluido con el firmware; el firmware de fábrica solo tiene la lista
por defecto.
:::

## Elegir un estilo

1. Abre `Main Menu → Settings → Desktop`.
2. Baja hasta **Menu Style**.
3. Pulsa <kbd>←</kbd> / <kbd>→</kbd> para elegir un estilo. **Default** es el menú estándar.
4. Sal de Settings y pulsa <kbd>OK</kbd> en el escritorio: el menú se abre con el nuevo estilo.

## Estilos disponibles

| Estilo | Aspecto | Origen |
|---|---|---|
| Default | la lista estándar del Flipper | integrado |
| 3D | un carrusel 3D de iconos | adaptado por @apfxtech, basado en el menú de carrusel 3D para OLED de @upiir |
| C64 | pantalla de Commodore 64 | adaptado de Momentum, por Sil (@Sil333033) |
| Compact | una lista más densa | adaptado de Momentum, por @MatthewKuKanich |
| CoverFlow | carrusel al estilo de las portadas de álbumes | adaptado de Momentum, por Cody Tolene (@CodyTolene), refinado por @956MB |
| DSi | estilo Nintendo DSi | adaptado de Momentum, por Willy-JL |
| Grid | iconos en una cuadrícula | de @apfxtech |
| Macintosh | escritorio clásico de Mac OS | adaptado por @apfxtech, basado en Ardutosh de @jhhoward |
| PS4 | estilo PlayStation 4 | adaptado de Momentum, por Willy-JL |
| Vertical | lista vertical | adaptado de Momentum, por Willy-JL |
| Wii | cuadrícula de canales de Nintendo Wii | adaptado de Momentum, por Willy-JL |

En Settings los estilos se listan alfabéticamente después de **Default**. En todos los estilos <kbd>OK</kbd> abre la
app seleccionada y <kbd>Back</kbd> vuelve al escritorio.

## Dónde residen los estilos

Los estilos son plugins del cargador: archivos `.fal` llamados `menu_style_<name>.fal` en
`/ext/apps_data/loader/plugins/`. La lista **Menu Style** se construye con los archivos que se encuentran ahí, así
que:

- los estilos necesitan la **tarjeta SD**;
- un estilo aparece como **Missing** si se ha borrado el archivo seleccionado (reinstala el firmware para
  restaurarlo), y como **Unknown** si no se ha podido leer la tarjeta;
- si un estilo no se puede cargar, el Flipper recurre al menú por defecto.

::: info Para desarrolladores
Un estilo nuevo es un `FlipperAppType.PLUGIN` con `requires=["loader"]` y un `appid` que empieza por `menu_style_`; ese
prefijo es lo que usa Settings para distinguir los estilos de menú de otros plugins del cargador que están en la misma
carpeta. Consulta `applications/system/menu_styles/` en el código fuente del firmware y
[Manifiestos de app](/es/dev/app-manifests).
:::

## Páginas relacionadas

- [Escritorio](/es/start/desktop)
- [Ajustes](/es/start/settings)
- [Funciones de Unleashed](/es/start/unleashed-features)
