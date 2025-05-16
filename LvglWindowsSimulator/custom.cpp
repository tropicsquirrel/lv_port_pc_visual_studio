#include <cstdio>


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

int32_t int_ms_since_touch = 0;

extern objects_t objects; // LVGL root screens object
extern Config config;     // Global configuration object
extern bool badgeMode_triggered;
extern lv_display_t* disp;

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

// change UI settings and apply them to the board
bool applyConfig(Config& config)
{
    //username
	lv_textarea_set_text(objects.txt_profile_username, config.user.displayName);

    //volume
    lv_slider_set_value(objects.sld_settings_volume, config.board.volume, LV_ANIM_OFF);
#ifndef _WIN32
	//Volume_adjustment(config.board.volume);
#endif // !_WIN32

    //airplane mode
    lv_obj_set_state(objects.check_settings_airplanemode, LV_STATE_CHECKED, config.board.airplaneMode);
    //actually change wifi

    //badge mode
    lv_obj_set_state(objects.check_settings_badgemode, LV_STATE_CHECKED, config.board.badgeMode.enabled);
    lv_label_set_text(objects.lbl_settings_badgedelay, std::to_string(config.board.badgeMode.delay).c_str());

    String displayUsernames;
    switch (config.board.displayNameOptions.showNamesFrom)
    {
    case Everyone:
        displayUsernames = "Everyone";
        break;
    case NotBlocked:
        displayUsernames = "Not Blocked";
        break;
    case Friends:
        displayUsernames = "Friends";
        break;
    case None:
        displayUsernames = "None";
        break;
    default:
        break;
    }
    lv_label_set_text(objects.lbl_settings_usernames, displayUsernames.c_str());

    String gameHosts;
    switch (config.board.displayNameOptions.gameHosts)
    {
    case Everyone:
        gameHosts = "Everyone";
        break;
    case NotBlocked:
        gameHosts = "Not Blocked";
        break;
    case Friends:
        gameHosts = "Friends";
        break;
    case None:
        gameHosts = "None";
        break;
    default:
        break;
    }
    lv_label_set_text(objects.lbl_settings_gamehosts, gameHosts.c_str());

    return true;
}

bool saveAndApplyBoardConfig(Config& config)
{
    // Save the configuration to the file
    if (!saveBoardConfig(config))
    {
        printf("Failed to save board config\n");
        return false;
    }
    // Apply the configuration to the board
    return applyConfig(config);
}

// en/disable airplane mode
static void set_airplane_mode(lv_event_t* e)
{
    config.board.airplaneMode = (lv_obj_get_state(objects.check_settings_airplanemode) & LV_STATE_CHECKED);
    saveAndApplyBoardConfig(config);
}

// en/disable badge mode
static void set_badge_mode(lv_event_t* e)
{
    config.board.badgeMode.enabled = (lv_obj_get_state(objects.check_settings_badgemode) & LV_STATE_CHECKED);
    saveAndApplyBoardConfig(config);
}

// increase badge mode delay by 5 seconds, but not above 900 (15 min)
static void increase_delay(lv_event_t* e)
{
    config.board.badgeMode.delay = min(900, config.board.badgeMode.delay + 5);
    saveAndApplyBoardConfig(config);
}

// decrease badge mode delay by 5 seconds, but not below 5
static void decrease_delay(lv_event_t* e)
{
    config.board.badgeMode.delay = max(5, config.board.badgeMode.delay - 5);
    saveAndApplyBoardConfig(config);
}

