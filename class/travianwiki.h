#ifndef TRAVIANWIKI_H
#define TRAVIANWIKI_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QWidget>

#include "class/time.h"


struct WikiBuilding
{
    int lvl;
    int wood;
    int clay;
    int iron;
    int corn;
    int corn2;
    Time buildTime;
    int culturePoint;
    QString bonus;
};

struct BuildTime
{
    int lvl;
    Time mainBuilding[21];
};

class TravianWiki : public QObject
{
    Q_OBJECT
public:
    explicit TravianWiki(QObject *parent = 0);

    // -------------------------------------------------------------------------------------------//
    //Resource
    // -------------------------------------------------------------------------------------------//
    QList<WikiBuilding> forest;
    QList<BuildTime> forestTime;

    QList<WikiBuilding> clayMine;
    QList<BuildTime> clayMineTime;

    QList<WikiBuilding> ironMine;
    QList<BuildTime> ironMineTime;

    QList<WikiBuilding> fildOfCorn;
    QList<BuildTime> fildOfCornTime;

    QList<WikiBuilding> sawmill;       //Tartak
    QList<BuildTime> sawmillTime;

    QList<WikiBuilding> brickyard;     //Cegielnia
    QList<BuildTime> brickyardTime;

    QList<WikiBuilding> ironFoundry;   //Huta Stali
    QList<BuildTime> ironFoundryTime;

    QList<WikiBuilding> grainMill;     //Młyn
    QList<BuildTime> grainMillTime;

    QList<WikiBuilding> bakery;        //Piekarnia
    QList<BuildTime> bakeryTime;

    // -------------------------------------------------------------------------------------------//
    //Military
    // -------------------------------------------------------------------------------------------//
    QList<WikiBuilding> workshopArmorer;        //Warsztat Płatnerza
    QList<BuildTime> workshopArmorerTime;

    QList<WikiBuilding> academy;                //Akademia
    QList<BuildTime> academyTime;

    QList<WikiBuilding> heroMansion;            //Dwór Bohatera
    QList<BuildTime> heroMansionTime;

    QList<WikiBuilding> tournamentSquare;          //Plac Turniejowy
    QList<BuildTime> tournamentSquareTime;

    QList<WikiBuilding> rallyPoint;                //Miejsce Zbiórki
    QList<BuildTime> rallyPointTime;

    QList<WikiBuilding> barracks;                  //Koszary
    QList<BuildTime> barracksTime;

    QList<WikiBuilding> stable;                    //Stajnia
    QList<BuildTime> stableTime;

    QList<WikiBuilding> workshop;                  //Warsztat
    QList<BuildTime> workshopTime;

    QList<WikiBuilding> greatBarracks;             //Duże Koszary
    QList<BuildTime> greatBarracksTime;

    QList<WikiBuilding> greatStable;               //Duża Stajnia
    QList<BuildTime> greatStableTime;

    QList<WikiBuilding> cityWall;                  //Mury Obronne
    QList<BuildTime> cityWallTime;

    QList<WikiBuilding> earthWall;                 //Wały
    QList<BuildTime> earthWallTime;

    QList<WikiBuilding> palisade;                  //Palisada
    QList<BuildTime> palisadeTime;

    QList<WikiBuilding> trapper;                   //Chata Trapera
    QList<BuildTime> trapperTime;


    // -------------------------------------------------------------------------------------------//
    //Infrastructure
    // -------------------------------------------------------------------------------------------//
    QList<WikiBuilding> townHall;               //Ratusz
    QList<BuildTime> townHallTime;

    QList<WikiBuilding> residence;              //Rezydencja
    QList<BuildTime> residenceTime;

    QList<WikiBuilding> palace;                 //Pałac
    QList<BuildTime> palaceTime;

    QList<WikiBuilding> treasury;               //Skarbiec
    QList<BuildTime> treasuryTime;

    QList<WikiBuilding> warehouse;                 //Magazyn
    QList<BuildTime> warehouseTime;

    QList<WikiBuilding> granary;                   //Spichlerz
    QList<BuildTime> granaryTime;

    QList<WikiBuilding> mainBuilding;              //Budynek Główny
    QList<BuildTime> mainBuildingTime;

    QList<WikiBuilding> marketplace;               //Rynek
    QList<BuildTime> marketplaceTime;

    QList<WikiBuilding> embassy;                   //Ambasada
    QList<BuildTime> embassyTime;

    QList<WikiBuilding> cranny;                    //Kryjówka
    QList<BuildTime> crannyTime;

    QList<WikiBuilding> tradeOffice;               //Targ
    QList<BuildTime> tradeOfficeTime;

    QList<WikiBuilding> stonemason;                //Kamieniarz
    QList<BuildTime> stonemasonTime;

    QList<WikiBuilding> brewery;                   //Browar
    QList<BuildTime> breweryTime;

    QList<WikiBuilding> greatWarehouse;            //Duży Magazyn
    QList<BuildTime> greatWarehouseTime;

    QList<WikiBuilding> greatGranary;              //Duży Spichlerz
    QList<BuildTime> greatGranaryTime;

    QList<WikiBuilding> wateringPlacenary;         //Wodopój
    QList<BuildTime> wateringPlacenaryTime;


    QList<WikiBuilding> *buildingTable[42];
    QList<BuildTime> *buildingTimeTable[42];


    void loadBuilding(QList<WikiBuilding> *fTargetList, QString fFilePath);
    void loadBuildTime(QList<BuildTime> *fTargetList, QString fFilePath);

    
signals:
    
public slots:
    
};

#endif // TRAVIANWIKI_H
