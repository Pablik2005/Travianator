#include "travianwiki.h"

TravianWiki::TravianWiki(QObject *parent) :
    QObject(parent)
{
    // -------------------------------------------------------------------------------------------//
    //Resource
    // -------------------------------------------------------------------------------------------//
    loadBuilding(&forest, ":/Data/Resources/Forest.txt");
    loadBuildTime(&forestTime, ":/Data/Resources/ForestTime.txt");
    buildingTable[1] = &forest;
    buildingTimeTable[1] = &forestTime;

    loadBuilding(&clayMine, ":/Data/Resources/ClayMine.txt");
    loadBuildTime(&clayMineTime, ":/Data/Resources/ClayMineTime.txt");
    buildingTable[2] = &clayMine;
    buildingTimeTable[2] = &clayMineTime;

    loadBuilding(&ironMine, ":/Data/Resources/IronMine.txt");
    loadBuildTime(&ironMineTime, ":/Data/Resources/IronMineTime.txt");
    buildingTable[3] = &ironMine;
    buildingTimeTable[3] = &ironMineTime;

    loadBuilding(&fildOfCorn, ":/Data/Resources/FildOfCorn.txt");
    loadBuildTime(&fildOfCornTime, ":/Data/Resources/FildOfCornTime.txt");
    buildingTable[4] = &fildOfCorn;
    buildingTimeTable[4] = &fildOfCornTime;

    loadBuilding(&sawmill, ":/Data/Resources/Sawmill.txt");
    loadBuildTime(&sawmillTime, ":/Data/Resources/SawmillTime.txt");
    buildingTable[5] = &sawmill;
    buildingTimeTable[5] = &sawmillTime;

    loadBuilding(&brickyard, ":/Data/Resources/Brickyard.txt");
    loadBuildTime(&brickyardTime, ":/Data/Resources/BrickyardTime.txt");
    buildingTable[6] = &brickyard;
    buildingTimeTable[6] = &brickyardTime;

    loadBuilding(&ironFoundry, ":/Data/Resources/IronFoundry.txt");
    loadBuildTime(&ironFoundryTime, ":/Data/Resources/IronFoundryTime.txt");
    buildingTable[7] = &ironFoundry;
    buildingTimeTable[7] = &ironFoundryTime;

    loadBuilding(&grainMill, ":/Data/Resources/GrainMill.txt");
    loadBuildTime(&grainMillTime, ":/Data/Resources/GrainMillTime.txt");
    buildingTable[8] = &grainMill;
    buildingTimeTable[8] = &grainMillTime;

    loadBuilding(&bakery, ":/Data/Resources/Bakery.txt");
    loadBuildTime(&bakeryTime, ":/Data/Resources/BakeryTime.txt");
    buildingTable[9] = &bakery;
    buildingTimeTable[9] = &bakeryTime;

    // -------------------------------------------------------------------------------------------//
    //Military
    // -------------------------------------------------------------------------------------------//
    loadBuilding(&workshopArmorer, ":/Data/Military/WorkshopArmorer.txt");
    loadBuildTime(&workshopArmorerTime, ":/Data/Military/WorkshopArmorerTime.txt");
    buildingTable[13] = &workshopArmorer;
    buildingTimeTable[13] = &workshopArmorerTime;

    loadBuilding(&academy, ":/Data/Military/Academy.txt");
    loadBuildTime(&academyTime, ":/Data/Military/AcademyTime.txt");
    buildingTable[22] = &academy;
    buildingTimeTable[22] = &academyTime;

    loadBuilding(&heroMansion, ":/Data/Military/HeroMansion.txt");
    loadBuildTime(&heroMansionTime, ":/Data/Military/HeroMansionTime.txt");
    buildingTable[37] = &heroMansion;
    buildingTimeTable[37] = &heroMansionTime;

    loadBuilding(&tournamentSquare, ":/Data/Military/TournamentSquare.txt");
    loadBuildTime(&tournamentSquareTime, ":/Data/Military/TournamentSquareTime.txt");
    buildingTable[14] = &tournamentSquare;
    buildingTimeTable[14] = &tournamentSquareTime;

    loadBuilding(&rallyPoint, ":/Data/Military/RallyPoint.txt");
    loadBuildTime(&rallyPointTime, ":/Data/Military/RallyPointTime.txt");
    buildingTable[16] = &rallyPoint;
    buildingTimeTable[16] = &rallyPointTime;

    loadBuilding(&barracks, ":/Data/Military/Barracks.txt");
    loadBuildTime(&barracksTime, ":/Data/Military/BarracksTime.txt");
    buildingTable[19] = &barracks;
    buildingTimeTable[19] = &barracksTime;

    loadBuilding(&stable, ":/Data/Military/Stable.txt");
    loadBuildTime(&stableTime, ":/Data/Military/StableTime.txt");
    buildingTable[20] = &stable;
    buildingTimeTable[20] = &stableTime;

    loadBuilding(&workshop, ":/Data/Military/Workshop.txt");
    loadBuildTime(&workshopTime, ":/Data/Military/WorkshopTime.txt");
    buildingTable[21] = &workshop;
    buildingTimeTable[21] = &workshopTime;

    loadBuilding(&greatBarracks, ":/Data/Military/GreatBarracks.txt");
    loadBuildTime(&greatBarracksTime, ":/Data/Military/GreatBarrackseTime.txt");
    buildingTable[29] = &greatBarracks;
    buildingTimeTable[29] = &greatBarracksTime;

    loadBuilding(&greatStable, ":/Data/Military/GreatStable.txt");
    loadBuildTime(&greatStableTime, ":/Data/Military/GreatStableTime.txt");
    buildingTable[30] = &greatStable;
    buildingTimeTable[30] = &greatStableTime;

    loadBuilding(&cityWall, ":/Data/Military/CityWall.txt");
    loadBuildTime(&cityWallTime, ":/Data/Military/CityWallTime.txt");
    buildingTable[31] = &cityWall;
    buildingTimeTable[31] = &cityWallTime;

    loadBuilding(&earthWall, ":/Data/Military/EarthWall.txt");
    loadBuildTime(&earthWallTime, ":/Data/Military/EarthWallTime.txt");
    buildingTable[32] = &earthWall;
    buildingTimeTable[32] = &earthWallTime;

    loadBuilding(&palisade, ":/Data/Military/Palisade.txt");
    loadBuildTime(&palisadeTime, ":/Data/Military/PalisadeTime.txt");
    buildingTable[33] = &palisade;
    buildingTimeTable[33] = &palisadeTime;

    loadBuilding(&trapper, ":/Data/Military/Trapper.txt");
    loadBuildTime(&trapperTime, ":/Data/Military/TrapperTime.txt");
    buildingTable[36] = &trapper;
    buildingTimeTable[36] = &trapperTime;

    // -------------------------------------------------------------------------------------------//
    //Infrastructure
    // -------------------------------------------------------------------------------------------//
    loadBuilding(&townHall, ":/Data/Infrastructure/TownHall.txt");
    loadBuildTime(&townHallTime, ":/Data/Infrastructure/TownHallTime.txt");
    buildingTable[24] = &townHall;
    buildingTimeTable[24] = &townHallTime;

    loadBuilding(&residence, ":/Data/Infrastructure/Residence.txt");
    loadBuildTime(&residenceTime, ":/Data/Infrastructure/ResidenceTime.txt");
    buildingTable[25] = &residence;
    buildingTimeTable[25] = &residenceTime;

    loadBuilding(&palace, ":/Data/Infrastructure/Palace.txt");
    loadBuildTime(&palaceTime, ":/Data/Infrastructure/PalaceTime.txt");
    buildingTable[26] = &palace;
    buildingTimeTable[26] = &palaceTime;

    loadBuilding(&treasury, ":/Data/Infrastructure/Treasury.txt");
    loadBuildTime(&treasuryTime, ":/Data/Infrastructure/TreasuryTime.txt");
    buildingTable[27] = &treasury;
    buildingTimeTable[27] = &treasuryTime;

    loadBuilding(&warehouse, ":/Data/Infrastructure/Warehouse.txt");
    loadBuildTime(&warehouseTime, ":/Data/Infrastructure/WarehouseTime.txt");
    buildingTable[10] = &warehouse;
    buildingTimeTable[10] = &warehouseTime;

    loadBuilding(&granary, ":/Data/Infrastructure/Granary.txt");
    loadBuildTime(&granaryTime, ":/Data/Infrastructure/GranaryTime.txt");
    buildingTable[11] = &granary;
    buildingTimeTable[11] = &granaryTime;

    loadBuilding(&mainBuilding, ":/Data/Infrastructure/MainBuilding.txt");
    loadBuildTime(&mainBuildingTime, ":/Data/Infrastructure/MainBuildingTime.txt");
    buildingTable[15] = &mainBuilding;
    buildingTimeTable[15] = &mainBuildingTime;

    loadBuilding(&marketplace, ":/Data/Infrastructure/Marketplace.txt");
    loadBuildTime(&marketplaceTime, ":/Data/Infrastructure/MarketplaceTime.txt");
    buildingTable[17] = &marketplace;
    buildingTimeTable[17] = &marketplaceTime;

    loadBuilding(&embassy, ":/Data/Infrastructure/Embassy.txt");
    loadBuildTime(&embassyTime, ":/Data/Infrastructure/EmbassyTime.txt");
    buildingTable[18] = &embassy;
    buildingTimeTable[18] = &embassyTime;

    loadBuilding(&cranny, ":/Data/Infrastructure/Cranny.txt");
    loadBuildTime(&crannyTime, ":/Data/Infrastructure/CrannyTime.txt");
    buildingTable[23] = &cranny;
    buildingTimeTable[23] = &crannyTime;

    loadBuilding(&tradeOffice, ":/Data/Infrastructure/TradeOffice.txt");
    loadBuildTime(&tradeOfficeTime, ":/Data/Infrastructure/TradeOfficeTime.txt");
    buildingTable[28] = &tradeOffice;
    buildingTimeTable[28] = &tradeOfficeTime;

    loadBuilding(&stonemason, ":/Data/Infrastructure/Stonemason.txt");
    loadBuildTime(&stonemasonTime, ":/Data/Infrastructure/StonemasonTime.txt");
    buildingTable[34] = &stonemason;
    buildingTimeTable[34] = &stonemasonTime;

    loadBuilding(&greatWarehouse, ":/Data/Infrastructure/GreatWarehouse.txt");
    loadBuildTime(&greatWarehouseTime, ":/Data/Infrastructure/GreatWarehouseTime.txt");
    buildingTable[38] = &greatWarehouse;
    buildingTimeTable[38] = &greatWarehouseTime;

    loadBuilding(&greatGranary, ":/Data/Infrastructure/GreatGranary.txt");
    loadBuildTime(&greatGranaryTime, ":/Data/Infrastructure/GreatGranaryTime.txt");
    buildingTable[39] = &greatGranary;
    buildingTimeTable[39] = &greatGranaryTime;


    loadBuilding(&wateringPlacenary, ":/Data/Infrastructure/WateringPlacenary.txt");
    loadBuildTime(&wateringPlacenaryTime, ":/Data/Infrastructure/WateringPlacenaryTime.txt");
    buildingTable[41] = &wateringPlacenary;
    buildingTimeTable[41] = &wateringPlacenaryTime;
}

