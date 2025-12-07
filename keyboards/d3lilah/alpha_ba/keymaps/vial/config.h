/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x61, 0x9A, 0x31, 0x31, 0xEB, 0xC4, 0xEB, 0xD5}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }
#define VIAL_INSECURE

// Vial configuration for combos, tap dances, etc.
#define VIAL_COMBO_ENTRIES 32
#define VIAL_TAP_DANCE_ENTRIES 16
#define VIAL_KEY_OVERRIDE_ENTRIES 16
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

// RGB Layer configuration
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_MAX_LAYERS 4

// Auto Shift configuration
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_ALPHA  // Do not Auto Shift alpha characters

// I2C Configuration for Elite Pi (maps to GP2/GP3 via CONVERT_TO)
#define I2C1_SDA_PIN D1
#define I2C1_SCL_PIN D0
#define I2C_DRIVER I2CD1

// Haptic feedback - DRV2605L Configuration
#define DRV2605L_FB_ERM_LRA 0      // 0 = ERM (Eccentric Rotating Mass), 1 = LRA (Linear Resonant Actuator)
#define DRV2605L_FB_BRAKEFACTOR 3  // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable:7
#define DRV2605L_FB_LOOPGAIN 1     // Low:0, Medium:1, High:2, Very High:3

// Motor settings - matching your motor specs (3V rated, 85mA)
#define DRV2605L_RATED_VOLTAGE 3   // Your motor is rated at 3V
#define DRV2605L_V_PEAK 5          // Peak can be higher for stronger effects
#define DRV2605L_V_RMS 2           // RMS voltage
#define DRV2605L_F_LRA 200         // Not used for ERM but defining anyway

// Try using the strong click effect (effect 1)
#define DRV2605L_GREETING 1         // Play effect 1 on boot
#define DRV2605L_DEFAULT_MODE 1     // Default to effect 1 (strong click 100%)

// Default haptic settings
#define NO_HAPTIC_MOD               // Disable haptic feedback on modifier keys

#if defined(__AVR_ATmega32U4__)
    #undef LOCKING_SUPPORT_ENABLE
    #undef LOCKING_RESYNC_ENABLE

    #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    #undef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_TWINKLE
#endif
