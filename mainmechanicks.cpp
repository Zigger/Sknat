#include "mainmechanicks.h"

MainMechanicks::MainMechanicks()
{
    inpCather = new InputCatcher();
    player = new TTank(0);
    house = new BaseStruct(1);

    sdlint = new SDLInterface();

    dt = 1;

    next_game_tick = SDL_GetTicks();
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
                } else if (!inpCather->keystate[SDLK_s] && !inpCather->keystate[SDLK_w]) {
                    player->speed = player->speed + 0.3*dt;
                }
            }
        } else if (player->speed == 0) {
            if (inpCather->keystate[SDLK_w]) { player->speed += 0.3*dt; }
            else if (inpCather->keystate[SDLK_s]) { player->speed -= 0.3*dt; }
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

void MainMechanicks::translate_sahpe()
{//finding new choordinates of base object figure.
    //axis:
    float ox_x;
    float ox_y;
    float oy_x;
    float oy_y;

    //new rotated axis
    ox_x = cos(player->directionAngle*(3.14/180));
    ox_y = sin(player->directionAngle*(3.14/180));
    oy_x = -sin(player->directionAngle*(3.14/180));
    oy_y = cos(player->directionAngle*(3.14/180));

    //new choordinates of shape-points
    for (int i = 0; i < 4; i++) {//0 = x : 1 = y
        float t_x;
        float t_y;
        t_x = player->position.x + ((player->shape[i][0]*ox_x)
                + (player->shape[i][1]*oy_x));
        t_y = player->position.y + ((player->shape[i][0]*ox_y)
                + (player->shape[i][1]*oy_y));
        player->currShape[i][0] = t_x;
        player->currShape[i][1] = t_y;
    }

}

void MainMechanicks::game_loop()
{
    sdlint->process_events();

    loops = 0;
    while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
//        cout << next_game_tick << " " << loops << " " <<"pp" << endl;
        world_processing();

        next_game_tick += SKIP_TICKS;
        loops++;
    }

    interpolation = float( SDL_GetTicks() + SKIP_TICKS - next_game_tick)
            /float( SKIP_TICKS);
//    cout << "DrawGLScene" << endl;
    sdlint->DrawGLScene(player, &interpolation);
        Sleep(1);

}

void MainMechanicks::world_processing()
{
    process_player(dt/50);
    translate_sahpe();
}
