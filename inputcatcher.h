#ifndef INPUTCATCHER_H
#define INPUTCATCHER_H

#include "sdlinterface.h"

class InputCatcher
{
public:
    InputCatcher();

    Uint8 *keystate;


    void updateKeystate();

};

#endif // INPUTCATCHER_H
