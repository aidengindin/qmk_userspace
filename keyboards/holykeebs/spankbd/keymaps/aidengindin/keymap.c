// Copyright 2025 Aiden Gindin
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "users/holykeebs/holykeebs.h"

// const tap_dance_action_t tap_dance_actions[] PROGMEM = {};
const key_override_t *key_overrides[] = {};

enum {
    _BASE,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
    _PROGRAM,
    _GAME,
    _GAME_NUM
};

enum custom_keycodes {
    LEQ = SAFE_RANGE,
    GEQ,
    NEQ,
    FAT_ARROW,
    THIN_ARROW,
    PAAMAYIM_NEKUDOTAYIM,
    LAND,
    LOR,
    PLUSEQ,
    MINUSEQ,
    UPDIR,
    INCREMENT,
    DECREMENT,
    SNIPER
};

// Home row mods
#define KC_GUI_A    GUI_T(KC_A)
#define KC_ALT_S    ALT_T(KC_S)
#define KC_CTL_D    CTL_T(KC_D)
#define KC_SFT_F    SFT_T(KC_F)
#define KC_SFT_J    SFT_T(KC_J)
#define KC_CTL_K    CTL_T(KC_K)
#define KC_ALT_L    ALT_T(KC_L)
#define KC_GUI_SCLN GUI_T(KC_SCLN)
#define KC_HYP_C    HYPR_T(KC_C)
#define KC_MEH_V    MEH_T(KC_V)
#define KC_MEH_M    MEH_T(KC_M)
#define KC_HYP_COMM HYPR_T(KC_COMMA)

// Layer toggles
#define KC_NAV_SPC      LT(_NAV,     KC_SPC)
#define KC_MOUSE_TAB    LT(_MOUSE,   KC_TAB)
#define KC_MEDIA_ESC    LT(_MEDIA,   KC_ESC)
#define KC_NUM_BSPC     LT(_NUM,     KC_BSPC)
#define KC_SYM_ENT      LT(_SYM,     KC_ENT)
#define KC_FUN_DEL      LT(_FUN,     KC_DEL)
#define KC_PROGRAM_SLSH LT(_PROGRAM, KC_SLSH)

const uint16_t PROGMEM leader_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
    COMBO(leader_combo, QK_LEAD),
};

void leader_start_user(void) {
    // TODO: light up the LEDs or something
}

void leader_end_user(void) {
    os_variant_t host_os = detected_host_os();

    if (leader_sequence_two_keys(KC_O, KC_W)) {
        if (host_os == OS_MACOS) {
            SEND_STRING(SS_LGUI("w"));
        } else {
            SEND_STRING(SS_LALT(SS_TAP(X_F4)));
        }
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NAV_SPC:
        case KC_MOUSE_TAB:
        case KC_MEDIA_ESC:
        case KC_NUM_BSPC:
        case KC_SYM_ENT:
        case KC_FUN_DEL:
            // Enable hold-on-other-key-press for thumb layer taps
            return true;
        default:
            // Disable for home row mods and other keys
            return false;
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case LEQ:
                SEND_STRING("<=");
                break;
            case GEQ:
                SEND_STRING(">=");
                break;
            case NEQ:
                SEND_STRING("!=");
                break;
            case FAT_ARROW:
                SEND_STRING("=>");
                break;
            case THIN_ARROW:
                SEND_STRING("->");
                break;
            case PAAMAYIM_NEKUDOTAYIM:
                SEND_STRING("::");
                break;
            case LAND:
                SEND_STRING("&&");
                break;
            case LOR:
                SEND_STRING("||");
                break;
            case PLUSEQ:
                SEND_STRING("+=");
                break;
            case MINUSEQ:
                SEND_STRING("-=");
                break;
            case UPDIR:
                SEND_STRING("../");
                break;
            case INCREMENT:
                SEND_STRING("++");
                break;
            case DECREMENT:
                SEND_STRING("--");
                break;
        }
    }
    return true;
}

//#ifdef POINTING_DEVICE_ENABLE
#if 0
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == _NAV) {
        if (mouse_report.x) tap_code(mouse_report.x > 0 ? KC_RGHT : KC_LEFT);
        if (mouse_report.y) tap_code(mouse_report.y > 0 ? KC_DOWN : KC_UP);
    } else {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
    }
    mouse_report.x = mouse_report.y = 0;
    return mouse_report;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────┬───────┬───────────┬────────────┬───────────┐   ┌─────────┬────────────┬──────────┬───────┬──────────────┐
