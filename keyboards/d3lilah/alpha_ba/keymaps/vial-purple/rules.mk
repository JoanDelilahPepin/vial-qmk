VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes
CONSOLE_ENABLE = yes
QMK_SETTINGS = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
AUTOCORRECT_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
LAYER_LOCK_ENABLE = no
REPEAT_KEY_ENABLE = no

# Haptic feedback - using DRV2605L for motor patterns
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l

# Custom solenoid support (requires deferred execution for precise timing)
DEFERRED_EXEC_ENABLE = yes

# I2C support for DRV2605L
I2C_DRIVER_REQUIRED = yes
