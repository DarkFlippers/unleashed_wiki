---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** et **BFT Mitto** construisent leur code tournant à partir d'un **Seed** secret. Sans celui-ci, le Flipper ne peut pas décoder ces télécommandes (elles apparaissent comme `KL: Unknown`, ou pas du tout) et ne peut pas fabriquer une télécommande que le récepteur accepterait. **Seed Capturer** (par @xMasterX) collecte la matière première nécessaire à la récupération du Seed : le `Fix` de la télécommande et une suite de valeurs `Hop` consécutives.

Il ne récupère **pas** le Seed lui-même et il **n'émet jamais** — il se contente d'écouter et d'écrire un fichier. La recherche s'effectue dans l'application compagnon [qUnleashed](/fr/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer est une application système intégrée d'Unleashed, et qUnleashed lit ses captures directement depuis le Flipper. Une fois le Seed connu, Unleashed peut décoder la télécommande et en créer de nouvelles via `Add Manually [Advanced]`.
:::

## Quand en avez-vous besoin

- La programmation radio du récepteur est désactivée, le seul moyen d'entrer est donc le clone d'une télécommande connue — et un clone a besoin du Seed.
- Votre télécommande FAAC / Genius est une **esclave**, qui ne peut pas émettre le code de programmation.
- Vous ne pouvez pas accéder physiquement au récepteur.
- Les installations **Erreka** où toutes les télécommandes partagent un même Seed.
- Les anciennes télécommandes **BFT Mitto** à Seed unique, quand la voie du bouton de programmation ne fonctionne pas (les télécommandes BFT plus récentes dérivent le Seed du numéro de série et se décodent dans un Read normal).

Si la télécommande peut être mise en mode programmation, le Seed est souvent émis en clair — cette voie est plus rapide ; voir [Programmer une nouvelle télécommande](/fr/subghz/remote-prog).

## Capture

1. Ouvrez `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Choisissez `New capture`.
3. **Type de télécommande :** `FAAC SLH`, `Genius`, `Erreka` ou `BFT Mitto`.
4. **Fréquence :** `433.92 MHz  AM650` ou `868.35 MHz  AM650` (`BFT Mitto` ne propose que 433.92 MHz).
5. Appuyez encore et encore sur **le même bouton de la même télécommande**, à peu près une fois par seconde, la télécommande collée au Flipper.
6. Observez l'écran :
   - `Fix XXXXXXXX` — la partie fixe de la télécommande ; l'application se verrouille sur la première qu'elle entend ;
   - `Hops n/10  Xpkt` — combien de hops **différents** sont collectés, et le nombre de paquets bruts ;
   - l'état `Hop n: XXXXXXXX` à chaque nouvelle valeur reçue.
7. À partir de **2 hops**, `Save` apparaît sur <kbd>OK</kbd>. Appuyez dessus ; l'application affiche `Saved N hops` et le nom du fichier.

<kbd>←</kbd> (`Reset`) jette la capture, ce qui permet de se verrouiller sur une autre télécommande ou un autre bouton.

| État | Signification |
|---|---|
| `Hop n: XXXXXXXX` | nouvelle partie tournante mémorisée — continuez d'appuyer |
| `Other remote XXXXXXXX` | une autre télécommande ou un autre bouton — ignoré |
| `Same hop, ignored` | répétition du dernier appui |
| `Have 10, enough` | c'est complet — appuyez sur `Save` |

**Combien d'appuis :** 2 est le minimum, 5 à 10 c'est mieux. Un point tout aussi important : les appuis doivent être **consécutifs, sans en manquer un seul** — vérifiez que `Hops` augmente à chaque appui. S'il en manque un, appuyez sur `Reset` et recommencez.

::: warning
Sur **FAAC SLH et Genius, le Seed est différent pour chaque bouton** — capturez le bouton que vous voulez réellement utiliser. Sur Erreka, le Seed est par télécommande (parfois par installation), sur BFT Mitto par télécommande.
:::

## Autres entrées du menu

- `Decode RAW file` — extraire les Fix/Hops d'un `.sub` RAW (depuis `/ext/subghz`) enregistré auparavant avec [Read RAW](/fr/subghz/read-raw) ; la fréquence vient du fichier. Un fichier-clé est refusé avec `Not a RAW capture`. Ici, <kbd>←</kbd> est `Back` et non `Reset`.
- `Delete all captures` — demande `Delete every capture file in subghz_seed_captures?`, puis les supprime.
- `Exit`.

## Le fichier de capture

Les fichiers sont écrits dans `/ext/apps_data/subghz_seed_captures/`, nommés `<Type>_<Fix>_<date-heure>.txt`, par exemple `Erreka_F00F1C9B_261008-142233.txt`. C'est un fichier texte, **pas un `.sub` rejouable** :

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Récupérer le Seed dans qUnleashed

1. Connectez le Flipper à **qUnleashed** et ouvrez son outil de récupération de Seed. Il va chercher les captures dans `subghz_seed_captures` tout seul — rien à copier ni à renommer.
2. Choisissez la capture et lancez la recherche (une recherche par force brute, raison pour laquelle elle ne tourne pas sur le Flipper).
3. Si le Seed est trouvé, qUnleashed peut composer le `.sub` de clone fini (numéro de série et bouton issus du `Fix`, plus le Seed et le compteur) et le déposer sur le Flipper.
4. Si rien n'est trouvé, c'est que la capture comportait très probablement un trou — recapturez, soigneusement.

Avec le Seed, vous pouvez aussi fabriquer des télécommandes à la main dans `Sub-GHz → Add Manually [Advanced]` : votre propre `SERIAL` + le `SEED` pour une nouvelle télécommande, ou le `SERIAL`/`BUTTON` de l'originale + le `SEED` + un `COUNTER` légèrement supérieur pour un clone. Un clone entre en conflit avec l'originale sur le compteur — voir [Codes tournants](/fr/subghz/rolling-codes).

::: warning
Uniquement pour les télécommandes et les récepteurs qui vous appartiennent.
:::

## Pages liées

- [Programmer une nouvelle télécommande](/fr/subghz/remote-prog) · [KeeLoq](/fr/subghz/keeloq) · [Add manually](/fr/subghz/add-manually)
- [Application qUnleashed](/fr/mobile/qunleashed-app)
