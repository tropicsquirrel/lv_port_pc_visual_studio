#include "json.h"

const char* DEFAULT_GAME_NAMES[] = {
    "Assimilation", "DNS", "Crypto", "AntiSocial",
    "QingTheory", "IoTConnect", "BotOrNot"
};
const size_t NUM_DEFAULT_GAMES = sizeof(DEFAULT_GAME_NAMES) / sizeof(DEFAULT_GAME_NAMES[0]);


// ContactManager implementation
ContactManager::ContactManager()
{
    std::fill_n(indexCache, 256, 0);
}

size_t ContactManager::findIndex(uint32_t nodeId) const
{
    if (nodeId < 256 && indexCache[nodeId] < contacts.size() &&
        contacts[indexCache[nodeId]].nodeId == nodeId)
    {
        return indexCache[nodeId];
    }

    auto it = std::find_if(contacts.begin(), contacts.end(),
        [nodeId](const ContactData& c) { return c.nodeId == nodeId; });

    if (it != contacts.end())
    {
        size_t index = std::distance(contacts.begin(), it);
        if (nodeId < 256)
        {
            const_cast<size_t*>(indexCache)[nodeId] = index;
        }
        return index;
    }
    return contacts.size();
}

ContactData* ContactManager::findContact(uint32_t nodeId)
{
    size_t index = findIndex(nodeId);
    return index < contacts.size() ? &contacts[index] : nullptr;
}

const ContactData* ContactManager::findContact(uint32_t nodeId) const
{
    size_t index = findIndex(nodeId);
    return index < contacts.size() ? &contacts[index] : nullptr;
}

void ContactManager::addOrUpdateContact(const ContactData& contact)
{
    size_t index = findIndex(contact.nodeId);
    if (index < contacts.size())
    {
        contacts[index] = contact;
    }
    else
    {
        contacts.push_back(contact);
        if (contact.nodeId < 256)
        {
            indexCache[contact.nodeId] = contacts.size() - 1;
        }
    }
}

// Update contact information from a JSON message (only Self Packets)
bool ContactManager::updateContactInfo(uint32_t nodeId, const String& msg, uint32_t meshNodeTime)
{
    ContactData* contact = findContact(nodeId);
    if (!contact)
    {
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, msg);
    if (error)
    {
        return false;
    }

    if (doc["DisplayName"].is<String>())
    {
        strlcpy(contact->displayName, doc["DisplayName"], sizeof(contact->displayName));
    }
    if (doc["TotalXP"].is<int>())
    {
        contact->totalXP = doc["TotalXP"];
    }

    contact->pendingSave = true;
    contact->lastUpdateTime = meshNodeTime;
    return true;
}

void ContactManager::fromJson(JsonObjectConst json)
{
    contacts.clear();
    std::fill_n(indexCache, 256, 0);

    for (const JsonPairConst kv : json)
    {
        ContactData contact;
        contact.nodeId = strtoul(kv.key().c_str(), nullptr, 10);

        JsonObjectConst data = kv.value().as<JsonObjectConst>();
        strlcpy(contact.displayName, data["DisplayName"] | "", sizeof(contact.displayName));
        contact.isFriend = data["Friend"] | false;
        contact.blocked = data["Blocked"] | false;
        contact.totalXP = data["TotalXP"] | 0;
        contact.avatar = data["Avatar"] | 0;

        addOrUpdateContact(contact);
    }
}

void ContactManager::toJson(JsonObject& json) const
{
    for (std::vector<ContactData>::const_iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        const ContactData& contact = *it;
        if (contact.pendingSave)
        {
            char nodeIdStr[16];
            snprintf(nodeIdStr, sizeof(nodeIdStr), "%u", contact.nodeId);

            //JsonObject contactObj = json.createNestedObject(nodeIdStr);
            JsonObject contactObj = json[nodeIdStr];
            contactObj["DisplayName"] = contact.displayName;
            contactObj["Friend"] = contact.isFriend;
            contactObj["Blocked"] = contact.blocked;
            contactObj["TotalXP"] = contact.totalXP;
            contactObj["Avatar"] = contact.avatar;
        }
    }
}

