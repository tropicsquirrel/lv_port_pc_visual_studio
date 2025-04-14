/*
Make sure your lv_conf.h has the following edits:

#define LV_USE_STDLIB_MALLOC LV_STDLIB_CUSTOM

#define LV_MEM_POOL_INCLUDE "lv_custom_alloc.h"
#define LV_MEM_POOL_ALLOC   lv_custom_malloc
#define LV_MEM_POOL_FREE    lv_custom_free

#define LV_MEM_SIZE (512U * 1024U)  // adjust based on your avatar/PNG count
*/

#pragma once

#include <stddef.h>
#include <stdbool.h> // for bool
#include "../LvglPlatform/lvgl/src/stdlib/lv_mem.h" // for lv_mem_monitor_t

#ifdef __cplusplus
extern "C" {
#endif

    void* lv_custom_malloc(size_t size);
    void  lv_custom_free(void* ptr);

    void* lv_malloc_core(size_t size);
    void  lv_free_core(void* ptr);
    void* lv_realloc_core(void* ptr, size_t new_size);

    void  lv_mem_init(void);
    void  lv_mem_deinit(void);

    void  lv_mem_monitor_core(lv_mem_monitor_t* mon_p);
    lv_result_t lv_mem_test_core(void);


#ifdef __cplusplus
}
#endif
