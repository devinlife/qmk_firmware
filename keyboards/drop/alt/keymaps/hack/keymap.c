#include QMK_KEYBOARD_H

#define LED_GCR_STEP                4           //GCR increment/decrement value
#define LED_GCR_MAX 100                         // Max GCR value (0 - 255) WARNING: Raising this value may overload the LED drivers and USB bus


#define RGBLIGHT_ENABLE
#define LIGHT_TIMEOUT 1000                     // Time in milliseconds before the light turns off

bool light_active  = false;
uint32_t light_timer = 0;

#define SPAM_DELAY 60000 // 1 second between spams
bool spam_active = false;
uint32_t spam_timer = 0;

uint32_t os_custom_code = 0;

enum alt_keycodes {
    MV_WIN = SAFE_RANGE, // CUSTOM: move window machine
    MV_MAC,              // CUSTOM: move mac machine
    MO_WIN,                 // CUSTOM: layer on windows
    MO_MAC,                 // CUSTOM: layer on mac
    CST_DDW,             //CUSTOM: delete a line in Windows
    CST_DDM,             //CUSTOM: delete a line in MacOS
    CHG_LANG,            // CUSTOM: change language
    APP1,              //CUSTOM:
    APP2,              //CUSTOM:
    APP3,              //CUSTOM:
    APP4,              //CUSTOM:
    APP5,              //CUSTOM:
    APP6,              //CUSTOM:
    APP7,              //CUSTOM:
    APP8,              //CUSTOM:
    APP9,              //CUSTOM:
    SPAM,              //CUSTOM: delete a line in MacOS
};

enum os_layers {
    WINDOWS_LAYER = 0,
    MAC_LAYER = 3
};

void enable_light(enum os_layers os_layer);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Windows Layout
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, SPAM,
        MO_WIN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  _______,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,          KC_UP,   _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             CHG_LANG, MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
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
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, SPAM,
        MO_MAC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  _______,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,          KC_UP,   _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             CHG_LANG, MO(5),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [4] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,         KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,          KC_F9,          KC_F10,  KC_F11,  KC_F12,  LSFT(KC_CAPS), KC_SCRL,
        _______, KC_GRV,        LSFT(KC_GRV),   _______, _______, CST_DDM, LGUI(KC_BSPC), KC_BSPC, LALT(KC_LEFT),  LGUI(KC_LEFT),  KC_HOME, _______, KC_PAUS, KC_M,          KC_INSERT,
        _______, LALT(KC_LBRC), LALT(KC_RBRC),  KC_PGUP, KC_PGDN, _______, KC_LEFT,       KC_DOWN, KC_UP,          KC_RIGHT,       MV_WIN,  MV_MAC,           _______,       KC_NUM_LOCK,
        _______, _______,       _______,        _______, _______, _______, _______,       KC_DEL,  LALT(KC_RIGHT), LGUI(KC_RIGHT), KC_END,  _______,          KC_VOLU,       _______,
        _______, _______,       _______,                                                  _______,                                 _______, _______, _______, KC_VOLD,       _______
    ),
    [5] = LAYOUT_65_ansi_blocker(
        _______, APP1,         APP2,             APP3,             APP4,               APP5,    APP6,      APP7,      APP8,    APP9,    _______, _______, _______, _______, _______,
        _______, _______,      _______,          _______,          LSFT(KC_F4),        _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______,
        KC_F14,  LSA(KC_E),    LSA(KC_F),        LCTL(LSFT(KC_G)), LGUI(LSFT(KC_F12)), _______, _______,   _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      LCTL(LSFT(KC_B)), _______,          KC_F4,              _______, _______,   _______,   _______, _______, _______, _______,          _______, _______,
        _______, _______,      _______,                                                _______,                                         _______, _______, _______, _______, _______
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
    layer_move(MAC_LAYER);
    enable_light(MAC_LAYER);
    light_active = true;
    light_timer = timer_read();
}

