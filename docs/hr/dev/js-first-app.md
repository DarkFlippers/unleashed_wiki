---
title: "JavaScript: vaša prva aplikacija"
sidebarTitle: "JS: prva aplikacija"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# Vaša prva JavaScript aplikacija

U ovim uputama napisat ćete kratku skriptu koja ispisuje brojeve s odgodom, a zatim je pokrenuti na Flipper Zeru na dva načina: iz izbornika uređaja i s računala putem CLI-ja. Potrebni su vam Flipper Zero, računalo i USB kabel.

## Korak 1. Izradite skriptu

Stvorite tekstualnu datoteku naziva `first_app.js` sa sljedećim sadržajem:

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

Što skripta radi:

- ispisuje **start** i čeka 1 sekundu;
- ispisuje **1**, **2** i **3** uz pauzu od 0,5 sekundi nakon svakog broja;
- ispisuje **end**.

`print()` ispisuje tekst, a `delay()` pauzira izvođenje za zadani broj milisekundi (1000 ms = 1 s). Obje su **ugrađene funkcije**, pa nije potrebno prethodno učitavati nijedan modul. Potpuni popis potražite na stranici [Ugrađene funkcije](/hr/dev/js-builtin).

## Korak 2. Kopirajte datoteku na Flipper Zero

1. Povežite Flipper Zero s računalom putem USB-a.
2. Otvorite [qFlipper](/hr/mobile/qflipper).
3. Idite na karticu **File manager** i otvorite `SD Card/apps/Scripts/`.
4. Povucite i ispustite `first_app.js` u prozor programa qFlipper.

Datoteku možete kopirati i putem čitača kartica. Mora završiti u mapi `/ext/apps/Scripts/`.

## Korak 3. Pokrenite skriptu

### Iz izbornika Flippera

1. Otvorite `Main Menu → Apps → Scripts`. Popis prikazuje skripte u mapi `SD Card/apps/Scripts/`.
2. Odaberite `first_app`.
3. Pritisnite <kbd>OK</kbd> za pokretanje.

![Skripta se izvršava na Flipper Zeru](/img/dev/js_first_app_on_fz.jpg)

Retci se pojavljuju na zaslonu Flippera uz odgode definirane u skripti.

### Putem CLI-ja

Pokretanje putem [CLI-ja](/hr/dev/cli) praktično je za otklanjanje pogrešaka: skriptu uređujete i testirate bez dodirivanja uređaja.

1. Povežite Flipper Zero putem USB-a.
2. Otvorite CLI (primjerice pomoću kartice CLI u qFlipperu, serijskog terminala ili naredbe `./fbt cli`).
3. Pokrenite `js` nakon čega slijedi putanja do skripte:

```sh
js /ext/apps/Scripts/first_app.js
```

![Ispis skripte u CLI-ju](/img/dev/js_first_app_on_cli.jpg)

Kada se skripta pokrene putem CLI-ja, sve što se ispisuje pomoću `print()` ide u CLI, a ne na zaslon Flippera.

## Rješavanje problema

- **Skripta se ne nalazi na popisu.** Provjerite ima li datoteka nastavak `.js` i nalazi li se u `/ext/apps/Scripts/` (podmape su dopuštene; uđite u njih).
- **Skripta se zaustavlja s pogreškom.** mJS podržava samo podskup JavaScripta (nema zatvorenja, streličastih funkcija ni klasa). Pokrenite je putem CLI-ja kako biste vidjeli poruku o pogrešci i broj retka.

**Sljedeće:** [Razvoj aplikacija uz JavaScript SDK](/hr/dev/js-sdk)
