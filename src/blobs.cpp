#include "blobs.h"
#include <string>
#include <map>
using namespace std;


#define BLOB_DEF(X) \
    extern "C" const char binary_##X##_start asm("_binary_"#X"_start"); \
    extern "C" const char binary_##X##_size  asm("_binary_"#X"_size")

#define BLOB_USE(NAME, X) \
    {NAME, {&binary_##X##_start, (size_t) &binary_##X##_size}}


BLOB_DEF(ghost_equip_wav);
BLOB_DEF(ghost_equip2_wav);
BLOB_DEF(ghost_equip3_wav);
BLOB_DEF(ghost_equip4_wav);
BLOB_DEF(ghost_equip5_wav);

BLOB_DEF(ghost_ping_wav);
BLOB_DEF(ghost_idle_loop_wav);

BLOB_DEF(greenm03_ttf);
BLOB_DEF(background_png);
BLOB_DEF(ghost_equip_wav);

BLOB_DEF(hud_blur_png);
BLOB_DEF(hud_left_png);
BLOB_DEF(hud_right_png);
BLOB_DEF(hud_text_png);
BLOB_DEF(hud_fill_png);


const map<string, blob> blobs = {
    BLOB_USE("ghost_equip.wav",  ghost_equip_wav),
    BLOB_USE("ghost_equip2.wav", ghost_equip2_wav),
    BLOB_USE("ghost_equip3.wav", ghost_equip3_wav),
    BLOB_USE("ghost_equip4.wav", ghost_equip4_wav),
    BLOB_USE("ghost_equip5.wav", ghost_equip5_wav),

    BLOB_USE("ghost_ping.wav", ghost_ping_wav),
    BLOB_USE("ghost_idle_loop.wav", ghost_idle_loop_wav),

    BLOB_USE("greenm03.ttf", greenm03_ttf),

    BLOB_USE("background.png", background_png),

    BLOB_USE("hud_blur.png", hud_blur_png),
    BLOB_USE("hud_left.png", hud_left_png),
    BLOB_USE("hud_right.png", hud_right_png),
    BLOB_USE("hud_text.png", hud_text_png),
    BLOB_USE("hud_fill.png", hud_fill_png)
};
