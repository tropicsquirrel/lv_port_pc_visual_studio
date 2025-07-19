#include "contacts.h"

int32_t int_contacts_tab_current = -1;    // what contacts tab is being shown: -1 = none, 0 = scan, 1 = crew
int32_t contactLastClicked;               // the ID of the last contact that was clicked

// Convert an IDPacket to a ContactData object
ContactData* idPacketToContactData(IDPacket* idPacket)
{
    if (nullptr == idPacket) return nullptr; // No packet found, exit
    ContactData* contact = new ContactData();
    contact->avatar = idPacket->avatarID;
    contact->isBlocked = false;
    strlcpy(contact->displayName, idPacket->displayName, sizeof(contact->displayName));
    contact->isCrew = false;
    contact->nodeId = idPacket->boardID;
    contact->totalXP = idPacket->totalXP;
    contact->lastUpdateTime = idPacket->timeArrived;
    return contact;
}

void contactListButtonClick(lv_event_t* e)
{
    // clear out the details
    lv_label_set_text(objects.lbl_contacts_name, "Select A Contact");
    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    lv_label_set_text(objects.lbl_contacts_xp, "0");

    // extract the ContactData from the user data of the clicked list entry
    // save that info in a global so we can use it in other functions later
    contactLastClicked = (int32_t)(lv_obj_get_user_data((lv_obj_t*)lv_event_get_target(e)));

    // try and get the contactData from config.contacts first
    ContactData* contact = config.contacts.findContact(contactLastClicked);
    if (nullptr == contact)
    {
        // if that fails, try and get it from scanResults
        contact = scanResults.findContact(contactLastClicked);
        if (nullptr == contact) return; // no contact found in either list; fail silently
    }

    // enable the checkboxes
    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_DISABLED);
    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_DISABLED);

    //set display name in the label
    lv_label_set_text(objects.lbl_contacts_name, getNameFromContact(contact));

    //set the avatar image
    lv_image_set_src(objects.img_contacts_avatar, avatarIDToFilename(contact->avatar));

    //set the XP
    char str_xp[16];
    snprintf(str_xp, sizeof(str_xp), "%d", contact->totalXP);
    lv_label_set_text(objects.lbl_contacts_xp, str_xp);

    if (contact->isCrew)
    {
        //if the contact is a friend, set the crew checkbox
        lv_obj_add_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    }

    if (contact->isBlocked)
    {
        //if the contact is blocked, set the blocked checkbox
        lv_obj_add_state(objects.check_contacts_block, LV_STATE_CHECKED);
    }
}

// populate the crew list with the current crew members
void populate_crew_list(lv_event_t* e)
{
    static std::unordered_map<int32_t, lv_obj_t*> crew_list_buttons;

    std::unordered_map<int32_t, bool> currentIDs;
    for (const auto& [id, _] : crew_list_buttons)
    {
        currentIDs[id] = false;
    }

    std::vector<ContactData*> contacts = config.contacts.getContacts();

    for (ContactData* contact : contacts)
    {
        currentIDs[contact->nodeId] = true;

        if (crew_list_buttons.count(contact->nodeId) == 0)
        {
            lv_obj_t* entry = lv_list_add_button(objects.list_contacts_crew, avatarIDToFilename(contact->avatar), getNameFromContact(contact));
            lv_obj_set_user_data(entry, (void*)contact->nodeId); // Store the nodeID to look up later
            lv_obj_add_event_cb(entry, contactListButtonClick, LV_EVENT_CLICKED, NULL);
            crew_list_buttons[contact->nodeId] = entry;
        }
    }

    // Remove any stale entries
    for (const auto& [id, seen] : currentIDs)
    {
        if (!seen && crew_list_buttons.count(id))
        {
            lv_obj_del(crew_list_buttons[id]);
            crew_list_buttons.erase(id);
        }
    }
}

