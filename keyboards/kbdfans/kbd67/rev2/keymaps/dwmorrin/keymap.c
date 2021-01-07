/* Copyright 2018 'mechmerlin'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const rgblight_segment_t PROGMEM rgb_layer_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLACK}
);
const rgblight_segment_t PROGMEM rgb_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM dm_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_0,
    rgb_layer_1
);

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  DM_WORD = SAFE_RANGE,
  DM_BACK,
  DM_END,
  DM_HOME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * | ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |F1  |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |F2  |
   * |----------------------------------------------------------------|
   * |Escape |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |F3  |
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |PgU|F4  |
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Cmd | Cmd/Spc| TG(1)|Ctl/Spc|Cmd|Alt|Ctrl|Hyp|PgD|F5  |
   * `----------------------------------------------------------------'
   */
[0] = LAYOUT_65_ansi_split_space(
  KC_GRV,  KC_1,    KC_2,   KC_3,  KC_4,   KC_5,   KC_6,    KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_F1, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,  KC_R,   KC_T,   KC_Y,    KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_F2, \
  KC_ESC,  KC_A,    KC_S,   KC_D,  KC_F,   KC_G,   KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_F3,  \
  KC_LSFT, KC_Z,    KC_X,   KC_C,  KC_V,   KC_B,   KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_PGUP, KC_F4, \
  KC_LCTL, KC_LALT, KC_LGUI,LGUI_T(KC_SPC),TG(1),  RCTL_T(KC_SPC),         KC_RGUI, KC_RALT, KC_RCTL, KC_HYPR, KC_PGDN, KC_F5),

  /* Keymap Vi Layer: pseudo vi normal mode and higher fn keys
   * ,----------------------------------------------------------------.
   * |   |   |   |   |END|   |   |   |   |   |HOM|F11|F12|Lef    |F6  |
   * |----------------------------------------------------------------|
   * |     |   |WRD|   |   |   |   |   |TO0|   |   |   |   |     |F7  |
   * |----------------------------------------------------------------|
   * |      |TO0|   |   |   |   |Lef|Dow| Up|Rig|   |   |        |F8  |
   * |----------------------------------------------------------------|
   * |        |   |Del|   |   |BCK|   |   |   |   |   |      |   |F9  |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |F10 |
   * `----------------------------------------------------------------'
   */
[1] = LAYOUT_65_ansi_split_space(
  _______, _______, _______, _______,  DM_END, _______, _______, _______, _______, _______,  DM_HOME, KC_F11,  KC_F12,  KC_LEFT, KC_F6, \
  _______, _______, DM_WORD, _______, _______, _______, _______, _______, TO(0),   _______,  _______, _______, _______, _______, KC_F7, \
  _______, TO(0),   _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,          _______, KC_F8, \
  _______, _______, KC_DEL,  _______, _______, DM_BACK, _______, _______, _______, _______,  _______, _______,          _______, KC_F9, \
  _______, _______, _______, _______, _______, _______,                            _______,  _______, _______, _______, _______, KC_F10),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DM_WORD:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
      }
      break;
    case DM_BACK:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
      }
      break;
    case DM_END: // no shift == 4, with shift == END
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) SEND_STRING(SS_LCTL("e"));
        else register_code(KC_4);
      }
      else if (!(get_mods() & MOD_MASK_SHIFT)) unregister_code(KC_4);
      break;
    case DM_HOME:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("a"));
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void keyboard_post_init_user(void) {
  rgblight_layers = dm_rgb_layers;
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, 0));
  rgblight_set_layer_state(1, layer_state_cmp(state, 1));
  return state;
}
