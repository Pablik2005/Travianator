#ifndef BUILDING_H
#define BUILDING_H

#include <QtCore>
#include <QtGui>

#include <QTime>
#include "Enums.h"
#include "travianwiki.h"
#include "time.h"


class Building
{

public:
    Building();
    Building(int fIdPlace, int fIdBuilding, int fLvl, TravianWiki *fTravianWiki);
    Building(int fIdPlace, int fIdBuilding, int fLvl, int mainBuildingLvl, TravianWiki *fTravianWiki);

    int idPlace;
    int idBuilding;
    int idCategory;  //2-resource 1-military 0- infractrustur

    int lvl;
    int maxLvl;

    int woodToUpgrade;
    int clayToUpgrade;
    int ironToUpgrade;
    int cornToUpgrade;
    int corn2ToUpgrade;

    QString bonus;
    QString bonusPast;

    bool canUpgrade;

    bool isResource;
    bool isExist;
    bool isUpgrading;
    QString abortValueD;

    Time timeToUpgradeEnd;
    Time upgradeLongTime;

    QString imgPath;

    TravianWiki *travianWiki;

    void config(int fIdPlace, TravianWiki *fTravianWiki, int fLvl);
    void setUpgradeLongTime(TravianWiki *fTravianWiki, int fMainBuildingLvl);

};


#endif // BUILDING_H
