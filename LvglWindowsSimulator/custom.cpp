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

int32_t int_contacts_tab_current = -1;    // what contacts tab is being shown: -1 = none, 0 = scan, 1 = crew
int32_t contactLastClicked;               // the ID of the last contact that was clicked

extern objects_t objects;                   // LVGL root screens object
extern Config config;                       // Global configuration object
extern std::vector<IDPacket> g_idPackets;   // global ID packet repo
extern ContactManager scanResults;          // global ID packet repo (converts from IDPacket to ContactData)
extern bool badgeMode_triggered;            // global 'is badge mode triggered?' bool
extern lv_display_t* disp;                  // global reference to the LVGL display

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

// Repeating callback task 
#ifdef _WIN32
static void _thread_loop(uint32_t ms) {
    while (_rrun) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        if (_rrun && _rcb) _rcb();
    }
}
#endif

// repeat the given callback function every ms milliseconds
void repeat_on(uint32_t ms, void (*cb)()) {
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
void repeat_off() {
#ifdef _WIN32
    _rrun = false;
    if (_rthr.joinable()) _rthr.join();
#else
    if (_rtr) {
        lv_timer_del(_rtr);
        _rtr = nullptr;
    }
#endif
    _rcb = nullptr;
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

static char* avatarIDToFilename(int32_t avatarID)
{
    // Convert the avatar ID to a filename
    static char filename[64];
    snprintf(filename, sizeof(filename), "L:/avatars/%d.png", avatarID);
    printf("Avatar ID: %d, Filename: %s\n", avatarID, filename);
    // DEBUG VERSION - CHANGE FOR PRODUCTION
    snprintf(filename, sizeof(filename), "L:/images/16x16.png");
    return filename;
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

// decrease badge mode delay by 5 seconds, but not below 5 seconds
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

// rotate through usernames you allow to display (all/none/friends/not blocked)
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

// rotate through who is allowed to join your games (all/none/friends/not blocked)
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

// Convert an IDPacket to a ContactData object
ContactData* idPacketToContactData(IDPacket* idPacket)
{
    if (nullptr == idPacket) return nullptr; // No packet found, exit
    ContactData* contact = new ContactData();
    contact->avatar = idPacket->avatarID;
    contact->blocked = false;
    strlcpy(contact->displayName, idPacket->displayName, sizeof(contact->displayName));
    contact->isFriend = false;
    contact->nodeId = idPacket->boardID;
    contact->totalXP = idPacket->totalXP;
    contact->lastUpdateTime = idPacket->timeArrived;
    return contact;
}

void contactListButtonClick(lv_event_t* e)
{
    // clear out the details
    lv_label_set_text(objects.lbl_contacts_name, "Select A Contact");
    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    lv_label_set_text(objects.lbl_contacts_xp, "0");

    //extract the ContactData from the user data of the clicked list entry
    int32_t nodeID = (int32_t)(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
    ContactData* contact = config.contacts.findContact(nodeID);
    if (nullptr == contact)
    {
        contact = scanResults.findContact(nodeID);
        if (nullptr == contact) return; // no contact found in either list; fail silently
    }

    //set the nodeID so we can track who was clicked
    contactLastClicked = nodeID;

    //set display name in the label
    lv_label_set_text(objects.lbl_contacts_name, (const char*)contact->displayName);

    //set the avatar image
    lv_image_set_src(objects.img_contacts_avatar, avatarIDToFilename(contact->nodeId));

    //set the XP
    char str_xp[16];
    snprintf(str_xp, sizeof(str_xp), "%d", contact->totalXP);
    lv_label_set_text(objects.lbl_contacts_xp, str_xp);

    if (contact->isFriend)
    {
        //if the contact is a friend, set the crew checkbox
        lv_obj_add_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    }

    if (contact->blocked)
    {
        //if the contact is blocked, set the blocked checkbox
        lv_obj_add_state(objects.check_contacts_block, LV_STATE_CHECKED);
    }
}

//// show data from the clicked list entry in the contact details section
//void list_scan_click(lv_event_t* e)
//{
//    // clear out the details
//    lv_label_set_text(objects.lbl_contacts_name, "Select A Contact");
//    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
//    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
//    lv_label_set_text(objects.lbl_contacts_xp, "0");
//
//    ////convert the IDPacket to ContactData
//    //ContactData* contactTapped = idPacketToContactData(static_cast<IDPacket*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e))));
//
//    ////extract the IDPacket from the user data of the clicked list entry
//    //if (nullptr == contactTapped) return; // No packet found, exit
//
//    ////set the nodeID so we can track who was clicked
//    //contactLastClicked = contactTapped;
//
//    IDPacket* pkt = static_cast<IDPacket*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
//    if (!pkt) return;
//
//    if (contactLastClicked) delete contactLastClicked;  // prevent leak
//
//    contactLastClicked = new ContactData();
//    contactLastClicked->nodeId = pkt->boardID;
//    contactLastClicked->avatar = pkt->avatarID;
//    contactLastClicked->totalXP = pkt->totalXP;
//    strlcpy(contactLastClicked->displayName, pkt->displayName, sizeof(contactLastClicked->displayName));
//    contactLastClicked->isFriend = false;
//    contactLastClicked->blocked = false;
//    contactLastClicked->lastUpdateTime = 0;
//
//    //set display name in the label
//    lv_label_set_text(objects.lbl_contacts_name, (const char*)contactLastClicked->displayName);
//
//    //set the avatar image
//    lv_image_set_src(objects.img_contacts_avatar, avatarIDToFilename(contactLastClicked->avatar));
//
//    //set the XP
//    char str_xp[16];
//    snprintf(str_xp, sizeof(str_xp), "%d", contactLastClicked->totalXP);
//    lv_label_set_text(objects.lbl_contacts_xp, str_xp);
//
//    //check to see if the contact is a friend or blocked
//    for(int i= 0; i < config.contacts.getContacts().size(); i++)
//    {
//        ContactData* contact = config.contacts.getContacts()[i];
//        if (contact->nodeId == contact->nodeId)
//        {
//            //found the contact, set the friend/blocked status
//            //blocked
//            if (contact->blocked)
//            {
//                lv_obj_add_state(objects.check_contacts_block, LV_STATE_CHECKED);
//            }
//
//            //friend
//            if (contact->isFriend)
//            {
//                lv_obj_add_state(objects.check_contacts_crew, LV_STATE_CHECKED);
//            }
//            return;
//        }
//    }
//}
//
//// show data from the clicked list entry in the contact details section
//void list_crew_click(lv_event_t* e)
//{
//    // clear out the details
//    lv_label_set_text(objects.lbl_contacts_name, "Select A Contact");
//    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
//    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
//    lv_label_set_text(objects.lbl_contacts_xp, "0");
//
//    //extract the IDPacket from the user data of the clicked list entry
//    ContactData* packet = static_cast<ContactData*>(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));
//    if (nullptr == packet) return; // No packet found, exit
//
//    //set the nodeID so we can track who was clicked
//    contactLastClicked = packet;
//
//    //set display name in the label
//    lv_label_set_text(objects.lbl_contacts_name, (const char*)packet->displayName);
//
//    //set the avatar image
//    lv_image_set_src(objects.img_contacts_avatar, avatarIDToFilename(packet->nodeId));
//
//    //set the XP
//    char str_xp[16];
//    snprintf(str_xp, sizeof(str_xp), "%d", packet->totalXP);
//    lv_label_set_text(objects.lbl_contacts_xp, str_xp);
//
//    if(packet->isFriend)
//        {
//        //if the contact is a friend, set the crew checkbox
//        lv_obj_add_state(objects.check_contacts_crew, LV_STATE_CHECKED);
//    }
//
//    if(packet->blocked)
//        {
//        //if the contact is blocked, set the blocked checkbox
//        lv_obj_add_state(objects.check_contacts_block, LV_STATE_CHECKED);
//    }
//}

// populate the crew list with the current crew members
void populate_crew_list(lv_event_t* e)
{
    static std::unordered_map<int32_t, lv_obj_t*> crew_list_buttons;

    std::unordered_map<int32_t, bool> currentIDs;
    for (const auto& [id, _] : crew_list_buttons) {
        currentIDs[id] = false;
    }

    std::vector<ContactData*> contacts = config.contacts.getContacts();

    for (ContactData* contact : contacts)
    {
        currentIDs[contact->nodeId] = true;

        if (crew_list_buttons.count(contact->nodeId) == 0) {
            lv_obj_t* entry = lv_list_add_button(objects.list_contacts_crew, "L:/images/16x16.png", contact->displayName);
            lv_obj_set_user_data(entry, (void*)contact->nodeId); // Store the nodeID to look up later
            lv_obj_add_event_cb(entry, contactListButtonClick, LV_EVENT_CLICKED, NULL);
            crew_list_buttons[contact->nodeId] = entry;
        }
    }

    // Remove any stale entries
    for (const auto& [id, seen] : currentIDs) {
        if (!seen && crew_list_buttons.count(id)) {
            lv_obj_del(crew_list_buttons[id]);
            crew_list_buttons.erase(id);
        }
    }
}

// TODO - something in here is causing invalidation of object user data (you can tell by the massive negative numbers in the XP field)
void populate_scan_list(lv_event_t* e)
{
    // return if the contacts screen is NOT active
    if (lv_obj_get_screen(objects.contacts) != lv_scr_act()) return;

    // declare unordered maps
    static std::unordered_map<int32_t, lv_obj_t*> scan_list_buttons;    // the map is between nodeIDs and pointers to button objects
    std::unordered_map<int32_t, bool> currentIDs;                       // map between nodeID and if that ID has been seen

    // populate scan_list_buttons with all existing buttons in the list
    for (uint32_t i=0; i < lv_obj_get_child_count_by_type(objects.list_contacts_scan, &lv_button_class); i++)
    {
        lv_obj_t* button = lv_obj_get_child_by_type(objects.list_contacts_scan, i, &lv_button_class);
        int32_t id = (uint32_t)lv_obj_get_user_data(button);
        scan_list_buttons[id] = button; // create an id entry for each button
        currentIDs[id] = false;  // create an entry for each id and set each to false (false = 'id does not exist in scanResults')
    }

    // Mark all current IDs as false (not seen this update)
    
    /*for (const auto& [id, _] : scan_list_buttons) {
        currentIDs[id] = false;
    }*/

    // go through each contact in scanResults
    //   update existing buttons with usernames
    //   create new buttons for new contacts
    //   remove buttons for contacts that have aged off
    for (size_t i = 0; i < scanResults.size(); i++)
    {
        // get a pointer to the i-th contact
        ContactData* contact = scanResults.getContacts()[i];
        if (!contact) continue; // just in case - this should never happen
        currentIDs[contact->nodeId] = true; // mark contact as 'exists' (creates the currentIDs[] entry if it doesn't exist)

        // if the contact is NOT listed in the UI yet
        if (scan_list_buttons.count(contact->nodeId) == 0)
        {
            // create the button
            lv_obj_t* entry = lv_list_add_button(objects.list_contacts_scan, "L:/images/16x16.png", contact->displayName);
            lv_obj_set_user_data(entry, (void*)contact->nodeId);
            lv_obj_add_event_cb(entry, contactListButtonClick, LV_EVENT_CLICKED, NULL);
            scan_list_buttons[contact->nodeId] = entry;
            continue;
        }

        // if the contact IS listed in the UI already
        // update their display name
        else
        {
            // make sure the contact still exists
            if (currentIDs[contact->nodeId])
            {
                lv_list_set_button_text(objects.list_contacts_scan, scan_list_buttons[contact->nodeId], contact->displayName);
                continue;
            }
        }

        // if the contact is no longer present in scanResults, remove the button
        for (const auto& [id, seen] : currentIDs) {
            if (!seen && scan_list_buttons.count(id))
            {
                lv_obj_del(scan_list_buttons[id]); // remove the button
                //scan_list_buttons.erase(id);       // not sure we want to delete an entry that the loop depends on...?
            }
        }
    }

    // Add new buttons and mark present ones as seen
    //for (size_t i = 0; i < g_idPackets.size(); ++i) {
    //    IDPacket* pkt = &g_idPackets[i];
    //    currentIDs[pkt->boardID] = true;

    //    if (scan_list_buttons.count(pkt->boardID) == 0) {
    //        lv_obj_t* entry = lv_list_add_button(objects.list_contacts_scan, "L:/images/16x16.png", pkt->displayName);
    //        lv_obj_set_user_data(entry, pkt);  // ✅ SAFE — direct pointer into vector
    //        lv_obj_add_event_cb(entry, list_scan_click, LV_EVENT_CLICKED, NULL);
    //        scan_list_buttons[pkt->boardID] = entry;
    //    }
    //}

    //// Remove buttons whose IDPackets are no longer present
    //for (const auto& [id, seen] : currentIDs) {
    //    if (!seen && scan_list_buttons.count(id)) {
    //        lv_obj_del(scan_list_buttons[id]);
    //        scan_list_buttons.erase(id);
    //    }
    //}
}

// Fires when a tab header on the contacts page is clicked
static void tabContactsClicked(lv_event_t* e)
{
    int_contacts_tab_current = (int32_t)lv_event_get_user_data(e);
}

// Fires when the user clicks 'block' on the contacts page
static void checkContactsBlockClick(lv_event_t* e)
{
    printf("BLock\n");
    //determine if this is on the scan or crew tab
    switch (int_contacts_tab_current)
    {
    case 0: //scan
        //if blocked is now TRUE:
        if (lv_obj_get_state(objects.check_contacts_block) & LV_STATE_CHECKED)
        {
            ContactData* contact = config.contacts.findContact(contactLastClicked);
            if (contact) //they're in the config.contacts list
            {
                contact->blocked = true;
            }
            else //add them to config.contacts
            {
                printf("Contact list size: %d\n", (int)config.contacts.size());
                contact = scanResults.findContact(contactLastClicked);
                if (contact)
                {
                    config.contacts.addOrUpdateContact(*contact);
                    printf("New contact list size: %d\n", (int)config.contacts.size());
                }
                else
                {
                    printf("CONTACT NOT FOUND - NOT ADDED TO CONFIG.CONTACTS (checkContactsBlockClick)\n");
                }
                populate_crew_list(NULL);
            }
            //convert the scan info to a ContactData object
            //set 'blocked' to TRUE
            //call addOrUpdateContact
        }
        //else (blocked is now FALSE), if crew is FALSE
        //remove the contact from ContactManager
        break;
    case 1: //crew

        break;
    default:
        break;
    }
}

static void checkContactsCrewClick(lv_event_t* e)
{

}

// Generic screen loader; requires that the screen to load is passed in as user_data
void load_screen(lv_event_t* e) {
    // Get the screen object from user_data
    lv_obj_t* target_screen = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
    if (target_screen) {
        lv_screen_load_anim(target_screen, LV_SCR_LOAD_ANIM_NONE, 200, 0, false);
    }
}

// Register a button (main UI) to change screens
static void cb_register(lv_obj_t* button, lv_obj_t* screen)
{
    lv_obj_add_event_cb(button, load_screen, LV_EVENT_PRESSED, screen);
}

// convert an lv_event code to a char*
const char* get_lv_event_name(lv_event_code_t event) {
    switch (event) {
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
                if (type == LV_INDEV_TYPE_POINTER) {
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

    // contacts screen callbacks

    lv_obj_add_event_cb(objects.check_contacts_block, checkContactsBlockClick, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(objects.check_contacts_crew, checkContactsCrewClick, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_clear_state(objects.check_contacts_block, LV_STATE_DISABLED);
    lv_obj_clear_state(objects.check_contacts_crew, LV_STATE_DISABLED);

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

    // if the Node ID is in the freinds or blocked list, add/update it in config.contacts
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
