/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"

// レイヤー構成（デフォルト含め5レイヤー）
enum layer_number {
    _BASE   = 0,
    _AML    = 1,  // オートマウスレイヤー
    _SCROLL = 2,  // スクロールレイヤー（トラックボール・LED設定キーも配置）
    _LOWER  = 3,
    _RAISE  = 4,
};

#define LW_MHEN LT(_LOWER, KC_INT5)  // lower
#define RS_HENK LT(_RAISE, KC_INT4)  // raise
#define DEL_ALT ALT_T(KC_DEL)
#define MO_SCRL MO(_SCROLL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
                        KC_LGUI, DEL_ALT, LW_MHEN,  KC_SPC,  MS_BTN1,                       MS_BTN2,  KC_ENT, RS_HENK, KC_BSPC,  KC_ESC,
                                                             KC_PGUP, MS_BTN3, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  // AML: ボールを動かすと自動で有効。J/K/L=クリック、H=押している間スクロール
  // 未定義(_______)の位置はデフォルトレイヤーのキーとして入力されAMLは即解除（A S D F Gと左親指は維持）
  [_AML] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                       MO_SCRL, MS_BTN1, MS_BTN3, MS_BTN2, _______, _______,
      _______, _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______,
                                                             _______, _______, _______, _______, _______, _______
    ),
  // スクロール: このレイヤーが有効な間はボールでスクロール
  [_SCROLL] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UG_TOGG,                                       SCRL_TO,  CPI_SW, SCRL_SW, ROT_L15, ROT_R15, XXXXXXX,
      XXXXXXX, XXXXXXX, UG_VALU, UG_SATU, UG_HUEU, UG_NEXT,                                       SCRL_MO, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, UG_VALD, UG_SATD, UG_HUED, UG_PREV,                                       SCRL_IN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______,
                                                             _______, _______, _______, _______, _______, _______
    ),
  [_LOWER] = LAYOUT(
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                       KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_COLN, KC_DQUO,
      KC_LSFT,  KC_GRV, KC_TILD, KC_NUBS, KC_PIPE, XXXXXXX,                                        KC_EQL, KC_PLUS, KC_LABK, KC_RABK, KC_QUES, KC_UNDS,
                        KC_LGUI, DEL_ALT, _______,  KC_SPC, MS_BTN4,                     MS_BTN5,  KC_ENT, MO_SCRL, KC_BSPC,  KC_ESC,
                                                             KC_PGUP, MS_BTN3, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX
    ),
  [_RAISE] = LAYOUT(
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
      KC_LCTL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_APP,   KC_UP, S(KC_INT1), KC_UNDS, KC_DQUO, KC_COLN,
      KC_LSFT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                                       KC_LEFT, KC_DOWN, KC_RGHT,  KC_DOT, KC_SLSH, KC_MINS,
                        KC_LGUI, DEL_ALT, MO_SCRL,  KC_SPC, MS_BTN4,                     MS_BTN5,  KC_ENT, _______, KC_BSPC,  KC_ESC,
                                                             KC_PGUP, MS_BTN3, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_AML]    = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_SCROLL] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_RAISE]  = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif

// Chordal Hold の手の割り当て ('L': 左手, 'R': 右手, '*': 左右どちらとも組み合わせ可)
// 親指キーと下段のキーは '*'
#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
              '*', '*', '*', '*', '*',      '*', '*', '*', '*', '*',
                             '*', '*', '*', '*', '*', '*'
);
#endif

// ===== オートマウスレイヤー（AML） =====
// AML中に押してもAMLを解除しないキーポジション {row, col}（デフォルトレイヤーでの位置）
//   {1,1}〜{1,5}: A S D F G
//   {3,0} {3,1} {3,2} {3,3} {3,5}: 左親指キー（LGUI, DEL_ALT, LW_MHEN, SPC, MS_BTN1）
#ifndef AML_KEEP_POSITIONS
#    define AML_KEEP_POSITIONS { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 5} }
#endif
// マウスボタンを押してからAMLを解除するまでの時間(ms)
#ifndef AML_CLICK_EXIT_TIME
#    define AML_CLICK_EXIT_TIME 250
#endif

static const uint8_t aml_keep_positions[][2] = AML_KEEP_POSITIONS;
#define AML_KEEP_POSITIONS_SIZE (sizeof(aml_keep_positions) / sizeof(aml_keep_positions[0]))

static matrix_row_t aml_kept_keys[MATRIX_ROWS];  // AML維持キーとして押下中のキー
static bool         aml_click_exit_pending = false;
static uint16_t     aml_click_exit_timer   = 0;
static uint8_t      aml_buttons_held       = 0;

static bool is_aml_keep_position(keypos_t key) {
    for (uint8_t i = 0; i < AML_KEEP_POSITIONS_SIZE; i++) {
        if (aml_keep_positions[i][0] == key.row && aml_keep_positions[i][1] == key.col) return true;
    }
    return false;
}

// AMLが自動で有効になっている状態か（TG/TOでトグルされている場合は除く）
static bool is_aml_layer_active(void) {
    return get_auto_mouse_enable() && layer_state_is(get_auto_mouse_layer()) && !get_auto_mouse_toggle();
}

