#include "tgraphics.h"
#include "ui_tgraphics.h"

GLint viewport[4];

TGraphics::TGraphics(QWidget *parent) :  QGLWidget(parent)
{
    qRegisterMetaType<GLfloat>("GLfloat");
    timer = new QTimer(this);

    QGLFormat frmt;
    frmt.setSwapInterval(1);
    setFormat(frmt);

    mech = new TBaseMechanicks();
    mechThread = new QThread(this);

    this->setMouseTracking(true);


    connect(this, SIGNAL(key_changed_signal(uint,bool)), mech, SLOT(key_pressed_slot(uint,bool)));
    connect(mech, SIGNAL(rotate_player(QPointF, GLfloat, float, GLfloat)), this, SLOT(rotate_player_slot(QPointF, GLfloat, float,GLfloat)));
    connect(this, SIGNAL(mousePosChanged(GLfloat,GLfloat)), mech, SLOT(mouse_PosChanged_slot(GLfloat,GLfloat)));
    connect(timer, SIGNAL(timeout()), this, SLOT(paint()));

    map_x = mech->worldmap->x;
    map_y = mech->worldmap->y;

    for (int i = 0; i < mech->mapObjList.count(); i++) {
        paintObj tempObj;
        tempObj.pos = mech->mapObjList.at(i)->position;
        tempObj.type = mech->mapObjList.at(i)->objType;
        tempObj.direction = mech->mapObjList.at(i)->directionAngle;
        tempObj.id = mech->mapObjList.at(i)->id;

        tempObj.vertexArray = *buildingsModels.HomeSimpleVA;

        paintObjects.append(tempObj);
    }


    player = new playerInf();
    player->playerzero();

    mech->moveToThread(mechThread);
//    inputCatcher->moveToThread(inputThread);
    mechThread->start();
//    inputThread->start();
    timer->start(20);

}


void TGraphics::initializeGL()
{
//    qglClearColor(QColor(0, 100, 100, 255));
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_3D);
//    glEnable(GL_MULTISAMPLE);
//    glEnable(GL_POINT_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);
}

void TGraphics::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    ratio=(GLfloat)h/(GLfloat)w;

    if (w>=h)
       glOrtho(-100.0/ratio, 100.0/ratio, -100.0, 100.0, -10.0, 10.0);
    else
       glOrtho(-100.0, 100.0, -100.0*ratio, 100.0*ratio, -10.0, 10.0);

    glViewport(0, 0, (GLint)w, (GLint)h);
    glGetIntegerv(GL_VIEWPORT, viewport);
}

void TGraphics::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    glColor3ub(0, 255, 0);
//    glBegin(GL_LINES);
//        glVertex2d(-100, 0);
//        glVertex2d(100, 0);

//        glVertex2d(0, -100);
//        glVertex2d(0, 100);
//    glEnd();

//====draw player
        draw_player();
//====draw target line
//     glColor3ub(255, 0, 0);
//     glBegin(GL_LINES);
//         glVertex2d(player->pPos.x(), player->pPos.y());
//         glVertex2d(mouseWorldX, mouseWorldY);
//     glEnd();


     glColor3ub(255, 0, 0);
     for (int i =0; i < paintObjects.count(); i++) {
        glPushMatrix();
            glTranslatef(paintObjects.at(i).pos.x(), paintObjects.at(i).pos.x(), 0.0);
            glRotated(paintObjects.at(i).direction, 0.0, 0.0, 1.0);
            glVertexPointer(3, GL_DOUBLE, 0, paintObjects.at(i).vertexArray);
            glDrawArrays(GL_QUADS, 0, 4);

        glPopMatrix();
     }

}

void TGraphics::keyPressEvent(QKeyEvent *ev)
{
    emit key_changed_signal(ev->key(), true);
}

void TGraphics::keyReleaseEvent(QKeyEvent *ev)
{
    emit key_changed_signal(ev->key(), false);
}

void TGraphics::mouseMoveEvent(QMouseEvent *ev)
{
    mouseMoveEvX = ev->pos().x();
    mouseMoveEvY = ev->pos().y();
}

void TGraphics::draw_player()
{
    glPushMatrix();
    //====draw chassis
        glTranslatef(player->pPos.x(), player->pPos.y(), 0.0f); //draw tank
        glRotatef(player->pDirection, 0.0, 0.0, 1.0);
        glTranslatef(0.0f, player->speed, 0.0f);
        glGetDoublev(GL_MODELVIEW_MATRIX, Tmodelview);
        glGetDoublev(GL_PROJECTION_MATRIX, Tprojection);
        glColor3ub(0, 255, 255);

        glVertexPointer(3, GL_DOUBLE, 0, tankModel.vertexArray);
        glDrawArrays(GL_QUADS, 0, 4);
    //====draw tower
        glRotatef(player->pTowerDirection, 0.0, 0.0, 1.0);

        glColor3ub(255, 255, 0);
        glVertexPointer(3, GL_DOUBLE, 0, tankModel.vertexArray);
        glDrawArrays(GL_TRIANGLES, 4, 3);
     glPopMatrix();
}


void TGraphics::apply_objList(QList<QPoint> posList, QList<uint> types)
{
    paintObjects.clear();
    for (int i = 0; i < posList.count(); i++) {
        paintObj tempObj;
        tempObj.pos = posList.at(i);
        tempObj.type = types.at(i);
    }
}

void TGraphics::rotate_player_slot(QPointF pos, GLfloat sp, float pDir, GLfloat ptDir)
{
    player->pDirection = pDir;
    player->pTowerDirection = ptDir;
    player->speed = sp;
    player->pPos.rx() = pos.x();
    player->pPos.ry() = pos.y();
//    qDebug() << pos;
}

void TGraphics::paint()
{
    float fDepth=0; // сюда пойдёт нормированное значение глубины

    ::glReadBuffer(GL_FRONT); // выбираем буффер для чтения
    ::glReadPixels(mouseMoveEvX, this->height() - mouseMoveEvY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &fDepth);
    // записываем нормированную глубину фрагмента под мышью

    GLint    viewport[4];    // параметры viewport-a.
    GLdouble projection[16]; // матрица проекции.
    GLdouble modelview[16];

    glGetIntegerv(GL_VIEWPORT,viewport);           // узнаём параметры viewport-a.
    glGetDoublev(GL_PROJECTION_MATRIX,projection); // узнаём матрицу проекции.
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);

    gluUnProject(
                (GLdouble)(mouseMoveEvX),
                 (GLdouble)(this->height() - mouseMoveEvY),
                 fDepth,
                 Tmodelview,
                 projection,
                 viewport,
                 &player->mouseX,
                &player->mouseY,
                &player->mouseZ);

    gluUnProject(
                (GLdouble)(mouseMoveEvX),
                 (GLdouble)(this->height() - mouseMoveEvY),
                 fDepth,
                 modelview,
                 projection,
                 viewport,
                 &mouseWorldX,
                &mouseWorldY,
                &mouseWorldZ);

    emit mousePosChanged(player->mouseX, player->mouseY);
    updateGL();
}

void playerInf::playerzero()
{
    pDirection = 0;
    pTowerDirection = 0;
    pPos.rx() = 0;
    pPos.ry() = 0;
    speed = 0;
}
