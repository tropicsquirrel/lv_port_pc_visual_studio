//#include "lvgl.h"
//#include "pngs.h"
//#include "custom.h"
//#include ".\eez\screens.h"
//#include <cstdio>
//
//int32_t int_max_items = 0;
//int32_t int_current_item = 0;
//
//static lv_obj_t* avatar_canvas = nullptr;
//static lv_color32_t* avatar_buf = nullptr;
//
//#define AVATAR_W 82
//#define AVATAR_H 82
//#define AVATAR_BUF_SIZE (AVATAR_W * AVATAR_H * sizeof(lv_color32_t))
//
//const char** avatar_layers[] = {
//    background_images,
//    body_images,
//    clothes_images,
//    head_images,
//    mouth_images,
//    beard_images,
//    mustache_images,
//    eye_l_images,
//    noses_images,
//    eye_r_images,
//    hair_images,
//    ears_images,
//    ridges_images,
//    eyebrows_l_images,
//    eyebrows_r_images,
//    borg_images,
//    accessories_images,
//    antennes_images,
//    glasses_images,
//    hands_images
//};
//
//int32_t* avatar_layer_indices[] = {
//    &int_current_background,
//    &int_current_body,
//    &int_current_clothes,
//    &int_current_head,
//    &int_current_mouth,
//    &int_current_beard,
//    &int_current_mustache,
//    &int_current_eye_l,
//    &int_current_noses,
//    &int_current_eye_r,
//    &int_current_hair,
//    &int_current_ears,
//    &int_current_ridges,
//    &int_current_eyebrow_l,
//    &int_current_eyebrow_r,
//    &int_current_borg,
//    &int_current_accessories,
//    &int_current_antennae,
//    &int_current_glasses,
//    &int_current_hands
//};
//
//static void blend_pixel(lv_color32_t* dest, lv_color32_t src) {
//    uint8_t alpha = src.alpha;
//    if (alpha == 255) {
//        *dest = src;
//    }
//    else if (alpha > 0) {
//        dest->red = (src.red * alpha + dest->red * (255 - alpha)) / 255;
//        dest->green = (src.green * alpha + dest->green * (255 - alpha)) / 255;
//        dest->blue = (src.blue * alpha + dest->blue * (255 - alpha)) / 255;
//        dest->alpha = 255;
//    }
//}
//
//bool blend_image_file(const char* path) {
//    FILE* file = fopen(path, "rb");
//    if (!file) return false;
//
//    lv_color32_t src[AVATAR_W * AVATAR_H];
//    size_t read = fread(src, 1, AVATAR_BUF_SIZE, file);
//    fclose(file);
//    if (read != AVATAR_BUF_SIZE) return false;
//
//    for (int i = 0; i < AVATAR_W * AVATAR_H; i++) {
//        blend_pixel(&avatar_buf[i], src[i]);
//    }
//
//    return true;
//}
//
//void render_avatar_composite() {
//    memset(avatar_buf, 0x00, AVATAR_BUF_SIZE);
//
//    for (int i = 0; i < 20; i++) {
//        const char* path = avatar_layers[i][*avatar_layer_indices[i]];
//        blend_image_file(path);
//    }
//
//    lv_canvas_set_buffer(avatar_canvas, avatar_buf, AVATAR_W, AVATAR_H, LV_COLOR_FORMAT_ARGB8888);
//}
//
//void setup_cb() {
//    lv_obj_add_event_cb(objects.roller_avatar_component, roller_changed, LV_EVENT_VALUE_CHANGED, NULL);
//    lv_obj_add_event_cb(objects.btn_avatar_next, avatar_next, LV_EVENT_CLICKED, NULL);
//    lv_obj_add_event_cb(objects.btn_avatar_prev, avatar_prev, LV_EVENT_CLICKED, NULL);
//    lv_obj_add_event_cb(objects.btn_avatar, load_screen_avatar, LV_EVENT_PRESSED, NULL);
//    lv_obj_add_event_cb(objects.btn_profile_main, load_screen_avatar, LV_EVENT_PRESSED, NULL);
//
//    if (!avatar_buf) {
//#ifdef _WIN32
//        avatar_buf = (lv_color32_t*)malloc(AVATAR_BUF_SIZE);
//#else
//#include <esp_heap_caps.h>
//        avatar_buf = (lv_color32_t*)heap_caps_malloc(AVATAR_BUF_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
//#endif
//    }
//
//    avatar_canvas = lv_canvas_create(objects.avatar);
//    lv_obj_align(avatar_canvas, LV_ALIGN_CENTER, 0, 0);
//    render_avatar_composite();
//    lv_roller_set_selected(objects.roller_avatar_component, 0, LV_ANIM_OFF);
//    update_counters();
//}
//
//void update_ui() {
//    char str_item_id[8];
//    snprintf(str_item_id, sizeof(str_item_id), "%d/%d", int_current_item + 1, int_max_items);
//    lv_label_set_text(objects.lbl_avatar_item_id, str_item_id);
//    render_avatar_composite();
//}



#include <cstdio>
#include ".\eez\screens.h"
#include ".\eez\vars.h"
#include ".\eez\images.h"
#include "custom.h"
#include "pngs.h"
#include "mp3s.h"


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

int32_t tint_r = 128; // Default value
int32_t tint_g = 128; // Default value
int32_t tint_b = 128; // Default value



// get/set red
int32_t get_var_tint_r() {
    return tint_r;
}
void set_var_tint_r(int32_t value) {
    tint_r = value;
}

// get/set green
int32_t get_var_tint_g() {
    return tint_g;
}
void set_var_tint_g(int32_t value) {
    tint_g = value;
}

// get/set blue
int32_t get_var_tint_b() {
    return tint_b;
}
void set_var_tint_b(int32_t value) {
    tint_b = value;
}

extern objects_t objects;

// set up callbacks for objects
void setup_cb()
{
    lv_obj_add_event_cb(objects.roller_avatar_component, roller_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_next, avatar_next, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_prev, avatar_prev, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar, load_screen_avatar, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(objects.btn_profile_main, load_screen_avatar, LV_EVENT_PRESSED, NULL);
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

void load_screen_avatar(lv_event_t* e)
{
    printf("Loading screen avatar\n");
    lv_screen_load_anim(objects.avatar, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
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

    snprintf(str_item_id, sizeof(str_item_id), "%d/%d", int_current_item+1, int_max_items);
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
