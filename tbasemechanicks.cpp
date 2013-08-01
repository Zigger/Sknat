#include "tbasemechanicks.h"

TBaseMechanicks::TBaseMechanicks(QObject *parent) :
    QObject(parent)
{
    keyStatus.keyW = false;
    keyStatus.keyA = false;
    keyStatus.keyS = false;
    keyStatus.keyD = false;

    mainTimer = new QTimer(this);

    float x, y;
    x = y = 0.0;
    player = new TTank(x, y, this);

    worldmap = new TWorldMAp(this);
    tanksList.clear();
    mapObjList.clear();

    for (int i =0; i < worldmap->structsList.count(); i++) {
        TStruct *tempOpbj = new TStruct(worldmap->structsList.at(i).pos.x(), worldmap->structsList.at(i).pos.y(), this);
        tempOpbj->directionAngle = 20;
        tempOpbj->id = worldmap->structsList.at(i).id;
        mapObjList.append(tempOpbj);
    }

    connect(mainTimer, SIGNAL(timeout()), this, SLOT(main_changes()));
    mainTimer->start(20);

}

void TBaseMechanicks::main_changes()
{
    processing_player();
}

void TBaseMechanicks::key_pressed_slot(uint key, bool kStatus)
{
//    qDebug() << keyStatus.keyW << keyStatus.keyA << keyStatus.keyS << keyStatus.keyD << "\r\n";
    if (key == Qt::Key_W) keyStatus.keyW =  kStatus;
    if (key == Qt::Key_A) keyStatus.keyA =  kStatus;
    if (key == Qt::Key_S) keyStatus.keyS =  kStatus;
    if (key == Qt::Key_D) keyStatus.keyD =  kStatus;
//    qDebug() << keyStatus.keyW << keyStatus.keyA << keyStatus.keyS << keyStatus.keyD << "\r\n";

}

void TBaseMechanicks::mouse_PosChanged_slot(GLfloat x, GLfloat y)
{
    player->towerDirection.rx() = x;
    player->towerDirection.ry() = y;
}

void TBaseMechanicks::processing_player()
{
    if (keyStatus.keyA == true) player->directionAngle += 5;
    if (keyStatus.keyD == true) player->directionAngle -= 5;

    if (player->speed < -5) player->speed = -5;
    if (player->speed > 5) player->speed = 5;
    if (player->speed > -0.02 && player->speed < 0.02) player->speed = 0;

    if (player->speed > 0) { // run forward
        if (player->speed <= 5) { //not maximum speed (5)
            if (keyStatus.keyW == true) {
                player->speed += 0.03;
            } else if (keyStatus.keyW == false && keyStatus.keyS == true){
                player->speed -= 0.06;
            }else if (keyStatus.keyW == false && keyStatus.keyS == false) {
                player->speed = player->speed - 0.03;
            }
        }
    } else if (player->speed < 0) { //run backward
        if (player->speed >= -5) { //not maximum speed (-5)
            if (keyStatus.keyS == true) {
                player->speed -= 0.03;
            } else if (keyStatus.keyS == false && keyStatus.keyW == true) {
                player->speed += 0.06;
            } else if (keyStatus.keyS == false && keyStatus.keyW == false) {
                player->speed = player->speed + 0.03;
            }
        }
    } else if (player->speed == 0) {
        if (keyStatus.keyW == true) { player->speed += 0.03; }
        else if (keyStatus.keyS == true) { player->speed -= 0.03; }
    }

    player->direction.rx() = (player->position.x()+(player->speed*sin((-player->directionAngle)*(3.14/180))));
    player->direction.ry() = (player->position.y()+(player->speed*cos((player->directionAngle)*(3.14/180))));
//ищем направление башни
    double dirTH = sqrt(pow(player->towerDirection.x(), 2) + pow(player->towerDirection.y(), 2));
    double dirTnormY = player->towerDirection.y() / dirTH;

    player->towerDirectionAngle = acos(dirTnormY)*(180/3.14);
    if (player->towerDirection.x() > 0) {
        player->towerDirectionAngle = -player->towerDirectionAngle;
    }
//ищем направление башни-----
    emit rotate_player(player->direction, player->speed, player->directionAngle, player->towerDirectionAngle);
    player->position.rx() = player->direction.rx();
    player->position.ry() = player->direction.ry();
}
