#include "building.h"


Building::Building()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    isUpgrading = false;
    isExist = true;
}

Building::Building(int fIdPlace, int fIdBuilding, int fLvl, TravianWiki *fTravianWiki)
{

    isUpgrading = false;
    isExist = true;
    idPlace = fIdPlace;
    idBuilding = fIdBuilding;
    if(idBuilding !=  0)
        config(fIdPlace, fTravianWiki, fLvl);
}

Building::Building(int fIdPlace, int fIdBuilding, int fLvl, int mainBuildingLvl, TravianWiki *fTravianWiki)
{

    isUpgrading = false;
    isExist = true;
    idBuilding = fIdBuilding;
    idPlace = fIdPlace;
    if(idBuilding !=  0)
    {
        config(fIdPlace, fTravianWiki, fLvl);
        upgradeLongTime = travianWiki->buildingTimeTable[idBuilding]->at(fLvl).mainBuilding[mainBuildingLvl];
    }
}

void Building::config(int fIdPlace, TravianWiki *fTravianWiki, int fLvl)
{
    lvl = fLvl;
    idPlace = fIdPlace;
    isUpgrading = false;
    imgPath = QString(":/IMG/Building/%1").arg(idBuilding);
    travianWiki = fTravianWiki;
    maxLvl = travianWiki->buildingTimeTable[idBuilding]->count();

    if(idBuilding > 4)
        isResource = false;
    else
        isResource = true;

    if(lvl != maxLvl)
    {
        bonus  = travianWiki->buildingTable[idBuilding]->at(fLvl).bonus;
        if( lvl > 1 )
            bonusPast  = travianWiki->buildingTable[idBuilding]->at(fLvl-1).bonus;
        else
            bonusPast = "";

        woodToUpgrade = travianWiki->buildingTable[idBuilding]->at(fLvl).wood;
        clayToUpgrade = travianWiki->buildingTable[idBuilding]->at(fLvl).clay;
        ironToUpgrade = travianWiki->buildingTable[idBuilding]->at(fLvl).iron;
        cornToUpgrade= travianWiki->buildingTable[idBuilding]->at(fLvl).corn;
        corn2ToUpgrade = travianWiki->buildingTable[idBuilding]->at(fLvl).corn2;
    }

}

void Building::setUpgradeLongTime(TravianWiki *fTravianWiki, int fMainBuildingLvl)
{
    if(lvl != maxLvl && idBuilding != 0)
    {
        travianWiki = fTravianWiki;
        upgradeLongTime = travianWiki->buildingTimeTable[idBuilding]->at(lvl).mainBuilding[fMainBuildingLvl];
    }
}
