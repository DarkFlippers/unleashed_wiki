---
title: Ručno dodavanje ključeva
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Ručno dodavanje iButton ključeva

Možete stvoriti virtualni ključ na temelju njegovog ID-a bez posjedovanja fizičkog ključa — primjerice iz broja ugraviranog na
ključ ili zapisanog ranije. Takav ključ može se emulirati i, za protokole koji podržavaju pisanje, [zapisati na praznu oznaku](/hr/ibutton/write).

## Koraci

1. Idite u `Main Menu → iButton → Add Manually`.
2. Odaberite protokol:

   | Stavka izbornika | ID za unos |
   |---|---|
   | **Dallas DS1990** | 8 bajtova ROM-a |
   | **Dallas DS1992** | 8 bajtova ROM-a |
   | **Dallas DS1996** | 8 bajtova ROM-a |
   | **Dallas DS1971** | 8 bajtova ROM-a |
   | **Dallas DS1420** | 8 bajtova ROM-a |
   | **Dallas (non-specific)** | 8 bajtova ROM-a — bilo koji 1-Wire uređaj, bez provjera |
   | **Cyfral** | 2 bajta |
   | **Metakom** | 4 bajta (svaki bajt mora imati ispravan paritet) |

   ![Popis tipova ključeva u Add Manually: Dallas DS1990, DS1992, DS1996 i DS1971](/screens/ibutton/add_manually.png)

3. Zaslon **Enter the key** otvara heksadecimalni uređivač. Unesite bajtove i pritisnite **Save**.
4. Unesite naziv (zadani prefiks `iBtn`) i spremite. Ključ se sprema u `/ext/ibutton/<naziv>.ibtn`.

## Uređivanje spremljenog ključa

`Main Menu → iButton → Saved` → ključ → **Edit** → promijenite heksadecimalnu vrijednost → **Save** → naziv → **Save**.

## Napomene o Dallas ID-ovima

Dallas ROM sastoji se od `family code` (1 bajt) + `serial` (6 bajtova) + `CRC` (1 bajt):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- Većina interfonskih ključeva su DS1990 s kodom obitelji (`family code`) `01`.
- Ako je CRC pogrešan, čitač može odbiti ključ, a Flipper prijavljuje CRC pogrešku pri ponovnom čitanju.
- Trebate ključ s namjerno neispravnim kodom obitelji ili CRC-om? Upotrijebite **Dallas (non-specific)** — ne obavlja nikakve provjere.
- Ručno dodani ključ **nema podatke iz memorije**; *Full Write on Same Type* zahtijeva stvarno čitanje.

::: tip Uređivač bajtova
U Unleashedu, uzastopno pritiskanje <kbd>↑</kbd> pri unosu bajtova otvara mini uređivač polubajtova (nibble editor) — korisno za dugačke ID-ove.
:::

## Povezano

- [Čitanje](/hr/ibutton/read) · [Pisanje](/hr/ibutton/write) · [Protokoli](/hr/ibutton/protocols) ·
  [Format datoteke](/hr/ibutton/file-format)
