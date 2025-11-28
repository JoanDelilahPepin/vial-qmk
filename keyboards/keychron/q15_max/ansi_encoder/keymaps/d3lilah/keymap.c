/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

// clang-format off

// Custom keycodes for writing macros - offset to avoid Keychron wireless keycodes
enum custom_keycodes {
    // Markdown formatting
    MD_H1 = QK_KB_0 + 20,  // Offset by 20 to be safe past all Keychron codes
    MD_H2,
    MD_H3,
    MD_BOLD,
    MD_ITALIC,
    MD_CODE,
    MD_LINK,
    MD_LIST,

    // Text editing operations
    CUT_LINE_START,
    CUT_LINE_END,
    CUT_WORD_PREV,
    CUT_WORD_NEXT,
    CUT_PARA,
    CUT_PARA_END,
    DUP_LINE,

    // Obsidian/Note-taking
    OBS_QUOTE,
    OBS_PAREN,
    OBS_BRACKET,
    OBS_EMDASH,
    OBS_TAG,
    OBS_WIKI,

    // Google Docs formatting
    GDOC_H1,
    GDOC_H2,
    GDOC_H3,
    GDOC_NORMAL,

    // Special functions
    CLR_FMT,
    WRAP_QUOTE,
    WRAP_PAREN,
    WRAP_BRACKET,

    // Autocorrect toggle
    KC_AC_TOGG
};

enum layers {
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4,
    _FN5,
    _FN6
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: MAC_BASE
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Mut│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │Bsp│Mut│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSh│ ↑ │Del│
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Opt│Cmd│   │     Space         │FN1│FN3│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [MAC_BASE] = LAYOUT_ansi_66(
        KC_MUTE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_MUTE,
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_RSFT,  KC_RSFT,
        MO(_FN4), KC_LCTL,  KC_LALT,  KC_LGUI,  LT(4,KC_SPC),                 KC_SPC,             MO(_FN2), KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_RCTL),

    /* Layer 1: WIN_BASE
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Mut│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │Bsp│Mut│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSh│ ↑ │Del│
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Win│Alt│   │     Space         │FN2│FN3│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [WIN_BASE] = LAYOUT_ansi_66(
        KC_MUTE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_MUTE,
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_RSFT,  KC_RSFT,
        MO(_FN4), KC_LCTL,  KC_LALT,  KC_LGUI,  LT(4,KC_SPC),                 KC_SPC,             MO(_FN2), KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_RCTL),

    /* Layer 2: _FN1 (Mac Function Layer)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │BrD│BrU│MCt│LPd│RGB│   │Prv│Ply│Nxt│Mut│VoD│VoU│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │RMD│RMI│   │   │   │   │   │   │   │Ins│PgU│Hom│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │SPD│SPI│   │   │   │   │   │   │   │PgD│End│       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │HUD│HUI│SAD│SAI│VAD│VAI│NKR│   │   │Del│   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN1] = LAYOUT_ansi_66(
        RGB_TOG,  KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_TOG,
        KC_GRV,   BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 3: _FN2 (Windows Function Layer)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │BrD│BrU│App│PSc│RGB│   │Prv│Ply│Nxt│Mut│VoD│VoU│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │RMD│RMI│   │   │   │   │   │   │Scr│Ins│PgU│Hom│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │SPD│SPI│   │   │   │   │   │   │   │PgD│End│       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │HUD│HUI│SAD│SAI│VAD│VAI│NKR│   │   │Del│   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN2] = LAYOUT_ansi_66(
        RGB_TOG,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_TOG,
        KC_GRV,   BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 4: _FN3 (Universal F-key Layer + Autocorrect)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ACT│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ~ │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │ACT│   │   │   │   │   │   │   │   │   │   │       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     * ACT = Autocorrect Toggle
     */
    [_FN3] = LAYOUT_ansi_66(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_AC_TOGG,
        KC_TILD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 5: _FN4 (Spare layer for user customization) */
    [_FN4] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 6: _FN5 (Spare layer for user customization) */
    [_FN5] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 7: _FN6 (Spare layer for user customization) */
    [_FN6] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),
};

// clang-format on

/* Process user keycodes */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process Keychron common keycodes (wireless functions)
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    // Handle writing macros
    if (record->event.pressed) {
        switch (keycode) {
            // Markdown headers
            case MD_H1:
                tap_code(KC_HOME);
                SEND_STRING("# ");
                return false;
            case MD_H2:
                tap_code(KC_HOME);
                SEND_STRING("## ");
                return false;
            case MD_H3:
                tap_code(KC_HOME);
                SEND_STRING("### ");
                return false;

            // Autocorrect toggle
            case KC_AC_TOGG:
                autocorrect_toggle();
                return false;

            // For now, just return true for other custom keycodes
            // You can implement them later or use Vial macros
            default:
                break;
        }
    }
    return true;
}

/* Encoder map for both knobs (positions 0,0 and 0,13) - 8 layers */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][2][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN2]     = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN3]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN4]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN5]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN6]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif