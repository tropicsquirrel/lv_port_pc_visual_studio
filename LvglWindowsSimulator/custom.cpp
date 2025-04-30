#include <cstdio>
#if defined(_WIN32) || defined(_WIN64)
#include ".\eez\screens.h"
#include ".\eez\vars.h"
#include ".\eez\images.h"
#include "pngs.h"
#include "mp3s.h"
#include "json.h"
#else
#include "screens.h"
#include "vars.h"
#include "images.h"
#include "../pngs.h"
#include "../mp3s.h"
#include "../json.h"
#endif

#include "custom.h"
#include <chrono>


/*
Layer Description
----- -----------
00    Background
01    Body
02    Clothes
03    Head
04    Mouth
05    Beard
06    Moustache
07    Eye-L
08    Nose
09    Eye-R
10    Hair
11    Ears
12    Ridges
13    Eyebrow-L
14    Eyebrow-R
15    Borg
16    Accessories
17    Antennae
18    Glasses
19    Hands
*/

int32_t int_max_items = 0;
int32_t int_current_item = 0;

extern objects_t objects; // LVGL root screens object
extern Config config;     // Global configuration object

void set_tint(lv_event_t* e)
{
    int32_t tint_r = lv_slider_get_value(objects.slider_avatar_red);
    int32_t tint_g = lv_slider_get_value(objects.slider_avatar_green);
    int32_t tint_b = lv_slider_get_value(objects.slider_avatar_blue);

    lv_color_t color = lv_color_make(tint_r, tint_g, tint_b);
    lv_opa_t intense = lv_slider_get_value(objects.slider_avatar_intensity);

    lv_obj_t* img1 = NULL;

    switch (lv_roller_get_selected(objects.roller_avatar_component))
    {
    case 0: //background
        img1 = objects.img_background;
        break;
    case 1: //body
        img1 = objects.img_body;
        break;
    case 2: //clothes
        img1 = objects.img_clothes;
        break;
    case 3: //head
        img1 = objects.img_head;
        break;
    case 4: //mouth
        img1 = objects.img_mouth;
        break;
    case 5: //beard
        img1 = objects.img_beard;
        break;
    case 6: //mustache
        img1 = objects.img_moustache;
        break;
    case 7: //eye-l
        img1 = objects.img_eye_left;
        break;
    case 8: //nose
        img1 = objects.img_nose;
        break;
    case 9: //eye-r
        img1 = objects.img_eye_right;
        break;
    case 10: //hair
        img1 = objects.img_hair;
        break;
    case 11: //ears
        img1 = objects.img_ears;
        break;
    case 12: //ridges
        img1 = objects.img_ridges;
        break;
    case 13: //eyebrows-l
        img1 = objects.img_eyebrow_left;
        break;
    case 14: //eyebrows-r
        img1 = objects.img_eyebrow_right;
        break;
    case 15: //borg
        img1 = objects.img_borg;
        break;
    case 16: //accessories
        img1 = objects.img_accessories;
        break;
    case 17: //antennae
        img1 = objects.img_antennae;
        break;
    case 18: //glasses
        img1 = objects.img_glasses;
        break;
    case 19: //hands		
        img1 = objects.img_hands;
        break;
    default:
        int_max_items = 0;
        break;
    }

    if (NULL != img1)
    {
        lv_obj_set_style_image_recolor_opa(img1, intense, 0);
        lv_obj_set_style_image_recolor(img1, color, 0);
    }
}

static void load_screen_settings(lv_event_t* e)
{
    lv_screen_load_anim(objects.settings, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
}

static void load_screen_avatar(lv_event_t* e)
{
    lv_screen_load_anim(objects.avatar, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
}

static void set_airplane_mode(lv_event_t* e)
{
    config.board.airplaneMode = (lv_obj_get_state(objects.check_settings_airplanemode) & LV_STATE_CHECKED);
    saveBoardConfig(config);
}

// set up callbacks for objects
void setup_cb()
{
    printf("initial airplane mode: %u\n", config.board.airplaneMode);
    lv_obj_add_event_cb(objects.roller_avatar_component, roller_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_next, avatar_next, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_prev, avatar_prev, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar, load_screen_avatar, LV_EVENT_PRESSED, NULL);
    //lv_obj_add_event_cb(objects.btn_profile_main, load_screen_avatar, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_red, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_green, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_blue, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_intensity, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.btn_main_settings, load_screen_settings, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(objects.check_settings_airplanemode, set_airplane_mode, LV_EVENT_VALUE_CHANGED, NULL);
    //lv_obj_add_event_cb(objects.slider_red, set_color_panel, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(objects.slider_green, set_color_panel, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(objects.slider_blue, set_color_panel, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(objects.progress, load_scroll_color_values, LV_EVENT_ALL, NULL);
    roller_changed(NULL); // Initialize the roller
    //update_ui(); //called by roller_changed() so not needed

    //test to show that we're reading images from the file system
    lv_fs_dir_t dir;
    lv_fs_res_t res;
    res = lv_fs_dir_open(&dir, "L:/images/bg");
    if (res != LV_FS_RES_OK) printf("Error accessing directory\n");

    char fn[256];
    while (1) {
        res = lv_fs_dir_read(&dir, fn, sizeof(fn));
        if (res == LV_FS_RES_NOT_EX) //End of directory
        {
            break;
        }
        if (res != LV_FS_RES_OK) {
            printf("Error reading directory\n");
            break;
        }

        /* fn is empty if there are no more files to read. */
        if (strlen(fn) == 0) {
            break;
        }

        printf("%s\n", fn);
    }

    lv_fs_dir_close(&dir);

    //load an image and display it
    lv_obj_t* obj = lv_image_create(objects.main);
    lv_obj_set_pos(obj, 135, 5);
    lv_obj_set_size(obj, 82, 82);
    lv_image_set_src(obj, background_images[2]);
    printf("image loaded\n");
}

// implement callback functions

// This function is called when the roller selection changes
void roller_changed(lv_event_t* e) {

    switch (lv_roller_get_selected(objects.roller_avatar_component))
    {
    case 0: //background
        int_max_items = int_background_count;
        int_current_item = int_current_background;
        break;
    case 1: //body
        int_max_items = int_body_count;
        int_current_item = int_current_body;
        break;
    case 2: //clothes
        int_max_items = int_clothes_count;
        int_current_item = int_current_clothes;
        break;
    case 3: //head
        int_max_items = int_head_count;
        int_current_item = int_current_head;
        break;
    case 4: //mouth
        int_max_items = int_mouth_count;
        int_current_item = int_current_mouth;
        break;
    case 5: //beard
        int_max_items = int_beard_count;
        int_current_item = int_current_beard;
        break;
    case 6: //mustache
        int_max_items = int_mustache_count;
        int_current_item = int_current_mustache;
        break;
    case 7: //eye-l
        int_max_items = int_eye_l_count;
        int_current_item = int_current_eye_l;
        break;
    case 8: //nose
        int_max_items = int_nose_count;
        int_current_item = int_current_noses;
        break;
    case 9: //eye-r
        int_max_items = int_eye_r_count;
        int_current_item = int_current_eye_r;
        break;
    case 10: //hair
        int_max_items = int_hair_count;
        int_current_item = int_current_hair;
        break;
    case 11: //ears
        int_max_items = int_ears_count;
        int_current_item = int_current_ears;
        break;
    case 12: //ridges
        int_max_items = int_ridges_count;
        int_current_item = int_current_ridges;
        break;
    case 13: //eyebrows-l
        int_max_items = int_eyebrow_l_count;
        int_current_item = int_current_eyebrow_l;
        break;
    case 14: //eyebrows-r
        int_max_items = int_eyebrow_r_count;
        int_current_item = int_current_eyebrow_r;
        break;
    case 15: //borg
        int_max_items = int_borg_count;
        int_current_item = int_current_borg;
        break;
    case 16: //accessories
        int_max_items = int_accessories_count;
        int_current_item = int_current_accessories;
        break;
    case 17: //antennae
        int_max_items = int_antennae_count;
        int_current_item = int_current_antennae;
        break;
    case 18: //glasses
        int_max_items = int_glasses_count;
        int_current_item = int_current_glasses;
        break;
    case 19: //hands		
        int_max_items = int_hands_count;
        int_current_item = int_current_hands;
        break;
    default:
        int_max_items = 0;
        break;
    }
    update_item_counter();
}

// fires when the '>' (next) avatar component variant button is clicked 
void avatar_next(lv_event_t* e) {
    play_random_beep(); // Play a random beep sound when the button is clicked
    int_current_item++;
    if (int_current_item >= int_max_items) {
        int_current_item = 0;
    }
    update_avatar_images();
}

// fires when the '<' (previous) avatar component variant button is clicked 
void avatar_prev(lv_event_t* e) {
    play_random_beep(); // Play a random beep sound when the button is clicked
    int_current_item--;
    if (int_current_item < 0) {
        int_current_item = int_max_items - 1;
    }
    update_avatar_images();
}

// This function updates the counters ("x/y") based on the current selection in the roller
void update_avatar_images()
{
    switch (lv_roller_get_selected(objects.roller_avatar_component))
    {
    case 0: //background
        int_current_background = int_current_item;
        lv_image_set_src(objects.img_background, background_images[int_current_background]);
        break;
    case 1: //body
        int_current_body = int_current_item;
        lv_image_set_src(objects.img_body, body_images[int_current_body]);
        break;
    case 2: //clothes
        int_current_clothes = int_current_item;
        lv_image_set_src(objects.img_clothes, clothes_images[int_current_clothes]);
        break;
    case 3: //head
        int_current_head = int_current_item;
        lv_image_set_src(objects.img_head, head_images[int_current_head]);
        break;
    case 4: //mouth
        int_current_mouth = int_current_item;
        lv_image_set_src(objects.img_mouth, mouth_images[int_current_mouth]);
        break;
    case 5: //beard
        int_current_beard = int_current_item;
        lv_image_set_src(objects.img_beard, beard_images[int_current_beard]);
        break;
    case 6: //mustache
        int_current_mustache = int_current_item;
        lv_image_set_src(objects.img_moustache, mustache_images[int_current_mustache]);
        break;
    case 7: //eye-l
        int_current_eye_l = int_current_item;
        lv_image_set_src(objects.img_eye_left, eye_l_images[int_current_eye_l]);
        break;
    case 8: //nose
        int_current_noses = int_current_item;
        lv_image_set_src(objects.img_nose, noses_images[int_current_noses]);
        break;
    case 9: //eye-r
        int_current_eye_r = int_current_item;
        lv_image_set_src(objects.img_eye_right, eye_r_images[int_current_eye_r]);
        break;
    case 10: //hair
        int_current_hair = int_current_item;
        lv_image_set_src(objects.img_hair, hair_images[int_current_hair]);
        break;
    case 11: //ears
        int_current_ears = int_current_item;
        lv_image_set_src(objects.img_ears, ears_images[int_current_ears]);
        break;
    case 12: //ridges
        int_current_ridges = int_current_item;
        lv_image_set_src(objects.img_ridges, ridges_images[int_current_ridges]);
        break;
    case 13: //eyebrow-l
        int_current_eyebrow_l = int_current_item;
        lv_image_set_src(objects.img_eyebrow_left, eyebrows_l_images[int_current_eyebrow_l]);
        break;
    case 14: //eyebrow-r
        int_current_eyebrow_r = int_current_item;
        lv_image_set_src(objects.img_eyebrow_right, eyebrows_r_images[int_current_eyebrow_r]);
        break;
    case 15: //borg
        int_current_borg = int_current_item;
        lv_image_set_src(objects.img_borg, borg_images[int_current_borg]);
        break;
    case 16: //accessories
        int_current_accessories = int_current_item;
        lv_image_set_src(objects.img_accessories, accessories_images[int_current_accessories]);
        break;
    case 17: //antennae
        int_current_antennae = int_current_item;
        break;
    case 18: //glasses
        int_current_glasses = int_current_item;
        lv_image_set_src(objects.img_glasses, glasses_images[int_current_glasses]);
        break;
    case 19: //hands
        int_current_hands = int_current_item;
        lv_image_set_src(objects.img_hands, hands_images[int_current_hands]);
        break;
    default:
        break;
    }
    update_item_counter();
}

// This function updates the UI elements based on the current selections
void update_item_counter()
{
    char str_item_id[8];

    //need to load images from flash
 //   lv_image_set_src(objects.img_background, background_images[int_current_background]);
 //   lv_image_set_src(objects.img_head, head_images[int_current_head]);
    //lv_image_set_src(objects.img_mouth, mouth_images[int_current_mouth]);
    //lv_image_set_src(objects.img_beard, beard_images[int_current_beard]);
    //lv_image_set_src(objects.img_moustache, mustache_images[int_current_mustache]);
    //lv_image_set_src(objects.img_nose, noses_images[int_current_noses]);
    //lv_image_set_src(objects.img_eye_left, eye_l_images[int_current_eye_l]);
    //lv_image_set_src(objects.img_eye_right, eye_r_images[int_current_eye_r]);
    //lv_image_set_src(objects.img_hair, hair_images[int_current_hair]);
    //lv_image_set_src(objects.img_ears, ears_images[int_current_ears]);
    //lv_image_set_src(objects.img_ridges, ridges_images[int_current_ridges]);
    //lv_image_set_src(objects.img_eyebrow_left, eyebrows_l_images[int_current_eyebrow_l]);
    //lv_image_set_src(objects.img_eyebrow_right, eyebrows_r_images[int_current_eyebrow_r]);
    //lv_image_set_src(objects.img_borg, borg_images[int_current_borg]);
    //lv_image_set_src(objects.img_accessories, accessories_images[int_current_accessories]);
    //lv_image_set_src(objects.img_clothes, clothes_images[int_current_clothes]);
    //lv_image_set_src(objects.img_hands, hands_images[int_current_hands]);
    //lv_image_set_src(objects.img_glasses, glasses_images[int_current_glasses]);

    snprintf(str_item_id, sizeof(str_item_id), "%d/%d", int_current_item + 1, int_max_items);
    lv_label_set_text(objects.lbl_avatar_item_id, str_item_id);
}

void load_scroll_color_values(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    //if (event == LV_EVENT_SCREEN_LOADED) {
    //        if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
    //            lv_obj_set_style_bg_color(objects.panel_color,
    //                lv_color_make(tint_r, tint_g, tint_b),
    //                LV_PART_MAIN);
    //            lv_slider_set_value(objects.slider_red, tint_r, LV_ANIM_OFF);
    //            lv_slider_set_value(objects.slider_green, tint_g, LV_ANIM_OFF);
    //            lv_slider_set_value(objects.slider_blue, tint_b, LV_ANIM_OFF);
    //        }
    //}
}
