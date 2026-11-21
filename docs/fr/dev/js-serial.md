---
title: "JavaScript : serial (UART)"
sidebarTitle: "JS : serial"
order: 340
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_serial.md]
sources: [unleashed-docs]
---
# Module serial

Le module `serial` envoie et reçoit des données via les ports UART du Flipper présents sur le connecteur GPIO.
Utilisez-le pour dialoguer avec des routeurs, des cartes ESP32, des modules GPS, des consoles de débogage, etc.

```js
let serial = require("serial");
```

| Nom du port | Broches |
|---|---|
| `"usart"` | TX = 13, RX = 14 |
| `"lpuart"` | TX = 15, RX = 16 |

Voir [Brochage GPIO](/fr/gpio/pinout). N'oubliez pas : l'UART du Flipper est en 3,3 V.

Scripts d'exemple : `uart_echo.js`, `uart_echo_8e1.js`, `bad_uart.js` dans `/ext/apps/Scripts/js_examples/`.

## Méthodes

### setup()
Configure le port série. Appelez-la **avant toutes les autres méthodes**. Elle désactive automatiquement le service
des modules d'extension afin d'éviter les interférences.

**Paramètres :**

- nom du port : `"usart"` ou `"lpuart"` ;
- débit en bauds ;
- objet de trame facultatif, par ex. `{ dataBits: "8", parity: "even", stopBits: "1" }` :
  - `dataBits` : `"6"`, `"7"`, `"8"`, `"9"`. 6 bits de données uniquement avec la parité activée (even ou odd) ;
    9 bits de données uniquement avec la parité désactivée (none) ;
  - `parity` : `"none"`, `"even"`, `"odd"` ;
  - `stopBits` : `"0.5"`, `"1"`, `"1.5"`, `"2"`. LPUART ne prend en charge que les bits d'arrêt entiers (1 et 2, pas
    0.5 ni 1.5).

```js
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

### write()
Écrit des données sur le port.

**Paramètres :** un ou plusieurs arguments de ces types :

- une chaîne ;
- un nombre unique, interprété comme un octet ;
- un tableau de nombres, chacun interprété comme un octet ;
- un `ArrayBuffer` ou un `DataView`.

```js
serial.write(0x0a); // Write a single byte 0x0A
serial.write("Hello, world!"); // Write a string
serial.write("Hello, world!", [0x0d, 0x0a]); // Write a string followed by two bytes
```

### read()
Lit un nombre fixe de caractères.

**Paramètres :** nombre d'octets à lire ; *(facultatif)* délai d'attente en ms.

**Renvoie :** une chaîne de caractères reçus, ou `undefined` si rien n'a été reçu avant l'expiration du délai.

```js
serial.read(1); // Read a single byte, without timeout
serial.read(10, 5000); // Read 10 bytes, with 5s timeout
```

### readln()
Lit jusqu'à un caractère de fin de ligne.

**Paramètres :** *(facultatif)* délai d'attente en ms.

**Renvoie :** une chaîne, ou `undefined` si rien n'a été reçu avant l'expiration du délai.

```js
serial.readln(); // Read without timeout
serial.readln(5000); // Read with 5s timeout
```

### readAny()
Lit la quantité de données disponible, quelle qu'elle soit. Cela évite qu'une boucle s'enlise sur de nombreuses
petites lectures.

**Paramètres :** *(facultatif)* délai d'attente en ms.

**Renvoie :** une chaîne, ou `undefined` si rien n'a été reçu avant l'expiration du délai.

```js
serial.readAny(); // Read without timeout
serial.readAny(5000); // Read with 5s timeout
```

### readBytes()
Lit un nombre fixe d'octets sous forme de données binaires.

**Paramètres :** nombre d'octets à lire ; *(facultatif)* délai d'attente en ms.

**Renvoie :** un `ArrayBuffer` contenant les données reçues, ou `undefined` si rien n'a été reçu avant l'expiration
du délai.

```js
serial.readBytes(4); // Read 4 bytes, without timeout

// Read one byte from receive buffer with zero timeout, returns UNDEFINED if Rx buffer is empty
serial.readBytes(1, 0);
```

::: info
La documentation d'origine décrit `readBytes()` comme « lire jusqu'à un saut de ligne ». C'est une erreur de
copier-coller : comme le montrent ses paramètres, elle lit le nombre d'octets indiqué.
:::

### expect()
Recherche un motif dans le flux de données entrant.

**Paramètres :**

- un motif unique ou un tableau de motifs, chacun étant :
  - une chaîne, ou
  - un tableau de nombres (octets) ;
- *(facultatif)* délai d'attente en ms.

**Renvoie :** l'indice du motif trouvé dans la liste, ou `undefined` si rien ne correspond.

```js
// Wait for root shell prompt with 1s timeout, returns 0 if it was received before timeout, undefined if not
serial.expect("# ", 1000);

// Infinitely wait for one of two strings, should return 0 if the first string got matched, 1 if the second one
serial.expect([": not found", "Usage: "]);
```

### end()
Désinitialise le port, pour qu'il puisse être reconfiguré dans le même script.

```js
serial.end();
// Configure LPUART port with baudrate = 115200
serial.setup("lpuart", 115200);
```

## Pages liées

- [GPIO](/fr/dev/js-gpio)
- `bad_uart.js` montre `expect()` à l'œuvre : il attend l'invite d'un shell root Linux (`# `) sur LPUART et lui envoie
  des commandes.
