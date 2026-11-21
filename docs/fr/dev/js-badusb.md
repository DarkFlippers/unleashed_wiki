---
title: "JavaScript : BadUSB"
sidebarTitle: "JS : badusb"
order: 290
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_badusb.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_badusb.c]
sources: [unleashed-docs, unleashed-src]
---
# Module BadUSB

Le module `badusb` transforme le Flipper Zero en clavier USB (HID) piloté depuis JavaScript. C'est une alternative
scriptable aux [fichiers DuckyScript BadUSB](/fr/badusb/script-format) classiques : vous disposez de variables, de
boucles et de tous les autres modules JS (GUI, storage, serial) dans le même script.

```js
let badusb = require("badusb");
```

::: warning
À n'utiliser que sur des ordinateurs qui vous appartiennent ou que vous êtes autorisé à tester.
:::

Script d'exemple : `/ext/apps/Scripts/js_examples/badusb_demo.js`.

## Méthodes

### setup()
Démarre l'USB HID, éventuellement avec des paramètres personnalisés. Appelez-la **avant toutes les autres méthodes**.

**Paramètres :** objet de configuration facultatif :

- `vid`, `pid` (nombre) : VID et PID ; s'ils sont utilisés, les deux sont obligatoires ;
- `mfrName` (chaîne) : nom du fabricant (32 caractères ASCII maximum), facultatif ;
- `prodName` (chaîne) : nom du produit (32 caractères ASCII maximum), facultatif ;
- `layoutPath` (chaîne) : chemin vers un fichier de disposition clavier, facultatif.

```js
// Start USB HID with default parameters
badusb.setup();
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer and product strings not defined
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB }); 
// Start USB HID with custom vid:pid = AAAA:BBBB, manufacturer string = "Flipper Devices", product string = "Flipper Zero"
badusb.setup({ vid: 0xAAAA, pid: 0xBBBB, mfrName: "Flipper Devices", prodName: "Flipper Zero" });
```

Les dispositions clavier sont les mêmes fichiers `.kl` que ceux utilisés par l'application BadUSB (dans
`/ext/badusb/assets/layouts/`), par ex. `layoutPath: "/ext/badusb/assets/layouts/de-DE.kl"`.

### isConnected()
Renvoie l'état de la connexion USB.

```js
if (badusb.isConnected()) {
    // Do something
} else {
    // Show an error
}
```

### press()
Appuie puis relâche une touche ou une combinaison de touches.

**Paramètres :** noms de touches ou de modificateurs, ou codes de touches. Voir la
[liste des noms de touches](#key-names).

```js
badusb.press("a"); // Press "a" key
badusb.press("A"); // SHIFT + "a"
badusb.press("CTRL", "a"); // CTRL + "a"
badusb.press("CTRL", "SHIFT", "ESC"); // CTRL + SHIFT + ESC combo
badusb.press(98); // Press key with HID code (dec) 98 (Numpad 0 / Insert)
badusb.press(0x47); // Press key with HID code (hex) 0x47 (Scroll lock)
```

### hold()
Maintient une touche enfoncée. Jusqu'à 5 touches (sans compter les modificateurs) peuvent être maintenues en même
temps.

**Paramètres :** identiques à `press()`.

```js
badusb.hold("a"); // Press and hold "a" key
badusb.hold("CTRL", "v"); // Press and hold CTRL + "v" combo
```

### release()
Relâche une touche précédemment maintenue. Appelée **sans paramètre**, elle relâche toutes les touches.

**Paramètres :** identiques à `press()`.

```js
badusb.release(); // Release all keys
badusb.release("a"); // Release "a" key
```

### print()
Saisit une chaîne.

**Paramètres :** la chaîne ; *(facultatif)* délai entre les appuis de touches, en ms.

```js
badusb.print("Hello, world!"); // print "Hello, world!"
badusb.print("Hello, world!", 100); // Add 100ms delay between key presses
```

### println()
Comme `print()`, suivi d'un appui sur <kbd>ENTER</kbd>.

```js
badusb.println("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### altPrint()
Saisit une chaîne avec la méthode **Alt+pavé numérique**, qui fonctionne indépendamment de la disposition clavier
configurée sur l'hôte. **Windows uniquement.**

**Paramètres :** la chaîne ; *(facultatif)* délai entre les appuis de touches, en ms.

```js
badusb.altPrint("Hello, world!"); // print "Hello, world!"
badusb.altPrint("Hello, world!", 100); // Add 100ms delay between key presses
```

### altPrintln()
Comme `altPrint()`, suivi d'un appui sur <kbd>ENTER</kbd>.

```js
badusb.altPrintln("Hello, world!");  // print "Hello, world!" and press "ENTER"
```

### quit() {#quit}
Libère l'USB. Facultatif, mais cela permet au script de basculer vers un autre mode USB, par exemple le module
`usbdisk`.

```js
badusb.quit();
usbdisk.start(...)
```

::: tip Unleashed
`usbdisk` (émulation de stockage de masse USB) est un module JS propre à Unleashed ; voir
[Présentation de JavaScript](/fr/dev/js-about#unleashed-extras).
:::

## Noms de touches {#key-names}

### Touches modificatrices

| Nom |
|---|
| CTRL |
| SHIFT |
| ALT |
| GUI |

### Touches spéciales

| Nom | Remarques |
|---|---|
| DOWN | Flèche bas |
| LEFT | Flèche gauche |
| RIGHT | Flèche droite |
| UP | Flèche haut |
| ENTER | |
| DELETE | |
| BACKSPACE | |
| END | |
| HOME | |
| ESC | |
| INSERT | |
| PAGEUP | |
| PAGEDOWN | |
| CAPSLOCK | |
| NUMLOCK | |
| SCROLLLOCK | |
| PRINTSCREEN | |
| PAUSE | Touche Pause/Attn |
| SPACE | |
| TAB | |
| MENU | Touche de menu contextuel |
| Fx | Touches F1-F24 |
| NUMx | Touches NUM0-NUM9 |

## Pages liées

- [Utilisation de Bad USB](/fr/badusb/usage) et [format des scripts](/fr/badusb/script-format)
- [Boucle d'événements](/fr/dev/js-event-loop), [GUI](/fr/dev/js-gui) pour des menus de charge utile interactifs
