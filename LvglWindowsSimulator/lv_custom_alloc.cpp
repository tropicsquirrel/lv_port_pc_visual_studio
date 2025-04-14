/*
Make sure your lv_conf.h has the following edits:

#define LV_USE_STDLIB_MALLOC LV_STDLIB_CUSTOM

#define LV_MEM_POOL_INCLUDE "lv_custom_alloc.h"
#define LV_MEM_POOL_ALLOC   lv_custom_malloc
#define LV_MEM_POOL_FREE    lv_custom_free

#define LV_MEM_SIZE (512U * 1024U)  // adjust based on your avatar/PNG count
*/
#include "lv_custom_alloc.h"
#include "lvgl.h"  // for lv_mem_monitor_t, etc.

void* lv_malloc_core(size_t size) {
    return lv_custom_malloc(size);
}

void lv_free_core(void* ptr) {
    lv_custom_free(ptr);
}

void* lv_realloc_core(void* ptr, size_t new_size) {
    if (!ptr) return lv_custom_malloc(new_size);

    // Reallocate manually
    void* new_ptr = lv_custom_malloc(new_size);
    if (!new_ptr) return NULL;

    // LVGL expects contents to be preserved (doesn't give old size)
    memcpy(new_ptr, ptr, new_size);  // might over-copy — safe in sim

    lv_custom_free(ptr);
    return new_ptr;
}

void lv_mem_init(void) {
    // No-op: PSRAM or malloc has no init
}

void lv_mem_deinit(void) {
    // No-op: nothing to free
}

void lv_mem_monitor_core(lv_mem_monitor_t* mon_p) {
    // Dummy stats for now — simulate "infinite heap" for simulator
    if (mon_p) {
        mon_p->total_size = 8 * 1024 * 1024;
        mon_p->free_cnt = 999;
        mon_p->free_size = 6 * 1024 * 1024;
        mon_p->free_biggest_size = 6 * 1024 * 1024;
        mon_p->used_cnt = 0;
        mon_p->max_used = 2 * 1024 * 1024;
        mon_p->frag_pct = 0;
    }
}

lv_result_t lv_mem_test_core(void) {
    return LV_RESULT_OK;
}

#if defined(_WIN32) || defined(_WIN64)
#include <stdlib.h>

void* lv_custom_malloc(size_t size) {
    return malloc(size);
}

void lv_custom_free(void* ptr) {
    free(ptr);
}
#else
#include "esp_heap_caps.h"

void* lv_custom_malloc(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
}

void lv_custom_free(void* ptr) {
    heap_caps_free(ptr);
}
#endif
