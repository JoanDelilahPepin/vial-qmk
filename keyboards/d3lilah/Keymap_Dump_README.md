# D3lilah's VIAL Keymap Dump Feature

A utility feature to export your VIAL-configured keymap to valid keymap.c format. This allows you to perfect your layout in the VIAL GUI, then export it for compilation into the firmware.

## Overview

When you configure your keyboard layout using VIAL's GUI, those changes are stored dynamically in EEPROM. This feature allows you to dump the current dynamic keymap to the QMK console in valid C code format that can be copied directly into your keymap.c file.

## Features

- Exports all configured layers in valid C syntax
- Outputs in LAYOUT_all format (or your keyboard's specific layout macro)
- Converts common keycodes to readable format (KC_NO → XXXXXXX, KC_TRNS → _______)
- Includes layer numbers as comments for clarity
- Quick cyan LED flash confirms dump operation

## Setup

### 1. Enable Required Features

In your `rules.mk`:

```makefile
# Enable console for keymap dumping
CONSOLE_ENABLE = yes

# Required for VIAL dynamic keymap access
VIA_ENABLE = yes
VIAL_ENABLE = yes
```

### 2. Add Custom Keycode

In your `keymap.c`:

```c
#include QMK_KEYBOARD_H
#include "dynamic_keymap.h"
#include "print.h"

enum custom_keycodes {
    DUMP_KM = QK_KB_0,  // Or SAFE_RANGE for non-VIAL builds
    // ... other custom keycodes
};
```

### 3. Add Dump Function

```c
// Function to dump current VIAL keymap in keymap.c format
void dump_keymap_as_c(void) {
    uprintf("\n// ========== VIAL Keymap Export ==========\n");
    uprintf("// Copy this into your keymap.c file\n");
    uprintf("// Generated on %s keyboard\n\n", PRODUCT);
    uprintf("const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n");

    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        uprintf("    [%u] = LAYOUT_all( // Layer %u\n", layer, layer);

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
```

### 4. Handle the Keycode

In your `process_record_user` function:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case DUMP_KM:
                // Dump current keymap to console
                dump_keymap_as_c();

                // Optional: Visual feedback
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
            // ... other cases
        }
    }
    return true;
}
```

### 5. Register in VIAL

Add to your `vial.json`:

```json
"customKeycodes": [
    {"name": "Dump KM", "title": "Dump Keymap to Console", "shortName": "DumpKM"},
    // ... other custom keycodes
]
```

## Usage

### 1. Enable QMK Console

#### macOS
```bash
# Install hid_listen
brew install hid_listen

# Run console listener
hid_listen
```

#### Windows
Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) and enable "Console" output.

#### Linux
```bash
# May need to run with sudo
sudo hid_listen
```

### 2. Trigger the Dump

1. Open VIAL and assign the "Dump KM" keycode to any key
2. Press the assigned key
3. Watch for a cyan LED flash confirming the dump
4. Check your console output for the exported keymap

### 3. Use the Export

Copy the output from the console and paste it into your keymap.c file, replacing the existing `keymaps` array.

## Example Output

```c
// ========== VIAL Keymap Export ==========
// Copy this into your keymap.c file
// Generated on Boston keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all( // Layer 0
        0x0029, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F, 0x0040,
        0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048,
        XXXXXXX, XXXXXXX, XXXXXXX,
        // ... more rows ...
    ),

    [1] = LAYOUT_all( // Layer 1
        _______, _______, _______, _______, _______, _______, _______,
        // ... more rows ...
    )
};
// ========== End Export ==========
```

## Advanced: Better Keycode Names

For more readable output, you can extend the function to convert hex values to keycode names:

```c
const char* keycode_to_string(uint16_t keycode) {
    switch (keycode) {
        case KC_A: return "KC_A";
        case KC_B: return "KC_B";
        // ... add more as needed
        case KC_ESC: return "KC_ESC";
        case KC_ENTER: return "KC_ENT";
        case KC_SPACE: return "KC_SPC";
        // Layer keys
        case MO(1): return "MO(1)";
        case TO(0): return "TO(0)";
        default: {
            static char hex[8];
            sprintf(hex, "0x%04X", keycode);
            return hex;
        }
    }
}
```

Then use it in the dump function:
```c
uprintf("%s", keycode_to_string(kc));
```

## Troubleshooting

### Console not showing output
- Ensure CONSOLE_ENABLE = yes in rules.mk
- Check that hid_listen or QMK Toolbox is running
- Try unplugging and replugging the keyboard after starting the console

### Keycode shows as hex instead of name
- This is normal for custom keycodes and complex keycodes
- You can manually replace hex values with proper names after export
- Consider extending the keycode_to_string function for frequently used keys

### LED doesn't flash
- RGB may be disabled - the dump will still work
- Check that RGB is enabled in your config

### Output is truncated
- Console buffer may be limited
- Try dumping one layer at a time by modifying the loop

## Benefits

1. **Perfect in GUI, compile for speed**: Configure complex layouts visually, then compile for faster response
2. **Backup your layout**: Export your perfect layout before experimenting
3. **Share configurations**: Easy to share your exact layout with others
4. **Version control**: Commit your exported layout to git
5. **Debug dynamic keymap**: See exactly what keycodes are stored

## Implementation Status

Currently implemented on:
- Boston (STM32F411) - Full implementation with RGB feedback
- Can be easily ported to any VIAL-enabled keyboard

---
*Last updated: December 2024*
*Created for perfect GUI → firmware workflow*