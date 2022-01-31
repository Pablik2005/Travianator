#ifndef TASK_H
#define TASK_H

#include <QTime>

#include "building.h"
#include "time.h"

//----------------------------------------------------------------------------------//
// Base - Task
//----------------------------------------------------------------------------------//

class Task
{
public:
    Task();

    int type;
    int idPlace;
    int idBuilding;

    int lvl;

    int neededWood;
    int neededClay;
    int neededIron;
    int neededCorn;
    int neededCorn2;

    bool isResource;

    QString imgPath;

    QString bonus;
    QString bonusPast;

    Time timeToWait;
    Time buildingTime;
    Time buildOn;

    bool static qSort(Task *fTask1, Task *fTask2);

};

QDataStream &operator<<(QDataStream &fStream, Task *fTask);
QDataStream &operator>>(QDataStream &fStream, Task *fTask);

//----------------------------------------------------------------------------------//
// Task - TaskBuildingUpgrade
//----------------------------------------------------------------------------------//
class TaskBuildingUpgrade : public Task
{

public:
    TaskBuildingUpgrade( Building tBuilding);


};


//----------------------------------------------------------------------------------//
// Task - TaskBuildingBuild
//----------------------------------------------------------------------------------//
class TaskBuildingBuild : public Task
{

public:
    TaskBuildingBuild( Building tBuilding);

};

#endif // TASK_H
