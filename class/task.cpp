#include "task.h"

Task::Task()
{
}

bool Task::qSort(Task *fTask1, Task *fTask2)
{
    return (fTask1->timeToWait < fTask2->timeToWait);
}

//----------------------------------------------------------------------------------//
// Task - TaskBuildingUpgrade
//----------------------------------------------------------------------------------//

TaskBuildingUpgrade::TaskBuildingUpgrade(Building tBuilding)
{

    type = 1;
    lvl = tBuilding.lvl;

    idPlace = tBuilding.idPlace;
    idBuilding = tBuilding.idBuilding;

    neededWood = tBuilding.woodToUpgrade;
    neededClay = tBuilding.clayToUpgrade;
    neededIron = tBuilding.ironToUpgrade;
    neededCorn = tBuilding.cornToUpgrade;
    neededCorn2 = tBuilding.corn2ToUpgrade;

    buildingTime = tBuilding.upgradeLongTime;
    buildOn.setHMS(Time::currentTime());

    bonus = tBuilding.bonus;
    bonusPast = tBuilding.bonusPast;

    imgPath = QString(":/IMG/Building/%1.png").arg(idBuilding);

    isResource = tBuilding.isResource;
}


//----------------------------------------------------------------------------------//
// Task - TaskBuildingBuild
//----------------------------------------------------------------------------------//

TaskBuildingBuild::TaskBuildingBuild(Building tBuilding)
{
    type = 2;
    lvl = tBuilding.lvl;

    idPlace = tBuilding.idPlace;
    idBuilding = tBuilding.idBuilding;

    neededWood = tBuilding.woodToUpgrade;
    neededClay = tBuilding.clayToUpgrade;
    neededIron = tBuilding.ironToUpgrade;
    neededCorn = tBuilding.cornToUpgrade;
    neededCorn2 = tBuilding.corn2ToUpgrade;

    buildingTime = tBuilding.upgradeLongTime;
    buildOn.setHMS(Time::currentTime());

    bonus = tBuilding.bonus;
    bonusPast = tBuilding.bonusPast;

    imgPath = QString(":/IMG/Building/%1.png").arg(idBuilding);

    isResource = tBuilding.isResource;
}

QDataStream &operator <<(QDataStream &fStream, Task *fTask)
{
    fStream << fTask->type << fTask->idPlace << fTask->idBuilding << fTask->lvl
            << fTask->neededWood << fTask->neededClay << fTask->neededIron << fTask->neededCorn << fTask->neededCorn2
            << fTask->isResource << fTask->imgPath << fTask->buildingTime << fTask->buildOn;

    return fStream;
}

QDataStream &operator >>(QDataStream &fStream, Task *fTask)
{
    fStream >> fTask->type >> fTask->idPlace >> fTask->idBuilding >> fTask->lvl >> fTask->neededWood >> fTask->neededClay >> fTask->neededIron >> fTask->neededCorn >> fTask->neededCorn2 >> fTask->isResource >> fTask->imgPath >> fTask->buildingTime >> fTask->buildOn;
    return fStream;
}
