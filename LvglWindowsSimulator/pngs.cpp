#include "pngs.h"

// Define all extern variables
int32_t int_current_accessories = 0;
int32_t int_current_antennae = 0;
int32_t int_current_beard = 0;
int32_t int_current_background = 0;
int32_t int_current_body = 0;
int32_t int_current_borg = 0;
int32_t int_current_clothes = 0;
int32_t int_current_ears = 0;
int32_t int_current_eye_l = 0;
int32_t int_current_eye_r = 0;
int32_t int_current_eyebrow_l = 0;
int32_t int_current_eyebrow_r = 0;
int32_t int_current_glasses = 0;
int32_t int_current_hair = 0;
int32_t int_current_hands = 0;
int32_t int_current_head = 0;
int32_t int_current_mouth = 0;
int32_t int_current_mustache = 0;
int32_t int_current_noses = 0;
int32_t int_current_ridges = 0;

const char* accessories_images[] = {
	"L:/images/accessories/0.bin",
	"L:/images/accessories/2.bin",
    "L:/images/accessories/11.bin",
    "L:/images/accessories/12.bin",
    "L:/images/accessories/13.bin",
    "L:/images/accessories/14.bin",
    "L:/images/accessories/15.bin",
    "L:/images/accessories/18.bin",
};

const char* antennes_images[] = {
	"L:/images/antennes/0.bin",
	"L:/images/antennes/1.bin",
	"L:/images/antennes/2.bin",
};

const char* beard_images[] = {
	"L:/images/beard/0.bin",
	"L:/images/beard/15.bin",
	"L:/images/beard/16.bin",
	"L:/images/beard/18.bin",
	"L:/images/beard/20.bin",
};

const char* background_images[] = {
	"L:/images/bg/0.bin",
	"L:/images/bg/1.bin",
	"L:/images/bg/2.bin",
    "L:/images/bg/3.bin",
    "L:/images/bg/4.bin",
    "L:/images/bg/5.bin",
    "L:/images/bg/6.bin",
    "L:/images/bg/7.bin",
    "L:/images/bg/8.bin",
    "L:/images/bg/11.bin",
    "L:/images/bg/12.bin",
    "L:/images/bg/13.bin",
    "L:/images/bg/14.bin",
    "L:/images/bg/15.bin",
    "L:/images/bg/16.bin",
    "L:/images/bg/17.bin",
    "L:/images/bg/18.bin",
    "L:/images/bg/19.bin",
    "L:/images/bg/20.bin",
	"L:/images/bg/21.bin",
	"L:/images/bg/22.bin",
	"L:/images/bg/23.bin",
	"L:/images/bg/24.bin",
	"L:/images/bg/25.bin",
	"L:/images/bg/26.bin",
	"L:/images/bg/27.bin",
	"L:/images/bg/28.bin",
	"L:/images/bg/29.bin",
	"L:/images/bg/30.bin",
	"L:/images/bg/31.bin",
	"L:/images/bg/32.bin",
};

const char* body_images[] = {
	"L:/images/body/2.bin",
	"L:/images/body/3.bin",
};

const char* borg_images[] = {
	"L:/images/borg/0.bin",
	"L:/images/borg/1.bin",
	"L:/images/borg/2.bin",
	"L:/images/borg/3.bin",
	"L:/images/borg/4.bin",
	"L:/images/borg/5.bin",
	"L:/images/borg/6.bin",
	"L:/images/borg/7.bin",
};

