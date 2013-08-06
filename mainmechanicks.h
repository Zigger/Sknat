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
    InputCatcher *inpCather;

    void process_player(double dt);
    void main_processing();

};

#endif // MAINMECHANICKS_H
