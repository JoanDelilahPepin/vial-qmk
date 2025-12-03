# Alpha-BA

![Alpha](https://i.imgur.com/J6EJ30N.jpg)

An RP2040-powered update of PyroL's original Alpha - a 28-key, semi-ortho keyboard.

## About This Fork

Alpha-BA is a modernized firmware for the Alpha keyboard using an Elite-Pi (RP2040) as a drop-in replacement for the original Pro Micro. The Elite-Pi is pin-compatible with the Pro Micro, so no hardware modifications are needed beyond swapping the controller.

## Features

In addition to the RP2040 upgrade, this firmware includes significant quality-of-life improvements:

- **Autocorrect** - Automatic typo correction
- **Auto Shift** - Hold any key slightly longer to get its shifted variant
- **Tap Dance** - Multi-function keys based on tap count and hold
- **Combos** - Press multiple keys simultaneously for additional functions
- **Redesigned Layers** - New layer structure optimized for a 28-key layout
- **Vial Support** - Full runtime configuration via Vial GUI

## Hardware

- **Original Design**: [PyroL](https://www.github.com/PyrooL)
- **Controller**: Elite-Pi (RP2040) or any Pro Micro-compatible RP2040 board
- **Original Hardware**: Alpha PCB (designed for Pro Micro)

## Building

```
make d3lilah/alpha-ba:vial
```

## Original Project

For build instructions, parts lists, Gerbers, and case files, see [PyrooL/Alpha](https://www.github.com/PyrooL/Alpha).