const char* clothes_images[] = {
    "L:/images/clothes/0.bin",
    "L:/images/clothes/1b.bin",
    "L:/images/clothes/1g.bin",
    "L:/images/clothes/1r.bin",
    "L:/images/clothes/4b.bin",
    "L:/images/clothes/4g.bin",
    "L:/images/clothes/4r.bin",
    "L:/images/clothes/6b.bin",
    "L:/images/clothes/6g.bin",
    "L:/images/clothes/6r.bin",
    "L:/images/clothes/9b.bin",
    "L:/images/clothes/9g.bin",
    "L:/images/clothes/9r.bin",
	"L:/images/clothes/13b.bin",
	"L:/images/clothes/13g.bin",
	"L:/images/clothes/13r.bin",
	"L:/images/clothes/15b.bin",
	"L:/images/clothes/15g.bin",
	"L:/images/clothes/15r.bin",
	"L:/images/clothes/17b.bin",
	"L:/images/clothes/17g.bin",
	"L:/images/clothes/17r.bin",
	"L:/images/clothes/19.bin",
	"L:/images/clothes/23.bin",
	"L:/images/clothes/24.bin",
	"L:/images/clothes/27.bin",
	"L:/images/clothes/34b.bin",
	"L:/images/clothes/34g.bin",
	"L:/images/clothes/34r.bin",
	"L:/images/clothes/36.bin",
	"L:/images/clothes/42b.bin",
	"L:/images/clothes/42g.bin",
	"L:/images/clothes/42r.bin",
	"L:/images/clothes/45b.bin",
	"L:/images/clothes/45g.bin",
	"L:/images/clothes/45r.bin",
	"L:/images/clothes/47.bin",
};

const char* ears_images[] = {
	"L:/images/ears/0.bin",
	"L:/images/ears/1.bin",
	"L:/images/ears/2.bin",
	"L:/images/ears/3.bin",
	"L:/images/ears/4.bin",
	"L:/images/ears/5.bin",
	"L:/images/ears/6.bin",
};

const char* eye_l_images[] = {
	"L:/images/eye-l/0.bin",
	"L:/images/eye-l/1.bin",
	"L:/images/eye-l/2.bin",
	"L:/images/eye-l/3.bin",
	"L:/images/eye-l/4.bin",
	"L:/images/eye-l/5.bin",
	"L:/images/eye-l/6.bin",
};

const char* eye_r_images[] = {
	"L:/images/eye-r/0.bin",
	"L:/images/eye-r/1.bin",
	"L:/images/eye-r/2.bin",
	"L:/images/eye-r/3.bin",
	"L:/images/eye-r/4.bin",
	"L:/images/eye-r/5.bin",
	"L:/images/eye-r/6.bin",
};

const char* eyebrows_l_images[] = {
	"L:/images/eyebrows-l/0.bin",
	"L:/images/eyebrows-l/1.bin",
	"L:/images/eyebrows-l/2.bin",
	"L:/images/eyebrows-l/3.bin",
	"L:/images/eyebrows-l/4.bin",
	"L:/images/eyebrows-l/5.bin",
	"L:/images/eyebrows-l/6.bin",
	"L:/images/eyebrows-l/7.bin",
	"L:/images/eyebrows-l/8.bin",
};

const char* eyebrows_r_images[] = {
	"L:/images/eyebrows-r/0.bin",
	"L:/images/eyebrows-r/1.bin",
	"L:/images/eyebrows-r/2.bin",
	"L:/images/eyebrows-r/3.bin",
	"L:/images/eyebrows-r/4.bin",
	"L:/images/eyebrows-r/5.bin",
	"L:/images/eyebrows-r/6.bin",
	"L:/images/eyebrows-r/7.bin",
	"L:/images/eyebrows-r/8.bin",
};

const char* glasses_images[] = {
	"L:/images/glasses/0.bin",
	"L:/images/glasses/1.bin",
	"L:/images/glasses/2.bin",
	"L:/images/glasses/3.bin",
	"L:/images/glasses/4.bin",
	"L:/images/glasses/5.bin",
};

