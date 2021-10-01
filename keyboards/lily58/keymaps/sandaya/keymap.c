#include "keymap.h"

#ifdef OLED_ENABLE
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
#endif 

#define JIGGLE_DELAY 5000
enum custom_keycodes {
    JIGGLE = SAFE_RANGE,
};
bool jiggle_mode = false;
uint32_t jiggle_timer = 0;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT( \
  KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,      KC_5,                            KC_6,     KC_7,    KC_8,    KC_9,     KC_0,      KC_MINS, \
  KC_BSLS, KC_Q,   KC_W,   KC_E,   KC_R,      KC_T,                            KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,      KC_EQL,  \
  KC_LCTL, HOME_A, HOME_S, HOME_D, HOME_F,    KC_G,                            KC_H,     HOME_J,  HOME_K,  HOME_L,   HOME_SCLN, KC_QUOT, \
  KC_LBRC, KC_Z,   HOME_X, KC_C,   KC_V,      KC_B,    U_NP,          JIGGLE,  KC_N,     KC_M,    KC_COMM, HOME_DOT, KC_SLSH,   KC_RBRC, \
                           U_NU,   MEDIA_ESC, NAV_SPC, MOUSE_TAB,     SYM_ENT, NUM_BSPC, FUN_DEL, U_NU \
),
[NUM] = LAYOUT( \
  U_NU, U_NU,    U_NU, U_NU, U_NU,   U_NU,                        U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, KC_LBRC, KC_7, KC_8, KC_9,   KC_RBRC,                     U_NA, U_NA,    U_NA,    U_NA,    RESET,   U_NU, \
  U_NU, KC_SCLN, KC_4, KC_5, KC_6,   KC_EQL,                      U_NA, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, U_NU, \
  U_NU, KC_GRV,  KC_1, KC_2, KC_3,   KC_BSLS, U_NP,         U_NU, U_NA, U_NA,    U_NA,    KC_ALGR, U_NA,    U_NU, \
                       U_NU, KC_DOT, KC_0,    KC_MINS,      U_NA, U_NA, U_NA,    U_NU \
),
[SYM] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                        U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                     U_NA, U_NA,    U_NA,    U_NA,    RESET,   U_NU, \
  U_NU, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                     U_NA, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, U_NU, \
  U_NU, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, U_NP,         U_NU, U_NA, U_NA,    U_NA,    KC_ALGR, U_NA,    U_NU, \
                          U_NU,    KC_LPRN, KC_RPRN, KC_UNDS,      U_NA, U_NA, U_NA,    U_NU \
),
[FUN] = LAYOUT( \
  U_NU, U_NU,   U_NU,  U_NU,  U_NU,   U_NU,                        U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, KC_F12, KC_F7, KC_F8, KC_F9,  KC_PSCR,                     U_NA, U_NA,    U_NA,    U_NA,    RESET,   U_NU, \
  U_NU, KC_F11, KC_F4, KC_F5, KC_F6,  KC_SLCK,                     U_NA, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, U_NU, \
  U_NU, KC_F10, KC_F1, KC_F2, KC_F3,  KC_PAUS, U_NP,         U_NU, U_NA, U_NA,    U_NA,    KC_ALGR, U_NA,    U_NU, \
                       U_NU,  KC_APP, KC_SPC,  KC_TAB,       U_NA, U_NA, U_NA,    U_NU \
),
#if defined MIRYOKU_NAV_VI
[NAV] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS, U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_ENT, KC_BSPC, KC_DEL,  U_NU \
),
[MOUSE] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                     U_NU,    U_NU,    U_NU,    U_NU,    U_NU,  U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NA,  U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, U_NA,  U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_BTN1, KC_BTN3, KC_BTN2, U_NU \
),
[MEDIA] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                     U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NA,    U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_MSTP, KC_MPLY, KC_MUTE, U_NU \
)
#else
[NAV] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                    U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,   KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_ENT, KC_BSPC, KC_DEL,  U_NU \
),
[MOUSE] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                     U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                     U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND,   U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                     U_NA,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,    U_NA,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_BTN1, KC_BTN3, KC_BTN2, U_NU \
),
[MEDIA] = LAYOUT( \
  U_NU, U_NU,    U_NU,    U_NU,    U_NU,    U_NU,                     U_NU,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
  U_NU, RESET,   U_NA,    U_NA,    U_NA,    U_NA,                     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, U_NU, \
  U_NU, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,                     U_NA,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, U_NU, \
  U_NU, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA, U_NP,      U_NU,    U_NA,    U_NA,    U_NA,    U_NA,    U_NA,    U_NU, \
                          U_NU,    U_NA,    U_NA, U_NA,      KC_MSTP, KC_MPLY, KC_MUTE, U_NU \
)
#endif // MIRYOKU_NAV_VI
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

   switch (keycode) {
    case JIGGLE:
        if (record->event.pressed) {
          jiggle_mode = !jiggle_mode;  
          jiggle_timer = timer_read32(); 
        }
        break;
    }

  #ifdef OLED_ENABLE
  process_record_user_oled(keycode, record);
  #endif  

  return true;
}


void matrix_scan_user(void){
  if (jiggle_mode) {  
    uint32_t elapsed = timer_elapsed32(jiggle_timer);
    if (elapsed > JIGGLE_DELAY) {   
      #if defined(__AVR_ATmega32U4__)
          uint8_t digit = (TCNT0 + TCNT1 + TCNT3 + TCNT4) % 10;
      #else
          uint8_t digit = rand() % 10;
      #endif    
      if (digit < 2) {
        tap_code(KC_MS_WH_DOWN);
      } else if (digit < 4) {
        tap_code(KC_MS_WH_UP);        
      } else if (digit < 7) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_RIGHT);
      } else {
        tap_code(KC_MS_DOWN);
        tap_code(KC_MS_LEFT);
      }
      
      jiggle_timer = timer_read32(); 
    }
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_F:
        case HOME_J:
            return true;
        default:
            return false;
    }
}

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {    
        case SYM_ENT:
            // Lower tapping term so Enter doesn't get hit accidentally
            return TAPPING_TERM - 50;    
        case HOME_A:
        case HOME_SCLN:
        case HOME_S:
        case HOME_L:
        case HOME_X:
        case HOME_DOT:
            // increase for modtaps for gui, alt
            return TAPPING_TERM + 50;  
        default:
            return TAPPING_TERM;
    }
};