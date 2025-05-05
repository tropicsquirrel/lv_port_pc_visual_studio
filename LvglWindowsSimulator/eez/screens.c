#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, 63);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___main_divider);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_settings_mission
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_mission = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_settings_contacts
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_contacts = obj;
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
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Contacts");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 275);
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
                    // btn_settings_info
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_info = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 231);
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
                    add_style_button_white_accent(obj);
                }
                {
                    // btn_avatar_settings_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_settings_1 = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_PRESSED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 37);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    // btn_settings_home
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_home = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 14, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Home");
                            add_style_text_button_grey(obj);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, -7);
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
                    // btn_settings_profile
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_profile = obj;
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 98, 37);
                    add_style_button_red_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 20, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Profile");
                            add_style_text_button_red(obj);
                        }
                    }
                }
            }
        }
        {
            // lbl_settings_random
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_settings_random = obj;
            lv_obj_set_pos(obj, 37, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "random #s");
            add_style_text_button_grey(obj);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 98, 127);
            lv_obj_set_size(obj, 142, 193);
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
                    // check_settings_airplanemode
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    objects.check_settings_airplanemode = obj;
                    lv_obj_set_pos(obj, 6, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Cloak Enable");
                    add_style_check_default(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 41, 30);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "(Airplane Mode)");
                    add_style_text_flavor_white(obj);
                }
                {
                    // check_settings_badgemode
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    objects.check_settings_badgemode = obj;
                    lv_obj_set_pos(obj, 6, 61);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Badge Mode");
                    add_style_check_default(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 12, 91);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Show badge after (sec):");
                    add_style_text_flavor_white(obj);
                }
                {
                    // btn_settings_delay_down
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_delay_down = obj;
                    lv_obj_set_pos(obj, 6, 112);
                    lv_obj_set_size(obj, 43, 37);
                    add_style_button_grey_rounded(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "-");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // lbl_settings_badgedelay
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.lbl_settings_badgedelay = obj;
                    lv_obj_set_pos(obj, 49, 118);
                    lv_obj_set_size(obj, 44, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "60");
                    add_style_text_label_white(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // btn_settings_delay_up
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_delay_up = obj;
                    lv_obj_set_pos(obj, 93, 112);
                    lv_obj_set_size(obj, 43, 37);
                    add_style_button_grey_rounded(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "+");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_lcars_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, 163);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Show Usernames:");
                    add_style_text_label_white(obj);
                }
                {
                    // btn_settings_usernames
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_usernames = obj;
                    lv_obj_set_pos(obj, 9, 188);
                    lv_obj_set_size(obj, 126, 37);
                    add_style_button_grey_rounded(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lbl_settings_usernames
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lbl_settings_usernames = obj;
                            lv_obj_set_pos(obj, -1, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "None");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 6, 237);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Show Game Hosts:");
                    add_style_text_label_white(obj);
                }
                {
                    // btn_settings_gamehosts
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_settings_gamehosts = obj;
                    lv_obj_set_pos(obj, 7, 261);
                    lv_obj_set_size(obj, 126, 37);
                    add_style_button_grey_rounded(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // lbl_settings_gamehosts
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.lbl_settings_gamehosts = obj;
                            lv_obj_set_pos(obj, 0, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "None");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // sld_settings_volume
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.sld_settings_volume = obj;
            lv_obj_set_pos(obj, 105, 49);
            lv_obj_set_size(obj, 129, 32);
            lv_slider_set_range(obj, 0, 21);
            lv_slider_set_value(obj, 10, LV_ANIM_OFF);
            add_style_slider_blue(obj);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 105, 19);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Volume");
            add_style_text_label_white(obj);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
}

