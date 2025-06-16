#include "mission.h"

// used to evaluate if host or join screens should have 'ready' or 'engage' enabled
void setMissionReadyState(lv_event_t* e)
{
    // for the host screen
    if (lv_scr_act() == lv_obj_get_screen(objects.host))
    {
        // if the selected dropdown index is NOT 0 
        if (lv_dropdown_get_selected(objects.ddl_host_games))
        {
            lv_obj_remove_state(objects.btn_host_start, LV_STATE_DISABLED);
            lv_obj_remove_state(objects.cnt_host_start, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(objects.btn_host_start, LV_STATE_DISABLED);
            lv_obj_add_state(objects.cnt_host_start, LV_STATE_DISABLED);
        }
    }

    // for the join screen
    if (lv_scr_act() == lv_obj_get_screen(objects.join))
    {
        char strRoller[64];
        lv_roller_get_selected_str(objects.roller_join_games, strRoller, sizeof(strRoller));

        uint32_t sel = lv_dropdown_get_selected(objects.ddl_join_games);
        sel += strcmp(strRoller, "No Crews Found");

        // if the selected dropdown index is NOT 0 AND the game roller
        if (lv_dropdown_get_selected(objects.ddl_join_games) > 0 &&
            strcmp(strRoller, "No Crews Found"))
        {
            lv_obj_remove_state(objects.btn_join_ready, LV_STATE_DISABLED);
            lv_obj_remove_state(objects.cnt_join_ready, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(objects.btn_join_ready, LV_STATE_DISABLED);
            lv_obj_add_state(objects.cnt_join_ready, LV_STATE_DISABLED);
        }
    }
}

// fires when a player entry on the Host screen is clicked
void hostPlayerListClick(lv_event_t* e)
{
    lv_obj_t* clickedButton = lv_event_get_current_target_obj(e);
    bool buttonCheckState = lv_obj_has_state(clickedButton, LV_STATE_CHECKED);

    // clear the 'checked' state from all entries
    for (int i = 0; i < lv_obj_get_child_count(objects.list_host_players); i++)
    {
        lv_obj_remove_state(lv_obj_get_child(objects.list_host_players, i), LV_STATE_CHECKED);
    }

    // re-check the one that got clicked
    if (buttonCheckState)
        lv_obj_add_state(clickedButton, LV_STATE_CHECKED);
    else
        lv_obj_remove_state(clickedButton, LV_STATE_CHECKED);
}