// Get friends
std::vector<ContactData*> ContactManager::getFriends()
{
    std::vector<ContactData*> result;
    for (std::vector<ContactData>::iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        ContactData& contact = *it;
        if (contact.isFriend)
        {
            result.push_back(&contact);
        }
    }
    return result;
}

bool ContactManager::hasPendingUpdates() const
{
    for (std::vector<ContactData>::const_iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it->pendingSave) return true;
    }
    return false;
}

void ContactManager::clearPendingUpdates()
{
    for (std::vector<ContactData>::iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        ContactData& contact = *it;
        contact.pendingSave = false;
    }
}

std::vector<ContactData*> ContactManager::getContacts()
{
    std::vector<ContactData*> result;
    for (std::vector<ContactData>::iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        ContactData& contact = *it;
        //if (contact.isFriend)
        //{
            result.push_back(&contact);
        //}
    }
    return result;
}

// Function to serialize Config into JSON document
static void serializeConfig(const Config& config, JsonDocument& doc)
{
    //JsonObject root = doc.to<JsonObject>();

    // Serialize contacts
    //JsonObject contacts = root.createNestedObject("Contacts");
    JsonObject contacts = doc["Contacts"];
    config.contacts.toJson(contacts);

    // Serialize games
    //JsonObject games = root.createNestedObject("Games");
    JsonObject games = doc["Games"];
    for (const Game& game : config.games)
    {
        //JsonObject gameObj = games.createNestedObject(game.description);
        JsonObject gameObj = games[game.description];
        gameObj["XP"] = game.XP;
    }

    String temp;
    serializeJsonPretty(doc, temp); // Print the JSON document to Serial for debugging
    printf("JSON Output:\n%s\n", temp.c_str());
    // Serialize user
    //JsonObject user = root.createNestedObject("User");
    JsonObject user = doc["User"];
    user["DisplayName"] = config.user.displayName;
    user["TotalXP"] = config.user.totalXP;
    //JsonObject userAvatar = user.createNestedObject("Avatar");
    user["Avatar"] = config.user.avatar;

    // Serialize board
    //JsonObject board = root.createNestedObject("Board");
    JsonObject board = doc["Board"];
    board["AirplaneMode"] = config.board.airplaneMode;
    board["IntroWatched"] = config.board.introWatched;
    board["Volume"] = config.board.volume;
    board["Ssid"] = config.board.ssid;
    board["Password"] = config.board.password;
    board["Port"] = config.board.port;
    board["Channel"] = config.board.channel;
    board["Hidden"] = config.board.hidden;

    //JsonObject badgeMode = board.createNestedObject("BadgeMode");
    JsonObject badgeMode = board["BadgeMode"];
    badgeMode["Enabled"] = config.board.badgeMode.enabled;
    badgeMode["Delay"] = config.board.badgeMode.delay;

    //JsonObject displayNameOptions = board.createNestedObject("DisplayNameOptions");
    JsonObject displayNameOptions = board["DisplayNameOptions"];
    displayNameOptions["AwayMissions"] = config.board.displayNameOptions.gameHosts;
    displayNameOptions["ShowNamesFrom"] = config.board.displayNameOptions.showNamesFrom;

    //JsonObject ranks = board.createNestedObject("Ranks");
    JsonObject ranks = board["Ranks"];
    ranks["CPO"] = config.board.ranks.cpo;
    ranks["Ensign"] = config.board.ranks.ensign;
    ranks["LTJG"] = config.board.ranks.ltjg;
    ranks["LT"] = config.board.ranks.lt;
    ranks["LTC"] = config.board.ranks.ltc;
    ranks["CDR"] = config.board.ranks.cdr;
    ranks["CAPT"] = config.board.ranks.capt;
}

// Helper function to convert string to display option
static DisplayOptions stringToDisplayOption(const char* str)
{
    if (strcmp(str, "Everyone") == 0) return Everyone;
    if (strcmp(str, "NotBlocked") == 0) return NotBlocked;
    if (strcmp(str, "Friends") == 0) return Friends;
    if (strcmp(str, "None") == 0) return None;
    return Everyone;  // default
}

