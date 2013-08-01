#ifndef TWORLDMAP_H
#define TWORLDMAP_H

#include <QObject>

#include "tobjects.h"

struct TObjInf {
    uint id;
    QPoint pos;
    uint type;
};

class TWorldMAp : public QObject
{
    Q_OBJECT
public:
    explicit TWorldMAp(QObject *parent = 0);
    float x;
    float y;

    QList<TObjInf> structsList;
    
signals:
    
public slots:
    
};

#endif // TWORLDMAP_H
