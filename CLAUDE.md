# QMK Userspace Build Commands

External userspace overlay: keymaps live here under `keyboards/<kb>/keymaps/<km>/` and are compiled against a
separate `qmk_firmware` tree via `QMK_USERSPACE`. Build targets are registered in `qmk.json`.

## Development Environment (NixOS)
```bash
# Enter development shell with QMK tools (toolchain is NOT on the base PATH)
nix develop

# First time setup (run inside nix develop)
qmk setup
qmk config user.overlay_dir="$(realpath .)"
```

## Keyboards and which QMK tree builds them

This repo compiles against **different `qmk_firmware` trees depending on the keyboard**, because not every
board is in mainline QMK. Each flash script sets `QMK_USERSPACE` to this repo and `pushd`es into the right tree.

| Keyboard | Target | QMK tree | Script |
|----------|--------|----------|--------|
| holykeebs spankbd (split, RP2040) | `holykeebs/spankbd:aidengindin` | holykeebs fork → `~/code/qmk_holykeebs` | `span.sh` |
| Keychron C3 Pro 8K (TKL, ANSI) | `keychron/c3_pro_8k/ansi:aidengindin` | Keychron fork, branch `2025q3` → `~/code/qmk_keychron` | `c3.sh` |

- **C3 Pro 8K is fork-only.** It does not exist in mainline QMK — only in `Keychron/qmk_firmware` on the
  `2025q3` branch (the 8K models live there: c1/c2/c3_pro_8k, v1/v3/v6_8k). Mainline's `keychron/c3_pro` is the
  *different, non-8K* board and its firmware will not run on 8K hardware. That branch supports external
  userspace, so the keymap can live here.
- The spankbd build additionally needs `-e USER_NAME=holykeebs` and the holykeebs `users/` module (see `span.sh`).

## Build & Flash Commands
```bash
# Compile firmware for specific keyboard/keymap
qmk compile -kb <keyboard> -km <keymap>
make <keyboard>:<keymap>

# Build all userspace targets
qmk userspace-compile

# Flash (keyboard must be in bootloader mode)
./span.sh    # spankbd: QK_BOOT = spc + p per side
./c3.sh      # C3 Pro 8K: hold Esc while plugging in
```

`.hex`/`.bin`/`.uf2` artifacts are gitignored.

## Code Style Guidelines
- **C Standard**: C99 with QMK macros
- **Formatting**: Google style with 4-space indentation (see .clang-format)
- **Headers**: Use `#include QMK_KEYBOARD_H` for keyboard-specific includes
- **License**: GPL-2.0-or-later with SPDX headers
- **Naming**: snake_case for functions/variables, UPPER_CASE for macros/enums
- **Keymaps**: Define layers with enum, use descriptive layer names (_BASE, _NAV, etc.)
- **Custom Keycodes**: Start from SAFE_RANGE in enum custom_keycodes
- **Home Row Mods**: Define as macros with KC_ prefix (e.g., KC_GUI_A)
- **Layer Toggles**: Use LT() macro with descriptive names
- **Comments**: Minimal inline comments, use ASCII art for keymap visualization

## Project Structure
- `keyboards/` - Custom keyboard keymaps
- `layouts/` - Layout-based keymaps
- `users/` - Shared user code
- `qmk.json` - Build targets configuration
