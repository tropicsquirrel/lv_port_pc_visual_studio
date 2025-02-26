#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: Button-Grey-Default
//

void init_style_button_grey_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff9ea4ba));
    lv_style_set_radius(style, 0);
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_button_grey_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_grey_default_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff6c748c));
};

lv_style_t *get_style_button_grey_default_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_default_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_button_grey_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_grey_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_button_grey_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_grey_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: Button-Grey-Text-10
//

void init_style_button_grey_text_10_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars10);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_10_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_10_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_10(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_10_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_10(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_10_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-14
//

void init_style_button_grey_text_14_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars14);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_14_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_14_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_14(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_14_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_14(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_14_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-16
//

void init_style_button_grey_text_16_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars16);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_16_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_16_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_16(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_16_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_16(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_16_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-18
//

void init_style_button_grey_text_18_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars18);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_18_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_18_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_18(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_18_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_18(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_18_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-20
//

void init_style_button_grey_text_20_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars20);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_20_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_20_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_20(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_20_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_20(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_20_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-22
//

void init_style_button_grey_text_22_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars22);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_22_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_22_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_22(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_22_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_22(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_22_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Grey-Text-24
//

void init_style_button_grey_text_24_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars24);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_button_grey_text_24_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_text_24_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_text_24(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_text_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_text_24(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_text_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_button_grey_default,
        add_style_button_grey_text_10,
        add_style_button_grey_text_14,
        add_style_button_grey_text_16,
        add_style_button_grey_text_18,
        add_style_button_grey_text_20,
        add_style_button_grey_text_22,
        add_style_button_grey_text_24,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_button_grey_default,
        remove_style_button_grey_text_10,
        remove_style_button_grey_text_14,
        remove_style_button_grey_text_16,
        remove_style_button_grey_text_18,
        remove_style_button_grey_text_20,
        remove_style_button_grey_text_22,
        remove_style_button_grey_text_24,
    };
    remove_style_funcs[styleIndex](obj);
}

