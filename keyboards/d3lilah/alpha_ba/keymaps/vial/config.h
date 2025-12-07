/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x61, 0x9A, 0x31, 0x31, 0xEB, 0xC4, 0xEB, 0xD5}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }
#define VIAL_INSECURE

// Vial configuration for combos, tap dances, etc.
// Use static combos defined in keymap.c instead of Vial's dynamic combos
#define VIAL_COMBO_DISABLE
#define VIAL_TAP_DANCE_ENTRIES 16
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define VIAL_KEY_OVERRIDE_ENTRIES 16
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

// RGB Layer configuration
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_MAX_LAYERS 5

// Auto Shift configuration
#define AUTO_SHIFT_TIMEOUT 175
#define NO_AUTO_SHIFT_ALPHA  // Do not Auto Shift alpha characters

// I2C Configuration for Elite Pi (maps to GP2/GP3 via CONVERT_TO)
#define I2C1_SDA_PIN D1
#define I2C1_SCL_PIN D0
#define I2C_DRIVER I2CD1

// Haptic feedback - DRV2605L Configuration (PUSHING HARD - prototype mode)
#define DRV2605L_FB_ERM_LRA 0      // 0 = ERM
#define DRV2605L_FB_BRAKEFACTOR 7  // Disable braking - let it rip
#define DRV2605L_FB_LOOPGAIN 3     // Very High

// Motor settings - pancake ERM, MAXIMUM OVERDRIVE
#define DRV2605L_RATED_VOLTAGE 3   // Rated 3V
#define DRV2605L_V_PEAK 5.5        // Push peak voltage harder
#define DRV2605L_LIBRARY 1         // TS2200 Library A (strongest for ERM)
#define DRV2605L_ERM_OPEN_LOOP 1   // Open loop = no feedback limiting = raw power

// Use strong buzz effect
#define DRV2605L_GREETING DRV2605L_EFFECT_STRONG_BUZZ_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_STRONG_BUZZ_100

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
