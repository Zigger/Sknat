#ifndef TOBJECTS_H
#define TOBJECTS_H

#include <QObject>
#include <QPointF>

//object types:
    //static structs:
const uint house = 0;

    //dynamic objects:
const uint tank = 1;

class TGameObject : public QObject
{
    Q_OBJECT
public:
    explicit TGameObject(QObject *parent);
    float directionAngle;
    QPointF position;
    QPointF direction;
    uint objType;
    uint id;
};

class TTank : public TGameObject
{
public:
    explicit TTank(float _x, float _y, QObject *parent);
    QPointF towerDirection;
    float towerDirectionAngle;
    float speed;
};

class TStruct : public TGameObject
{
public:
    explicit TStruct(float _x, float _y, QObject *parent);
    uint structClass;
};



#endif // TGAMEOBJECT_H
