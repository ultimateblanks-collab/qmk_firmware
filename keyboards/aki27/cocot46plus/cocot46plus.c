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
#include <math.h>


// Invert vertical scroll direction
#ifndef COCOT_SCROLL_INV_DEFAULT
#    define COCOT_SCROLL_INV_DEFAULT 1
#endif

#ifndef COCOT_CPI_OPTIONS
#    define COCOT_CPI_OPTIONS { 250, 500, 750, 1000, 1250 }
#endif
#ifndef COCOT_CPI_DEFAULT
#    define COCOT_CPI_DEFAULT 4
#endif

#ifndef COCOT_SCROLL_DIVIDERS
#    define COCOT_SCROLL_DIVIDERS { 1, 2, 3, 4, 5, 6 }
#endif
#ifndef COCOT_SCROLL_DIV_DEFAULT
#    define COCOT_SCROLL_DIV_DEFAULT 4
#endif


#ifndef COCOT_ROTATION_ANGLE
#    define COCOT_ROTATION_ANGLE { -60, -45, -30, -15, 0, 15, 30, 45, 60 }
#endif
#ifndef COCOT_ROTATION_DEFAULT
#    define COCOT_ROTATION_DEFAULT 2
#endif


cocot_config_t cocot_config;
uint16_t cpi_array[] = COCOT_CPI_OPTIONS;
uint16_t scrl_div_array[] = COCOT_SCROLL_DIVIDERS;
uint16_t angle_array[] = COCOT_ROTATION_ANGLE;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define SCRL_DIV_SIZE (sizeof(scrl_div_array) / sizeof(uint16_t))
#define ANGLE_SIZE (sizeof(angle_array) / sizeof(uint16_t))


// Trackball State
bool     BurstState        = false;  // init burst state for Trackball module
uint16_t MotionStart       = 0;      // Timer for accel, 0 is resting state


void pointing_device_init_kb(void) {
    // set the CPI.
    pointing_device_set_cpi(cpi_array[cocot_config.cpi_idx]);
    adns5050_write_reg(0x22, 0b10000 | 0x80);
}


report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    static float x_accumulator = 0.0;
    static float y_accumulator = 0.0;
    static float prev_x = 0.0, prev_y = 0.0;

    float sensitivity = 0.5;           // Movement sensitivity
    float smoothing_factor = 0.7;     // Smoothing factor
    float sensitivity_multiplier = 1.5; // Sensitivity adjustment multiplier

    // Apply rotation angle adjustment
    double rad = (double)angle_array[cocot_config.rotation_angle] * (M_PI / 180) * -1;
    float rotated_x = mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    float rotated_y = mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    // Apply smoothing to the rotated values
    float smoothed_x = prev_x * smoothing_factor + rotated_x * (1.0 - smoothing_factor);
    float smoothed_y = prev_y * smoothing_factor + rotated_y * (1.0 - smoothing_factor);
    prev_x = smoothed_x;
    prev_y = smoothed_y;

    // Apply sensitivity multiplier
    smoothed_x *= sensitivity_multiplier;
    smoothed_y *= sensitivity_multiplier;

    // Scroll mode handling
    if (cocot_get_scroll_mode()) {
        static int h_acm = 0, v_acm = 0;

        // Determine scroll direction
        if (abs((int)smoothed_x) > abs((int)smoothed_y)) {
            smoothed_y = 0; // Horizontal scroll
        } else {
            smoothed_x = 0; // Vertical scroll
        }

        // Accumulate scroll values
        if (cocot_config.scrl_inv > 0) {  // scrl_inv は 1 / -1 で切り替わるため符号で判定
            h_acm += smoothed_x;
            v_acm -= smoothed_y;
        } else {
            h_acm -= smoothed_x;
            v_acm += smoothed_y;
        }

        // Calculate scroll values with division factor
        int8_t h_scroll = h_acm >> scrl_div_array[cocot_config.scrl_div];
        int8_t v_scroll = v_acm >> scrl_div_array[cocot_config.scrl_div];

        // Apply scroll to mouse report
        if (h_scroll != 0) {
            mouse_report.h += h_scroll;
            h_acm -= h_scroll << scrl_div_array[cocot_config.scrl_div];
        }
        if (v_scroll != 0) {
            mouse_report.v += v_scroll;
            v_acm -= v_scroll << scrl_div_array[cocot_config.scrl_div];
        }

        // Reset X/Y movement in scroll mode
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // Movement smoothing and accumulation for normal mode
        x_accumulator += smoothed_x * sensitivity;
        y_accumulator += smoothed_y * sensitivity;
        if (fabs(x_accumulator) >= 1.0) {
            mouse_report.x = (int8_t)x_accumulator;
            x_accumulator -= mouse_report.x;
        } else {
            mouse_report.x = 0;
        }
        if (fabs(y_accumulator) >= 1.0) {
            mouse_report.y = (int8_t)y_accumulator;
            y_accumulator -= mouse_report.y;
        } else {
            mouse_report.y = 0;
        }
    }

    return pointing_device_task_user(mouse_report);
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == CPI_SW && record->event.pressed) {
        cocot_config.cpi_idx = (cocot_config.cpi_idx + 1) % CPI_OPTION_SIZE;
        eeconfig_update_kb(cocot_config.raw);
        pointing_device_set_cpi(cpi_array[cocot_config.cpi_idx]);
    }

    if (keycode == SCRL_SW && record->event.pressed) {
        cocot_config.scrl_div = (cocot_config.scrl_div + 1) % SCRL_DIV_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == ROT_R15 && record->event.pressed) {
        cocot_config.rotation_angle = (cocot_config.rotation_angle + 1) % ANGLE_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == ROT_L15 && record->event.pressed) {
        cocot_config.rotation_angle = (ANGLE_SIZE + cocot_config.rotation_angle - 1) % ANGLE_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == SCRL_IN && record->event.pressed) {
        cocot_config.scrl_inv = -cocot_config.scrl_inv;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == SCRL_TO && record->event.pressed) {
        {
            cocot_config.scrl_mode ^= 1;
        }
    }

    if (keycode == SCRL_MO) {
        {
            cocot_config.scrl_mode ^= 1;
        }
    }

    return true;
}

