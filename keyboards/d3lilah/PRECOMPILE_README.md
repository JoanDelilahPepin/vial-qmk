# Pre-compiling VIAL Configuration into QMK Firmware

This guide documents the process of taking a VIAL configuration dump and pre-compiling it into QMK firmware so that keyboards work perfectly out-of-the-box without needing to load a .vil file.

## Overview

VIAL normally stores configuration dynamically in EEPROM, which means a fresh firmware flash results in an unconfigured keyboard. This process allows you to "bake in" your VIAL configuration directly into the firmware, giving you the best of both worlds:
- Keyboard works immediately after flashing with your exact configuration
- VIAL GUI can still be used to make changes dynamically

## Prerequisites

1. A working VIAL keymap with the `DUMP_KM` custom keycode
2. Your desired configuration already set up in VIAL GUI
3. Console enabled in your debug keymap (`CONSOLE_ENABLE = yes` in rules.mk)

## Step 1: Create a Debug Keymap with Dump Functionality

First, create a debug keymap that can export your VIAL configuration:

```c
// In keymap.c, add this custom keycode
enum custom_keycodes {
    DUMP_KM = QK_KB_0,
    // ... other keycodes
};

// In process_record_user, add the dump functionality
case DUMP_KM:
    if (record->event.pressed) {
        // Dump keymap
        uprintf("\n\n========== VIAL Configuration Export ==========\n");
        uprintf("// Keymap exported from VIAL configuration\n");
        uprintf("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n");

        for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
            uprintf("    [%d] = LAYOUT_all( // Layer %d\n", layer, layer);
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                uprintf("        ");
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
                    uprintf("0x%04X", keycode);
                    if (col < MATRIX_COLS - 1) uprintf(", ");
                }
                if (row < MATRIX_ROWS - 1) uprintf(",");
                uprintf("\n");
            }
            uprintf("    )%s\n", (layer < DYNAMIC_KEYMAP_LAYER_COUNT - 1) ? "," : "");
        }
        uprintf("};\n");

        // Dump tap dances
        #ifdef VIAL_TAP_DANCE_ENABLE
        uprintf("\n// Tap Dance configurations (count: %d)\n", VIAL_TAP_DANCE_ENTRIES);
        for (uint8_t i = 0; i < VIAL_TAP_DANCE_ENTRIES; i++) {
            vial_tap_dance_entry_t td;
            if (dynamic_keymap_get_tap_dance(i, &td) == 0) {
                if (td.on_tap != KC_NO || td.on_hold != KC_NO) {
                    uprintf("// TD(%d): tap=0x%04X, hold=0x%04X, double=0x%04X, tap_hold=0x%04X, term=%d\n",
                            i, td.on_tap, td.on_hold, td.on_double_tap, td.on_tap_hold, td.custom_tapping_term);
                }
            }
        }
        #endif

        // Dump macros
        uprintf("\n// Macro definitions\n");
        dump_macros_as_c(); // Implementation details in debug keymap

        uprintf("\n========== Export Complete ==========\n\n");
    }
    return false;
```

## Step 2: Export Your Configuration

1. Flash the debug firmware to your keyboard
2. Open a console monitor (QMK Toolbox or similar)
3. Press the `DUMP_KM` key
4. Copy the entire output between the `==========` markers

## Step 3: Create Your Pre-compiled Keymap

Create a new keymap (e.g., `keymaps/precompiled`) based on your existing VIAL keymap.

### Essential Files

#### rules.mk
```makefile
# Enable VIAL with pre-compiled defaults
VIA_ENABLE = yes
VIAL_ENABLE = yes
QMK_SETTINGS = yes

# Enable features as needed
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
AUTOCORRECT_ENABLE = yes
# ... other features
```

#### config.h
```c
#pragma once

// VIAL configuration
#define VIAL_KEYBOARD_UID {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX}
#define VIAL_UNLOCK_COMBO_ROWS {1, 4}
#define VIAL_UNLOCK_COMBO_COLS {0, 13}

// Feature configuration
#define VIAL_TAP_DANCE_ENTRIES 8
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// Auto Shift defaults (if using)
#ifdef AUTO_SHIFT_ENABLE
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_ALPHA  // Configure as needed
#endif
```

## Step 4: Map the Dump to Your Layout

The dump provides raw matrix positions (ROWS × COLS). You need to map these to your keyboard's layout macro (e.g., `LAYOUT_all`).

### Important Conversions

1. **Keycodes**: Replace hex values with QMK keycodes:
   ```c
   0x0029 → KC_ESC
   0x001E → KC_1
   0x5221 → MO(1)  // Layer momentary
   0x5700 → TD(0)  // Tap dance 0
   ```

