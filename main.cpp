
#include "mainmechanicks.h"

int main()
{
    MainMechanicks *mech = new MainMechanicks();
    while (1) {
        mech->game_loop();

    }

    return 0;
}

