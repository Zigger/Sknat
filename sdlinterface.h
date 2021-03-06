#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL2/SDL.h>

#include <math.h>
#include "mainmap.h"
#include "graphmodels.h"

#undef main



class SDLInterface
{
public:
    SDLInterface();
    void quit();
    SDL_Event any_ev;
    void process_events();
    int mouseMoveEvX;
    int mouseMoveEvY;
    GLdouble mouseWorldX;
    GLdouble mouseWorldY;
    GLdouble mouseWorldZ;

//    SDL_Window *window;
    int height;
    int width;
    GLfloat ratio;

    void DrawGLScene(TTank *_pl, double *interpolation);
    void drawPlayer(TTank *pl, double *interpolation);
    void drawTargetLine(TTank *pl, double *interpolation);
    void translatePlayersMousePos(TTank *pl);

    void image_shape(TTank *pl);

    TGraphTank tankModel;

//====matrix
    GLdouble Tmodelview[16];
    GLdouble Tprojection[16];
private:
    SDL_GLContext *context;
    SDL_Window *window;

};

#endif // SDLINTERFACE_H