//static bool loadConfig(Config& config, const JsonDocument& doc)
//{
//    //serialPrintJson(doc); // Print the JSON document to Serial for debugging
//
//    // Load contacts
//    LV_LOG_INFO("Loading contacts...");
//    JsonObjectConst contactsObj = doc["Contacts"].as<JsonObjectConst>();
//    if (!contactsObj.isNull())
//    {
//        config.contacts.fromJson(contactsObj);
//    }
//    else
//    {
//        LV_LOG_ERROR("Contacts key not found!");
//    }
//
//    // Load games
//    LV_LOG_INFO("Loading Games...");
//    JsonObjectConst games = doc["Games"].as<JsonObjectConst>();
//
//    // Add all games that exist in JSON
//    for (JsonPairConst kv : games) {
//        Game g;
//        strlcpy(g.description, kv.key().c_str(), sizeof(g.description));
//        g.XP = kv.value()["XP"] | 0;
//        config.games.push_back(g);
//    }
//
//    // Ensure all required game names exist
//    for (size_t i = 0; i < NUM_DEFAULT_GAMES; ++i) {
//        const char* name = DEFAULT_GAME_NAMES[i];
//        auto it = std::find_if(config.games.begin(), config.games.end(), [name](const Game& g) {
//            return strcmp(g.description, name) == 0;
//            });
//        if (it == config.games.end()) {
//            Game g;
//            strlcpy(g.description, name, sizeof(g.description));
//            g.XP = 0;
//            config.games.push_back(g);
//        }
//    }
//
//    // Load user
//    JsonObjectConst userObj = doc["User"].as<JsonObjectConst>();
//    if (userObj)
//    {
//        strlcpy(config.user.displayName, userObj["DisplayName"] | "", sizeof(config.user.displayName));
//        config.user.totalXP = userObj["TotalXP"] | 0;
//        config.user.avatar = userObj["Avatar"] | 0;
//    }
//    else
//    {
//        LV_LOG_ERROR("User key not found!");
//    }
//
//    // Load board settings
//    JsonObjectConst boardObj = doc["Board"].as<JsonObjectConst>();
//    if (boardObj)
//    {
//        config.board.airplaneMode = boardObj["AirplaneMode"] | false;
//        config.board.introWatched = boardObj["IntroWatched"] | false;
//        config.board.volume = boardObj["Volume"] | 0;
//        strlcpy(config.board.ssid, boardObj["Ssid"] | "sheetmetalcon", sizeof(config.board.ssid));
//        strlcpy(config.board.password, boardObj["Password"] | "default_password", sizeof(config.board.password));
//        config.board.port = boardObj["Port"] | 5555;
//        config.board.channel = boardObj["Channel"] | 6;
//        config.board.hidden = boardObj["Hidden"] | false;
//
//        JsonObjectConst badgeModeObj = boardObj["BadgeMode"].as<JsonObjectConst>();
//        config.board.badgeMode.enabled = badgeModeObj["Enabled"] | false;
//        config.board.badgeMode.delay = badgeModeObj["Delay"] | 0;
//
//        JsonObjectConst displayNameOptionsObj = boardObj["DisplayNameOptions"].as<JsonObjectConst>();
//        config.board.displayNameOptions.awayMissions = stringToDisplayOption(displayNameOptionsObj["AwayMissions"] | "Everyone");
//        config.board.displayNameOptions.acceptInvitesFrom = stringToDisplayOption(displayNameOptionsObj["AcceptInvitesFrom"] | "Everyone");
//        config.board.displayNameOptions.showNamesFrom = stringToDisplayOption(displayNameOptionsObj["ShowNamesFrom"] | "Everyone");
//
//        JsonObjectConst ranksObj = boardObj["Ranks"].as<JsonObjectConst>();
//        config.board.ranks.cpo = ranksObj["CPO"] | 0;
//        config.board.ranks.ensign = ranksObj["Ensign"] | 0;
//        config.board.ranks.ltjg = ranksObj["LTJG"] | 0;
//        config.board.ranks.lt = ranksObj["LT"] | 0;
//        config.board.ranks.ltc = ranksObj["LTC"] | 0;
//        config.board.ranks.cdr = ranksObj["CDR"] | 0;
//        config.board.ranks.capt = ranksObj["CAPT"] | 0;
//    }
//    else
//    {
//        LV_LOG_ERROR("Board key not found!");
//    }
//
//    return true;
//}

