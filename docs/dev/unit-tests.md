---
title: Unit tests
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Unit tests

Unit tests feed known inputs to feature code and check that the results are correct. They are essential for robust,
bug-free code.

The firmware contains a separate app, **`unit_tests`** (`applications/debug/unit_tests`), which runs **on the
Flipper itself** — so tests use the real hardware and rule out platform-related differences.

When contributing to the firmware, ship unit tests with new features where possible, and run the existing ones to
make sure your change doesn't introduce regressions.

## Running the tests

1. **Build firmware with the test app set:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` is required
   `fbt_options.py` defaults to `DEBUG=1`, and a debug image no longer fits below the radio stack's flash region —
   packaging stops with `Firmware image overlaps C2 region and is not programmable!`. As of API 88.23 a debug image is
   about 7 KB too large for this app set (10 KB for the default set), so trimming the tests won't help.
   (`COMPACT=1` is already the default; it's spelled out to match other commands.)

   Keep in mind that `DEBUG=0` compiles out `furi_assert()`, so assertions in the code under test won't fire.
   `furi_check()` and the minunit assertions are unaffected.
   :::

   The `unit_tests` app set contains: `basic_services`, `updater_app`, `radio_device_cc1101_ext`, `unit_tests`,
   `infrared`, `archive`.

2. **Flash the firmware including SD card resources** (`build/latest/resources`) — e.g. install the generated
   `.tgz` from `dist/` with qFlipper, or use `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`.
   The test assets must end up on the SD card.
3. **Open a [CLI](/dev/cli) session** and run:

   ```
   unit_tests
   ```

**Expected result:** suites run one by one, then a report like:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

If you see `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, the SD card
resources weren't installed — repeat step 2 with resources.

To run **one** test and skip the rest, pass its name:

```
unit_tests test_infrared
```

Other suites are skipped (`Skipping …`); a wrong name gives `No suite named …`. Test names match the app IDs
(`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`, `test_lfrfid`, …) defined in
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
This is a special firmware build without the usual apps. Install a normal build again when you're done.
:::

## Adding unit tests

### Entry point

All tests run from the `unit_tests` "mother" app. The test code itself is packaged as a `PLUGIN` app in a
subdirectory of `tests/` inside `unit_tests`, and is referenced in the common `application.fam`. Copy the structure
of an existing test.

### Test assets

Some tests need external data ("assets"). They live in
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
each in its own subdirectory. Assets can be of any type: plain text, Flipper Format (FFF), binary, etc.

### Example: infrared protocols

Every infrared protocol has a set of unit tests, so add one when you add a new protocol:

1. Create `test_<your_protocol_name>.irtest` in the
   [infrared assets directory](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Fill it with test data (see below).
3. Add the test code to
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Build and install the firmware with resources, then run the tests and check they pass.

#### Test data format

Each infrared test has three sections:

| Section | Does |
|---|---|
| `decoder` | Takes a raw signal, outputs decoded messages |
| `encoder` | Takes decoded messages, outputs a raw signal |
| `encoder_decoder` | Encodes decoded messages to raw, then decodes them again |

`.irtest` files are regular [`.ir` files](/infrared/file-format) with a few additions:

- decoder input signals are named `decoder_input_N` (N = test sequence number), expected output `decoder_expected_N`;
- for encoder tests the two are swapped;
- decoded data is an **array**, because one raw signal may decode into several messages — a single message is an
  array of size 1.

Use existing `.irtest` files as syntax examples.

#### Recording raw signals

Open a CLI session and run:

```
ir rx raw
```

Point the remote at the Flipper and press buttons. The raw data is printed in a ready-to-use format.

## Related pages

- [Integration testing](/dev/testing)
- [Flipper Build Tool (fbt)](/dev/fbt)
- [Command-line interface](/dev/cli)
