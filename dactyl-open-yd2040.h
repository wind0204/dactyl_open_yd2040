#ifndef DACTYL_OPEN_YD2040_H
#define DACTYL_OPEN_YD2040_H


#include <stdint.h>




#define QWERTY_LAYER 0
#define SECOND_LAYER 1
#define THIRD_LAYER  2
#define NR_LAYERS ( 2 + 1 )



enum the_error_code {
  err_not_my_business = 1,
  err_unknown,
};
enum the_event_code {
  tec_nkro_state_change = 1,
  tec_2nd_layer,
  //tec_handshake,
};

struct short_cry_m2s {
  uint16_t the_event_code;
  uint16_t the_value;
};
struct short_cry_s2m {
  uint8_t err_no;
};




#endif