// load the badge screen and rotate the display
void load_screen_badge()
{
#ifndef _WIN32
    set_display_rotation(disp, LV_DISPLAY_ROTATION_180);
#endif
    lv_screen_load_anim(objects.badge, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
}

// end badge mode and go back to the main screen
static void end_badge_mode(lv_event_t* e)
{
#ifndef _WIN32
    set_display_rotation(disp, LV_DISPLAY_ROTATION_0);
#endif
    badgeMode_triggered = false;
    lv_screen_load_anim(objects.main, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
}

// rotate through usernames you allow to display
static void set_usernames(lv_event_t* e)
{
    char* usernames = lv_label_get_text(objects.lbl_settings_usernames);
    if (strcmp(usernames, "Everyone") == 0)
        config.board.displayNameOptions.showNamesFrom = NotBlocked;
    else if (strcmp(usernames, "Not Blocked") == 0)
        config.board.displayNameOptions.showNamesFrom = Friends;
    else if (strcmp(usernames, "Friends") == 0)
        config.board.displayNameOptions.showNamesFrom = None;
    else
    {
        config.board.displayNameOptions.showNamesFrom = Everyone;
    }
    saveAndApplyBoardConfig(config);
}

// rotate through who is allowed to join your games
static void set_gamehosts(lv_event_t* e)
{
    char* gameHosts = lv_label_get_text(objects.lbl_settings_gamehosts);
    if (strcmp(gameHosts, "Everyone") == 0)
        config.board.displayNameOptions.gameHosts = NotBlocked;
    else if (strcmp(gameHosts, "Not Blocked") == 0)
        config.board.displayNameOptions.gameHosts = Friends;
    else if (strcmp(gameHosts, "Friends") == 0)
        config.board.displayNameOptions.gameHosts = None;
    else
    {
        config.board.displayNameOptions.gameHosts = Everyone;
    }
    saveAndApplyBoardConfig(config);
}

// change the badge volume
static void set_volume(lv_event_t* e)
{
    config.board.volume = lv_slider_get_value(objects.sld_settings_volume);
    saveAndApplyBoardConfig(config);
}

// setup a simplified keyboard
//static void remap_keyboard(lv_event_t* e)
//{
//    static const char* kb_map[] = { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
//                                    "A", "S", "D", "F", "G", "H", "J", "K", "L",  LV_SYMBOL_NEW_LINE, "\n",
//                                    "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "?", "\n",
//                                    LV_SYMBOL_CLOSE, " ",  " ", " ", LV_SYMBOL_OK, NULL
//    };
//
//    /*Set the relative width of the buttons and other controls*/
//    static const lv_buttonmatrix_ctrl_t kb_ctrl[] = { LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_6,
//                                                     LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_6,
//                                                     LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4, LV_BUTTONMATRIX_CTRL_WIDTH_4,
//                                                     LV_BUTTONMATRIX_CTRL_WIDTH_2, (lv_buttonmatrix_ctrl_t)(LV_BUTTONMATRIX_CTRL_HIDDEN | LV_BUTTONMATRIX_CTRL_WIDTH_2), LV_BUTTONMATRIX_CTRL_WIDTH_6, (lv_buttonmatrix_ctrl_t)(LV_BUTTONMATRIX_CTRL_HIDDEN | LV_BUTTONMATRIX_CTRL_WIDTH_2), LV_BUTTONMATRIX_CTRL_WIDTH_2
//    };
//    
//    /*Create a keyboard and add the new map as USER_1 mode*/
//    lv_keyboard_set_map(objects.kbd_profile, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
//    lv_keyboard_set_mode(objects.kbd_profile, LV_KEYBOARD_MODE_USER_1);
//}

// reset username
static void profile_undo(lv_event_t* e)
{
	lv_textarea_set_text(objects.txt_profile_username, config.user.displayName);
}

// save username
static void profile_save(lv_event_t* e)
{
	const char* newName = lv_textarea_get_text(objects.txt_profile_username);
	if (strlen(newName) > 0)
	{
		strlcpy(config.user.displayName, newName, sizeof(config.user.displayName));
		saveAndApplyBoardConfig(config);
	}
}

// Generic screen loader; requires that the screen to load is passed in as user_data
void load_screen(lv_event_t* e) {
    // Get the screen object from user_data
    lv_obj_t* target_screen = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    if (target_screen) {
        lv_screen_load_anim(target_screen, LV_SCR_LOAD_ANIM_FADE_OUT, 200, 0, false);
    }
}

// Register a button 
static void cb_register(lv_obj_t* button, lv_obj_t* screen)
{
	lv_obj_add_event_cb(button, load_screen, LV_EVENT_PRESSED, screen);
}

// set up callbacks for objects
void setup_cb()
{
	// main UI button callbacks
    cb_register(objects.btn_main_mission, objects.mission);
    cb_register(objects.btn_main_contacts, objects.contacts);
    cb_register(objects.btn_main_info, objects.info);
    cb_register(objects.btn_main_settings, objects.settings);
    cb_register(objects.btn_main_profile, objects.profile);
    cb_register(objects.btn_main_avatar, objects.avatar);
    cb_register(objects.btn_avatar_mission, objects.mission);
    cb_register(objects.btn_avatar_contacts, objects.contacts);
    cb_register(objects.btn_avatar_info, objects.info);
    cb_register(objects.btn_avatar_settings, objects.settings);
    cb_register(objects.btn_avatar_profile, objects.profile);
    cb_register(objects.btn_avatar_main, objects.main);
    cb_register(objects.btn_mission_contacts, objects.contacts);
    cb_register(objects.btn_mission_info, objects.info);
    cb_register(objects.btn_mission_settings, objects.settings);
    cb_register(objects.btn_mission_profile, objects.profile);
    cb_register(objects.btn_mission_main, objects.main);
    cb_register(objects.btn_contacts_mission, objects.mission);
    cb_register(objects.btn_contacts_info, objects.info);
    cb_register(objects.btn_contacts_settings, objects.settings);
    cb_register(objects.btn_contacts_profile, objects.profile);
    cb_register(objects.btn_contacts_main, objects.main);
    cb_register(objects.btn_info_contacts, objects.contacts);
    cb_register(objects.btn_info_mission, objects.mission);
    cb_register(objects.btn_info_settings, objects.settings);
    cb_register(objects.btn_info_profile, objects.profile);
    cb_register(objects.btn_info_main, objects.main);
    cb_register(objects.btn_settings_mission, objects.mission);
    cb_register(objects.btn_settings_contacts, objects.contacts);
    cb_register(objects.btn_settings_info, objects.info);
    cb_register(objects.btn_settings_profile, objects.profile);
    cb_register(objects.btn_settings_main, objects.main);
    //cb_register(objects.btn_profile_mission, objects.mission);
    //cb_register(objects.btn_profile_contacts, objects.contacts);
    //cb_register(objects.btn_profile_info, objects.info);
    //cb_register(objects.btn_profile_settings, objects.settings);
    cb_register(objects.btn_profile_main, objects.main);

    // special UI buttons for loading screens    
    lv_obj_add_event_cb(objects.cnt_badge_tappad, end_badge_mode, LV_EVENT_CLICKED, NULL);

    // avatar screen callbacks
    lv_obj_add_event_cb(objects.roller_avatar_component, roller_changed, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_next, avatar_next, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_avatar_prev, avatar_prev, LV_EVENT_CLICKED, NULL);
    
    lv_obj_add_event_cb(objects.slider_avatar_red, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_green, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_blue, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.slider_avatar_intensity, set_tint, LV_EVENT_VALUE_CHANGED, NULL);
    
	// profile screen callbacks
	lv_obj_add_event_cb(objects.btn_profile_undo, profile_undo, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_profile_save, profile_save, LV_EVENT_CLICKED, NULL);

	// settings screen callbacks
    lv_obj_add_event_cb(objects.check_settings_airplanemode, set_airplane_mode, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.check_settings_badgemode, set_badge_mode, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.btn_settings_delay_down, decrease_delay, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_settings_delay_up, increase_delay, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_settings_usernames, set_usernames, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_settings_gamehosts, set_gamehosts, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.sld_settings_volume, set_volume, LV_EVENT_VALUE_CHANGED, NULL);
    

    roller_changed(NULL); // Initialize the roller
    applyConfig(config); // Apply the config to the UI and the board

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
