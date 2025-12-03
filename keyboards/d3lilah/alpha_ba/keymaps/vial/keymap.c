#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"
#include "print.h"

#define HOME 0
#define MODS 1
#define MODS2 2
#define OTHER 3

enum custom_keycodes {
    DUMP_KM = QK_KB_0,
    AC_TOG,
    MACRO1
};

// ========== RGB Layer Definitions ==========
// Layer 0 (HOME) - Green (HSV: 85)
const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 11, 85, 255, 128}
);

// Layer 1 (MODS) - Purple (HSV: 191)
const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 11, 191, 255, 128}
);

// Layer 2 (MODS2) - Pink (HSV: 234)
const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 11, 234, 255, 128}
);

// Layer 3 (OTHER) - Yellow (HSV: 43)
const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 11, 43, 255, 128}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_0,
    layer_1,
    layer_2,
    layer_3
);

// ========== Keymap Dump Function ==========
void dump_keymap_as_c(void) {
    uprintf("\n// ========== VIAL Keymap Export ==========\n");
    uprintf("// Copy this into your keymap.c file\n");
    uprintf("// Generated on Alpha-BA keyboard\n\n");
    uprintf("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n");

    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        uprintf("    [%u] = LAYOUT( // Layer %u\n", layer, layer);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uprintf("        ");
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                uint16_t kc = dynamic_keymap_get_keycode(layer, row, col);

                // Convert common keycodes to readable format
                if (kc == KC_NO) {
                    uprintf("XXXXXXX");
                } else if (kc == KC_TRNS) {
                    uprintf("_______");
                } else {
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

// ========== Layer State Handling ==========
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, true);
    return state;
}

// ========== Initialization ==========
void keyboard_post_init_user(void) {
    // Enable RGB layer indication
    rgblight_layers = my_rgb_layers;

    // Wait for USB/console to be ready before dumping
    wait_ms(1000);
    // Dump keymap once after boot for debugging
    dump_keymap_as_c();

    // Enable autocorrect by default
    autocorrect_enable();
}

// ========== Key Processing ==========
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DUMP_KM:
                // Dump current keymap to console
                dump_keymap_as_c();

                // Visual feedback - quick cyan flash
                #ifdef RGBLIGHT_ENABLE
                rgblight_layers = NULL;
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv_noeeprom(128, 255, 255);  // Cyan
                rgblight_set();
                wait_ms(100);
                rgblight_sethsv_noeeprom(0, 0, 0);
                rgblight_set();
                rgblight_layers = my_rgb_layers;
                layer_state_set_user(layer_state);
                #endif

                return false;

            case AC_TOG:
                // Toggle autocorrect
                autocorrect_toggle();

                #ifdef RGBLIGHT_ENABLE
                rgblight_layers = NULL;
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                if (autocorrect_is_enabled()) {
                    // Flash once for ON - blue flash
                    rgblight_sethsv_noeeprom(170, 255, 255);  // Blue
                    rgblight_set();
                    wait_ms(150);
                    rgblight_sethsv_noeeprom(0, 0, 0);    // Off
                    rgblight_set();
                    wait_ms(150);
                } else {
                    // Flash twice for OFF - blue flashes
                    for (int i = 0; i < 2; i++) {
                        rgblight_sethsv_noeeprom(170, 255, 255);  // Blue
                        rgblight_set();
                        wait_ms(150);
                        rgblight_sethsv_noeeprom(0, 0, 0);      // Off
                        rgblight_set();
                        wait_ms(150);
                    }
                }
                rgblight_layers = my_rgb_layers;
                layer_state_set_user(layer_state);
                #endif

                return false;

            case MACRO1:
                SEND_STRING("I'm so sorry... -PyroL");
                return false;
        }
    }
    return true;
}

// ========== Autocorrect Visual Feedback ==========
bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    #ifdef RGBLIGHT_ENABLE
    rgblight_layers = NULL;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(170, 255, 255);  // Long blue flash for correction
    rgblight_set();
    wait_ms(300);
    rgblight_sethsv_noeeprom(0, 0, 0);
    rgblight_set();
    rgblight_layers = my_rgb_layers;
    layer_state_set_user(layer_state);
    #endif

    return true;
}

// ========== Bootloader Visual Feedback ==========
bool shutdown_user(bool jump_to_bootloader) {
    #ifdef RGBLIGHT_ENABLE
    if (jump_to_bootloader) {
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        // Flash magenta rapidly before entering bootloader
        for (int i = 0; i < 5; i++) {
            rgblight_sethsv_noeeprom(213, 255, 255);  // Magenta
            rgblight_set();
            wait_ms(100);
            rgblight_sethsv_noeeprom(0, 0, 0);
            rgblight_set();
            wait_ms(100);
        }
    }
    #endif
    return true;
}

// ========== Keymaps ==========
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HOME] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, TO(1),
        KC_Z, KC_X, KC_C, KC_V, MT(MOD_LSFT, KC_SPC), KC_B, KC_N, KC_M),

    [MODS] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_BSPC, KC_ESC, KC_TAB, KC_SCLN, KC_QUOT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, TO(2),
        KC_LCTL, KC_LGUI, KC_LALT, TO(0), MT(MOD_LSFT, KC_ENT), KC_COMM, KC_DOT, KC_SLSH),

    [MODS2] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_LSFT, KC_F11, KC_F12, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, TO(3),
        RGB_VAI, RGB_VAD, RGB_HUI, TO(0), RGB_MOD, KC_MPLY, KC_VOLD, KC_VOLU),

    [OTHER] = LAYOUT(
        QK_BOOT, DUMP_KM, AC_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, TO(0), MACRO1, KC_NO, KC_NO, KC_NO),
};
