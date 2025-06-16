#pragma once

#include "custom.h"

void set_tint(lv_event_t* e);
void roller_changed(lv_event_t* e);
void avatar_next(lv_event_t* e);
void avatar_prev(lv_event_t* e);
void update_avatar_images();
void update_item_counter();
void load_scroll_color_values(lv_event_t* e);