// populates the results in the 'scan' list of contacts
void populate_scan_list(lv_event_t* e)
{
    // return if the contacts screen is NOT active to save CPU
    if (lv_obj_get_screen(objects.contacts) != lv_scr_act()) return;

    // declare unordered maps
    static std::unordered_map<int32_t, lv_obj_t*> scan_list_buttons;    // the map is between nodeIDs and pointers to button objects
    std::unordered_map<int32_t, bool> currentIDs;                       // map between nodeID and if that ID has been seen

    // populate scan_list_buttons with all existing buttons in the list
    for (uint32_t i = 0; i < lv_obj_get_child_count(objects.list_contacts_scan); i++)
    {
        lv_obj_t* button = lv_obj_get_child(objects.list_contacts_scan, i);
        int32_t id = (uint32_t)lv_obj_get_user_data(button);
        scan_list_buttons[id] = button; // create an id entry for each button
        currentIDs[id] = false;  // create an entry for each id and set each to false (false = 'id does not exist in scanResults')
    }

    // go through each contact in scanResults
    //   update existing buttons with usernames
    //   create new buttons for new contacts
    //   remove buttons for contacts that have aged off
    for (size_t i = 0; i < scanResults.size(); i++)
    {
        // get a pointer to the i-th contact
        ContactData* contact = scanResults.getContacts()[i];
        if (!contact) continue; // just in case - this should never happen
        currentIDs[contact->nodeId] = true; // mark contact as 'exists' (creates the currentIDs[] entry if it doesn't exist)

        // if the contact is NOT listed in the UI yet
        if (scan_list_buttons.count(contact->nodeId) == 0)
        {
            // create the button
            lv_obj_t* entry = lv_list_add_button(objects.list_contacts_scan, avatarIDToFilename(contact->avatar), getNameFromContact(contact));
            lv_obj_set_user_data(entry, (void*)contact->nodeId);
            lv_obj_add_event_cb(entry, contactListButtonClick, LV_EVENT_CLICKED, NULL);
            scan_list_buttons[contact->nodeId] = entry;
            continue;
        }

        // if the contact IS listed in the UI already
        // update their display name
        else
        {
            // make sure the contact still exists
            if (currentIDs[contact->nodeId])
            {
                lv_list_set_button_text(objects.list_contacts_scan, scan_list_buttons[contact->nodeId], getNameFromContact(contact));
                continue;
            }
        }
    }

    // for each contact no longer present in scanResults, remove the button
    for (const auto& [id, seen] : currentIDs)
    {
        if (!seen && scan_list_buttons.count(id))
        {
            lv_obj_delete(scan_list_buttons[id]); // remove the button
            scan_list_buttons.erase(id);
        }
    }

}

// Fires when a tab header on the contacts page is clicked
void tabContactsClicked(lv_event_t* e)
{
    int_contacts_tab_current = (int32_t)lv_event_get_user_data(e);
}

