# Alpha-BA

*A themed, RP2040-powered variant of PyroL's Alpha keyboard*

![Alpha](https://github.com/JoanDelilahPepin/vial-qmk/blob/vial/keyboards/d3lilah/alpha_ba/alpha_ba.png)
*Photo shows: [Tikiwin's Alpha case design](https://www.thingiverse.com/thing:3487311) printed in purple by [WeirdLittleKeebs](https://www.etsy.com/shop/WeirdLittleKeebs), with GMK Terror Below keycaps (green). Many Alpha case designs are available.*

- **Keyboard Maintainer**: [d3lilah](https://github.com/JoanDelilahPepin)
- **Original Alpha Designer**: [PyroL](https://github.com/PyrooL/Alpha)
- **Hardware Supported**: Original Alpha PCB (v2.1) with Elite-Pi controller
- **Hardware Availability**: [PyroL/Alpha](https://github.com/PyrooL/Alpha) - PCB files, case files, build guide
- **Variant Theme**: Elphaba (Wicked musical)

## About Alpha-BA

The Alpha-BA is a firmware variant for **PyroL's Alpha keyboard**, maintaining full hardware compatibility with the original Alpha PCB. This variant explores what's possible when combining PyroL's innovative 28-key design with the enhanced capabilities of modern RP2040 controllers.

The name "Alpha-BA" is a playful combination of "Better Alpha" (representing technical improvements) and "Elphaba" (the Wicked Witch of the West from the musical Wicked), reflected in the purple and green color scheme throughout the hardware and firmware.

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

## Original Alpha Project

**All credit for the Alpha keyboard design goes to [PyroL](https://github.com/PyrooL)**. The Alpha is an innovative 28-key keyboard that challenges conventional keyboard design. This firmware variant aims to enhance PyroL's original vision while maintaining complete hardware compatibility.

For the original project resources:
- **PCB Files**: [PyrooL/Alpha](https://github.com/PyrooL/Alpha)
- **Case Designs**: Available in the original repository
- **Build Guide**: See PyroL's documentation
- **Community**: Check the 40% Keyboards Discord

## Build Information

Make example for this keyboard (after setting up your build environment):

    make d3lilah/alpha_ba:default

Flashing example for this keyboard:

    make d3lilah/alpha_ba:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Acknowledgments

Special thanks to PyroL for creating the Alpha keyboard and making it open source. The Alpha-BA variant exists only because of PyroL's original work and commitment to the open hardware community.