void TravianWiki::loadBuilding(QList<WikiBuilding> *fTargetList, QString fFilePath)
{
    QFile tFile(fFilePath);
    if(tFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream tStream(&tFile);

        QString tLine = tStream.readLine();
        do{
            QStringList tElementList = tLine.split('-');

            WikiBuilding tWikiBuilding;
            tWikiBuilding.lvl = tElementList.at(0).toInt();
            tWikiBuilding.wood = tElementList.at(1).toInt();
            tWikiBuilding.clay = tElementList.at(2).toInt();
            tWikiBuilding.iron = tElementList.at(3).toInt();
            tWikiBuilding.corn = tElementList.at(4).toInt();
            tWikiBuilding.corn2 = tElementList.at(5).toInt();

            tWikiBuilding.buildTime.setHMS(tElementList.at(6));

            tWikiBuilding.culturePoint = tElementList.at(7).toInt();
            tWikiBuilding.bonus = tElementList.at(8);

            fTargetList->append(tWikiBuilding);

            tLine = tStream.readLine();
        }while(!tLine.isNull());
    }
    tFile.close();
}

void TravianWiki::loadBuildTime(QList<BuildTime> *fTargetList, QString fFilePath)
{
    QFile tFile(fFilePath);
    if(tFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream tStream(&tFile);

        QString tLine = tStream.readLine();
        do{
            QStringList tElementList = tLine.split('-');

            BuildTime tBuildTime;
            tBuildTime.lvl = tElementList.at(0).toInt();

            for(int i=0; i<21; i++)
            {
                tBuildTime.mainBuilding[i].setHMS( tElementList.at(i+1) );
            }

            fTargetList->append(tBuildTime);


            tLine = tStream.readLine();
        }while(!tLine.isNull());


    }
    tFile.close();
}
