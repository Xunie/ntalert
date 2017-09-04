#include "blobs.h"
#include <string>
#include <map>
using namespace std;


// this stuff is all linked in:
extern unsigned char _binary_ghost_equip_wav_start;
extern unsigned char _binary_ghost_equip_wav_size;
extern unsigned char _binary_ghost_equip2_wav_start;
extern unsigned char _binary_ghost_equip2_wav_size;
extern unsigned char _binary_ghost_equip3_wav_start;
extern unsigned char _binary_ghost_equip3_wav_size;
extern unsigned char _binary_ghost_equip4_wav_start;
extern unsigned char _binary_ghost_equip4_wav_size;
extern unsigned char _binary_ghost_equip5_wav_start;
extern unsigned char _binary_ghost_equip5_wav_size;

extern unsigned char _binary_ghost_ping_wav_start;
extern unsigned char _binary_ghost_ping_wav_size;

extern unsigned char _binary_ghost_idle_loop_wav_start;
extern unsigned char _binary_ghost_idle_loop_wav_size;


// font
extern unsigned char _binary_greenm03_ttf_start;
extern unsigned char _binary_greenm03_ttf_size;


// background
extern unsigned char _binary_background_png_start;
extern unsigned char _binary_background_png_size;


// hud
extern unsigned char _binary_hud_blur_png_start;
extern unsigned char _binary_hud_blur_png_size;
extern unsigned char _binary_hud_left_png_start;
extern unsigned char _binary_hud_left_png_size;
extern unsigned char _binary_hud_right_png_start;
extern unsigned char _binary_hud_right_png_size;
extern unsigned char _binary_hud_text_png_start;
extern unsigned char _binary_hud_text_png_size;
extern unsigned char _binary_hud_fill_png_start;
extern unsigned char _binary_hud_fill_png_size;


const map<string, blob> blobs = {
    {"ghost_equip.wav",  {&_binary_ghost_equip_wav_start,  (size_t) &_binary_ghost_equip_wav_size }},
    {"ghost_equip2.wav", {&_binary_ghost_equip2_wav_start, (size_t) &_binary_ghost_equip2_wav_size}},
    {"ghost_equip3.wav", {&_binary_ghost_equip3_wav_start, (size_t) &_binary_ghost_equip3_wav_size}},
    {"ghost_equip4.wav", {&_binary_ghost_equip4_wav_start, (size_t) &_binary_ghost_equip4_wav_size}},
    {"ghost_equip5.wav", {&_binary_ghost_equip5_wav_start, (size_t) &_binary_ghost_equip5_wav_size}},
    {"ghost_ping.wav",   {&_binary_ghost_ping_wav_start,   (size_t) &_binary_ghost_ping_wav_size}},

    {"ghost_idle_loop.wav", {&_binary_ghost_idle_loop_wav_start, (size_t) &_binary_ghost_idle_loop_wav_size}},

    {"greenm03.ttf", {&_binary_greenm03_ttf_start, (size_t) &_binary_greenm03_ttf_size}},

    {"background.png", {&_binary_background_png_start, (size_t) &_binary_background_png_size}},

    {"hud_blur.png",  {&_binary_hud_blur_png_start,  (size_t) &_binary_hud_blur_png_size}},
    {"hud_left.png",  {&_binary_hud_left_png_start,  (size_t) &_binary_hud_left_png_size}},
    {"hud_right.png", {&_binary_hud_right_png_start, (size_t) &_binary_hud_right_png_size}},
    {"hud_text.png",  {&_binary_hud_text_png_start,  (size_t) &_binary_hud_text_png_size}},
    {"hud_fill.png",  {&_binary_hud_fill_png_start,  (size_t) &_binary_hud_fill_png_size}}
};
