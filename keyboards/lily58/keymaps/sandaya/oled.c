#include "oled.h"

#ifndef KEYLOGGER_LENGTH
#define KEYLOGGER_LENGTH ((uint8_t)(OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH))
#endif

static char keyloc_str[24] = {};
static char keycode_str[24] = {};
static char keylogs_str[KEYLOGGER_LENGTH + 1] = {0};

// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on


void add_keylog(uint16_t keycode, keyrecord_t *record) {
         
    snprintf(keycode_str, sizeof(keycode_str), "kc:%2d (0x%04X)",
            keycode, keycode); 


    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        if (((keycode & 0xFF) == KC_BSPC) && mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
            memset(keylogs_str, ' ', sizeof(keylogs_str) - 1);
            snprintf(keyloc_str, sizeof(keyloc_str), "kl:%dx%d ky: lg:",
                record->event.key.row, record->event.key.col);  
            return;
        }
        if (record->tap.count) {
            keycode = keycode & 0xFF;
        } else if (keycode > 0xFF) {
            return;
        }
    }

    for (uint8_t i = 1; i < KEYLOGGER_LENGTH; i++) {
        keylogs_str[i - 1] = keylogs_str[i];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylogs_str[(KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
        snprintf(keyloc_str, sizeof(keyloc_str), "kl:%dx%d ky:%c lg:",
                record->event.key.row, record->event.key.col, keylogs_str[(KEYLOGGER_LENGTH - 1)]); 
    }
}

void render_keylogger_status(void) {
    
    oled_write_ln(keycode_str, false);  
    oled_write(keyloc_str, false);
    oled_write_ln(keylogs_str, false);
}

void render_mod_status(uint8_t modifiers) {    
    
    oled_write_P(PSTR("shift"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("ctrl"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("alt"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("gui"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\n"), false);
}

void render_keylock_status(uint8_t led_usb_state) {
    
    oled_write_P(PSTR("num"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("caps"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("scroll"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_write_P(PSTR("\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_keylogger_status();
        render_mod_status(get_mods() | get_oneshot_mods());
        render_keylock_status(host_keyboard_leds());     
    } else {
                
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode, record);
    }
    return true;
}

