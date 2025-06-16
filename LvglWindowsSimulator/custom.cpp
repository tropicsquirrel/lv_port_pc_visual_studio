#include <cstdio>
#include "custom.h"
#include <chrono>

#ifdef _WIN32
#include <thread>
#include <atomic>
static std::thread _rthr;
static std::atomic<bool> _rrun{ false };
#else
#include <lvgl.h>
static lv_timer_t* _rtr = nullptr;
#endif

// globals
static void (*_rcb)() = nullptr; //repeating callback function pointer
uint64_t tickDelta = 0;
uint64_t tickThreshold = 100;

int32_t int_ms_since_touch = 0;

extern objects_t objects;                   // LVGL root screens object
extern Config config;                       // Global configuration object
extern std::vector<IDPacket> g_idPackets;   // global ID packet repo
extern ContactManager scanResults;          // global ID packet repo (converts from IDPacket to ContactData)
extern bool badgeMode_triggered;            // global 'is badge mode triggered?' bool
extern lv_display_t* disp;                  // global reference to the LVGL display

// Repeating callback task 
#ifdef _WIN32
static void _thread_loop(uint32_t ms)
{
    while (_rrun)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        if (_rrun && _rcb) _rcb();
    }
}
#endif

// repeat the given callback function every ms milliseconds
void repeat_on(uint32_t ms, void (*cb)())
{
    repeat_off();
    _rcb = cb;
#ifdef _WIN32
    _rrun = true;
    _rthr = std::thread(_thread_loop, ms);
#else
    // no-capture lambda converts to lv_timer_cb_t
    _rtr = lv_timer_create(
        [](lv_timer_t* t) { if (_rcb) _rcb(); },
        ms, nullptr
    );
#endif
}

// stop the repeating callback
void repeat_off()
{
#ifdef _WIN32
    _rrun = false;
    if (_rthr.joinable()) _rthr.join();
#else
    if (_rtr)
    {
        lv_timer_del(_rtr);
        _rtr = nullptr;
    }
#endif
    _rcb = nullptr;
}

char* avatarIDToFilename(int32_t avatarID)
{
    // Convert the avatar ID to a filename
    static char filename[64];
    snprintf(filename, sizeof(filename), "L:/avatars/%d.png", avatarID);
    printf("Avatar ID: %d, Filename: %s\n", avatarID, filename);
    // DEBUG VERSION - CHANGE FOR PRODUCTION
    snprintf(filename, sizeof(filename), "L:/images/16x16.png");
    return filename;
}

