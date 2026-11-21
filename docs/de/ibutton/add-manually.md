---
title: Schlüssel manuell anlegen
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton-Schlüssel manuell anlegen

Du kannst einen virtuellen Schlüssel allein aus seiner ID erzeugen, ohne den physischen Schlüssel zu haben — etwa aus
einer eingravierten oder früher notierten Nummer. Er lässt sich emulieren und bei schreibbaren Protokollen
[auf einen Rohling schreiben](/de/ibutton/write).

## Schritt für Schritt

1. Öffne `Main Menu → iButton → Add Manually`.
2. Wähle das Protokoll:

   | Menüname | Einzugebende ID |
   |---|---|
   | **Dallas DS1990** | 8 Byte ROM |
   | **Dallas DS1992** | 8 Byte ROM |
   | **Dallas DS1996** | 8 Byte ROM |
   | **Dallas DS1971** | 8 Byte ROM |
   | **Dallas DS1420** | 8 Byte ROM |
   | **Dallas (non-specific)** | 8 Byte ROM — jedes 1-Wire-Gerät, keine Prüfungen |
   | **Cyfral** | 2 Byte |
   | **Metakom** | 4 Byte (jedes Byte muss die richtige Parität haben) |

   ![Typliste in Add Manually: Dallas DS1990, DS1992, DS1996 und DS1971](/screens/ibutton/add_manually.png)

3. Der Bildschirm **Enter the key** öffnet einen Hex-Editor. Tippe die Bytes ein und drücke **Save**.
4. Gib einen Namen ein (Standardpräfix `iBtn`) und speichere. Der Schlüssel landet in `/ext/ibutton/<name>.ibtn`.

## Einen gespeicherten Schlüssel bearbeiten

`Main Menu → iButton → Saved` → Schlüssel → **Edit** → Hex ändern → **Save** → Name → **Save**.

## Hinweise zu Dallas-IDs

Ein Dallas-ROM besteht aus `family code` (1 Byte) + `serial` (6 Byte) + `CRC` (1 Byte):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- Die meisten Türsprechanlagen-Schlüssel sind DS1990 mit Family Code `01`.
- Stimmt die CRC nicht, kann ein Lesegerät den Schlüssel abweisen, und der Flipper meldet beim Zurücklesen einen
  CRC-Fehler.
- Du brauchst einen Schlüssel mit absichtlich ungültigem Family Code oder ungültiger CRC? Nimm **Dallas
  (non-specific)** — dort wird nichts geprüft.
- Ein manuell angelegter Schlüssel hat **keine Speicherdaten**; Full Write on Same Type braucht einen echten
  Lesevorgang.

::: tip Byte-Editor
In Unleashed öffnet mehrfaches Drücken von <kbd>↑</kbd> in der Byte-Eingabe einen kleinen Nibble-Editor — praktisch
bei langen IDs.
:::

## Verwandte Seiten

- [Lesen](/de/ibutton/read) · [Schreiben](/de/ibutton/write) · [Protokolle](/de/ibutton/protocols) ·
  [Dateiformat](/de/ibutton/file-format)
