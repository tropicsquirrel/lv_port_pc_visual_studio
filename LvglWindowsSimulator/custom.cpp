#include "custom.h"

void style_objects()
{
    lv_obj_t* tab_buttons = lv_tabview_get_tab_btns(objects.main_tabview);

    // Style for checked (active) tab buttons
    static lv_style_t style_tab_checked;
    lv_style_init(&style_tab_checked);
    lv_style_set_bg_color(&style_tab_checked, lv_color_hex(0x00FF41)); // Green background
    lv_style_set_text_color(&style_tab_checked, lv_color_hex(0xFFFFFF)); // White text

    // Style for the tab indicator (the line under active tab) - using border bottom
    static lv_style_t style_tab_indicator;
    lv_style_init(&style_tab_indicator);
    lv_style_set_border_side(&style_tab_indicator, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_border_color(&style_tab_indicator, lv_color_hex(0x00FF00)); // Green border
    lv_style_set_border_width(&style_tab_indicator, 3); // Thickness of the indicator line

    // Updated each tab button to have the checked style applied when active
    uint32_t tab_count = lv_obj_get_child_count(tab_buttons);
    LV_LOG_WARN("Tab count: %u\n", tab_count);
    for (uint32_t i = 0; i < tab_count; i++)
    {
        lv_obj_t* tab_btn = lv_obj_get_child(tab_buttons, i);
        lv_obj_add_style(tab_btn, &style_tab_checked, LV_STATE_CHECKED);
        lv_obj_add_style(tab_btn, &style_tab_indicator, LV_STATE_CHECKED); // Green border bottom when checked
    }
}
