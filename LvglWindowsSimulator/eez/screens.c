#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include "custom.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 24, 0, e);
    }
}

static void event_handler_cb_progress_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pip_right
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.pip_right = obj;
            lv_obj_set_pos(obj, 106, 75);
            lv_obj_set_size(obj, 14, 14);
            lv_led_set_color(obj, lv_color_hex(0xffffff00));
            lv_led_set_brightness(obj, 255);
            add_style_pip_filled(obj);
        }
        {
            // pip_right_mid
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.pip_right_mid = obj;
            lv_obj_set_pos(obj, 106, 51);
            lv_obj_set_size(obj, 14, 14);
            lv_led_set_color(obj, lv_color_hex(0xffffff00));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_outline_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pip_left_mid
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.pip_left_mid = obj;
            lv_obj_set_pos(obj, 106, 27);
            lv_obj_set_size(obj, 14, 14);
            lv_led_set_color(obj, lv_color_hex(0xffffff00));
            lv_led_set_brightness(obj, 255);
            add_style_pip_empty(obj);
        }
        {
            // pip_left
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.pip_left = obj;
            lv_obj_set_pos(obj, 106, 3);
            lv_obj_set_size(obj, 14, 14);
            lv_led_set_color(obj, lv_color_hex(0xff000000));
            lv_led_set_brightness(obj, 255);
            add_style_pip_hidden(obj);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, 63);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___main_divider);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 137, 25);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_klingon48x48);
        }
        {
            // ctr_mission
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_mission = obj;
            lv_obj_set_pos(obj, 0, 144);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 13, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_button_grey_accent(obj);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 6, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Mission");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // ctr_crew
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_crew = obj;
            lv_obj_set_pos(obj, 0, 188);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 13, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_button_grey_accent(obj);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 17, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Crew");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // ctr_info
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_info = obj;
            lv_obj_set_pos(obj, 0, 232);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 13, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_button_grey_accent(obj);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 20, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Info");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // ctr_settings
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_settings = obj;
            lv_obj_set_pos(obj, 0, 276);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 13, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_button_grey_accent(obj);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 5, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Settings");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // ctr_progress
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_progress = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 98, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
                    add_style_button_red_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 13, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Progress");
                            add_style_text_button_red(obj);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 0, 49);
            lv_obj_set_size(obj, 98, 9);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_button_grey_accent(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 37, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            add_style_text_button_grey(obj);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // flavor_main1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main1 = obj;
            lv_obj_set_pos(obj, 111, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main2 = obj;
            lv_obj_set_pos(obj, 111, 151);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main3 = obj;
            lv_obj_set_pos(obj, 111, 169);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main4 = obj;
            lv_obj_set_pos(obj, 111, 187);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main5 = obj;
            lv_obj_set_pos(obj, 111, 204);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main6 = obj;
            lv_obj_set_pos(obj, 111, 222);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_main7
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_main7 = obj;
            lv_obj_set_pos(obj, 111, 240);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 04 08 15 16 23 42");
            add_style_text_flavor_black(obj);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 106, 272);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___subdivider);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, -390, 203);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___icons);
            lv_img_set_zoom(obj, 24);
        }
        {
            // flavor_side1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_side1 = obj;
            lv_obj_set_pos(obj, 186, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 00");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_side2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_side2 = obj;
            lv_obj_set_pos(obj, 186, 29);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 00");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_side3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_side3 = obj;
            lv_obj_set_pos(obj, 186, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 00");
            add_style_text_flavor_black(obj);
        }
        {
            // flavor_side4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.flavor_side4 = obj;
            lv_obj_set_pos(obj, 186, 64);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00 00 00");
            add_style_text_flavor_black(obj);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 27, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj7;
            lv_label_set_text(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_progress() {
    void *flowState = getFlowState(0, 1);
    lv_obj_t *obj = lv_obj_create(0);
    objects.progress = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(obj, load_scroll_color_values, LV_EVENT_ALL, flowState);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, 94);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___main_divider);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 134, -10);
            lv_obj_set_size(obj, LV_PCT(33), LV_PCT(48));
            lv_img_set_src(obj, &img_klingon48x48);
            lv_img_set_zoom(obj, 512);
        }
        {
            // ctr_progress_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_progress_1 = obj;
            lv_obj_set_pos(obj, 0, 45);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 6);
                    lv_obj_set_size(obj, 98, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_progress_obj1, LV_EVENT_ALL, flowState);
                    add_style_button_red_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 13, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Cancel");
                            add_style_text_button_red(obj);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 221, 18);
            lv_obj_set_size(obj, 98, 9);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
            add_style_button_grey_accent(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj16 = obj;
            lv_obj_set_pos(obj, 37, 154);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            add_style_text_button_grey(obj);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 106, 232);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___subdivider);
        }
        {
            // slider_red
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_red = obj;
            lv_obj_set_pos(obj, 120, 253);
            lv_obj_set_size(obj, 78, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, tint_r, LV_ANIM_OFF);
            add_style_slider_red(obj);
            lv_obj_add_event_cb(obj, set_color_panel, LV_EVENT_ALL, flowState);
        }
        {
            // slider_green
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_green = obj;
            lv_obj_set_pos(obj, 120, 277);
            lv_obj_set_size(obj, 78, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            add_style_slider_green(obj);
            lv_obj_add_event_cb(obj, set_color_panel, LV_EVENT_ALL, flowState);
        }
        {
            // slider_blue
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_blue = obj;
            lv_obj_set_pos(obj, 120, 301);
            lv_obj_set_size(obj, 78, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            add_style_slider_blue(obj);
            lv_obj_add_event_cb(obj, set_color_panel, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 0, 176);
            lv_obj_set_size(obj, 106, 144);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ctr_mission_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.ctr_mission_1 = obj;
                    lv_obj_set_pos(obj, -15, -15);
                    lv_obj_set_size(obj, 98, 44);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 7);
                            lv_obj_set_size(obj, 13, 37);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_button_grey_accent(obj);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj10 = obj;
                            lv_obj_set_pos(obj, 21, 7);
                            lv_obj_set_size(obj, 77, 37);
                            add_style_button_grey_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 16, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Head");
                                    add_style_text_button_grey(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    // ctr_crew_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.ctr_crew_1 = obj;
                    lv_obj_set_pos(obj, -15, 29);
                    lv_obj_set_size(obj, 98, 44);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 7);
                            lv_obj_set_size(obj, 13, 37);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_button_grey_accent(obj);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj11 = obj;
                            lv_obj_set_pos(obj, 21, 7);
                            lv_obj_set_size(obj, 77, 37);
                            add_style_button_grey_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 16, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Torso");
                                    add_style_text_button_grey(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    // ctr_info_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.ctr_info_1 = obj;
                    lv_obj_set_pos(obj, -15, 73);
                    lv_obj_set_size(obj, 98, 44);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 7);
                            lv_obj_set_size(obj, 13, 37);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_button_grey_accent(obj);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj12 = obj;
                            lv_obj_set_pos(obj, 21, 7);
                            lv_obj_set_size(obj, 77, 37);
                            add_style_button_grey_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 20, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Eyes");
                                    add_style_text_button_grey(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    // ctr_settings_1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.ctr_settings_1 = obj;
                    lv_obj_set_pos(obj, -15, 117);
                    lv_obj_set_size(obj, 98, 44);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 7);
                            lv_obj_set_size(obj, 13, 37);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_button_grey_accent(obj);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj13 = obj;
                            lv_obj_set_pos(obj, 21, 7);
                            lv_obj_set_size(obj, 77, 37);
                            add_style_button_grey_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 21, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Hair");
                                    add_style_text_button_grey(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    // ctr_settings_2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.ctr_settings_2 = obj;
                    lv_obj_set_pos(obj, -15, 162);
                    lv_obj_set_size(obj, 98, 44);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 7);
                            lv_obj_set_size(obj, 13, 37);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                            add_style_button_grey_accent(obj);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj14 = obj;
                            lv_obj_set_pos(obj, 21, 7);
                            lv_obj_set_size(obj, 77, 37);
                            add_style_button_grey_default(obj);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 12, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Mouth");
                                    add_style_text_button_grey(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // ctr_mission_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ctr_mission_3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 98, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 13, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
                    add_style_button_grey_accent(obj);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj15 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 6, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Confirm");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // panel_Color
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_color = obj;
            lv_obj_set_pos(obj, 116, 160);
            lv_obj_set_size(obj, 105, 66);
        }
    }
    
    tick_screen_progress();
}

