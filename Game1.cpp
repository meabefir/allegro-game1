#include <ctime>
#include <cmath>
#include <iostream>

#include "alllegro.h"

#include "random.h"
#include "setup.h"
#include "player.h"
#include "debugger.h"
#include "collision_manager.h"

#define USE_DEBUG 1

using namespace std;

extern ALLEGRO_DISPLAY* disp;

long frames;
double current_time;
double delta_time;

void draw_hud() {
    static const ALLEGRO_TRANSFORM* prev_transform = al_get_current_transform();

    static ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, 0, 0);
    al_use_transform(&transform);

#if USE_DEBUG
    debugger->draw();
#endif

    al_use_transform(prev_transform);
}

int main()
{
	srand(time(NULL));

    must_init(al_init(), "allegro");
    must_init(al_install_mouse(), "mouse");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* framerate_timer = al_create_timer(1.0 / FRAMERATE);
    ALLEGRO_TIMER* physics_timer = al_create_timer(1.0 / PHYSICS_FRAMERATE);
    must_init(framerate_timer, "timer");
    must_init(physics_timer, "timer");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    disp_init();
    audio_init();
    font_init();
    keyboard_init();
    
    must_init(al_init_image_addon(), "image");
    must_init(al_init_primitives_addon(), "primitives");

    init_projectiles();

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(framerate_timer));
    al_register_event_source(queue, al_get_timer_event_source(physics_timer));

    debugger->add_field("frame time:", FIELD_TYPE::DOUBLE, &delta_time);
    ALLEGRO_BITMAP* background = al_load_bitmap("assets/background.jpg");

    ///
    CAMERA* camera = new CAMERA(BUFFER_W, BUFFER_H);
    PLAYER* player = new PLAYER(camera);

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    al_start_timer(framerate_timer);
    al_start_timer(physics_timer);
    while (1)
    {
        al_wait_for_event(queue, &event);
        keyboard_update(&event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (event.timer.source == framerate_timer) {
                // game loop
                delta_time = al_get_time() - current_time;
                current_time = al_get_time();

                player->update();
                projectile_manager->update();
                collision_manager->update();
                projectile_manager->cleanup();

                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                redraw = true;
                frames++;
            }
            else if (event.timer.source == physics_timer) {
                // physics update
                collision_manager->fixed_update();
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {

            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // background
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    al_draw_bitmap(background, j * 800, i * 800, 0);
                }
            }
            player->draw();
            projectile_manager->draw();
            camera->draw();

            draw_hud();

            disp_post_draw();
            redraw = false;
        }
    }

    bitmap_manager->delete_instance();
    blender_manager->delete_instance();
    debugger->delete_instance();
    projectile_manager->delete_instance();

    disp_deinit();
    font_deinit();
    al_destroy_timer(framerate_timer);
    al_destroy_event_queue(queue);

    delete player;
    delete camera;

	return 0;
}

