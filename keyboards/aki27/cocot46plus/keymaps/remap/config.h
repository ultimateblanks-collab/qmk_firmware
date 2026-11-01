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

/* オートマウスレイヤー（AML） */
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1
#define AUTO_MOUSE_TIME 30000      // AMLのタイムアウト(ms)
#define AML_CLICK_EXIT_TIME 250    // マウスボタンを押してからAML解除までの時間(ms)

/* RDP対策：修飾付きキーコードの修飾キーと本体の間の待ち時間(ms) */
#define RDP_PRESS_DELAY 40
#define RDP_RELEASE_DELAY 5
