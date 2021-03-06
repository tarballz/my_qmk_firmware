#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define TAPPING_TERM 200

// So I can switch between mac and linux layouts.
#define LINUX 1

enum layers
{
  _LAYER0 = 0,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _LAYER4,
  _LAYER5,
  _LAYER6
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
  KC_APPA,               // Tap layer thing
  KC_APPB,
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

/* --------------------------------------------------------------- */
#if 0
void activate_layer_disable_others (int exceptLayer)
{
  int index;

  layer_on (exceptLayer);

  for (index = _LAYER6; index >= _LAYER0; --index)
  {
    if ( (index != exceptLayer) && (IS_LAYER_ON (index)) )
      layer_off (index);
  }
}
#endif

/* --------------------------------------------------------------- */

/* Now define behavior for these custom keycodes */
bool process_record_user (uint16_t keycode, keyrecord_t *record)
{
  static uint16_t lt12_timer;

  switch (keycode) {

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
        #if LINUX == 1
          register_code (KC_LSFT);
          register_code (KC_F9);
          unregister_code (KC_LSFT);
          unregister_code (KC_F9);
        #else
          SEND_STRING (SS_LCTRL ("d"));
        #endif
      }
      return false;

    /* Stop debug */
    case KC_SF2:
      if (record->event.pressed)
      {
        #if LINUX == 1
          register_code (KC_LCTL);
          register_code (KC_F2);
          unregister_code (KC_LCTL);
          unregister_code (KC_F2);
        #else
          register_code (KC_LWIN);
          register_code (KC_F2);
          unregister_code (KC_LWIN);
          unregister_code (KC_F2);
        #endif
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

    /* Only go to layer 6 (layer switch layer) if the button is held,
     * if tapped, goto layer 1 */
    case KC_APPA:
      if (record->event.pressed)
      {
        lt12_timer = timer_read();
        layer_on(_LAYER6);
        //layer_state = 1UL<<_LAYER6;
      }
      else
      {
        layer_off(_LAYER6);
        if (timer_elapsed(lt12_timer) < TAPPING_TERM)
        {
#if 0
          layer_on(_LAYER1);
          if (IS_LAYER_ON(_LAYER6))
            layer_off(_LAYER6);
          if (IS_LAYER_ON(_LAYER4))
            layer_off(_LAYER4);
          if (IS_LAYER_ON(_LAYER3))
            layer_off(_LAYER3);
          if (IS_LAYER_ON(_LAYER2))
            layer_off(_LAYER2);
          if (IS_LAYER_ON(_LAYER0))
            layer_off(_LAYER0);
#else
          default_layer_set(1U<<_LAYER1);
          layer_clear();
          // DF(_LAYER1); // Same as layer_move?
          //layer_move(_LAYER1);
          //layer_state_set (1UL<<_LAYER1);
#endif
        }
      }
      return false;

    /* Only go to layer 5 (layer switch layer) if the button is held,
     * if tapped, goto layer 0 */
    case KC_APPB:
      if (record->event.pressed)
      {
        lt12_timer = timer_read();
        layer_on(_LAYER6);
      }
      else
      {
        layer_off(_LAYER6);
        if (timer_elapsed(lt12_timer) < TAPPING_TERM)
        {
          layer_on(_LAYER0);
          if (IS_LAYER_ON(_LAYER6))
            layer_off(_LAYER6);
          if (IS_LAYER_ON(_LAYER4))
            layer_off(_LAYER4);
          if (IS_LAYER_ON(_LAYER3))
            layer_off(_LAYER3);
          if (IS_LAYER_ON(_LAYER2))
            layer_off(_LAYER2);
          if (IS_LAYER_ON(_LAYER1))
            layer_off(_LAYER1);
        }
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

/* --------------------------------------------------------------- */

#define _______ KC_TRNS
#define XXXXXXX KC_NO
// Defining FN_RT to momentarily switch to _LAYER5EX when held, and right arrow
// when tapped
#define FN_RT LT(_LAYER6, KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Jetbrains L1 */
    [_LAYER0] = LAYOUT(
      KC_F8,   KC_F7,  KC_SHF8,
      KC_CTLD, KC_SF2, KC_APPA),
#if 0
    /* Jetbrains L2 */
    [_LAYER1] = LAYOUT(
      KC_SSLB, KC_SSRB, KC_SF8,
      KC_ASR,  KC_AF10, KC_APPB),
#else
    /* Eclipse layer */
    [_LAYER1] = LAYOUT(
      KC_F6,   KC_F5,   KC_F7,
      KC_F11, RCTL(KC_F2), MO(_LAYER6)),
#endif
    /* VSCode L1*/
    [_LAYER2] = LAYOUT(
      KC_SAL, KC_SAR, TO(_LAYER3),
      KC_GOB, KC_GOF, MO(_LAYER6)),
    /* VSCode L2 */
    [_LAYER3] = {
      { KC_AF12, XXXXXXX, TO(_LAYER2),
        XXXXXXX, XXXXXXX, _______     }
    },
    /* Xcode */
    [_LAYER4] = LAYOUT(
      KC_F6, KC_F7, KC_F8,
      KC_SB, KC_SR, _______),
    /* Arrow and pgup/down layer */
    [_LAYER5] = LAYOUT(
      KC_PGUP, KC_UP,  KC_PGDOWN,
      KC_LEFT, KC_DOWN, FN_RT),
    /* Layer-switch layer */
    [_LAYER6] = LAYOUT(
      TO(_LAYER0), TO(_LAYER1), TO(_LAYER4),
      TO(_LAYER2), TO(_LAYER5), MO(_LAYER6)),
#if 0
    /* Secondary layer-switch layer for arrows */
    [_LAYER5EX] = LAYOUT(
      TO(_LAYER0), TO(_LAYER1), XXXXXXX,
      TO(_LAYER2), TO(_LAYER5), MO(_LAYER5EX))
#endif

};

void matrix_init_user(void)
{
#ifdef BACKLIGHT_ENABLE
    backlight_level(0);
#endif
}