// return the name/board ID of a contact, depending on the user's settings
//  Display Names   -> Everyone     = always show username
//                  -> None         = always show board ID
//                  -> Not Blocked  = show DisplayName unless isBlocked
//                  -> Crew         = only show DisplayName if isCrew
char* getName(ContactData* contact)
{
    char retVal[64];

    switch (config.board.displayNameOptions.showNamesFrom)
    {
    case Everyone:
        return contact->displayName;
        break;

    case None:
        snprintf(retVal, sizeof(retVal), "%u", contact->nodeId);
        return retVal;
        break;

    case NotBlocked:
        if (contact->isBlocked)
        {
            snprintf(retVal, sizeof(retVal), "%u", contact->nodeId);
            return retVal;
        }
        else
            return contact->displayName;
        break;

    case Crew:
        return contact->displayName;
        break;

    default:
        snprintf(retVal, sizeof(retVal), "%u", contact->nodeId);
        return retVal;
        break;
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
    case Crew:
        displayUsernames = "Crew";
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
    case Crew:
        gameHosts = "Crew";
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

// load the badge screen and rotate the display
void load_screen_badge()
{
#ifndef _WIN32
    set_display_rotation(disp, LV_DISPLAY_ROTATION_180);
#endif
    lv_screen_load_anim(objects.badge, LV_SCR_LOAD_ANIM_NONE, 200, 0, false);
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

// Game 1 image tests
void game1_image_test(lv_event_t* e)
{
    tickDelta++;

    if (tickDelta < tickThreshold) return; // wait for the next tick

    lv_obj_t* images[15];

    images[0] = objects.img_game1_test1;
    images[1] = objects.img_game1_test2;
    images[2] = objects.img_game1_test3;
    images[3] = objects.img_game1_test4;
    images[4] = objects.img_game1_test5;
    images[5] = objects.img_game1_test6;
    images[6] = objects.img_game1_test7;
    images[7] = objects.img_game1_test8;
    images[8] = objects.img_game1_test9;
    images[9] = objects.img_game1_test10;
    images[10] = objects.img_game1_test11;
    images[11] = objects.img_game1_test12;
    images[12] = objects.img_game1_test13;
    images[13] = objects.img_game1_test14;
    images[14] = objects.img_game1_test15;

    uint32_t x;
    uint32_t y;

    for (int i = 0; i < 15; i++)
    {
        x = (lv_obj_get_x(images[i]) + rand() % 5) % 240;
        y = (lv_obj_get_y(images[i]) + rand() % 5) % 320;
        lv_obj_move_to(images[i], x, y);
    }

    tickDelta = 0; // reset the tick delta
}

void game1Slower(lv_event_t* e)
{
    tickThreshold += 10;
    printf("tickThreshold: %u\n", tickThreshold);
}

void game1Faster(lv_event_t* e)
{
    tickThreshold -= 10;
    printf("tickThreshold: %u\n", tickThreshold);
}

// Generic screen loader; requires that the screen to load is passed in as user_data
void load_screen(lv_event_t* e)
{
    // Get the screen object from user_data
    lv_obj_t* target_screen = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    if (target_screen)
    {
        lv_screen_load_anim(target_screen, LV_SCR_LOAD_ANIM_NONE, 200, 0, false);
    }
}

// Register a button (main UI) to change screens
static void cb_register(lv_obj_t* button, lv_obj_t* screen)
{
    lv_obj_add_event_cb(button, load_screen, LV_EVENT_PRESSED, screen);
}

// convert an lv_event code to a char*
const char* get_lv_event_name(lv_event_code_t event)
{
    switch (event)
    {
    case LV_EVENT_ALL: return "LV_EVENT_ALL";
    case LV_EVENT_PRESSED: return "LV_EVENT_PRESSED";
    case LV_EVENT_PRESSING: return "LV_EVENT_PRESSING";
    case LV_EVENT_PRESS_LOST: return "LV_EVENT_PRESS_LOST";
    case LV_EVENT_SHORT_CLICKED: return "LV_EVENT_SHORT_CLICKED";
    case LV_EVENT_LONG_PRESSED: return "LV_EVENT_LONG_PRESSED";
    case LV_EVENT_LONG_PRESSED_REPEAT: return "LV_EVENT_LONG_PRESSED_REPEAT";
    case LV_EVENT_CLICKED: return "LV_EVENT_CLICKED";
    case LV_EVENT_RELEASED: return "LV_EVENT_RELEASED";
    case LV_EVENT_SCROLL_BEGIN: return "LV_EVENT_SCROLL_BEGIN";
    case LV_EVENT_SCROLL_END: return "LV_EVENT_SCROLL_END";
    case LV_EVENT_SCROLL: return "LV_EVENT_SCROLL";
    case LV_EVENT_GESTURE: return "LV_EVENT_GESTURE";
    case LV_EVENT_KEY: return "LV_EVENT_KEY";
    case LV_EVENT_FOCUSED: return "LV_EVENT_FOCUSED";
    case LV_EVENT_DEFOCUSED: return "LV_EVENT_DEFOCUSED";
    case LV_EVENT_LEAVE: return "LV_EVENT_LEAVE";
    case LV_EVENT_HIT_TEST: return "LV_EVENT_HIT_TEST";
    case LV_EVENT_COVER_CHECK: return "LV_EVENT_COVER_CHECK";
    case LV_EVENT_REFR_EXT_DRAW_SIZE: return "LV_EVENT_REFR_EXT_DRAW_SIZE";
    case LV_EVENT_DRAW_MAIN_BEGIN: return "LV_EVENT_DRAW_MAIN_BEGIN";
    case LV_EVENT_DRAW_MAIN: return "LV_EVENT_DRAW_MAIN";
    case LV_EVENT_DRAW_MAIN_END: return "LV_EVENT_DRAW_MAIN_END";
    case LV_EVENT_DRAW_POST_BEGIN: return "LV_EVENT_DRAW_POST_BEGIN";
    case LV_EVENT_DRAW_POST: return "LV_EVENT_DRAW_POST";
    case LV_EVENT_DRAW_POST_END: return "LV_EVENT_DRAW_POST_END";
    case LV_EVENT_DRAW_TASK_ADDED: return "LV_EVENT_DRAW_TASK_ADDED";
    case LV_EVENT_VALUE_CHANGED: return "LV_EVENT_VALUE_CHANGED";
    case LV_EVENT_INSERT: return "LV_EVENT_INSERT";
    case LV_EVENT_REFRESH: return "LV_EVENT_REFRESH";
    case LV_EVENT_READY: return "LV_EVENT_READY";
    case LV_EVENT_CANCEL: return "LV_EVENT_CANCEL";
    default: return "OTHER_EVENT";
    }
}

// print info about the event; expects string data in the 'user data' field of the event
static void debug_events(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if (event < 23 || event > 31)
    {
        printf("%s: Event: %s\n", static_cast<char*>(lv_event_get_user_data(e)), get_lv_event_name(event));

        if (event == LV_EVENT_CLICKED)
        {
            lv_indev_t* indev = lv_event_get_indev(e); // Get the indev object associated with the event
            if (indev)
            {
                lv_indev_type_t type = lv_indev_get_type(indev); // Get the type of the indev object
                if (type == LV_INDEV_TYPE_POINTER)
                {
                    lv_point_t point;
                    lv_indev_get_point(indev, &point); // Get the point associated with the event
                    printf("Pointer event at (%d, %d)\n", point.x, point.y);
                }
            }
        }
    }
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
    cb_register(objects.btn_host_contacts, objects.contacts);
    cb_register(objects.btn_host_info, objects.info);
    cb_register(objects.btn_host_settings, objects.settings);
    cb_register(objects.btn_host_profile, objects.profile);
    cb_register(objects.btn_host_main, objects.main);
    cb_register(objects.btn_join_contacts, objects.contacts);
    cb_register(objects.btn_join_info, objects.info);
    cb_register(objects.btn_join_settings, objects.settings);
    cb_register(objects.btn_join_profile, objects.profile);
    cb_register(objects.btn_join_main, objects.main);

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

    // mission screen callbacks
    cb_register(objects.btn_mission_host, objects.host);
    cb_register(objects.btn_mission_join, objects.join);

    // host screen callbacks
    lv_dropdown_set_symbol(objects.ddl_host_games, NULL);
    lv_obj_add_event_cb(objects.ddl_host_games, setMissionReadyState, LV_EVENT_VALUE_CHANGED, (void*)1); // 1 = host
    //lv_obj_add_event_cb(objects.btn_host_kick, kickHostedPlayer, LV_EVENT_CLICKED, NULL);
    // populate 4 test players
    for (int i = 0; i < 4; i++)
    {
        char player[16];
        snprintf(player, sizeof(player), "Player %u", i);
        lv_obj_t* button = lv_list_add_button(objects.list_host_players, avatarIDToFilename(1), player);
        lv_obj_set_style_text_font(button, &ui_font_lcars_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_set_style_bg_color(button, lv_color_make(158, 164, 186), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_add_event_cb(button, hostPlayerListClick, LV_EVENT_CLICKED, NULL);
    }

    // join screen callbacks
    lv_dropdown_set_symbol(objects.ddl_join_games, NULL);
    lv_obj_add_event_cb(objects.ddl_join_games, setMissionReadyState, LV_EVENT_VALUE_CHANGED, (void*)2); // 2 = join
    lv_obj_add_event_cb(objects.roller_join_games, setMissionReadyState, LV_EVENT_VALUE_CHANGED, NULL);

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

    // contacts screen callbacks
    lv_obj_add_event_cb(objects.check_contacts_block, checkContactsBlockClick, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.check_contacts_crew, checkContactsCrewClick, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_state(objects.check_contacts_block, LV_STATE_DISABLED);
    lv_obj_add_state(objects.check_contacts_crew, LV_STATE_DISABLED);

    // contact tab button callback & styling
    lv_obj_t* tabview_contacts_buttons = lv_tabview_get_tab_bar(objects.tabview_contacts);
    lv_obj_set_style_bg_color(tabview_contacts_buttons, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
    for (int i = 0; i < lv_tabview_get_tab_count(objects.tabview_contacts); i++)
    {
        lv_obj_t* button = lv_obj_get_child(tabview_contacts_buttons, i);
        lv_obj_set_style_radius(button, 11, LV_PART_MAIN);
        lv_obj_set_style_text_color(button, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
        lv_obj_add_event_cb(button, tabContactsClicked, LV_EVENT_CLICKED, (void*)i); //lets us know what tab has been clicked
    }
    // add contacts
    populate_crew_list(NULL); // Populate the crew list

    // game1
    cb_register(objects.btn_mission_game1, objects.game1);
    lv_obj_add_event_cb(objects.cnt_game1_left, game1Slower, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.cnt_game1_right, game1Faster, LV_EVENT_CLICKED, NULL);
    lv_img_set_src(objects.img_game1_test1, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test2, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test3, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test4, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test5, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test6, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test7, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test8, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test9, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test10, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test11, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test12, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test13, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test14, "L:/images/16x16.png");
    lv_img_set_src(objects.img_game1_test15, "L:/images/16x16.png");

    // other stuff
    roller_changed(NULL); // Initialize the roller
    applyConfig(config); // Apply the config to the UI and the board

    //load an image and display it
    lv_obj_t* obj = lv_image_create(objects.main);
    lv_obj_set_pos(obj, 135, 5);
    lv_obj_set_size(obj, 82, 82);
    lv_image_set_src(obj, background_images[2]);
    printf("image loaded\n");
}

// Add/update IDPackets received to config.contacts or scanResults
void processIDPacket(IDPacket packet)
{
    // convert to a ContactData object
    ContactData* contact = idPacketToContactData(&packet);
    ContactData* foundContact = config.contacts.findContact(contact->nodeId);

    // if the Node ID is in the freinds or isBlocked list, add/update it in config.contacts
    if (foundContact)
    {
        config.contacts.addOrUpdateContact(*contact);
        printf("updated board.contacts with node ID %u\n", contact->nodeId);
        return;
    }

    // the contact wasn't in the config.contacts list
    // add/update it in the scan results list
    scanResults.addOrUpdateContact(*contact);
    printf("added or updated %u in scan results\n", contact->nodeId);
}
