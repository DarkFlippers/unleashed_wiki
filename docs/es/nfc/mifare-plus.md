---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** es el sucesor de MIFARE Classic en el catálogo de NXP. Puede funcionar en varios **niveles de
seguridad**:

| Nivel | Comportamiento | Qué hace el Flipper |
|---|---|---|
| **SL0** | Estado de fábrica o de personalización | Identifica la tarjeta, emulación del UID |
| **SL1** | **Compatible con MIFARE Classic** (Crypto-1) | Se lee **como MIFARE Classic**: valen los diccionarios, los ataques anidados, MFKey y qUnleashed |
| **SL2** | Datos de estilo Classic con AES (no en las piezas EV) | Identifica la tarjeta, emulación del UID |
| **SL3** | ISO14443-4, autenticación AES-128 y mensajería segura | Ataque de diccionario de claves AES, volcado completo, emulación completa y reescritura en la tarjeta de origen |

Variantes de producto: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (y una «Plus» genérica);
tamaños 1K (SE), 2K y 4K.

::: tip Unleashed
La identificación de MIFARE Plus por producto, nivel y tamaño, la **lectura de SL3 con diccionarios AES**,
*Show Keys*, la emulación, *Write to Initial Card* / *Update from Initial Card*, una caché de claves por UID y los
generadores de MIFARE Plus en *Add Manually* son funciones de Unleashed.
:::

## Lectura

1. `Main Menu → NFC → Read`, y apoya la tarjeta.
2. Las tarjetas **SL1** se leen como MIFARE Classic (véase [MIFARE Classic](/es/nfc/mifare-classic)). La
   recuperación de claves en SL1 funciona exactamente igual que en Classic; la
   [guía de qUnleashed](/es/nfc/qunleashed) de @gromovyna señala que se aplica **solo** a MIFARE Plus en **SL1**.
3. Tarjetas **SL3**: el ataque de diccionario AES empieza automáticamente (cabecera **"MF Plus Dictionary"**).
   Primero se prueban las claves de usuario y después el diccionario de sistema; una clave en caché de un guardado
   anterior del mismo UID se prueba antes que las dos. La pantalla muestra *Keys Found* / *Sectors Read*. No hay una
   entrada «Unlock with Dictionary» aparte: el ataque forma parte de `Read`.
4. Guarda la tarjeta. Las claves se guardan en caché en `/ext/nfc/.cache/<UID>.mfpkeys`, así que la siguiente
   lectura de la misma tarjeta se autentica al primer intento.

Diccionarios: sistema `/ext/nfc/assets/mf_plus_dict.nfc` (33 claves AES-128 de los valores por defecto de
Proxmark3), usuario `/ext/nfc/assets/mf_plus_dict_user.nfc`. Se gestionan en
`NFC → Extra Actions → MIFARE Plus Keys` (**Add** para añadir una clave de 16 bytes, **List** para borrar).

### Menús de una tarjeta SL3

- Después de leer: **Save**, **Emulate**, **Show Keys** (*"Found MFP Keys"*: claves A/B por sector y claves de
  administración como la Card Master Key, además de los totales) e **Info**.
- Tarjeta guardada: **Emulate**, **Write to Initial Card** (escribe el volcado de vuelta en la misma tarjeta),
  **Update from Initial Card** (vuelve a leer la tarjeta de origen con las claves guardadas; con otras muestra
  *"Use the source card only"*), **Show Keys**, **Rename**, **Delete** e **Info**.
- `Info → More` abre un centro con **View Dump** (bloques, claves de administración, bloques de configuración y
  firma) e **ISO14443-4 Data** (ATS y demás) → **More** (campos de GetVersion: fabricante de hardware y de software,
  tipo, versión, tamaño, lote, semana y año de producción).

En los demás niveles solo se conserva la identidad y se ofrece **Emulate UID**.

## Cómo se identifica una MIFARE Plus

El firmware combina tres señales:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, pero también SL0 y
   DESFire).
2. **Bytes históricos del ATS** con la forma `C1 05 …`: identifican Plus S / X / SE sin ninguna clave.
3. **GetVersion** y una sonda del nivel de seguridad en las piezas EV1/EV2, que dan el tipo y el tamaño de forma
   autoritativa.

Como el SAK `20` se comparte con DESFire, una tarjeta solo se declara Plus cuando la sonda o la huella del ATS lo
confirman.

### Referencia: cómo lo hace NXP TagInfo

La documentación de Unleashed incluye un análisis de la propia aplicación **NFC TagInfo** de NXP (v6.2.0) usada como
referencia. Su procedimiento de decisión:

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → "Classic lane" (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, then DESELECT (C2)
│   │   match ATS historical bytes → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), status 90 → EV generation → EV1
│   ├─ security level = SL1 (answers Classic block auth)
│   └─ size = Plus AES First-Auth probe to increasing key-block addresses
└─ SAK == 20 → "ISO-DEP lane" (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) succeeds → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ storage size)
    └─ size = GET_VERSION storage byte (22 = 2K, 42 = 4K)
```

Huellas de ATS (bytes históricos, byte a byte):

| Bytes históricos del ATS | Subtipo | Código de producto |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (alternativa) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Muestra de ingeniería | — |
| sin coincidencia | Plus **X** (por defecto) | `MF1PLUS` |

En la familia `C1 05 2F 2F …`, el byte 4 distingue la S (`00`) de la X (`01`). Las piezas EV1/EV2 responden a
**Read-Signature** (`3C`); las Plus S y X, no. En GetVersion el byte de fabricante es `04` (NXP) y el byte de
almacenamiento `22` = 2K, `42` = 4K.

Interpretación del SAK que usa TagInfo:

| SAK | Significado |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / variante Plus 2K |
| `28`, `38` | SmartMX con Classic 1K / 4K |
| `88` | NXP Classic 1K (bit 0x80) |
| `98`, `B8` | Variantes SmartMX / Pro |
| `01` | Marcador heredado / TNP |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

El tamaño de memoria en SL1 se sondea con tramas **First-Auth** de Plus AES `70 XX 40 01 00` a los bloques de clave
`0x4010`, `0x4020`, `0x4040` y `0x4064`: el más alto que responde acota el número de sectores (base / 2K / 4K /
ampliado). Códigos de producto emitidos: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE),
`MF1P2101` (EV1 2K).

## Crear una MIFARE Plus a mano

`NFC → Add Manually` ofrece Plus SE (UID de 4 o 7 bytes), Plus S, X, EV1 y EV2 en 2K/4K con UID de 4 o 7 bytes. La
tarjeta generada recibe los bytes históricos del ATS correspondientes; véase
[Añadir tarjetas a mano](/es/nfc/add-manually).

## Relacionado

[MIFARE Classic](/es/nfc/mifare-classic) · [Leer tarjetas](/es/nfc/read) · [qUnleashed](/es/nfc/qunleashed) ·
[Formato de los ficheros NFC](/es/nfc/file-format)
