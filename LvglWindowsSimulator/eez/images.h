#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_ui_elements_240x320;
extern const lv_img_dsc_t img_klingon48x48;
extern const lv_img_dsc_t img_ui_elements_240x320_transparent;
extern const lv_img_dsc_t img_lcars_240x320___middle;
extern const lv_img_dsc_t img_lcars_240x320___small_bottom;
extern const lv_img_dsc_t img_lcars_240x320___small_top;
extern const lv_img_dsc_t img_lcars_240x320___top;
extern const lv_img_dsc_t img_ui_element___main_divider;
extern const lv_img_dsc_t img_ui_element___subdivider;
extern const lv_img_dsc_t img_ui_element___icons;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[10];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/