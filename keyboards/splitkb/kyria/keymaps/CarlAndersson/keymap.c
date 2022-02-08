#include QMK_KEYBOARD_H

#include "oneshot.h"

enum layers {
    BASE = 0,
    SYMBOLS,
    EXTEND,
    NUMLOCK,
    META,
};

enum custom_keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_ALT,
    OS_CTRL,
    OS_CMD,
    OS_HOLD,
};


#define MC_COPY LGUI(KC_C)
#define MC_PSTE LGUI(KC_V)
#define MC_CUT LGUI(KC_X)
#define MC_UNDO LGUI(KC_Z)
#define MC_CMNT LGUI(KC_SLSH)
#define MC_MOUSEWIN LALT(LGUI(LCTL(KC_Z)))
#define MC_KBRDWIN LALT(LGUI(LCTL(KC_X)))

#define SE_ARNG LALT(KC_LBRC)
#define SE_ADIA LALT(KC_QUOT)
#define SE_ODIA LALT(KC_SCLN)

#define LA_EXTEND MO(EXTEND)
#define LA_SYMBOLS MO(SYMBOLS)
#define LA_NMLCK TG(NUMLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  Q   | W    | F    | P    | G    |                              |   J  |  L   |  U   |  Y   | -  _ |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  A   | R    | S    | T    | D    |                              |   H  |  N   |  E   |  I   |  O   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  Z   | X    | C    | V    | B    |      |      |  |      |      |   K  |  M   | ,  ; | .  : | '  / |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Ext  | Shft | Bcsp |  | Entr | Spce | Sym  |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [BASE] = LAYOUT(
      _______, KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, _______,
      _______, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
      _______, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,      _______, _______,      _______, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, _______,
                            _______, _______,  LA_EXTEND, KC_LSFT, KC_BSPC,     KC_ENTER, KC_SPC,  LA_SYMBOLS,  _______, _______
    ),
/*
 * Symbols layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   ?  | 7    | 8    |  9   |      |                              |  J   |  *   |  /   |  +   |  -   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |   0  | 4    | 5    |  6   |      |                              |  <   |  (   |  [   |  {   |  =   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   e  | 1    | 2    |  3   |      |      |      |  |      |      |  >   |  )   |  ]   |  }   | "    |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Sym2 | Spce |      |  |      | Spce | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [SYMBOLS] = LAYOUT(
      _______, KC_QUES, KC_7,    KC_8,    KC_9,    KC_NO,                                                KC_J,    KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______,
      _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_NO,                                                KC_LABK, KC_LPRN, KC_LBRC, KC_LCBR, KC_EQL,  _______,
      _______, KC_E,    KC_1,    KC_2,    KC_3,    KC_NO,    _______, _______,         _______, _______, KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_DQUO,  _______,
                                 _______, _______, _______,  KC_SPC,  _______,         _______, KC_SPC,  _______, _______, _______
    ),
/*
 * Extend layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      | Esc  | Spce | Entr | Bcsp |NumLck|                              |      | Del  |  ↑   |   å  |  ä   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shft | Ctrl | Alt  | Cmd  |MseWin|                              |KeyWin|   ←  |OsHold|  →   |  ö   |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Pste |Coment|      |      |  |      |      |      | Tab  |  ↓   |      |  \   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      | Spce | Sym2 |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [EXTEND] = LAYOUT(
      _______, KC_ESC,  KC_SPC,  KC_ENT,  KC_BSPC, LA_NMLCK,                                        KC_NO,   KC_DEL,  KC_UP,   SE_ARNG, SE_ADIA, _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  MC_MOUSEWIN,                                  MC_KBRDWIN, KC_LEFT, OS_HOLD, KC_RGHT, SE_ODIA, _______,
      _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, MC_CMNT, _______, _______,     _______, _______, KC_NO,   KC_TAB,  KC_DOWN, KC_NO,   KC_BSLS, _______,
                                 _______, _______, _______, _______, _______,     _______, KC_SPC,  _______,  _______, _______
    ),

/*
 * Meta layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  !   |      |      |  %   |      |                              |      |      | PgUp |      |  ~   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  @   | $    |  &   |  ^   |  |   |                              |      | Home |      |  End |      |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |      |      |  #   |      |      |      |  |      |      |      |Dedet |PgDown| Indnt|  `   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      |      | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [META] = LAYOUT(
      _______, KC_EXLM, KC_NO,   KC_NO,   KC_PERC, KC_NO,                                           KC_NO,   KC_NO,   KC_PGUP, KC_NO,   KC_TILD, _______,
      _______, KC_AT,   KC_DLR,  KC_AMPR, KC_CIRC, KC_PIPE,                                         KC_NO,   KC_HOME, KC_NO,   KC_END,  KC_NO,   _______,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_HASH, _______, _______, _______,     _______, _______, _______,G(KC_LBRC),KC_PGDN,G(KC_RBRC),KC_GRV,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),


/*
 * NumLock layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      | Exit |  7   |  8   |  9   |      |                              |  F1  |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  0   |  4   |  5   |  6   |      |                              |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  e   |  1   |  2   |  3   |      |      |      |  |      |      |  F11 |  F12 |  F13 |  F14 |  F15 |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |  -   |  +   |      |  |      |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

   [NUMLOCK] = LAYOUT(
      _______, LA_NMLCK,KC_7,    KC_8,    KC_9,    _______,                                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
      _______, KC_0,    KC_4,    KC_5,    KC_6,    _______,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, KC_E,    KC_1,    KC_2,    KC_3,    _______, _______, _______,     _______, _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______,
                                 _______, _______, KC_MINS, KC_PLUS, _______,     _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-----------------------------------------.                              ,-----------------------------------------.
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
//  * |      |      |      |      |      |      |                              |      |      |      |      |      |      |
//  * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
//  * |      |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |      |
//  * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
//  *                      |      |      |      |      |      |  |      |      |      |      |      |
//  *                      `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                         _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
//     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, SYMBOLS, EXTEND, META);
    return state;
}

const key_override_t shift_comma_2_semicolon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t shift_dot_2_colon_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t shift_quote_2_slash_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_SLSH);

const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comma_2_semicolon_override,
    &shift_dot_2_colon_override,
    &shift_quote_2_slash_override,
    NULL // Null terminate the array of overrides!
};


bool oneshot_hold = false;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_EXTEND:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {

    switch (keycode) {
    case LA_SYMBOLS:
    case LA_EXTEND:
    case OS_SHFT:
    case OS_ALT:
    case OS_CTRL:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case OS_HOLD:
        oneshot_hold = !oneshot_hold;
        break;
    }

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT, OS_HOLD,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL, OS_HOLD,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT, OS_HOLD,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD, OS_HOLD,
        keycode, record
    );

    return true;
}