const char* hair_images[] = {
	"L:/images/hair/0.bin",
	"L:/images/hair/1.bin",
    "L:/images/hair/2.bin",
    "L:/images/hair/3.bin",
    "L:/images/hair/4.bin",
    "L:/images/hair/5.bin",
    "L:/images/hair/6.bin",
    "L:/images/hair/7.bin",
    "L:/images/hair/8.bin",
    "L:/images/hair/9.bin",
	"L:/images/hair/10.bin",
	"L:/images/hair/11.bin",
	"L:/images/hair/12.bin",
	"L:/images/hair/13.bin",
	"L:/images/hair/14.bin",
	"L:/images/hair/15.bin",
	"L:/images/hair/16.bin",
	"L:/images/hair/17.bin",
	"L:/images/hair/18.bin",
	"L:/images/hair/19.bin",
	"L:/images/hair/20.bin",
	"L:/images/hair/27.bin",
	"L:/images/hair/32.bin",
	"L:/images/hair/33.bin",
	"L:/images/hair/34.bin",
	"L:/images/hair/36.bin",
	"L:/images/hair/37.bin",
	"L:/images/hair/38.bin",
	"L:/images/hair/39.bin",
	"L:/images/hair/40.bin",
	"L:/images/hair/41.bin",
	"L:/images/hair/42.bin",
	"L:/images/hair/43.bin",
	"L:/images/hair/44.bin",
	"L:/images/hair/45.bin",
	"L:/images/hair/46.bin",
};

const char* hands_images[] = {
	"L:/images/hands/0.bin",
	"L:/images/hands/1.bin",
	"L:/images/hands/2.bin",
	"L:/images/hands/3.bin",
	"L:/images/hands/4.bin",
	"L:/images/hands/5.bin",
	"L:/images/hands/6.bin",
	"L:/images/hands/7.bin",
	"L:/images/hands/8.bin",
};

const char* head_images[] = {
	"L:/images/head/1.bin",
	"L:/images/head/2.bin",
	"L:/images/head/3.bin",
	"L:/images/head/4.bin",
	"L:/images/head/5.bin",
	"L:/images/head/6.bin",
	"L:/images/head/7.bin",
	"L:/images/head/8.bin",
	"L:/images/head/9.bin",
    "L:/images/head/10.bin",
    "L:/images/head/11.bin",
    "L:/images/head/12.bin",
    "L:/images/head/13.bin",
    "L:/images/head/14.bin",
    "L:/images/head/15.bin",
    "L:/images/head/16.bin",
};

const char* mouth_images[] = {
	"L:/images/mouth/0.bin",
	"L:/images/mouth/1.bin",
	"L:/images/mouth/6.bin",
	"L:/images/mouth/7.bin",
	"L:/images/mouth/8.bin",
	"L:/images/mouth/9.bin",
    "L:/images/mouth/10.bin",
    "L:/images/mouth/11.bin",
    "L:/images/mouth/12.bin",
    "L:/images/mouth/13.bin",
    "L:/images/mouth/14.bin",
    "L:/images/mouth/15.bin",
    "L:/images/mouth/16.bin",
    "L:/images/mouth/17.bin",
    "L:/images/mouth/18.bin",
    "L:/images/mouth/19.bin",
};

const char* mustache_images[] = {
	"L:/images/mustache/0.bin",
	"L:/images/mustache/1.bin",
	"L:/images/mustache/2.bin",
	"L:/images/mustache/3.bin",
	"L:/images/mustache/4.bin",
	"L:/images/mustache/5.bin",
	"L:/images/mustache/6.bin",
	"L:/images/mustache/7.bin",
	"L:/images/mustache/8.bin",
};

