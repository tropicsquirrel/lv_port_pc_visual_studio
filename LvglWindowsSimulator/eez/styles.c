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

void add_style_button_grey_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button-Red-Default
//

void init_style_button_red_default_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffe74429));
    lv_style_set_border_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_width(style, 3);
    lv_style_set_radius(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_button_red_default_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_red_default_MAIN_PRESSED(style);
    }
    return style;
};

void init_style_button_red_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_shadow_width(style, 0);
    lv_style_set_border_color(style, lv_color_hex(0xffe74429));
    lv_style_set_border_width(style, 3);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 8);
    lv_style_set_pad_bottom(style, 8);
    lv_style_set_pad_left(style, 13);
    lv_style_set_pad_right(style, 13);
};

lv_style_t *get_style_button_red_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_red_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_red_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_red_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_button_red_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_red_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_red_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_button_red_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Button-Grey
//

void init_style_text_button_grey_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars_20);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_pad_top(style, 2);
    lv_style_set_pad_bottom(style, 2);
    lv_style_set_pad_left(style, 2);
    lv_style_set_pad_right(style, 6);
};

lv_style_t *get_style_text_button_grey_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_button_grey_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_button_grey(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_button_grey_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_button_grey(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_button_grey_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Button-Red
//

void init_style_text_button_red_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xffe74429));
    lv_style_set_text_font(style, &ui_font_lcars_20);
    lv_style_set_pad_right(style, 6);
    lv_style_set_pad_left(style, 2);
    lv_style_set_pad_bottom(style, 2);
    lv_style_set_pad_top(style, 2);
};

lv_style_t *get_style_text_button_red_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_button_red_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_text_button_red_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_text_button_red_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_button_red_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_text_button_red(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_button_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_text_button_red_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_text_button_red(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_button_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_text_button_red_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: Button-Grey-Accent
//

void init_style_button_grey_accent_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 0);
    lv_style_set_bg_color(style, lv_color_hex(0xff52586e));
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_button_grey_accent_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_grey_accent_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_grey_accent(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_grey_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_grey_accent(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_grey_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Pip-Filled
//

void init_style_pip_filled_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_outline_width(style, 6);
    lv_style_set_outline_color(style, lv_color_hex(0xff000000));
    lv_style_set_outline_pad(style, 2);
};

lv_style_t *get_style_pip_filled_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pip_filled_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pip_filled(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_pip_filled_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pip_filled(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_pip_filled_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Pip-Hidden
//

void init_style_pip_hidden_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_outline_width(style, 6);
    lv_style_set_outline_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_pip_hidden_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pip_hidden_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pip_hidden(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_pip_hidden_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pip_hidden(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_pip_hidden_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Pip-Empty
//

void init_style_pip_empty_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xff000000));
    lv_style_set_border_width(style, 7);
    lv_style_set_outline_color(style, lv_color_hex(0xff000000));
    lv_style_set_outline_width(style, 6);
    lv_style_set_outline_pad(style, 2);
};

lv_style_t *get_style_pip_empty_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_pip_empty_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_pip_empty(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_pip_empty_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_pip_empty(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_pip_empty_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Flavor-Orange
//

void init_style_text_flavor_orange_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffff8901));
    lv_style_set_text_font(style, &ui_font_lcars_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_text_flavor_orange_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_flavor_orange_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_flavor_orange(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_flavor_orange_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_flavor_orange(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_flavor_orange_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Flavor-White
//

void init_style_text_flavor_white_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffffff));
    lv_style_set_text_font(style, &ui_font_lcars_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_text_flavor_white_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_flavor_white_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_flavor_white(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_flavor_white_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_flavor_white(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_flavor_white_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Flavor-Gray-Light
//

void init_style_text_flavor_gray_light_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff959189));
    lv_style_set_text_font(style, &ui_font_lcars_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_text_flavor_gray_light_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_flavor_gray_light_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_flavor_gray_light(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_flavor_gray_light_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_flavor_gray_light(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_flavor_gray_light_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Flavor-Gray-Dark
//

void init_style_text_flavor_gray_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff2e312e));
    lv_style_set_text_font(style, &ui_font_lcars_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_text_flavor_gray_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_flavor_gray_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_flavor_gray_dark(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_flavor_gray_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_flavor_gray_dark(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_flavor_gray_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Text-Flavor-Black
//

void init_style_text_flavor_black_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff000000));
    lv_style_set_text_font(style, &ui_font_lcars_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_text_flavor_black_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_text_flavor_black_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_text_flavor_black(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_text_flavor_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_text_flavor_black(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_text_flavor_black_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Slider_Red
//

void init_style_slider_red_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
    lv_style_set_text_color(style, lv_color_hex(0xffffffff));
};

lv_style_t *get_style_slider_red_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_red_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_slider_red_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_slider_red_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_red_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_slider_red_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_slider_red_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_red_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_slider_red(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_slider_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_red_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_red_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_slider_red(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_slider_red_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_red_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_red_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
// Style: Slider_Green
//

void init_style_slider_green_KNOB_DEFAULT(lv_style_t *style) {
    init_style_slider_red_KNOB_DEFAULT(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xff00ff3d));
};

lv_style_t *get_style_slider_green_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_green_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_slider_green_INDICATOR_DEFAULT(lv_style_t *style) {
    init_style_slider_red_INDICATOR_DEFAULT(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xff00ff3d));
};

lv_style_t *get_style_slider_green_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_green_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_slider_green_MAIN_DEFAULT(lv_style_t *style) {
    init_style_slider_red_MAIN_DEFAULT(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xff00ff3d));
};

lv_style_t *get_style_slider_green_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_green_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_slider_green(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_slider_green_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_green_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_slider_green(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_slider_green_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_green_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Slider_Blue
//

void init_style_slider_blue_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff2196f3));
};

lv_style_t *get_style_slider_blue_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_blue_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_slider_blue_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff2196f3));
};

lv_style_t *get_style_slider_blue_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_blue_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_slider_blue_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff2196f3));
};

lv_style_t *get_style_slider_blue_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_blue_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_slider_blue(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_slider_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_blue_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_blue_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_slider_blue(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_slider_blue_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_blue_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_blue_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_button_grey_default,
        add_style_button_red_default,
        add_style_text_button_grey,
        add_style_text_button_red,
        add_style_button_grey_accent,
        add_style_pip_filled,
        add_style_pip_hidden,
        add_style_pip_empty,
        add_style_text_flavor_orange,
        add_style_text_flavor_white,
        add_style_text_flavor_gray_light,
        add_style_text_flavor_gray_dark,
        add_style_text_flavor_black,
        add_style_slider_red,
        add_style_slider_green,
        add_style_slider_blue,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_button_grey_default,
        remove_style_button_red_default,
        remove_style_text_button_grey,
        remove_style_text_button_red,
        remove_style_button_grey_accent,
        remove_style_pip_filled,
        remove_style_pip_hidden,
        remove_style_pip_empty,
        remove_style_text_flavor_orange,
        remove_style_text_flavor_white,
        remove_style_text_flavor_gray_light,
        remove_style_text_flavor_gray_dark,
        remove_style_text_flavor_black,
        remove_style_slider_red,
        remove_style_slider_green,
        remove_style_slider_blue,
    };
    remove_style_funcs[styleIndex](obj);
}

