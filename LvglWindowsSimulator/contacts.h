#pragma once

#include "custom.h"

extern Config config;
extern ContactManager scanResults;

ContactData* idPacketToContactData(IDPacket* idPacket);
void contactListButtonClick(lv_event_t* e);
void populate_crew_list(lv_event_t* e);
void populate_scan_list(lv_event_t* e);
void tabContactsClicked(lv_event_t* e);
void checkContactsBlockClick(lv_event_t* e);
void checkContactsCrewClick(lv_event_t* e);
