#include "common.h"

unsigned char key[ALLEGRO_KEY_MAX];

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