const char* noses_images[] = {
	"L:/images/noses/0.bin",
	"L:/images/noses/1.bin",
    "L:/images/noses/2.bin",
    "L:/images/noses/3.bin",
    "L:/images/noses/4.bin",
    "L:/images/noses/5.bin",
    "L:/images/noses/6.bin",
    "L:/images/noses/7.bin",
    "L:/images/noses/8.bin",
    "L:/images/noses/9.bin",
    "L:/images/noses/10.bin",
	"L:/images/noses/11.bin",
	"L:/images/noses/12.bin",
	"L:/images/noses/13.bin",
	"L:/images/noses/14.bin",
	"L:/images/noses/15.bin",
	"L:/images/noses/16.bin",
	"L:/images/noses/17.bin",
	"L:/images/noses/18.bin",
	"L:/images/noses/19.bin",
	"L:/images/noses/20.bin",
	"L:/images/noses/21.bin",
	"L:/images/noses/22.bin",
	"L:/images/noses/23.bin",
	"L:/images/noses/24.bin",
	"L:/images/noses/25.bin",
	"L:/images/noses/26.bin",
	"L:/images/noses/27.bin",
	"L:/images/noses/28.bin",
	"L:/images/noses/29.bin",
	"L:/images/noses/30.bin",
	"L:/images/noses/31.bin",
	"L:/images/noses/32.bin",
	"L:/images/noses/33.bin",
	"L:/images/noses/34.bin",
	"L:/images/noses/35.bin",
	"L:/images/noses/36.bin",
	"L:/images/noses/37.bin",
	"L:/images/noses/38.bin",
	"L:/images/noses/39.bin",
	"L:/images/noses/40.bin",
	"L:/images/noses/41.bin",
	"L:/images/noses/42.bin",
	"L:/images/noses/43.bin",
	"L:/images/noses/44.bin",
	"L:/images/noses/45.bin",
	"L:/images/noses/46.bin",
	"L:/images/noses/47.bin",
	"L:/images/noses/48.bin",
	"L:/images/noses/49.bin",
	"L:/images/noses/50.bin",
	"L:/images/noses/51.bin",
	"L:/images/noses/52.bin",
	"L:/images/noses/53.bin",
	"L:/images/noses/54.bin",
	"L:/images/noses/55.bin",
	"L:/images/noses/56.bin",
	"L:/images/noses/57.bin",
	"L:/images/noses/58.bin",
	"L:/images/noses/59.bin",
	"L:/images/noses/60.bin",
	"L:/images/noses/61.bin",
	"L:/images/noses/62.bin",
	"L:/images/noses/63.bin",
};

const char* ridges_images[] = {
	"L:/images/ridges/0.bin",
	"L:/images/ridges/1.bin",
	"L:/images/ridges/2.bin",
	"L:/images/ridges/3.bin",
	"L:/images/ridges/4.bin",
	"L:/images/ridges/5.bin",
	"L:/images/ridges/6.bin",
	"L:/images/ridges/7.bin",
	"L:/images/ridges/8.bin",
	"L:/images/ridges/9.bin",
    "L:/images/ridges/10.bin",
    "L:/images/ridges/11.bin",
    "L:/images/ridges/12.bin",
};

int32_t int_background_count = sizeof(background_images) / sizeof(background_images[0]);
int32_t int_body_count = sizeof(body_images) / sizeof(body_images[0]);
int32_t int_clothes_count = sizeof(clothes_images) / sizeof(clothes_images[0]);
int32_t int_head_count = sizeof(head_images) / sizeof(head_images[0]);
int32_t int_mouth_count = sizeof(mouth_images) / sizeof(mouth_images[0]);
int32_t int_beard_count = sizeof(beard_images) / sizeof(beard_images[0]);
int32_t int_mustache_count = sizeof(mustache_images) / sizeof(mustache_images[0]);
int32_t int_nose_count = sizeof(noses_images) / sizeof(noses_images[0]);
int32_t int_eye_l_count = sizeof(eye_l_images) / sizeof(eye_l_images[0]);
int32_t int_eye_r_count = sizeof(eye_r_images) / sizeof(eye_r_images[0]);
int32_t int_hair_count = sizeof(hair_images) / sizeof(hair_images[0]);
int32_t int_ears_count = sizeof(ears_images) / sizeof(ears_images[0]);
int32_t int_ridges_count = sizeof(ridges_images) / sizeof(ridges_images[0]);
int32_t int_eyebrow_l_count = sizeof(eyebrows_l_images) / sizeof(eyebrows_l_images[0]);
int32_t int_eyebrow_r_count = sizeof(eyebrows_r_images) / sizeof(eyebrows_r_images[0]);
int32_t int_borg_count = sizeof(borg_images) / sizeof(borg_images[0]);
int32_t int_accessories_count = sizeof(accessories_images) / sizeof(accessories_images[0]);
int32_t int_antennae_count = sizeof(antennes_images) / sizeof(antennes_images[0]);
int32_t int_glasses_count = sizeof(glasses_images) / sizeof(glasses_images[0]);
int32_t int_hands_count = sizeof(hands_images) / sizeof(hands_images[0]);
