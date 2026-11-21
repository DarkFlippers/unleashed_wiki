---
title: Modules d'extension
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Modules d'extension

Un **module d'extension** est une carte tierce branchée sur le connecteur GPIO que le Flipper détecte automatiquement
et qu'il autorise à le piloter via **RPC** (le même protocole que celui utilisé par qFlipper et l'application mobile).
Le [Video Game Module](/fr/gpio/video-game-module) en est l'exemple le plus connu. La détection et la liaison sont
assurées par le service `expansion` du firmware et par l'**Expansion Module Protocol** décrit ci-dessous.

## Réglage : quel UART écouter

1. Ouvrez `Main Menu → Settings → Expansion Modules`.
2. Réglez `Listen UART` :
   - `USART` — broches 13 (TX) / 14 (RX). Obligatoire pour le Video Game Module.
   - `LPUART` — broches 15 (TX) / 16 (RX).
   - `None` — détection désactivée ; le Flipper ignore les modules.
3. Appuyez sur <kbd>BACK</kbd>. Le choix est enregistré et appliqué immédiatement.

| UART | Broche TX | Broche RX |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Quand choisir None
Si vous utilisez le même UART pour autre chose (une carte Wi-Fi, du GSM, un GPS, le pont USB-UART) et que vous
constatez un comportement anormal, réglez `Listen UART` sur `None` ou sur l'autre UART. Les applications qui
s'accaparent le port série suspendent la détection pendant leur exécution.
:::

## Expansion Module Protocol (pour les développeurs de modules)

Un protocole orienté octet, synchrone, de type requête-réponse, transporté sur l'UART, avec détection du module,
négociation du débit, somme de contrôle XOR et transfert transparent du trafic RPC.

### Terminologie

- **Hôte** — le Flipper. **Périphérique / module** — le module d'extension.
- **Intervalle de timeout, Tto = 250 ms** — une inactivité de cette durée est considérée comme une connexion perdue.
- **Temps mort lors d'un changement de débit, Tdt = 25 ms** — aucun trafic n'est autorisé juste après un changement de
  vitesse.

### Structure d'une trame

| En-tête (1 octet) | Contenu (0 octet ou plus) | Somme de contrôle (1 octet) |
|---|---|---|
| Type de trame | Charge utile | XOR de tous les octets précédents, valeur initiale 0 |

| Type | En-tête | Contenu | Rôle |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Maintient une connexion inactive en vie |
| STATUS | `0x02` | code d'erreur (1 octet) | Confirme chaque trame reçue |
| BAUD RATE | `0x03` | débit (4 octets) | Négocie la vitesse |
| CONTROL | `0x04` | commande (1 octet) | Démarre/arrête le RPC, pilote le 5 V |
| DATA | `0x05` | taille (1 octet, `0x00`–`0x40`) + jusqu'à 64 octets de données | Transporte les données RPC |

Codes d'erreur STATUS : `0x00` OK, `0x01` erreur inconnue, `0x02` débit non pris en charge.

Commandes CONTROL :

| Commande | Signification | Autorisée quand |
|---|---|---|
| `0x00` | Démarrer la session RPC | RPC inactif |
| `0x01` | Arrêter la session RPC | RPC actif |
| `0x02` | Activer l'OTG (5 V) sur le GPIO | RPC inactif (sinon, utilisez les messages RPC) |
| `0x03` | Désactiver l'OTG (5 V) sur le GPIO | RPC inactif (sinon, utilisez les messages RPC) |

### Déroulement de la connexion

1. **C'est le module qui l'initie**, en tirant brièvement la broche RX du Flipper à l'état bas.
2. Le Flipper répond par un **HEARTBEAT** : il est prêt.
3. Dans l'intervalle Tto, le module doit envoyer une trame **BAUD RATE** — toujours en premier, même si 9600 convient.
   La vitesse initiale est toujours de **9600 bauds**. Le Flipper répond STATUS OK ou `0x02` ; en cas de refus, le
   module peut proposer d'autres débits. Rien d'autre n'est autorisé avant que la négociation n'aboutisse.
4. Les deux parties changent de vitesse ; le module attend Tdt.
5. Le module envoie **CONTROL → Start RPC**, le Flipper confirme par un STATUS.
6. Les requêtes RPC passent dans des trames **DATA** (découpées en blocs de 64 octets ; chaque bloc est confirmé par un
   STATUS). Les réponses RPC reviennent sous forme de trames DATA, que le module doit confirmer par un STATUS.
7. En période d'inactivité, le module envoie un **HEARTBEAT** plus souvent qu'à chaque Tto ; le Flipper répond par un
   HEARTBEAT.
8. **CONTROL → Stop RPC** met fin à la session. Après Tto de silence, le Flipper revient à l'état d'attente.

```text
        MODULE               |            FLIPPER
-----------------------------+---------------------------
Pull down RX                -->
                            <--       Heartbeat
Baud Rate                   -->
                            <--       Status [OK | Error]
(both change baud rate, module waits Tdt)
Control [Start RPC]         -->
                            <--       Status [OK | Error]
Data [RPC Request]          -->
                            <--       Status [OK | Error]
                            <--       Data [RPC Response]
Status [OK | Error]         -->
Heartbeat                   -->
                            <--       Heartbeat
Control [Stop RPC]          -->
                            <--       Status [OK | Error]
```

### Erreurs

À la moindre erreur détectée (somme de contrôle incorrecte, trame inattendue), la partie qui l'a constatée
**interrompt toute communication et se réinitialise**. L'autre partie atteint son timeout au bout de Tto et la
connexion est rétablie à partir de l'étape 1.

### Pilotage programmatique

Les applications du firmware peuvent appeler `expansion_enable()` / `expansion_disable()` (et
`expansion_set_listen_serial()`) depuis le service `expansion` plutôt que de passer par l'écran de réglages. Une
application de debug, `expansion_test`, est fournie dans l'arborescence des sources comme implémentation de module de
référence.

## Pages liées

- [Video Game Module](/fr/gpio/video-game-module)
- [Brochage GPIO](/fr/gpio/pinout)
- [Modules externes](/fr/gpio/external-modules)
