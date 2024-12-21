#include "quantum.h"
#include "rgblight.h"
#include "led.h"
#include "keyboard.h"
#include "dactyl-open-yd2040.h"
#include "transactions.h"
#include <string.h>
#include <stdint.h>

#ifdef CONSOLE_ENABLE
  #include "print.h"
#endif  // CONSOLE_ENABLE

#define LIR_INTERBAL 750  // interval for the long-interval routine in milliseconds
#define TRANSACTION_INTERVAL 256

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



//void init_dactyl_yd2040( void );
void refresh_system_led_states( led_t led_state );
void refresh_nkro_state( uint16_t nkro_state );
void refresh_2nd_layer_indicator( uint8_t is_2nd_layer_on );



static uint8_t should_send_msg[2];
static uint8_t last_state_2nd_layer;

void short_cry_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
  const struct short_cry_m2s *m2s = (const struct short_cry_m2s*)in_data;
  struct short_cry_s2m *s2m = (typeof(s2m))out_data;
  
  s2m->err_no = 0;
  switch ( m2s->the_event_code ) {
    case tec_nkro_state_change:
      if ( is_keyboard_left() ) {
        s2m->err_no = err_not_my_business;
        break;
      }
      refresh_nkro_state( m2s->the_value );
      break;
    case tec_2nd_layer:
      refresh_2nd_layer_indicator( m2s->the_value );
      break;
    //case tec_handshake:
    //  init_dactyl_yd2040();
    //  break;
    default:
      s2m->err_no = err_unknown;
  }
}




void keyboard_pre_init_kb( void ) {
  memset(should_send_msg, 0, sizeof(should_send_msg));
}

void keyboard_post_init_kb( void ) {
  #ifdef CONSOLE_ENABLE
  debug_enable = true;
  dprintf("{Dactyl Pivot - Open} keyboard_post_init_kb\n");
  #endif // CONSOLE_ENABLE

  // Use the blue LED on yd2040 as an indicator. (Left: SECOND_LAYER,  Right: NKRO)
  gpio_set_pin_output(GP25);
  gpio_write_pin_low(GP25);

  refresh_system_led_states( host_keyboard_led_state() );

  transaction_register_rpc(RPC_ID_SHORT_CRY, short_cry_handler);

  keyboard_post_init_user();
}



void refresh_nkro_state( uint16_t nkro_state ) {
  #ifdef CONSOLE_ENABLE
  dprintf("{Dactyl Pivot - Open} refresh_nkro_state\n");
  #endif // CONSOLE_ENABLE

  // light up the led when NKRO is off
  if ( nkro_state )
    gpio_write_pin_low(GP25);
  else
    gpio_write_pin_high(GP25);
}



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NK_TOGG:
      // Don't do anything extra when the key is released.
      if (!record->event.pressed)
        return true;

      // NKRO state indicator is on the right half.
      if ( is_keyboard_left() ) {
        should_send_msg[tec_nkro_state_change - 1] = -1;
        return true;
      }

      refresh_nkro_state( (uint16_t) keymap_config.nkro );
      return true;

    default:
      return true; // Process all other keycodes normally
  }
}




void refresh_2nd_layer_indicator( uint8_t is_2nd_layer_on ) {
  static uint8_t was_2nd_layer_on = 0;
  // The indicator for SECOND_LAYER is on the left half.
  if ( !is_keyboard_left() ) {

    // No need to share other layers' states but SECOND_LAYER's
    if ( is_2nd_layer_on == was_2nd_layer_on )
      return;

    should_send_msg[tec_2nd_layer - 1] = -1;
    last_state_2nd_layer = is_2nd_layer_on;
    
    was_2nd_layer_on = is_2nd_layer_on;
    return;
  }


  // The simple code for the left half goes like this:
  if ( is_2nd_layer_on )
    gpio_write_pin_high(GP25);
  else
    gpio_write_pin_low(GP25);

  was_2nd_layer_on = is_2nd_layer_on;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  #ifdef CONSOLE_ENABLE
  dprintf("{Dactyl Pivot - Open} layer_state_set_kb(\n"
      "\tlayer_state_t state = %x\n)\n", state);
  //dprintf("{Dactyl Pivot - Open} layer_state_t is %u bytes long.\n)\n", sizeof(state));
  // it's 2 bytes long
  #endif // CONSOLE_ENABLE

  refresh_2nd_layer_indicator( layer_state_cmp(state, SECOND_LAYER) );
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
  #ifdef CONSOLE_ENABLE
  dprintf("{Dactyl Pivot - Open} led_update_kb(\n"
      "\tled_t led_state = %x\n)\n", led_state.raw);
  #endif // CONSOLE_ENABLE
  bool res = led_update_user(led_state);
  if ( res ) {
    refresh_system_led_states(led_state);
  }

//end_led_update_kb:
  return res;
}




