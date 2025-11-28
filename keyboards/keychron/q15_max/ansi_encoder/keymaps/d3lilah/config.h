/* Copyright 2024 @ d3lilah
 * Personal configuration for Keychron Q15 Max
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

/* Vial Keyboard UID - Unique ID for d3lilah's Q15 Max */
#define VIAL_KEYBOARD_UID {0xD3, 0x11, 0x1A, 0x15, 0x5A, 0xA1, 0x01, 0x01}

/* Vial unlock combo - ESC + Enter (top-left + main enter) */
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* Eight layers for personal use */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* 32 macros for writing tasks */
#undef VIAL_MACRO_COUNT
#define VIAL_MACRO_COUNT 32

/* Tap Dance and Combos */
#define VIAL_TAP_DANCE_ENTRIES 16
#define VIAL_COMBO_ENTRIES 16

/* Personal preferences for d3lilah */
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

/* Mouse keys for navigation */
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

/* Personal preferences */
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT

/* Include expanded RGB effects from d3lilah's configuration */
#ifdef RGB_MATRIX_ENABLE
#include "rgb_effects_config.h"
#endif