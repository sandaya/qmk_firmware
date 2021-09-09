

#pragma once

//#define MIRYOKU_CLIPBOARD_MAC
#define MIRYOKU_NAV_VI


#define MASTER_LEFT
//#define USE_SERIAL_PD2

// Default tapping term is 200
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// This prevents accidental repeats of the tap-hold keys when typing quickly.
#define TAPPING_FORCE_HOLD_PER_KEY

#undef PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// The setting below defines how many times you need to tap a TT() to toggle the layer.
#define TAPPING_TOGGLE 3

// Limits the max. amount of layers to 8 to save firmware memory.
#define LAYER_STATE_8BIT

// Save firmware space
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT


// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

// Underglow
#undef RGBLED_NUM
#ifdef RGBLIGHT_ENABLE
  #define RGBLED_NUM 12
  #define RGBLED_SPLIT {6,6}
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_SLEEP
#endif 

// Encoder
#ifdef ENCODER_ENABLE 
  #define ENCODERS_PAD_A { F5 }
  #define ENCODERS_PAD_B { F4 }
#endif

#ifdef OLED_ENABLE
  #define OLED_TIMEOUT 30000
  #define OLED_BRIGHTNESS 125
#endif

