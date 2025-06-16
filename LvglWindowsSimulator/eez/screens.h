#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *avatar;
    lv_obj_t *profile;
    lv_obj_t *mission;
    lv_obj_t *host;
    lv_obj_t *join;
    lv_obj_t *game1;
    lv_obj_t *contacts;
    lv_obj_t *settings;
    lv_obj_t *info;
    lv_obj_t *badge;
    lv_obj_t *pip_right;
    lv_obj_t *pip_right_mid;
    lv_obj_t *pip_left_mid;
    lv_obj_t *pip_left;
    lv_obj_t *btn_main_mission;
    lv_obj_t *btn_main_contacts;
    lv_obj_t *btn_main_info;
    lv_obj_t *btn_main_settings;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *btn_main_profile;
    lv_obj_t *lbl_main_random;
    lv_obj_t *flavor_main1;
    lv_obj_t *flavor_main2;
    lv_obj_t *flavor_main3;
    lv_obj_t *flavor_main4;
    lv_obj_t *flavor_main5;
    lv_obj_t *flavor_main6;
    lv_obj_t *flavor_main7;
    lv_obj_t *flavor_side1;
    lv_obj_t *flavor_side2;
    lv_obj_t *flavor_side3;
    lv_obj_t *flavor_side4;
    lv_obj_t *btn_main_avatar;
    lv_obj_t *roller_avatar_component;
    lv_obj_t *btn_avatar_mission;
    lv_obj_t *btn_avatar_contacts;
    lv_obj_t *btn_avatar_info;
    lv_obj_t *btn_avatar_settings;
    lv_obj_t *obj2;
    lv_obj_t *btn_avatar_main;
    lv_obj_t *btn_avatar_profile;
    lv_obj_t *lbl_avatar_random;
    lv_obj_t *img_background;
    lv_obj_t *img_body;
    lv_obj_t *img_clothes;
    lv_obj_t *img_head;
    lv_obj_t *img_mouth;
    lv_obj_t *img_beard;
    lv_obj_t *img_moustache;
    lv_obj_t *img_eye_left;
    lv_obj_t *img_nose;
    lv_obj_t *img_eye_right;
    lv_obj_t *img_hair;
    lv_obj_t *img_ears;
    lv_obj_t *img_ridges;
    lv_obj_t *img_eyebrow_left;
    lv_obj_t *img_eyebrow_right;
    lv_obj_t *img_borg;
    lv_obj_t *img_accessories;
    lv_obj_t *img_antennae;
    lv_obj_t *img_glasses;
    lv_obj_t *img_hands;
    lv_obj_t *slider_avatar_red;
    lv_obj_t *slider_avatar_green;
    lv_obj_t *slider_avatar_blue;
    lv_obj_t *slider_avatar_intensity;
    lv_obj_t *obj3;
    lv_obj_t *btn_avatar_prev;
    lv_obj_t *obj4;
    lv_obj_t *btn_avatar_next;
    lv_obj_t *lbl_avatar_item_id;
    lv_obj_t *btn_profile_profile;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *btn_profile_main;
    lv_obj_t *obj7;
    lv_obj_t *btn_profile_save;
    lv_obj_t *obj8;
    lv_obj_t *btn_profile_undo;
    lv_obj_t *txt_profile_username;
    lv_obj_t *obj9;
    lv_obj_t *btn_mission_mission;
    lv_obj_t *btn_mission_contacts;
    lv_obj_t *btn_mission_info;
    lv_obj_t *btn_mission_settings;
    lv_obj_t *btn_mission_profile;
    lv_obj_t *obj10;
    lv_obj_t *btn_mission_main;
    lv_obj_t *lbl_mission_random;
    lv_obj_t *btn_mission_game1;
    lv_obj_t *btn_mission_host;
    lv_obj_t *btn_mission_join;
    lv_obj_t *btn_host_mission;
    lv_obj_t *btn_host_contacts;
    lv_obj_t *btn_host_info;
    lv_obj_t *btn_host_settings;
    lv_obj_t *btn_host_profile;
    lv_obj_t *obj11;
    lv_obj_t *btn_host_main;
    lv_obj_t *lbl_host_random;
    lv_obj_t *ddl_host_games;
    lv_obj_t *cnt_host_start;
    lv_obj_t *btn_host_start;
    lv_obj_t *list_host_players;
    lv_obj_t *cnt_host_kick;
    lv_obj_t *btn_host_kick;
    lv_obj_t *btn_mission_mission_2;
    lv_obj_t *btn_join_contacts;
    lv_obj_t *btn_join_info;
    lv_obj_t *btn_join_settings;
    lv_obj_t *btn_join_profile;
    lv_obj_t *obj12;
    lv_obj_t *btn_join_main;
    lv_obj_t *lbl_join_random;
    lv_obj_t *cnt_join_ready;
    lv_obj_t *btn_join_ready;
    lv_obj_t *ddl_join_games;
    lv_obj_t *roller_join_games;
    lv_obj_t *cnt_join_ready_1;
    lv_obj_t *btn_join_refresh;
    lv_obj_t *cnt_game1_left;
    lv_obj_t *cnt_game1_right;
    lv_obj_t *img_game1_test1;
    lv_obj_t *img_game1_test2;
    lv_obj_t *img_game1_test3;
    lv_obj_t *img_game1_test4;
    lv_obj_t *img_game1_test5;
    lv_obj_t *img_game1_test6;
    lv_obj_t *img_game1_test7;
    lv_obj_t *img_game1_test8;
    lv_obj_t *img_game1_test9;
    lv_obj_t *img_game1_test10;
    lv_obj_t *img_game1_test11;
    lv_obj_t *img_game1_test12;
    lv_obj_t *img_game1_test13;
    lv_obj_t *img_game1_test14;
    lv_obj_t *img_game1_test15;
    lv_obj_t *btn_contacts_mission;
    lv_obj_t *btn_contacts_contacts;
    lv_obj_t *btn_contacts_info;
    lv_obj_t *btn_contacts_settings;
    lv_obj_t *btn_contacts_profile;
    lv_obj_t *obj13;
    lv_obj_t *btn_contacts_main;
    lv_obj_t *lbl_contacts_random;
    lv_obj_t *img_contacts_avatar;
    lv_obj_t *lbl_contacts_name;
    lv_obj_t *check_contacts_crew;
    lv_obj_t *check_contacts_block;
    lv_obj_t *lbl_contacts_xp;
    lv_obj_t *tabview_contacts;
    lv_obj_t *tab_contacts_scan;
    lv_obj_t *list_contacts_scan;
    lv_obj_t *tab_contacts_crew;
    lv_obj_t *list_contacts_crew;
    lv_obj_t *btn_settings_mission;
    lv_obj_t *btn_settings_contacts;
    lv_obj_t *btn_settings_info;
    lv_obj_t *btn_avatar_settings_1;
    lv_obj_t *obj14;
    lv_obj_t *btn_settings_main;
    lv_obj_t *btn_settings_profile;
    lv_obj_t *lbl_settings_random;
    lv_obj_t *check_settings_airplanemode;
    lv_obj_t *check_settings_badgemode;
    lv_obj_t *btn_settings_delay_down;
    lv_obj_t *lbl_settings_badgedelay;
    lv_obj_t *btn_settings_delay_up;
    lv_obj_t *btn_settings_usernames;
    lv_obj_t *lbl_settings_usernames;
    lv_obj_t *btn_settings_gamehosts;
    lv_obj_t *lbl_settings_gamehosts;
    lv_obj_t *sld_settings_volume;
    lv_obj_t *btn_info_mission;
    lv_obj_t *btn_info_contacts;
    lv_obj_t *btn_info_info;
    lv_obj_t *btn_info_settings;
    lv_obj_t *btn_info_profile;
    lv_obj_t *obj15;
    lv_obj_t *btn_info_main;
    lv_obj_t *lbl_main_random_2;
    lv_obj_t *img_badge_avatar;
    lv_obj_t *bar_badge_game1;
    lv_obj_t *bar_badge_game2;
    lv_obj_t *bar_badge_game3;
    lv_obj_t *bar_badge_game4;
    lv_obj_t *bar_badge_game5;
    lv_obj_t *bar_badge_game6;
    lv_obj_t *bar_badge_game7;
    lv_obj_t *pip_badge_top;
    lv_obj_t *pip_badge_top_mid;
    lv_obj_t *pip_badge_bottom_mid;
    lv_obj_t *pip_badge_bottom;
    lv_obj_t *cnt_badge_tappad;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_AVATAR = 2,
    SCREEN_ID_PROFILE = 3,
    SCREEN_ID_MISSION = 4,
    SCREEN_ID_HOST = 5,
    SCREEN_ID_JOIN = 6,
    SCREEN_ID_GAME1 = 7,
    SCREEN_ID_CONTACTS = 8,
    SCREEN_ID_SETTINGS = 9,
    SCREEN_ID_INFO = 10,
    SCREEN_ID_BADGE = 11,
};

void create_screen_main();
void tick_screen_main();

void create_screen_avatar();
void tick_screen_avatar();

void create_screen_profile();
void tick_screen_profile();

void create_screen_mission();
void tick_screen_mission();

void create_screen_host();
void tick_screen_host();

void create_screen_join();
void tick_screen_join();

void create_screen_game1();
void tick_screen_game1();

void create_screen_contacts();
void tick_screen_contacts();

void create_screen_settings();
void tick_screen_settings();

void create_screen_info();
void tick_screen_info();

void create_screen_badge();
void tick_screen_badge();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/