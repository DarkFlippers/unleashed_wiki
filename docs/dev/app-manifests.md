---
title: App manifests (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# App manifests (.fam)

Every firmware component — services, user apps, settings pages — is developed independently and described by a
manifest file called `application.fam`. It declares the component's basic properties and how it relates to the rest
of the system.

At build time `fbt` collects all manifests, resolves their dependencies and builds **only** the components that the
current build configuration references (see [fbt → firmware app sets](/dev/fbt#firmware-app-sets)).

## App definition

A manifest is a Python snippet calling `App()` with keyword arguments. Only **`appid`** and **`apptype`** are
mandatory; the rest are optional and some only make sense for certain app types.

### App types (`apptype`)

`apptype` is a member of `FlipperAppType`:

| Value | Component type |
|---|---|
| `SERVICE` | System service, created at early startup |
| `SYSTEM` | Not shown in menus; started by other apps or from the CLI |
| `APP` | Regular app in the main menu |
| `PLUGIN` | Built as part of the firmware and placed in the Plugins menu |
| `DEBUG` | Visible only in the Debug menu, with debug mode enabled |
| `ARCHIVE` | The one and only Archive app |
| `SETTINGS` | Placed in the system Settings menu |
| `STARTUP` | Callback run at system startup; does not define a separate app |
| `EXTERNAL` | Built as a `.fap` app |
| `METAPACKAGE` | No code; used to declare dependencies and app bundles |

### Common parameters

| Parameter | Meaning |
|---|---|
| `appid` | String ID of the app inside the build system. Used in build configurations and for resolving dependencies and conflicts |
| `apptype` | See the table above |
| `name` | Name shown in menus |
| `entry_point` | C function used as the entry point. C++ names are mangled — wrap the function in `extern "C"` |
| `flags` | Internal flags for system apps. **Do not use** |
| `cdefines` | C preprocessor definitions declared globally for other apps when this app is in the build. For external apps — used when building the app itself |
| `requires` | App IDs to add to the build whenever this app is built |
| `conflicts` | App IDs this app conflicts with; if any is present, `fbt` aborts the build |
| `provides` | Functionally identical to `requires` |
| `stack_size` | Stack size in bytes allocated when the app starts. Too small → crash on stack overflow; too large → less heap for the app |
| `icon` | Animated icon from built-in assets, used when the app is built into the firmware |
| `order` | Sort order within its group (lower = earlier). Used for startup hooks and menu entries |
| `sdk_headers` | C headers of this app to include in the API for external apps |
| `targets` | Compatible [hardware targets](/dev/hardware-targets). Default `["all"]` |
| `resources` | Folder inside the app's sources packaged as SD card resources (only if the app is in the build). Default `""` — none |

::: tip
Use the `top` and `free` [CLI commands](/dev/cli) to profile your app's memory use when choosing `stack_size`.
:::

### Parameters for external apps (FAPs)

| Parameter | Meaning |
|---|---|
| `sources` | File masks for gathering sources in the app folder. Default `["*.c*"]` (C and C++). The `lib` folder is reserved for `fap_private_libs`. Masks starting with `!` exclude files; masks without wildcards (`*`, `?`) are literal paths. Example: `["*.c*", "!plugins"]` |
| `fap_version` | App version string, default `"0.1"`. A tuple `(x, y)` also works. Extra dot-separated parts are allowed, but only major and minor are stored in the `.fap` |
| `fap_icon` | `.png` file, 1-bit colour, 10×10 px, embedded in the `.fap` |
| `fap_libs` | Extra libraries to link against — gives access to functions not exported by the firmware, at the cost of a larger `.fap` and more RAM |
| `fap_category` | App subcategory; also determines the folder under `apps/` on the SD card |
| `fap_description` | Short description (may be empty) |
| `fap_author` | Author (may be empty) |
| `fap_weburl` | Homepage (may be empty) |
| `fap_icon_assets` | Folder with image assets to preprocess and build together with the app |
| `fap_extbuild` | Parts of sources built by external tools: a list of `ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Boolean, default `False`. `PLUGIN` type only: embed the plugin in the host app's `.fap` as a resource; it is extracted to `apps_assets/APPID` on start |
| `fap_private_libs` | Libraries shipped as sources with the app — see below |

#### External build commands (`fap_extbuild`)

Commands run from the firmware root. Intermediate files must go into the app's temporary build folder. `fbt`
expands these variables (and other internal ones):

- `${FAP_WORK_DIR}` — the app's temporary build folder
- `${FAP_SRC_DIR}` — the app's source folder

Example — building an app from Rust sources:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Private libraries (`fap_private_libs`)

Library sources go into a subfolder of `lib/` inside the app folder. Each library is a `Lib()` call:

| `Lib()` parameter | Meaning | Default |
|---|---|---|
| `name` | Library folder name (**required**) | — |
| `fap_include_paths` | Paths (relative to the library) added to the app's include path | `["."]` |
| `sources` | File masks for the library's sources, relative to its root | `["*.c*"]` |
| `cflags` | Extra compiler flags | `[]` |
| `cdefines` | Extra preprocessor definitions | `[]` |
| `cincludes` | Extra include paths, relative to the **app** root (e.g. for config headers) | `[]` |

Example:

```python
    fap_private_libs=[
            Lib(
                name="mbedtls",
                fap_include_paths=["include"],
                sources=[
                    "library/des.c",
                    "library/sha1.c",
                    "library/platform_util.c",
                ],
                cdefines=["MBEDTLS_ERROR_C"],
            ),
            Lib(
                name="loclass",
                cflags=["-Wno-error"],
            ),
        ],
```

What `fbt` does with it:

- **mbedtls** — built from `lib/mbedtls`; `lib/mbedtls/include` is added to the app's include path; only the
  three listed files are compiled; `MBEDTLS_ERROR_C` is defined for its sources.
- **loclass** — built from all sources in `lib/loclass`; `lib/loclass` is added to the include path; warnings are
  **not** treated as errors (`-Wno-error`), handy for large third-party code.

Both libraries are linked into the app.

## A complete `.fam` file

One file can define several apps. Here is part of `applications/services/bt/application.fam`:

```python
App(
    appid="bt_start",
    apptype=FlipperAppType.STARTUP,
    entry_point="bt_on_system_start",
    order=70,
)

App(
    appid="bt_settings",
    name="Bluetooth",
    apptype=FlipperAppType.SETTINGS,
    entry_point="bt_settings_app",
    stack_size=1 * 1024,
    requires=[
        "bt",
        "gui",
    ],
    order=10,
)
```

A manifest for your own external app, as generated by `ufbt create APPID=test_app` (from
`scripts/ufbt/project_template/app_template/application.fam`):

```python
# For details & more options, see documentation/AppManifests.md in firmware repo

App(
    appid="test_app",  # Must be unique
    name="App test_app",  # Displayed in menus
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Optional values
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bit PNG
    # fap_description="A simple app",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Image assets to compile for this application
)
```

For more examples look at the `.fam` files throughout the firmware — e.g. `applications/system/*/application.fam`
for the extra Unleashed apps.

## Related pages

- [Your first app in C](/dev/first-app-c)
- [Flipper Build Tool (fbt)](/dev/fbt)
- [Hardware targets](/dev/hardware-targets)
