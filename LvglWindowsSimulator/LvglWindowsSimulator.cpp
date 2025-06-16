#include <Windows.h>
#include <vector>
#include <algorithm>
#include <cstring>

#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "eez/ui.h"
#include "custom.h"
#include "json.h"
#include "global.hpp"

Config config;                            // Global variable to store configuration
GameState gameState;                      // Global variable to store game state
unsigned long badgeMode_lastActivity = 0; // Last activity timestamp for badge mode
bool badgeMode_triggered = false;         // Flag to indicate if badge mode is triggered
std::vector<IDPacket> g_idPackets;        // Global variable to store ID packets
ContactManager scanResults;

#ifndef _WIN32
portMUX_TYPE muxGameState = portMUX_INITIALIZER_UNLOCKED;
#endif

// moved to json.cpp
//#if defined(_WIN32)
//#include <chrono>
//
//unsigned long millis() {
//    static auto start = std::chrono::steady_clock::now();
//    auto now = std::chrono::steady_clock::now();
//    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
//}
//#endif

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
}


// Print out known ID packets
static void printIDPackets()
{
    printf("-----[%d ID Packets]-----\n", (int)g_idPackets.size());
    for (auto& p : g_idPackets)
    {
        printf("-Board: %d:\n\tName: %s\n\tAvatar: %d\n\tStatus: %d\n\tXP: %d\n\tTime: %d\n", p.boardID, p.displayName, p.avatarID, p.status, p.totalXP, p.timeArrived);
    }
}

// Merge a new packet into g_idPackets:
//  – if avatarID already exists, just bump its time & update fields
//  – otherwise push_back a fresh entry
static void handleIncomingIDPacket(const IDPacket& pkt) {
    int32_t now = millis();
    for (auto& p : g_idPackets) {
        if (p.boardID == pkt.boardID) {
            // update existing
            strncpy(p.displayName, pkt.displayName,
                sizeof(p.displayName) - 1);
            p.displayName[sizeof(p.displayName) - 1] = '\0';
            p.avatarID = pkt.avatarID;
            p.status = pkt.status;
            p.totalXP = pkt.totalXP;
            p.timeArrived = now;
            return;
        }
    }
    // new one
    IDPacket np = pkt;
    np.timeArrived = now;
    g_idPackets.push_back(np);
    //printIDPackets();
    processIDPacket(pkt);
    populate_scan_list(NULL); // Update the UI with the new packet if the contacts screen is active
}

// Remove old packets from g_idPackets
static void cleanupStaleIDPackets() {
    int32_t now = millis();
    auto it = std::remove_if(
        g_idPackets.begin(), g_idPackets.end(),
        [now](const IDPacket& p) {
            return (now - p.timeArrived) >= PLAYER_TIMEOUT;
        });
    g_idPackets.erase(it, g_idPackets.end());
}

// Generate a random IDPacket for testing purposes
static IDPacket generateRandomIDPacket() {
    IDPacket p;
    p.boardID = max(1, rand() % 32);  // max of 32 possible boards, never return 0
    p.avatarID = rand() % 8;  // avatar 1-8
    snprintf(p.displayName, sizeof(p.displayName),
        "P%02d", p.avatarID);
    p.status = static_cast<PlayerStatus>(rand() % 3);
    p.totalXP = rand() % 1000;
    printf("packet generated\n");
    // p.timeArrived will be set by handleIncomingIDPacket
    return p;
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

    srand(millis()); //seed the random number generator

    while (1)
    {
        // variables for simulating incoming ID packets
        static unsigned long lastSim = 0;
        constexpr unsigned long SIM_INTERVAL = 5000;  // every 5 s

        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
        ui_tick();
        badgeMode_timer_loop();

        // Simulate an arrival every SIM_INTERVAL:
        unsigned long now = millis();
        if (now - lastSim >= SIM_INTERVAL) {
            lastSim = now;
            IDPacket p = generateRandomIDPacket();
            handleIncomingIDPacket(p);
        }

        // Then always purge old packets:
        cleanupStaleIDPackets();

        game1_image_test(NULL);
    }

    return 0;
}
