/* Copyright 2020 Jack Kester
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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE,
    _LOWER,
};

enum {
    TD_LO = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LO] = ACTION_TAP_DANCE_DOUBLE(KC_MUTE, LGUI(KC_L))
};

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes {
//     QMKBEST = SAFE_RANGE,
//     QMKURL
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
        KC_MEDIA_NEXT_TRACK,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_PREV_TRACK,   TD(TD_LO),     MO(_LOWER),    RESET 
    ),
    [_LOWER] = LAYOUT_all(
        LSG(KC_L),   LSG(KC_BSLS),   LGUI(KC_5),    LGUI(KC_4),    KC_TRNS,    KC_TRNS
    )   
};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)){
        case 1:
            if (!clockwise) {
                tap_code(KC_RGHT);
            } else {
                tap_code(KC_DOWN);
            }
            break;
        default:
            // Volume control
            if (!clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return 1;
}
#endif

