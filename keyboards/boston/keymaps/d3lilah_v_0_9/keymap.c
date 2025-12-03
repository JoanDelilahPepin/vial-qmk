/* Copyright 2020 Pylon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include <stddef.h>  // For offsetof macro

// Custom keycodes for pre-compiled macros
// Using QK_KB_0 (USER00) as base for VIAL compatibility
enum custom_keycodes {
    MD_H1 = QK_KB_0,
    MD_H2,
    MD_H3,
    BOLD,
    ITALIC,
    CLR_FMT,
    CUT_LINE_START,
    CUT_LINE_END,
    CUT_WORD_PREV,
    CUT_WORD_NEXT,
    CUT_PARA,
    CUT_PARA_END,
    PASTE,
    OBS_QUOTE,
    OBS_PAREN,
    OBS_EMDASH,
    WRAP_QUOTE,
    WRAP_PAREN,
    GDOC_H1,
    GDOC_H2,
    GDOC_H3,
    GDOC_NORMAL,
    AC_TOG,  // Custom keycode for autocorrect toggle
    DOUBLE_ZERO,  // Double zero for numpad
    DUMP_KM  // Dump keymap to console
};

// Tap Dance declarations
enum {
    LAYER_SWITCH = 0,  // TD(0) - Layer switching tap dance
    FEATURE_TOG = 1    // TD(1) - Feature toggle tap dance
};

    /* Due to how the matrix is setup - the right split backspace key is, for firmware purposes the key to the right of up arrow, which on the actual keyboard is a blocker*/

// Keymap exported from VIAL configuration
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_MUTE, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_MPRV, KC_MPLY, KC_MNXT, KC_INS,  KC_HOME, KC_PGUP,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUSE,KC_DEL,  KC_END,  KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, TD(FEATURE_TOG), TD(LAYER_SWITCH), KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_TAB,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  MO(2),   KC_P4,   KC_P5,   KC_P6,   KC_PEQL,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        MO(1),   KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT,KC_P0,   KC_P0,   DOUBLE_ZERO
    ),

    [1] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CUT_LINE_START, CUT_PARA, CUT_WORD_PREV, CUT_WORD_NEXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CUT_LINE_END, _______, WRAP_QUOTE, CUT_PARA_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TD(LAYER_SWITCH), _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MD_H1, MD_H2, MD_H3, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BOLD, ITALIC, CLR_FMT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, AC_TOG, WRAP_PAREN, OBS_EMDASH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TD(LAYER_SWITCH), _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, GDOC_H1, GDOC_H2, GDOC_H3, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BOLD, ITALIC, GDOC_NORMAL, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, AC_TOG, WRAP_PAREN, OBS_EMDASH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT_all(
        QK_BOOT, DUMP_KM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TD(LAYER_SWITCH), _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// Tap Dance Note: TD(LAYER_SWITCH) and TD(FEATURE_TOG) are handled by VIAL
// They will be loaded from EEPROM or can be configured via VIAL GUI
// LAYER_SWITCH (TD0) = NumLock toggle
// FEATURE_TOG (TD1) = Calculator launch

/*Default layer is white.*/

/*Remember to also change the color in keyboard_post_init_kb in boston.c to make the startup color match the layer 0 color */


const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 0, 0, 128}  /*White*/
);

const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 21, 255, 128} /*Orange*/
);

const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 43, 255, 128} /*Yellow*/
);

const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 75, 255, 128} /*Green*/
);

const rgblight_segment_t PROGMEM layer_4[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 135, 255, 128} /*Teal*/
);

const rgblight_segment_t PROGMEM layer_5[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 160, 200, 128} /*Blue*/

);

const rgblight_segment_t PROGMEM layer_6[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 190, 255, 128} /*Magenta*/
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_0,
    layer_1,
    layer_2,
    layer_3,
    layer_4,
    layer_5,
    layer_6
);

