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
    float shape[4][3];
    float currShape[4][3];
};

class BaseStruct : public TObject
{//any map struct
public:
    BaseStruct(unsigned int id);
    unsigned int type;
    float shape[4][3];
};

#endif // TOBJECTS_H
