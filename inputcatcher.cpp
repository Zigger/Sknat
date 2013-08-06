#include "inputcatcher.h"

InputCatcher::InputCatcher()
{
    keystate = SDL_GetKeyState(NULL);
}

void InputCatcher::updateKeystate()
{
    keystate = SDL_GetKeyState(NULL);
}