void keyboard_post_init_user(void) {
    /* Enable the LED layers */
    rgblight_layers = my_rgb_layers;

    // Enable autocorrect by default
    autocorrect_enable();

    // Initialize Auto Shift settings
    #ifdef AUTO_SHIFT_ENABLE
    // Enable Auto Shift by default
    autoshift_enable();

    // Set Auto Shift timeout to 175ms
    set_autoshift_timeout(175);

    // Initialize QMK Settings for Auto Shift if not already set
    #ifdef QMK_SETTINGS
        // The auto_shift byte is at offset 24 in the QMK Settings structure
        // (After 12 uint16_t values = 24 bytes)
        const uint16_t AUTO_SHIFT_OFFSET = 24;

        // Check if Auto Shift settings are uninitialized in EEPROM
        uint8_t auto_shift_byte = dynamic_keymap_get_qmk_settings(AUTO_SHIFT_OFFSET);

        // If uninitialized (0xFF) or disabled (bit 0 not set), set our defaults
        if (auto_shift_byte == 0xFF || !(auto_shift_byte & 1)) {
            // Set the Auto Shift byte with our desired configuration:
            // Bit 0: Enable (1)
            // Bit 1: Enable for modifiers (0)
            // Bit 2: No auto shift special (0)
            // Bit 3: No auto shift numeric (0)
            // Bit 4: No auto shift alpha (1) - this is set
            // Bit 5: Enable repeat (0)
            // Bit 6: Disable repeat when timeout exceeded (0)
            auto_shift_byte = 0x11; // Binary: 00010001 (enable + no alpha)
            dynamic_keymap_set_qmk_settings(AUTO_SHIFT_OFFSET, auto_shift_byte);
        }
    #endif
    #endif

    // Initialize tap dances with defaults if they're not configured
    #ifdef VIAL_TAP_DANCE_ENABLE
    // Check if tap dances are uninitialized and set defaults
    vial_tap_dance_entry_t td;

    // Check TD(0) - LAYER_SWITCH
    if (dynamic_keymap_get_tap_dance(LAYER_SWITCH, &td) == 0) {
        if (td.on_tap == KC_NO || td.on_tap == 0xFFFF) {
            // TD(0) - Layer switching
            td.on_tap = TO(0);           // Switch to layer 0
            td.on_hold = TO(3);          // Switch to layer 3
            td.on_double_tap = TO(1);    // Switch to layer 1
            td.on_tap_hold = TO(2);      // Switch to layer 2
            td.custom_tapping_term = 235;
            dynamic_keymap_set_tap_dance(LAYER_SWITCH, &td);
        }
    }

    // Check TD(1) - FEATURE_TOG
    if (dynamic_keymap_get_tap_dance(FEATURE_TOG, &td) == 0) {
        if (td.on_tap == KC_NO || td.on_tap == 0xFFFF) {
            // TD(1) - Feature toggles
            td.on_tap = AC_TOG;          // Autocorrect toggle
            td.on_hold = KC_CAPS;        // Caps Lock
            td.on_double_tap = AS_TOGG;  // Auto-shift toggle
            td.on_tap_hold = CW_TOGG;    // Caps Word toggle
            td.custom_tapping_term = 235;
            dynamic_keymap_set_tap_dance(FEATURE_TOG, &td);
        }
    }
    #endif

    // Flash once on startup to show autocorrect is on
    // Temporarily disable layers for the flash
    rgblight_layers = NULL;
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(0, 0, 255);  // White
    rgblight_set();  // Force update
    wait_ms(300);
    rgblight_sethsv_noeeprom(0, 0, 0);    // Off
    rgblight_set();  // Force update
    wait_ms(200);

    // Re-enable layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    /* Both layers will light up if both kb layers are active */
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, true);
    return true;
} 

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

            // ========== MARKDOWN HEADERS ==========
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

            // ========== TEXT FORMATTING ==========
            case BOLD:
                register_code(KC_LGUI);
                tap_code(KC_B);
                unregister_code(KC_LGUI);
                return false;

            case ITALIC:
                register_code(KC_LGUI);
                tap_code(KC_I);
                unregister_code(KC_LGUI);
                return false;

            case CLR_FMT:
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_LCTL);
                tap_code(KC_K);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
                return false;

            // ========== LINE OPERATIONS ==========
            case CUT_LINE_START:
                register_code(KC_LSFT);
                tap_code(KC_HOME);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_LINE_END:
                register_code(KC_LSFT);
                tap_code(KC_END);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== WORD OPERATIONS ==========
            case CUT_WORD_PREV:
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_WORD_NEXT:
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== PARAGRAPH OPERATIONS ==========
            case CUT_PARA:
                register_code(KC_LGUI);
                tap_code(KC_A);
                unregister_code(KC_LGUI);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            case CUT_PARA_END:
                register_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_DOWN);
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                return false;

            // ========== PASTE ==========
            case PASTE:
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                return false;

            // ========== OBSIDIAN MACROS ==========
            case OBS_QUOTE:
                SEND_STRING("\\\"");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case OBS_PAREN:
                SEND_STRING("\\(\\)");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                return false;

            case OBS_EMDASH:
                SEND_STRING("---");
                return false;

            // ========== WRAP OPERATIONS (for Google Docs) ==========
            case WRAP_QUOTE:
                // Cut current selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);                // Wait for clipboard
                SEND_STRING("\"");           // Opening quote
                wait_ms(150);
                // Paste
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING("\" ");          // Closing quote + space
                return false;

            case WRAP_PAREN:
                // Cut current selection
                register_code(KC_LGUI);
                tap_code(KC_X);
                unregister_code(KC_LGUI);
                wait_ms(150);                // Wait for clipboard
                SEND_STRING("(");            // Opening paren
                wait_ms(150);
                // Paste
                register_code(KC_LGUI);
                tap_code(KC_V);
                unregister_code(KC_LGUI);
                wait_ms(150);
                SEND_STRING(") ");           // Closing paren + space
                return false;

            // ========== GOOGLE DOCS HEADERS ==========
            case GDOC_H1:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_1);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_H2:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_2);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_H3:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_3);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case GDOC_NORMAL:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                tap_code(KC_0);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                return false;

            case AC_TOG:
                // Toggle autocorrect
                autocorrect_toggle();

                // Temporarily disable layer indication
                rgblight_layers = NULL;

                // Enable RGB if it's off
                if (!rgblight_is_enabled()) {
                    rgblight_enable_noeeprom();
                }

                // Visual feedback
                if (autocorrect_is_enabled()) {
                    // Flash once for ON - bright white flash
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv_noeeprom(0, 0, 255);  // White
                    rgblight_set();  // Force update
                    wait_ms(200);
                    rgblight_sethsv_noeeprom(0, 0, 0);    // Off
                    rgblight_set();  // Force update
                    wait_ms(200);
                } else {
                    // Flash twice for OFF - red flashes
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    for (int i = 0; i < 2; i++) {
                        rgblight_sethsv_noeeprom(0, 255, 255);  // Red
                        rgblight_set();  // Force update
                        wait_ms(200);
                        rgblight_sethsv_noeeprom(0, 0, 0);      // Off
                        rgblight_set();  // Force update
                        wait_ms(200);
                    }
                }

                // Re-enable layer indication
                rgblight_layers = my_rgb_layers;
                // Force layer update to restore original color
                layer_state_set_user(layer_state);

                return false;

            case DOUBLE_ZERO:
                // Type "00" for numpad
                tap_code(KC_P0);
                tap_code(KC_P0);
                return false;

            case DUMP_KM:
                // Placeholder for keymap dump functionality
                // This would normally dump the keymap to console
                // For now, just print a message if console is enabled
                #ifdef CONSOLE_ENABLE
                    uprintf("DUMP_KM pressed - feature not implemented in this build\n");
                #endif
                return false;
        }
    }

    // Handle Auto Shift toggle visual feedback
    if (keycode == AS_TOGG && record->event.pressed) {
        // Get current state before the toggle
        bool was_enabled = get_autoshift_state();

        // Temporarily disable layer indication
        rgblight_layers = NULL;

        // Enable RGB if it's off
        if (!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }

        // The toggle will happen after we return true
        // So we check the opposite of current state
        if (!was_enabled) {  // Will be ON after toggle
            // Flash once for ON - green flash
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(85, 255, 255);  // Green (HSV: 85 degrees)
            rgblight_set();  // Force update
            wait_ms(200);
            rgblight_sethsv_noeeprom(0, 0, 0);    // Off
            rgblight_set();  // Force update
            wait_ms(200);
        } else {  // Will be OFF after toggle
            // Flash twice for OFF - blue flashes
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            for (int i = 0; i < 2; i++) {
                rgblight_sethsv_noeeprom(170, 255, 255);  // Blue (HSV: 170 degrees)
                rgblight_set();  // Force update
                wait_ms(200);
                rgblight_sethsv_noeeprom(0, 0, 0);      // Off
                rgblight_set();  // Force update
                wait_ms(200);
            }
        }

        // Re-enable layer indication
        rgblight_layers = my_rgb_layers;
        // Force layer update to restore original color
        layer_state_set_user(layer_state);
    }

    return true;
}

// Called when autocorrect makes a correction
bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    // Temporarily disable layer indication
    rgblight_layers = NULL;

    // Enable RGB if it's off
    if (!rgblight_is_enabled()) {
        rgblight_enable_noeeprom();
    }

    // Quick purple flash to indicate a correction was made
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(213, 255, 255);  // Purple (HSV: 213 degrees)
    rgblight_set();  // Force update
    wait_ms(100);  // Quick flash

    // Re-enable layer indication
    rgblight_layers = my_rgb_layers;
    // Force layer update to restore original color
    layer_state_set_user(layer_state);

    // Return true to allow the correction to happen
    return true;
}
