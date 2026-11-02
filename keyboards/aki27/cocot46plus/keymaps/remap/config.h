#pragma once

/* レイヤー数（デフォルト含め5） */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* RGBアニメーション無効（単色・レイヤー表示は残る） */
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT

/* タップ／ホールド設定 */
#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD
/* HOLD_ON_OTHER_KEY_PRESS は定義しない（off） */
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 175

/* RDP対策：修飾付きキーコードの修飾キーと本体の間の待ち時間(ms) */
#define RDP_PRESS_DELAY 70     // 初期値。RDP_UP/RDP_DNで変更しEEPROMに保存
#define RDP_RELEASE_DELAY 5

/* トラックボールのCPI：センサー(ADNS-5050)の最小刻み125で125〜1625の13段階 */
#define COCOT_CPI_OPTIONS { 125, 250, 375, 500, 625, 750, 875, 1000, 1125, 1250, 1375, 1500, 1625 }
#define COCOT_CPI_DEFAULT 9      // 初期値 1250（EEPROM初期化時のみ）
#define CPI_UPDN_STEP 1          // CPI_UP / CPI_DN 1回で動く段数（1段 = 125）
