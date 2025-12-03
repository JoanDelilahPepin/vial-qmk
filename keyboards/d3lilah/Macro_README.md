# D3lilah's Macro Implementation Reference

Complete macro implementations for text editing, formatting, and navigation. These macros are optimized for macOS and have been tested on Boston, pad_18, and other keyboards.

## Table of Contents
- [Markdown/Obsidian Macros](#markdownobsidian-macros)
- [Google Docs Macros](#google-docs-macros)
- [Text Manipulation Macros](#text-manipulation-macros)
- [Cut Operations](#cut-operations)
- [Wrap Operations](#wrap-operations)
- [Implementation Guide](#implementation-guide)

## Markdown/Obsidian Macros

These macros are designed for Markdown editors like Obsidian, where you need to insert formatted text directly.

### Headers

```c
case MD_H1:
    tap_code(KC_HOME);
    SEND_STRING("# ");
    return false;

case MD_H2:
    tap_code(KC_HOME);
    SEND_STRING("## ");
    return false;

case MD_H3:
    tap_code(KC_HOME);
    SEND_STRING("### ");
    return false;
```

### Text Formatting

```c
case BOLD:
    register_code(KC_LGUI);
    tap_code(KC_B);
    unregister_code(KC_LGUI);
    return false;

case ITALIC:
    register_code(KC_LGUI);
    tap_code(KC_I);
    unregister_code(KC_LGUI);
    return false;
```

### Obsidian-Specific Characters

```c
case OBS_QUOTE:
    // Insert escaped quote for Obsidian
    SEND_STRING("\\\"");
    tap_code(KC_LEFT);
    tap_code(KC_LEFT);
    return false;

case OBS_PAREN:
    // Insert escaped parentheses for Obsidian
    SEND_STRING("\\(\\)");
    tap_code(KC_LEFT);
    tap_code(KC_LEFT);
    tap_code(KC_LEFT);
    return false;

case OBS_EMDASH:
    // Triple dash for em dash in Markdown
    SEND_STRING("---");
    return false;
```

### Clear Formatting (Obsidian)

```c
case CLR_FMT:
    // Clear Formatting in Obsidian: Cmd+Shift+Ctrl+K
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    register_code(KC_LCTL);
    tap_code(KC_K);
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
    unregister_code(KC_LGUI);
    return false;
```

## Google Docs Macros

These macros use keyboard shortcuts to apply formatting in Google Docs.

### Headers

```c
case GDOC_H1:
    // Apply Heading 1 style: Cmd+Alt+1
    register_code(KC_LGUI);
    register_code(KC_LALT);
    tap_code(KC_1);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    return false;

case GDOC_H2:
    // Apply Heading 2 style: Cmd+Alt+2
    register_code(KC_LGUI);
    register_code(KC_LALT);
    tap_code(KC_2);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    return false;

case GDOC_H3:
    // Apply Heading 3 style: Cmd+Alt+3
    register_code(KC_LGUI);
    register_code(KC_LALT);
    tap_code(KC_3);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    return false;

case GDOC_NORMAL:
    // Apply Normal text style: Cmd+Alt+0
    register_code(KC_LGUI);
    register_code(KC_LALT);
    tap_code(KC_0);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
    return false;
```

## Text Manipulation Macros

### Cut Operations

These macros cut text at various boundaries.

```c
case CUT_LINE_START:
    // Select to beginning of line and cut
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    tap_code(KC_LEFT);
    unregister_code(KC_LSFT);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;

case CUT_LINE_END:
    // Select to end of line and cut
    register_code(KC_LGUI);
    register_code(KC_LSFT);
    tap_code(KC_RGHT);
    unregister_code(KC_LSFT);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;

case CUT_WORD_PREV:
    // Select previous word and cut
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_LEFT);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;

case CUT_WORD_NEXT:
    // Select next word and cut
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_RGHT);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;

case CUT_PARA:
    // Select entire paragraph and cut
    // Move to paragraph start
    register_code(KC_LALT);
    tap_code(KC_UP);
    unregister_code(KC_LALT);
    // Select to paragraph end
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_DOWN);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    // Cut
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;

case CUT_PARA_END:
    // Select to end of paragraph and cut
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_DOWN);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    return false;
```

### Paste

```c
case PASTE:
    register_code(KC_LGUI);
    tap_code(KC_V);
    unregister_code(KC_LGUI);
    return false;
```

## Wrap Operations

These are the Google Docs versions that cut selected text and wrap it with characters.

### Important: Delays for Clipboard Operations

The 150ms delays are **critical** for clipboard operations to complete properly!

```c
case WRAP_QUOTE:
    // Cut current selection
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    wait_ms(150);                // Wait for clipboard
    SEND_STRING("\"");           // Opening quote
    wait_ms(150);
    // Paste
    register_code(KC_LGUI);
    tap_code(KC_V);
    unregister_code(KC_LGUI);
    wait_ms(150);
    SEND_STRING("\" ");          // Closing quote + space
    return false;

case WRAP_PAREN:
    // Cut current selection
    register_code(KC_LGUI);
    tap_code(KC_X);
    unregister_code(KC_LGUI);
    wait_ms(150);                // Wait for clipboard
    SEND_STRING("(");            // Opening paren
    wait_ms(150);
    // Paste
    register_code(KC_LGUI);
    tap_code(KC_V);
    unregister_code(KC_LGUI);
    wait_ms(150);
    SEND_STRING(") ");           // Closing paren + space
    return false;
```

## Implementation Guide

### 1. Define Custom Keycodes

In your `keymap.c`:

```c
enum custom_keycodes {
    // Markdown Headers
    MD_H1 = QK_KB_0,  // Use QK_KB_0 as base for Vial compatibility
    MD_H2,
    MD_H3,

    // Text Formatting
    BOLD,
    ITALIC,
    CLR_FMT,

    // Cut Operations
    CUT_LINE_START,
    CUT_LINE_END,
    CUT_WORD_PREV,
    CUT_WORD_NEXT,
    CUT_PARA,
    CUT_PARA_END,

    // Basic Operations
    PASTE,

    // Obsidian-specific
    OBS_QUOTE,
    OBS_PAREN,
    OBS_EMDASH,

    // Wrap Operations (Google Docs)
    WRAP_QUOTE,
    WRAP_PAREN,

    // Google Docs Headers
    GDOC_H1,
    GDOC_H2,
    GDOC_H3,
    GDOC_NORMAL
};
```

### 2. Add to process_record_user

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // Add all macro cases here
            // See individual sections above for implementations
        }
    }
    return true;
}
```

### 3. Configure in vial.json

Add to the `customKeycodes` array:

```json
"customKeycodes": [
    {"name": "MD H1", "title": "Markdown Header 1", "shortName": "MD H1"},
    {"name": "MD H2", "title": "Markdown Header 2", "shortName": "MD H2"},
    {"name": "MD H3", "title": "Markdown Header 3", "shortName": "MD H3"},
    {"name": "Bold", "title": "Bold Text", "shortName": "Bold"},
    {"name": "Italic", "title": "Italic Text", "shortName": "Italic"},
    {"name": "Clear Format", "title": "Obsidian: Clear Format", "shortName": "ClrFmt"},
    {"name": "Cut Line Start", "title": "Cut to Line Start", "shortName": "Cut^Ln"},
    {"name": "Cut Line End", "title": "Cut to Line End", "shortName": "CutvLn"},
    {"name": "Cut Word Prev", "title": "Cut Previous Word", "shortName": "Cut<Wd"},
    {"name": "Cut Word Next", "title": "Cut Next Word", "shortName": "Cut>Wd"},
    {"name": "Cut Paragraph", "title": "Cut Paragraph", "shortName": "CutPara"},
    {"name": "Cut Para End", "title": "Cut to Paragraph End", "shortName": "CutvPar"},
    {"name": "Paste", "title": "Paste", "shortName": "Paste"},
    {"name": "Obs Quote", "title": "Obsidian: Insert Quote", "shortName": "ObsQte"},
    {"name": "Obs Paren", "title": "Obsidian: Insert Paren", "shortName": "ObsPrn"},
    {"name": "Obs Em-Dash", "title": "Obsidian: Em Dash", "shortName": "ObsDash"},
    {"name": "Wrap Quote", "title": "GDocs: Wrap in Quotes", "shortName": "WrapQte"},
    {"name": "Wrap Paren", "title": "GDocs: Wrap in Parens", "shortName": "WrapPrn"},
    {"name": "GDoc H1", "title": "Google Docs Header 1", "shortName": "GD H1"},
    {"name": "GDoc H2", "title": "Google Docs Header 2", "shortName": "GD H2"},
    {"name": "GDoc H3", "title": "Google Docs Header 3", "shortName": "GD H3"},
    {"name": "GDoc Normal", "title": "Google Docs Normal Text", "shortName": "GD Norm"}
]
```

## Key Patterns and Best Practices

### 1. **Modifier Key Order**
Always register modifiers before the key press and unregister in reverse order:
```c
register_code(KC_LGUI);
register_code(KC_LALT);
tap_code(KC_1);
unregister_code(KC_LALT);
unregister_code(KC_LGUI);
```

### 2. **Clipboard Operations**
Always add delays when working with clipboard:
```c
tap_code(KC_X);          // Cut
wait_ms(150);            // Critical delay!
// ... do something ...
tap_code(KC_V);          // Paste
wait_ms(150);            // Another delay
```

### 3. **Cursor Positioning**
After inserting paired characters, move cursor back:
```c
SEND_STRING("\\\"");     // Insert \"
tap_code(KC_LEFT);       // Move cursor
tap_code(KC_LEFT);       // between the quotes
```

### 4. **Application Context**
- **Obsidian/Markdown**: Direct text insertion with escape sequences
- **Google Docs**: Use keyboard shortcuts (Cmd+Alt+number)
- **Wrap operations**: Include space after closing character

## Platform Notes

### macOS Specific
These macros use macOS keyboard shortcuts:
- `KC_LGUI` = Command key
- `KC_LALT` = Option key
- Cut/Copy/Paste = Cmd+X/C/V
- Word navigation = Option+Arrow
- Line navigation = Cmd+Arrow

### Windows/Linux Adaptation
Replace:
- `KC_LGUI` → `KC_LCTL` (Control key)
- `KC_LALT` → `KC_LALT` (Alt key remains)
- Adjust shortcuts as needed for your applications

## Troubleshooting

### Macros not working
- Ensure custom keycodes are defined starting from `QK_KB_0`
- Check that `process_record_user` returns `false` for handled cases
- Verify Vial custom keycodes match the enum names

### Clipboard operations failing
- Increase `wait_ms()` delays if operations are too fast
- Some applications may need longer delays (200-300ms)

### Wrong characters appearing
- Check keyboard language settings match expected layout
- Verify escape sequences for your specific application

## Testing Checklist

- [ ] All Markdown headers insert correctly
- [ ] Bold/Italic formatting works
- [ ] Cut operations select correct text boundaries
- [ ] Wrap operations preserve selected text
- [ ] Google Docs headers apply correct styles
- [ ] Obsidian escape characters render properly
- [ ] Clipboard operations complete reliably

---
*Last updated: December 2024*
*Tested on: Boston (STM32F411), pad_18 (RP2040), D_38 (RP2040)*