2. **Custom Keycodes**: Define your custom keycodes:
   ```c
   enum custom_keycodes {
       MY_MACRO = QK_KB_0,
       // ... other custom keycodes
   };
   ```

3. **Layout Mapping**: Account for your keyboard's physical layout:
   - Some matrix positions might not be used
   - Split keys (like split backspace) need special handling
   - ISO vs ANSI differences

## Step 5: Initialize Tap Dances

Tap dances need special initialization in EEPROM:

```c
// Define tap dance names
enum {
    TD_LAYER_SWITCH = 0,
    TD_FEATURE_TOG = 1
};

void keyboard_post_init_user(void) {
    #ifdef VIAL_TAP_DANCE_ENABLE
    vial_tap_dance_entry_t td;

    // Initialize TD(0) if unconfigured
    if (dynamic_keymap_get_tap_dance(TD_LAYER_SWITCH, &td) == 0) {
        if (td.on_tap == KC_NO || td.on_tap == 0xFFFF) {
            td.on_tap = TO(0);
            td.on_hold = TO(3);
            td.on_double_tap = TO(1);
            td.on_tap_hold = TO(2);
            td.custom_tapping_term = 235;
            dynamic_keymap_set_tap_dance(TD_LAYER_SWITCH, &td);
        }
    }
    // Repeat for other tap dances...
    #endif
}
```

## Step 6: Initialize QMK Settings

For features like Auto Shift that use QMK Settings:

```c
void keyboard_post_init_user(void) {
    #ifdef AUTO_SHIFT_ENABLE
    // Enable Auto Shift
    autoshift_enable();
    set_autoshift_timeout(175);

    #ifdef QMK_SETTINGS
    // Initialize QMK Settings in EEPROM
    // Auto shift byte is at offset 24 in the settings structure
    const uint16_t AUTO_SHIFT_OFFSET = 24;
    uint8_t auto_shift_byte = dynamic_keymap_get_qmk_settings(AUTO_SHIFT_OFFSET);

    if (auto_shift_byte == 0xFF || !(auto_shift_byte & 1)) {
        // Set enable bit and configuration
        auto_shift_byte = 0x11; // Enable + no alpha shifting
        dynamic_keymap_set_qmk_settings(AUTO_SHIFT_OFFSET, auto_shift_byte);
    }
    #endif
    #endif
}
```

## Step 7: Add Custom Macros

Implement any custom macros from your dump:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DOUBLE_ZERO:
                tap_code(KC_P0);
                tap_code(KC_P0);
                return false;

            case MY_MACRO:
                SEND_STRING("My text");
                return false;
            // ... other macros
        }
    }
    return true;
}
```

## Step 8: Test and Verify

1. Compile the firmware:
   ```bash
   qmk compile -kb yourkeyboard -km precompiled
   ```

2. Flash and test:
   - All keys should work immediately
   - Tap dances should function without configuration
   - Custom macros should be active
   - VIAL GUI should still allow modifications

## Troubleshooting

### Tap dances appear but don't work
- Ensure tap dance initialization runs in `keyboard_post_init_user()`
- Check that TD indices match between enum and initialization
- Verify `TAP_DANCE_ENABLE = yes` in rules.mk

### Auto Shift not enabled by default
- QMK Settings need explicit EEPROM initialization
- The enable bit must be set in the auto_shift byte
- Check QMK_SETTINGS is enabled

### Keymap doesn't match physical layout
- Verify matrix-to-layout mapping
- Account for unused matrix positions
- Check for split keys (backspace, shift, etc.)

### Compilation errors
- Ensure all custom keycodes are defined
- Include necessary headers (`#include <stddef.h>` for offsetof)
- Check that feature flags match between config and code

## Benefits

This approach provides:
- ✅ Immediate functionality after flashing
- ✅ No need to distribute .vil files
- ✅ Factory-fresh experience for end users
- ✅ VIAL GUI still works for customization
- ✅ Configuration survives in compiled firmware

## Example Implementations

See the following keymaps for reference:
- `keyboards/boston/keymaps/d3lilah_v_0_9/` - Full implementation with tap dances, Auto Shift, and custom macros
- `keyboards/boston/keymaps/debug/` - Debug keymap with dump functionality

## Notes

- This process works with any VIAL-enabled keyboard
- The debug dump captures the current EEPROM state
- Pre-compiled settings can be overridden via VIAL GUI
- Consider firmware size constraints on memory-limited MCUs