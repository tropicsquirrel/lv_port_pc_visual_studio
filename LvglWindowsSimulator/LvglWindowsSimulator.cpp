#include <Windows.h>

#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "eez/ui.h"
#include "custom.h"
#include "json.h"
#include "global.hpp"

#include "game.h"
#include "g_game1.h"

Config config;
GameState gameState;
unsigned long badgeMode_lastActivity = 0;
bool badgeMode_triggered = false;

#if defined(_WIN32)
#include <chrono>

unsigned long millis() {
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}
#endif

void badgeMode_timer_loop() {
    if (badgeMode_triggered)
    {
        badgeMode_lastActivity = millis();
        return;
    }

    unsigned long now = millis();
    if (now - badgeMode_lastActivity >= config.board.badgeMode.delay * 1000 && config.board.badgeMode.enabled) {
        badgeMode_triggered = true;
        load_screen_badge();
    }
    //only triggers once
}


int main()
{
    gameState.playerCount = 0;

    lv_init();
    
    /*
     * Optional workaround for users who wants UTF-8 console output.
     * If you don't want that behavior can comment them out.
     *
     * Suggested by jinsc123654.
     */
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int32_t zoom_level = 200;
    bool allow_dpi_override = false;
    bool simulator_mode = true;
    lv_display_t* display = lv_windows_create_display(
        L"LVGL Windows Simulator Display 1",
        240,
        320,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = LoadIconW(
        GetModuleHandleW(NULL),
        MAKEINTRESOURCE(IDI_LVGL_WINDOWS));
    if (icon_handle)
    {
        SendMessageW(
            window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        SendMessageW(
            window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    lv_indev_t* keypad_indev = lv_windows_acquire_keypad_indev(display);
    if (!keypad_indev)
    {
        return -1;
    }

    lv_indev_t* encoder_indev = lv_windows_acquire_encoder_indev(display);
    if (!encoder_indev)
    {
        return -1;
    }

    // capture mouse events
    //lv_indev_set_read_cb(pointer_indev, read_touchpad); //gets input but seems to block the UI... no bueno

    ui_init();
    //lv_demo_widgets();
    //lv_demo_benchmark();

    // Load JSON configuration
    
    if (loadConfig(config))
    {
        printf("Config loaded successfully\n");
        if (config.contacts.size() > 0)
        {
            printf("Loaded %zu contacts\n", config.contacts.size());
        }
    }
    else
    {
        printf("Error loading config, using defaults\n");
    }
    printConfig(config, false);  // Set to true for verbose output

    setup_cb();

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
        ui_tick();
        badgeMode_timer_loop();

        if(nullptr != game_master && game_master->setup == true)
            game_master->Update();
    }

    return 0;
}
