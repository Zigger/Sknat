#ifndef TOBJECTS_H
#define TOBJECTS_H

class TPoint {
public:
    double x;
    double y;
    double z;
};

class TObject
{
public:    
    TObject(unsigned int _id);
    unsigned int id;
    TPoint position;
    TPoint direction;
    float directionAngle;
};

class TTank : public TObject
{
public:
    TTank(unsigned int id);
    float towerDirAngle;
    TPoint towerVector;
    bool isMooving;
    double speed;
};

class BaseStruct : public TObject
{//any map struct
public:
    unsigned int type;
};

#endif // TOBJECTS_H
