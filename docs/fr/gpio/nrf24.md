---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 GHz)

Le **nRF24L01(+)** de Nordic Semiconductor est un émetteur-récepteur 2,4 GHz bon marché utilisé dans de nombreuses
souris et claviers sans fil ainsi que dans des projets amateurs. Il se connecte au Flipper en SPI.

## Apps

Le pack Base contient le Sniffer et le Mouse Jacker, ceux qu'utilise le guide ci-dessous. Le pack Extra en ajoute six autres :

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Collecte les adresses de claviers sans fil pour Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Injecte des touches dans le récepteur vulnérable d'un clavier ou d'une souris sans fil |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Utilitaire général pour le nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Cherche et décode les paquets nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Montre quels canaux 2,4 GHz sont occupés |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Lit et écrit des champs nommés d'un appareil nRF24 à partir d'un fichier de configuration |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Autre version du Sniffer ci-dessus |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Autre version du Mouse Jacker ci-dessus |

Pilote, Sniffer et Mouse Jacker par [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Toutes ces apps se trouvent dans les
[packs d'apps](https://github.com/xMasterX/all-the-plugins/releases/latest) — voir [Les modules et leurs apps](/fr/gpio/module-apps).

::: warning Aspect légal
Pour l'éducation et pour votre propre matériel uniquement. Injecter des frappes clavier dans l'ordinateur d'autrui est
illégal.
:::

## Câblage

| Broche du Flipper | Broche du nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — laisser non connectée |

![Câblage du nRF24L01 vers le Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Brochage par UberGuidoZ.*

Le nRF24 utilise les mêmes broches SPI (2–5) qu'un [CC1101 externe](/fr/subghz/external-cc1101). Ne connectez qu'un
seul des deux à la fois, sauf si vous utilisez une carte combinée conçue pour les deux (suivez alors sa
documentation).

## Utilisation

1. Éteignez le Flipper, connectez le module, rallumez.
2. Ouvrez **NRF24: Sniffer** (`Apps → GPIO`). Lancez le balayage ; utilisez les boutons pour changer de mode et de
   canal comme indiqué à l'écran.
3. Attendez que le sniffer trouve une **adresse**.
4. Ouvrez **NRF24: Mouse Jacker**.
5. Sélectionnez l'adresse, puis ouvrez le script Bad USB à envoyer.
6. Les frappes clavier sont transmises au dongle cible.

Vidéo de démonstration : [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). La syntaxe des scripts est la même que
pour [Bad USB](/fr/badusb/script-format).

## Si le module est capricieux

Le nRF24 consomme du courant par courtes pointes. S'il ne fonctionne que par intermittence, ajoutez un condensateur
entre **VCC et GND** directement au niveau du module :

- un électrolytique de 3,3 µF à 10 µF (attention à la polarité : le négatif vers GND). Un seul 10 µF suffit
  généralement.
- éventuellement un céramique de 0,1 µF en parallèle : le gros condensateur absorbe les variations lentes, le petit
  les pointes de commutation rapides.

Les versions « plus » (nRF24L01+PA+LNA) dotées d'un amplificateur en ont encore plus besoin.

![Condensateur sur le module nRF24](/img/remote/218b238eb91c9e38.jpg)

## Crédits

- Technique de sniffing : Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Vulnérabilités MouseJack : Marc Newlin, [recherche Bastille](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Pilote inspiré de [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html) ; code MouseJack
  inspiré de [JackIt](https://github.com/insecurityofthings/jackit).

## Pages liées

- [Modules externes](/fr/gpio/external-modules)
- [Bad USB](/fr/badusb/usage)
- [Brochage GPIO](/fr/gpio/pinout)