//    │   q   │   w   │     e     │     r      │     t     │   │    y    │     u      │    i     │   o   │      p       │
//    ├───────┼───────┼───────────┼────────────┼───────────┤   ├─────────┼────────────┼──────────┼───────┼──────────────┤
//    │ gUI_A │ aLT_S │   cTL_D   │   sFT_F    │     g     │   │    h    │   sFT_J    │  cTL_K   │ aLT_L │   gUI_SCLN   │
//    ├───────┼───────┼───────────┼────────────┼───────────┤   ├─────────┼────────────┼──────────┼───────┼──────────────┤
//    │   z   │   x   │   hYP_C   │ csa-none_V │     b     │   │    n    │ csa-none_M │ hYP_COMM │   .   │ pROGRAM_SLSH │
//    └───────┴───────┼───────────┼────────────┼───────────┤   ├─────────┼────────────┼──────────┼───────┴──────────────┘
//                    │ mEDIA_ESC │  nAV_SPC   │ mOUSE_TAB │   │ sYM_ENT │  nUM_BSPC  │ fUN_DEL  │
//                    └───────────┴────────────┴───────────┘   └─────────┴────────────┴──────────┘
[_BASE] = LAYOUT_split_3x5_3(
  KC_Q     , KC_W     , KC_E         , KC_R       , KC_T         ,     KC_Y       , KC_U        , KC_I        , KC_O     , KC_P           ,
  KC_GUI_A , KC_ALT_S , KC_CTL_D     , KC_SFT_F   , KC_G         ,     KC_H       , KC_SFT_J    , KC_CTL_K    , KC_ALT_L , KC_GUI_SCLN    ,
  KC_Z     , KC_X     , KC_HYP_C     , KC_MEH_V   , KC_B         ,     KC_N       , KC_MEH_M    , KC_HYP_COMM , KC_DOT   , KC_PROGRAM_SLSH,
                        KC_MEDIA_ESC , KC_NAV_SPC , KC_MOUSE_TAB ,     KC_SYM_ENT , KC_NUM_BSPC , KC_FUN_DEL
),

//    ┌──────┬──────┬───────────┬──────────┬─────┐   ┌─────────┬──────┬──────┬──────┬─────────┐
//    │      │      │           │          │     │   │  caps   │      │      │      │ QK_BOOT │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├─────────┼──────┼──────┼──────┼─────────┤
//    │ lgui │ lalt │   lctl    │   lsft   │     │   │ CW_TOGG │ left │ down │  up  │  rght   │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├─────────┼──────┼──────┼──────┼─────────┤
//    │      │      │ csag-none │ csa-none │     │   │   ins   │ home │ pgdn │ pgup │   end   │
//    └──────┴──────┼───────────┼──────────┼─────┤   ├─────────┼──────┼──────┼──────┴─────────┘
//                  │           │          │     │   │         │      │      │
//                  └───────────┴──────────┴─────┘   └─────────┴──────┴──────┘
[_NAV] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,     KC_CAPS , _______ , _______ , _______ , QK_BOOT,
  KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,     CW_TOGG , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT,
  _______ , _______ , KC_HYPR , KC_MEH  , _______ ,     KC_INS  , KC_HOME , KC_PGDN , KC_PGUP , KC_END ,
                      _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌──────┬──────┬───────────┬──────────┬─────┐   ┌──────┬────────┬──────┬──────┬──────┐
//    │      │      │           │          │     │   │      │        │      │      │      │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├──────┼────────┼──────┼──────┼──────┤
//    │ lgui │ lalt │   lctl    │   lsft   │     │   │      │ SNIPER │ btn4 │ btn5 │      │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├──────┼────────┼──────┼──────┼──────┤
//    │      │      │ csag-none │ csa-none │     │   │      │  wh_l  │ wh_d │ wh_u │ wh_r │
//    └──────┴──────┼───────────┼──────────┼─────┤   ├──────┼────────┼──────┼──────┴──────┘
//                  │           │          │     │   │ btn2 │  btn1  │ btn3 │
//                  └───────────┴──────────┴─────┘   └──────┴────────┴──────┘
[_MOUSE] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______,
  KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,     _______ , SNIPER  , KC_BTN4 , KC_BTN5 , _______,
  _______ , _______ , KC_HYPR , KC_MEH  , _______ ,     _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R,
                      _______ , _______ , _______ ,     KC_BTN2 , KC_BTN1 , KC_BTN3
),

//    ┌──────┬──────┬───────────┬──────────┬─────┐   ┌──────┬──────┬──────┬──────┬──────┐
//    │      │      │           │          │     │   │      │      │      │      │      │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │ lgui │ lalt │   lctl    │   lsft   │     │   │      │ mprv │ vold │ volu │ mnxt │
//    ├──────┼──────┼───────────┼──────────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │      │      │ csag-none │ csa-none │     │   │      │      │      │      │      │
//    └──────┴──────┼───────────┼──────────┼─────┤   ├──────┼──────┼──────┼──────┴──────┘
//                  │           │          │     │   │ mstp │ mply │ mute │
//                  └───────────┴──────────┴─────┘   └──────┴──────┴──────┘
[_MEDIA] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______,
  KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______ ,     _______ , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT,
  _______ , _______ , KC_HYPR , KC_MEH  , _______ ,     _______ , _______ , _______ , _______ , _______,
                      _______ , _______ , _______ ,     KC_MSTP , KC_MPLY , KC_MUTE
),