// Read in a JSON document and return it (or an empty document)
static JsonDocument readJson(const char* filename)
{
    JsonDocument doc;  // Adjust size based on your needs
    LV_LOG_INFO("Starting read:");
    LV_LOG_INFO(filename);
    lv_fs_file_t f;
    lv_fs_res_t res = lv_fs_open(&f, filename, LV_FS_MODE_RD);
    if (res != LV_FS_RES_OK)
    {
        LV_LOG_ERROR("Failed to open JSON file: %d", (int)res);
        return doc;
    }
    LV_LOG_INFO("JSON open");
    // Read file contents in chunks
    const size_t CHUNK_SIZE = 256;
    char chunk[CHUNK_SIZE];
    String jsonString;

    while (true)
    {
        uint32_t br;  // bytes read
        res = lv_fs_read(&f, chunk, CHUNK_SIZE - 1, &br);
        if (res != LV_FS_RES_OK)
        {
            LV_LOG_ERROR("Failed to read JSON file: %d", (int)res);
            lv_fs_close(&f);
            return doc;
        }

        if (br == 0) break;  // End of file

        LV_LOG_TRACE("Chunk:");
        LV_LOG_TRACE(chunk);
        chunk[br] = '\0';  // Null terminate this chunk
        jsonString += chunk;

        if (br < CHUNK_SIZE - 1) break;  // Partial read means we hit EOF
    }
    LV_LOG_INFO("Done reading JSON");
    // Close the file
    lv_fs_close(&f);
    LV_LOG_INFO("JSON file closed");
    // Deserialize the JSON
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error)
    {
        LV_LOG_ERROR("deserializeJson() failed: ");
        LV_LOG_ERROR(error.c_str());
        return doc;
    }

    if (doc.overflowed())
    {
        LV_LOG_ERROR("deserializeJson() failed: ");
        LV_LOG_ERROR("Not enough memory to store entire JSON document");
        return doc;
    }

    LV_LOG_INFO("JSON deserialized");
    return doc;
}

static bool writeJson(const char* fileName, const JsonDocument& doc)
{
    lv_fs_file_t f;
    lv_fs_res_t res = lv_fs_open(&f, fileName, LV_FS_MODE_WR);
    if (res != LV_FS_RES_OK)
    {
        LV_LOG_ERROR("Failed to open file for writing. Error: %d", (int)res);
        return false;
    }

    // First serialize to String to get the size
    String jsonString;
    serializeJson(doc, jsonString);

    // Write the string to file
    uint32_t bw;  // bytes written
    res = lv_fs_write(&f, jsonString.c_str(), jsonString.length(), &bw);
    if (res != LV_FS_RES_OK || bw != (uint32_t)jsonString.length())
    {
        LV_LOG_ERROR("Failed to write file. Error: %d", (int)res);
        return false;
    }

    if (&f)
    {
        res = lv_fs_close(&f);
    }

    if (res != LV_FS_RES_OK)
    {
        LV_LOG_ERROR("Failed to close file. Error: %d", (int)res);
        return false;
    }

    return true;
}

// Print a JSON document to the serial port
void serialPrintJson(JsonDocument doc)
{
    // Windows
#if defined(_WIN32) || defined(_WIN64)
    String jsonString;
    serializeJsonPretty(doc, jsonString);
    printf("%s\n", jsonString.c_str());
    // Arduino
#else
    Serial.begin(115200);
    serializeJsonPretty(doc, Serial);
#endif
}

// debug: converts a displayOption (int) to a string
static const char* displayOptionToString(int option)
{
    switch (option)
    {
    case Everyone: return "Everyone";
    case NotBlocked: return "NotBlocked";
    case Friends: return "Friends";
    case None: return "None";
    default: return "Unknown";
    }
}

// debug: prints a Config{} struct to the serial port
static void printConfig(const Config& config)
{
    printf("=== Config Dump ===\n");


    printf("\n=== End Config Dump ===");
}

// Test all json functions
static bool jsonTest(const char* inFile, const char* outFile)
{
    return true;
}

