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
      XXXXXXX, XXXXXXX, UG_VALD, UG_SATD, UG_HUED, UG_PREV,                                       SCRL_IN,  CPI_DN,  CPI_UP, XXXXXXX, XXXXXXX, XXXXXXX,
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
//   {1,2}〜{1,5}: S D F G
//   {3,0} {3,1} {3,2} {3,3} {3,5}: 左親指キー（LGUI, DEL_ALT, LW_MHEN, SPC, MS_BTN1）
#ifndef AML_KEEP_POSITIONS
#    define AML_KEEP_POSITIONS { {1, 2}, {1, 3}, {1, 4}, {1, 5}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 5} }
#endif
// AML中に押すと、キーを入力せずにAMLだけ解除するポジション {row, col}
//   {1,1}: A
#ifndef AML_EXIT_ONLY_POSITIONS
#    define AML_EXIT_ONLY_POSITIONS { {1, 1} }
#endif
// マウスボタンを押してからAMLを解除するまでの時間(ms)
#ifndef AML_CLICK_EXIT_TIME
#    define AML_CLICK_EXIT_TIME 250
#endif

static const uint8_t aml_keep_positions[][2] = AML_KEEP_POSITIONS;
#define AML_KEEP_POSITIONS_SIZE (sizeof(aml_keep_positions) / sizeof(aml_keep_positions[0]))

static const uint8_t aml_exit_only_positions[][2] = AML_EXIT_ONLY_POSITIONS;
#define AML_EXIT_ONLY_POSITIONS_SIZE (sizeof(aml_exit_only_positions) / sizeof(aml_exit_only_positions[0]))

static matrix_row_t aml_kept_keys[MATRIX_ROWS];      // AML維持キーとして押下中のキー
static matrix_row_t aml_swallowed_keys[MATRIX_ROWS]; // AML解除のためだけに押され、入力を捨てたキー
static bool         aml_click_exit_pending = false;
static uint16_t     aml_click_exit_timer   = 0;
static uint8_t      aml_buttons_held       = 0;

static bool is_aml_keep_position(keypos_t key) {
    for (uint8_t i = 0; i < AML_KEEP_POSITIONS_SIZE; i++) {
        if (aml_keep_positions[i][0] == key.row && aml_keep_positions[i][1] == key.col) return true;
    }
    return false;
}

static bool is_aml_exit_only_position(keypos_t key) {
    for (uint8_t i = 0; i < AML_EXIT_ONLY_POSITIONS_SIZE; i++) {
        if (aml_exit_only_positions[i][0] == key.row && aml_exit_only_positions[i][1] == key.col) return true;
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
        case AM_TOG:
        case RDP_UP:
        case RDP_DN:
        case RDP_TOG:
            return true;
        default:
            return IS_MOUSE_KEYCODE(keycode);
    }
}

static bool is_matrix_key(keyrecord_t *record) {
    return IS_KEYEVENT(record->event) && record->event.key.row < MATRIX_ROWS && record->event.key.col < MATRIX_COLS;
}

// ===== ユーザー設定（ユーザー用EEPROM領域 32bit。抜き差し・再書き込み後も保持） =====
// RDP対策の押下側の待ちの初期値(ms)。実際の値は RDP_UP / RDP_DN で変更でき、EEPROMに保存される
#ifndef RDP_PRESS_DELAY
#    define RDP_PRESS_DELAY 70
#endif
// 修飾キー解放→次のキー押下、キー押下→そのキーの解放の最低間隔（順序を保つための短い待ち。固定）
#ifndef RDP_RELEASE_DELAY
#    define RDP_RELEASE_DELAY 5
#endif
// RDP_UP / RDP_DN の刻みと上限(ms)
#ifndef RDP_DELAY_STEP
#    define RDP_DELAY_STEP 10
#endif
#ifndef RDP_DELAY_MAX
#    define RDP_DELAY_MAX 200
#endif
// RDP_UP / RDP_DN / RDP_TOG を押したときに、OLEDへ設定値を一時表示する時間(ms)
#ifndef RDP_POPUP_TIME
#    define RDP_POPUP_TIME 2000
#endif
#define RDP_CONFIG_MAGIC 0xA5

