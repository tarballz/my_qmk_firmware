
#include "m10a.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
  _LAYER0,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _LAYER4,
  _LAYER5,
  _LAYER6,
  _LAYER7,
  _LAYER8,
  _LAYER9
};

// // Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXX   KC_NO
#define KC_LWIN KC_LGUI

/* Declare custom keycodes */
enum my_keycodes
{
  KC_DBLD = SAFE_RANGE,  // Docker build
  KC_DKLL,               // Docker kill
  /* ----- AppCode keycodes ----- */
  KC_SHF8,               // Shift + F8      (Step out)
  KC_CTLD,               // Ctrl + D        (Start debug)
  KC_SF2,                // Super + F2      (Stop debug)
  KC_SF8 ,               // Super + F8      (Toggle breakpoint)
  KC_AF10,               // Alt   + F10     (Go to execution point)
  KC_ASR,                // Alt + Super + R (Continue)
  KC_AF9,                // Alt + F9        (Continue to cursor)
  /* ----- XCode keycodes ----- */
  KC_SB,                 // Super + B        (Build)
  KC_SR,                 // Super + R        (Run)
  KC_SP,                 // Super + .        (Stop)
  KC_CSY,                // Ctrl + Super + Y (Continue)
  KC_CSC,                // Ctrl + Super + C (Continue to cursor)
  KC_SBSL,               // Super + BkSlash  (Toggle Breakpoint)
  
};

/* Now define behavior for these custom keycodes */
bool process_record_user (uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {

    // Docker build
    case KC_DBLD:
      if (record->event.pressed)
      {
        /* Launch an eOS terminal */
        SEND_STRING (SS_LGUI ("t"));

        /* Add a slight delay to make sure screen is caught up */
        _delay_ms (500);

        /* Run docker_go.sh */
        SEND_STRING ("cd /home/cool/Mantis && ./docker_go.sh" SS_TAP (X_ENTER));
        SEND_STRING ("r00t005" SS_TAP (X_ENTER));
      }
      return false;

    // Docker kill
    case KC_DKLL:
      if (record->event.pressed)
      {
        /* Launch an eOS terminal */
        SEND_STRING (SS_LGUI ("t"));

        /* Add a slight delay to make sure screen is caught up */
        _delay_ms (500);

        /* Run docker_stopall.sh */
        SEND_STRING ("cd /home/cool/Mantis && ./docker_stopall.sh" SS_TAP (X_ENTER));
        SEND_STRING ("r00t005" SS_TAP (X_ENTER));
      }
      return false;

    /* ----- AppCode keycodes ----- */
    /* Step out */
    case KC_SHF8:
      if (record->event.pressed)
      {
        register_code (KC_LSFT);
        register_code (KC_F8);
        unregister_code (KC_LSFT);
        unregister_code (KC_F8);
      }
      return false;

    /* Start debug */
    case KC_CTLD:
      if (record->event.pressed)
      {
        SEND_STRING (SS_LCTRL ("d"));
      }
      return false;

    /* Stop debug */
    case KC_SF2:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_F2);
        unregister_code (KC_LWIN);
        unregister_code (KC_F2);
      }
      return false;

    /* Toggle breakpoint */
    case KC_SF8:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_F8);
        unregister_code (KC_LWIN);
        unregister_code (KC_F8);
      }
      return false;

    /* Show execution point */
    case KC_AF10:
      if (record->event.pressed)
      {
        register_code (KC_LALT);
        register_code (KC_F10);
        unregister_code (KC_LALT);
        unregister_code (KC_F10);
      }
      return false;

    /* Continue */
    case KC_ASR:
      if (record->event.pressed)
      {
        register_code (KC_LALT);
        register_code (KC_LWIN);
        register_code (KC_R);
        unregister_code (KC_LALT);
        unregister_code (KC_LWIN);
        unregister_code (KC_R);
      }
      return false;

    /* Continue to cursor */
    case KC_AF9:
      if (record->event.pressed)
      {
        register_code (KC_LALT);
        register_code (KC_F9);
        unregister_code (KC_LALT);
        unregister_code (KC_F9);
      }
      return false;

    /* ----- XCode keycodes ----- */
    /* Build */
    case KC_SB:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_B);
        unregister_code (KC_LWIN);
        unregister_code (KC_B);
      }
      return false;

    /* Run */
    case KC_SR:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_R);
        unregister_code (KC_LWIN);
        unregister_code (KC_R);
      }
      return false;

    /* Stop */
    case KC_SP:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_DOT);
        unregister_code (KC_LWIN);
        unregister_code (KC_DOT);
      }
      return false;

    /* Continue */
    case KC_CSY:
      if (record->event.pressed)
      {
        register_code (KC_LCTL);
        register_code (KC_LWIN);
        register_code (KC_Y);
        unregister_code (KC_LCTL);
        unregister_code (KC_LWIN);        
        unregister_code (KC_Y);           
      }
      return false;

    /* Continue to cursor */
    case KC_CSC:
      if (record->event.pressed)
      {
        register_code (KC_LCTL);
        register_code (KC_LWIN);
        register_code (KC_C);
        unregister_code (KC_LCTL);
        unregister_code (KC_LWIN);        
        unregister_code (KC_C);    
      }
      return false;
    
    /* Toggle breakpoint */
    case KC_SBSL: 
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_BSLASH);
        unregister_code (KC_LWIN);
        unregister_code (KC_BSLASH);
      }
      return false;

  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = {
    {KC_F8,     KC_F7,    KC_SHF8    },
    {KC_CTLD,   KC_SF2,   KC_SF8     },
    {KC_ASR,    KC_AF9,   KC_AF10    },
    {XXXXX,     XXXXX,    MO(_LAYER9)}
  },
  [_LAYER1] = {
    {KC_F6,   KC_F7,   KC_F8  },
    {KC_SR,   KC_SP,   KC_SBSL},
    {KC_CSY,  KC_CSC,  KC_SB  },
    {XXXXX,   XXXXX,   _______}
  },
  [_LAYER2] = {
    {KC_DBLD, KC_DKLL,  KC_C},
    {KC_D,  KC_E,   KC_F},
    {KC_G,  KC_H,   KC_I},
    {XXXXX, XXXXX,  _______}
  },
  [_LAYER3] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  [_LAYER4] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  [_LAYER5] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  [_LAYER6] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  [_LAYER7] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  [_LAYER8] = {
    {KC_A, KC_B, KC_C},
    {KC_D, KC_E, KC_F},
    {KC_G, KC_H, KC_I},
    {XXXXX, XXXXX, _______}
  },
  /* Layer-select layer */
  [_LAYER9] = {
    {TO(_LAYER0), TO(_LAYER1), TO(_LAYER2)},
    {   KC_D,       KC_E,         KC_F    },
    {  BL_INC,     BL_DEC,        RESET   },
    {   XXXXX,      XXXXX,       _______  }
  }
};

void matrix_init_user(void) {
  #ifdef BACKLIGHT_ENABLE
    backlight_level(0);
  #endif
}
