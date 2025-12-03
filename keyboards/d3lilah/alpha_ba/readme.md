# Alpha-BA

*A themed, RP2040-powered variant of PyroL's Alpha keyboard*

![Alpha](https://github.com/JoanDelilahPepin/vial-qmk/blob/vial/keyboards/d3lilah/alpha_ba/alpha_ba.png)

**Original Designer**: [PyroL](https://github.com/PyrooL/Alpha)
**Variant Designer**: d3lilah
**Theme**: Elphaba (Wicked)

## About Alpha-BA

The Alpha-BA ("Better Alpha" / "Elpha-BA") is a themed variant of PyroL's original Alpha - a 28-key, semi-ortho keyboard. The name is a playful combination of "Better Alpha" (representing technical improvements) and "Elphaba" (the Wicked Witch of the West from the musical Wicked), reflected in the purple and green color scheme throughout the hardware and firmware.

### What Makes It "BA"

- **Purple and green aesthetics** inspired by Wicked's Elphaba
- **RP2040-powered performance** via Elite-Pi controller (drop-in Pro Micro replacement)
- **Enhanced firmware features** leveraging the RP2040's superior processing power and memory
- **Theatrical layer indication** with colors themed to match (green, purple, pink, gold)
- **Smart typing assistance** with massive autocorrect dictionary and Auto Shift, making this tiny board surprisingly usable

The Elite-Pi is pin-compatible with the Pro Micro, so no hardware modifications are needed beyond swapping the controller - but the experience is dramatically enhanced.

## Features

### Autocorrect
- 3,667-word Iyada dictionary for automatic typo correction
- Enabled by default on boot
- Toggle with `AC_TOG` custom keycode
- Visual feedback: blue flash (1x on, 2x off), long blue flash when correction fires

### Auto Shift
- Hold any key slightly longer (175ms) to get its shifted variant
- Alpha keys (A-Z) excluded - only numbers and special characters auto-shift
- Enabled by default on boot
- Toggle with `AS_TOGG` (Quantum tab in Vial)
- Visual feedback: orange flash (1x on, 2x off)

### RGB Layer Indication (Wicked Theme)
- 11 WS2812 LEDs on pin F4
- Layer 0 (HOME): Green - Elphaba's signature color
- Layer 1 (MODS): Purple - Elphaba's magic
- Layer 2 (MODS2): Pink - Glinda's influence
- Layer 3 (OTHER): Gold - The Yellow Brick Road

### Visual Feedback Summary
| Action | Color | Pattern |
|--------|-------|---------|
| Autocorrect ON | Blue | 1 flash |
| Autocorrect OFF | Blue | 2 flashes |
| Autocorrect fires | Blue | Long flash |
| Auto Shift ON | Orange | 1 flash |
| Auto Shift OFF | Orange | 2 flashes |
| Keymap dump | Cyan | 1 flash |
| Bootloader | Magenta | 5 rapid flashes |

### Vial Support
- Full runtime configuration via Vial GUI
- Dynamic keymaps stored in EEPROM
- QMK Settings integration for tweaking auto shift timing, etc.
- Custom keycodes exposed: `Dump KM`, `AC_TOG`, `MACRO1`

### Developer Features
- **Keymap Dump**: Press `DUMP_KM` to export current Vial keymap to console in C format
- Auto-dumps keymap on boot (after 1 second delay)
- Use `hid_listen` or QMK Toolbox console to capture output
- Console enabled for debugging

### Additional Features
- Tap Dance support (configure in Vial)
- Combo support (configure in Vial)
- Key Override support
- Caps Word

## Hardware

- **Original Design**: [PyroL](https://www.github.com/PyrooL)
- **Controller**: Elite-Pi (RP2040) or any Pro Micro-compatible RP2040 board
- **LEDs**: 11x WS2812 RGB LEDs
- **Original Hardware**: Alpha PCB (designed for Pro Micro)

## Building

```
make d3lilah/alpha_ba:vial
```

## Flashing

1. Hold BOOTSEL on the Elite-Pi while plugging in (or double-tap reset)
2. Copy the `.uf2` file to the mounted `RPI-RP2` drive:
   ```
   cp d3lilah_alpha_ba_vial.uf2 /Volumes/RPI-RP2/
   ```

## Layer Structure

- **Layer 0 (HOME)**: Alpha keys, space bar with shift on hold
- **Layer 1 (MODS)**: Numbers, backspace, navigation arrows
- **Layer 2 (MODS2)**: Function keys, symbols, RGB controls
- **Layer 3 (OTHER)**: Bootloader, debug functions, macros

## Original Project

For build instructions, parts lists, Gerbers, and case files, see [PyrooL/Alpha](https://www.github.com/PyrooL/Alpha).
