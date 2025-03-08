#include QMK_KEYBOARD_H

#define LED_GCR_STEP                4           //GCR increment/decrement value
#define LED_GCR_MAX 165                         // Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus


// #define RGB_MATRIX_ENABLE
#define RGBLIGHT_ENABLE
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255  // 최대 밝기 설정
#define LIGHT_TIMEOUT 3000                     // Time in milliseconds before the light turns off

uint32_t light_timer = 0;


#define SPAM_DELAY 60000 // 1 second between spams
bool spam_active = false;
uint32_t spam_timer = 0;


enum alt_keycodes {
    MV_WIN = SAFE_RANGE,   //CUSTOM: move window machine
    MV_MAC,              //CUSTOM: move mac machine
    CST_DDW,              //CUSTOM: delete a line in Windows
    CST_DDM,              //CUSTOM: delete a line in MacOS
    SPAM,              //CUSTOM: delete a line in MacOS
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
        _______, _______,      LCTL(LSFT(KC_B)), _______,          KC_F4,              _______, _______, _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      _______,                                                _______,                              _______, _______, _______, _______, _______
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
        _______, _______,      LCTL(LSFT(KC_B)), _______,          KC_F4,              _______, _______,   _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      _______,                                                _______,                                         _______, _______, _______, _______,   _______
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

void set_mac_mode(void) {
    layer_move(3);
    rgb_matrix_enable();
    rgb_matrix_sethsv(0, 255, 255);  // set color to red
    light_timer = timer_read();
}

void set_window_mode(void) {
    layer_move(3);
    rgb_matrix_enable();
    rgb_matrix_sethsv(170, 255, 255);  // set color to blue
    light_timer = timer_read();
}


void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode_noeeprom(1); // 기본 단색 모드
    set_mac_mode();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
        default:
            return true; //Process all other keycodes normally
    }
}

void check_spam_active(void){
  if (spam_active) {
    // Check if it's been SPAM_DELAY milliseconds since the last spam
    if (timer_elapsed32(spam_timer) > SPAM_DELAY) {
      tap_code(KC_COMMA);           // Send a comma
      spam_timer = timer_read32();  // Reset spam timer
    }
  }

  if (timer_elapsed(light_timer) > LIGHT_TIMEOUT) {
    rgblight_disable();  // 라이트 끄기
  }
}

void matrix_scan_user(void) {
  check_spam_active();

  if (timer_elapsed(light_timer) > LIGHT_TIMEOUT) {
    rgblight_disable();  // 라이트 끄기
  }
}