void tick_screen_progress() {
    void *flowState = getFlowState(0, 1);
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj16);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj16;
            lv_label_set_text(objects.obj16, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_mission() {
    void *flowState = getFlowState(0, 2);
    lv_obj_t *obj = lv_obj_create(0);
    objects.mission = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    
    tick_screen_mission();
}

void tick_screen_mission() {
    void *flowState = getFlowState(0, 2);
}

void create_screen_crew() {
    void *flowState = getFlowState(0, 3);
    lv_obj_t *obj = lv_obj_create(0);
    objects.crew = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    
    tick_screen_crew();
}

void tick_screen_crew() {
    void *flowState = getFlowState(0, 3);
}

void create_screen_info() {
    void *flowState = getFlowState(0, 4);
    lv_obj_t *obj = lv_obj_create(0);
    objects.info = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    
    tick_screen_info();
}

void tick_screen_info() {
    void *flowState = getFlowState(0, 4);
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 5);
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 5);
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Main", "Progress", "Mission", "Crew", "Info", "Settings" };
static const char *object_names[] = { "main", "progress", "mission", "crew", "info", "settings", "obj0", "obj1", "pip_right", "pip_right_mid", "pip_left_mid", "pip_left", "ctr_mission", "obj2", "ctr_crew", "obj3", "ctr_info", "obj4", "ctr_settings", "obj5", "ctr_progress", "obj6", "flavor_main1", "flavor_main2", "flavor_main3", "flavor_main4", "flavor_main5", "flavor_main6", "flavor_main7", "flavor_side1", "flavor_side2", "flavor_side3", "flavor_side4", "obj7", "ctr_progress_1", "obj8", "slider_red", "slider_green", "slider_blue", "obj9", "ctr_mission_1", "obj10", "ctr_crew_1", "obj11", "ctr_info_1", "obj12", "ctr_settings_1", "obj13", "ctr_settings_2", "obj14", "ctr_mission_3", "obj15", "panel_color", "obj16" };
static const char *style_names[] = { "Button-Grey-Default", "Button-Red-Default", "Text-Button-Grey", "Text-Button-Red", "Button-Grey-Accent", "Pip-Filled", "Pip-Hidden", "Pip-Empty", "Text-Flavor-Orange", "Text-Flavor-White", "Text-Flavor-Gray-Light", "Text-Flavor-Gray-Dark", "Text-Flavor-Black", "Slider_Red", "Slider_Green", "Slider_Blue" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_progress,
    tick_screen_mission,
    tick_screen_crew,
    tick_screen_info,
    tick_screen_settings,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_progress();
    create_screen_mission();
    create_screen_crew();
    create_screen_info();
    create_screen_settings();
}
