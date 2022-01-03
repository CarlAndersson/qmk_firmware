#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

enum layers {
    BSE = 0,
    SYM,
    NAV,
    NUM,
    MSE,
    FNC,
    TLE,
};

enum custom_keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_ALT,
    OS_CTRL,
    OS_CMD,
    OS_HOLD,
    SW_APP,  // Switch to next app         (cmd-tab)
};


// #define OS_SHFT OSM(MOD_LSFT)
// #define OS_ALT OSM(MOD_LALT)
// #define OS_CTRL OSM(MOD_LCTL)
// #define OS_CMD OSM(MOD_LGUI)
// #define OS_SHFT OSM(MOD_RSFT)
// #define OS_ALT OSM(MOD_RALT)
// #define OS_CTRL OSM(MOD_RCTL)
// #define OS_CMD OSM(MOD_RGUI)

#define SPC_LFT LALT(LCTL(KC_LEFT))
#define SPC_RGT LALT(LCTL(KC_RIGHT))
// #define SW_WIN LCMD(KC_TAB)
#define SW_TAB LCTL(KC_TAB)
#define MC_LNCH LGUI(KC_SPC)
#define MC_NOTE LGUI(LALT(KC_SPC))
#define MC_TERM LCTL(LALT(KC_SPC))
#define MC_COPY LGUI(KC_C)
#define MC_PSTE LGUI(KC_V)
#define MC_CUT LGUI(KC_X)
#define MC_UNDO LGUI(KC_Z)

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)
// #define LA_MSE MO(MSE)
#define LA_TLE MO(TLE)
#define LA_FNC MO(FNC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*          
 * Base Layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  | ?  ! |OSHold|
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |BspDel|   A  |   R  |   S  |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  | Entr |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * | Tab  |   Z  |   X  |   C  |   V  |   B  | Lnch | Note |  | Term |      |   N  |   M  | ,  ; | .  : | '  " |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Nav  | Shft | Fnc  |  | Tile | Spce | Syms |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [BSE] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                             KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUES, OS_HOLD,
      KC_BSPC, KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
      KC_TAB,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    MC_LNCH, MC_NOTE,      MC_TERM, _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, _______,
                            _______, _______,  LA_NAV,  KC_LSFT, LA_FNC,       LA_TLE,  KC_SPC,  LA_SYM,  _______, _______
    ),
/*
 * Symbols layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |   <  |   {  |   [  |   (  |  $   |                              |      |  )   |  ]   |  }   |  >   |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |   -  |   +  |   =  |   _  |  @   |                              |   ~  | Cmd  | Alt  | Ctrl | Shft |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |   ^  |   &  |   *  |   /  |  %   |      |      |  |      |      |      |  \   |  |   |  #   |  `   |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | Num  |      |      |  |      |      | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */
    [SYM] = LAYOUT(
      _______, KC_LT,   KC_LCBR, KC_LBRC, KC_LPRN, KC_DLR,                                              _______, KC_RPRN, KC_RBRC, KC_RCBR, KC_GT,   _______,
      _______, KC_MINS, KC_PLUS, KC_EQL,  KC_UNDS, KC_AT,                                               KC_TILD, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, _______,
      _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_SLSH, KC_PERC, _______, _______,         _______, _______, _______, KC_BSLS, KC_PIPE, KC_HASH, KC_GRV,  _______,
                                 _______, _______, LA_NUM,  _______, _______,         _______, _______, _______, _______, _______
    ),
/*
 * Navigation layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |      | Home |  ↑   | End  | PgUp |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shft | Ctrl | Alt  | Cmd  |      |                              |      |   ←  | NoOp |  →   | PgDn |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Pste |      |      |      |  |      |      |      | Spc ←|  ↓   | Spc →|Sw Win|      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      |      | Num  |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                         _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
      _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  _______,                                         _______, KC_LEFT, KC_NO,   KC_RGHT, KC_PGDN, _______,
      _______, MC_UNDO, MC_CUT,  MC_COPY, MC_PSTE, _______, _______, _______,     _______, _______, _______, SPC_LFT, KC_DOWN, SPC_RGT, SW_APP,  _______,
                                 _______, _______, _______, _______, _______,     _______, _______, LA_NUM,  _______, _______
    ),

/*
 * Numbers layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      |      |      |      |      |                              |   j  |      |      |      |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |  -   |  e   |  +   |      |      |      |  |      |      |      |      |   ,  |   .  |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      | ---- |      |      |  |      |      | ---- |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    [NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                         KC_J,    _______, _______, _______, _______, _______,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MINS, KC_E,    KC_PLUS, _______, _______, _______,     _______, _______, _______, _______, KC_COMM, KC_DOT,  _______, _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),


/*
 * Mouse layer
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |      | Mb 3 | Mb 2 | Mb 1 |      |                              |      |Scr ← |  ↑   |Scr → |Scr ↑ |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      | Shft | Ctrl | Alt  | Cmd  |      |                              |      |   ←  | Mb 1 |  →   |Scr ↓ |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |      |Spd 0 |Spd 1 |Spd 2 |      |      |      |  |      |      |      |      |  ↓   |      |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  | ---- |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */

    // [MSE] = LAYOUT(
    //   _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, _______,                                         _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, _______,
    //   _______, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  _______,                                         _______, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_D, _______,
    //   _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______,     _______, _______, _______, _______, KC_MS_D, _______, _______, _______,
    //                              _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    // ),

