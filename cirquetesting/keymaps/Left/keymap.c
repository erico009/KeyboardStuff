// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define _CENTER 512
#define _DEAD 20
bool wasdMode = true;
bool arrowMode = false;
#define _DOWN_TRESHOLD (_CENTER+_DEAD)
#define _UP_TRESHOLD (_CENTER-_DEAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_5x7_2(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSLS, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, 
		KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_MINS, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(1), 
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_NO, KC_NO),
	[1] = LAYOUT_5x7_2(
		KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F13, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(1), 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS),
};
#ifdef JOYSTICK_ENABLE
#include "joystick.h"
#include "analog.h"
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F0, 95, 518, 985),
    JOYSTICK_AXIS_IN(F1, 859, 514, 9),
};
  int16_t xPos = 0;
  int16_t yPos = 0;

  bool yDownHeld = false;
  bool yUpHeld = false;
  bool xLeftHeld = false;
  bool xRightHeld = false;
void matrix_scan_user(void) {
    if (wasdMode) {
      yPos = analogReadPin(F0);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
          register_code(KC_W);
          yDownHeld = true;
        } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
          yDownHeld = false;
          unregister_code(KC_W);
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
          yUpHeld = true;
          register_code(KC_S);
        } else if (yUpHeld && yPos > _UP_TRESHOLD) {
          yUpHeld = false;
          unregister_code(KC_S);
        }
      
      xPos = analogReadPin(F1);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_A);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_A);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_D);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_D);
      }
    }
	else if (arrowMode) {
      yPos = analogReadPin(F0);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
          register_code(KC_UP);
          yDownHeld = true;
        } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
          yDownHeld = false;
          unregister_code(KC_UP);
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
          yUpHeld = true;
          register_code(KC_DOWN);
        } else if (yUpHeld && yPos > _UP_TRESHOLD) {
          yUpHeld = false;
          unregister_code(KC_DOWN);
        }
      
      xPos = analogReadPin(F1);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_LEFT);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_LEFT);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_RIGHT);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_RIGHT);
      }
    }
  }
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_F13 && record->event.pressed) {
    if (!wasdMode && !arrowMode) {
      wasdMode = true;
    } else if (wasdMode){
      wasdMode = false;
	  arrowMode = true;
    } else if (arrowMode){
		arrowMode = false;
	}
  }
  return true;
};