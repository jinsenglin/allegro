#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_KEYBOARD_STATE keyState ;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_FONT *font = NULL;

//Custom Definition
const char *title = "Final Project 1061044s";
const float FPS = 60;
const int WIDTH = 800;
const int HEIGHT = 600;
typedef struct character
{
    int x;
    int y;
    ALLEGRO_BITMAP *image_path;

}Character;

Character character1;
Character character2;
Character character3;

Character character1Weapon;
Character character2Weapon;
Character character3Weapon;

int character1HP = 100;
int character2HP = 100;
int character3HP = 100;

int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int window = 1;
bool judge_next_window = false;
int next_window = 2;
bool ture_1 , ture_2;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();
    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void game_begin() {
    // Load sound
    song = al_load_sample( "hello.wav" );
    if (!song){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }
    // Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_clear_to_color(al_map_rgb(100,100,100));
    // Load and draw text
    font = al_load_ttf_font("pirulen.ttf",12,0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+120 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+170 , ALLEGRO_ALIGN_CENTRE, "Press '1' to about");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to exit");
    al_draw_rectangle(200, 410, 600, 450, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(200, 460, 600, 500, al_map_rgb(255, 255, 255), 0);
    al_draw_rectangle(200, 510, 600, 550, al_map_rgb(255, 255, 255), 0);
    al_flip_display();
}

int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    // Our setting for controlling animation
    if(event.timer.source == timer){
        ture_1 = !ture_1 ;
    }
    if(event.timer.source == timer2){
        ture_2 = !ture_2 ;
    }

    // Keyboard
    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event.keyboard.keycode)
        {
            // P1 control
            case ALLEGRO_KEY_W:
                character1.y -= 30;
                character1Weapon.y = character1.y;
                break;
            case ALLEGRO_KEY_S:
                character1.y += 30;
                character1Weapon.y = character1.y;
                break;
            case ALLEGRO_KEY_A:
                character1.x -= 30;
                character1Weapon.x = character1.x;
                character1HP -= 10;
                break;
            case ALLEGRO_KEY_D:
                character1.x += 30;
                character1Weapon.x = character1.x;
                break;

            // P2 control
            case ALLEGRO_KEY_UP:
                character2.y -= 30;
                character2Weapon.y = character2.y;
                break;
            case ALLEGRO_KEY_DOWN:
                character2.y += 30;
                character2Weapon.y = character2.y;
                break;
            case ALLEGRO_KEY_RIGHT:
                character2.x += 30;
                character2Weapon.x = character2.x;
                character2HP -= 10;
                break;
            case ALLEGRO_KEY_LEFT:
                character2.x -= 30;
                character2Weapon.x = character2.x;
                break;

            // For Start Menu
            case ALLEGRO_KEY_ENTER:
                judge_next_window = true;
                break;
                
            // For Exit Menu
            case ALLEGRO_KEY_ESCAPE:
                return GAME_TERMINATE;
                
            // For About Menu
            case ALLEGRO_KEY_1:
                judge_next_window = true;
                next_window = 3;
                break;
        }
    }

    // Shutdown our program
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    return 0;
}

int game_run() {
    int error = 0;
    // First window(Menu)
    if(window == 1){
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
            if(judge_next_window) {
                window = next_window;
                switch (next_window) {
                    case 2:
                        // Setting Character
                        character1.x = WIDTH / 2 - 300;
                        character1.y = HEIGHT / 2 + 75;
                        character2.x = WIDTH / 2 + 170;
                        character2.y = HEIGHT / 2 + 100;
                        character1.image_path = al_load_bitmap("maokai.png");
                        character2.image_path= al_load_bitmap("teemo.png");
                        character3.image_path = al_load_bitmap("Azir.png");
                        background = al_load_bitmap("stage.jpg");
                        
                        // Setting Character's Weapon
                        character1Weapon.x = character1.x;
                        character1Weapon.y = character1.y;
                        character1Weapon.image_path = al_load_bitmap("dart.png");
                        character2Weapon.x = character2.x;
                        character2Weapon.y = character2.y;
                        character2Weapon.image_path = al_load_bitmap("dart.png");
                        character3Weapon.image_path = al_load_bitmap("dart.png");
                        
                        //Initialize Timer
                        timer  = al_create_timer(1.0);
                        timer2  = al_create_timer(1.0/3.0);
                        al_register_event_source(event_queue, al_get_timer_event_source(timer)) ;
                        al_register_event_source(event_queue, al_get_timer_event_source(timer2)) ;
                        al_start_timer(timer);
                        al_start_timer(timer2);
                        break;
                    case 3:
                        // Change Menu
                        al_clear_to_color(al_map_rgb(100,100,100));
                        // Load and draw text
                        font = al_load_ttf_font("pirulen.ttf",12,0);
                        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+20 , ALLEGRO_ALIGN_CENTRE, "About");
                        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+70 , ALLEGRO_ALIGN_CENTRE, "Author: 1061044s");
                        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to exit");
                        al_draw_rectangle(200, 250, 600, 450, al_map_rgb(255, 255, 255), 0);
                        al_draw_rectangle(200, 510, 600, 550, al_map_rgb(255, 255, 255), 0);
                        al_flip_display();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    // Second window(Main Game)
    else if(window == 2){
        // Change Image for animation
        al_draw_bitmap(background, 0, 0, 0);
        if(ture_1)al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
        if(ture_2)al_draw_bitmap(character2.image_path, character2.x, character2.y, 0);
        else al_draw_bitmap(character3.image_path, character2.x, character2.y, 0);
        
        // Draw HP bar
        al_draw_filled_rectangle(10, 10, 10 + character1HP, 20, al_map_rgb(255, 0, 0));
        al_draw_filled_rectangle(10, 50, 10 + character2HP, 60, al_map_rgb(255, 0, 0));
        
        // Draw weapon
        if(ture_1)al_draw_bitmap(character1Weapon.image_path, character1Weapon.x, character1Weapon.y, 0);
        if(ture_2)al_draw_bitmap(character2Weapon.image_path, character2Weapon.x, character2Weapon.y, 0);
        else al_draw_bitmap(character3Weapon.image_path, character2Weapon.x, character2Weapon.y, 0);
        
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        // Listening for new event
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    else if (window == 3){
        // Listening for new event
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(image);
    al_destroy_sample(song);
}
