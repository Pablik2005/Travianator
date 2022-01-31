#ifndef LISTITEMBUILDTASK_H
#define LISTITEMBUILDTASK_H

#include "list.h"
#include "../language.h"
#include "../item/itembuildtask.h"
#include "../time.h"


class ListItemBuildTask: public List
{
    Q_OBJECT
public:
    ListItemBuildTask(QWidget *parent);

    Time *time;
    NationType *nation;
    bool *isFieldOfCornBuilding;
    Time *fieldOfCornBuildingEnd;

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

    Language **activeLanguage;

    QList<Building> buildingInConstrction;


    void addTask(Task fTask);
    void clear();
    void refresh();
    void refreshRomans();
    void refreshNotRomans();

    void setPointer(Time *fTime,
                    bool *fIsFieldOfCornBuilding,
                    Time *fFieldOfCornBuildingEnd,

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
                    NationType *fNation,
                    Language **fActiveLanguage);

signals:
    void clicked(int index);

public slots:
    void clicked(ItemBuildTask *Item);

};

#endif // LISTITEMBUILDTASK_H

