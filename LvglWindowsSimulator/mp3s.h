#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <lvgl.h>

#if LV_USE_OS != LV_OS_WINDOWS
#include "Audio_PCM5101.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

	extern const char* mp3_beeps_path;
	extern const char* mp3_announcements_path;

	extern const char* mp3_beeps[]; 
	extern const char* mp3_announcements[];

	void play_random_beep();

#ifdef __cplusplus
}
#endif
