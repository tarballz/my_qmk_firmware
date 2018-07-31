#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define TAPPING_TERM 200
uint16_t lt12_timer;

enum layers
{
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4,
    _LAYER5
};

enum custom_keycodes
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
  KC_SSRB,               //Shft+Spr+]       (Go to right tab)
  KC_SSLB,               //Shft+spr+[       (Go to left tab)
  KC_APPL,               // Tap layer thing
  /* ----- XCode keycodes ----- */
  KC_SB,                 // Super + B        (Build)
  KC_SR,                 // Super + R        (Run)
  KC_SP,                 // Super + .        (Stop)
  KC_CSY,                // Ctrl + Super + Y (Continue)
  KC_CSC,                // Ctrl + Super + C (Continue to cursor)
  KC_SBSL,               // Super + BkSlash  (Toggle Breakpoint)
  /* ----- VSCode keycodes ----- */
  KC_GOB,                // Ctrl + -         (Go back)
  KC_GOF,                // Ctrl + Shft + -  (Go forward)
  KC_SAR,                // Spr+Alt+Right    (Next tab)
  KC_SAL,                // Spr+Alt+Left     (Prev tab)
  KC_AF12,               // Alt + F12        (Peek Definition)
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

    /* Right editor tab */
    case KC_SSRB:
      if (record->event.pressed)
      {
        register_code (KC_LSFT);
        register_code (KC_LWIN);
        register_code (KC_RBRC);
        unregister_code (KC_LSFT);
        unregister_code (KC_LWIN);
        unregister_code (KC_RBRC);
      }
      return false;

    /* Left editor tab */
    case KC_SSLB:
      if (record->event.pressed)
      {
        register_code (KC_LSFT);
        register_code (KC_LWIN);
        register_code (KC_LBRC);
        unregister_code (KC_LSFT);
        unregister_code (KC_LWIN);
        unregister_code (KC_LBRC);
      }
      return false;

    /* Only go to layer 5 (layer switch layer) if the button is held,
     * if tapped, goto layer 4 */
    case KC_APPL: 
      if (record->event.pressed)
      {
        lt12_timer = timer_read();
        layer_on(_LAYER5);
      }
      else
      {
        layer_off(_LAYER5);
        if (timer_elapsed(lt12_timer) < TAPPING_TERM)
          layer_on(_LAYER4);
      }
      return true;

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

    /* ----- VSCode keycodes ----- */
    /* Go back */
    case KC_GOB:
      if (record->event.pressed)
      {
        register_code (KC_LCTL);
        register_code (KC_MINUS);
        unregister_code (KC_LCTL);
        unregister_code (KC_MINUS);
      }
      return false;

    /* Go forward */
    case KC_GOF:
      if (record->event.pressed)
      {
        register_code (KC_LCTL);
        register_code (KC_LSFT);
        register_code (KC_MINUS);
        unregister_code (KC_LCTL);
        unregister_code (KC_LSFT);
        unregister_code (KC_MINUS);
      }
      return false;

    /* Next tab */
    case KC_SAR:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_LALT);
        register_code (KC_RIGHT);
        unregister_code (KC_LWIN);
        unregister_code (KC_LALT);
        unregister_code (KC_RIGHT);
      }
      return false;

    /* Prev tab */
    case KC_SAL:
      if (record->event.pressed)
      {
        register_code (KC_LWIN);
        register_code (KC_LALT);
        register_code (KC_LEFT);
        unregister_code (KC_LWIN);
        unregister_code (KC_LALT);
        unregister_code (KC_LEFT);
      }
      return false;

    /* Peek Def */
    case KC_AF12:
      if (record->event.pressed)
      {
        register_code (KC_LALT);
        register_code (KC_F12);
        unregister_code (KC_LALT);
        unregister_code (KC_F12);
      }
      return false;

  }
  return true;
}

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Appcode L1 */
    [_LAYER0] = LAYOUT(
      KC_F8,   KC_F7,  KC_SHF8,    
      KC_CTLD, KC_SF2, KC_APPL),
    /* Xcode */
    [_LAYER1] = LAYOUT(
      KC_F6, KC_F7, KC_F8,
      KC_SB, KC_SR, MO(_LAYER5)),
    /* VSCode L1*/
    [_LAYER2] = LAYOUT(
      KC_SAL, KC_SAR, TO(_LAYER3),
      KC_GOB, KC_GOF, _______),
    /* VSCode L2 */
    [_LAYER3] = {
      { KC_AF12, XXXXXXX, TO(_LAYER2),
        XXXXXXX, XXXXXXX, _______     }
    },
    /* Appcode L2 */
    [_LAYER4] = LAYOUT(
      KC_SSLB, KC_SSRB, TO(_LAYER0),
      KC_ASR,  KC_AF10, _______),
    /* Layer-switch layer */
    [_LAYER5] = LAYOUT(
      TO(_LAYER0), TO(_LAYER1), TO(_LAYER2),
      TO(_LAYER4), XXXXXXX,     _______)
};

void matrix_init_user(void)
{
#ifdef BACKLIGHT_ENABLE
    backlight_level(0);
#endif
}
