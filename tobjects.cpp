#include "tobjects.h"

TGameObject::TGameObject(QObject *parent)
    : QObject(parent)
{
    position.rx() = 0;
    position.ry() = 0;
    direction.rx() = 0;
    direction.ry() = 0;
    directionAngle = 0;
}


TTank::TTank(float _x, float _y, QObject *parent)
    : TGameObject(parent)
{
    position.rx() = _x;
    position.ry() = _y;
    towerDirection.rx() = 0;
    towerDirection.ry() = 0;
    towerDirectionAngle = 0;
    speed = 0;
    objType = tank;
}


TStruct::TStruct(float _x, float _y, QObject *parent)
    : TGameObject(parent)
{
    position.rx() = _x;
    position.ry() = _y;
    objType = house;
}
