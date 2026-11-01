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

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t scrl_div;
        uint8_t rotation_angle;
        int8_t scrl_inv;
        bool scrl_mode;
        report_mouse_t last_mouse;
    };
} cocot_config_t;

enum cocot_keycodes {

    COCOT_SAFE_RANGE = SAFE_RANGE,
    CPI_SW,
    SCRL_SW,
    ROT_R15,
    ROT_L15,
    SCRL_MO,
    SCRL_TO,
    SCRL_IN
};

#define CPI_SW QK_KB_0
#define SCRL_SW QK_KB_1
#define ROT_R15 QK_KB_2
#define ROT_L15 QK_KB_3
#define SCRL_MO QK_KB_4
#define SCRL_TO QK_KB_5
#define SCRL_IN QK_KB_6
#define CPI_UP  QK_KB_7   // CPIを1段上げる
#define CPI_DN  QK_KB_8   // CPIを1段下げる
#define AM_TOG  QK_KB_9   // AML機能のオン／オフ（状態は保存）
#define RDP_UP  QK_KB_10  // RDP対策：押下側の待ちを+10ms（保存）
#define RDP_DN  QK_KB_11  // RDP対策：押下側の待ちを-10ms（保存）
#define RDP_TOG QK_KB_12  // RDP対策のオン／オフ（保存。オフでQMK標準の動作）

// RDP対策の状態表示(OLED用)。keymap側で定義すると表示される(未定義なら表示なし)
char cocot_rdp_indicator(void);               // 4行目末尾の1文字。0なら表示しない
bool cocot_rdp_popup(char *buf, uint8_t len); // trueのとき4行目をbufの内容に置き換える

extern cocot_config_t cocot_config;

bool cocot_get_scroll_mode(void);
void cocot_set_scroll_mode(bool mode);

void render_logo(void);
void oled_write_layer_state(void);