void housekeeping_task_kb(void) {

  // timestamp for last long interval routine.
  static uint16_t last_tick_lir = 0;
  static uint16_t last_tick_transaction = 0;

  // I thought led_update_kb sometimes got skipped...
  // But it turns out somehow the keyboard keeps the old state even when
  // it has sent the led state change to host system once in a while.
  // host_keyboard_led_state returns false information then. FIXME
  if ( timer_elapsed(last_tick_lir) > LIR_INTERBAL ) {
    /*
    #ifdef CONSOLE_ENABLE
    if ( LIR_INTERBAL >= 1500 )
      dprintf("{Dactyl Pivot - Open} Long-interval routine(refresh_system_led_states)\n");
    #endif // CONSOLE_ENABLE
    led_t led_state = host_keyboard_led_state();
    refresh_system_led_states( led_state );

    last_tick_lir = timer_read();
    */
  }

  if ( !is_keyboard_master() ) {
    goto end_housekeeping;
  }
  if ( timer_elapsed(last_tick_transaction) > TRANSACTION_INTERVAL ) {
    uint_fast8_t i;
    for ( i = 0; i < 2; i++ ) {
      if ( should_send_msg[i] ) {
        break;
      }
    }
    if ( i >= 2 ) {
      goto end_housekeeping;
    }
    switch ( i + 1 ) {
      case tec_nkro_state_change:
        {
        #ifdef CONSOLE_ENABLE
        dprintf("{Dactyl Pivot - Open} Sending a new nkro state to the slave...\n");
        #endif // CONSOLE_ENABLE
        struct short_cry_m2s m2s;
        m2s.the_event_code = tec_nkro_state_change;
        m2s.the_value = (typeof(m2s.the_value)) keymap_config.nkro;
        struct short_cry_s2m s2m;
        if ( transaction_rpc_exec(RPC_ID_SHORT_CRY, sizeof(m2s), &m2s, sizeof(s2m), &s2m) ) {
          last_tick_transaction = timer_read();
          #ifdef CONSOLE_ENABLE
          dprintf("{Dactyl Pivot - Open} Reply from slave = %x\n", s2m.err_no);
          #endif // CONSOLE_ENABLE
          if ( s2m.err_no == 0 ) {
            should_send_msg[i] = 0;
          }
        } else {
          #ifdef CONSOLE_ENABLE
          dprintf("{Dactyl Pivot - Open} Slave sync failed!\n");
          #endif // CONSOLE_ENABLE
        }
        break;
        }

      case tec_2nd_layer:
        {
        #ifdef CONSOLE_ENABLE
        dprintf("{Dactyl Pivot - Open} Sending the 2nd_layer state to the slave...\n");
        #endif // CONSOLE_ENABLE
        struct short_cry_m2s m2s;
        m2s.the_event_code = tec_2nd_layer;
        m2s.the_value = (typeof(m2s.the_value)) last_state_2nd_layer;
        struct short_cry_s2m s2m;
        if ( transaction_rpc_exec(RPC_ID_SHORT_CRY, sizeof(m2s), &m2s, sizeof(s2m), &s2m) ) {
          last_tick_transaction = timer_read();
          #ifdef CONSOLE_ENABLE
          dprintf("{Dactyl Pivot - Open} Reply from slave = %x\n", s2m.err_no);
          #endif // CONSOLE_ENABLE
          if ( s2m.err_no == 0 ) {
            should_send_msg[i] = 0;
          }
        } else {
          #ifdef CONSOLE_ENABLE
          dprintf("{Dactyl Pivot - Open} Slave sync failed!\n");
          #endif // CONSOLE_ENABLE
        }
        break;
        }

    }  // switch ( i + 1 )


  }  // timer_elapsed(last_tick_transaction) > TRANSACTION_INTERVAL

end_housekeeping:
  housekeeping_task_user();
}
