# D3lilah's Autocorrect Implementation Guide for Vial

This document provides a working pattern for implementing QMK's autocorrect feature with Vial, including visual LED feedback. This setup has been tested and confirmed working on the Boston keyboard.

## The Problem

QMK's autocorrect keycodes (AC_TOGG, AC_ON, AC_OFF) are not exposed in Vial's GUI Quantum tab, even though they are standard QMK keycodes. This makes it difficult to assign the autocorrect toggle to a key through Vial's interface.

## The Solution

Create a custom keycode that wraps the autocorrect functionality and expose it through Vial's custom keycodes section.

## Implementation Steps

### 1. Enable Required Features in `rules.mk`

```makefile
# Vial configuration
VIA_ENABLE = yes
VIAL_ENABLE = yes
QMK_SETTINGS = yes        # Critical for QMK features in Vial
ENCODER_MAP_ENABLE = yes  # If your keyboard has encoders

# Enable features
AUTOCORRECT_ENABLE = yes  # Enable autocorrect feature
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

# Extra features
LAYER_LOCK_ENABLE = yes
TRI_LAYER_ENABLE = yes
```

**Important**: `QMK_SETTINGS = yes` is required for QMK settings to work properly with Vial.

### 2. Add Autocorrect Dictionary

Place your `autocorrect_data.h` file in the keymap directory. You can generate this file using:

```bash
qmk generate-autocorrect-data autocorrect_dictionary.txt
```

For the large 3,667-word Iyada dictionary, the file will be approximately 509KB.

### 3. Define Custom Keycode in `keymap.c`

```c
#include QMK_KEYBOARD_H

// Custom keycodes for pre-compiled macros
// Using QK_KB_0 (USER00) as base for VIAL compatibility
enum custom_keycodes {
    MD_H1 = QK_KB_0,
    // ... other custom keycodes ...
    AC_TOG  // Custom keycode for autocorrect toggle
};
```

### 4. Handle the Custom Keycode in `process_record_user`

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // ... other custom keycodes ...

            case AC_TOG:
                // Toggle autocorrect
                autocorrect_toggle();

                // Visual feedback - save current RGB state
                uint8_t prev_mode = rgblight_get_mode();
                uint8_t prev_hue = rgblight_get_hue();
                uint8_t prev_sat = rgblight_get_sat();
                uint8_t prev_val = rgblight_get_val();

                if (autocorrect_is_enabled()) {
                    // Flash once for ON - bright white flash
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv_noeeprom(0, 0, 255);  // White
                    wait_ms(150);
                    rgblight_sethsv_noeeprom(0, 0, 0);    // Off
                    wait_ms(150);
                } else {
                    // Flash twice for OFF - red flashes
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    for (int i = 0; i < 2; i++) {
                        rgblight_sethsv_noeeprom(0, 255, 255);  // Red
                        wait_ms(150);
                        rgblight_sethsv_noeeprom(0, 0, 0);      // Off
                        wait_ms(150);
                    }
                }

                // Restore previous RGB state
                rgblight_mode_noeeprom(prev_mode);
                rgblight_sethsv_noeeprom(prev_hue, prev_sat, prev_val);

                return false;
        }
    }
    return true;
}
```

### 5. Enable Autocorrect by Default (Optional)

Add this to `keyboard_post_init_user` to enable autocorrect on startup:

```c
void keyboard_post_init_user(void) {
    // ... other initialization ...

    // Enable autocorrect by default
    autocorrect_enable();

    // Optional: Flash once to indicate autocorrect is on
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(0, 0, 255);  // White
    wait_ms(150);
    rgblight_sethsv_noeeprom(0, 0, 0);    // Off
}
```

### 6. Expose the Keycode in `vial.json`

Add the custom keycode to your `vial.json` file's `customKeycodes` array:

```json
"customKeycodes": [
    // ... other custom keycodes ...
    {"name": "AC_TOG", "title": "Toggle Autocorrect", "shortName": "AC Tog"}
],
```

## Special Considerations for RGB Layer Keyboards

If your keyboard uses RGB layers (like the Boston), the layer system may override your flash attempts. Use this enhanced version:

```c
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
```

## Using in Vial

After compiling and flashing:

1. Open Vial
2. Go to the **User** or **Custom** tab (not Quantum)
3. Find **"AC Tog"** or **"Toggle Autocorrect"**
4. Drag it to any key on your layout

## Alternative: Using Raw Keycodes

If you don't want to use custom keycodes, you can use Vial's "Any" key feature:

1. Select a key in Vial
2. Choose "Any"
3. Enter `0x7C76` (hex) or `31862` (decimal) for AC_TOGG

## Visual Feedback

- **One white flash**: Autocorrect enabled
- **Two red flashes**: Autocorrect disabled
- **White flash on startup**: Autocorrect is enabled by default

## Troubleshooting

### Autocorrect not working
- Verify `AUTOCORRECT_ENABLE = yes` in rules.mk
- Check that autocorrect_data.h exists in your keymap folder
- Ensure `QMK_SETTINGS = yes` is set

### Toggle key not showing in Vial
- Confirm the custom keycode is in vial.json
- Make sure you're looking in the User/Custom tab, not Quantum
- Try using the "Any" key with raw value 0x7C76

### LED feedback not working
- Check if RGB is enabled in your keyboard
- For keyboards with RGB layers, use the enhanced version that temporarily disables layers
- Add `rgblight_set()` calls to force LED updates
- Ensure rgblight is enabled with `rgblight_enable_noeeprom()`

## Key Learnings

1. **QMK_SETTINGS = yes** is critical for QMK features in Vial
2. **Custom keycodes** are the most reliable way to expose autocorrect toggle in Vial
3. **RGB layers** can interfere with flash feedback and need special handling
4. **autocorrect_toggle()** and **autocorrect_is_enabled()** are the key functions
5. **Force RGB updates** with `rgblight_set()` when layers are involved

## Files Required

- `rules.mk` - Enable autocorrect and QMK settings
- `keymap.c` - Define and handle AC_TOG custom keycode
- `vial.json` - Expose AC_TOG to Vial interface
- `autocorrect_data.h` - Generated dictionary file
- `config.h` - Optional, for other settings

This pattern has been tested and confirmed working on:
- Boston keyboard with STM32F411
- D_38 handwired with RP2040
- Keychron Q15 Max

---
*Last updated: December 2024*
*Tested with Vial-QMK fork*