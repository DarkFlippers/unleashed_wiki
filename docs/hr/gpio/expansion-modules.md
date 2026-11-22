---
title: Moduli za proširenje
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Moduli za proširenje

**Modul za proširenje** jest pločica treće strane na GPIO priključku koju Flipper automatski prepoznaje i omogućuje joj upravljanje uređajem putem **RPC-a** (istog protokola koji koriste qFlipper i mobilna aplikacija). [Video Game Module](/hr/gpio/video-game-module) najpoznatiji je primjer. Otkrivanjem i vezom upravlja servis `expansion` u firmveru te **Expansion Module Protocol** opisan u nastavku.

## Postavka: koji UART slušati

1. Otvorite `Main Menu → Settings → Expansion Modules`.
2. Postavite `Listen UART`:
   - `USART` — pinovi 13 (TX) / 14 (RX). Obavezno za Video Game Module.
   - `LPUART` — pinovi 15 (TX) / 16 (RX).
   - `None` — otkrivanje isključeno; Flipper zanemaruje module.
3. Pritisnite <kbd>BACK</kbd>. Odabir se sprema i primjenjuje odmah.

| UART | TX pin | RX pin |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Kada odabrati None
Ako isti UART koristite za nešto drugo (Wi-Fi pločicu, GSM, GPS, USB-UART most) i primijetite neuobičajeno ponašanje, postavite `Listen UART` na `None` ili na drugi UART. Aplikacije koje preuzimaju serijski priključak privremeno pauziraju otkrivanje dok su pokrenute.
:::

## Protokol modula za proširenje (za programere modula)

Bajtovno orijentiran, sinkroni protokol zahtjev-odgovor preko UART-a, s otkrivanjem modula, pregovaranjem brzine prijenosa (baud rate), XOR kontrolnim zbrojem i prozirnim prosljeđivanjem RPC prometa.

### Pojmovi

- **Host** — Flipper. **Uređaj / modul** — modul za proširenje.
- **Vrijeme isteka, Tto = 250 ms** — neaktivnost koja se tretira kao prekinuta veza.
- **Mrtvo vrijeme pri promjeni brzine, Tdt = 25 ms** — promet nije dopušten neposredno nakon promjene brzine.

### Struktura okvira

| Zaglavlje (1 bajt) | Sadržaj (0+ bajtova) | Kontrolni zbroj (1 bajt) |
|---|---|---|
| Vrsta okvira | Korisni teret (payload) | XOR svih prethodnih bajtova, početna vrijednost 0 |

| Vrsta | Zaglavlje | Sadržaj | Svrha |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Održava neaktivnu vezu aktivnom |
| STATUS | `0x02` | kod pogreške (1 bajt) | Potvrđuje svaki primljeni okvir |
| BAUD RATE | `0x03` | brzina prijenosa (4 bajta) | Pregovara brzinu |
| CONTROL | `0x04` | naredba (1 bajt) | Pokreće/zaustavlja RPC, upravlja s 5 V |
| DATA | `0x05` | veličina (1 bajt, `0x00`–`0x40`) + do 64 bajtova podataka | Prenosi RPC podatke |

Kodovi pogrešaka STATUS: `0x00` OK, `0x01` nepoznata pogreška, `0x02` brzina prijenosa nije podržana.

Naredbe CONTROL:

| Naredba | Značenje | Dopušteno kada |
|---|---|---|
| `0x00` | Pokreni RPC sesiju | RPC nije aktivan |
| `0x01` | Zaustavi RPC sesiju | RPC je aktivan |
| `0x02` | Omogući OTG (5 V) na GPIO-u | RPC nije aktivan (inače koristite RPC poruke) |
| `0x03` | Onemogući OTG (5 V) na GPIO-u | RPC nije aktivan (inače koristite RPC poruke) |

### Tijek povezivanja

1. **Modul započinje vezu** kratkim spuštanjem RX pina Flippera na nisku razinu.
2. Flipper odgovara okvirom **HEARTBEAT**: spreman.
3. Unutar Tto modul mora poslati okvir **BAUD RATE** — uvijek prvi, čak i ako je 9600 u redu. Početna brzina uvijek je **9600 bauda**. Flipper odgovara sa STATUS OK ili `0x02`; u slučaju odbijanja modul može ponuditi druge brzine. Ništa drugo nije dopušteno dok pregovaranje ne uspije.
4. Obje strane mijenjaju brzinu; modul čeka Tdt.
5. Modul šalje **CONTROL → Start RPC**, Flipper potvrđuje sa STATUS.
6. RPC zahtjevi idu u okvirima **DATA** (podijeljeni u blokove od 64 bajta; svaki blok potvrđuje se sa STATUS). RPC odgovori vraćaju se kao DATA okviri, koje modul mora potvrditi sa STATUS.
7. Kada miruje, modul šalje **HEARTBEAT** češće od svakih Tto; Flipper odgovara s HEARTBEAT.
8. **CONTROL → Stop RPC** završava sesiju. Nakon Tto tišine Flipper se vraća u stanje čekanja.

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

### Pogreške

Pri bilo kojoj otkrivenoj pogrešci (loš kontrolni zbroj, neočekivan okvir) strana koja ju je uočila **prekida svu komunikaciju i resetira se**. Druga strana dočeka istek Tto i veza se ponovno uspostavlja od 1. koraka.

### Programsko upravljanje

Aplikacije u firmveru mogu pozivati `expansion_enable()` / `expansion_disable()` (i `expansion_set_listen_serial()`) iz servisa `expansion` umjesto zaslona Postavki. Aplikacija za otklanjanje pogrešaka `expansion_test` uključena je u stablo izvornog kôda kao referentna implementacija modula.

## Povezano

- [Video Game Module](/hr/gpio/video-game-module)
- [Raspored GPIO pinova](/hr/gpio/pinout)
- [Vanjski moduli](/hr/gpio/external-modules)
