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
	"L:/images/accessories/0.png",
	"L:/images/accessories/2.png",
    "L:/images/accessories/11.png",
    "L:/images/accessories/12.png",
    "L:/images/accessories/13.png",
    "L:/images/accessories/14.png",
    "L:/images/accessories/15.png",
    "L:/images/accessories/18.png",
};

const char* antennes_images[] = {
	"L:/images/antennes/0.png",
	"L:/images/antennes/1.png",
	"L:/images/antennes/2.png",
};

const char* beard_images[] = {
	"L:/images/beard/0.png",
	"L:/images/beard/15.png",
	"L:/images/beard/16.png",
	"L:/images/beard/18.png",
	"L:/images/beard/20.png",
};

const char* background_images[] = {
	"L:/images/bg/0.png",
	"L:/images/bg/1.png",
	"L:/images/bg/2.png",
    "L:/images/bg/3.png",
    "L:/images/bg/4.png",
    "L:/images/bg/5.png",
    "L:/images/bg/6.png",
    "L:/images/bg/7.png",
    "L:/images/bg/8.png",
    "L:/images/bg/11.png",
    "L:/images/bg/12.png",
    "L:/images/bg/13.png",
    "L:/images/bg/14.png",
    "L:/images/bg/15.png",
    "L:/images/bg/16.png",
    "L:/images/bg/17.png",
    "L:/images/bg/18.png",
    "L:/images/bg/19.png",
    "L:/images/bg/20.png",
	"L:/images/bg/21.png",
	"L:/images/bg/22.png",
	"L:/images/bg/23.png",
	"L:/images/bg/24.png",
	"L:/images/bg/25.png",
	"L:/images/bg/26.png",
	"L:/images/bg/27.png",
	"L:/images/bg/28.png",
	"L:/images/bg/29.png",
	"L:/images/bg/30.png",
	"L:/images/bg/31.png",
	"L:/images/bg/32.png",
};

const char* body_images[] = {
	"L:/images/body/2.png",
	"L:/images/body/3.png",
};

const char* borg_images[] = {
	"L:/images/borg/0.png",
	"L:/images/borg/1.png",
	"L:/images/borg/2.png",
	"L:/images/borg/3.png",
	"L:/images/borg/4.png",
	"L:/images/borg/5.png",
	"L:/images/borg/6.png",
	"L:/images/borg/7.png",
};

const char* clothes_images[] = {
    "L:/images/clothes/0.png",
    "L:/images/clothes/1b.png",
    "L:/images/clothes/1g.png",
    "L:/images/clothes/1r.png",
    "L:/images/clothes/4b.png",
    "L:/images/clothes/4g.png",
    "L:/images/clothes/4r.png",
    "L:/images/clothes/6b.png",
    "L:/images/clothes/6g.png",
    "L:/images/clothes/6r.png",
    "L:/images/clothes/9b.png",
    "L:/images/clothes/9g.png",
    "L:/images/clothes/9r.png",
	"L:/images/clothes/13b.png",
	"L:/images/clothes/13g.png",
	"L:/images/clothes/13r.png",
	"L:/images/clothes/15b.png",
	"L:/images/clothes/15g.png",
	"L:/images/clothes/15r.png",
	"L:/images/clothes/17b.png",
	"L:/images/clothes/17g.png",
	"L:/images/clothes/17r.png",
	"L:/images/clothes/19.png",
	"L:/images/clothes/23.png",
	"L:/images/clothes/24.png",
	"L:/images/clothes/27.png",
	"L:/images/clothes/34b.png",
	"L:/images/clothes/34g.png",
	"L:/images/clothes/34r.png",
	"L:/images/clothes/36.png",
	"L:/images/clothes/42b.png",
	"L:/images/clothes/42g.png",
	"L:/images/clothes/42r.png",
	"L:/images/clothes/45b.png",
	"L:/images/clothes/45g.png",
	"L:/images/clothes/45r.png",
	"L:/images/clothes/47.png",
};

const char* ears_images[] = {
	"L:/images/ears/0.png",
	"L:/images/ears/1.png",
	"L:/images/ears/2.png",
	"L:/images/ears/3.png",
	"L:/images/ears/4.png",
	"L:/images/ears/5.png",
	"L:/images/ears/6.png",
};

