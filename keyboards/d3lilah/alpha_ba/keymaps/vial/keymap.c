#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"
#include "print.h"
#include "vial.h"
#include "qmk_settings.h"
#ifdef HAPTIC_ENABLE
#include "haptic.h"
#include "drv2605l.h"
#endif

#define HOME 0
#define MODS 1
#define MODS2 2
#define OTHER 3

enum custom_keycodes {
    DUMP_KM = QK_KB_0,
    AC_TOG,
    MACRO1,
    HPT_TEST  // Haptic test keycode
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

// ========== Forward declarations ==========
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

// ========== Macros Dump Function ==========
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
// ========== Combos Dump Function ==========
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
// ========== Tap Dances Dump Function ==========
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
// ========== Key Overrides Dump Function ==========
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

// ========== Master Dump Function ==========
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

// ========== Layer State Handling ==========
static uint8_t previous_layer = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));

    // Haptic feedback on layer change
    #ifdef HAPTIC_ENABLE
    uint8_t current_layer = get_highest_layer(state);
    if (current_layer != previous_layer) {
        switch (current_layer) {
            case HOME:
                drv2605l_pulse(DRV2605L_EFFECT_STRONG_CLICK_100);
                break;
            case MODS:
                drv2605l_pulse(DRV2605L_EFFECT_DOUBLE_CLICK_100);
                break;
            case MODS2:
                drv2605l_pulse(DRV2605L_EFFECT_TRIPLE_CLICK_100);
                break;
            case OTHER:
                drv2605l_pulse(DRV2605L_EFFECT_SHARP_TICK_1_100);
                break;
        }
        previous_layer = current_layer;
    }
    #endif

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

    // Initialize haptic feedback
    #ifdef HAPTIC_ENABLE
    uprintf("Initializing haptic feedback...\n");
    haptic_init();
    haptic_enable();

    // Set to a strong click effect (mode 1)
    haptic_set_mode(1);
    // Set feedback to max
    haptic_set_feedback(255);

    uprintf("Haptic enabled: %d\n", haptic_get_enable());
    uprintf("Haptic mode: %d\n", haptic_get_mode());
    uprintf("Haptic feedback: %d\n", haptic_get_feedback());

    // Try to trigger haptic feedback multiple times
    uprintf("Testing haptic play...\n");
    haptic_play();
    wait_ms(200);
    haptic_play();
    wait_ms(200);
    haptic_play();
    uprintf("Haptic test complete\n");
    #endif

    // Wait for USB/console to be ready before dumping
    wait_ms(1000);
    // Dump all VIAL configuration once after boot for debugging
    dump_all_vial_config();

    // Enable autocorrect by default
    autocorrect_enable();

    // Initialize Auto Shift settings
    #ifdef AUTO_SHIFT_ENABLE
    autoshift_enable();
    set_autoshift_timeout(300);  // 300ms timeout for testing (can adjust as needed)

    #ifdef QMK_SETTINGS
    // Write Auto Shift enable state to EEPROM
    // The auto_shift byte is at offset 27 in qmk_settings_t
    const uint16_t AUTO_SHIFT_OFFSET = 27;

    // Always set it to our desired configuration
    // Bit 0 (0x01): enable = ON
    // Bit 1 (0x02): modifiers = OFF
    // Bit 2 (0x04): no_auto_shift_special = OFF
    // Bit 3 (0x08): no_auto_shift_numeric = OFF (we WANT numeric shifting!)
    // Bit 4 (0x10): no_auto_shift_alpha = ON (we DON'T want alpha shifting)
    // Bit 5 (0x20): repeat = OFF
    // Bit 6 (0x40): no_auto_repeat = OFF
    uint8_t auto_shift_byte = 0x11;  // Binary: 00010001
    dynamic_keymap_set_qmk_settings(AUTO_SHIFT_OFFSET, auto_shift_byte);
    #endif
    #endif
}

