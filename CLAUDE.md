# QMK Userspace Build Commands

## Development Environment (NixOS)
```bash
# Enter development shell with QMK tools
nix develop

# First time setup (run inside nix develop)
qmk setup
qmk config user.overlay_dir="$(realpath .)"
```

## Build & Flash Commands
```bash
# Compile firmware for specific keyboard/keymap
qmk compile -kb <keyboard> -km <keymap>
make <keyboard>:<keymap>

# Flash firmware (requires keyboard in bootloader mode)
make holykeebs/spankbd:aidengindin:flash -e USER_NAME=holykeebs -e POINTING_DEVICE=trackpoint_trackball -e CONSOLE=yes -j8

# Build all userspace targets
qmk userspace-compile
```

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