#include "mainmechanicks.h"

MainMechanicks::MainMechanicks()
{
    inpCather = new InputCatcher();
    player = new TTank(0);

    sdlint = new SDLInterface();

    dt = 1;
}

void MainMechanicks::process_player(double dt)
{
    inpCather->updateKeystate();
    if (inpCather->keystate[SDLK_a]) player->directionAngle += 150*(dt);
    if (inpCather->keystate[SDLK_d]) player->directionAngle -= 150*(dt);

    //normalize player speed
    if (player->speed < -1) player->speed = -1;
    if (player->speed > 1) player->speed = 1;
    if (player->speed > -0.02*dt && player->speed < 0.02*dt) player->speed = 0;
    //normalize player speed-----

    //finding player's new speed
        if (player->speed > 0) { // run forward
            if (player->speed <= 1) { //not maximum speed (5)
                if (inpCather->keystate[SDLK_w]) {
                    player->speed += 0.3*dt;
                } else if (!inpCather->keystate[SDLK_w] && inpCather->keystate[SDLK_s]){
                    player->speed -= 0.6*dt;
                }else if (!inpCather->keystate[SDLK_w] && inpCather->keystate[SDLK_s] == false) {
                    player->speed = player->speed - 0.3*dt;
                }
            }
        } else if (player->speed < 0) { //run backward
            if (player->speed >= -1) { //not maximum speed (-5)
                if (inpCather->keystate[SDLK_s]) {
                    player->speed -= 0.3*dt;
                } else if (!inpCather->keystate[SDLK_s] && inpCather->keystate[SDLK_w]) {
                    player->speed += 0.6*dt;
                } else if (!inpCather->keystate[SDLK_s] && inpCather->keystate[SDLK_w]) {
                    player->speed = player->speed + 0.3*dt;
                }
            }
        } else if (player->speed == 0) {
            if (inpCather->keystate[SDLK_w]) { player->speed += 0.3*dt; }
            else if (inpCather->keystate[SDLK_s] == true) { player->speed -= 0.3*dt; }
        }
    //finding player's new speed-----

    //finding player's new position (that is the same, as direction)
        player->direction.x = (player->position.x+(player->speed*sin((-player->directionAngle)*(3.14/180))));
        player->direction.y = (player->position.y+(player->speed*cos((player->directionAngle)*(3.14/180))));
    //finding player's new position------
    //ищем направление башни
        double dirTH = sqrt(pow(player->towerVector.x, 2) + pow(player->towerVector.y, 2));
        double dirTnormY = player->towerVector.y / dirTH;

        player->towerDirAngle = acos(dirTnormY)*(180/3.14);
        if (player->towerVector.x > 0) {
            player->towerDirAngle = -player->towerDirAngle;
        }
    //ищем направление башни-----


    player->position.x = player->direction.x;
    player->position.y = player->direction.y;

}

void MainMechanicks::main_processing()
{
    sdlint->process_events();
    ticksNew = SDL_GetTicks();
    dt = (double)(ticksNew - ticksOld)/1000;
    ticksOld = ticksNew;

    if (dt > (0.016f)) dt = 0.016;
    if (dt < (0.001f)) dt = 0.001;

    process_player(dt);
    sdlint->DrawGLScene(player);
    Sleep(2);

}
