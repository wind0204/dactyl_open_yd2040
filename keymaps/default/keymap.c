//#include <bits/struct_mutex.h>
//#include <math.h>
#include QMK_KEYBOARD_H
#include "dactyl-open-yd2040.h"


enum tap_dance {
  TD_RCTL_L2,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_RCTL_L2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RCTL, SECOND_LAYER),
};

// How long (in milliseconds) to wait between animation steps for each of the "Solid color breathing" animations
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {16, 8, 4, 2};


//#define TAPPING_TOGGLE 2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY_LAYER] = LAYOUT_5x7(
        // left hand
        KC_GRAVE,  KC_1   ,   KC_2   ,   KC_3   ,   KC_4   ,   KC_5   ,  KC_6   ,
        KC_TAB ,   KC_Q   ,   KC_W   ,   KC_E   ,   KC_R   ,   KC_T   ,  _______ ,
        KC_CAPS,   KC_A   ,   KC_S   ,   KC_D   ,   KC_F   ,   KC_G   ,  KC_LBRC,
        KC_LSFT,   KC_Z   ,   KC_X   ,   KC_C   ,   KC_V   ,   KC_B   ,
        _______,   _______,   _______,   _______,   KC_LALT,             KC_DEL , AU_TOGG,
                                                               KC_SPC ,  KC_LCTL, KC_LGUI,
        // right hand ( inversed )
        KC_EQL ,   KC_MINS,   KC_0   ,   KC_9   ,   KC_8   ,   KC_7   ,  KC_PGUP,
        KC_BSLS,   KC_P   ,   KC_O   ,   KC_I   ,   KC_U   ,   KC_Y   ,  KC_PGDN,
        KC_QUOT,   KC_SCLN,   KC_L   ,   KC_K   ,   KC_J   ,   KC_H   ,  KC_RBRC,
        KC_RSFT,   KC_SLSH,   KC_DOT ,   KC_COMM,   KC_M   ,   KC_N   ,
        OSL(THIRD_LAYER), KC_ENT, KC_END, KC_HOME,  KC_RALT,             KC_BSPC, KC_PSCR,
                                                               KC_SPC ,  TD(TD_RCTL_L2), KC_ESC
    ),

    [SECOND_LAYER] = LAYOUT_5x7(
        // left hand
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   KC_BTN2,   KC_BTN1,   KC_BTN3,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,
        NK_TOGG,   _______,   _______,   _______,   _______,             _______, _______,
                                                                _______, _______, _______ ,
        // right hand ( inversed )
        _______,   KC_PMNS,   KC_PAST,   KC_PSLS,   _______,   _______,  _______,
        _______,   KC_PPLS,   KC_P9  ,   KC_P8  ,   KC_P7  ,   _______,  _______,
        _______,   KC_PPLS,   KC_P6  ,   KC_P5  ,   KC_P4  ,   _______,  _______,
        _______,   KC_PENT,   KC_P3  ,   KC_P2  ,   KC_P1  ,   _______,
        _______,   KC_PENT,   KC_PDOT,   KC_P0  ,   KC_P0  ,             _______, _______,
                                                                _______, _______, _______
    ),

    [THIRD_LAYER] = LAYOUT_5x7(
        // left hand
        _______,   KC_F1  ,   KC_F2  ,   KC_F3  ,   KC_F4  ,   KC_F5  ,  KC_F6  ,
        _______,   _______,   KC_UP  ,   _______,   _______,   _______,  _______,
        _______,   KC_LEFT,   KC_DOWN,   KC_RGHT,   _______,   _______,  _______,
        KC_NUM ,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,             _______, _______,
                                                                _______, _______, _______,
        // right hand ( inversed )
        KC_F12 ,   KC_F11 ,   KC_F10 ,   KC_F9  ,   KC_F8  ,   KC_F7  ,  KC_INS ,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,             _______, _______,
                                                                _______, _______, _______
    ),

};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [QWERTY_LAYER] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
  [SECOND_LAYER] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
  [THIRD_LAYER] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
};
#endif
