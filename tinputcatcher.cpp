#include "tinputcatcher.h"

TInputCatcher::TInputCatcher(QObject *parent)
{

}

void TInputCatcher::key_PressEvent(QKeyEvent *ev)
{
//    qDebug() << "TInputCatcher::keyPressEvent" << ev->key();
//    if (ev->key() == Qt::Key_A) {
//        keyStatus.keyA = true;
//    } else if (ev->key() == Qt::Key_D) {
//        keyStatus.keyD = true;
//    } else if (ev->key() == Qt::Key_W) {
//        keyStatus.keyW = true;
//    } else if (ev->key() == Qt::Key_S) {
//        keyStatus.keyS = true;
//    }
    emit key_changed_signal(ev->key(), true);
}

void TInputCatcher::key_ReleaseEvent(QKeyEvent *ev)
{
//    if (key == Qt::Key_A) {
//        keyStatus.keyA = false;
//    } else if (key == Qt::Key_D) {
//        keyStatus.keyD = false;
//    } else if (key == Qt::Key_W) {
//        keyStatus.keyW = false;
//    } else if (key == Qt::Key_S) {
//        keyStatus.keyS = false;
//    }
    emit key_changed_signal(ev->key(), false);
}