//    ┌───┬───┬───┬───┬───┐   ┌─────┬──────────┬───────────┬──────┬──────┐
//    │ [ │ 7 │ 8 │ 9 │ ] │   │     │          │           │      │      │
//    ├───┼───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ ' │ 4 │ 5 │ 6 │ = │   │     │   lsft   │   lctl    │ lalt │ lgui │
//    ├───┼───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ ` │ 1 │ 2 │ 3 │ \ │   │     │ csa-none │ csag-none │      │      │
//    └───┴───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┴──────┘
//            │ . │ 0 │ - │   │     │          │           │
//            └───┴───┴───┘   └─────┴──────────┴───────────┘
[_NUM] = LAYOUT_split_3x5_3(
  KC_LBRC , KC_7 , KC_8   , KC_9 , KC_RBRC ,     _______ , _______ , _______ , _______ , _______,
  KC_QUOT , KC_4 , KC_5   , KC_6 , KC_EQL  ,     _______ , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI,
  KC_GRV  , KC_1 , KC_2   , KC_3 , KC_BSLS ,     _______ , KC_MEH  , KC_HYPR , _______ , _______,
                   KC_DOT , KC_0 , KC_MINS ,     _______ , _______ , _______
),

//    ┌───┬───┬───┬───┬───┐   ┌─────┬──────────┬───────────┬──────┬──────┐
//    │ { │ & │ * │ ( │ } │   │     │          │           │      │      │
//    ├───┼───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ " │ $ │ % │ ^ │ + │   │     │   lsft   │   lctl    │ lalt │ lgui │
//    ├───┼───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ ~ │ ! │ @ │ # │ | │   │     │ csa-none │ csag-none │      │      │
//    └───┴───┼───┼───┼───┤   ├─────┼──────────┼───────────┼──────┴──────┘
//            │ ( │ ) │ _ │   │     │          │           │
//            └───┴───┴───┘   └─────┴──────────┴───────────┘
[_SYM] = LAYOUT_split_3x5_3(
  KC_LCBR , KC_AMPR , KC_ASTR , KC_LPRN , KC_RCBR ,     _______ , _______ , _______ , _______ , _______,
  KC_DQUO , KC_DLR  , KC_PERC , KC_CIRC , KC_PLUS ,     _______ , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI,
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_PIPE ,     _______ , KC_MEH  , KC_HYPR , _______ , _______,
                      KC_LPRN , KC_RPRN , KC_UNDS ,     _______ , _______ , _______
),

//    ┌─────┬────┬─────┬─────┬───────────┐   ┌─────┬──────────┬───────────┬──────┬──────┐
//    │ f12 │ f7 │ f8  │ f9  │ DF(_GAME) │   │     │          │           │      │      │
//    ├─────┼────┼─────┼─────┼───────────┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ f11 │ f4 │ f5  │ f6  │   sCRL    │   │     │   lsft   │   lctl    │ lalt │ lgui │
//    ├─────┼────┼─────┼─────┼───────────┤   ├─────┼──────────┼───────────┼──────┼──────┤
//    │ f10 │ f1 │ f2  │ f3  │   paus    │   │     │ csa-none │ csag-none │      │      │
//    └─────┴────┼─────┼─────┼───────────┤   ├─────┼──────────┼───────────┼──────┴──────┘
//               │ app │ spc │    tab    │   │     │          │           │
//               └─────┴─────┴───────────┘   └─────┴──────────┴───────────┘
[_FUN] = LAYOUT_split_3x5_3(
  KC_F12 , KC_F7 , KC_F8  , KC_F9  , DF(_GAME) ,     _______ , _______ , _______ , _______ , _______,
  KC_F11 , KC_F4 , KC_F5  , KC_F6  , KC_SCRL   ,     _______ , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI,
  KC_F10 , KC_F1 , KC_F2  , KC_F3  , KC_PAUS   ,     _______ , KC_MEH  , KC_HYPR , _______ , _______,
                   KC_APP , KC_SPC , KC_TAB    ,     _______ , _______ , _______
),

