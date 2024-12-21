#pragma once




/* USB Device descriptor parameter */
#define VENDOR_ID       0x15F4  // This ID is registered for 'Computer & Entertainment, Inc.'
#define PRODUCT_ID      0xFFFE  // Can I use `0xFFFF - 1`?
#define DEVICE_VER      0x0001  // Is this 0.0.1 ? or just 1?


/* The key matrix */
#define NR_ROWS 6
#define NR_COLUMNS 7
//#define MATRIX_COLS NR_COLUMNS
//#define MATRIX_ROWS ( NR_ROWS * 2 )
//#define MATRIX_COL_PINS { GP10, GP7, GP6, GP5, GP4, GP3, GP2 }
//#define MATRIX_ROW_PINS { GP20, GP19, GP18, GP17, GP16, GP15 }

#define DIODE_DIRECTION COL2ROW


/* Handedness */
#define SPLIT_HAND_MATRIX_GRID GP17, GP2  // I wrote the row pin first because DIODE_DIRECTION is COL2ROW,
                                          // and the doc says output pin first, input pin second;
                                          // They mean that logical output pin for reading at the first element of the array,
                                          // and logical input pin for changing the flow of electric current at the second.
                                          // and they internally change the flow of electric current at the ROW of COL2ROW matrix
                                          // when they peek at an intersection for SPLIT_HAND_MATRIX_GRID
                                          // reading the change of voltage at the COL.
#define MATRIX_MASKED  // const matrix_row_t matrix_mask[] is defined in rev1.c

//#define EE_HANDS
// When EE_HANDS is defined: add '-bl uf2-split-(left)|(right)' to the command sequence for flashing.
//  qmk flash -kb handwired/wind0204/dactyl_open_yd2040 -km default -bl uf2-split-left
//  qmk flash -kb handwired/wind0204/dactyl_open_yd2040 -km default -bl uf2-split-right


/* Synchronize */
#define SPLIT_LED_STATE_ENABLE  // The firmware on slave does call layer_state_set_kb without this.
#undef SPLIT_LED_STATE_ENABLE  // So it's not useful my keyboard.

#define SPLIT_LAYER_STATE_ENABLE  // This won't make slave respond to led state changes and write high for the LED accordingly.
#undef SPLIT_LAYER_STATE_ENABLE  // So it's not useful my keyboard.


/* UART */
// Use UART0 for communication between the halves
#define SERIAL_USART_DRIVER SIOD0
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0    // USART TX pin
#define SERIAL_USART_RX_PIN GP1    // USART RX pin
//#define UART_DRIVER SIOD0
//#define UART_TX_PIN GP0
//#define UART_RX_PIN GP1


/* USB */
// Determine who is master and who is slave using a GPIO pin
// I've connected a voltage divider circuit to GP22, V+(Vout) and GND
//#define USB_VBUS_PIN GP22
// XXX My voltage divider circuit experiment somehow failed!
// Use the default behavior for now.. (SPLIT_USB_DETECT)
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 2048


/* TRANSACTIONS */
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_SHORT_CRY



/* Rotary Encoders */
// I had to remove these two lines below to avoid conflicts with auto-generated empty ENCODERS_PAD_A definition.
// Trying one more time
//#define ENCODERS_PAD_A { GP14 }
//#define ENCODERS_PAD_B { GP13 }

#undef ENCODER_DIRECTION_FLIP

// This might be too quick.
#define ENCODER_RESOLUTION 4



// CRC8 on USB interfacing
#define CRC8_OPTIMIZE_SPEED
//#define CRC8_USE_TABLE  // This dirsrupts the RPC calls on YD2040


/* Let me try entering the bootloader by double tapping something */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25


/* YD-RP2040-2022 V1.1 has one WS2812, So I get 2 RGB LEDs in total from both split halves. */
#define WS2812_DI_PIN GP23

// If the color is wrong I have to try other byte order for the XL-5050RGBC-WS2812B
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
//#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_BGR

#define RGBLIGHT_LED_COUNT 2
//#define RGBLED_SPLIT {1, 1}  // Reason for commenting out: This applies RGBLIGHT_SPLIT

//#define RGBLIGHT_SPLIT  // Mirror the RGBs? No thanks.
#define RGBLIGHT_LIMIT_VAL 254
#define RGBLIGHT_DEFAULT_VAL ( 254 / 2 )

// Don't turn off lights when host goes to sleep.
#undef RGBLIGHT_SLEEP

#define RGBLIGHT_HUE_STEP 32
#define RGBLIGHT_SAT_STEP 16
#define RGBLIGHT_VAL_STEP 16

// Haven't tried #0, #1, #2 but #3 looks fine.
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING + 3

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_BREATHE_MAX ( RGBLIGHT_DEFAULT_VAL / 8 * 5 )
#define RGBLIGHT_EFFECT_BREATHE_CENTER 2.7  // Valid values are 1.0 to 2.7
// RGBLED_BREATHING_INTERVALS is defined in keymap.c


#define TAPPING_TERM 175
