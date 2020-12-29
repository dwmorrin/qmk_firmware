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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  DM_WORD = SAFE_RANGE,
  DM_BACK,
  DM_DEL,
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
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|TG(1) |PgU|F4  |
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |Cmd |        Space          |Cmd|Alt|Ctrl|F8 |PgD|F12 |
   * `----------------------------------------------------------------'
   */
[0] = LAYOUT_65_ansi(
  KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_F1, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_F2, \
  KC_ESC,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_F3,  \
  KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, TG(1),            KC_PGUP, KC_F4, \
  KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                          KC_RGUI, KC_RALT, KC_RCTL, KC_F8,   KC_PGDN, KC_F12),

  /* Keymap Fn Layer
   * ,----------------------------------------------------------------.
   * |   |   |   |   |END|   |   |   |   |F9 |HOM|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |WRD|   |   |   |   |   |TO0|SLk|Pau|Up |   |     |    |
   * |----------------------------------------------------------------|
   * |      |Lef|Dow|Rig|   |   |Lef|Dow| Up|Rig|   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |DEL|   |   |BCK|   |   |End|PDn|Dow|      |PUp|    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |Hom|PDn|End |
   * `----------------------------------------------------------------'
   */
[1] = LAYOUT_65_ansi(
  _______, _______,_______,_______,DM_END ,_______,_______,_______,_______,  KC_F9,DM_HOME, KC_F11, KC_F12,          KC_DEL,KC_INS, \
  _______, _______,DM_WORD,_______,_______,_______,_______,_______,TO(0),KC_SLCK,KC_PAUS,  KC_UP,_______,     _______,_______,   \
  _______, KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,_______,_______,            _______,_______, \
  _______, _______,DM_DEL ,_______,_______,DM_BACK,_______,_______, KC_END,KC_PGDN,KC_DOWN,       _______,KC_PGUP,_______, \
  _______, _______,_______,                     _______,                     _______,_______,_______,KC_HOME,KC_PGDN, KC_END),

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
    case DM_DEL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("d"));
  }
      break;
    case DM_END:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("e"));
      }
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

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch(get_highest_layer(state)) {
    case 1:
      rgblight_setrgb(0xFF, 0x00, 0x00);
      break;
    default:
      rgblight_setrgb(0x00, 0x00, 0x00);
  }
  return state;
}
