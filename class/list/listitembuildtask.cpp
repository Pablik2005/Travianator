#include "listitembuildtask.h"

ListItemBuildTask::ListItemBuildTask(QWidget *parent)
{
    this->setParent(parent);

    isHorizontal=false;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    page->setGeometry(0,0,130,170);

    setItemSize(130,185);

}

void ListItemBuildTask::addTask(Task fTask)
{
    ItemBuildTask *tItem = new ItemBuildTask(page);
    tItem->task = fTask;

    tItem->setBuildingType(fTask.imgPath);
    tItem->setTitle( (*activeLanguage)->Buildings.at( tItem->task.idBuilding ));


    tItem->show();
    itemList.append( (Item*)tItem );

    connect(tItem, SIGNAL(clicked(ItemBuildTask*)), this, SLOT(clicked(ItemBuildTask*)));
    connect(tItem, SIGNAL(mouseMoveSignal(QMouseEvent*)), this, SLOT(mouseMoveSlot(QMouseEvent*)));
    connect(tItem, SIGNAL(mousePressSignal(QMouseEvent*)), this, SLOT(mousePressSlot(QMouseEvent*)));
    connect(tItem, SIGNAL(mouseReleaseSignal(QMouseEvent*)), this, SLOT(mouseReleaseSlot(QMouseEvent*)));

    page->setGeometry(0,0, itemSize.width(), itemSize.height()* itemList.count());
}

void ListItemBuildTask::clear()
{
    foreach(Item *i, itemList)
        delete (ItemBuildTask*)i;

    itemList.clear();
    page->setGeometry(0,0,0,0);
}

void ListItemBuildTask::refresh()
{


    if(itemList.count())
    {
        if(*nation == 0)
            refreshRomans();
        else
            refreshNotRomans();

    }



}

