---
title: Layout di tastiera
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Layout di tastiera per Bad USB

Una tastiera USB non invia caratteri, invia **posizioni di tasti**. Il computer le trasforma in caratteri secondo il
*proprio* layout di tastiera. Quindi, per digitare `z` su un PC tedesco (QWERTZ), il Flipper deve premere il tasto che
su una tastiera statunitense è `y`. Un **file di layout** (`.kl`) dice a Bad USB quale tasto (e quale modificatore)
produce ciascun carattere sul layout di destinazione.

::: tip Unleashed
I layout di tastiera per Bad USB arrivano da
[rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl) e fanno parte di Unleashed. Il comando
`DUCKY_LANG` per singolo script è una novità di Unleashed (PR #1224).
:::

## Layout disponibili

File in `/ext/badusb/assets/layouts/` (31 nella build attuale):

| File | Layout |
|---|---|
| `en-US.kl` | Inglese (USA), il **predefinito** e il fallback integrato |
| `en-UK.kl` | Inglese (Regno Unito) |
| `de-DE.kl`, `de-DE-mac.kl` | Tedesco (Germania), PC e Mac |
| `de-CH.kl` | Tedesco (Svizzera) |
| `fr-FR.kl`, `fr-FR-mac.kl` | Francese (Francia), PC e Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | Francese (Belgio, Canada, Svizzera) |
| `es-ES.kl`, `es-LA.kl` | Spagnolo (Spagna, America Latina) |
| `it-IT.kl`, `it-IT-mac.kl` | Italiano, PC e Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portoghese (Portogallo, Brasile) |
| `nl-NL.kl` | Olandese |
| `da-DA.kl` | Danese |
| `nb-NO.kl` | Norvegese |
| `sv-SE.kl` | Svedese |
| `fi-FI.kl` | Finlandese |
| `cz_CS.kl` | Ceco |
| `sk-SK.kl` | Slovacco |
| `hu-HU.kl` | Ungherese |
| `hr-HR.kl` | Croato |
| `si-SI.kl` | Sloveno |
| `ba-BA.kl` | Bosniaco |
| `tr-TR.kl` | Turco |
| `ja-JP.kl` | Giapponese |
| `dvorak.kl` | Dvorak (USA) |
| `colemak.kl` | Colemak |

Non esiste un layout russo/cirillico: il formato può descrivere soltanto caratteri ASCII (vedi sotto).

## Scegliere un layout

**Globalmente** (per tutti gli script): nella schermata dello script premi <kbd>←</kbd>
**Config → Keyboard Layout (global)** e scegli un file `.kl`. La scelta viene salvata in
`/ext/badusb/.badusb.settings` e mostrata tra parentesi nella schermata dello script, per esempio `(de-DE)`. Se il
file salvato manca o è danneggiato, viene usato `en-US`.

![Menu Config di Bad USB, Keyboard Layout (global) è la prima voce](/screens/badusb/config.png)

**Per singolo script**: metti `DUCKY_LANG <name>` in cima allo script:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` è il nome del file senza `.kl`. Alias: `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Si applica da quella riga in poi e viene riportato al layout globale all'inizio di ogni esecuzione.
- Un nome sconosciuto o non valido ripiega sul layout integrato `en-US` senza interrompere lo script.

## Cosa NON cambia un layout

- Attraverso il layout passano solo il testo di `STRING` / `STRINGLN` e i tasti a carattere singolo (`CTRL c`,
  `HOLD a`…). I tasti con nome (`ENTER`, `F5`, le frecce…) sono gli stessi dappertutto.
- `ALTCHAR` / `ALTSTRING` non usano affatto il layout; digitano i caratteri in base al loro codice tramite
  `ALT`+tastierino numerico, ed è per questo che funzionano con qualsiasi layout su Windows.
- Il layout deve corrispondere alla **lingua di inserimento attuale dell'host**. Su un PC con più lingue (per esempio
  inglese e russo) porta l'host sulla lingua del layout prima di eseguire, altrimenti `STRING` digiterà lettere
  cirilliche.

## Formato dei file (`.kl`)

Un file `.kl` è una tabella binaria di esattamente **256 byte**: 128 voci da 2 byte (`uint16` little-endian), una per
ciascun codice ASCII da 0 a 127.

- **Byte basso**: il codice HID usage del tasto da premere (per esempio `0x1F` = il tasto `2`).
- **Byte alto**: i bit dei modificatori da tenere premuti con esso:

| Bit (byte alto) | Modificatore |
|---|---|
| `0x01` | Ctrl sinistro |
| `0x02` | Shift sinistro |
| `0x04` | Alt sinistro |
| `0x08` | GUI sinistro |
| `0x10` | Ctrl destro |
| `0x20` | Shift destro |
| `0x40` | Alt destro (AltGr) |
| `0x80` | GUI destro |

Esempio da `de-DE.kl`: la voce per `"` (ASCII 34) è `1F 02`, cioè Shift + `2`, che è dove si trovano le virgolette
doppie su una tastiera tedesca.

Poiché la tabella ha solo 128 voci, **si possono digitare solo caratteri ASCII**; una `STRING` con un byte qualsiasi
≥ 128 (accenti UTF-8, cirillico, emoji) interrompe lo script con
*"Native .kl supports ASCII, not UTF-8"*. I nomi dei file possono contenere lettere, cifre, `-` e `_` (max. 32
caratteri prima di `.kl`).

Per creare un tuo layout, segui le istruzioni di
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) e copia il file risultante
in `/ext/badusb/assets/layouts/`.

## Pagine correlate

- [Formato degli script](/it/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Usare Bad USB](/it/badusb/usage)
- [Esempi](/it/badusb/examples)