//    ┌───────────┬──────────────────────┬───────────┬────────────┬─────────┐   ┌─────┬─────┬─────┬─────┬─────┐
//    │ INCREMENT │ PAAMAYIM_NEKUDOTAYIM │    LOR    │    LAND    │ PLUSEQ  │   │     │     │     │     │     │
//    ├───────────┼──────────────────────┼───────────┼────────────┼─────────┤   ├─────┼─────┼─────┼─────┼─────┤
//    │    LEQ    │          <           │     >     │    GEQ     │   NEQ   │   │     │     │     │     │     │
//    ├───────────┼──────────────────────┼───────────┼────────────┼─────────┤   ├─────┼─────┼─────┼─────┼─────┤
//    │ DECREMENT │        UPDIR         │ FAT_ARROW │ THIN_ARROW │ MINUSEQ │   │     │     │     │     │     │
//    └───────────┴──────────────────────┼───────────┼────────────┼─────────┤   ├─────┼─────┼─────┼─────┴─────┘
//                                       │           │            │         │   │     │     │     │
//                                       └───────────┴────────────┴─────────┘   └─────┴─────┴─────┘
[_PROGRAM] = LAYOUT_split_3x5_3(
  INCREMENT , PAAMAYIM_NEKUDOTAYIM , LOR       , LAND       , PLUSEQ  ,     _______ , _______ , _______ , _______ , _______,
  LEQ       , KC_LT                , KC_GT     , GEQ        , NEQ     ,     _______ , _______ , _______ , _______ , _______,
  DECREMENT , UPDIR                , FAT_ARROW , THIN_ARROW , MINUSEQ ,     _______ , _______ , _______ , _______ , _______,
                                     _______   , _______    , _______ ,     _______ , _______ , _______
),

//    ┌───┬───┬──────┬─────┬──────┐   ┌─────┬───────────────┬──────┬───┬───┐
//    │ q │ w │  e   │  r  │  t   │   │  y  │       u       │  i   │ o │ p │
//    ├───┼───┼──────┼─────┼──────┤   ├─────┼───────────────┼──────┼───┼───┤
//    │ a │ s │  d   │  f  │  g   │   │  h  │       j       │  k   │ l │ ; │
//    ├───┼───┼──────┼─────┼──────┤   ├─────┼───────────────┼──────┼───┼───┤
//    │ z │ x │  c   │  v  │  b   │   │  n  │       m       │  ,   │ . │ / │
//    └───┴───┼──────┼─────┼──────┤   ├─────┼───────────────┼──────┼───┴───┘
//            │ lctl │ spc │ lsft │   │ ent │ MO(_GAME_NUM) │ lalt │
//            └──────┴─────┴──────┘   └─────┴───────────────┴──────┘
[_GAME] = LAYOUT_split_3x5_3(
  KC_Q , KC_W , KC_E    , KC_R   , KC_T    ,     KC_Y   , KC_U          , KC_I    , KC_O   , KC_P   ,
  KC_A , KC_S , KC_D    , KC_F   , KC_G    ,     KC_H   , KC_J          , KC_K    , KC_L   , KC_SCLN,
  KC_Z , KC_X , KC_C    , KC_V   , KC_B    ,     KC_N   , KC_M          , KC_COMM , KC_DOT , KC_SLSH,
                KC_LCTL , KC_SPC , KC_LSFT ,     KC_ENT , MO(_GAME_NUM) , KC_LALT
),

//    ┌─────┬───┬─────┬───┬─────┐   ┌─────┬─────┬──────┬──────┬───────────┐
//    │ esc │ 7 │  8  │ 9 │ f3  │   │ f6  │ f9  │      │      │ DF(_BASE) │
//    ├─────┼───┼─────┼───┼─────┤   ├─────┼─────┼──────┼──────┼───────────┤
//    │ tab │ 4 │  5  │ 6 │ f2  │   │ f5  │ f8  │ vold │ volu │           │
//    ├─────┼───┼─────┼───┼─────┤   ├─────┼─────┼──────┼──────┼───────────┤
//    │  `  │ 1 │  2  │ 3 │ f1  │   │ f4  │ f7  │ f10  │ f11  │    f12    │
//    └─────┴───┼─────┼───┼─────┤   ├─────┼─────┼──────┼──────┴───────────┘
//              │     │ 0 │     │   │     │     │      │
//              └─────┴───┴─────┘   └─────┴─────┴──────┘
[_GAME_NUM] = LAYOUT_split_3x5_3(
  KC_ESC , KC_7 , KC_8    , KC_9 , KC_F3   ,     KC_F6   , KC_F9   , _______ , _______ , DF(_BASE),
  KC_TAB , KC_4 , KC_5    , KC_6 , KC_F2   ,     KC_F5   , KC_F8   , KC_VOLD , KC_VOLU , _______  ,
  KC_GRV , KC_1 , KC_2    , KC_3 , KC_F1   ,     KC_F4   , KC_F7   , KC_F10  , KC_F11  , KC_F12   ,
                  _______ , KC_0 , _______ ,     _______ , _______ , _______
)
};