void ListItemBuildTask::refreshRomans()
{
    int tTime = time->secondsTo(Time::currentTime());

    Time timeBuildingConstructionResources(0,0,0);
    Time timeBuildingConstructionInfrastructure(0,0,0);

    foreach(Building i, buildingInConstrction)
        if( i.isResource)
        {
            if( i.timeToUpgradeEnd.addSeconds(-tTime) > timeBuildingConstructionResources )
                timeBuildingConstructionResources.setHMS(i.timeToUpgradeEnd.addSeconds(-tTime));
        }else
        {
            if( i.timeToUpgradeEnd.addSeconds(-tTime) > timeBuildingConstructionInfrastructure )
                timeBuildingConstructionInfrastructure.setHMS(i.timeToUpgradeEnd.addSeconds(-tTime));
        }

    int totalWood = 0;
    int totalClay = 0;
    int totalIron = 0;
    int totalCorn = 0;
    int totalCorn2 = 0;

    int tCurrentWood = tTime * (*peerSecWood) + (*currentWood);
    int tCurrentClay = tTime * (*peerSecClay) + (*currentClay);
    int tCurrentIron = tTime * (*peerSecIron) + (*currentIron);
    int tCurrentCorn = tTime * (*peerSecCorn) + (*currentCorn);
    int tCorn2 = (*currentCorn2);

    for(int i=0; i<itemList.count(); i++)
    {
        itemList.at(i)->setGeometry(0,i*itemSize.height(),itemSize.width(),itemSize.height());

        totalWood += ((ItemBuildTask*) itemList.at(i))->task.neededWood;
        totalClay += ((ItemBuildTask*) itemList.at(i))->task.neededClay;
        totalIron += ((ItemBuildTask*) itemList.at(i))->task.neededIron;
        totalCorn += ((ItemBuildTask*) itemList.at(i))->task.neededCorn;
        totalCorn2 += ((ItemBuildTask*) itemList.at(i))->task.neededCorn2;

        ((ItemBuildTask*) itemList.at(i))->setUpgradeTime( ((ItemBuildTask*) itemList.at(i))->task.buildingTime.toString() );
        ((ItemBuildTask*) itemList.at(i))->setBonus( ((ItemBuildTask*) itemList.at(i))->task.bonus );
        ((ItemBuildTask*) itemList.at(i))->setBonusPast( ((ItemBuildTask*) itemList.at(i))->task.bonusPast );

        int timeToResourceEnough = 0;

        //Woood
        if( tCurrentWood < totalWood )
        {

            int tTimeToResourceEnough = (double) (totalWood - tCurrentWood) / (*peerSecWood);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setWoodRed(totalWood - tCurrentWood);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setWoodTime(tTime.toString());

        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setWoodGreen(tCurrentWood - totalWood);
            ((ItemBuildTask*) itemList.at(i))->setWoodTime("");
        }

        //Clay
        if( tCurrentClay < totalClay )
        {

            int tTimeToResourceEnough = (double) (totalClay - tCurrentClay) / (*peerSecClay);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setClayRed(totalClay - tCurrentClay);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setClayTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setClayGreen(tCurrentClay - totalClay);
            ((ItemBuildTask*) itemList.at(i))->setClayTime("");
        }

        //Iron
        if( tCurrentIron < totalIron )
        {

            int tTimeToResourceEnough = (double) (totalIron - tCurrentIron) / (*peerSecIron);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setIronRed(totalIron - tCurrentIron);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setIronTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setIronGreen(tCurrentIron - totalIron);
            ((ItemBuildTask*) itemList.at(i))->setIronTime("");
        }

        //Corn
        if( tCurrentCorn < totalCorn )
        {

            int tTimeToResourceEnough = (double) (totalCorn - tCurrentCorn) / (*peerSecCorn);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setCornRed(totalCorn - tCurrentCorn);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setCornTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setCornGreen(tCurrentCorn - totalCorn);
            ((ItemBuildTask*) itemList.at(i))->setCornTime("");
        }

        //Corn2
        if( ((ItemBuildTask*) itemList.at(i))->task.idBuilding == 4 )
        {
            tCorn2+=3;
            ((ItemBuildTask*) itemList.at(i))->setCorn2Green(tCorn2);
        }
        else if( (tCorn2) < totalCorn2 )
            ((ItemBuildTask*) itemList.at(i))->setCorn2Red(totalCorn2 - tCorn2);
        else
            ((ItemBuildTask*) itemList.at(i))->setCorn2Green(tCorn2 - totalCorn2);

        //Lvl
        if(timeToResourceEnough == 0 && (tCorn2) >= totalCorn2)
        {
            ((ItemBuildTask*) itemList.at(i))->setLvlGreen(((ItemBuildTask*) itemList.at(i))->task.lvl);
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setLvlRed(((ItemBuildTask*) itemList.at(i))->task.lvl);
        }

        // Key Time
        if(Time::currentTime() >= ((ItemBuildTask*) itemList.at(i))->task.buildOn)
            ((ItemBuildTask*) itemList.at(i))->setKeyHidden();
        else
        {
            ((ItemBuildTask*) itemList.at(i))->setKeyTime( (((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime()).toString() );
        }

        // Avaible Time
        // Resource
        if( ((ItemBuildTask*) itemList.at(i))->task.isResource )
        {
            QList<Time> tList;
            tList.append( Time().fromSeconds(timeToResourceEnough) );
            tList.append( timeBuildingConstructionResources );
            tList.append( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );

            int index = Time::returnTheLongestTimeIndex(tList);


            if( index == -1)
            {
                if(*isFieldOfCornBuilding)
                {
                    ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ).toString() );
                    ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ) );
                    timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime ) +  Time::toSeconds(((ItemBuildTask*) itemList.at(i))->task.timeToWait)));
                }

            }else if( index == 0 )
            {
                int tHours = timeToResourceEnough / 3600;
                int tMinutes = timeToResourceEnough % 3600 / 60;
                Time tTime(tHours, tMinutes, timeToResourceEnough - (tHours * 3600 + tMinutes*60));
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(tTime.toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( tTime );

                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( timeToResourceEnough + Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));


            }else if( index == 1 )
            {
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(timeBuildingConstructionResources.toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( timeBuildingConstructionResources );
                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));

            }else if( index == 2 )
            {
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( (((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime()).toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );
                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() )));
            }

        // Infrastructure
        }else
        {
            QList<Time> tList;
            tList.append( Time().fromSeconds(timeToResourceEnough) );
            tList.append( timeBuildingConstructionInfrastructure );
            tList.append( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );

            int index = Time::returnTheLongestTimeIndex(tList);

            if( index == -1)
            {
                if(*isFieldOfCornBuilding)
                {
                    ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ).toString() );
                    ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ) );
                    timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime ) +  Time::toSeconds(((ItemBuildTask*) itemList.at(i))->task.timeToWait)));
                }

            }else if( index == 0 )
            {
                int tHours = timeToResourceEnough / 3600;
                int tMinutes = timeToResourceEnough % 3600 / 60;
                Time tTime(tHours, tMinutes, timeToResourceEnough - (tHours * 3600 + tMinutes*60));
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(tTime.toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( tTime );

                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( timeToResourceEnough + Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));


            }else if( index == 1 )
            {
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(timeBuildingConstructionInfrastructure.toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( timeBuildingConstructionInfrastructure );
                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));

            }else if( index == 2 )
            {
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( (((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime()).toString());
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );
                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() )));
            }
        }
    }
}