// byte0: フラグ（bit0 = AML無効）。既存の個体はこの領域が0なので、書き込み直後はAML有効
// byte1〜3: RDP設定（magicが合わなければ初期化。AMLのフラグは残す）
typedef union {
    uint32_t raw;
    struct {
        uint8_t flags;
        uint8_t rdp_magic;
        uint8_t rdp_delay;    // 押下側の待ち(ms)
        uint8_t rdp_enabled;  // 1: オン, 0: オフ（QMK標準の動作）
    };
} user_config_t;
#define UCFG_AML_DISABLED 0x01
static user_config_t user_config;

static void update_rdp_led(void);

static void rdp_config_reset(void) {
    user_config.rdp_magic   = RDP_CONFIG_MAGIC;
    user_config.rdp_delay   = RDP_PRESS_DELAY;
    user_config.rdp_enabled = 1;
}

void eeconfig_init_user(void) {
    user_config.raw = 0;  // AML有効
    rdp_config_reset();
    eeconfig_update_user(user_config.raw);
}

static void aml_set_enabled(bool enable) {
    set_auto_mouse_enable(enable);
    if (!enable) {
        // 無効化した時にAMLレイヤーに入っていたら抜ける（TG(1)の固定も解除）
        if (get_auto_mouse_toggle()) auto_mouse_toggle();
        layer_off(get_auto_mouse_layer());
        aml_click_exit_pending = false;
    }
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.rdp_magic != RDP_CONFIG_MAGIC || user_config.rdp_delay > RDP_DELAY_MAX || user_config.rdp_enabled > 1) {
        rdp_config_reset();  // 旧ファームからの移行時など。AMLのフラグはそのまま
        eeconfig_update_user(user_config.raw);
    }
    aml_set_enabled(!(user_config.flags & UCFG_AML_DISABLED));
    update_rdp_led();
}

// 維持ポジション・マウス系以外のキーが押されたら即AML解除。
// キーコード確定より前にレイヤーを落とすので、押したキーはデフォルトレイヤー側のキーとして入力される。
// AML_EXIT_ONLY_POSITIONS のキーは、AMLだけ解除してキー入力は捨てる（押下・解放とも）。
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!is_matrix_key(record)) return true;
    keypos_t     key = record->event.key;
    matrix_row_t bit = (matrix_row_t)1 << key.col;

    if (record->event.pressed) {
        if (is_aml_layer_active() && !is_aml_keep_position(key) && !is_aml_mouse_keycode(keycode)) {
            auto_mouse_reset_trigger(true);
            if (is_aml_exit_only_position(key)) {
                aml_swallowed_keys[key.row] |= bit;
                return false;
            }
        }
    } else if (aml_swallowed_keys[key.row] & bit) {
        aml_swallowed_keys[key.row] &= ~bit;
        return false;
    }
    return true;
}

// AMLを維持するキー（エンコーダ回転、マウス系キー、AML中に押された維持ポジション）
bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    // ロータリーエンコーダの回転ではAMLを解除しない
    if (IS_ENCODEREVENT(record->event)) return true;
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

// インジケータLED（2個）：RDP_LED_INDEX をRDP対策の表示（オンで白点灯）、もう1個をレイヤー表示に使う。
// 実機で左右が逆なら RDP_LED_INDEX を 1 にする。
#ifndef RDP_LED_INDEX
#    define RDP_LED_INDEX 0
#endif
#define LAYER_LED_INDEX (1 - RDP_LED_INDEX)

static void update_rdp_led(void) {
    if (user_config.rdp_enabled) {
        rgblight_sethsv_at(HSV_WHITE, RDP_LED_INDEX);
    } else {
        rgblight_setrgb_at(0, 0, 0, RDP_LED_INDEX);
    }
}

// レイヤー表示LEDとスクロールモード
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t li = LAYER_LED_INDEX;
    switch (get_highest_layer(state)) {
        case _AML:
            rgblight_sethsv_at(HSV_GREEN, li);
            cocot_set_scroll_mode(false);
            break;
        case _SCROLL:
            rgblight_sethsv_at(HSV_YELLOW, li);
            cocot_set_scroll_mode(true);
            break;
        case _LOWER:
            rgblight_sethsv_at(HSV_BLUE, li);
            cocot_set_scroll_mode(false);
            break;
        case _RAISE:
            rgblight_sethsv_at(HSV_RED, li);
            cocot_set_scroll_mode(false);
            break;
        default:
            rgblight_setrgb_at(0, 0, 0, li);
            cocot_set_scroll_mode(false);
            break;
    }
    update_rdp_led();
    rgblight_set_effect_range(2, 10);
    return state;
}

