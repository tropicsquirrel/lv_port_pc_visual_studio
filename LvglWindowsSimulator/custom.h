#include <lvgl.h>
#include <stdint.h>
#include <unordered_map>

#if defined(_WIN32) || defined(_WIN64)
#include ".\eez\screens.h"
#include ".\eez\fonts.h"
#include ".\eez\vars.h"
#include ".\eez\images.h"
#include "pngs.h"
#include "mp3s.h"
#include "json.h"
#include "global.hpp"
#else
#include "screens.h"
#include "fonts.h"
#include "vars.h"
#include "images.h"
#include "../pngs.h"
#include "../mp3s.h"
#include "../json.h"
#include "../Display_Driver.h"
#include "../Audio_PCM5101.h"
#include "../global.hpp"
#endif

#include "avatar.h"
#include "profile.h"
#include "mission.h"
#include "contacts.h"
#include "settings.h"
#include "info.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    // For some reason these aren't part of the lv_buttonmatrix.h header (lv_buttonmatrix_ctrl_t)
#define LV_BUTTONMATRIX_CTRL_NONE     (lv_buttonmatrix_ctrl_t)0x0000
#define LV_BUTTONMATRIX_CTRL_WIDTH_1  (lv_buttonmatrix_ctrl_t)0x0001
#define LV_BUTTONMATRIX_CTRL_WIDTH_2  (lv_buttonmatrix_ctrl_t)0x0002
#define LV_BUTTONMATRIX_CTRL_WIDTH_3  (lv_buttonmatrix_ctrl_t)0x0003
#define LV_BUTTONMATRIX_CTRL_WIDTH_4  (lv_buttonmatrix_ctrl_t)0x0004
#define LV_BUTTONMATRIX_CTRL_WIDTH_5  (lv_buttonmatrix_ctrl_t)0x0005
#define LV_BUTTONMATRIX_CTRL_WIDTH_6  (lv_buttonmatrix_ctrl_t)0x0006
#define LV_BUTTONMATRIX_CTRL_WIDTH_7  (lv_buttonmatrix_ctrl_t)0x0007
#define LV_BUTTONMATRIX_CTRL_WIDTH_8  (lv_buttonmatrix_ctrl_t)0x0008
#define LV_BUTTONMATRIX_CTRL_WIDTH_9  (lv_buttonmatrix_ctrl_t)0x0009
#define LV_BUTTONMATRIX_CTRL_WIDTH_10 (lv_buttonmatrix_ctrl_t)0x000A
#define LV_BUTTONMATRIX_CTRL_WIDTH_11 (lv_buttonmatrix_ctrl_t)0x000B
#define LV_BUTTONMATRIX_CTRL_WIDTH_12 (lv_buttonmatrix_ctrl_t)0x000C
#define LV_BUTTONMATRIX_CTRL_WIDTH_13 (lv_buttonmatrix_ctrl_t)0x000D
#define LV_BUTTONMATRIX_CTRL_WIDTH_14 (lv_buttonmatrix_ctrl_t)0x000E
#define LV_BUTTONMATRIX_CTRL_WIDTH_15 (lv_buttonmatrix_ctrl_t)0x000F

    void game1_image_test(lv_event_t* e);

    char* avatarIDToFilename(int32_t avatarID);
    bool applyConfig(Config& config);
    bool saveAndApplyBoardConfig(Config& config);

    // repeating task callback start/stop
    void repeat_on(uint32_t ms, void (*cb)());
    void repeat_off();

    void populate_crew_list(lv_event_t* e);
    void populate_scan_list(lv_event_t* e);

    void processIDPacket(IDPacket packet);

    void roller_changed(lv_event_t* e);
    void avatar_next(lv_event_t* e);
    void avatar_prev(lv_event_t* e);
    void load_scroll_color_values(lv_event_t* e);
    void setup_cb(void);
    void update_avatar_images(void);
    void update_item_counter(void);
    //void load_screen_avatar(lv_event_t* e);
    void load_screen_badge();
    bool applyConfig(Config& config);

#ifdef __cplusplus
}
#endif
