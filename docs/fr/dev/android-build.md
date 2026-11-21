---
title: Compiler des applications sur Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Compiler des applications sur Android (Termux + uFBT)

Mettez en place `ufbt` dans [Termux](https://termux.dev/) sur un téléphone Android ordinaire, non rooté, et compilez
des applications Flipper Zero (`.fap`) directement sur le téléphone — sans PC, sans proot, sans machine virtuelle.

::: info Crédits
Mis au point par [@CamsShaft](https://github.com/CamsShaft) après de nombreux essais sur un Samsung Galaxy S22
(SM-S901W, aarch64). Guide d'origine (MIT) :
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Il fait partie de la
documentation Unleashed.
:::

**Portée :** cette procédure compile des **applications**, pas le firmware. Pour le firmware lui-même, voir
[Compiler le firmware](/fr/dev/build).

Les chemins ci-dessous supposent un appareil **aarch64** et le préfixe Termux par défaut
(`$PREFIX` = `/data/data/com.termux/files/usr`). Votre appareil peut différer — les pannes typiques sont traitées
dans [Dépannage](#troubleshooting).

## Pourquoi cela demande du travail supplémentaire

uFBT télécharge une chaîne de compilation croisée `arm-none-eabi-gcc` précompilée pour un Linux ordinaire avec
**glibc**. Termux s'exécute sur la libc **Bionic** d'Android, avec une organisation de système de fichiers non
standard, et chaque binaire ELF de la chaîne d'outils réclame `/lib/ld-linux-aarch64.so.1` comme éditeur de liens
dynamique — qui n'existe pas sur Android.

La solution : installer la couche de compatibilité glibc de Termux, puis exécuter chaque binaire de la chaîne
d'outils à travers l'éditeur de liens propre à glibc, via un petit script d'enveloppe.

::: danger N'exécutez pas `patchelf` sur les binaires de la chaîne d'outils
Cela corrompt l'organisation de leurs segments ELF et vous obtenez des segfaults depuis `cc1`. Les enveloppes
ci-dessous laissent les binaires intacts, octet pour octet.
:::

## Prérequis

- Un appareil Android aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/) installé **depuis F-Droid** — le build Google Play est
  obsolète et ne fonctionnera pas.
- Une connexion Internet et quelques Go libres pour la chaîne d'outils, le SDK et glibc.

## 1. Paquets de base

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` n'est **pas** optionnel : la boucle d'enveloppe de l'étape 6 s'en sert pour distinguer les binaires ELF du
reste.

## 2. Couche de compatibilité glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Ce doivent être **deux commandes distinctes** : `glibc-repo` ajoute le dépôt dont provient `glibc-runner`. Ensemble,
elles installent une glibc complète sous `$PREFIX/glibc/`, y compris l'éditeur de liens dynamique. Vérifiez :

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Ne définissez jamais `LD_PRELOAD` globalement vers le `libc.so.6` de glibc.** Cela casse les binaires Bionic
propres à Termux, Python compris, de façon peu évidente. Les enveloppes de l'étape 6 rendent cela inutile.
:::

## 3. Installer uFBT et les dépendances Python de compilation

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Paquet | Nécessaire pour |
|---|---|
| `colorlog` | La journalisation des scripts de compilation |
| `heatshrink2` | La compression des icônes et des ressources |
| `pyelftools` | L'étape de post-traitement `FASTFAP` |
| `scons` | Le système de compilation — doit être une installation autonome ; la copie fournie avec la chaîne d'outils est inutilisable ici |
| `pillow` | La conversion des icônes ; sans lui, la seule erreur est un laconique `convert: No such file or directory` |

Si la roue (wheel) `pillow` échoue à la compilation, utilisez le paquet Termux : `pkg install python-pillow`.

## 4. Pointer uFBT vers le SDK Unleashed {#_4-point-ufbt-at-the-unleashed-sdk}

**uFBT utilise par défaut le SDK du firmware officiel.** Pour compiler contre Unleashed, passez l'index de mises à
jour Unleashed :

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Canaux : `dev` et `release`. **Chaque `ufbt update` ultérieur nécessite les mêmes options**, sans quoi vous
retombez silencieusement sur le SDK officiel et compilez contre la mauvaise API.

Si `~/.ufbt/toolchain/` est encore vide, n'importe quel appel à uFBT amorce la chaîne d'outils :

```sh
ufbt -h
```

Une erreur mentionnant `python3` à ce stade est normale — l'étape 5 la corrige. Vérifiez que la chaîne d'outils est
bien arrivée :

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Rediriger le Python de la chaîne d'outils

La chaîne d'outils embarque son propre Python lié à glibc, qui ne peut pas s'exécuter ici. Faites pointer chaque
entrée `python3*` vers le Python de Termux :

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Envelopper les binaires de la chaîne d'outils

Tout le reste dépend de cette étape. Chaque enveloppe exécute le vrai binaire à travers l'éditeur de liens dynamique
de glibc avec un `--library-path` explicite : le binaire lui-même n'est donc jamais modifié.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

Les trois motifs correspondent à trois répertoires distincts de binaires ELF. En oublier un donne une erreur
caractéristique :

| Répertoire | Contient | Erreur s'il n'est pas enveloppé |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Pourquoi les garde-fous comptent (surtout lors d'une nouvelle exécution) :

- `*.so` est ignoré car `liblto_plugin.so` dans `libexec/` est une bibliothèque partagée et non un exécutable ;
  l'envelopper donne `invalid ELF header`.
- `*.real` et la vérification de `$f.real` rendent la fonction idempotente : la relancer après une mise à jour de la
  chaîne d'outils ne peut pas envelopper une enveloppe.
- Dans `bin/`, seuls les `arm-none-eabi-*` sont enveloppés, volontairement : `bin/python3` pointe désormais vers le
  Python Bionic de Termux et ne doit **pas** passer par l'éditeur de liens de glibc.

::: warning
`ufbt update` peut remplacer toute la chaîne d'outils — **relancez les étapes 5 et 6 après chaque mise à jour.**
:::

## 7. Compiler

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Une compilation réussie se termine ainsi :

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

Le `.fap` se trouve dans `dist/`. Comparez l'API indiquée avec celle du firmware de votre Flipper — une
incompatibilité signifie que l'application refusera de se charger.

## 8. Transférer le .fap sur le Flipper

`ufbt launch` et `ufbt flash_usb` ont besoin d'une connexion série (`/dev/ttyACM*`). **Sur un Android d'origine, non
rooté, cela ne fonctionne pas** — Android n'expose pas les nœuds de périphériques USB CDC-ACM à Termux. Seul un
appareil rooté avec un pilote CDC-ACM fonctionnel peut utiliser ces commandes.

Copiez plutôt le fichier à l'extérieur. Les FAP résident dans `/ext/apps/<Category>/` sur la carte microSD :

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

Depuis `Downloads`, le fichier est visible par les autres applications : transférez-le donc sur le Flipper de la
façon habituelle — avec l'application mobile Flipper, ou un lecteur de cartes microSD USB-C.

## Dépannage {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

L'un des trois répertoires de l'étape 6 n'a pas été enveloppé. Relancez les appels à `wrap` — ils sont sans risque à
répéter.

### `liblto_plugin.so: invalid ELF header`

Une bibliothèque partagée a été enveloppée. Restaurez-la :

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` venant de cc1

Le binaire a été corrompu, presque toujours par `patchelf`. Retéléchargez la chaîne d'outils :

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Puis refaites les étapes 5 et 6. **N'utilisez jamais `patchelf` sur ces binaires.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

`pillow` est absent : `pip install pillow`, ou `pkg install python-pillow`.

### `python3: No such file or directory`

Le lien symbolique Python de la chaîne d'outils est cassé ou a été restauré par une mise à jour. Relancez l'étape 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` pointe vers le `libc.so.6` de glibc, ce qui casse les binaires Bionic de Termux. Videz-le :

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Vérifiez ensuite les restes dans les fichiers de démarrage de votre interpréteur de commandes :

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` annonce que le SDK est à jour, mais la chaîne d'outils est absente

uFBT suit le SDK et la chaîne d'outils séparément. Forcez les deux :

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Puis refaites les étapes 5 et 6.

### L'application se compile mais indique la mauvaise version d'API

Un `ufbt update` a été lancé sans `--index-url` : uFBT est donc repassé au SDK officiel. Relancez la commande de
[l'étape 4](#_4-point-ufbt-at-the-unleashed-sdk).

### Les enveloppes ont disparu après une mise à jour

C'est normal — `ufbt update` peut remplacer tout le répertoire de la chaîne d'outils. Relancez les étapes 5 et 6.

## Ce qui se passe réellement

Chaque enveloppe exécute son vrai binaire à travers l'éditeur de liens dynamique de glibc, avec `--library-path`
pointant vers les bibliothèques de glibc. Quand `arm-none-eabi-gcc` exécute `cc1`, il tombe sur un script shell qui
enchaîne via l'éditeur de liens vers le binaire `.real` intact. La sortie compilée en croisé n'est pas affectée :
elle cible un Cortex-M nu, pas Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Pages liées

- [Votre première application en C](/fr/dev/first-app-c)
- [Compiler le firmware](/fr/dev/build)
- [Applications sur la carte SD](/fr/apps/sd-card-apps)
- [Application mobile Flipper](/fr/mobile/mobile-app)