// ---------------------------------------------------------------------------
// RDP対策
// RDP上では、修飾キーとキー本体のレポートが短い間隔で続くと、修飾キーより先に
// キーが処理されて修飾が効かないことがある。修飾キーの状態が変わった直後のキー押下だけ、
// 一定時間空くまで待ってから送る。
//   - 修飾付きキーコード(KC_EXLM, LSFT(kc), LCTL(kc)など): 修飾→待ち→キー
//   - HRM(mod-tap)のホールド、物理的な修飾キー、LMなど: get_mods()の変化を検出し、
//     直後に押されたキーを待たせる(押されるのが遅ければ待ちは発生しない)
// RDP_UP / RDP_DN で押下側の待ちを10ms刻みで変更、RDP_TOG でオン/オフ（設定はEEPROMに保存）
// ---------------------------------------------------------------------------
static uint16_t rdp_mod_press_time;   // 最後に修飾キーが押された時刻
static uint16_t rdp_mod_release_time; // 最後に修飾キーが離された時刻
static uint16_t rdp_key_press_time;   // 最後にキーが押された時刻
static uint8_t  rdp_mods_before;      // 処理前の修飾キー状態(post_process_record_userで比較)
static uint16_t rdp_popup_time;
static bool     rdp_popup_active;

// 直前の修飾キー変化から必要な間隔が空くまで待つ
static void rdp_wait_after_mods(void) {
    uint16_t since_press   = timer_elapsed(rdp_mod_press_time);
    uint16_t since_release = timer_elapsed(rdp_mod_release_time);
    uint16_t wait          = 0;
    if (since_press < user_config.rdp_delay) wait = user_config.rdp_delay - since_press;
    if (since_release < RDP_RELEASE_DELAY && RDP_RELEASE_DELAY - since_release > wait) wait = RDP_RELEASE_DELAY - since_release;
    if (wait) wait_ms(wait);
}

// 押下とその直後の解放が続けて処理される場合(Permissive Holdで溜められたキーなど)に最低間隔を空ける
static void rdp_wait_before_release(void) {
    uint16_t since = timer_elapsed(rdp_key_press_time);
    if (since < RDP_RELEASE_DELAY) wait_ms(RDP_RELEASE_DELAY - since);
}

// 修飾キーそのものの押下か(この場合は待たない)
static bool rdp_is_mod_press(uint16_t keycode, keyrecord_t *record) {
    if (IS_MODIFIER_KEYCODE(keycode)) return true;
#ifndef NO_ACTION_TAPPING
    if (IS_QK_MOD_TAP(keycode) && record->tap.count == 0) return true; // HRMのホールド
#endif
    return false;
}

// RDP_UP / RDP_DN / RDP_TOG の処理
static void rdp_change_setting(uint16_t keycode) {
    if (keycode == RDP_UP) {
        user_config.rdp_delay = (user_config.rdp_delay + RDP_DELAY_STEP > RDP_DELAY_MAX) ? RDP_DELAY_MAX : user_config.rdp_delay + RDP_DELAY_STEP;
    } else if (keycode == RDP_DN) {
        user_config.rdp_delay = (user_config.rdp_delay < RDP_DELAY_STEP) ? 0 : user_config.rdp_delay - RDP_DELAY_STEP;
    } else {
        user_config.rdp_enabled = !user_config.rdp_enabled;
    }
    eeconfig_update_user(user_config.raw);
    update_rdp_led();
    rdp_popup_time   = timer_read();
    rdp_popup_active = true;
}

#ifdef OLED_ENABLE
// cocot46plus.c のOLED表示から呼ばれる（cocot46plus.h で宣言）
// 4行目末尾の常時表示: オン'R' / オフ'-'
char cocot_rdp_indicator(void) {
    return user_config.rdp_enabled ? 'R' : '-';
}

