#ifndef TINPUTCATCHER_H
#define TINPUTCATCHER_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QCoreApplication>

class TInputCatcher : public QWidget
{
    Q_OBJECT
public:
    explicit TInputCatcher(QObject *parent = 0);

    void key_PressEvent(QKeyEvent *ev);
    void key_ReleaseEvent(QKeyEvent *ev);
signals:
    void key_changed_signal(uint keyNum, bool keyStat);
    
public slots:
    
};

#endif // TINPUTCATCHER_H
