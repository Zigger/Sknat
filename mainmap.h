#ifndef MAINMAP_H
#define MAINMAP_H

#include <iostream>
#include "tobjects.h"
#include <list>
using namespace std;

class MainMap
{    
public:
    explicit MainMap();
    list<TObject*> objList;

    
};

#endif // MAINMAP_H
