#include "quantum.h"
#include "rgblight.h"
#include "led.h"
#include "keyboard.h"
#include "dactyl-open-yd2040.h"


#define THE_FREQUENCY 750  // in milliseconds

// Mask out handedness diode to prevent it
// from keeping the keyboard awake.
const matrix_row_t matrix_mask[] = {
  0b01111111,
  0b01111111,
  0b01111111,
  0b00111111,
  0b01111111,
  0b01110000,
  0b01111111,
  0b01111111,
  0b01111111,
  0b00111111,
  0b01111111,
  0b01110000,
};



void refresh_system_led_states( led_t led_state );
void refresh_nkro_state( void );




void keyboard_pre_init_user( void ) {
  // Use the blue LED on yd2040 as an indicator. (Left: SECOND_LAYER,  Right: NKRO)
  gpio_set_pin_output(GP25);
  refresh_nkro_state();
  refresh_system_led_states( host_keyboard_led_state() );
}



void refresh_nkro_state( void ) {
  // light up the led when NKRO is off
  if ( keymap_config.nkro )
    gpio_write_pin_high(GP25);
  else
    gpio_write_pin_low(GP25);
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NK_TOGG:
      // NKRO state indicator is on the right half.
      if ( is_keyboard_left() )
        return true;

      // Don't do anything extra when the key is released.
      if (!record->event.pressed)
        return true;

      refresh_nkro_state();
      return true;

    default:
      return true; // Process all other keycodes normally
  }
}




layer_state_t layer_state_set_user(layer_state_t state) {
  // The indicator for SECOND_LAYER is on the left half.
  if ( !is_keyboard_left() )
    return state;

  if ( layer_state_cmp(state, SECOND_LAYER) )
    gpio_write_pin_high(GP25);
  else
    gpio_write_pin_low(GP25);

  return state;
}




void refresh_system_led_states( led_t led_state ) {
  if ( is_keyboard_left() ) {
    // is it the left half?
    if ( !led_state.caps_lock ) {
      if ( rgblight_is_enabled() )
        rgblight_disable_noeeprom();
      return;
    }
    if ( !rgblight_is_enabled() )
      rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);

  } else {
    // is it the right half?
    if ( !led_state.num_lock ) {
      if ( rgblight_is_enabled() )
        rgblight_disable_noeeprom();
      return;
    }

    if ( !rgblight_is_enabled() )
      rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
  }
}


bool led_update_kb(led_t led_state) {
  bool res = led_update_user(led_state);
  if ( res ) {
    refresh_system_led_states(led_state);
  }

//end_led_update_kb:
  return res;
}




void housekeeping_task_kb(void) {

  /*
  static uint16_t last_tick = 0;

  // Just in case capslock and numlock is modified by a method other than our keyboard.
  if ( timer_elapsed(last_tick) > THE_FREQUENCY ) {
    led_t host_keeb_led_state = host_keyboard_led_state();

    if ( is_keyboard_left() ) {
      // is it the left half?

      if ( !host_keeb_led_state.caps_lock ) {
        if ( rgblight_is_enabled() )
          rgblight_disable_noeeprom();
        goto end_housekeeping_kb;
      }

      if ( !rgblight_is_enabled() )
        rgblight_enable_noeeprom();
      rgblight_sethsv_noeeprom(HSV_GREEN);

    } else {
      // is it the right half?

      if ( !host_keeb_led_state.num_lock ) {
        if ( rgblight_is_enabled() )
          rgblight_disable_noeeprom();
        goto end_housekeeping_kb;
      }

      if ( !rgblight_is_enabled() )
        rgblight_enable_noeeprom();
      rgblight_sethsv_noeeprom(HSV_BLUE);
    }

end_housekeeping_kb:
    last_tick = timer_read();
  }
  */

  housekeeping_task_user();
}
