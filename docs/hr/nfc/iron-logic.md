---
title: Čitači Iron Logic
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Čitači Iron Logic (CP-Z-2 "3 crte" / "4 crte")

Čitači Iron Logic ("čepovi") česti su u portafonima i sustavima kontrole pristupa diljem bivšeg SSSR-a. Oni štite MIFARE Classic privjeske ključevima po kartici i filtrima protiv kloniranja, pa čitanje, emuliranje i kopiranje **vlastitog** privjeska pomoću Flipper Zera zahtijeva više od jednog prolaza.

::: tip Opseg
Samo za vlastite vjerodajnice i zakonito istraživanje. Temeljeno na članku autora @gromovyna (2025-03-13).
:::

## Kako se ovi sustavi brane od kloniranja

Iron Logic se temelji na jeftinom MIFARE Classicu i na njega dodaje slojeve obrane:

- **Diverzifikacija ključeva.** Ključevi sektora izvode se za svaku karticu iz UID-a kartice i "mape objekta" čitača (konstante učitane u čitač). Napad rječnikom stoga na konfiguriranom sustavu obično ne pronalazi ništa.
- **Filtri** protiv magic kartica i emulatora (primjerice "samo IL-30", OTP1, OTP2), ovisno o firmveru čitača.
- **Dinamički način rada** ("samo prvi", pogledajte [Dinamički upis Iron Logic](/hr/nfc/iron-logic-enrollment)) u kojem se podaci na kartici mijenjaju pri svakom prolasku.

## Koji čitač imate

| Varijanta | Napomene |
|---|---|
| CP-Z-2 ("3 crte") | Stariji, ukinut, ali i dalje čest. |
| CP-Z-2 (mod. MF-I) ("4 crte") | Trenutni model, podržan izdanjima firmvera. Članak je pisan za ovaj model, ali radi i za stariji. |

Prepoznavanje po kućištu nije 100 % pouzdano (instalater može staviti novu elektroniku u staro kućište), ali u praksi gotovo uvijek funkcionira. Čitači se također koriste unutar panela drugih proizvođača (Eltis, Metakom i drugi); to nije važno jer je cilj izvući sve sektore MIFARE Classic kartice.

## Provjerite imate li sreće

### SmartMX kartica (IL-30)

Ako se koristi čitač sa "4 crte", a Flipper prikaže zaslon u stilu "nepodržana kartica", provjerite karticu: **SAK = 28** i **ATQA = 0004** znači **SmartMX** karticu, a čitač može imati uključen filtar **"IL-30 only"**. Svejedno možete isprobati korake u nastavku za slučaj da je filtar isključen i čitač radi u mješovitom načinu (novi SmartMX i stari MIFARE Classic ključevi). Ako ništa ne radi, a trebate kopiju, autor predlaže radionicu opremljenu uređajima iKey koji zapisuju podatke na originalne čipove (iMF+) koristeći logičku grešku u sustavu Iron Logic.

### Dinamički portafoni ("Sokol" tvrtke Petrunja)

Portafoni Sokol (obično izgrađeni na panelu Eltis 5000) koriste čitače Iron Logic **s dinamikom**: podaci u ključu mijenjaju se pri svakom prolasku i stare kopije postaju nevažeće. Emuliranje ili zapisivanje na praznu karticu može **oštetiti vaš original**. Detalji: [dinamički upis](/hr/nfc/iron-logic-enrollment).

## 1. korak: iščitajte sve sektore

Trebaju vam svi sektori i svi ključevi kartice. Nemojte čekati da se napad rječnikom završi: s diverzificiranim ključevima to nema smisla.