void ListItemBuildTask::refreshNotRomans()
{
    int tTime = time->secondsTo(Time::currentTime());

    Time timeBuildingConstruction(0,0,0);

    foreach(Building i, buildingInConstrction)
        if( i.timeToUpgradeEnd.addSeconds(-tTime) > timeBuildingConstruction )
            timeBuildingConstruction.setHMS(i.timeToUpgradeEnd.addSeconds(-tTime));

    int totalWood = 0;
    int totalClay = 0;
    int totalIron = 0;
    int totalCorn = 0;
    int totalCorn2 = 0;

    int tCurrentWood = tTime * (*peerSecWood) + (*currentWood);
    int tCurrentClay = tTime * (*peerSecClay) + (*currentClay);
    int tCurrentIron = tTime * (*peerSecIron) + (*currentIron);
    int tCurrentCorn = tTime * (*peerSecCorn) + (*currentCorn);
    int tCorn2 = (*currentCorn2);

    for(int i=0; i<itemList.count(); i++)
    {
        itemList.at(i)->setGeometry(0,i*170,130,170);

        totalWood += ((ItemBuildTask*) itemList.at(i))->task.neededWood;
        totalClay += ((ItemBuildTask*) itemList.at(i))->task.neededClay;
        totalIron += ((ItemBuildTask*) itemList.at(i))->task.neededIron;
        totalCorn += ((ItemBuildTask*) itemList.at(i))->task.neededCorn;
        totalCorn2 += ((ItemBuildTask*) itemList.at(i))->task.neededCorn2;

        ((ItemBuildTask*) itemList.at(i))->setUpgradeTime( ((ItemBuildTask*) itemList.at(i))->task.buildingTime.toString() );

        int timeToResourceEnough = 0;

        //Woood
        if( tCurrentWood < totalWood )
        {

            int tTimeToResourceEnough = (double) (totalWood - tCurrentWood) / (*peerSecWood);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setWoodRed(totalWood - tCurrentWood);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setWoodTime(tTime.toString());

        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setWoodGreen(tCurrentWood - totalWood);
            ((ItemBuildTask*) itemList.at(i))->setWoodTime("");
        }

        //Clay
        if( tCurrentClay < totalClay )
        {

            int tTimeToResourceEnough = (double) (totalClay - tCurrentClay) / (*peerSecClay);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setClayRed(totalClay - tCurrentClay);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setClayTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setClayGreen(tCurrentClay - totalClay);
            ((ItemBuildTask*) itemList.at(i))->setClayTime("");
        }

        //Iron
        if( tCurrentIron < totalIron )
        {

            int tTimeToResourceEnough = (double) (totalIron - tCurrentIron) / (*peerSecIron);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setIronRed(totalIron - tCurrentIron);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setIronTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setIronGreen(tCurrentIron - totalIron);
            ((ItemBuildTask*) itemList.at(i))->setIronTime("");
        }

        //Corn
        if( tCurrentCorn < totalCorn )
        {

            int tTimeToResourceEnough = (double) (totalCorn - tCurrentCorn) / (*peerSecCorn);

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;

            ((ItemBuildTask*) itemList.at(i))->setCornRed(totalCorn - tCurrentCorn);

            int tHours = tTimeToResourceEnough / 3600;
            int tMinutes = tTimeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, tTimeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setCornTime(tTime.toString());
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setCornGreen(tCurrentCorn - totalCorn);
            ((ItemBuildTask*) itemList.at(i))->setCornTime("");
        }

        //Corn2
        if( ((ItemBuildTask*) itemList.at(i))->task.idBuilding == 4 )
        {
            tCorn2+=3;
            ((ItemBuildTask*) itemList.at(i))->setCorn2Green(tCorn2);
        }
        else if( (tCorn2) < totalCorn2 )
            ((ItemBuildTask*) itemList.at(i))->setCorn2Red(totalCorn2 - tCorn2);
        else
            ((ItemBuildTask*) itemList.at(i))->setCorn2Green(tCorn2 - totalCorn2);

        //Lvl
        if(timeToResourceEnough == 0 && tCorn2 >= totalCorn2)
        {
            ((ItemBuildTask*) itemList.at(i))->setLvlGreen(((ItemBuildTask*) itemList.at(i))->task.lvl);
        }else
        {
            ((ItemBuildTask*) itemList.at(i))->setLvlRed(((ItemBuildTask*) itemList.at(i))->task.lvl);
        }

        // Key Time
        if(Time::currentTime() >= ((ItemBuildTask*) itemList.at(i))->task.buildOn)
            ((ItemBuildTask*) itemList.at(i))->setKeyHidden();
        else
        {
            ((ItemBuildTask*) itemList.at(i))->setKeyTime( (((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime()).toString() );
        }

        // Avaible Time
        // Resource
        QList<Time> tList;
        tList.append( Time().fromSeconds(timeToResourceEnough) );
        tList.append( timeBuildingConstruction );
        tList.append( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );

        int index = Time::returnTheLongestTimeIndex(tList);

        if( index == -1)
        {
            if(*isFieldOfCornBuilding)
            {
                ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ).toString() );
                ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( fieldOfCornBuildingEnd->addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(*time)) ) );
                timeBuildingConstruction.setHMS( timeBuildingConstruction.addSeconds( timeToResourceEnough + Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));

            }

        }else if( index == 0 )
        {
            int tHours = timeToResourceEnough / 3600;
            int tMinutes = timeToResourceEnough % 3600 / 60;
            Time tTime(tHours, tMinutes, timeToResourceEnough - (tHours * 3600 + tMinutes*60));
            ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(tTime.toString());
            ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( tTime );
            timeBuildingConstruction.setHMS( timeBuildingConstruction.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime ) +  Time::toSeconds(((ItemBuildTask*) itemList.at(i))->task.timeToWait)));

        }else if( index == 1 )
        {
            ((ItemBuildTask*) itemList.at(i))->setAvaibleTime(timeBuildingConstruction.toString());
            ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( timeBuildingConstruction );
            timeBuildingConstruction.setHMS( timeBuildingConstruction.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildingTime )));

        }else if( index == 2 )
        {
            ((ItemBuildTask*) itemList.at(i))->setAvaibleTime( (((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime()).toString());
            ((ItemBuildTask*) itemList.at(i))->task.timeToWait.setHMS( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() );
            timeBuildingConstruction.setHMS( timeBuildingConstruction.addSeconds( Time::toSeconds( ((ItemBuildTask*) itemList.at(i))->task.buildOn - Time::currentTime() )));
        }
    }
}

