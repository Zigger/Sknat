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

    shape[0][0] = (-4.0);
    shape[0][1] = (-6.0);
    shape[0][2] = (0.1);

    shape[1][0] = (4.0);
    shape[1][1] = (-6.0);
    shape[1][2] = (0.1);

    shape[2][0] = (4.0);
    shape[2][1] = (6.0);
    shape[2][2] = (0.1);

    shape[3][0] = (-4.0);
    shape[3][1] = (6.0);
    shape[3][2] = (0.1);

    currShape[0][1] = (-4.0);
    currShape[0][2] = (-6.0);
    currShape[0][3] = (0.1);

    currShape[1][0] = (4.0);
    currShape[1][1] = (-6.0);
    currShape[1][2] = (0.1);

    currShape[2][0] = (4.0);
    currShape[2][1] = (6.0);
    currShape[2][2] = (0.1);

    currShape[3][0] = (-4.0);
    currShape[3][1] = (6.0);
    currShape[3][2] = (0.1);
}


BaseStruct::BaseStruct(unsigned int id)
    : TObject(id)
{
    shape[0][0] = (-10.0f);
    shape[0][1] = (-10.0);
    shape[0][2] = (3.0);

    shape[1][0] = (10.0);
    shape[1][1] = (-10.0);
    shape[1][2] = (3.0);

    shape[2][0] = (10.0);
    shape[2][1] = (10.0);
    shape[2][2] = (3.0);

    shape[3][0] = (-10.0);
    shape[3][1] = (10.0);
    shape[3][2] = (3.0);
}