static void printContactData(const ContactData& contact, bool verbose = false, int indent = 0)
{
    String spaces(indent, ' ');
    printf("%sContact NodeID: %u\n", spaces.c_str(), contact.nodeId);
    printf("%s  DisplayName: %s\n", spaces.c_str(), contact.displayName);
    printf("%s  Roles: %s%s\n", spaces.c_str(),"x",
        contact.isFriend ? "Contact " : "");
    printf("%s  Status: %s%s\n", spaces.c_str(),
        contact.blocked ? "Blocked " : "",
        contact.pendingSave ? "PendingSave " : "");
    printf("%s  LastUpdate: %llu\n", spaces.c_str(), contact.lastUpdateTime);
    printf("%s  TotalXP: %d\n", spaces.c_str(), contact.totalXP);
    printf("%s  Avatar: %d\n", spaces.c_str(), contact.avatar);

}

static void printContactManager(const ContactManager& manager, bool verbose = false)
{
    printf("\n=== Contact Manager Debug Dump ===");

    // Print statistics
    size_t totalContacts = 0;
    size_t totalCrew = 0;
    size_t blockedContacts = 0;
    size_t pendingUpdates = 0;

    for (const auto& contact : manager)
    {
        if (contact.isFriend) totalContacts++;
        if (contact.blocked) blockedContacts++;
        if (contact.pendingSave) pendingUpdates++;
    }

    printf("\nStatistics:");
    printf("  Total Entries: %zu\n", manager.size());
    printf("  Contacts: %zu\n", totalContacts);
    printf("  Crew Members: %zu\n", totalCrew);
    printf("  Blocked: %zu\n", blockedContacts);
    printf("  Pending Updates: %zu\n", pendingUpdates);

    // Print all contacts
    printf("\nDetailed Contact List:\n");
    for (const auto& contact : manager)
    {
        printContactData(contact, verbose);
        printf("\n"); // Add spacing between contacts
    }

    // Print specific lists if requested
    if (verbose)
    {
        printf("\nBlocked Contacts:");
        for (const auto& contact : manager)
        {
            if (contact.blocked)
            {
                printContactData(contact, false, 2);
            }
        }

        printf("\nPending Updates:");
        for (const auto& contact : manager)
        {
            if (contact.pendingSave)
            {
                printContactData(contact, false, 2);
            }
        }
    }

    printf("\n=== End Contact Manager Dump ===\n");
}

void printConfig(const Config& config, bool verbose)
{
    printf("\n====== Configuration Debug Dump ======");

    // Print Contacts
    printf("\n--- Contact Manager ---\n");
    printContactManager(config.contacts, verbose);

    // Print Games
    printf("\n--- Games ---\n");
    for (const auto& game : config.games)
    {
        printf("  %s: %d XP\n", game.description, game.XP);
    }

    // Print User
    printf("\n--- User ---\n");
    printf("  DisplayName: %s\n", config.user.displayName);
    printf("  TotalXP: %d\n", config.user.totalXP);
    printf("  Avatar: %d\n", config.user.avatar);

    // Print Board Settings
    printf("\n--- Board Settings ---\n");
    printf("  AirplaneMode: %s\n", config.board.airplaneMode ? "true" : "false");
    printf("  IntroWatched: %s\n", config.board.introWatched ? "true" : "false");
    printf("  Volume: %d\n", config.board.volume);
    printf("  SSID: %s\n", config.board.ssid);
    printf("  Port: %d\n", config.board.port);
    printf("  Channel: %d\n", config.board.channel);
    printf("  Hidden: %s\n", config.board.hidden ? "true" : "false");

    printf("  Badge Mode:");
    printf("    Enabled: %s\n", config.board.badgeMode.enabled ? "true" : "false");
    printf("    Delay: %d\n", config.board.badgeMode.delay);

    printf("  Display Name Options:");
    printf("    Away Missions: %d\n", config.board.displayNameOptions.gameHosts);
    printf("    Show Names From: %d\n", config.board.displayNameOptions.showNamesFrom);

    printf("  Ranks:");
    printf("    CPO: %d\n", config.board.ranks.cpo);
    printf("    Ensign: %d\n", config.board.ranks.ensign);
    printf("    LTJG: %d\n", config.board.ranks.ltjg);
    printf("    LT: %d\n", config.board.ranks.lt);
    printf("    LTC: %d\n", config.board.ranks.ltc);
    printf("    CDR: %d\n", config.board.ranks.cdr);
    printf("    CAPT: %d\n", config.board.ranks.capt);

    printf("\n====== End Configuration Dump ======\n");
}