void ListItemBuildTask::setPointer(Time *fTime,
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
                                   Language **fActiveLanguage)
{
    time = fTime;
    isFieldOfCornBuilding = fIsFieldOfCornBuilding;
    fieldOfCornBuildingEnd = fFieldOfCornBuildingEnd;

    currentWood = fCurrentWood;
    currentClay = fCurrentClay;
    currentIron = fCurrentIron;
    currentCorn = fCurrentCorn;
    currentCorn2 = fCurrentCorn2;

    maxWood = fMaxWood;
    maxClay = fMaxClay;
    maxIron = fMaxIron;
    maxCorn = fMaxCorn;

    productionWood = fProductionWood;
    productionClay = fProductionClay;
    productionIron = fProductionIron;
    productionCorn = fProductionCorn;

    peerSecWood = fPeerSecWood;
    peerSecClay = fPeerSecClay;
    peerSecIron = fPeerSecIron;
    peerSecCorn = fPeerSecCorn;

    nation = fNation;
    activeLanguage = fActiveLanguage;

}

void ListItemBuildTask::clicked(ItemBuildTask *Item)
{
    for(int i=0; i<itemList.count(); i++)
    {
        if(((ItemBuildTask*) itemList.at(i)) == Item)
        {
            emit clicked(i);
            break;
        }
    }
}