// ========== Key Processing ==========
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DUMP_KM:
                // Dump all VIAL configuration to console
                dump_all_vial_config();

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

                // Haptic feedback: strong buzz ON, short double click OFF
                #ifdef HAPTIC_ENABLE
                if (autocorrect_is_enabled()) {
                    drv2605l_pulse(DRV2605L_EFFECT_STRONG_BUZZ_100);
                } else {
                    drv2605l_pulse(DRV2605L_EFFECT_SHORT_DOUBLE_CLICK_STRONG_1_100);
                }
                #endif

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

            case HPT_TEST:
                #ifdef HAPTIC_ENABLE
                // Test haptic feedback with detailed debug
                uprintf("\n=== HAPTIC TEST ===\n");
                uprintf("Haptic enabled: %d\n", haptic_get_enable());
                uprintf("Haptic mode: %d\n", haptic_get_mode());
                uprintf("Haptic feedback: %d\n", haptic_get_feedback());

                // Try different modes
                uprintf("Testing different modes...\n");
                for (uint8_t mode = 1; mode <= 10; mode++) {
                    uprintf("Mode %d: ", mode);
                    haptic_set_mode(mode);
                    haptic_set_feedback(255);  // Max feedback
                    haptic_play();
                    wait_ms(300);
                }

                // Reset to mode 1
                haptic_set_mode(1);
                haptic_set_feedback(255);

                // Visual feedback - quick white flash
                #ifdef RGBLIGHT_ENABLE
                rgblight_layers = NULL;
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv_noeeprom(0, 0, 255);  // White
                rgblight_set();
                wait_ms(100);
                rgblight_sethsv_noeeprom(0, 0, 0);
                rgblight_set();
                rgblight_layers = my_rgb_layers;
                layer_state_set_user(layer_state);
                #endif
                uprintf("=== HAPTIC TEST COMPLETE ===\n\n");
                #endif
                return false;
        }
    }

    // Handle Auto Shift toggle visual feedback
    if (keycode == AS_TOGG && record->event.pressed) {
        // Get current state before the toggle
        bool was_enabled = get_autoshift_state();

        // Haptic feedback: strong buzz ON, short double click OFF
        // Toggle happens after we return, so check opposite
        #ifdef HAPTIC_ENABLE
        if (!was_enabled) {
            drv2605l_pulse(DRV2605L_EFFECT_STRONG_BUZZ_100);
        } else {
            drv2605l_pulse(DRV2605L_EFFECT_SHORT_DOUBLE_CLICK_STRONG_1_100);
        }
        #endif

        #ifdef RGBLIGHT_ENABLE
        // Temporarily disable layer indication
        rgblight_layers = NULL;

        // Enable RGB if it's off
        if (!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }

        // The toggle will happen after we return true
        // So we check the opposite of current state
        if (!was_enabled) {  // Will be ON after toggle
            // Flash once for ON - pink flash
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(234, 255, 255);  // Pink
            rgblight_set();  // Force update
            wait_ms(200);
            rgblight_sethsv_noeeprom(0, 0, 0);    // Off
            rgblight_set();  // Force update
            wait_ms(200);
        } else {  // Will be OFF after toggle
            // Flash twice for OFF - pink flashes
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            for (int i = 0; i < 2; i++) {
                rgblight_sethsv_noeeprom(234, 255, 255);  // Pink
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
        #endif
    }

    return true;
}

// ========== Autocorrect Visual Feedback ==========
bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    // Strong triple pulse when autocorrect fires
    #ifdef HAPTIC_ENABLE
    drv2605l_pulse(DRV2605L_EFFECT_TRIPLE_CLICK_100);
    #endif

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
        UG_VALU, UG_VALD, UG_HUEU, TO(0), UG_NEXT, KC_MPLY, KC_VOLD, KC_VOLU),

    [OTHER] = LAYOUT(
        QK_BOOT, DUMP_KM, AC_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, TO(0), MACRO1, KC_NO, KC_NO, KC_NO),
};