// RDP_UP / RDP_DN / RDP_TOG を押してから RDP_POPUP_TIME の間だけ、4行目を設定値の表示に切り替える
// 例: "RDP ON    70ms" / "RDP OFF  ( 70ms)"（snprintfは容量が大きいので使わない）
bool cocot_rdp_popup(char *buf, uint8_t len) {
    if (!rdp_popup_active) return false;
    if (timer_elapsed(rdp_popup_time) >= RDP_POPUP_TIME) {
        rdp_popup_active = false;
        return false;
    }
    char num[4];
    get_numeric_str(num, sizeof(num), user_config.rdp_delay, ' ');
    const char *head = user_config.rdp_enabled ? PSTR("RDP ON   ") : PSTR("RDP OFF  (");
    uint8_t     n    = 0;
    for (char c; n < len - 1 && (c = pgm_read_byte(head + n)) != '\0'; n++) buf[n] = c;
    for (uint8_t i = 0; i < 3 && n < len - 1; i++) buf[n++] = num[i];
    if (n < len - 1) buf[n++] = 'm';
    if (n < len - 1) buf[n++] = 's';
    if (!user_config.rdp_enabled && n < len - 1) buf[n++] = ')';
    buf[n] = '\0';
    return true;
}
#endif

// CPIを段階的に増減する（CPI_UP / CPI_DN）。端では止まり、ループしない。設定はEEPROMに保存。
#ifndef CPI_UPDN_STEP
#    define CPI_UPDN_STEP 1
#endif
extern uint16_t cpi_array[];
static const uint16_t cpi_options[] = COCOT_CPI_OPTIONS;
#define CPI_OPTIONS_COUNT (sizeof(cpi_options) / sizeof(cpi_options[0]))

static void cpi_step(int8_t dir) {
    int16_t idx = (int16_t)cocot_config.cpi_idx + dir * CPI_UPDN_STEP;
    if (idx < 0) idx = 0;
    if (idx > (int16_t)CPI_OPTIONS_COUNT - 1) idx = CPI_OPTIONS_COUNT - 1;
    if (idx == cocot_config.cpi_idx) return;
    cocot_config.cpi_idx = (uint8_t)idx;
    eeconfig_update_kb(cocot_config.raw);
    pointing_device_set_cpi(cpi_array[cocot_config.cpi_idx]);
}

// Mod-Tap のタップ側で Shift 付き記号を出す（OSはJIS配列前提）。
// Mod-Tap はタップ側に基本キーコードしか持てず、LALT_T(S(KC_6)) と書いても Shift が落ちるため、
// タップ時の処理を横取りして Shift+キー を送る。RDP対策がオンなら同じ待ちを入れる。
static void rdp_tap_shifted(uint8_t kc) {
    if (!user_config.rdp_enabled) {
        tap_code16(S(kc));
        return;
    }
    register_weak_mods(MOD_BIT(KC_LSFT));
    rdp_mod_press_time = timer_read();
    rdp_wait_after_mods();  // = 設定中の押下側の待ち
    register_code(kc);
    rdp_key_press_time = timer_read();
    rdp_wait_before_release();
    unregister_code(kc);
    wait_ms(RDP_RELEASE_DELAY);
    unregister_weak_mods(MOD_BIT(KC_LSFT));
    rdp_mod_release_time = timer_read();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == AM_TOG) {
        if (record->event.pressed) {
            user_config.flags ^= UCFG_AML_DISABLED;
            eeconfig_update_user(user_config.raw);
            aml_set_enabled(!(user_config.flags & UCFG_AML_DISABLED));
        }
        return false;
    }

    if (keycode == RDP_UP || keycode == RDP_DN || keycode == RDP_TOG) {
        if (record->event.pressed) rdp_change_setting(keycode);
        return false;
    }

    if (keycode == CPI_UP || keycode == CPI_DN) {
        if (record->event.pressed) cpi_step(keycode == CPI_UP ? 1 : -1);
        return false;
    }

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

    // RDP対策（オフのときはQMK標準の動作。Mod-TapのShift付きタップだけは下で処理する）
    rdp_mods_before = get_mods();
    bool rdp_on     = user_config.rdp_enabled;
    if (rdp_on) {
        if (record->event.pressed) {
            if (!rdp_is_mod_press(keycode, record)) rdp_wait_after_mods();
        } else {
            rdp_wait_before_release();
        }
    }

    switch (keycode) {
        case LALT_T(KC_6):  // ホールド:Alt   / タップ:＆（Shift+6）
        case LCTL_T(KC_8):  // ホールド:Ctrl  / タップ:（（Shift+8）
        case LSFT_T(KC_9):  // ホールド:Shift / タップ:）（Shift+9）
            if (record->tap.count) {
                if (record->event.pressed) rdp_tap_shifted(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
                return false;  // タップの解放も横取り（基本キーの解放を送らない）
            }
            break;  // ホールドは通常の修飾キーとして処理
    }

    if (!rdp_on) return true;

    if (IS_QK_MODS(keycode)) {
        // 5bit形式(bit4が右手フラグ)の修飾を8bitのHIDモッドマスクへ変換
        uint8_t m5   = QK_MODS_GET_MODS(keycode);
        uint8_t mods = (m5 & 0x10) ? (uint8_t)((m5 & 0x0F) << 4) : (uint8_t)(m5 & 0x0F);
        uint8_t kc   = QK_MODS_GET_BASIC_KEYCODE(keycode);
        if (record->event.pressed) {
            register_weak_mods(mods);
            rdp_mod_press_time = timer_read();
            rdp_wait_after_mods();  // = 設定中の押下側の待ち
            register_code(kc);
            rdp_key_press_time = timer_read();
        } else {
            unregister_code(kc);
            wait_ms(RDP_RELEASE_DELAY);
            unregister_weak_mods(mods);
            rdp_mod_release_time = timer_read();
        }
        return false;
    }

    if (record->event.pressed) {
        rdp_key_press_time = timer_read();
    }
    return true;
}

