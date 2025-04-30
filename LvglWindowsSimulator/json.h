#pragma once

#if defined(_WIN32) || defined(_WIN64)
// ArduinoJson needs these Arduino-type stubs on Windows
#include <string>
#include <sstream>

// Fake "String" class for ArduinoJson compatibility
class String : public std::string {
public:
    using std::string::string;
    const char* c_str() const { return std::string::c_str(); }

    // Add write() for ArduinoJson compatibility
    size_t write(uint8_t c) {
        this->push_back(static_cast<char>(c));
        return 1;
    }

    size_t write(const uint8_t* buffer, size_t length) {
        this->append(reinterpret_cast<const char*>(buffer), length);
        return length;
    }
};

// Fake "Stream" class for ArduinoJson compatibility
class Stream {
public:
    virtual int available() { return 0; }
    virtual int read() { return -1; }
    virtual int peek() { return -1; }
    virtual void flush() {}
};

#include "./ArduinoJson/src/ArduinoJson.h"

// Provide strlcpy for Windows
inline void strlcpy(char* dst, const char* src, size_t size) {
    if (size == 0) return;
    std::strncpy(dst, src, size - 1);
    dst[size - 1] = '\0';
}

#else
#include "FreeRTOS.h" //needed?
#include "xtensa/xtruntime-frames.h" //needed?
#include <Arduino.h>
#include <ArduinoJson.h>
//#include <ArduinoJson.hpp>
#endif

#include <vector>
#include <lvgl.h>

enum DisplayOptions
{
    Everyone = 0,   // everyone
    NotBlocked = 1, // all except blocked
    Friends = 2,    // friends only
    None = 3        // no names
};

struct AvatarComponent
{
    char imagePath[256]; // = "L:/wink.png";
    int red; // = 0;
    int green; // = 0;
    int blue; // = 0;
};

struct Avatar
{
    AvatarComponent background;
    AvatarComponent head;
    AvatarComponent clothes;
    AvatarComponent ears;
    AvatarComponent eyes;
    AvatarComponent hair;
    AvatarComponent accessory;
};

struct ContactData
{
    uint32_t nodeId = 0;
    char displayName[64] = "";
    bool isCrew = false;
    bool isFriend = false;
    bool blocked = false;
    bool pendingSave = false;
    uint64_t lastUpdateTime = 0;
    int totalXP = 0;
    Avatar avatar;
};

struct Ranks
{
    int cpo = 100;
    int ensign = 200;
    int ltjg = 400;
    int lt = 800;
    int ltc = 1600;
    int cdr = 3200;
    int capt = 6400;
};

struct BadgeMode
{
    bool enabled = true;
    int delay = 60;
};

struct DisplayNameOptions
{
    DisplayOptions awayMissions = Everyone;
    DisplayOptions acceptInvitesFrom = Everyone;
    DisplayOptions showNamesFrom = Everyone;
};

struct Board
{
    bool airplaneMode = false;
    char ssid[64] = "sheetmetalcon";
    char password[64] = "V9$Jqc8EmDPHVQ3kGf_qgAVmjdrqj@y";
    int port = 5555;
    int channel = 6;
    bool hidden = 0;
    bool introWatched = false;
    int volume = 100;
    BadgeMode badgeMode;
    DisplayNameOptions displayNameOptions;
    Ranks ranks;
};

struct Game
{
    char description[128];
    int XP = 0;
};

// Contact management class
class ContactManager
{
private:
    std::vector<ContactData> contacts;
    size_t indexCache[256];

    size_t findIndex(uint32_t nodeId) const;

public:
    ContactManager();

    // Core operations
    ContactData* findContact(uint32_t nodeId);
    const ContactData* findContact(uint32_t nodeId) const;
    void addOrUpdateContact(const ContactData& contact);
    bool updateContactInfo(uint32_t nodeId, const String& msg, uint32_t meshNodeTime);

    // JSON operations
    void fromJson(JsonObjectConst json);
    void toJson(JsonObject& json) const;

    // Update tracking
    bool hasPendingUpdates() const;
    void clearPendingUpdates();

    // Container operations
    size_t size() const { return contacts.size(); }
    std::vector<ContactData>::iterator begin() { return contacts.begin(); }
    std::vector<ContactData>::iterator end() { return contacts.end(); }
    std::vector<ContactData>::const_iterator begin() const { return contacts.begin(); }
    std::vector<ContactData>::const_iterator end() const { return contacts.end(); }

    // Filtering
    std::vector<ContactData*> getContacts();
    std::vector<ContactData*> getCrew();
    std::vector<ContactData*> getFriends();
};

struct Config
{
    ContactManager contacts;
    std::vector<Game> games;
    ContactData user;
    Board board;
};

bool loadBoardConfig(Config& config, const char* fileName = "L:/default.json");
bool saveBoardConfig(Config& config, const char* fileName = "L:/default.json");
void printConfig(const Config& config, bool verbose = false);
void serialPrintJson(JsonDocument doc);
