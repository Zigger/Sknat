#ifndef MAINMECHANICKS_H
#define MAINMECHANICKS_H

#include "inputcatcher.h"

class MainMechanicks
{
public:
    MainMechanicks();
    SDLInterface *sdlint;
    Uint32 ticksOld;
    Uint32 ticksNew;
    double dt;

    TTank *player;
    BaseStruct *house;

    InputCatcher *inpCather;

    void process_player(double dt);
    void translate_sahpe();

    void game_loop();
    void world_processing();

//game loop:
    const int TICKS_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    unsigned long next_game_tick;
    int loops;
    double interpolation;
};

#endif // MAINMECHANICKS_H
