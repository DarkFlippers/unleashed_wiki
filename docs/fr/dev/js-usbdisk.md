---
title: "JavaScript : usbdisk"
sidebarTitle: "JS : usbdisk"
order: 430
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_usbdisk]
sources: [unleashed-src]
---
# Module stockage de masse USB

Un extra Unleashed, absent du firmware d'origine. Il fait passer le Flipper pour une clé USB auprès d'un PC. Le contenu vient d'un fichier image sur la carte SD ; le PC lit et écrit les blocs directement dans ce fichier.

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
```

Script d'exemple : `/ext/apps/Scripts/js_examples/usbdisk.js`.

`createImage()` crée une image vide, ou vous copiez vous-même un `.img` dans `/ext/apps_data/mass_storage/`. Le fichier est lu par blocs de 512 octets, sa taille doit donc être un multiple de 512.

Si le script a utilisé BadUSB avant, appelez d'abord [`badusb.quit()`](/fr/dev/js-badusb#quit) pour libérer le port USB.

## Méthodes

### createImage()
Crée une image vide à la taille demandée. La place est seulement réservée, pas écrite, donc même une grosse image est rapide. Les 4 premiers Ko sont mis à zéro pour que le PC propose de formater le nouveau disque. Lève une erreur si quelque chose se trouve déjà à ce chemin, ou si la carte est trop pleine.

- **Paramètres :** `path`, où mettre l'image ; `size`, sa taille en octets, arrondie au bloc de 512 octets inférieur.

### start()
Ouvre l'image en lecture-écriture et connecte le lecteur au PC. Le nom du lecteur est celui du fichier image sans son extension. Lève une erreur si le fichier est absent ou si un disque tourne déjà.

- **Paramètres :** `path`, le chemin complet de l'image, par ex. `"/ext/apps_data/mass_storage/128MB.img"`.

### stop()
Déconnecte le lecteur et ferme le fichier. Se fait aussi à la fin du script.

### wasEjected()
- **Renvoie :** un booléen, `true` dès que le PC a éjecté le lecteur. Servez-vous-en comme condition de boucle. Lève une erreur si le disque ne tourne pas.

## Exemple

```js
checkSdkFeatures(["usbdisk"]);
let usbdisk = require("usbdisk");
let storage = require("storage");

let imagePath = "/ext/apps_data/mass_storage/128MB.img";
if (!storage.fileExists(imagePath)) {
    usbdisk.createImage(imagePath, 128 * 1024 * 1024);
}

print("Starting UsbDisk...");
usbdisk.start(imagePath);

print("Started, waiting until ejected...");
while (!usbdisk.wasEjected()) {
    delay(1000);
}

print("Ejected, stopping UsbDisk...");
usbdisk.stop();
```

::: tip
`createImage()` est arrivé après le reste du module. Un script qui peut aussi tourner sur un build plus ancien devrait d'abord tester `doesSdkSupport(["usbdisk-createimage"])`, comme le fait l'exemple fourni.
:::

## Pages liées

- [Module BadUSB](/fr/dev/js-badusb) — `quit()` libère l'USB pour ce module
- [Module storage](/fr/dev/js-storage) — vérifier que l'image existe avant de démarrer
- [JavaScript : présentation](/fr/dev/js-about)
