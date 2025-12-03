# D3lilah's Feature State and Layer RGB Feedback System

This document provides implementation patterns for RGB LED feedback on QMK keyboards, including layer-based color changes and feature toggle indicators. Tested and confirmed working on Boston keyboard and other boards.

## Overview

This system provides visual LED feedback for:
- Layer changes (different colors per layer)
- Feature toggles (Autocorrect, Auto Shift, etc.)
- Active events (Autocorrect firing)

## Prerequisites

Your keyboard needs:
- RGB lighting enabled (`RGBLIGHT_ENABLE = yes` in rules.mk)
- RGB functions available in QMK

## Layer-Based RGB Colors

### 1. Define Layer Colors

In your `keymap.c`, define RGB segments for each layer:

```c
// Define colors for each layer
const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 0, 0, 128}  // White (HSV: 0 hue, 0 sat, 128 value)
);

const rgblight_segment_t PROGMEM layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 0, 255, 255}  // Red
);

const rgblight_segment_t PROGMEM layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 120, 255, 255}  // Cyan
);

const rgblight_segment_t PROGMEM layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, 40, 255, 255}  // Yellow
);

// Add more layers as needed...
```

Format: `{start_led, num_leds, hue, saturation, value}`
- `start_led`: First LED index (usually 0)
- `num_leds`: How many LEDs to light (4 in this example)
- `hue`: Color (0-255, see HSV color wheel)
- `saturation`: Color purity (0-255, 0=white, 255=pure color)
- `value`: Brightness (0-255)

### 2. Create Layer Array

```c
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_0,
    layer_1,
    layer_2,
    layer_3
    // Add all your defined layers here
);
```

### 3. Initialize in `keyboard_post_init_user`

```c
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
```

### 4. Update Colors on Layer Change

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    // Update each layer's RGB state based on whether it's active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

// Optional: Force layer 0 to always be on
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, true);
    return true;
}
```

## Feature Toggle Visual Feedback

### Autocorrect Toggle (AC_TOGG)

Add this to your `process_record_user` function:

```c
case AC_TOG:  // Custom keycode for autocorrect
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
        // Flash once for ON - white flash
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
            rgblight_sethsv_noeeprom(0, 0, 0);    // Off
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

### Auto Shift Toggle (AS_TOGG)

Handle the built-in AS_TOGG keycode:

```c
// In process_record_user, OUTSIDE the switch statement
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
        rgblight_sethsv_noeeprom(85, 255, 255);  // Green (HSV: 85)
        rgblight_set();  // Force update
        wait_ms(200);
        rgblight_sethsv_noeeprom(0, 0, 0);    // Off
        rgblight_set();  // Force update
        wait_ms(200);
    } else {  // Will be OFF after toggle
        // Flash twice for OFF - blue flashes
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        for (int i = 0; i < 2; i++) {
            rgblight_sethsv_noeeprom(170, 255, 255);  // Blue (HSV: 170)
            rgblight_set();  // Force update
            wait_ms(200);
            rgblight_sethsv_noeeprom(0, 0, 0);    // Off
            rgblight_set();  // Force update
            wait_ms(200);
        }
    }

    // Re-enable layer indication
    rgblight_layers = my_rgb_layers;
    // Force layer update to restore original color
    layer_state_set_user(layer_state);
}

return true;  // Let QMK handle the actual toggle
```

## Active Event Feedback

### Autocorrect Fires (Word Corrected)

Add this callback function to detect when autocorrect actually makes a correction:

```c
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
    rgblight_sethsv_noeeprom(213, 255, 255);  // Purple (HSV: 213)
    rgblight_set();  // Force update
    wait_ms(100);  // Quick flash

    // Re-enable layer indication
    rgblight_layers = my_rgb_layers;
    // Force layer update to restore original color
    layer_state_set_user(layer_state);

    // Return true to allow the correction to happen
    return true;
}
```

## Visual Feedback Color Reference

### Standard Pattern
- **One flash** = Feature ON
- **Two flashes** = Feature OFF

### Color Meanings
| Feature | ON | OFF |
|---------|-----|-----|
| Autocorrect | 1x White | 2x Red |
| Auto Shift | 1x Green | 2x Blue |
| Autocorrect Fires | Purple flash | - |

### HSV Color Values
| Color | Hue | Saturation | Value |
|-------|-----|------------|-------|
| White | 0 | 0 | 255 |
| Red | 0 | 255 | 255 |
| Green | 85 | 255 | 255 |
| Blue | 170 | 255 | 255 |
| Purple | 213 | 255 | 255 |
| Yellow | 40 | 255 | 255 |
| Cyan | 120 | 255 | 255 |
| Orange | 20 | 255 | 255 |

## Implementation Notes

### Important Pattern for RGB Layers

When temporarily showing feedback, follow this pattern:

1. **Save and disable layers**: `rgblight_layers = NULL;`
2. **Ensure RGB is on**: Check with `rgblight_is_enabled()`
3. **Set mode and color**: Use `_noeeprom` functions
4. **Force update**: Call `rgblight_set()` after each change
5. **Wait**: Use `wait_ms()` for timing
6. **Restore layers**: `rgblight_layers = my_rgb_layers;`
7. **Update layer state**: Call `layer_state_set_user(layer_state)`

### Why Disable Layers?

RGB layers constantly update the LEDs based on the active layer. If you don't temporarily disable them, your flash effects will be immediately overwritten by the layer color.

### Key Functions

- `rgblight_sethsv_noeeprom(h, s, v)` - Set color without saving to EEPROM
- `rgblight_mode_noeeprom(mode)` - Set mode without saving
- `rgblight_set()` - Force immediate LED update
- `rgblight_enable_noeeprom()` - Enable RGB without saving
- `wait_ms(ms)` - Delay in milliseconds

## Complete Example Structure

```c
// 1. Layer color definitions
const rgblight_segment_t PROGMEM layer_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, 0, 0, 128});
// ... more layers ...

// 2. Layer array
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_0
    // ... more layers ...
);

// 3. Initialization
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;

    // Optional: Enable autocorrect by default
    autocorrect_enable();
}

// 4. Layer state handler
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    // ... more layers ...
    return state;
}

// 5. Process record for feature toggles
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle custom keycodes and built-in toggles
    // ... (see examples above) ...
    return true;
}

// 6. Autocorrect callback
bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    // ... (see example above) ...
    return true;
}
```

## Troubleshooting

### LEDs not flashing
- Ensure RGB is enabled in rules.mk
- Check that `rgblight_set()` is called after color changes
- Verify layers are temporarily disabled during flash

### Colors immediately revert
- Make sure to disable layers with `rgblight_layers = NULL`
- Re-enable layers after the flash sequence

### Flash too fast/slow
- Adjust `wait_ms()` values
- 100-200ms is usually good for visibility

### Layer colors not working
- Verify `rgblight_layers` is set in `keyboard_post_init_user`
- Check that `layer_state_set_user` is updating all layers

## Additional Ideas

- **Caps Lock indicator**: Flash when Caps Lock is activated
- **Combo feedback**: Flash when a combo is triggered
- **Typing speed indicator**: Change color based on WPM
- **Error states**: Red flash for invalid operations
- **Battery level** (wireless boards): Color gradient based on charge

---
*Last updated: December 2024*
*Tested on: Boston (STM32F411), D_38 (RP2040), Q15 Max*