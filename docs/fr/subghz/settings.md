---
title: Radio Settings (réglages radio)
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings (réglages radio)

`Main Menu → Sub-GHz → Radio Settings` regroupe les réglages qui s'appliquent à toute l'application Sub-GHz :
radio utilisée, puissance d'émission, nommage des fichiers et comportement du compteur tournant. Les réglages de
réception (fréquence, modulation, hopping, filtres) se trouvent dans `Read → Config` — voir
[Read](/fr/subghz/read#config).

::: tip Unleashed
Dans le firmware d'origine, ce menu ne fait que basculer entre le module interne et le module externe. Unleashed
ajoute **TX Power**, **Protocol Names**, **Counter Incr.**, et en mode Debug **Ext Amp & LEDs** et **Debug Pin**.
:::

## Entrées du menu

![Radio Settings : Module, TX Power, Protocol Names et Counter Incr.](/screens/subghz/radio_settings.png)

| Entrée | Valeurs | Rôle |
|---|---|---|
| `Module` | `Internal`, `External` | Radio utilisée en réception et en émission. `External` n'est proposé que si un CC1101 externe est détecté sur le GPIO ; s'il ne répond pas, le Flipper retombe sur `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Puissance d'émission. `Preset` = ce que définit le preset de modulation (par défaut). Les valeurs basses sont pratiques pour des essais à courte portée |
| `Protocol Names` | `OFF` / `ON` | Sur `ON`, les noms de fichiers générés automatiquement contiennent le nom du protocole + l'horodatage, au lieu d'un simple horodatage ou d'un nom aléatoire |
| `Counter Incr.` | `+1`, `+2`, `+3` (normal) | De combien le compteur tournant est incrémenté à chaque émission pour les protocoles dynamiques. Par défaut `+1` |

Entrées supplémentaires en **mode Debug** (`Settings → System → Debug → ON`) :

| Entrée | Valeurs | Rôle |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Liste complète des pas de compteur pour les expérimentations : grands sauts, `OVFL` (pas de 65535), `OFEX` (mode spécial), `No` (compteur inchangé) et pas négatifs |
| `Ext Amp & LEDs` | `ON` / `OFF` | Pilote la broche d'amplificateur / LED des modules externes (GPIO PC3, comme sur les modules E07). Par défaut `ON`. Désactivez-le si votre module utilise cette broche pour autre chose |
| `Debug Pin` | `OFF` / `17(1W)` | Recopie le signal de données de la radio sur la broche GPIO 17 (1-Wire) — pour le développement de protocoles avec un analyseur logique |

`TX Power`, `Protocol Names` et `Ext Amp & LEDs` sont enregistrés immédiatement (dans
`/ext/subghz/assets/last_subghz.settings`). `Counter Incr.` n'est pas enregistré : il reste actif jusqu'au
redémarrage du Flipper, puis revient à `+1`.

::: warning Pas du compteur
Les pas de compteur importants ou négatifs sont réservés aux expérimentations **sur vos propres récepteurs**. Faire
sauter un compteur loin en avant déplace définitivement le compteur mémorisé par le récepteur au-delà de celui de
votre télécommande d'origine ; revenir en arrière fait que le récepteur vous ignore. Pour coexister avec la
télécommande d'origine, utilisez les [Modes de compteur](/fr/subghz/counter-mode) ou créez une nouvelle
télécommande avec [Add Manually](/fr/subghz/add-manually). Pour le contexte :
[Codes tournants](/fr/subghz/rolling-codes).
:::

## Autres réglages stockés sur la carte SD

| Fichier | Rôle | Détails |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Fréquences supplémentaires, liste du hopper, fréquence par défaut, presets de modulation personnalisés | [Fréquences](/fr/subghz/frequencies#adding-frequencies), [Formats de fichiers](/fr/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Plage de fréquences étendue (hors spécification) | [Fréquences](/fr/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vos propres clés constructeur KeeLoq | [Formats de fichiers](/fr/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/fr/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Dernière fréquence, modulation, filtres et seuil d'analyseur utilisés — écrit par l'application | ne pas éditer à la main |

Les fichiers se terminant par `.example` sont des modèles : renommez-les en `…_user` pour les activer. Les fichiers
`_user` ne sont pas écrasés par les mises à jour du firmware.

## Dépannage

- **`Module` n'affiche que `Internal`** — aucun CC1101 externe détecté. Vérifiez le câblage et l'alimentation, puis
  revenez dans le menu. Voir [CC1101 externe](/fr/subghz/external-cc1101).
- **Les signaux émis sont faibles** — vérifiez que `TX Power` n'est pas réglé sur une valeur négative.
- **Les noms de fichiers ne sont que des dates** — activez `Protocol Names`.
- **Pas d'entrées `Ext Amp & LEDs` / `Debug Pin`** — elles n'apparaissent qu'en mode Debug.

## Voir aussi

- [Read → Config](/fr/subghz/read#config) · [Fréquences](/fr/subghz/frequencies) · [CC1101 externe](/fr/subghz/external-cc1101)
- [Modes de compteur](/fr/subghz/counter-mode) · [Formats de fichiers](/fr/subghz/file-format) · [Réglages dangereux](/fr/start/dangerous-settings)
