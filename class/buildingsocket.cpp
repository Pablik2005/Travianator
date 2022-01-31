#include "buildingsocket.h"

BuildingSocket::BuildingSocket(QObject *parent) :
    QObject(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    itsIdBuilding40 = false;

    /*
     * Build Now
     * Add Task
     * Add Task On
     * Add Tasks
     * Add Tasks On
     */
    buildMenuActionBuildNow = new QWidgetAction(&buildMenu);
    buildMenuActionButtonBuildNow = new Button(&buildMenu);
        buildMenuActionButtonBuildNow->setFramePolice(2);
        buildMenuActionButtonBuildNow->setMaximumHeight(25);

        buildMenuActionBuildNow->setDefaultWidget(buildMenuActionButtonBuildNow);
        connect(buildMenuActionButtonBuildNow, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    buildMenuActionAddTask = new QWidgetAction(&buildMenu);
        buildMenuActionButtonAddTask = new Button(&buildMenu);
        buildMenuActionButtonAddTask->setFramePolice(2);
        buildMenuActionButtonAddTask->setMaximumHeight(25);
        buildMenuActionAddTask->setDefaultWidget(buildMenuActionButtonAddTask);
        connect(buildMenuActionButtonAddTask, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    buildMenuActionAddTaskOn = new QWidgetAction(&buildMenu);
        buildMenuActionButtonAddTaskOn = new Button(&buildMenu);
        buildMenuActionButtonAddTaskOn->setFramePolice(2);
        buildMenuActionButtonAddTaskOn->setMaximumHeight(25);
        buildMenuActionAddTaskOn->setDefaultWidget(buildMenuActionButtonAddTaskOn);
        connect(buildMenuActionButtonAddTaskOn, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    buildMenuActionAddTasks = new QWidgetAction(&buildMenu);
        buildMenuActionButtonAddTasks = new Button(&buildMenu);
        buildMenuActionButtonAddTasks->setFramePolice(2);
        buildMenuActionButtonAddTasks->setMaximumHeight(25);
        buildMenuActionAddTasks->setDefaultWidget(buildMenuActionButtonAddTasks);
        connect(buildMenuActionButtonAddTasks, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    buildMenuActionAddTasksOn = new QWidgetAction(&buildMenu);
        buildMenuActionButtonAddTasksOn = new Button(&buildMenu);
        buildMenuActionButtonAddTasksOn->setFramePolice(2);
        buildMenuActionButtonAddTasksOn->setMaximumHeight(25);
        buildMenuActionAddTasksOn->setDefaultWidget(buildMenuActionButtonAddTasksOn);
        connect(buildMenuActionButtonAddTasksOn, SIGNAL(clicked()), this, SLOT(actionTriggered()));

    buildMenu.addAction(buildMenuActionBuildNow);
    buildMenu.addAction(buildMenuActionAddTask);
    buildMenu.addAction(buildMenuActionAddTaskOn);
    buildMenu.addAction(buildMenuActionAddTasks);
    buildMenu.addAction(buildMenuActionAddTasksOn);


}

void BuildingSocket::setBuilding(Building fBuilding)
{
    building = fBuilding;

    itemBuilding->building = &building;

    if(building.idBuilding != 0)
    {
        itemBuilding->setTitle( (*activeLanguage)->Buildings.at( building.idBuilding ));
        itemBuilding->setBuildingType(building.imgPath);
        itemBuilding->setUpgradeTime(building.upgradeLongTime.toString());
        itemBuilding->setBonus( building.bonus );
        itemBuilding->setBonusPast( building.bonusPast );


        if(!building.isResource && building.idBuilding != 31 && building.idBuilding != 32 && building.idBuilding != 33)
            mapItem->backGround->setPixmap(QPixmap::fromImage(QImage(building.imgPath)));
    }else
    {
        if(!building.isResource && !itsIdBuilding40)
            mapItem->setPlus();
        else if(itsIdBuilding40)
        {
            building = Building(40,(31 + *nation), 0, travianWiki);
            building.setUpgradeLongTime(travianWiki, *mainBuildingLvl);

            itemBuilding->setTitle( (*activeLanguage)->Buildings.at( building.idBuilding ));
            itemBuilding->setBuildingType(building.imgPath);
            itemBuilding->setUpgradeTime(building.upgradeLongTime.toString());
            itemBuilding->setBonus( building.bonus );
            itemBuilding->setBonusPast( building.bonusPast );
        }
    }
}

void BuildingSocket::setNotExistBuilding(Building fBuilding)
{
    this->setBuilding(fBuilding);
    building.isExist = false;
    refresh();
}

void BuildingSocket::setMapItem(BuildingMapItem *fMapItem)
{
    mapItem = fMapItem;
    connect(mapItem, SIGNAL(clicked()), this, SLOT(clicked()));
}

void BuildingSocket::setItemBuilding(ItemBuilding *fItemBuilding)
{
    itemBuilding = fItemBuilding;
    connect(itemBuilding, SIGNAL(clicked()), this, SLOT(clicked()));
}

void BuildingSocket::refresh()
{
    int tTime = time->secondsTo(Time::currentTime());

    if(building.idBuilding != 0)
    {
        if(building.lvl != building.maxLvl)
        {
            int timeToUpgrade = 0;

            //Woood
            int tCurrentWood = tTime * (*peerSecWood) + (*currentWood);
            if( tCurrentWood < building.woodToUpgrade )
            {

                int tTimeToUpgrade = (double) (building.woodToUpgrade - tCurrentWood) / (*peerSecWood);

                if(timeToUpgrade < tTimeToUpgrade)
                    timeToUpgrade = tTimeToUpgrade;

                itemBuilding->setWoodRed(building.woodToUpgrade);

                int tHours = tTimeToUpgrade / 3600;
                int tMinutes = tTimeToUpgrade % 3600 / 60;
                Time tTime(tHours, tMinutes, tTimeToUpgrade - (tHours * 3600 + tMinutes*60));
                itemBuilding->setWoodTime(tTime.toString());
            }else
            {
                itemBuilding->setWoodGreen(building.woodToUpgrade);
                itemBuilding->setWoodTime("");
            }

            //Clay
            int tCurrentClay = tTime * (*peerSecClay) + (*currentClay);
            if( tCurrentClay < building.clayToUpgrade )
            {

                int tTimeToUpgrade = (double) (building.clayToUpgrade - tCurrentClay) / (*peerSecClay);

                if(timeToUpgrade < tTimeToUpgrade)
                    timeToUpgrade = tTimeToUpgrade;

                itemBuilding->setClayRed(building.clayToUpgrade);

                int tHours = tTimeToUpgrade / 3600;
                int tMinutes = tTimeToUpgrade % 3600 / 60;
                Time tTime(tHours, tMinutes, tTimeToUpgrade - (tHours * 3600 + tMinutes*60));
                itemBuilding->setClayTime(tTime.toString());
            }else
            {
                itemBuilding->setClayGreen(building.clayToUpgrade);
                itemBuilding->setClayTime("");
            }

            //Iron
            int tCurrentIron = tTime * (*peerSecIron) + (*currentIron);
            if( tCurrentIron < building.ironToUpgrade )
            {

                int tTimeToUpgrade = (double) (building.ironToUpgrade - tCurrentIron) /(*peerSecIron);

                if(timeToUpgrade < tTimeToUpgrade)
                    timeToUpgrade = tTimeToUpgrade;

                itemBuilding->setIronRed(building.ironToUpgrade);

                int tHours = tTimeToUpgrade / 3600;
                int tMinutes = tTimeToUpgrade % 3600 / 60;
                Time tTime(tHours, tMinutes, tTimeToUpgrade - (tHours * 3600 + tMinutes*60));
                itemBuilding->setIronTime(tTime.toString());
            }else
            {
                itemBuilding->setIronGreen(building.ironToUpgrade);
                itemBuilding->setIronTime("");
            }

            //Corn
            int tCurrentCorn = tTime * (*peerSecCorn) + (*currentCorn);
            if( tCurrentCorn < building.cornToUpgrade )
            {     
                itemBuilding->setCornRed(building.cornToUpgrade);

                if(*peerSecCorn > 0)
                {
                    int tTimeToUpgrade = (double) (building.cornToUpgrade - tCurrentCorn) / (*peerSecCorn);

                    if(timeToUpgrade < tTimeToUpgrade)
                        timeToUpgrade = tTimeToUpgrade;

                    int tHours = tTimeToUpgrade / 3600;
                    int tMinutes = tTimeToUpgrade % 3600 / 60;
                    Time tTime(tHours, tMinutes, tTimeToUpgrade - (tHours * 3600 + tMinutes*60));
                    itemBuilding->setCornTime(tTime.toString());
                }else
                {
                    timeToUpgrade = 1;
                    itemBuilding->setCornTime("(-) Prod..");
                }

            }else
            {
                itemBuilding->setCornGreen(building.cornToUpgrade);
                itemBuilding->setCornTime("");
            }


            //Lvl
            if(timeToUpgrade == 0)
            {
                //Corn2
                if( building.idBuilding == 4 )
                {
                    building.canUpgrade = true;
                    itemBuilding->setCorn2Green( building.corn2ToUpgrade );
                }else if( (*currentCorn2) < building.corn2ToUpgrade )
                {
                    building.canUpgrade = false;
                    itemBuilding->setCorn2Red( building.corn2ToUpgrade );
                }else
                {
                    building.canUpgrade = true;
                    itemBuilding->setCorn2Green( building.corn2ToUpgrade );
                }

            }else
            {
                building.canUpgrade = false;
                itemBuilding->setCorn2Green( building.corn2ToUpgrade );
            }


            if(building.canUpgrade)
            {
                itemBuilding->setLvlGreen(building.lvl);
                mapItem->setGreen(building.lvl);
            }else
            {
                itemBuilding->setLvlRed(building.lvl);
                mapItem->setRed(building.lvl);
            }

            if(building.isUpgrading)
            {
                itemBuilding->setLvlBrown(building.lvl);
                mapItem->setBrown(building.lvl);
            }else if(!building.isExist)
            {
                itemBuilding->setLvlBlue(building.lvl);
                mapItem->setBlue(building.lvl);
            }

        }else
        {
            mapItem->setGold(building.lvl);
        }
    }
}

void BuildingSocket::setPointer(Time *fTime,
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
                                Language **fActiveLanguage)
{
    time = fTime;

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

    travianWiki = fTravianWiki;
    nation = fNation;
    buildTaskBuildList = fBuildTaskBuildList;
    mainBuildingLvl = fMainBuildingLvl;
    activeLanguage = fActiveLanguage;
}

void BuildingSocket::showMenu(int Build0_Upgrade1, int *fMenuChoice, int *fLvlCount, Time *fTime, bool *save)
{
    *fMenuChoice = -1;
    setMenuLanguage(Build0_Upgrade1);

    buildMenu.setGeometry(QCursor::pos().x(), QCursor::pos().y(),buildMenu.size().width(),buildMenu.size().height());
    QAction *tAction = buildMenu.exec();

    *fLvlCount = 0;
    for(int i=0; i<buildMenu.actions().count(); i++)
        if(buildMenu.actions().at(i) == tAction)
        {
            *fMenuChoice = i;
            break;
        }

    if(*fMenuChoice == 0 || *fMenuChoice == 1)
        *save = true;

    switch(*fMenuChoice)
    {
    case 2 :
        {
            DialogGetTime tDialog((QWidget*) this->parent());
            tDialog.setLanguage(activeLanguage);
            tDialog.exec();

            if(tDialog.save)
            {
                fTime->setHMS(tDialog.time);
                *save = true;
            }
        }
        break;
    case 3 :
        {
            bool okPressed;
            QInputDialog tDialog((QWidget*) this->parent());
            int tInt = tDialog.getInt((QWidget*) this->parent(), "Get lvl", "Lvl (Max: "+QString::number(building.maxLvl)+")", building.lvl+1, building.lvl+1, building.maxLvl,1, &okPressed);

            if(okPressed)
            {
                *fLvlCount = tInt-building.lvl;
                *save = true;
            }
        }
        break;
    case 4 :
        {
            bool okPressed;
            QInputDialog tDialog((QWidget*) this->parent());
            int tInt = tDialog.getInt((QWidget*) this->parent(), "Get lvl", "Lvl (Max: "+QString::number(building.maxLvl)+")", building.lvl+1, building.lvl+1, building.maxLvl,1, &okPressed);

            if(okPressed)
            {
                DialogGetTime tDialog((QWidget*) this->parent());
                tDialog.setLanguage(activeLanguage);
                tDialog.exec();

                if(tDialog.save)
                {
                    fTime->setHMS(tDialog.time);
                    *fLvlCount = tInt-building.lvl;
                    *save = true;
                }
            }
        }
        break;
    }

}

void BuildingSocket::setMenuLanguage(int Build0_Upgrade1)
{
    if(Build0_Upgrade1 == 0)
        buildMenuActionButtonBuildNow->setText( (*activeLanguage)->BuildMenuBuildNow );
    else
        buildMenuActionButtonBuildNow->setText( (*activeLanguage)->BuildMenuUpgradeNow );

    buildMenuActionButtonAddTaskOn->setText( (*activeLanguage)->BuildMenuAddTaskOn );
    buildMenuActionButtonAddTask->setText( (*activeLanguage)->BuildMenuAddTask );
    buildMenuActionButtonAddTasks->setText( (*activeLanguage)->BuildMenuAddTasks );
    buildMenuActionButtonAddTasksOn->setText( (*activeLanguage)->BuildMenuAddTasksOn );
}



void BuildingSocket::clicked()
{

    //Wybydowane
    if(building.idBuilding != 0)
    {
        if(building.lvl != building.maxLvl)
        {
            //Upgrade
            if(building.idPlace != 40 || building.lvl > 0)
            {
                int menuChoice;
                int lvlCount;
                Time time(0,0,0);

                bool tSave = false;
                showMenu(1, &menuChoice, &lvlCount, &time, &tSave);

                if(tSave)
                    emit clickedUpgrade(building.idPlace, menuChoice, lvlCount, time);
            }
            //Budowanie
            else
            {
                int menuChoice;
                int lvlCount;
                Time time;

                bool tSave = false;
                showMenu(0, &menuChoice, &lvlCount, &time, &tSave);

                if(tSave)
                    emit clickedBuildFortification(40, (31 + *nation), menuChoice, lvlCount, time);
            }
        }
    //Plac budowy
    }else
    {
        building.lvl = 1;
        building.maxLvl = 25;

        int menuChoice;
        int lvlCount;
        Time time;

        bool tSave = false;
        showMenu(0, &menuChoice, &lvlCount, &time, &tSave);

        if(tSave)
            emit clickedBuild(building.idPlace, menuChoice, lvlCount, time);
    }

}

void BuildingSocket::actionTriggered()
{
}


