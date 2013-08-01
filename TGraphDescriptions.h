#ifndef TGRAPHDESCRIPTIONS_H
#define TGRAPHDESCRIPTIONS_H

#include <qopengl.h>

struct TGraphTank
{
public:
    GLdouble vertexArray[7][3];
    uint type;

    explicit TGraphTank();
};

struct TGraphBuildings
{
public:
    explicit TGraphBuildings();
    GLdouble HomeSimpleVA[4][3];

};



#endif // TGRAPHDESCRIPTIONS_H