// AMLを解除しない「マウス系」のキーコード
static bool is_aml_mouse_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_LCTL:
        case KC_LSFT:
        case MO_SCRL:
        case SCRL_MO:
            return true;
        default:
            return IS_MOUSE_KEYCODE(keycode);
    }
}

static bool is_matrix_key(keyrecord_t *record) {
    return IS_KEYEVENT(record->event) && record->event.key.row < MATRIX_ROWS && record->event.key.col < MATRIX_COLS;
}

void keyboard_post_init_user(void) {
    set_auto_mouse_enable(true);
}

// 維持ポジション・マウス系以外のキーが押されたら即AML解除。
// キーコード確定より前にレイヤーを落とすので、押したキーはデフォルトレイヤー側のキーとして入力される。
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && is_matrix_key(record) && is_aml_layer_active() &&
        !is_aml_keep_position(record->event.key) && !is_aml_mouse_keycode(keycode)) {
        auto_mouse_reset_trigger(true);
    }
    return true;
}

// AMLを維持するキー（マウス系キーと、AML中に押された維持ポジション）
bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    if (is_matrix_key(record)) {
        keypos_t     key = record->event.key;
        matrix_row_t bit = (matrix_row_t)1 << key.col;
        if (record->event.pressed) {
            if (is_aml_layer_active() && is_aml_keep_position(key)) {
                aml_kept_keys[key.row] |= bit;
                return true;
            }
        } else if (aml_kept_keys[key.row] & bit) {
            // 押した時に維持キーとして数えたものは、離した時も同じ扱いにする
            aml_kept_keys[key.row] &= ~bit;
            return true;
        }
    }
    return is_aml_mouse_keycode(keycode);
}

// マウスボタンを押してからAML_CLICK_EXIT_TIME経過でAML解除（ボタンを押し続けている間は待つ）
void housekeeping_task_user(void) {
    if (aml_click_exit_pending && aml_buttons_held == 0 && timer_elapsed(aml_click_exit_timer) > AML_CLICK_EXIT_TIME) {
        aml_click_exit_pending = false;
        if (is_aml_layer_active()) {
            // レイヤーを落として状態をリセット。再発動の待ち(delay)は解除し、
            // クリック後にボールを動かせばすぐAMLへ戻れるようにする。
            auto_mouse_reset_trigger(true);
            auto_mouse_keyevent(true);
            auto_mouse_keyevent(false);
        }
    }
}

// レイヤー表示LEDとスクロールモード
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _AML:
            rgblight_sethsv_range(HSV_GREEN, 0, 2);
            cocot_set_scroll_mode(false);
            break;
        case _SCROLL:
            rgblight_sethsv_range(HSV_YELLOW, 0, 2);
            cocot_set_scroll_mode(true);
            break;
        case _LOWER:
            rgblight_sethsv_range(HSV_BLUE, 0, 2);
            cocot_set_scroll_mode(false);
            break;
        case _RAISE:
            rgblight_sethsv_range(HSV_RED, 0, 2);
            cocot_set_scroll_mode(false);
            break;
        default:
            rgblight_sethsv_range(0, 0, 0, 0, 2);
            cocot_set_scroll_mode(false);
            break;
    }
    rgblight_set_effect_range(2, 10);
    return state;
}

// RDP対策: 修飾付きキーコード(KC_EXLM, LSFT(kc), LCTL(kc)など)で、
// 修飾キーの押下とキー本体の押下の間に待ちを入れる。
// 間隔が短すぎるとRDP上で修飾キーより先にキーが処理され、Shiftが効かないことがあるため。
// 押下側: 文字はキー押下時のShift状態で決まるので、ここを長めに取る
// 解放側: 文字の決定には影響しないので、順序を保つ程度の短い待ちにする
#ifndef RDP_PRESS_DELAY
#    define RDP_PRESS_DELAY 40
#endif
#ifndef RDP_RELEASE_DELAY
#    define RDP_RELEASE_DELAY 5
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // マウスボタンの押下でAML解除タイマーを開始（押すたびに再スタート）
    if (keycode >= MS_BTN1 && keycode <= MS_BTN8) {
        if (record->event.pressed) {
            aml_buttons_held++;
            if (is_aml_layer_active()) {
                aml_click_exit_pending = true;
                aml_click_exit_timer   = timer_read();
            }
        } else if (aml_buttons_held) {
            aml_buttons_held--;
        }
    }

    if (IS_QK_MODS(keycode)) {
        // 5bit形式(bit4が右手フラグ)の修飾を8bitのHIDモッドマスクへ変換
        uint8_t m5   = QK_MODS_GET_MODS(keycode);
        uint8_t mods = (m5 & 0x10) ? (uint8_t)((m5 & 0x0F) << 4) : (uint8_t)(m5 & 0x0F);
        uint8_t kc   = QK_MODS_GET_BASIC_KEYCODE(keycode);
        if (record->event.pressed) {
            register_weak_mods(mods);
            wait_ms(RDP_PRESS_DELAY);
            register_code(kc);
        } else {
            unregister_code(kc);
            wait_ms(RDP_RELEASE_DELAY);
            unregister_weak_mods(mods);
        }
        return false;
    }
    return true;
}