// Fires when the user clicks 'block' on the contacts page
void checkContactsBlockClick(lv_event_t* e)
{
    if (0 == contactLastClicked) return; // no contact selected, exit

    char display[64];
    ContactData* contact;

    //if isBlocked is now TRUE:
    if (lv_obj_get_state(objects.check_contacts_block) & LV_STATE_CHECKED)
    {
        contact = config.contacts.findContact(contactLastClicked);
        if (contact) // if they're in the config.contacts list
        {
            contact->isBlocked = true;
            snprintf(display, sizeof(display), "Crewmate '%s' blocked.", getNameFromContact(contact));
            lv_label_set_text(objects.lbl_contacts_name, display);
        }
        else // if not, add them to config.contacts, remove from scanResults
        {
            contact = scanResults.findContact(contactLastClicked); // pull the info from scanResults
            if (contact)
            {
                contact->isBlocked = true; // set isBlocked = TRUE before storing
                config.contacts.addOrUpdateContact(*contact);
                scanResults.removeContact(contactLastClicked); // and remove them from scanResults
                snprintf(display, sizeof(display), "'%s' blocked.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
            }
            else // contact no longer exists for some reason
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
    }
    // if isBlocked is now FALSE:
    else
    {
        // crew = TRUE, isBlocked = FALSE -> keep in config.contacts
        if (lv_obj_get_state(objects.check_contacts_crew) & LV_STATE_CHECKED)
        {
            contact = config.contacts.findContact(contactLastClicked);
            if (contact) // if they're in the config.contacts list
            {
                contact->isBlocked = false;
                snprintf(display, sizeof(display), "Crew '%s' allowed.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
            }
            else // contact no longer exists for some reason
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
        else // crew = FALSE, isBlocked = FALSE -> remove from config.contacts (scanning will pick them up again when in range)
        {
            contact = config.contacts.findContact(contactLastClicked); // pull the info from scanResults
            if (contact)
            {
                snprintf(display, sizeof(display), "Contact '%s' allowed.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
                config.contacts.removeContact(contactLastClicked);
            }
            else
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
    }

    // clear out the details (prevents double-clicking from causing issues)
    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    lv_label_set_text(objects.lbl_contacts_xp, "0");
    contactLastClicked = 0;

    // disable the checkboxes
    lv_obj_add_state(objects.check_contacts_block, LV_STATE_DISABLED);
    lv_obj_add_state(objects.check_contacts_crew, LV_STATE_DISABLED);


    populate_crew_list(NULL); // then update the crew list
    populate_scan_list(NULL); // and update the scan list
}

// fires when a contact's 'Crew' block is un/checked
void checkContactsCrewClick(lv_event_t* e)
{
    if (0 == contactLastClicked) return; // no contact selected, exit

    char display[64];
    ContactData* contact;

    //if crew is now TRUE:
    if (lv_obj_get_state(objects.check_contacts_crew) & LV_STATE_CHECKED)
    {
        contact = config.contacts.findContact(contactLastClicked);
        if (contact) // if they're in the config.contacts list
        {
            contact->isCrew = true;
            snprintf(display, sizeof(display), "'%s' added to crew.", getNameFromContact(contact));
            lv_label_set_text(objects.lbl_contacts_name, display);
        }
        else // if not, add them to config.contacts, remove from scanResults
        {
            contact = scanResults.findContact(contactLastClicked); // pull the info from scanResults
            if (contact)
            {
                contact->isCrew = true; // set crew = TRUE before storing
                config.contacts.addOrUpdateContact(*contact);
                snprintf(display, sizeof(display), "'%s' added to crew.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
                scanResults.removeContact(contactLastClicked); // and remove them from scanResults
            }
            else // should never happen, but just in case...
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
    }
    // if crew is now FALSE:
    else
    {
        // crew = FALSE, isBlocked = TRUE -> keep in config.contacts
        if (lv_obj_get_state(objects.check_contacts_block) & LV_STATE_CHECKED)
        {
            contact = config.contacts.findContact(contactLastClicked);
            if (contact) // if they're in the config.contacts list
            {
                contact->isCrew = false;
                snprintf(display, sizeof(display), "'%s' removed from crew.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
            }
            else
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
        else // crew = FALSE, isBlocked = FALSE -> remove from config.contacts (scanning will pick them up again when in range)
        {
            contact = config.contacts.findContact(contactLastClicked);
            if (contact)
            {
                snprintf(display, sizeof(display), "'%s' removed from crew.", getNameFromContact(contact));
                lv_label_set_text(objects.lbl_contacts_name, display);
                config.contacts.removeContact(contactLastClicked);
            }
            else
            {
                lv_label_set_text(objects.lbl_contacts_name, "Contact lost.");
            }
        }
    }

    // clear out the details (prevents double-clicking from causing issues)
    lv_obj_remove_state(objects.check_contacts_block, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.check_contacts_crew, LV_STATE_CHECKED);
    lv_label_set_text(objects.lbl_contacts_xp, "0");
    contactLastClicked = 0;

    // disable the checkboxes
    lv_obj_add_state(objects.check_contacts_block, LV_STATE_DISABLED);
    lv_obj_add_state(objects.check_contacts_crew, LV_STATE_DISABLED);

    populate_crew_list(NULL); // then update the crew list
    populate_scan_list(NULL); // and update the scan list
}
