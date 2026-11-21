---
title: Protocoles pris en charge
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Protocoles iButton pris en charge

Établi d’après `lib/ibutton/protocols/` du firmware Unleashed. Le firmware regroupe les protocoles en **Dallas**
(1-Wire) et **misc** (Cyfral, Metakom).

| Protocole (nom de fichier) | Libellé du menu | Family code | Mémoire | Émulation | Write ID vers | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 o de SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 o de SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 o d’EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | quelconque | — (ROM seule) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | Code de 2 octets | ✓ | TM01x | — |
| `Metakom` | Metakom | — | Code de 4 octets | ✓ | TM01x | — |

## Dallas 1-Wire

La « touch memory » de Dallas Semiconductor (aujourd’hui Analog Devices). Chaque périphérique possède une ROM de
8 octets : family code, numéro de série sur 48 bits et CRC-8. Le Flipper vérifie le CRC et identifie le type d’après le
family code.

- **DS1990 (DS1990A)** — la clé classique sans mémoire, utilisée par la plupart des interphones.
- **DS1420** — totalement compatible avec le DS1990, seul le family code diffère (`81` au lieu de `01`).
- **DS1992 / DS1996** — clés à mémoire SRAM ; DS1971 — à mémoire EEPROM. Le Flipper lit cette mémoire, peut l’afficher
  (**Data Info**), l’émuler et la copier vers une clé du même type.
- **Dallas (non-specific)** — catégorie fourre-tout pour tout autre périphérique 1-Wire : seule la ROM est lue, rien
  n’est vérifié. Utile aussi pour fabriquer une clé avec un family code ou un CRC volontairement erroné.

## Cyfral

Un protocole de clé d’interphone répandu en Russie et dans la CEI ; ce n’est pas du 1-Wire. Le code est stocké sur
2 octets. Il peut être émulé et écrit sur un support vierge TM01x.

## Metakom

Un autre protocole d’interphone de la CEI. Le code tient sur 4 octets, chaque octet portant un bit de parité — une clé
à parité incorrecte est signalée comme invalide et n’est pas écrite. Il peut être émulé et écrit sur un support vierge
TM01x.

## Supports vierges

| Support vierge | Accepte | Comportement |
|---|---|---|
| **RW1990.1** | ROM Dallas (8 octets) | Déverrouillage, écriture (bits inversés), verrouillage |
| **RW1990.2** | ROM Dallas (8 octets) | Déverrouillage, écriture, verrouillage |
| **TM2004** | ROM Dallas (8 octets) | Écrit depuis l’adresse 0 avec relecture de contrôle de chaque octet |
| **TM01x** | ROM Dallas, Cyfral, Metakom | Cyfral/Metakom sont écrits sous forme d’une trame de 36 bits (préfixe de 4 bits + 32 bits de code), vérifiés, puis **finalisés** (sans retour). Les ID Dallas ne sont pas finalisés |

Voir [Écriture](/fr/ibutton/write) pour la mise en pratique.

::: tip Unleashed
La documentation officielle ne mentionne ni le DS1420, ni le réglage Write Blanks, ni l’écriture sur TM01x pour
Cyfral/Metakom.
:::

## Voir aussi

- [Lecture](/fr/ibutton/read) · [Écriture](/fr/ibutton/write) · [Format de fichier](/fr/ibutton/file-format)
