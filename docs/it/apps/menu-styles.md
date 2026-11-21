---
title: Stili del menu principale
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Stili del menu principale

::: tip Unleashed
Unleashed permette di cambiare l'aspetto del **menu principale** (l'elenco che si apre premendo <kbd>OK</kbd> sul
desktop). Ogni aspetto è un piccolo plugin distribuito con il firmware; il firmware di serie offre solo l'elenco
predefinito.
:::

## Scegliere uno stile

1. Apri `Main Menu → Settings → Desktop`.
2. Scorri fino a **Menu Style**.
3. Premi <kbd>←</kbd> / <kbd>→</kbd> per scegliere uno stile. **Default** è il menu standard.
4. Esci da Settings e premi <kbd>OK</kbd> sul desktop: il menu si apre nel nuovo stile.

## Stili disponibili

| Stile | Aspetto | Origine |
|---|---|---|
| Default | l'elenco standard del Flipper | integrato |
| 3D | un carosello 3D di icone | portato da @apfxtech, basato sul menu a carosello OLED 3D di @upiir |
| C64 | schermata del Commodore 64 | portato da Momentum, di Sil (@Sil333033) |
| Compact | un elenco più compatto | portato da Momentum, di @MatthewKuKanich |
| CoverFlow | carosello in stile copertine di album | portato da Momentum, di Cody Tolene (@CodyTolene), perfezionato da @956MB |
| DSi | stile Nintendo DSi | portato da Momentum, di Willy-JL |
| Grid | icone disposte a griglia | di @apfxtech |
| Macintosh | desktop classico di Mac OS | portato da @apfxtech, basato su Ardutosh di @jhhoward |
| PS4 | stile PlayStation 4 | portato da Momentum, di Willy-JL |
| Vertical | elenco verticale | portato da Momentum, di Willy-JL |
| Wii | griglia dei canali Nintendo Wii | portato da Momentum, di Willy-JL |

In Settings gli stili sono elencati in ordine alfabetico dopo **Default**. In ogni stile <kbd>OK</kbd> apre l'app
selezionata e <kbd>Back</kbd> riporta al desktop.

## Dove risiedono gli stili

Gli stili sono plugin del loader: file `.fal` chiamati `menu_style_<name>.fal` in
`/ext/apps_data/loader/plugins/`. L'elenco **Menu Style** è costruito a partire dai file trovati lì, quindi:

- gli stili richiedono la **scheda SD**;
- uno stile compare come **Missing** se il file selezionato è stato eliminato (reinstalla il firmware per
  ripristinarlo) e come **Unknown** se la scheda non è stata letta;
- se uno stile non si carica, il Flipper torna al menu predefinito.

::: info Per sviluppatori
Un nuovo stile è un `FlipperAppType.PLUGIN` con `requires=["loader"]` e un `appid` che inizia con `menu_style_`; è
quel prefisso che Settings usa per distinguere gli stili di menu dagli altri plugin del loader presenti nella stessa
cartella. Vedi `applications/system/menu_styles/` nei sorgenti del firmware e
[Manifest delle app](/it/dev/app-manifests).
:::

## Pagine correlate

- [Desktop](/it/start/desktop)
- [Impostazioni](/it/start/settings)
- [Funzioni di Unleashed](/it/start/unleashed-features)