void set_window_mode(void) {
    layer_move(WINDOWS_LAYER);
    enable_light(WINDOWS_LAYER);
    light_active = true;
    light_timer = timer_read();
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(1); // 기본 단색 모드
    set_mac_mode();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CHG_LANG:
            if (record->event.pressed) {
                if (os_custom_code == OS_LINUX) { // for android
                    register_code(KC_LSFT);
                    tap_code(KC_SPC);
                    unregister_code(KC_LSFT);
                } else {
                    tap_code(KC_F13); //for mac and windows
                }
            }
            return false;
        case MV_WIN:
            if (record->event.pressed) {
                tap_code(KC_F14);
                set_window_mode();
            }
            return false;
        case MV_MAC:
            if (record->event.pressed) {
                tap_code(KC_F15);
                set_mac_mode();
            }
            return false;
         case MO_WIN:
            if (record->event.pressed) {
                layer_on(WINDOWS_LAYER + 1);
                enable_light(WINDOWS_LAYER);
            } else {
                layer_off(WINDOWS_LAYER+1);
                rgblight_disable();  // 라이트 끄기
            }
            return false;
        case MO_MAC:
            if (record->event.pressed) {
                layer_on(MAC_LAYER+1);
                enable_light(MAC_LAYER);
            } else {
                layer_off(MAC_LAYER+1);
                rgblight_disable();  // 라이트 끄기
            }
            return false;

        case CST_DDM:
            if (record->event.pressed) {
                // Alt + Left (이전 동작)
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                unregister_code(KC_LALT);

                // Shift + Alt + Right (다음 동작)
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);

                // Backspace
                tap_code(KC_BSPC);
            }
            return false;
        case CST_DDW:
            if (record->event.pressed) {
                // Home 키 입력
                tap_code(KC_HOME);

                // Shift + End (텍스트 블록 선택)
                register_code(KC_LSFT);
                tap_code(KC_END);
                unregister_code(KC_LSFT);

                // Backspace (선택한 텍스트 삭제)
                tap_code(KC_BSPC);
            }
            return false;
        case APP1:
        case APP2:
        case APP3:
        case APP4:
        case APP5:
        case APP6:
        case APP7:
        case APP8:
        case APP9:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LGUI);
                if (keycode == APP1) {
                    tap_code(KC_1);
                } else if (keycode == APP2) {
                    tap_code(KC_2);
                } else if (keycode == APP3) {
                    tap_code(KC_3);
                } else if (keycode == APP4) {
                    tap_code(KC_4);
                } else if (keycode == APP5) {
                    tap_code(KC_5);
                } else if (keycode == APP6) {
                    tap_code(KC_6);
                } else if (keycode == APP7) {
                    tap_code(KC_7);
                } else if (keycode == APP8) {
                    tap_code(KC_8);
                } else if (keycode == APP9) {
                    tap_code(KC_9);
                }
                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
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

void check_and_send_spam(void){
    // Check if it's been SPAM_DELAY milliseconds since the last spam
    if (timer_elapsed32(spam_timer) > SPAM_DELAY) {
        tap_code(KC_COMMA);           // Send a comma
        spam_timer = timer_read32();  // Reset spam timer
    }
}

void enable_light(enum os_layers os_layer) {
    rgb_matrix_enable();
    if (os_layer == WINDOWS_LAYER) {
        rgb_matrix_sethsv(170, 255, 255);  // set color to blue
    } else if (os_layer == MAC_LAYER) {
        rgb_matrix_sethsv(0, 255, 255); // set color to red
    }
}

void disable_light_if_timeout(void){
  if (timer_elapsed(light_timer) > LIGHT_TIMEOUT) {
    rgblight_disable();  // 라이트 끄기
    light_active = false;
  }
}

void matrix_scan_user(void) {
  if (spam_active) {
    check_and_send_spam();
  }

  if (light_active) {
    disable_light_if_timeout();
  }
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        os_custom_code = OS_UNSURE;
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            os_custom_code = OS_MACOS;
            break;
        case OS_WINDOWS:
            os_custom_code = OS_WINDOWS;
            break;
        case OS_LINUX:
            os_custom_code = OS_LINUX;  //for android
            set_window_mode();
            break;
        case OS_UNSURE:
            os_custom_code = OS_UNSURE;
            break;
    }

    return true;
}
