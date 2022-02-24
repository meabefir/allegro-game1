#pragma once
#include "common.h"

void disp_init();

void disp_deinit();

void audio_init();

void audio_deinit();

void font_init();

void font_deinit();

void disp_pre_draw();

void disp_post_draw();

#define KEY_SEEN     1
#define KEY_RELEASED 2

void keyboard_init();

void keyboard_update(ALLEGRO_EVENT* event);