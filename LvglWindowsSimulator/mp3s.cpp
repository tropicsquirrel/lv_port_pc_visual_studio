#include "mp3s.h"

const char* mp3_beeps_path = "/mp3/beeps";
const char* mp3_announcements_path = "/mp3/computer";

const char* mp3_beeps[] = {
	"keyok1.mp3",
	"keyok2.mp3",
	"keyok3.mp3"
};

const char* mp3_announcements[] = {
	"accesing_mono.mp3"
};

void play_random_beep()
{
	int32_t random_index = rand() % (sizeof(mp3_beeps) / sizeof(mp3_beeps[0])); // Get a random index for the beeps array
#if LV_USE_OS != LV_OS_WINDOWS
        Play_Music(mp3_beeps_path, mp3_beeps[random_index]); // Play a random beep sound
#endif
	//return mp3_beeps[random_index];
}