const char* eye_l_images[] = {
	"L:/images/eye-l/0.png",
	"L:/images/eye-l/1.png",
	"L:/images/eye-l/2.png",
	"L:/images/eye-l/3.png",
	"L:/images/eye-l/4.png",
	"L:/images/eye-l/5.png",
	"L:/images/eye-l/6.png",
};

const char* eye_r_images[] = {
	"L:/images/eye-r/0.png",
	"L:/images/eye-r/1.png",
	"L:/images/eye-r/2.png",
	"L:/images/eye-r/3.png",
	"L:/images/eye-r/4.png",
	"L:/images/eye-r/5.png",
	"L:/images/eye-r/6.png",
};

const char* eyebrows_l_images[] = {
	"L:/images/eyebrows-l/0.png",
	"L:/images/eyebrows-l/1.png",
	"L:/images/eyebrows-l/2.png",
	"L:/images/eyebrows-l/3.png",
	"L:/images/eyebrows-l/4.png",
	"L:/images/eyebrows-l/5.png",
	"L:/images/eyebrows-l/6.png",
	"L:/images/eyebrows-l/7.png",
	"L:/images/eyebrows-l/8.png",
};

const char* eyebrows_r_images[] = {
	"L:/images/eyebrows-r/0.png",
	"L:/images/eyebrows-r/1.png",
	"L:/images/eyebrows-r/2.png",
	"L:/images/eyebrows-r/3.png",
	"L:/images/eyebrows-r/4.png",
	"L:/images/eyebrows-r/5.png",
	"L:/images/eyebrows-r/6.png",
	"L:/images/eyebrows-r/7.png",
	"L:/images/eyebrows-r/8.png",
};

const char* glasses_images[] = {
	"L:/images/glasses/0.png",
	"L:/images/glasses/1.png",
	"L:/images/glasses/2.png",
	"L:/images/glasses/3.png",
	"L:/images/glasses/4.png",
	"L:/images/glasses/5.png",
};

const char* hair_images[] = {
	"L:/images/hair/0.png",
	"L:/images/hair/1.png",
    "L:/images/hair/2.png",
    "L:/images/hair/3.png",
    "L:/images/hair/4.png",
    "L:/images/hair/5.png",
    "L:/images/hair/6.png",
    "L:/images/hair/7.png",
    "L:/images/hair/8.png",
    "L:/images/hair/9.png",
	"L:/images/hair/10.png",
	"L:/images/hair/11.png",
	"L:/images/hair/12.png",
	"L:/images/hair/13.png",
	"L:/images/hair/14.png",
	"L:/images/hair/15.png",
	"L:/images/hair/16.png",
	"L:/images/hair/17.png",
	"L:/images/hair/18.png",
	"L:/images/hair/19.png",
	"L:/images/hair/20.png",
	"L:/images/hair/27.png",
	"L:/images/hair/32.png",
	"L:/images/hair/33.png",
	"L:/images/hair/34.png",
	"L:/images/hair/36.png",
	"L:/images/hair/37.png",
	"L:/images/hair/38.png",
	"L:/images/hair/39.png",
	"L:/images/hair/40.png",
	"L:/images/hair/41.png",
	"L:/images/hair/42.png",
	"L:/images/hair/43.png",
	"L:/images/hair/44.png",
	"L:/images/hair/45.png",
	"L:/images/hair/46.png",
};

const char* hands_images[] = {
	"L:/images/hands/0.png",
	"L:/images/hands/1.png",
	"L:/images/hands/2.png",
	"L:/images/hands/3.png",
	"L:/images/hands/4.png",
	"L:/images/hands/5.png",
	"L:/images/hands/6.png",
	"L:/images/hands/7.png",
	"L:/images/hands/8.png",
};

const char* head_images[] = {
	"L:/images/head/1.png",
	"L:/images/head/2.png",
	"L:/images/head/3.png",
	"L:/images/head/4.png",
	"L:/images/head/5.png",
	"L:/images/head/6.png",
	"L:/images/head/7.png",
	"L:/images/head/8.png",
	"L:/images/head/9.png",
    "L:/images/head/10.png",
    "L:/images/head/11.png",
    "L:/images/head/12.png",
    "L:/images/head/13.png",
    "L:/images/head/14.png",
    "L:/images/head/15.png",
    "L:/images/head/16.png",
};

