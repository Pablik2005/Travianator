#ifndef DIALOGBUILDINGTOBUILD_H
#define DIALOGBUILDINGTOBUILD_H

#include <QDialog>

#include <QtGui>
#include <QtCore>

#include "../Enums.h"
#include "../language.h"
#include "../list/list.h"
#include "../buildingsocket.h"
#include "../item/itembuildinghorizontal.h"

class DialogBuildingToBuild : public QDialog
{
    Q_OBJECT
public:
    DialogBuildingToBuild(QWidget *parent );

    //-----------GUI-----------//
    QHBoxLayout *mainLayout;
    QTabWidget *tabWidget;

    QWidget *pageInfrastructure;
    QVBoxLayout *infrastructureLayout;
    List *infrastructureList1;
    List *infrastructureList2;

    QWidget *pageMilitary;
    QVBoxLayout *militaryLayout;
    List *militaryList1;
    List *militaryList2;

    QWidget *pageResources;
    QVBoxLayout *resourcesLayout;
    List *resourcesList1;
    List *resourcesList2;

    QFont font;


    //-----------Requestments-----------//
    int forest;
    int clayMine;
    int ironMine;
    int fildOfCorn;
    int sawmill;
    int brickyard;
    int ironFoundry;
    int grainMill;
    int bakery;

    int warehouse;
    int granary;
    int mainBuilding;
    int marketplace;
    int embassy;
    int cranny;
    int townHall;
    int residence;
    int palace;
    int treasury;
    int tradeOffice;
    int stonemason;
    int brewery;
    int greatWarehouse;
    int greatGranary;
    int wonderOfTheWorld;
    int wateringPlacenary;

    int workshopArmorer;
    int tournamentSquare;
    int rallyPoint;
    int barracks;
    int stable;
    int workshop;
    int academy;
    int greatBarracks;
    int greatStable;
    int cityWall;
    int earthWall;
    int palisade;
    int trapper;
    int heroMansion;

    int warehouseSum;
    int granarySum;
    int greatWarehouseSum;
    int greatGranarySum;
    int crannySum;
    int trapperSum;

    //-----------Pointers-----------//
    NationType *nation;
    TravianWiki *travianWiki;
    bool *isCapitol;

    int *maxWood;
    int *maxClay;
    int *maxIron;
    int *maxCorn;

    int *productionWood;
    int *productionClay;
    int *productionIron;
    int *productionCorn;

    int *currentWood;
    int *currentClay;
    int *currentIron;
    int *currentCorn;
    int *currentCorn2;

    double *peerSecWood;
    double *peerSecClay;
    double *peerSecIron;
    double *peerSecCorn;

    Time *time;
    Language **activeLanguage;

    QList<BuildingSocket*> *resourceList;
    QList<BuildingSocket*> *infrastructureList;

    //-----------Others-----------//
    QList<ItemBuildingHorizontal*> infrastructureItemList;
    QList<ItemBuildingHorizontal*> militaryItemList;
    QList<ItemBuildingHorizontal*> resourcesItemList;

    int idBuilding;

    void setBuildingInfo(ItemBuildingHorizontal *fBuilding);

    void findeRequestments();
    void createItems();
    void assignedItems();

    void createList();

    void setPointers(   NationType *fNation,
                        TravianWiki *fTravianWiki,
                        bool *fIsCapital,

                        int *fMaxWood,
                        int *fMaxClay,
                        int *fMaxIron,
                        int *fMaxCorn,

                        int *fProductionWood,
                        int *fProductionClay,
                        int *fProductionIron,
                        int *fProductionCorn,

                        int *fCurrentWood,
                        int *fCurrentClay,
                        int *fCurrentIron,
                        int *fCurrentCorn,
                        int *fCurrentCorn2,

                        double *fPeerSecWood,
                        double *fPeerSecClay,
                        double *fPeerSecIron,
                        double *fPeerSecCorn,

                        Time *fTime,
                        Language **fActiveLanguage,

                        QList<BuildingSocket*> *fResourceList,
                        QList<BuildingSocket*> *fInfrastructureList);


signals:

public slots:
    void selected(ItemBuildingHorizontal *tBuilding);

};

#endif // DIALOGBUILDINGTOBUILD_H
