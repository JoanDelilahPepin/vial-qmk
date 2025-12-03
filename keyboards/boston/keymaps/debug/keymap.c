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
#include "dynamic_keymap.h"
#include "print.h"

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
    DUMP_KM  // Dump keymap to console
};

    /* Due to how the matrix is setup - the right split backspace key is, for firmware purposes the key to the right of up arrow, which on the actual keyboard is a blocker*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_all(
	KC_MUTE, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , KC_F23 , KC_F24 ,                  KC_MPRV, KC_MPLY,  KC_MNXT ,          KC_INS , KC_HOME, KC_PGUP,
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,                  KC_PSCR, KC_SCRL,  KC_PAUSE,          KC_DEL , KC_END , KC_PGDN,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL ,  KC_BSPC, KC_BSPC,        KC_CALC,           KC_NUM , KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC,  KC_BSLS,                 RGB_TOG,           KC_P7   , KC_P8  , KC_P9  , KC_PEQL,
    KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,  KC_ENT ,                 KC_MSEL,           KC_P4   , KC_P5  , KC_P6  , KC_PPLS,
    KC_LSFT, KC_BSLS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,                           KC_UP  ,           KC_P1   , KC_P2  , KC_P3  , KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC , KC_SPC , KC_SPC ,                   KC_RALT, KC_APP , KC_RCTL,                          KC_LEFT,  KC_DOWN, KC_RGHT,  KC_P0   , KC_P0  , KC_PDOT
    ),

   [1] = LAYOUT_all(

    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______, _______,        _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                           _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,         _______ ,_______ ,_______ ,                  _______ ,_______ ,_______ ,                          _______,  _______, _______,  _______ , _______, _______
    ),

   [2] = LAYOUT_all(

    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______, _______,        _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                           _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,         _______ ,_______ ,_______ ,                  _______ ,_______ ,_______ ,                          _______,  _______, _______,  _______ , _______, _______
    ),

   [3] = LAYOUT_all(

    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                  _______, _______,  _______ ,          _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______, _______,        _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,  _______,                 _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                           _______,           _______ , _______, _______, _______,
    _______,_______,_______ ,         _______ ,_______ ,_______ ,                  _______ ,_______ ,_______ ,                          _______,  _______, _______,  _______ , _______, _______
    )
};

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

// Forward declarations
void dump_keymap_as_c(void);
void dump_macros_as_c(void);
#ifdef VIAL_COMBO_ENABLE
void dump_combos_as_c(void);
#endif
#ifdef VIAL_TAP_DANCE_ENABLE
void dump_tap_dances_as_c(void);
#endif
#ifdef VIAL_KEY_OVERRIDE_ENABLE
void dump_key_overrides_as_c(void);
#endif
void dump_all_vial_config(void);

// Function to dump VIAL macros
void dump_macros_as_c(void) {
    uint16_t macro_buffer_size = dynamic_keymap_macro_get_buffer_size();
    uint8_t macro_count = dynamic_keymap_macro_get_count();

    uprintf("\n// ========== VIAL Macros Export ==========\n");
    uprintf("// Total macro slots available: %d\n", macro_count);
    uprintf("// Macro buffer size: %d bytes\n\n", macro_buffer_size);

    // Read macro buffer in small chunks to avoid stack overflow
    #define CHUNK_SIZE 64
    uint8_t chunk[CHUNK_SIZE];
    uint16_t offset = 0;
    uint8_t macro_num = 0;
    bool in_macro = false;

    while (offset < macro_buffer_size && macro_num < macro_count) {
        // Read a chunk
        uint16_t bytes_to_read = (macro_buffer_size - offset) > CHUNK_SIZE ? CHUNK_SIZE : (macro_buffer_size - offset);
        dynamic_keymap_macro_get_buffer(offset, bytes_to_read, chunk);

        // Process the chunk
        for (uint16_t i = 0; i < bytes_to_read; i++) {
            if (chunk[i] == 0) {
                if (in_macro) {
                    // End of macro
                    uprintf("\n\n");
                    in_macro = false;
                }
                macro_num++;
                if (macro_num >= macro_count) break;
            } else {
                if (!in_macro) {
                    // Start of new macro
                    uprintf("// Macro %d:\n", macro_num);
                    uprintf("// Raw bytes: ");
                    in_macro = true;
                }
                uprintf("0x%02X ", chunk[i]);
            }
        }
        offset += bytes_to_read;
    }

    if (in_macro) {
        uprintf("\n\n");
    }
}

#ifdef VIAL_COMBO_ENABLE
// Function to dump VIAL combos
void dump_combos_as_c(void) {
    uprintf("\n// ========== VIAL Combos Export ==========\n");
    uprintf("#ifdef COMBO_ENABLE\n\n");

    vial_combo_entry_t combo_entry;
    uint8_t valid_combos = 0;

    // First pass: count valid combos
    for (uint8_t i = 0; i < VIAL_COMBO_ENTRIES; i++) {
        if (dynamic_keymap_get_combo(i, &combo_entry) == 0) {
            if (combo_entry.input[0] != 0 || combo_entry.output != 0) {
                valid_combos++;
            }
        }
    }

    uprintf("// %d combos configured (of %d available)\n\n", valid_combos, VIAL_COMBO_ENTRIES);

    // Second pass: output combo definitions
    for (uint8_t i = 0; i < VIAL_COMBO_ENTRIES; i++) {
        if (dynamic_keymap_get_combo(i, &combo_entry) == 0) {
            if (combo_entry.input[0] != 0 || combo_entry.output != 0) {
                uprintf("// Combo %d:\n", i);
                uprintf("// Input keys: 0x%04X", combo_entry.input[0]);
                for (uint8_t j = 1; j < 4; j++) {
                    if (combo_entry.input[j] != 0) {
                        uprintf(", 0x%04X", combo_entry.input[j]);
                    }
                }
                uprintf("\n// Output: 0x%04X\n\n", combo_entry.output);
            }
        }
    }

    uprintf("#endif // COMBO_ENABLE\n");
}
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
// Function to dump VIAL tap dances
void dump_tap_dances_as_c(void) {
    uprintf("\n// ========== VIAL Tap Dances Export ==========\n");
    uprintf("#ifdef TAP_DANCE_ENABLE\n\n");

    vial_tap_dance_entry_t td_entry;
    uint8_t valid_tds = 0;

    // Count valid tap dances
    for (uint8_t i = 0; i < VIAL_TAP_DANCE_ENTRIES; i++) {
        if (dynamic_keymap_get_tap_dance(i, &td_entry) == 0) {
            if (td_entry.on_tap != 0 || td_entry.on_hold != 0 ||
                td_entry.on_double_tap != 0 || td_entry.on_tap_hold != 0) {
                valid_tds++;
            }
        }
    }

    uprintf("// %d tap dances configured (of %d available)\n\n", valid_tds, VIAL_TAP_DANCE_ENTRIES);

    // Output tap dance definitions
    for (uint8_t i = 0; i < VIAL_TAP_DANCE_ENTRIES; i++) {
        if (dynamic_keymap_get_tap_dance(i, &td_entry) == 0) {
            if (td_entry.on_tap != 0 || td_entry.on_hold != 0 ||
                td_entry.on_double_tap != 0 || td_entry.on_tap_hold != 0) {
                uprintf("// Tap Dance %d:\n", i);
                uprintf("// On Tap: 0x%04X\n", td_entry.on_tap);
                uprintf("// On Hold: 0x%04X\n", td_entry.on_hold);
                uprintf("// On Double Tap: 0x%04X\n", td_entry.on_double_tap);
                uprintf("// On Tap-Hold: 0x%04X\n", td_entry.on_tap_hold);
                uprintf("// Tapping Term: %d\n\n", td_entry.custom_tapping_term);
            }
        }
    }

    uprintf("#endif // TAP_DANCE_ENABLE\n");
}
#endif

#ifdef VIAL_KEY_OVERRIDE_ENABLE
// Function to dump VIAL key overrides
void dump_key_overrides_as_c(void) {
    uprintf("\n// ========== VIAL Key Overrides Export ==========\n");
    uprintf("#ifdef KEY_OVERRIDE_ENABLE\n\n");

    vial_key_override_entry_t ko_entry;
    uint8_t valid_kos = 0;

    // Count valid key overrides
    for (uint8_t i = 0; i < VIAL_KEY_OVERRIDE_ENTRIES; i++) {
        if (dynamic_keymap_get_key_override(i, &ko_entry) == 0) {
            if (ko_entry.trigger != 0 || ko_entry.replacement != 0) {
                valid_kos++;
            }
        }
    }

    uprintf("// %d key overrides configured (of %d available)\n\n", valid_kos, VIAL_KEY_OVERRIDE_ENTRIES);

    // Output key override definitions
    for (uint8_t i = 0; i < VIAL_KEY_OVERRIDE_ENTRIES; i++) {
        if (dynamic_keymap_get_key_override(i, &ko_entry) == 0) {
            if (ko_entry.trigger != 0 || ko_entry.replacement != 0) {
                uprintf("// Key Override %d:\n", i);
                uprintf("// Trigger: 0x%04X\n", ko_entry.trigger);
                uprintf("// Replacement: 0x%04X\n", ko_entry.replacement);
                uprintf("// Layers: 0x%04X\n", ko_entry.layers);
                uprintf("// Mods: 0x%02X\n", ko_entry.trigger_mods);
                uprintf("// Options: 0x%02X\n\n", ko_entry.options);
            }
        }
    }

    uprintf("#endif // KEY_OVERRIDE_ENABLE\n");
}
#endif

// Function to dump ALL VIAL configuration
void dump_all_vial_config(void) {
    // Dump keymap
    dump_keymap_as_c();

    // Dump macros
    dump_macros_as_c();

    // Dump combos if enabled
    #ifdef VIAL_COMBO_ENABLE
    dump_combos_as_c();
    #endif

    // Dump tap dances if enabled
    #ifdef VIAL_TAP_DANCE_ENABLE
    dump_tap_dances_as_c();
    #endif

    // Dump key overrides if enabled
    #ifdef VIAL_KEY_OVERRIDE_ENABLE
    dump_key_overrides_as_c();
    #endif

    uprintf("\n// ========== Complete VIAL Export Done ==========\n\n");
}

// Function to dump current VIAL keymap in keymap.c format
void dump_keymap_as_c(void) {
    uprintf("\n// ========== VIAL Keymap Export ==========\n");
    uprintf("// Copy this into your keymap.c file\n");
    uprintf("// Generated on Boston keyboard\n\n");
    uprintf("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n");

    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        uprintf("    [%u] = LAYOUT_all( // Layer %u\n", layer, layer);

        // Boston has a specific matrix layout, let's output in a more readable format
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uprintf("        ");
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t kc = dynamic_keymap_get_keycode(layer, row, col);

                // Try to convert common keycodes to names for readability
                if (kc == KC_NO) {
                    uprintf("XXXXXXX");
                } else if (kc == KC_TRNS) {
                    uprintf("_______");
                } else if (kc < 0x100) {
                    // Basic keycodes - could expand this with a lookup table
                    uprintf("0x%04X", kc);
                } else {
                    // Special keycodes, layers, etc
                    uprintf("0x%04X", kc);
                }

                if (col < MATRIX_COLS - 1) uprintf(", ");
            }
            if (row < MATRIX_ROWS - 1) {
                uprintf(",\n");
            } else {
                uprintf("\n");
            }
        }

        if (layer < DYNAMIC_KEYMAP_LAYER_COUNT - 1) {
            uprintf("    ),\n\n");
        } else {
            uprintf("    )\n");
        }
    }
    uprintf("};\n");
    uprintf("// ========== End Export ==========\n\n");
}

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

            case DUMP_KM:
                // Dump complete VIAL configuration to console
                dump_all_vial_config();

                // Optional: Quick visual feedback that dump occurred
                rgblight_layers = NULL;
                if (!rgblight_is_enabled()) {
                    rgblight_enable_noeeprom();
                }

                // Quick cyan flash to indicate dump
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv_noeeprom(120, 255, 255);  // Cyan
                rgblight_set();
                wait_ms(100);
                rgblight_sethsv_noeeprom(0, 0, 0);
                rgblight_set();
                wait_ms(100);

                // Re-enable layer indication
                rgblight_layers = my_rgb_layers;
                layer_state_set_user(layer_state);

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
