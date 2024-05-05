#include QMK_KEYBOARD_H

enum alt_keycodes {
    L_BRI = SAFE_RANGE,    //LED Brightness Increase
    L_BRD,                 //LED Brightness Decrease
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
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  DF(3),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(2),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_F13 , MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,        KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,          KC_F10,  KC_F11,  KC_F12,  KC_CAPS, KC_SCRL,
        XXXXXXX, KC_GRV,  LSFT(KC_GRV), XXXXXXX, XXXXXXX, XXXXXXX, LCTL(KC_BSPC), KC_BSPC, KC_HOME, LCTL(KC_LEFT),  KC_HOME, XXXXXXX, KC_PAUS, KC_W,    KC_INSERT,
        XXXXXXX, KC_WBAK, KC_WFWD,      KC_PGUP, KC_PGDN, XXXXXXX, KC_LEFT,       KC_DOWN, KC_UP,   KC_RIGHT,       XXXXXXX, XXXXXXX,          XXXXXXX, KC_NUM_LOCK,
        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,        KC_DEL,  KC_END,  LCTL(KC_RIGHT), KC_END,  XXXXXXX,          KC_VOLU, MO(2),
        XXXXXXX, XXXXXXX, XXXXXXX,                                                  XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX
    ),
    [2] = LAYOUT_65_ansi_blocker(
        XXXXXXX, LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), XXXXXXX,     XXXXXXX, KC_PSCR, RSG(KC_S), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      LSFT(KC_F4), XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F14,  LSA(KC_E),    LSA(KC_F),    RCS(KC_G),    RSG(KC_F12), XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,      RCS(KC_B),    XXXXXXX,      KC_F6,       XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          L_BRI  , XXXXXXX,
        XXXXXXX, XXXXXXX,      XXXXXXX,                                          XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, L_BRD  , XXXXXXX
    ),
    // Mac Layout
    [3] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, DF(0),
        MO(4),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  XXXXXXX,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(5),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_F13 , MO(5),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [4] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,         KC_F2,          KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,          KC_F9,          KC_F10,  KC_F11,  KC_F12,  LSFT(KC_CAPS), KC_SCRL,
        XXXXXXX, KC_GRV,        LSFT(KC_GRV),   XXXXXXX, XXXXXXX, XXXXXXX, LGUI(KC_BSPC), KC_BSPC, LALT(KC_LEFT),  LGUI(KC_LEFT),  KC_HOME, XXXXXXX, KC_PAUS, KC_M,          KC_INSERT,
        XXXXXXX, LALT(KC_LBRC), LALT(KC_RBRC),  KC_PGUP, KC_PGDN, XXXXXXX, KC_LEFT,       KC_DOWN, KC_UP,          KC_RIGHT,       XXXXXXX, XXXXXXX,          XXXXXXX,       KC_NUM_LOCK,
        XXXXXXX, XXXXXXX,       XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_DEL,  LALT(KC_RIGHT), LGUI(KC_RIGHT), KC_END,  XXXXXXX,          KC_VOLU,       MO(5),
        XXXXXXX, XXXXXXX,       XXXXXXX,                                                  XXXXXXX,                                 XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,       XXXXXXX
    ),
    [5] = LAYOUT_65_ansi_blocker(
        XXXXXXX, LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), XXXXXXX,     XXXXXXX, LSA(KC_3), LSA(KC_4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      LSFT(KC_F4), XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F14,  LSA(KC_E),    LSA(KC_F),    RCS(KC_G),    RSG(KC_F12), XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,      RCS(KC_B),    XXXXXXX,      KC_F4,       XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          L_BRI,   XXXXXXX,
        XXXXXXX, XXXXXXX,      XXXXXXX,                                 XXXXXXX,                                         XXXXXXX, XXXXXXX, XXXXXXX, L_BRD,   XXXXXXX
    ),
    /*
    [X] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if ((gcr_desired + LED_GCR_STEP) > LED_GCR_MAX) {
                    gcr_desired = LED_GCR_MAX;
                } else {
                    gcr_desired += LED_GCR_STEP;
                }
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if ((gcr_desired - LED_GCR_STEP) < 0) {
                    gcr_desired = 0;
                } else {
                    gcr_desired -= LED_GCR_STEP;
                }
            }
            return false;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
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