void create_screen_main() {
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_main_mission
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_main_mission = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_main_contacts
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_main_contacts = obj;
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
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Contacts");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 275);
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
                    // btn_main_info
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_main_info = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 231);
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
                    // btn_main_settings
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_main_settings = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 38);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 98, 37);
                    add_style_button_grey_default(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6c748c), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, -7);
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
                    // btn_main_profile
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_main_profile = obj;
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 98, 37);
                    add_style_button_red_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 20, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Profile");
                            add_style_text_button_red(obj);
                        }
                    }
                }
            }
        }
        {
            // lbl_main_random
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_main_random = obj;
            lv_obj_set_pos(obj, 37, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "random #s");
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
            lv_obj_set_pos(obj, 104, 281);
            lv_obj_set_size(obj, 100, 40);
            lv_img_set_src(obj, &img_ui_element___icons);
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
        {
            // btn_avatar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.btn_avatar = obj;
            lv_obj_set_pos(obj, 120, 0);
            lv_obj_set_size(obj, 120, 89);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_avatar() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.avatar = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // roller_avatar_component
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_avatar_component = obj;
            lv_obj_set_pos(obj, 102, 113);
            lv_obj_set_size(obj, 134, 104);
            lv_roller_set_options(obj, "Background\nBody\nClothes\nHead\nMouth\nBeard\nMoustache\nEye: Left\nNose\nEye: Right\nHair\nEars\nRidges\nBrow: Left\nBrow: Right\nCybernetics\nAccessories\nAntennae\nEyewear\nHands", LV_ROLLER_MODE_INFINITE);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 20, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, 63);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___main_divider);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_avatar_mission
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_mission = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
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
                    // btn_avatar_contacts
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_contacts = obj;
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
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Contacts");
                            add_style_text_button_grey(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 275);
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
                    // btn_avatar_info
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_info = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 231);
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
                    // btn_avatar_settings
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_settings = obj;
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
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 0, 37);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    // btn_avatar_home
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_home = obj;
                    lv_obj_set_pos(obj, 21, 7);
                    lv_obj_set_size(obj, 77, 37);
                    add_style_button_grey_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 14, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Home");
                            add_style_text_button_grey(obj);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, -7);
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
                    // btn_avatar_profile
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.btn_avatar_profile = obj;
                    lv_obj_set_pos(obj, 0, 7);
                    lv_obj_set_size(obj, 98, 37);
                    add_style_button_red_default(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 20, 1);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Profile");
                            add_style_text_button_red(obj);
                        }
                    }
                }
            }
        }
        {
            // lbl_avatar_random
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_avatar_random = obj;
            lv_obj_set_pos(obj, 37, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "random #s");
            add_style_text_button_grey(obj);
            lv_obj_set_style_text_font(obj, &ui_font_lcars_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // img_background
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_background = obj;
            lv_obj_set_pos(obj, 135, 5);
            lv_obj_set_size(obj, 82, 82);
        }
        {
            // img_body
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_body = obj;
            lv_obj_set_pos(obj, 154, 57);
            lv_obj_set_size(obj, 48, 30);
        }
        {
            // img_clothes
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_clothes = obj;
            lv_obj_set_pos(obj, 152, 62);
            lv_obj_set_size(obj, 52, 25);
        }
        {
            // img_head
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_head = obj;
            lv_obj_set_pos(obj, 154, 14);
            lv_obj_set_size(obj, 43, 52);
        }
        {
            // img_mouth
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_mouth = obj;
            lv_obj_set_pos(obj, 160, 45);
            lv_obj_set_size(obj, 23, 14);
        }
        {
            // img_beard
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_beard = obj;
            lv_obj_set_pos(obj, 155, 41);
            lv_obj_set_size(obj, 38, 27);
        }
        {
            // img_moustache
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_moustache = obj;
            lv_obj_set_pos(obj, 158, 49);
            lv_obj_set_size(obj, 24, 20);
        }
        {
            // img_eye_left
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_eye_left = obj;
            lv_obj_set_pos(obj, 158, 34);
            lv_obj_set_size(obj, 11, 10);
        }
        {
            // img_nose
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_nose = obj;
            lv_obj_set_pos(obj, 163, 34);
            lv_obj_set_size(obj, 12, 18);
        }
        {
            // img_eye_right
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_eye_right = obj;
            lv_obj_set_pos(obj, 173, 34);
            lv_obj_set_size(obj, 13, 11);
        }
        {
            // img_hair
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_hair = obj;
            lv_obj_set_pos(obj, 137, 5);
            lv_obj_set_size(obj, 79, 82);
        }
        {
            // img_ears
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_ears = obj;
            lv_obj_set_pos(obj, 184, 29);
            lv_obj_set_size(obj, 16, 28);
        }
        {
            // img_ridges
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_ridges = obj;
            lv_obj_set_pos(obj, 146, 13);
            lv_obj_set_size(obj, 61, 45);
        }
        {
            // img_eyebrow_left
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_eyebrow_left = obj;
            lv_obj_set_pos(obj, 157, 27);
            lv_obj_set_size(obj, 12, 11);
        }
        {
            // img_eyebrow_right
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_eyebrow_right = obj;
            lv_obj_set_pos(obj, 171, 29);
            lv_obj_set_size(obj, 14, 9);
        }
        {
            // img_borg
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_borg = obj;
            lv_obj_set_pos(obj, 144, 13);
            lv_obj_set_size(obj, 64, 58);
        }
        {
            // img_accessories
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_accessories = obj;
            lv_obj_set_pos(obj, 147, 27);
            lv_obj_set_size(obj, 58, 60);
        }
        {
            // img_antennae
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_antennae = obj;
            lv_obj_set_pos(obj, 157, 5);
            lv_obj_set_size(obj, 41, 22);
        }
        {
            // img_glasses
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_glasses = obj;
            lv_obj_set_pos(obj, 154, 33);
            lv_obj_set_size(obj, 37, 14);
        }
        {
            // img_hands
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.img_hands = obj;
            lv_obj_set_pos(obj, 137, 37);
            lv_obj_set_size(obj, 39, 50);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 104, 241);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_ui_element___subdivider);
            lv_img_set_zoom(obj, 265);
        }
        {
            // slider_avatar_red
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_avatar_red = obj;
            lv_obj_set_pos(obj, 102, 249);
            lv_obj_set_size(obj, 100, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 128, LV_ANIM_OFF);
            add_style_slider_red(obj);
            lv_obj_set_style_radius(obj, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // slider_avatar_green
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_avatar_green = obj;
            lv_obj_set_pos(obj, 102, 269);
            lv_obj_set_size(obj, 100, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 128, LV_ANIM_OFF);
            add_style_slider_green(obj);
            lv_obj_set_style_radius(obj, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // slider_avatar_blue
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_avatar_blue = obj;
            lv_obj_set_pos(obj, 102, 289);
            lv_obj_set_size(obj, 100, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 128, LV_ANIM_OFF);
            add_style_slider_blue(obj);
            lv_obj_set_style_radius(obj, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // slider_avatar_intensity
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.slider_avatar_intensity = obj;
            lv_obj_set_pos(obj, 102, 309);
            lv_obj_set_size(obj, 100, 10);
            lv_slider_set_range(obj, 0, 255);
            lv_slider_set_value(obj, 128, LV_ANIM_OFF);
            add_style_slider_white(obj);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 102, 195);
            lv_obj_set_size(obj, 24, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_avatar_prev
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_avatar_prev = obj;
            lv_obj_set_pos(obj, 102, 195);
            lv_obj_set_size(obj, 41, 44);
            add_style_button_grey_rounded(obj);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -7, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "<");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lcars_60, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 216, 195);
            lv_obj_set_size(obj, 24, 44);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9ea4ba), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // btn_avatar_next
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_avatar_next = obj;
            lv_obj_set_pos(obj, 199, 195);
            lv_obj_set_size(obj, 41, 44);
            add_style_button_grey_rounded(obj);
            lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 7, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, ">");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lcars_60, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // lbl_avatar_item_id
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lbl_avatar_item_id = obj;
            lv_obj_set_pos(obj, 160, 220);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "1/1");
            add_style_text_flavor_white(obj);
        }
    }
    
    tick_screen_avatar();
}

void tick_screen_avatar() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_settings,
    tick_screen_main,
    tick_screen_avatar,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_settings();
    create_screen_main();
    create_screen_avatar();
}
