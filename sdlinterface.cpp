#include "sdlinterface.h"

SDLInterface::SDLInterface()
{
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ){
      printf("Unable to init SDL: %s\n", SDL_GetError());
      exit(1);
    } else {
        cout<< "All is good" << endl;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    SDL_SetVideoMode(800,600,32,SDL_OPENGL);
//    window = SDL_CreateWindow("test", 0, 0, 640, 480, SDL_WINDOW_OPENGL);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0);
//    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glEnable(GL_TEXTURE_3D);
    glEnableClientState(GL_VERTEX_ARRAY);
//    glLoadIdentity();
//    gluPerspective(45.0f,640/480,0.1f,100.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    width = 800;
    height = 600;
    ratio=(GLfloat)height/(GLfloat)width;

    if (width>=height)
       glOrtho(-100.0/ratio, 100.0/ratio, -100.0, 100.0, -10.0, 10.0);
    else
       glOrtho(-100.0, 100.0, -100.0*ratio, 100.0*ratio, -10.0, 10.0);

    glViewport(0, 0, width, height);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

}

void SDLInterface::quit()
{
    SDL_Quit();
}

void SDLInterface::process_events()
{
    while (SDL_PollEvent(&any_ev)) {
        if (any_ev.type == SDL_MOUSEMOTION) {
            mouseMoveEvX = any_ev.motion.x;
            mouseMoveEvY = any_ev.motion.y;
        }
    }
}

void SDLInterface::DrawGLScene(TTank *_pl, double *interpolation)
{
    translatePlayersMousePos(_pl);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(0, 255, 0);
    glBegin(GL_LINES);
        glVertex2d(-100, 0);
        glVertex2d(100, 0);
        glVertex2d(0, -100);
        glVertex2d(0, 100);
    glEnd();


//====draw player
    drawPlayer(_pl, interpolation);

//====draw target line
    drawTargetLine(_pl, interpolation);
//image shape (debug)
        image_shape(_pl);


    glFlush();
//    SDL_GL_SwapWindow(window);
    SDL_GL_SwapBuffers();
}

void SDLInterface::drawPlayer(TTank *pl, double *interpolation)
{
    glPushMatrix();
    //====draw chassis
        glTranslatef(pl->position.x,
                     pl->position.y,
                     0.0f); //draw tank
        glRotatef(pl->directionAngle, 0.0, 0.0, 1.0);
        glTranslatef(0.0f, pl->speed*(*interpolation), 0.0f);
        glGetDoublev(GL_MODELVIEW_MATRIX, Tmodelview);
        glGetDoublev(GL_PROJECTION_MATRIX, Tprojection);
        glColor3ub(0, 255, 255);

        glVertexPointer(3, GL_DOUBLE, 0, tankModel.vertexArray);
        glDrawArrays(GL_QUADS, 0, 4);
    //====draw tower
        glRotatef(pl->towerDirAngle, 0.0, 0.0, 1.0);

        glColor3ub(255, 255, 0);
        glVertexPointer(3, GL_DOUBLE, 0, tankModel.vertexArray);
        glDrawArrays(GL_TRIANGLES, 4, 3);

    glPopMatrix();
}

void SDLInterface::drawTargetLine(TTank *pl, double *interpolation)
{
    glColor3ub(255, 0, 0);
//    glPushMatrix();

//        glTranslatef(pl->position.x,
//                    pl->position.y,
//                    0.0f); //draw tank
//        glRotatef(pl->directionAngle, 0.0, 0.0, 1.0);
//        glTranslatef(0.0f, pl->speed*(*interpolation), 0.0f);

        glBegin(GL_LINES);
            glVertex2d(pl->position.x, pl->position.y);

//    glPopMatrix();

            glVertex2d(mouseWorldX, mouseWorldY);
        glEnd();

}

void SDLInterface::translatePlayersMousePos(TTank *pl)
{
    float fDepth=0; // сюда пойдёт нормированное значение глубины

    glReadBuffer(GL_FRONT); // выбираем буффер для чтения
    glReadPixels(mouseMoveEvX, this->height - mouseMoveEvY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &fDepth);
    // записываем нормированную глубину фрагмента под мышью

    GLint    viewport[4];    // параметры viewport-a.
    GLdouble projection[16]; // матрица проекции.
    GLdouble modelview[16];

    glGetIntegerv(GL_VIEWPORT,viewport);           // узнаём параметры viewport-a.
    glGetDoublev(GL_PROJECTION_MATRIX,projection); // узнаём матрицу проекции.
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);

    gluUnProject(
                (GLdouble)(mouseMoveEvX),
                 (GLdouble)(this->height - mouseMoveEvY),
                 fDepth,
                 Tmodelview,
                 projection,
                 viewport,
                 &pl->towerVector.x,
                 &pl->towerVector.y,
                 &pl->towerVector.z);

    gluUnProject(
                (GLdouble)(mouseMoveEvX),
                 (GLdouble)(this->height - mouseMoveEvY),
                 fDepth,
                 modelview,
                 projection,
                 viewport,
                 &mouseWorldX,
                &mouseWorldY,
                &mouseWorldZ);
}

void SDLInterface::image_shape(TTank *pl)
{
    glColor3d(255, 255, 255);
    glBegin(GL_POINTS);
    glVertex3f(pl->currShape[0][0], pl->currShape[0][1], pl->currShape[0][2]);
    glVertex3f(pl->currShape[1][0], pl->currShape[1][1], pl->currShape[1][2]);
    glVertex3f(pl->currShape[2][0], pl->currShape[2][1], pl->currShape[2][2]);
    glVertex3f(pl->currShape[3][0], pl->currShape[3][1], pl->currShape[3][2]);
    glEnd();
}
