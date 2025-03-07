#include QMK_KEYBOARD_H

#define LED_GCR_STEP                4           //GCR increment/decrement value
#define LED_GCR_MAX 165                         // Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus


// #define RGB_MATRIX_ENABLE
#define RGBLIGHT_ENABLE
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255  // 최대 밝기 설정
#define LIGHT_TIMEOUT 3000                     // Time in milliseconds before the light turns off

uint32_t light_timer = 0;


#define SPAM_DELAY 2000  // 500 milliseconds between spams
bool spam_active = false;
uint32_t spam_timer = 0;


enum alt_keycodes {
    L_BRI = SAFE_RANGE,    //LED Brightness Increase
    L_BRD,                 //LED Brightness Decrease
    MV_WIN,              //CUSTOM: move window machine
    MV_MAC,              //CUSTOM: move mac machine
    CST_DDW,              //CUSTOM: delete a line in Windows
    CST_DDM,              //CUSTOM: delete a line in MacOS
    SPAM,              //CUSTOM: delete a line in MacOS
    U_T_AUTO,              // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              // USB Toggle Automatic GCR control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    MD_BOOT,               // Restart into bootloader after hold timeout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Windows Layout
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, SPAM,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  _______,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_F13 , MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,        KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,          KC_F10,  KC_F11,  KC_F12,  KC_CAPS, KC_SCRL,
        _______, KC_GRV,  LSFT(KC_GRV), _______, _______, CST_DDW, LCTL(KC_BSPC), KC_BSPC, KC_HOME, LCTL(KC_LEFT),  KC_HOME, _______, KC_PAUS, KC_W,    KC_INSERT,
        _______, KC_WBAK, KC_WFWD,      KC_PGUP, KC_PGDN, _______, KC_LEFT,       KC_DOWN, KC_UP,   KC_RIGHT,       MV_WIN,  MV_MAC,           _______, KC_NUM_LOCK,
        _______, _______, _______,      _______, _______, _______, KC_APP,        KC_DEL,  KC_END,  LCTL(KC_RIGHT), KC_END,  _______,          KC_VOLU, _______,
        _______, _______, _______,                                                  _______,                        _______, _______, _______, KC_VOLD, _______
    ),
    [2] = LAYOUT_65_ansi_blocker(
        _______, LCTL(KC_F13), LCTL(KC_F14),     LCTL(KC_F15),     _______,            _______, KC_PSCR, RSG(KC_S), _______, _______, _______, _______, _______, _______, _______,
        _______, _______,      _______,          _______,          LSFT(KC_F4),        _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
        KC_F14,  LSA(KC_E),    LSA(KC_F),        LCTL(LSFT(KC_G)), LGUI(LSFT(KC_F12)), _______, _______, _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      LCTL(LSFT(KC_B)), _______,          KC_F4,              _______, _______, _______,   _______, _______, _______, _______,          L_BRI,   _______,
        _______, _______,      _______,                                                _______,                              _______, _______, _______, L_BRD,   _______
    ),
    // Mac Layout
    [3] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, SPAM,
        MO(4),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  _______,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_F13 , MO(5),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [4] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,         KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,          KC_F9,          KC_F10,  KC_F11,  KC_F12,  LSFT(KC_CAPS), KC_SCRL,
        _______, KC_GRV,        LSFT(KC_GRV),   _______, _______, CST_DDM, LGUI(KC_BSPC), KC_BSPC, LALT(KC_LEFT),  LGUI(KC_LEFT),  KC_HOME, _______, KC_PAUS, KC_M,          KC_INSERT,
        _______, LALT(KC_LBRC), LALT(KC_RBRC),  KC_PGUP, KC_PGDN, _______, KC_LEFT,       KC_DOWN, KC_UP,          KC_RIGHT,       MV_WIN,  MV_MAC,           _______,       KC_NUM_LOCK,
        _______, _______,       _______,        _______, _______, _______, _______,       KC_DEL,  LALT(KC_RIGHT), LGUI(KC_RIGHT), KC_END,  _______,          KC_VOLU,       _______,
        _______, _______,       _______,                                                  _______,                                 _______, _______, _______, KC_VOLD,       _______
    ),
    [5] = LAYOUT_65_ansi_blocker(
        _______, LCTL(KC_F13), LCTL(KC_F14),     LCTL(KC_F15),     _______,            _______, LSA(KC_3), LSA(KC_4), _______, _______, _______, _______, _______, _______, _______,
        _______, _______,      _______,          _______,          LSFT(KC_F4),        _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______,
        KC_F14,  LSA(KC_E),    LSA(KC_F),        LCTL(LSFT(KC_G)), LGUI(LSFT(KC_F12)), _______, _______,   _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      LCTL(LSFT(KC_B)), _______,          KC_F4,              _______, _______,   _______,   _______, _______, _______, _______,          L_BRI,   _______,
        _______, _______,      _______,                                                _______,                                         _______, _______, _______, L_BRD,   _______
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

void keyboard_pre_init_user(void) {
    // Call the pre init code.
    // Set the init layer to 3
    // layer_move(3);
}

void set_mac_mode(void) {
    layer_move(3);
    rgb_matrix_enable();
    rgb_matrix_sethsv(0, 255, 255);
    light_timer = timer_read();  // 현재 시간 저장
}

void set_window_mode(void) {
    layer_move(3);
    rgb_matrix_enable();
    rgb_matrix_sethsv(170, 255, 255);
    light_timer = timer_read();  // 현재 시간 저장
}


void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode_noeeprom(1); // 기본 단색 모드
    set_mac_mode();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case MV_WIN:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F14));
                set_window_mode();
            }
            return false;
        case MV_MAC:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_F15));
                set_mac_mode();
            }
            return false;
        case CST_DDM:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT) SS_UP(X_LSFT));
                SEND_STRING(SS_TAP(X_BSPC));
            }
            return false;
        case CST_DDW:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME));
                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
                SEND_STRING(SS_TAP(X_BSPC));
            }
            return false;
        case L_BRI:
            if (record->event.pressed) {
                // if ((gcr_desired + LED_GCR_STEP) > LED_GCR_MAX) {
                //     gcr_desired = LED_GCR_MAX;
                // } else {
                //     gcr_desired += LED_GCR_STEP;
                // }
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                // if ((gcr_desired - LED_GCR_STEP) < 0) {
                //     gcr_desired = 0;
                // } else {
                //     gcr_desired -= LED_GCR_STEP;
                // }
            }
            return false;
         case SPAM:  // When you press custom SPAM keycode
            if (record->event.pressed) {
                spam_active = !spam_active; // Toggle spamming
                if(spam_active) {
                    spam_timer = timer_read32(); // Reset spam timer
                    SEND_STRING("spam: start");
                } else {
                    SEND_STRING("spam: end");
                }
            }
            return false;
        case U_T_AUTO:
            // if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
            //     TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            // }
            return false;
        case U_T_AGCR:
            // if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
            //     TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            // }
            return false;
        case DBG_TOG:
            // if (record->event.pressed) {
            //     TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            // }
            return false;
        case DBG_MTRX:
            // if (record->event.pressed) {
            //     TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            // }
            return false;
        case DBG_KBD:
            // if (record->event.pressed) {
            //     TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            // }
            return false;
        case DBG_MOU:
            // if (record->event.pressed) {
            //     TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            // }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void matrix_scan_user(void){
  if (spam_active) {
    // Check if it's been SPAM_DELAY milliseconds since the last spam
    if (timer_elapsed32(spam_timer) > SPAM_DELAY) {
      tap_code(KC_COMMA);           // Send a comma
      tap_code(KC_COMMA);           // Send a comma
      tap_code(KC_BACKSPACE);           // Send a comma
      tap_code(KC_BACKSPACE);           // Send a comma
      spam_timer = timer_read32();  // Reset spam timer
    }
  }

  if (timer_elapsed(light_timer) > LIGHT_TIMEOUT) {
    rgblight_disable();  // 라이트 끄기
  }
}

