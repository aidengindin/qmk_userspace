#!/usr/bin/env bash
# Build & flash the Keychron C3 Pro 8K (ANSI) aidengindin keymap.
#
# The C3 Pro 8K target lives only in Keychron's fork (branch 2025q3), so this
# builds against ~/code/qmk_keychron rather than the mainline ~/code/qmk_firmware.
# The keymap itself lives in this userspace repo (external userspace overlay).

export QMK_USERSPACE=~/code/qmk_userspace/

pushd ~/code/qmk_keychron/ || exit 1

echo "Plug in the C3 Pro 8K. Hold Esc while plugging in to enter the bootloader."
make keychron/c3_pro_8k/ansi:aidengindin:flash -j8 || { popd; exit 1; }

popd
