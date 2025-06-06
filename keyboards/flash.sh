export QMK_USERSPACE=~/code/qmk_userspace/

cmd='make holykeebs/spankbd:aidengindin:flash -e USER_NAME=holykeebs -e POINTING_DEVICE=trackpoint_trackball -e CONSOLE=yes -j8'

echo $HOME
pushd $HOME/code/qmk_holykeebs/

echo "Compiling left side firmware. Plug in left side. QK_BOOT (spc + p) to enter bootloader."
$cmd -e SIDE=left || exit 1

echo "Compiling right side firmware. Plug in right side. Remember, keys will be reversed."
$cmd -e SIDE=right || exit 1