/*
 * Fn and media keys
 *
 * ,-----------------------------------------.                              ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                              |      | Prev | Puse | Next |      |      |
 * |------+------+------+------+------+------|                              |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |                              |      |VolDwn| Mute |VolUp |      |      |
 * |------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+------|
 * |      |  F11 |  F12 |  F13 |  F14 |  F15 |      |      |  |      |      |      |      |      |      |      |      |
 * `--------------------+------+------+------+------+------|  |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |  | ---- |      |      |      |      |
 *                      `----------------------------------'  `----------------------------------'
 */ 
    [FNC] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                           _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                                          _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
      _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    ),
 /*
 * Window tiler
 *
 * ,-------------------------------------------------------------------------------------------.                              ,---------------------------------------------------------------------------------------------.
 * |      |                |Upper left quart|  Upper half    |Upper righ quart|                |                              |                |   Prev Space   |  Next Space    |                |                |        |
 * |------+----------------+----------------+----------------+----------------+----------------|                              |----------------+----------------+----------------+----------------+----------------+--------|
 * |      |  Prev monitor  | Left half      |   Maximize     |  Right half    |  Next monitor  |                              |                |   Prev App     |  Next App      |  Prev Win      |  Next Win      |        |
 * |------+----------------+----------------+----------------+----------------+----------------+-------------.  ,-------------+----------------+----------------+----------------+----------------+----------------+--------|
 * |      |                |Lower left quart|   Lower half   |Lower righ quart|                |      |      |  |      |      |                |                |                |                |                |        |
 * `------+----------------+----------------+----------------+----------------+----------------+------+------|  |------+------+----------------+----------------------------------------------------------------------------'
 *                                          |                |                |                |      | ---- |  |      |      |                |                |                |
 *                                          `----------------------------------------------------------------'  `----------------------------------------------------------------'
 */
    [TLE] = LAYOUT(
      _______, _______,      LSFT(LALT(KC_F18)), LSFT(LCTL(KC_F18)), LSFT(LCMD(KC_F18)), _______,                                              _______,       _______,           _______,            _______,           _______,      _______,
      _______, LSFT(KC_F18), LALT(KC_F18),       KC_F18,             LCTL(KC_F18),       LCMD(KC_F18),                                         _______,       _______,           _______,            _______,           _______,      _______,
      _______, _______,      LCMD(LALT(KC_F18)), LCMD(LCTL(KC_F18)), LCTL(LALT(KC_F18)), _______,      _______, _______,     _______, _______, _______,       _______,           _______,            _______,           _______,      _______,
                                                 _______,            _______,            _______,      _______, _______,     _______, _______, _______, _______, _______
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

// layer_state_t layer_state_set_user(layer_state_t state) {
//     state = update_tri_layer_state(state, SYM, NAV, FNC);
//     state = update_tri_layer_state(state, NUM, MSE, TLE);
//     return state;
// }


const key_override_t shift_comma_2_semicolon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t shift_dot_2_colon_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t shift_question_2_exclamation_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
const key_override_t shift_backspace_2_del = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t **key_overrides = (const key_override_t *[]){
    &shift_comma_2_semicolon_override,
    &shift_dot_2_colon_override,
    &shift_question_2_exclamation_override,
    &shift_backspace_2_del,
    NULL // Null terminate the array of overrides!
};


bool oneshot_hold = false;

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    // case LA_NUM:
    // case LA_MSE:
        return true;
    // case OS_HOLD:
        // return locked;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    // if (locked) {
    //     return true;
    // }

    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case LA_NUM:
    // case LA_MSE:
    case KC_LSFT:
    case OS_SHFT:
    case OS_ALT:
    case OS_CTRL:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

// bool sw_win_active = false;
bool sw_app_active = false;

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

    update_swapper(
        &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
        keycode, record
    );

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
