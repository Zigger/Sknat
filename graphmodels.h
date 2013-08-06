#ifndef GRAPHMODELS_H
#define GRAPHMODELS_H

#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>

struct TGraphTank
{
public:
    GLdouble vertexArray[7][3];
    unsigned int type;

    explicit TGraphTank();
};

struct TGraphBuildings
{
public:
    explicit TGraphBuildings();
    GLdouble HomeSimpleVA[4][3];

};

#endif // GRAPHMODELS_H
