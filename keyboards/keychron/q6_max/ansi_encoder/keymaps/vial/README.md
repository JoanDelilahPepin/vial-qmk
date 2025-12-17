# Keychron Q6 Max VIAL Port

**Status:** Working
**Date:** 2024-12-16
**Author:** d3lilah

## Features

- Full VIAL support with live keymap editing
- VIALRGB lighting control in VIAL GUI
- All three transport modes working: USB, Bluetooth, 2.4G
- Automatic USB/Bluetooth hot-switching when cable connected/disconnected
- Encoder support with per-layer mapping
- Custom Keychron keycodes (Mission Control, Launchpad, BT hosts, etc.)

## Building

```bash
make keychron/q6_max/ansi_encoder:vial
```

To flash:
```bash
make keychron/q6_max/ansi_encoder:vial:flash
```

## Key Discovery: 2-Position Switch Behavior

The Q6 Max physical switch appears to be a 3-position switch, but GPIO analysis revealed it only controls one pin effectively:

| Switch Position | P24G Pin (A10) | BT Pin (A9) | pins_state |
|-----------------|----------------|-------------|------------|
| 2.4G            | LOW            | LOW         | 0x00       |
| USB/BT          | HIGH           | LOW         | 0x01       |

The BT pin (A9) reads LOW regardless of switch position. This means the switch is effectively 2-position:
- **Position 1 (2.4G):** 2.4G wireless mode
- **Position 2 (USB/BT):** USB if cable connected, otherwise Bluetooth

## Solution Implemented

Modified `keyboards/keychron/common/wireless/keychron_wireless_common.c` to:

1. Map `pins_state == 0x00` to 2.4G mode
2. Map `pins_state == 0x01` to USB or Bluetooth based on `usb_power_connected()`
3. Added continuous USB power monitoring for seamless hot-switching

This allows:
- Switch to 2.4G position → 2.4G mode
- Switch to USB/BT position with cable → USB mode
- Switch to USB/BT position without cable → Bluetooth mode
- Plug/unplug cable while in USB/BT position → automatic switching

## Files Modified

### VIAL Keymap Files (this directory)
- `config.h` - VIAL UID, unlock combo
- `keymap.c` - Standard 4-layer keymap (MAC_BASE, MAC_FN, WIN_BASE, WIN_FN)
- `rules.mk` - Enables VIA, VIAL, VIALRGB, encoder map
- `vial.json` - VIAL GUI layout with custom keycodes

### Common Keychron Files
- `keyboards/keychron/common/wireless/keychron_wireless_common.c` - Transport switching logic
- `keyboards/keychron/common/keychron_common.c` - Keychron keycode handling
- `keyboards/keychron/q6_max/q6_max.c` - GPIO pin initialization

### GPIO Configuration

Final working configuration in `q6_max.c`:
```c
palSetLineMode(P24G_MODE_SELECT_PIN, PAL_MODE_INPUT);
palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT_PULLUP);
```

## Custom Keycodes

Available in VIAL under "User" tab:
- `KC_LOPTN` / `KC_ROPTN` - macOS Option keys
- `KC_LCMMD` / `KC_RCMMD` - macOS Command keys
- `KC_MCTRL` - Mission Control
- `KC_LNPAD` - Launchpad
- `KC_TASK_VIEW` - Windows Task View
- `KC_FILE_EXPLORER` - Windows File Explorer
- `KC_SCREEN_SHOT` - macOS Screenshot
- `KC_SIRI` / `KC_CORTANA` - Voice assistants
- `BT_HST1` / `BT_HST2` / `BT_HST3` - Bluetooth host selection
- `P2P4G` - 2.4G dongle mode
- `BAT_LVL` - Battery level display

## Notes for Other Q Max Ports

When porting other Q Max boards:

1. **Test GPIO pins first** - Use debug LEDs to verify actual pin states for each switch position
2. **Check pin behavior** - Not all boards may have the same GPIO behavior
3. **USB power detection** - `usb_power_connected()` is the reliable way to detect USB vs wireless
4. **Transport logic** - The `wireless_pre_task()` function in `keychron_wireless_common.c` handles mode selection

## Debugging Tips

If transport switching doesn't work, add temporary RGB indicators to check GPIO states:

```c
// In rgb_matrix_indicators_user():
if (gpio_read_pin(P24G_MODE_SELECT_PIN)) {
    rgb_matrix_set_color(0, 0, 255, 0);  // Green = HIGH
} else {
    rgb_matrix_set_color(0, 255, 0, 0);  // Red = LOW
}
```

## License

GPL v2 - see LICENSE file in repository root.
