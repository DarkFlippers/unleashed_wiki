---
title: Format d'archive Heatshrink
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Format d'archive tar compressée Heatshrink

Le Flipper sait lire les archives `.tar` compressées avec la bibliothèque
[Heatshrink](https://github.com/atomicobject/heatshrink). Cela réduit la taille des paquets de mise à jour et accélère
les mises à jour OTA — les ressources de la carte SD présentes dans chaque paquet de mise à jour (`resources.ths`)
utilisent ce format.

Heatshrink lui-même ne définit pas de conteneur pour ses paramètres de compression : le Flipper ajoute donc un petit
en-tête.

## Structure du fichier

| Décalage | Taille | Champ | Valeur |
|--:|--:|---|---|
| 0 | 4 octets | Magic | `0x48 0x53 0x44 0x53` — `HSDS` en ASCII (« HeatShrink DataStream ») |
| 4 | 1 octet | Version | `0x01` |
| 5 | 1 octet | Taille de fenêtre | Logarithme base 2 de la taille de la fenêtre glissante ; équivalent de `-w` dans la CLI Heatshrink |
| 6 | 1 octet | Taille de lookahead | Logarithme base 2 de la taille du tampon de lookahead ; équivalent de `-l` dans la CLI Heatshrink |
| 7 | … | Données | Flux compressé Heatshrink |

L'en-tête fait **7 octets** au total. À l'intérieur du flux compressé se trouve une archive tar classique non
compressée (USTAR).

## Comment les outils du firmware la créent

D'après `scripts/flipper/assets/tarball.py` et `heatshrink_stream.py` :

- extension : `.ths` (« .Tar.HeatShrink ») ;
- paramètres par défaut : fenêtre `13`, lookahead `6` ;
- l'en-tête est empaqueté avec `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (le magic est un entier
  32 bits en little-endian, ce qui donne sur le disque les octets `48 53 44 53`) ;
- le tar est en USTAR, avec uid/gid `0`, mtime `0`, nom d'utilisateur/de groupe `furippa`, et les fichiers parasites
  de macOS sont filtrés.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## L'utiliser sur l'appareil

La bibliothèque tar du firmware ouvre les archives `.ths` dans un mode *heatshrink* en lecture seule, choisi
automatiquement d'après l'extension du fichier. Le [CLI](/fr/dev/cli#storage) peut donc les décompresser
directement :

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Pages liées

- [Mises à jour OTA](/fr/dev/ota)
- [Interface en ligne de commande](/fr/dev/cli)
