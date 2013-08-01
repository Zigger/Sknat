#include "tworldmap.h"

TWorldMAp::TWorldMAp(QObject *parent) :
    QObject(parent)
{
    x = 100;
    y = 100;

    TObjInf tempStruct;
    tempStruct.type = 0;
    tempStruct.pos.rx() = 80;
    tempStruct.pos.ry() = 80;
    tempStruct.id = 0;
    structsList.append(tempStruct);
}
