#include "tobjects.h"

TObject::TObject(unsigned int _id)
{
    id = _id;
    position.x = 0;
    position.y = 0;
    position.z = 0;
    directionAngle = 0;
    direction.x = 0;
    direction.y = 0;
    direction.z = 0;
}


TTank::TTank(unsigned int id)
    : TObject(id)
{
    towerDirAngle = 0;
    towerVector.x = 0;
    towerVector.y = 0;
    towerVector.z = 0;
    speed = 0;
    isMooving = false;
}
