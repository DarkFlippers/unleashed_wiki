---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** es una aplicación de fuerza bruta de códigos estáticos del equipo de Unleashed. Recorre los códigos posibles de un protocolo de código fijo y los transmite uno tras otro. Puedes usar un protocolo preconfigurado de su lista, o cargar tu propio fichero `.sub` y elegir qué bytes iterar.

::: warning
Úsala únicamente con tus propios equipos o con permiso explícito. Aplicar fuerza bruta a la cancela o la barrera de otra persona es ilegal en la mayoría de los países.
:::

::: tip Unleashed
La aplicación no forma parte de la imagen del firmware ni está en su árbol de código fuente. Se distribuye como aplicación externa (`.fap`) en los packs de aplicaciones de Unleashed, compilada a partir de [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Instala el pack (véase [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps)) y búscala en `Apps → Sub-GHz`.
:::

## Cuándo tiene sentido

- **Solo con código estático (fijo).** La fuerza bruta funciona únicamente cuando el receptor acepta el mismo código indefinidamente, como ocurre con CAME de 12 bits, Nice Flo de 12 bits, los mandos de estilo Princeton y otros similares con microinterruptores. Un receptor de código rodante (KeeLoq, Nice Flor-S, CAME Atomo y otros) nunca acepta un código adivinado, así que la fuerza bruta es inútil ahí (véase [Códigos rodantes](/es/subghz/rolling-codes)).
- **Has perdido el mando de tu propio aparato de código estático** y no conoces su código, o quieres comprobar con qué rapidez se puede adivinar tu propio sistema de código fijo.

Si todavía tienes un mando que funciona, es mucho más rápido simplemente [leerlo](/es/subghz/read).

## Cómo se usa

### Protocolos preconfigurados

1. Abre `Apps → Sub-GHz` e inicia la aplicación Bruteforce.
2. Elige un protocolo de la lista.
3. Para cambiar cuántas veces se repite cada código, pulsa <kbd>→</kbd> sobre el protocolo seleccionado.
4. Inicia el ataque y mantén el Flipper cerca del receptor hasta que reaccione.

### Tu propio fichero

1. Guarda primero una señal del protocolo objetivo, por ejemplo con [Read](/es/subghz/read) o [Add Manually](/es/subghz/add-manually).
2. En la aplicación, carga ese fichero `.sub`.
3. Selecciona los bytes de la clave a los que quieres aplicar fuerza bruta. Los demás bytes se mantienen tal cual están en el fichero.
4. Inicia el ataque.

### Retardo entre señales

El retardo entre los códigos transmitidos se fija en la pantalla principal de la aplicación. **Mantén <kbd>↑</kbd>** allí (la indicación en pantalla dice "Up to Save") para guardarlo. Un retardo más corto termina antes, pero algunos receptores pierden códigos que llegan demasiado seguidos.

## Consejos y errores habituales

- **Frecuencia o modulación incorrectas**: el receptor no oye nada. Comprueba primero la banda con el [Frequency Analyzer](/es/subghz/frequency-analyzer).
- **Demasiadas pocas repeticiones**: muchos receptores necesitan que un código se repita varias veces antes de actuar. Aumenta las repeticiones con <kbd>→</kbd> sobre el protocolo.
- **Tarda mucho**: el número de códigos crece exponencialmente con el número de bits. Los códigos de 12 bits son rápidos, mientras que las claves más largas pueden tardar un tiempo inviable. Reduce la búsqueda aplicando fuerza bruta solo a los bytes desconocidos de tu propio fichero.
- **La transmisión está bloqueada**: la frecuencia está fuera del rango permitido. Véase [Frecuencias](/es/subghz/frequencies).

## Páginas relacionadas

- [Sistemas compatibles](/es/subghz/supported-systems): qué protocolos son estáticos
- [Add Manually](/es/subghz/add-manually)
- [Formato de fichero .sub](/es/subghz/file-format)