//bool loadBoardConfig(Config& config, const char* fileName)
//{
//    JsonDocument defaultJson;
//
//    //load fileName
//    defaultJson = readJson(fileName);
//    if (defaultJson.size() < 1)
//    {
//        LV_LOG_ERROR("No records in JSON config: %s. Using default config.", fileName);
//        config = Config(); //ensure we reset to defaults
//        return true;
//    }
//
//    //parse fileName
//    if (!loadConfig(config, defaultJson))
//    {
//        LV_LOG_ERROR("Error loading JSON config");
//        return false;
//    }
//
//    LV_LOG_INFO("Board config successfully loaded.");
//    //printConfig(config);
//    return true;
//}

// Function to load configuration from a JSON file
bool loadConfig(Config& cfg, const char* filename) {
    lv_fs_file_t file;
    if (lv_fs_open(&file, filename, LV_FS_MODE_RD) != LV_FS_RES_OK) {
        LV_LOG_ERROR("Failed to open file for reading");
        return false;
    }

    String jsonString;
    char buffer[256];
    uint32_t read = 0;

    while (lv_fs_read(&file, buffer, sizeof(buffer) - 1, &read) == LV_FS_RES_OK && read > 0) {
        buffer[read] = '\0';
        jsonString += buffer;
    }
    lv_fs_close(&file);

    JsonDocument doc;

    if (deserializeJson(doc, jsonString)) {
        LV_LOG_ERROR("Failed to parse JSON config. Loading defaults.");
        doc.clear(); // Clear the document & try again
    }

    JsonObject user = doc["User"];
    strlcpy(cfg.user.displayName, user["DisplayName"] | "Queue Who", sizeof(cfg.user.displayName));
    cfg.user.totalXP = user["TotalXP"] | 0;
    cfg.user.avatar = user["Avatar"] | 0; 

    JsonObject contacts = doc["Contacts"];
    for (JsonPair kv : contacts) {
        ContactData c;
        c.nodeId = strtoul(kv.key().c_str(), nullptr, 10);
        JsonObject entry = kv.value().as<JsonObject>();
        strlcpy(c.displayName, entry["DisplayName"] | "", sizeof(c.displayName));
        c.isFriend = entry["Friend"] | false;
        c.blocked = entry["Blocked"] | false;
        c.totalXP = entry["TotalXP"] | 0;
        c.avatar = entry["Avatar"] | 0; 
        cfg.contacts.addOrUpdateContact(c);
    }

    cfg.games.clear();
    JsonObject games = doc["Games"];

    // Add all games that exist in JSON
    for (JsonPair kv : games) {
        Game g;
        strlcpy(g.description, kv.key().c_str(), sizeof(g.description));
        g.XP = kv.value()["XP"] | 0;
        cfg.games.push_back(g);
    }

    // Ensure all required game names exist
    for (size_t i = 0; i < NUM_DEFAULT_GAMES; ++i) {
        const char* name = DEFAULT_GAME_NAMES[i];
        auto it = std::find_if(cfg.games.begin(), cfg.games.end(), [name](const Game& g) {
            return strcmp(g.description, name) == 0;
            });
        if (it == cfg.games.end()) {
            Game g;
            strlcpy(g.description, name, sizeof(g.description));
            g.XP = 0;
            cfg.games.push_back(g);
        }
    }

    JsonObject board = doc["Board"];
    cfg.board.airplaneMode = board["AirplaneMode"] | false;
    cfg.board.introWatched = board["IntroWatched"] | false;
    cfg.board.volume = board["Volume"] | 100;
    strlcpy(cfg.board.ssid, board["Ssid"] | "sheetmetalcon", sizeof(cfg.board.ssid));
    strlcpy(cfg.board.password, board["Password"] | "V9$Jqc8EmDPHVQ3kGf_qgAVmjdrqj@y", sizeof(cfg.board.password));
    cfg.board.port = board["Port"] | 5555;
    cfg.board.channel = board["Channel"] | 6;
    cfg.board.hidden = board["Hidden"] | false;

    JsonObject badge = board["BadgeMode"];
    cfg.board.badgeMode.enabled = badge["Enabled"] | false;
    cfg.board.badgeMode.delay = badge["Delay"] | 60;

    JsonObject display = board["DisplayNameOptions"];
    cfg.board.displayNameOptions.gameHosts = (DisplayOptions)(display["AwayMissions"] | 0);
    cfg.board.displayNameOptions.showNamesFrom = (DisplayOptions)(display["ShowNamesFrom"] | 0);

    JsonObject ranks = board["Ranks"];
    cfg.board.ranks.cpo = ranks["CPO"] | 0;
    cfg.board.ranks.ensign = ranks["Ensign"] | 0;
    cfg.board.ranks.ltjg = ranks["LTJG"] | 0;
    cfg.board.ranks.lt = ranks["LT"] | 0;
    cfg.board.ranks.ltc = ranks["LTC"] | 0;
    cfg.board.ranks.cdr = ranks["CDR"] | 0;
    cfg.board.ranks.capt = ranks["CAPT"] | 0;

    return true;
}

