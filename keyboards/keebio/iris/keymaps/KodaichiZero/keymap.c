#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FIGHT 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  FIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// KC_HOME KC_END
  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,          KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_SPC,  KC_LALT,                    RAISE,  RSFT_T(KC_BSPC),  LOWER
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP,                            KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                            KC_PMNS, KC_P1,   KC_P2,   KC_P3,   _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, KC_PAUS, KC_PSCR, _______,          _______, KC_PPLS, KC_P0,   KC_PDOT, KC_PEQL, KC_BSLS, KC_PENT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                             RGB_TOG, RGB_M_P, RGB_RMOD,RGB_MOD, RGB_SPI, RGB_SPD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ACL2, KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                            RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ACL1, KC_BTN5, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ACL0, KC_INS,  KC_SCRL, KC_NUM,  KC_CAPS, KC_WH_D, _______,          _______, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLU, KC_VOLD, KC_MUTE,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            TG(_FIGHT), _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            SGUI(KC_S), LALT(KC_ENT), LGUI(KC_L),  _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, LALT(KC_F4), LALT(KC_TAB), LGUI(KC_D), _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FIGHT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, KC_LSFT, _______,                   _______, KC_RSFT, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

bool rgb_matrix_indicators_user(void) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        HSV t_hsv;
        RGB t_rgb;

        case 1:;
        //When the LOWER layout is active, we highlight the virtual numpad and the cursor keys.
			uint8_t arr1[15] = {8, 14, 15, 16, 36, 37, 38, 41, 42, 43, 48, 49, 50, 53, 54};
			t_hsv = rgb_matrix_get_hsv();
         t_hsv.h = 90;
			t_rgb = hsv_to_rgb(t_hsv);
			for(int i = 0; i < sizeof(arr1); i++) {
				rgb_matrix_set_color(arr1[i], t_rgb.r, t_rgb.g, t_rgb.b);
			}
            break;

        case 2:;
		//When the UPPER layout is active, we highlight the RGB controls and the mouse movement keys.
			uint8_t arr2[15] = {8, 14, 15, 16, 35, 34, 36, 37, 39, 40, 41, 42, 43, 44, 45};
         t_hsv = rgb_matrix_get_hsv();
			t_hsv.h = 130;
			t_rgb = hsv_to_rgb(t_hsv);
			for(int i = 0; i < sizeof(arr2); i++) {
				rgb_matrix_set_color(arr2[i], t_rgb.r, t_rgb.g, t_rgb.b);
			}
            break;

        case 3:
		//When the ADJUST layer is active, we highlight the special shortcut keys.

			//Alt+F4
         t_hsv = rgb_matrix_get_hsv();
			t_hsv.h = 0;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(52, t_rgb.r, t_rgb.g, t_rgb.b);

			//Alt+Tab
			t_hsv.h = 20;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(53, t_rgb.r, t_rgb.g, t_rgb.b);

			//Win+D
			t_hsv.h = 30;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(54, t_rgb.r, t_rgb.g, t_rgb.b);

			//Win+Shift+S
			t_hsv.h = 160;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(51, t_rgb.r, t_rgb.g, t_rgb.b);

			//Alt+Enter
			t_hsv.h = 50;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(50, t_rgb.r, t_rgb.g, t_rgb.b);

			//Win+L
			t_hsv.h = 115;
			t_rgb = hsv_to_rgb(t_hsv);
			rgb_matrix_set_color(49, t_rgb.r, t_rgb.g, t_rgb.b);

         break;
    }
    return true;
}
