#ifndef TBASEMECHANICKS_H
#define TBASEMECHANICKS_H

#include <QObject>
#include <QGLWidget>
#include <QTimer>
#include <QDebug>
#include <math.h>

#include "tworldmap.h"
#include "tinputcatcher.h"

class TKeyStatus
{
public:
    bool keyW;
    bool keyA;
    bool keyS;
    bool keyD;
};

class TBaseMechanicks : public QObject
{
    Q_OBJECT
public:
    explicit TBaseMechanicks(QObject *parent = 0);

    QTimer *mainTimer;
    TInputCatcher *inputCatcher;
    TKeyStatus keyStatus;
    TTank *player;

    TWorldMAp *worldmap;
    QList<TTank*> tanksList;
    QList<TStruct*> mapObjList;

signals:
    void rotate_player(QPointF, GLfloat, float, GLfloat);
    void objects_changed();
    
public slots:
    void main_changes();
    void key_pressed_slot(uint key, bool kStatus);
    void mouse_PosChanged_slot(GLfloat x, GLfloat y);

private:
    void processing_player();
    void processing_map_objects();
};

#endif // TBASEMECHANICKS_H
