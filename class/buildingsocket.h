#ifndef BUILDINGSOCKET_H
#define BUILDINGSOCKET_H

#include <QObject>

#include "building.h"
#include "buildingmapitem.h"
#include "item/itembuilding.h"
#include "travianwiki.h"
#include "Enums.h"
#include "language.h"

#include "widget/buttonlist.h"

#include "list/listitembuildtask.h"

#include "dialog/dialoggettime.h"



class BuildingSocket : public QObject
{
    Q_OBJECT
public:

    BuildingSocket(QObject *parent);

    bool itsIdBuilding40;

    Building building;
    BuildingMapItem *mapItem;
    ItemBuilding *itemBuilding;

    bool isResource;

    Time *time;

    int *currentWood;
    int *currentClay;
    int *currentIron;
    int *currentCorn;
    int *currentCorn2;

    int *maxWood;
    int *maxClay;
    int *maxIron;
    int *maxCorn;

    int *productionWood;
    int *productionClay;
    int *productionIron;
    int *productionCorn;

    double *peerSecWood;
    double *peerSecClay;
    double *peerSecIron;
    double *peerSecCorn;

    TravianWiki *travianWiki;
    NationType *nation;
    ListItemBuildTask *buildTaskBuildList;
    int *mainBuildingLvl;
    Language **activeLanguage;



    void setBuilding(Building fBuilding);
    void setNotExistBuilding(Building fBuilding);
    void setMapItem(BuildingMapItem *fMapItem);
    void setItemBuilding(ItemBuilding *fItemBuilding);
    void refresh();
    void setPointer(Time *fTime,
                    int *fCurrentWood,
                    int *fCurrentClay,
                    int *fCurrentIron,
                    int *fCurrentCorn,
                    int *fCurrentCorn2,

                    int *fMaxWood,
                    int *fMaxClay,
                    int *fMaxIron,
                    int *fMaxCorn,

                    int *fProductionWood,
                    int *fProductionClay,
                    int *fProductionIron,
                    int *fProductionCorn,

                    double *fPeerSecWood,
                    double *fPeerSecClay,
                    double *fPeerSecIron,
                    double *fPeerSecCorn,

                    TravianWiki *fTravianWiki,
                    NationType *fNation,
                    ListItemBuildTask *fBuildTaskBuildList,
                    int *fMainBuildingLvl,
                    Language **fActiveLanguage);

    //-----Menu-------//
    QMenu buildMenu;
    QWidgetAction *buildMenuActionBuildNow;
    QWidgetAction *buildMenuActionAddTask;
    QWidgetAction *buildMenuActionAddTaskOn;
    QWidgetAction *buildMenuActionAddTasks;
    QWidgetAction *buildMenuActionAddTasksOn;


    Button *buildMenuActionButtonBuildNow;
    Button *buildMenuActionButtonAddTask;
    Button *buildMenuActionButtonAddTaskOn;
    Button *buildMenuActionButtonAddTasks;
    Button *buildMenuActionButtonAddTasksOn;


    void showMenu(int Build0_Upgrade1, int *fMenuChoice, int *fLvlCount, Time *fTime, bool *save);
    void setMenuLanguage(int Build0_Upgrade1);

signals:
    void clickedBuild(int fIdPlace, int fMenuChoice, int fLvlCount, Time fTime);
    void clickedUpgrade(int fIdPlace, int fMenuChoice, int fLvlCount, Time fTime);
    void clickedBuildFortification(int fIdPlace, int fIdBuilding, int fMenuChoice, int fLvlCount, Time fTime);

public slots:
    void clicked();

    void actionTriggered();


};

#endif // BUILDINGSOCKET_H