// Function to convert Config struct to JSON document
static void configToJson(const Config& config, JsonDocument& doc)
{
    auto user = doc["User"];
    user["DisplayName"] = config.user.displayName;
    user["TotalXP"] = config.user.totalXP;

    //user["Image"] = config.user.image;  // Simplified

    auto contacts = doc["Contacts"];
    for (const auto& c : config.contacts) {
        char id[16];
        snprintf(id, sizeof(id), "%u", c.nodeId);
        auto entry = contacts[id];
        entry["DisplayName"] = c.displayName;
        entry["Friend"] = c.isFriend;
        entry["Blocked"] = c.blocked;
        entry["TotalXP"] = c.totalXP;
        entry["Avatar"] = c.avatar; 
    }

    auto board = doc["Board"];
    board["AirplaneMode"] = config.board.airplaneMode;
    board["IntroWatched"] = config.board.introWatched;
    board["Volume"] = config.board.volume;
    board["Ssid"] = config.board.ssid;
    board["Password"] = config.board.password;
    board["Port"] = config.board.port;
    board["Channel"] = config.board.channel;
    board["Hidden"] = config.board.hidden;

    auto badge = board["BadgeMode"];
    badge["Enabled"] = config.board.badgeMode.enabled;
    badge["Delay"] = config.board.badgeMode.delay;

    auto display = board["DisplayNameOptions"];
    display["AwayMissions"] = config.board.displayNameOptions.gameHosts;
    display["ShowNamesFrom"] = config.board.displayNameOptions.showNamesFrom;

    auto ranks = board["Ranks"];
    ranks["CPO"] = config.board.ranks.cpo;
    ranks["Ensign"] = config.board.ranks.ensign;
    ranks["LTJG"] = config.board.ranks.ltjg;
    ranks["LT"] = config.board.ranks.lt;
    ranks["LTC"] = config.board.ranks.ltc;
    ranks["CDR"] = config.board.ranks.cdr;
    ranks["CAPT"] = config.board.ranks.capt;

    auto games = doc["Games"];
    for (const Game& g : config.games) {
        JsonObject entry = games[g.description];
        entry["XP"] = g.XP;
    }



    //String temp;
    //serializeJsonPretty(doc, temp);
    //printf("JSON Output:\n%s\n", temp.c_str());
}

// Function to save the board configuration to a file
bool saveBoardConfig(Config& config, const char* fileName)
{
    JsonDocument defaultJson;

    //convert config struct to JsonDocument
    configToJson(config, defaultJson);
    //serializeConfig(config, defaultJson);
    if (defaultJson.size() < 1)
    {
        LV_LOG_ERROR("Error converting config to JsonDocument");
        return false;
    }

    //write JsonDocument to fileName
    if (!writeJson(fileName, defaultJson))
    {
        LV_LOG_ERROR("Error writing config to: %s", fileName);
        return false;
    }

    LV_LOG_INFO("Board config successfully written.");
    return true;
}