void eeconfig_init_kb(void) {
    cocot_config.cpi_idx = COCOT_CPI_DEFAULT;
    cocot_config.scrl_div = COCOT_SCROLL_DIV_DEFAULT;
    cocot_config.rotation_angle = COCOT_ROTATION_DEFAULT;
    cocot_config.scrl_inv = COCOT_SCROLL_INV_DEFAULT;
    cocot_config.scrl_mode = false;
    eeconfig_update_kb(cocot_config.raw);
    eeconfig_init_user();
    adns5050_write_reg(0x22, 0b10000 | 0x80);
}


void matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    cocot_config.raw = eeconfig_read_kb();
    if (cocot_config.cpi_idx >= CPI_OPTION_SIZE) // || cocot_config.scrl_div > SCRL_DIV_SIZE || cocot_config.rotation_angle > ANGLE_SIZE)
    {
        eeconfig_init_kb();
    }
    matrix_init_user();
}


bool cocot_get_scroll_mode(void) {
    return cocot_config.scrl_mode;
}

void cocot_set_scroll_mode(bool mode) {
    cocot_config.scrl_mode = mode;
}



// OLED utility
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

static const char PROGMEM cocot_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
    0};

void render_logo(void) {
    oled_write_P(cocot_logo, false);
};

// RDP対策の状態表示。keymap側で定義されていなければ何も表示しない
__attribute__((weak)) char cocot_rdp_indicator(void) {
    return 0;
}
__attribute__((weak)) bool cocot_rdp_popup(char *buf, uint8_t len) {
    return false;
}

#define COCOT_OLED_COLS 21 // 128px / 6px(フォント幅)

static uint8_t oled_put_P(char *line, uint8_t n, const char *s) {
    for (char c; n < COCOT_OLED_COLS && (c = pgm_read_byte(s)) != '\0'; s++) line[n++] = c;
    return n;
}
static uint8_t oled_put(char *line, uint8_t n, const char *s) {
    while (n < COCOT_OLED_COLS && *s) line[n++] = *s++;
    return n;
}

// 4行目: <レイヤー名>/<C|S>/<CPI>/<スクロール>/<角度>[/<RDP R|->]
// 例: "Base /C/1250/ 4/-30/R"（ちょうど21文字）
// RDP_UP / RDP_DN / RDP_TOG を押した直後は、設定値の表示に一時的に切り替わる
void oled_write_layer_state(void) {
    char    line[COCOT_OLED_COLS + 1];
    uint8_t n = 0;

    if (cocot_rdp_popup(line, sizeof(line))) {
        while (n < COCOT_OLED_COLS && line[n] != '\0') n++;
    } else {
        int cpi        = cpi_array[cocot_config.cpi_idx];
        int scroll_div = scrl_div_array[cocot_config.scrl_div];
        int angle      = (int16_t)angle_array[cocot_config.rotation_angle];

        // snprintf は容量が大きいため、QMK標準の get_numeric_str で右詰めの数値文字列を作る
        char buf1[5];
        char buf2[3];
        char buf3[4];
        get_numeric_str(buf1, sizeof(buf1), (uint32_t)cpi, ' ');
        get_numeric_str(buf2, sizeof(buf2), (uint32_t)scroll_div, ' ');
        get_numeric_str(buf3, sizeof(buf3), (uint32_t)(angle < 0 ? -angle : angle), ' ');
        if (angle < 0) {
            // 符号を数字の直前に置く（角度は最大2桁なので先頭に空白がある）
            for (int8_t i = 1; i >= 0; i--) {
                if (buf3[i] == ' ') { buf3[i] = '-'; break; }
            }
        }

        const char *name;
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:  name = PSTR("Base "); break;
            case 1:  name = PSTR("Mouse"); break;
            case 2:  name = PSTR("Scrl "); break;
            case 3:  name = PSTR("Lower"); break;
            case 4:  name = PSTR("Raise"); break;
            default: name = PSTR("Undef"); break;
        }
        n = oled_put_P(line, n, name);
        n = oled_put_P(line, n, cocot_get_scroll_mode() ? PSTR("/S/") : PSTR("/C/"));
        n = oled_put(line, n, buf1);
        n = oled_put_P(line, n, PSTR("/"));
        n = oled_put(line, n, buf2);
        n = oled_put_P(line, n, PSTR("/"));
        n = oled_put(line, n, buf3);

        char rdp = cocot_rdp_indicator();
        if (rdp && n + 2 <= COCOT_OLED_COLS) {
            line[n++] = '/';
            line[n++] = rdp;
        }
    }

    // 1行ちょうどの文字数にそろえる（前の表示の消え残りを防ぐ）
    while (n < COCOT_OLED_COLS) line[n++] = ' ';
    line[COCOT_OLED_COLS] = '\0';
    oled_write(line, false);
}

#endif

