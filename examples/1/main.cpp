//
//  main.cpp
//  allegro-exercise
//
//  Created by cclin on 12/01/2018.
//  Copyright © 2018 cclin. All rights reserved.
//

#include "main.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main(int argc, char **argv) {

    al_init();

    al_create_display(640, 480);

    al_clear_to_color(al_map_rgb(255, 0, 255));

    al_flip_display();

    al_rest(5.0f);

    return 0;
}