// キー処理の後で修飾キーの状態を比較し、押された/離された時刻を記録する。
// mod-tapのホールド、物理的な修飾キー、LM(layer, mod)などをまとめて検出できる。
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods_after = get_mods();
    if (mods_after & ~rdp_mods_before) rdp_mod_press_time = timer_read();
    if (rdp_mods_before & ~mods_after) rdp_mod_release_time = timer_read();
}

// トラックボールでのスクロール方向を反転（縦・横とも）
// EEPROMの設定に依存せず常に反転させる。SCRL_IN を押すと元の向きに戻る。
#ifndef SCROLL_REVERSE
#    define SCROLL_REVERSE 1
#endif

// LOWERレイヤー中はカーソル移動量を 1/SLOW_CPI_DIV にする（細かい操作用）。
// ADNS-5050のCPIは125刻みでしか設定できず正確な1/4にならないため、
// センサーのCPIは変えずに移動量をソフトウェアで割る。端数は持ち越すので小さな動きも失われない。
#ifndef SLOW_CPI_LAYER
#    define SLOW_CPI_LAYER _LOWER
#endif
#ifndef SLOW_CPI_DIV
#    define SLOW_CPI_DIV 4
#endif

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static int16_t slow_x_rem = 0, slow_y_rem = 0;
    if (layer_state_is(SLOW_CPI_LAYER)) {
        slow_x_rem += mouse_report.x;
        slow_y_rem += mouse_report.y;
        mouse_report.x = slow_x_rem / SLOW_CPI_DIV;
        mouse_report.y = slow_y_rem / SLOW_CPI_DIV;
        slow_x_rem -= mouse_report.x * SLOW_CPI_DIV;
        slow_y_rem -= mouse_report.y * SLOW_CPI_DIV;
    } else {
        slow_x_rem = 0;
        slow_y_rem = 0;
    }
#if SCROLL_REVERSE
    mouse_report.h = -mouse_report.h;
    mouse_report.v = -mouse_report.v;
#endif
    return mouse_report;
}

// PCのスリープ中はLEDとトラックボールセンサーを消灯する。
// RGBLIGHT_SLEEP（keyboard.json の "sleep": true）は演出範囲(LED 2〜11)しか消さないため、
// レイヤー表示用のLED 0〜1 はここで消す。
// センサー(ADNS-5050)はパワーダウンさせて照明LEDを消し、復帰時に初期化し直す。
#include "drivers/sensors/adns5050.h"

static bool leds_suspended = false;

void suspend_power_down_user(void) {
    if (!leds_suspended) {
        leds_suspended = true;
        rgblight_setrgb_range(0, 0, 0, 0, 2);
        adns5050_power_down();
    }
}

void suspend_wakeup_init_user(void) {
    leds_suspended = false;
    adns5050_init();            // センサーをリセットしてパワーダウンから復帰
    pointing_device_init_kb();  // CPIとLEDモードを再設定
    layer_state_set_user(layer_state);  // レイヤー表示LEDを復元
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_set_cursor(0, 0);
    render_logo();
    oled_write_layer_state();
    return false;
}
#endif
