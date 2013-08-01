#ifndef TGRAPHICS_H
#define TGRAPHICS_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QThread>
#include <QDebug>
#include <GL/glu.h>

#include "TGraphDescriptions.h"
#include "tbasemechanicks.h"

class paintObj
{
public:
    QPointF pos;
    GLfloat direction;
    uint type;
    GLdouble *vertexArray;
    uint graphStatus;
    uint id;
};

class paintBuildings : public paintObj
{
public:


};

struct playerInf {
    void playerzero();
    GLfloat pDirection;
    QPointF pPos;
    GLfloat pTowerDirection;
    GLdouble mouseX;
    GLdouble mouseY;
    GLdouble mouseZ;
    GLfloat speed;
};

class TGraphics : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit TGraphics(QWidget *parent = 0);
//    ~TGraphics();

    GLfloat map_x = 100;
    GLfloat map_y = 100;

signals:
    void key_changed_signal(uint keyNum, bool keyStat);
    void mousePosChanged(GLfloat x, GLfloat y);

public slots:
    void apply_objList(QList<QPoint> posList, QList<uint> types);
    void rotate_player_slot(QPointF pos, GLfloat sp, float pDir, GLfloat ptDir);
    void paint();

private:
    TBaseMechanicks *mech;
    TInputCatcher *inputCatcher;
    QThread *mechThread;
    QThread *inputThread;

    playerInf *player;



    int mouseMoveEvX;
    int mouseMoveEvY;
    GLdouble mouseWorldX;
    GLdouble mouseWorldY;
    GLdouble mouseWorldZ;


    TGraphTank tankModel;
    TGraphBuildings buildingsModels;
    QTimer *timer;

    GLfloat ratio;

    QList<paintObj> paintObjects;

//====matrix
    GLdouble Tmodelview[16];
    GLdouble Tprojection[16];

//=========== functions ================
//presets
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
//presets      ----

    void draw_player();

};

#endif // TGRAPHICS_H
