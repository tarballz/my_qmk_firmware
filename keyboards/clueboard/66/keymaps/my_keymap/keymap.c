#include "66.h"

// Helpful defines
#define _______ KC_TRNS

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _GL 1
#define _WL 2
#define _FL 3
#define _CL 4

// Defining FN_CAPS to Momemtarily switch to _FL when held, and caps when tapped.
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
// Defining shorter dynamic macro keycodes
#define D_R1 DYN_REC_START1
#define D_R2 DYN_REC_START2
#define D_P1 DYN_MACRO_PLAY1
#define D_P2 DYN_MACRO_PLAY2
#define D_SP DYN_REC_STOP

// Declaring new keycode for auto-run
enum my_keycodes {
	RUND = SAFE_RANGE,   // For down(shift + w)
	RUNU,			           // For up(shift + w)
  DYNAMIC_MACRO_RANGE, // For Dynamic Macros
};
// For whatever reason I have to include the dynamic macro header here
#include "dynamic_macro.h"

// Define behavior for RUND and RUNU custom keycodes
// Could also use process_record_kb()?  Not sure of the difference
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // Apparently I also need this for Dynamic Macros
  if (!process_record_dynamic_macro(keycode, record))
  {
    return false;
  }
	switch(keycode) {
		case RUND:
      if(record->event.pressed)
      {
        register_code(KC_LSFT);
        register_code(KC_W);
      }
			return false;

		case RUNU:
			if(record->event.pressed)
      {
				unregister_code(KC_LSFT);
				unregister_code(KC_W);
			}
			return false;
	}
	return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = KEYMAP(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_GRV, KC_BSPC,        KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,                KC_PGDN, \
  FN_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,                          \
  KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,	 KC_COMM, KC_DOT, KC_SLSH,KC_RO,  KC_RSFT,        KC_UP,           \
  KC_LCTL,KC_LGUI,KC_LALT,KC_MHEN,        KC_SPC, KC_SPC,                         KC_HENK,KC_RALT,MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),


  /* Keymap _GL: Gaming Layer
   */
[_GL] = KEYMAP(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   RUND,   RUNU,   KC_GRV, KC_BSPC,        KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,                KC_PGDN, \
  KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,                          \
  KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,	  KC_M,  KC_COMM, KC_DOT, KC_SLSH,KC_RO,  KC_RSFT,        KC_UP,           \
  KC_LCTL,KC_NO  ,KC_LALT,KC_MHEN,        KC_SPC, KC_SPC,                         KC_HENK,KC_RALT,MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),


  /* Keymap _WL: Work Layer
   */
[_WL] = KEYMAP(
  KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_GRV, KC_BSPC,        KC_PGUP, \
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,                KC_PGDN, \
  FN_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,                          \
  KC_LSPO,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH,KC_RO,  KC_RSPC,        KC_UP,           \
  KC_LCTL,KC_LGUI,KC_LALT,KC_MHEN,        KC_SPC, KC_SPC,                         KC_HENK,KC_RGUI,MO(_FL),KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = KEYMAP(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,KC_DEL,         KC_VOLU, \
  _______, D_R1,   D_R2,   D_SP,  _______,_______,_______,_______,_______,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_MUTE,                KC_VOLD, \
  _______, D_P1,   D_P2,  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  _______,_______,_______,_______,MO(_CL),_______,_______,_______,TO(_BL),TO(_GL),TO(_WL),_______,_______,_______,        KC_PGUP,         \
  _______,_______,_______,_______,        _______,_______,                        _______,_______,MO(_FL),_______,KC_HOME,KC_PGDN,KC_END),

  /* Keymap _CL: Control layer
   */
[_CL] = KEYMAP(
  BL_STEP,RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN,RGB_M_K,RGB_M_X,RGB_M_G,_______,_______,_______,_______,_______,RGB_TOG,        RGB_VAI, \
  _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,                RGB_VAD, \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,                         \
  MO(_FL),_______,_______,_______,MO(_CL),_______,_______,_______,_______,_______,_______,_______,_______,_______,        RGB_SAI,         \
  _______,_______,_______,_______,        RGB_MOD,   RGB_MOD,                     _______,_______,MO(_FL),_______,RGB_HUD,RGB_SAD,RGB_HUI),

};

