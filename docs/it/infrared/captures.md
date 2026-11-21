---
title: Contribuire con le acquisizioni
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Contribuire con acquisizioni IR ai telecomandi universali

Se un [telecomando universale](/it/infrared/universal-remotes) non funziona con il tuo apparecchio, puoi registrare il
tuo telecomando originale e aggiungerlo alla libreria, così funzionerà per tutti. Questa pagina spiega come fare
acquisizioni **pulite**: corte, decodificate dove possibile e con il nome esatto che il telecomando universale si
aspetta.

Il metodo è quello della guida Unleashed di **@amec0e** (che mantiene gli asset IR di Unleashed), basata sulla
documentazione originale *UniversalRemotes* di @gsurkov, @skotopes, @knrn-ai, @DrZlo13 e @ahumeniy.

## Nomi dei pulsanti per libreria {#button-names-per-library}

Il telecomando universale usa solo i segnali il cui `name:` corrisponde esattamente a uno dei suoi pulsanti (le
maiuscole contano). Ognuno di essi può essere omesso se il tuo apparecchio non lo ha.

| Libreria | File | Nomi dei segnali |
|---|---|---|
| TVs | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projectors | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LEDs | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Fans | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| ACs | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

Su molti telecomandi audio `Play` e `Pause` sono lo stesso pulsante: registralo come `Play` e tralascia `Pause`.

## TV, audio, proiettori, ventilatori, LED

1. Punta il telecomando verso il ricevitore IR del Flipper.
2. Avvia `Infrared → Learn New Remote` per il primo pulsante, oppure seleziona `+` nel telecomando per i successivi.
3. Fai una **pressione rapida** del pulsante del telecomando e salvalo con il nome corrispondente della tabella sopra.
4. Ripeti i passi 2-3 per tutti i pulsanti.
5. Prova ogni pulsante salvato sull'apparecchio reale: ognuno deve fare ciò che dice il suo nome.

::: warning Non tenere premuto il pulsante
Tenere premuto il pulsante del telecomando produce acquisizioni lunghe con molte ripetizioni. Richiedono più tempo per
essere inviate e rallentano l'intero telecomando universale per tutti.
:::

### Parsed o RAW

**Parsed** è il risultato migliore: il protocollo è stato riconosciuto e vengono memorizzati solo protocollo,
indirizzo e comando.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Le interferenze provocate da altri apparecchi intorno a te (lampade, retroilluminazione del TV, altri telecomandi)
possono far finire un'acquisizione in **RAW** anche se il protocollo è noto. Se hai ottenuto un RAW per un telecomando
comune, premi **Retry** sul Flipper qualche volta finché ottieni un'acquisizione parsed pulita.

Il **RAW** va bene quando il telecomando usa davvero un protocollo sconosciuto. Cerca di ottenere il *minor numero di
campioni* che funzioni ancora sull'apparecchio: una pressione rapida, tipicamente **circa 100 campioni**.
Un'acquisizione ideale di una singola pressione è così:

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Condizionatori {#air-conditioners}

I telecomandi dei condizionatori sono diversi: il telecomando mantiene lo stato (modalità, temperatura, ventola,
alette) sul suo display, e ogni pressione invia **l'intero stato** in un colpo solo. Perciò ogni "pulsante" di un
condizionatore è in realtà uno stato completo che va acquisito nel suo insieme.

Per ogni segnale **tranne `Off`**:

1. Premi **Power** sul telecomando così che il suo display mostri il condizionatore come acceso.
2. Imposta la modalità e la temperatura secondo la tabella sotto. Lascia tutto il resto (velocità della ventola,
   alette) su **AUTO** se possibile.
3. Premi **Power** sul telecomando per spegnerlo.
4. Sul Flipper avvia l'apprendimento (`Learn New Remote` per il primo, `+` per gli altri).
5. Punta il telecomando verso il Flipper e premi **Power** un'altra volta (è il frame "accendi in questa modalità").
6. Salva il segnale con il nome indicato nella tabella.
7. Ripeti per ogni riga.

| Segnale | Modalità | Temperatura | Nota |
|:---:|:---:|:---:|---|
| `Dh` | Deumidificazione | N/D | |
| `Cool_hi` | Raffreddamento | la più bassa | temperatura più bassa disponibile in modalità raffreddamento |
| `Cool_lo` | Raffreddamento | 23 °C | |
| `Heat_hi` | Riscaldamento | la più alta | temperatura più alta disponibile in modalità riscaldamento |
| `Heat_lo` | Riscaldamento | 23 °C | |

Poi registra **`Off`**:

1. Assicurati che il display del telecomando mostri il condizionatore come acceso.
2. Avvia l'apprendimento sul Flipper e punta il telecomando verso di esso.
3. Premi **Power** così che il telecomando mostri lo stato spento.
4. Salva il segnale come `Off`.

Ottieni così fino a 6 segnali. Provali tutti sul condizionatore reale.

## Preparare il file e inviarlo

1. Copia il file `.ir` da `/ext/infrared/` sul tuo computer con [qFlipper](/it/mobile/qflipper) (o con l'app mobile) e
   aprilo in un editor di testo.
2. Fai precedere i tuoi segnali da un commento con il modello, così la libreria resta ordinata:
   ```text
   # Model: <your brand and model>
   ```
   L'ordine dei segnali all'interno del blocco non conta.
3. Fai il fork del [repository Unleashed](https://github.com/DarkFlippers/unleashed-firmware) e **aggiungi** il tuo
   blocco **alla fine** del file corrispondente in
   `applications/main/infrared/resources/infrared/assets/`.
4. Apri una pull request con il file modificato. Dopo la revisione arriverà nella build successiva per tutti.

Il formato dei file è descritto in [Formato dei file IR](/it/infrared/file-format#library-files). Grandi raccolte della
comunità di telecomandi già pronti: [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) e l'ufficiale
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB) usata dall'[app mobile](/it/infrared/mobile).

## Pagine correlate

- [Telecomandi universali](/it/infrared/universal-remotes)
- [Apprendere e inviare segnali](/it/infrared/read)
- [Formato dei file IR](/it/infrared/file-format)
