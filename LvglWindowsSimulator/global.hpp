#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <lvgl.h>

    constexpr int32_t PLAYER_TIMEOUT = 30000; // 30 seconds;

    /// <summary> Represents the possible states a player can be in </summary>
    enum PlayerStatus
    {
        Idle = 0,       // Connected to the mesh, not in a game
        Hosting = 1,    // In lobby, hosting
        InLobby = 2,    // In lobby (not hosting)
        Ready = 3,      // In lobby, ready to play
        InGame = 4,     // Currently playing
        Offline = 5     // Disconnected; assigned on-client to players who we haven't seen packets from in PLAYER_TIMEOUT ms
    };

    /// <summary> Used to accept or reject a join request. </summary>
    enum JoinRequest
    {
        Request = 0,    // Requesting to join a game
        Accept = 1,     // Accept the join request
        Reject = 2      // Reject the join request
    };

    /// <summary> Contains information about current game we're in (if any). </summary>
    struct GameState
    {
        int32_t sessionID;               // game session ID
        int32_t playerCount;             // number of players in the game
        int32_t playerIDs[4];            // IDs fo other players
        int32_t avatarIDs[4];            // avatar IDs of other players
        PlayerStatus playerStatus[4];    // status of other players
        int32_t scores[4];               // score for other players (percentage)
        int32_t timeSinceLastMessage[4]; // time since last message from each player
    };

    // Set up automatic critical sections for mods to a GameState object
    // Usage:
    // withGameState([](GameState& s) {s.totalXP += 10;});

//#if defined(_WIN32) || defined(_WIN64)
//    // On Windows, no real concurrency — just call directly
//    template <typename Func>
//    void withGameState(Func&& func) {
//        func(gameState);
//    }
//#else
//#include "freertos/FreeRTOS.h"
//#include "esp32/rom/ets_sys.h"
//#include "esp_attr.h"
//
//    extern portMUX_TYPE muxGameState;
//
//    template <typename Func>
//    void withGameState(Func&& func) {
//        taskENTER_CRITICAL(&muxGameState);
//        func(gameState);
//        taskEXIT_CRITICAL(&muxGameState);
//    }
//#endif

    /// <summary> Used to advertise a game, admit/reject players from the lobby and show ready status. Unicast. </summary>
    struct SessionPacket
    {
        int32_t sessionID;      // game session ID
        PlayerStatus status;    // player status
        JoinRequest request;    // join request
    };

    /// <summary> Packet broadcast from each client regularly. Broadcast. </summary>
    struct IDPacket
    {
        int32_t boardID;        // board ID
        int32_t avatarID;       // avatar ID
        char displayName[64];   // display name
        PlayerStatus status;    // player status
        int32_t timeArrived;    // time the packet arrived
        int32_t totalXP;        // total XP
    };

#ifdef __cplusplus
}
#endif
