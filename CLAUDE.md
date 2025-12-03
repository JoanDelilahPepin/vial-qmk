# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a fork of vial-qmk (QMK firmware with Vial support). Vial adds dynamic keymap configuration via a GUI without reflashing, while maintaining full QMK compatibility.

## Build Commands

```bash
# Compile firmware
make <keyboard>:<keymap>

# Compile and flash
make <keyboard>:<keymap>:flash

# Examples for d3lilah keyboards
make d3lilah/d_38:vial
make d3lilah/numpad:vial
make d3lilah/pad_18:vial

# Examples for other keyboards with d3lilah keymaps
make boston:d3lilah
make boston:d3lilah_v_0_9
make cannonkeys/bastion60:d3lilah
make 1upkeyboards/pi60_rgb_v2:d3lilah

# Useful targets
make clean                  # Remove .build directory
make list-keyboards         # List all keyboards
```

## Architecture

### Key Directories
- `keyboards/` - Keyboard definitions (1000+)
- `quantum/` - Core QMK functionality + Vial extensions
- `builddefs/` - Build system makefiles
- `platforms/` - Platform-specific code (AVR, ARM, RP2040)
- `drivers/` - Hardware drivers

### Vial-Specific Files
- `quantum/vial.c/h` - Vial protocol implementation
- `quantum/vialrgb.c/h` - Vial RGB lighting support
- `quantum/qmk_settings.c/h` - Runtime settings framework
- `builddefs/build_vial.mk` - Vial build configuration
- `util/vial_generate_definition.py` - Converts vial.json to C header

### Keyboard Directory Structure
```
keyboards/<vendor>/<keyboard>/
├── keyboard.json           # Main keyboard info (data-driven config)
├── config.h               # Base configuration
├── rules.mk               # Build flags
└── keymaps/
    ├── default/
    │   └── keymap.c       # Required default keymap
    └── vial/
        ├── config.h       # Vial-specific config (UID, unlock combo)
        ├── keymap.c       # Default layer for Vial
        ├── rules.mk       # Vial build flags
        └── vial.json      # Layout definition for Vial GUI (required)
```

### Vial Keymap Requirements
In `keymaps/vial/config.h`:
```c
#define VIAL_KEYBOARD_UID {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX}
#define VIAL_UNLOCK_COMBO_ROWS { row1, row2 }
#define VIAL_UNLOCK_COMBO_COLS { col1, col2 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 4  // Number of layers
#define VIAL_TAP_DANCE_ENTRIES 8      // If using tap dance
```

In `keymaps/vial/rules.mk`:
```makefile
VIA_ENABLE = yes
VIAL_ENABLE = yes
```

## d3lilah Custom Work

### Custom Keyboards (`keyboards/d3lilah/`)
- `d_38/` - 38-key keyboard
- `numpad/` - Numpad
- `pad_18/` - 18-key pad

Documentation in that directory covers pre-compiling Vial configs, keymap dumps, macros, and feature/layer state management.

### Custom Keymaps on Other Keyboards

**Boston** (`keyboards/boston/keymaps/`):
- `d3lilah` - Main custom keymap
- `d3lilah_v_0_9` - Pre-compiled version with tap dances and Auto Shift
- `debug` - Debug keymap with dump functionality

**Cannonkeys Bastion60** (`keyboards/cannonkeys/bastion60/keymaps/`):
- `d3lilah` - Custom keymap
- `vial-dual-use` - Dual-use key configuration
- `vial-dual-use-delilah` - Personal dual-use setup
- `vial-gaming` - Gaming-optimized layout

**1upkeyboards Pi60 RGB V2** (`keyboards/1upkeyboards/pi60_rgb_v2/keymaps/`):
- `d3lilah` - Custom keymap
- `vial-dual-use-delilah` - Personal dual-use setup
- `holy60` - Holy60 layout

## Vial Features (enabled by default with VIAL_ENABLE)
- Dynamic keymaps (stored in EEPROM)
- Tap dance, combos, key overrides
- Caps word, layer lock, repeat key
- QMK Settings (runtime configuration)
- RGB lighting control via VialRGB

## Firmware Size Optimization
Use `LTO_ENABLE = yes` in rules.mk for link-time optimization on space-constrained MCUs.