1. Pročitajte karticu (`Main Menu → NFC → Read`). Pogledajte [Čitanje kartica](/hr/nfc/read).
2. Ako je rezultat **pročitano 16/16 sektora, ali pronađeno 0/32 ključeva**, kartica ima stražnja vrata (backdoor). Idite izravno na [Vodič za Nested / Fudan backdoor](/hr/nfc/nested-fudan).
3. Ako nemate nijedan ključ, prikupite nonceove s čitača (pogledajte u nastavku), a zatim izvucite ključeve pomoću [MFKey](/hr/nfc/mfkey).
4. Izvucite preostale ključeve pomoću Nested napada ([vodič](/hr/nfc/nested-fudan)).

### Prikupljanje nonceova s čitača

Donedavno se smatralo da Flipper uopće ne može raditi s čitačima s 4 crte. Zahvaljujući @blowtreez pokazalo se da je to moguće, iako zahtijeva preciznost i vježbu. Flipper prikuplja nonceove sa **svih** verzija čitača, neovisno o broju crta ili firmveru.

- Pronađite položaj u kojem Flipper komunicira s čitačem. Empirijski: natpis **"FLI"** na kućištu Flippera trebao bi biti **iznad čitača**.
- Držite ga što je bliže moguće, tako da dodiruje čitač.
- Ponekad (kao u autorovom slučaju) ne radi u zaštitnoj maskici; izvadite Flipper i pokušajte bez nje.

Zatim slijedite službeni članak [Oporavak MIFARE Classic ključeva](https://docs.flipper.net/nfc/mfkey32).

::: tip Autorove bilješke
- U većini slučajeva dovoljni su ključevi i potpuno pročitani sektori **0, 1 i 14**, ali neki sustavi drže podatke u prilagođenim sektorima (primjerice 8). Uvijek napravite potpunu kopiju i dešifrirajte sve sektore.
- Autor spominje da posjeduje privatni API koji izračunava ključ sektora 14 iz UID-a kartice kako bi se nastavilo s Nested napadom (ponuđeno u chatu Unleashed zajednice).
:::

## 2. korak: emulacija

- Radi na svim čitačima "3 crte" (uz rijetke iznimke) i na čitačima "4 crte" osim ako ne koriste najnoviji firmver (**7.28**, kako je navedeno u objavi na kanalu).
- Na starijim verzijama kao što je **7.20** (trenutni tvornički firmver) emulacija radi, ali morate pronaći točan položaj Flippera u odnosu na čitač, kao i pri prikupljanju nonceova.
- Filtri OTP1 i OTP2 **ne** utječu na emulaciju.
- Chameleon Ultra ponaša se na isti način.
- S uključenim filtrom "IL-30 only" emulacija neće raditi.

## 3. korak: kopiranje na praznu karticu

Univerzalni izbor je prazna kartica **CUID static nonce (poznata i kao MF-3.2)** (pogledajte [Magic kartice](/hr/nfc/magic-cards)). U vrijeme pisanja radila je na svim verzijama firmvera i postavkama filtara za oba tipa čitača. Za "3 crte" radi i običan **CUID**, a neki su korisnici uspjeli čak i sa **Zero**.

Autor preporučuje da ne lovite minimalnu radnu karticu osim ako uživate u eksperimentiranju: razlika u cijeni između CUID static nonce i običnog CUID-a je mala, a izbjegavate "faktor kockarnice". Također je pronašao nekoliko običnih CUID čipova (novije revizije) koji rade na svim verzijama firmvera za 4 crte, kao i ranije prijave zajednice o uspjehu s običnim CUID karticama, što donedavno nije mogao pouzdano reproducirati.

## Nije pokriveno

Autor navodi teme koje su izvan opsega ili se još istražuju: kako su implementirani filtri OTP1/OTP2, KDF za ključ A sektora 14 iz UID-a te uloga mape objekta u šifriranju sektora.

## Povezano

- [Nested i Fudan backdoor](/hr/nfc/nested-fudan) · [MFKey](/hr/nfc/mfkey) · [Magic kartice](/hr/nfc/magic-cards)
- [Dinamički upis Iron Logic](/hr/nfc/iron-logic-enrollment) · [Vizit filtri](/hr/nfc/vizit-filters)
