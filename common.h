#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "alllegro.h"

#define BUFFER_W 960
#define BUFFER_H 720

#define DISP_SCALE 1
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

#define pi ALLEGRO_PI
#define _pi_180 pi / 180.0;
#define _180_pi 180.0 / pi

#define FRAMERATE 300.0
#define PHYSICS_FRAMERATE 60.0

void must_init(bool test, const char* description);