const char* mouth_images[] = {
	"L:/images/mouth/0.png",
	"L:/images/mouth/1.png",
	"L:/images/mouth/6.png",
	"L:/images/mouth/7.png",
	"L:/images/mouth/8.png",
	"L:/images/mouth/9.png",
    "L:/images/mouth/10.png",
    "L:/images/mouth/11.png",
    "L:/images/mouth/12.png",
    "L:/images/mouth/13.png",
    "L:/images/mouth/14.png",
    "L:/images/mouth/15.png",
    "L:/images/mouth/16.png",
    "L:/images/mouth/17.png",
    "L:/images/mouth/18.png",
    "L:/images/mouth/19.png",
};

const char* mustache_images[] = {
	"L:/images/mustache/0.png",
	"L:/images/mustache/1.png",
	"L:/images/mustache/2.png",
	"L:/images/mustache/3.png",
	"L:/images/mustache/4.png",
	"L:/images/mustache/5.png",
	"L:/images/mustache/6.png",
	"L:/images/mustache/7.png",
	"L:/images/mustache/8.png",
};

const char* noses_images[] = {
	"L:/images/noses/0.png",
	"L:/images/noses/1.png",
    "L:/images/noses/2.png",
    "L:/images/noses/3.png",
    "L:/images/noses/4.png",
    "L:/images/noses/5.png",
    "L:/images/noses/6.png",
    "L:/images/noses/7.png",
    "L:/images/noses/8.png",
    "L:/images/noses/9.png",
    "L:/images/noses/10.png",
	"L:/images/noses/11.png",
	"L:/images/noses/12.png",
	"L:/images/noses/13.png",
	"L:/images/noses/14.png",
	"L:/images/noses/15.png",
	"L:/images/noses/16.png",
	"L:/images/noses/17.png",
	"L:/images/noses/18.png",
	"L:/images/noses/19.png",
	"L:/images/noses/20.png",
	"L:/images/noses/21.png",
	"L:/images/noses/22.png",
	"L:/images/noses/23.png",
	"L:/images/noses/24.png",
	"L:/images/noses/25.png",
	"L:/images/noses/26.png",
	"L:/images/noses/27.png",
	"L:/images/noses/28.png",
	"L:/images/noses/29.png",
	"L:/images/noses/30.png",
	"L:/images/noses/31.png",
	"L:/images/noses/32.png",
	"L:/images/noses/33.png",
	"L:/images/noses/34.png",
	"L:/images/noses/35.png",
	"L:/images/noses/36.png",
	"L:/images/noses/37.png",
	"L:/images/noses/38.png",
	"L:/images/noses/39.png",
	"L:/images/noses/40.png",
	"L:/images/noses/41.png",
	"L:/images/noses/42.png",
	"L:/images/noses/43.png",
	"L:/images/noses/44.png",
	"L:/images/noses/45.png",
	"L:/images/noses/46.png",
	"L:/images/noses/47.png",
	"L:/images/noses/48.png",
	"L:/images/noses/49.png",
	"L:/images/noses/50.png",
	"L:/images/noses/51.png",
	"L:/images/noses/52.png",
	"L:/images/noses/53.png",
	"L:/images/noses/54.png",
	"L:/images/noses/55.png",
	"L:/images/noses/56.png",
	"L:/images/noses/57.png",
	"L:/images/noses/58.png",
	"L:/images/noses/59.png",
	"L:/images/noses/60.png",
	"L:/images/noses/61.png",
	"L:/images/noses/62.png",
	"L:/images/noses/63.png",
};

const char* ridges_images[] = {
	"L:/images/ridges/0.png",
	"L:/images/ridges/1.png",
	"L:/images/ridges/2.png",
	"L:/images/ridges/3.png",
	"L:/images/ridges/4.png",
	"L:/images/ridges/5.png",
	"L:/images/ridges/6.png",
	"L:/images/ridges/7.png",
	"L:/images/ridges/8.png",
	"L:/images/ridges/9.png",
    "L:/images/ridges/10.png",
    "L:/images/ridges/11.png",
    "L:/images/ridges/12.png",
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
