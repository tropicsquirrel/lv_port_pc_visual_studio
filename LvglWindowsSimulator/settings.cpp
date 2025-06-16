#include "settings.h"

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

// en/disable airplane mode
void set_airplane_mode(lv_event_t* e)
{
    config.board.airplaneMode = (lv_obj_get_state(objects.check_settings_airplanemode) & LV_STATE_CHECKED);
    saveAndApplyBoardConfig(config);
}

// en/disable badge mode
void set_badge_mode(lv_event_t* e)
{
    config.board.badgeMode.enabled = (lv_obj_get_state(objects.check_settings_badgemode) & LV_STATE_CHECKED);
    saveAndApplyBoardConfig(config);
}

// increase badge mode delay by 5 seconds, but not above 900 (15 min)
void increase_delay(lv_event_t* e)
{
    config.board.badgeMode.delay = min(900, config.board.badgeMode.delay + 5);
    saveAndApplyBoardConfig(config);
}

// decrease badge mode delay by 5 seconds, but not below 5 seconds
void decrease_delay(lv_event_t* e)
{
    config.board.badgeMode.delay = max(5, config.board.badgeMode.delay - 5);
    saveAndApplyBoardConfig(config);
}

// rotate through usernames you allow to display (all/none/friends/not blocked)
void set_usernames(lv_event_t* e)
{
    char* usernames = lv_label_get_text(objects.lbl_settings_usernames);
    if (strcmp(usernames, "Everyone") == 0)
        config.board.displayNameOptions.showNamesFrom = NotBlocked;
    else if (strcmp(usernames, "Not Blocked") == 0)
        config.board.displayNameOptions.showNamesFrom = Crew;
    else if (strcmp(usernames, "Crew") == 0)
        config.board.displayNameOptions.showNamesFrom = None;
    else
    {
        config.board.displayNameOptions.showNamesFrom = Everyone;
    }
    saveAndApplyBoardConfig(config);
}

// rotate through who is allowed to join your games (all/none/friends/not blocked)
void set_gamehosts(lv_event_t* e)
{
    char* gameHosts = lv_label_get_text(objects.lbl_settings_gamehosts);
    if (strcmp(gameHosts, "Everyone") == 0)
        config.board.displayNameOptions.gameHosts = NotBlocked;
    else if (strcmp(gameHosts, "Not Blocked") == 0)
        config.board.displayNameOptions.gameHosts = Crew;
    else if (strcmp(gameHosts, "Crew") == 0)
        config.board.displayNameOptions.gameHosts = None;
    else
    {
        config.board.displayNameOptions.gameHosts = Everyone;
    }
    saveAndApplyBoardConfig(config);
}

// change the badge volume
void set_volume(lv_event_t* e)
{
    config.board.volume = lv_slider_get_value(objects.sld_settings_volume);
    saveAndApplyBoardConfig(config);
}
