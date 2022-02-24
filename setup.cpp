#include "setup.h"

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

extern unsigned char key[ALLEGRO_KEY_MAX];

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    /*sample_shot = al_load_sample("shot.flac");
    must_init(sample_shot, "shot sample");*/
}

void audio_deinit()
{
    /*al_destroy_sample(sample_shot);*/
}

ALLEGRO_FONT* font;

void font_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");
}

void font_deinit()
{
    al_destroy_font(font);
}

void disp_pre_draw()
{
    // al_set_target_bitmap(buffer);
}

void disp_post_draw()
{
    // al_set_target_backbuffer(disp);
    // al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);
    // al_draw_bitmap(buffer, 0, 0, 0);

    al_flip_display();
}

void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= KEY_RELEASED;
        break;
    }
}