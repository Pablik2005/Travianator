#include "dialogbuildingtobuild.h"

DialogBuildingToBuild::DialogBuildingToBuild(QWidget *parent) :
    QDialog(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    tabWidget = new QTabWidget(this);
        mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(tabWidget);

    this->setLayout(mainLayout);
        mainLayout->setMargin(0);
        //this->setMinimumSize(600, 300);
        //this->setMaximumSize(600, 300);
        this->setMinimumWidth(600);
        this->setMinimumHeight(300);
        this->setMaximumHeight(300);

    pageInfrastructure = new QWidget(tabWidget);
        infrastructureList1 = new List(pageInfrastructure, true);
            infrastructureList1->setStyleSheet("border-color: white");;
            infrastructureList1->setItemSize(215, 90);
            infrastructureList1->setMaximumHeight(110);
            infrastructureList1->setMaximumHeight(110);
        infrastructureList2 = new List(pageInfrastructure, true);
            infrastructureList2->setStyleSheet("border-color: white");
            infrastructureList2->setItemSize(215, 90);
            infrastructureList2->setMaximumHeight(110);
            infrastructureList2->setMaximumHeight(110);
        infrastructureLayout = new QVBoxLayout(this);
            infrastructureLayout->setMargin(0);
            infrastructureLayout->addWidget(infrastructureList1);
            infrastructureLayout->addWidget(infrastructureList2);
            pageInfrastructure->setLayout(infrastructureLayout);

    pageMilitary = new QWidget(tabWidget);
        militaryList1 = new List(pageMilitary, true);
            militaryList1->setStyleSheet("border-color: white");
            militaryList1->setItemSize(215, 90);
            militaryList1->setMaximumHeight(110);
            militaryList1->setMaximumHeight(110);
        militaryList2 = new List(pageMilitary, true);
            militaryList2->setStyleSheet("border-color: white");
            militaryList2->setItemSize(215, 90);
            militaryList2->setMaximumHeight(110);
            militaryList2->setMaximumHeight(110);
        militaryLayout = new QVBoxLayout(this);
            militaryLayout->setMargin(0);
            militaryLayout->addWidget(militaryList1);
            militaryLayout->addWidget(militaryList2);
            pageMilitary->setLayout(militaryLayout);

    pageResources = new QWidget(tabWidget);
        resourcesList1 = new List(pageResources, true);
            resourcesList1->setStyleSheet("border-color: white");
            resourcesList1->setItemSize(215, 90);
            resourcesList1->setMaximumHeight(110);
            resourcesList1->setMaximumHeight(110);
        resourcesList2 = new List(pageResources, true);
            resourcesList2->setStyleSheet("border-color: white");
            resourcesList2->setItemSize(215, 90);
            resourcesList2->setMaximumHeight(110);
            resourcesList2->setMaximumHeight(110);
        resourcesLayout = new QVBoxLayout(this);
            resourcesLayout->setMargin(0);
            resourcesLayout->addWidget(resourcesList1);
            resourcesLayout->addWidget(resourcesList2);
            pageResources->setLayout(resourcesLayout);


    tabWidget->addTab(pageInfrastructure,"Infrastructure");
    tabWidget->addTab(pageMilitary,"Military");
    tabWidget->addTab(pageResources,"Resources");

    this->setWindowTitle("Buildings");
}

void DialogBuildingToBuild::setPointers( NationType *fNation,
                                       TravianWiki *fTravianWiki,
                                       bool *fIsCapitol,

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
                                       QList<BuildingSocket*> *fInfrastructureList)
{
    nation = fNation;
    travianWiki = fTravianWiki;
    isCapitol = fIsCapitol;

    maxWood = fMaxWood;
    maxClay = fMaxClay;
    maxIron = fMaxIron;
    maxCorn = fMaxCorn;

    productionWood = fProductionWood;
    productionClay = fProductionClay;
    productionIron = fProductionIron;
    productionCorn = fProductionCorn;

    currentWood = fCurrentWood;
    currentClay = fCurrentClay;
    currentIron = fCurrentIron;
    currentCorn = fCurrentCorn;
    currentCorn2 = fCurrentCorn2;

    peerSecWood = fPeerSecWood;
    peerSecClay = fPeerSecClay;
    peerSecIron = fPeerSecIron;
    peerSecCorn = fPeerSecCorn;

    time = fTime;
    activeLanguage = fActiveLanguage;

    resourceList = fResourceList;
    infrastructureList = fInfrastructureList;
}

void DialogBuildingToBuild::selected(ItemBuildingHorizontal *tBuilding)
{
    idBuilding = tBuilding->idBuilding;
    close();
}

void DialogBuildingToBuild::findeRequestments()
{

    forest = -1;
    clayMine = -1;
    ironMine = -1;
    fildOfCorn = -1;
    sawmill = -1;
    brickyard = -1;
    ironFoundry = -1;
    grainMill = -1;
    bakery = -1;

    warehouse = -1;
    granary = -1;
    mainBuilding = -1;
    marketplace = -1;
    embassy = -1;
    cranny = -1;
    townHall = -1;
    residence = -1;
    palace = -1;
    treasury = -1;
    tradeOffice = -1;
    stonemason = -1;
    brewery = -1;
    greatWarehouse = -1;
    greatGranary = -1;
    wonderOfTheWorld = -1;
    wateringPlacenary = -1;

    workshopArmorer = -1;
    tournamentSquare = -1;
    rallyPoint = -1;
    barracks = -1;
    stable = -1;
    workshop = -1;
    academy = -1;
    greatBarracks = -1;
    greatStable = -1;
    cityWall = -1;
    earthWall = -1;
    palisade = -1;
    trapper = -1;
    heroMansion = -1;

    warehouseSum = 0;
    granarySum = 0;
    greatWarehouseSum = 0;
    greatGranarySum = 0;
    crannySum = 0;
    trapperSum = 0;

    foreach(BuildingSocket *i, *infrastructureList)
    {
        switch(i->building.idBuilding)
        {
            //---------------------Resource---------------------//
            //Tartak
            case 5 :
            {
                sawmill = i->building.lvl;

            }break;
            //Cegielnia
            case 6 :
            {
                brickyard = i->building.lvl;

            }break;
            //Huta Stali
            case 7 :
            {
                ironFoundry = i->building.lvl;

            }break;
            //Młyn
            case 8 :
            {
                grainMill = i->building.lvl;

            }break;
            //Piekarnia
            case 9 :
            {
                bakery = i->building.lvl;

            }break;
            //---------------------Infrastructure---------------------//
            //Magazyn
            case 10 :
            {
                if(warehouse < i->building.lvl)
                    warehouse = i->building.lvl;
                warehouseSum += i->building.lvl;

            }break;
            //Spichlerz
            case 11 :
            {
                if(granary < i->building.lvl)
                    granary = i->building.lvl;
                granarySum += i->building.lvl;

            }break;
            //Główny Budynek
            case 15 :
            {
                mainBuilding = i->building.lvl;

            }break;
            //Rynek
            case 17 :
            {
                marketplace = i->building.lvl;
            }break;
            //Ambasada
            case 18 :
            {
                embassy = i->building.lvl;
            }break;
            //Kryjówka
            case 23 :
            {
                if(cranny < i->building.lvl)
                    cranny = i->building.lvl;
                crannySum += i->building.lvl;

            }break;
            //Ratusz
            case 24 :
            {
                townHall = i->building.lvl;
            }break;
            //Rezydencja
            case 25 :
            {
                residence = i->building.lvl;
            }break;
            //Pałac
            case 26 :
            {
                palace = i->building.lvl;
            }break;
            //Skarbiec
            case 27 :
            {
                treasury = i->building.lvl;
            }break;
            //Targ
            case 28 :
            {
                 tradeOffice = i->building.lvl;
            }break;
            //Kamieniaż
            case 34 :
            {
                stonemason = i->building.lvl;
            }break;
            //Browar
            case 35 :
            {
                brewery = i->building.lvl;
            }break;
            //Duży Magazyn
            case 38 :
            {
                if(greatWarehouse < i->building.lvl)
                    greatWarehouse = i->building.lvl;
                greatWarehouseSum += i->building.lvl;
            }break;
            //Duży Spichlerz
            case 39 :
            {
                if(greatGranary < i->building.lvl)
                    greatGranary = i->building.lvl;
                greatGranarySum += i->building.lvl;
            }break;
            //Cud Świata
            case 40 :
            {
                wonderOfTheWorld = i->building.lvl;
            }break;
            //Wodopój
            case 41 :
            {
                wateringPlacenary = i->building.lvl;
            }break;
            //---------------------Military---------------------//
            //Warsztat Płatnerza
            case 13 :
            {
                workshopArmorer = i->building.lvl;
            }break;
            //Plac Turniejowy
            case 14 :
            {
                tournamentSquare = i->building.lvl;
            }break;
            //Miejsce Zbiórki
            case 16 :
            {
                 rallyPoint = i->building.lvl;
            }break;
            //Koszary
            case 19 :
            {
                barracks = i->building.lvl;
            }break;
            //Stajnia
            case 20 :
            {
                stable = i->building.lvl;
            }break;
            //Warsztat
            case 21 :
            {
                workshop = i->building.lvl;
            }break;
            //Akademia
            case 22 :
            {
                academy = i->building.lvl;
            }break;
            //Duże Koszary
            case 29 :
            {
                greatGranary = i->building.lvl;
            }break;
            //Duża Stajnia
            case 30 :
            {
                greatStable = i->building.lvl;
            }break;
            //Mury Obronne
            case 31 :
            {
                cityWall = i->building.lvl;
            }break;
            //Wały
            case 32 :
            {
                earthWall = i->building.lvl;
            }break;
            //Palisada
            case 33 :
            {
                palisade = i->building.lvl;
            }break;
            //Chata Trapera
            case 36 :
            {
                if(trapper < i->building.lvl)
                    trapper = i->building.lvl;
                trapperSum += i->building.lvl;
            }break;
            //Dwór Bohatera
            case 37 :
            {
                heroMansion = i->building.lvl;
            }break;
        }
    }


    forest = -1;
    clayMine = -1;
    ironMine = -1;
    fildOfCorn = -1;

    foreach(BuildingSocket *i, *resourceList)
    {
        switch(i->building.idBuilding)
        {
            //Las
            case 1 :
                {
                    if(forest < i->building.lvl)
                        forest = i->building.lvl;

                }break;
            //Kopalnia Gliny
            case 2 :
                {
                    if(clayMine < i->building.lvl)
                        clayMine = i->building.lvl;
                }break;
            //Kopalnia Żelaza
            case 3 :
                {
                    if(ironMine < i->building.lvl)
                        ironMine = i->building.lvl;
                }break;
            //Pole Zboża
            case 4 :
                {
                    if(fildOfCorn < i->building.lvl)
                        fildOfCorn = i->building.lvl;
                }break;
        }
    }
}

void DialogBuildingToBuild::createItems()
{
    ItemBuildingHorizontal *tBuilding;

    //-------------------------------------------------------------------------------//
    //Infrastructure
    //-------------------------------------------------------------------------------//
    foreach(ItemBuildingHorizontal *i, infrastructureItemList)
        delete i;
    infrastructureItemList.clear();

    //---------------------------------------------//
    //Magazyn
    //---------------------------------------------//
    if(warehouse >= 1)
    {
        if(warehouseSum%20 == 0)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(10) );
            tBuilding->idBuilding = 10;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }
    }else if(mainBuilding >= 1)
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(10) );
        tBuilding->idBuilding = 10;
        setBuildingInfo(tBuilding);
        infrastructureItemList.append(tBuilding);

    }else
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setBuildingType(10);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(10) );
        tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) + " 1");
        tBuilding->idList = 3;
        infrastructureItemList.append(tBuilding);
    }
    //---------------------------------------------//
    //Spichlerz
    //---------------------------------------------//
    if(granary >= 1)
    {
        if(granarySum%20 == 0)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(11) );
            tBuilding->idBuilding = 11;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }
    }else if(mainBuilding >= 1)
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(11) );
        tBuilding->idBuilding = 11;
        setBuildingInfo(tBuilding);
        infrastructureItemList.append(tBuilding);

    }else
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setBuildingType(10);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(11) );
        tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) + " 1");
        tBuilding->idList = 3;
        infrastructureItemList.append(tBuilding);
    }
    //---------------------------------------------//
    //Główny Budynek
    //---------------------------------------------//
    if(mainBuilding < 1)
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(15) );
        tBuilding->idBuilding = 15;
        setBuildingInfo(tBuilding);
        infrastructureItemList.append(tBuilding);
    }
    //---------------------------------------------//
    //Rynek
    //---------------------------------------------//
    if(marketplace < 1)
    {
        if(mainBuilding >= 1 && warehouse >=1 && granary >= 1)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(17) );
            tBuilding->idBuilding = 17;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(17);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(17) );

            if( mainBuilding >= 1 )
                tBuilding->setReq1Green( (*activeLanguage)->Buildings.at(15) +" 1");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 1");

            if( warehouse >=1 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(11) +" 1");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(11) +" 1");

            if( granary >= 1 )
                tBuilding->setReq3Green((*activeLanguage)->Buildings.at(10) +" 1");
            else
                tBuilding->setReq3Red((*activeLanguage)->Buildings.at(10) +" 1");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Ambasada
    //---------------------------------------------//
    if(embassy < 1)
    {
        if(mainBuilding >= 1)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(18) );
            tBuilding->idBuilding = 18;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(18);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(18) );
            tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 1");
            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Kryjówka
    //---------------------------------------------//
    if(cranny >= 1)
    {
        if(crannySum%10 == 0)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(23) );
            tBuilding->idBuilding = 23;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }
    }else
    {
        tBuilding = new ItemBuildingHorizontal(this);
        tBuilding->setTitle( (*activeLanguage)->Buildings.at(23) );
        tBuilding->idBuilding = 23;
        setBuildingInfo(tBuilding);
        infrastructureItemList.append(tBuilding);

    }
    //---------------------------------------------//
    //Ratusz
    //---------------------------------------------//
    if(townHall < 1)
    {
        if(mainBuilding >= 10 && academy >=10)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(24) );
            tBuilding->idBuilding = 24;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(24);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(24) );

            if( mainBuilding >= 10 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 10");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 10");

            if( academy >=10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(22) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(22) +" 10");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Rezydencja
    //---------------------------------------------//
    if(residence < 1)
    {
        if(mainBuilding >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(25) );
            tBuilding->idBuilding = 25;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(25);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(25) );
            tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Pałac
    //---------------------------------------------//
    if(palace < 1)
    {
        if(mainBuilding >= 5 && embassy >=1)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(26) );
            tBuilding->idBuilding = 26;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(26);
            tBuilding->setTitle("Pałac");

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( embassy >= 1 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(18) +" 1");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(18) +" 1");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Skarbiec
    //---------------------------------------------//
    if(treasury < 1)
    {
        if(mainBuilding >= 10)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(27) );
            tBuilding->idBuilding = 27;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(27);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(27) );
            tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 10");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Targ
    //---------------------------------------------//
    if(tradeOffice < 1)
    {
        if(marketplace >= 20 && stable >=10)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(28) );
            tBuilding->idBuilding = 28;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(28);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(28) );

            if( marketplace >= 20 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(17) +" 20");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(17) +" 20");

            if( stable >= 10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(20) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(20) +" 10");

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Pracownia Kamieniarza
    //---------------------------------------------//
    if(stonemason < 1)
    {
        if(mainBuilding >= 5 && (*isCapitol))
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(34) );
            tBuilding->idBuilding = 34;
            setBuildingInfo(tBuilding);
            infrastructureItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(34);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(34) );

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( *isCapitol )
                tBuilding->setReq2Green( (*activeLanguage)->Capitol );
            else
                tBuilding->setReq2Red( (*activeLanguage)->Capitol );

            tBuilding->idList = 3;
            infrastructureItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Duży Magazyn
    //---------------------------------------------//
    if(greatWarehouse < 1)
    {

    }
    //---------------------------------------------//
    //Duży Spichlerz
    //---------------------------------------------//
    if(greatWarehouse < 1)
    {

    }
    //---------------------------------------------//
    //Cud Świata
    //---------------------------------------------//
    if(greatWarehouse < 1)
    {

    }


    //-------------------------------------------------------------------------------//
    //Military
    //-------------------------------------------------------------------------------//
    foreach(ItemBuildingHorizontal *i, militaryItemList)
        delete i;
    militaryItemList.clear();
    //---------------------------------------------//
    //Warsztat Płatnerza
    //---------------------------------------------//
    if(workshopArmorer < 1)
    {
        if(mainBuilding >= 3 && academy >= 1)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(13) );
            tBuilding->idBuilding = 13;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(13);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(13) );

            if( mainBuilding >= 3 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 3");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 3");

            if( academy >= 1)
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(22) +" 1");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(22) +" 1");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Plac Turniejowy
    //---------------------------------------------//
    if(tournamentSquare < 1)
    {
        if(rallyPoint >= 15)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(14) );
            tBuilding->idBuilding = 14;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(14);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(14) );
            tBuilding->setReq1Red((*activeLanguage)->Buildings.at(16) +" 15");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Koszary
    //---------------------------------------------//
    if(barracks < 1)
    {
        if(mainBuilding >= 3 && rallyPoint >= 1)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(19) );
            tBuilding->idBuilding = 19;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(19);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(19) );

            if( mainBuilding >= 3 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 3");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 3");

            if( rallyPoint >= 1 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(16) +" 1");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(16) +" 1");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Stajnia
    //---------------------------------------------//
    if(stable < 1)
    {
        if(academy >= 5 && workshopArmorer >= 3)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(20) );
            tBuilding->idBuilding = 20;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(20);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(20) );

            if( academy >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(22) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(22) +" 5");

            if( workshopArmorer >= 3 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(13) +" 3");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(13) +" 3");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Warsztat
    //---------------------------------------------//
    if(workshop < 1)
    {
        if(academy >= 10 && mainBuilding >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(21) );
            tBuilding->idBuilding = 21;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(21);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(21) );

            if( academy >= 10 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(22) +" 10");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(22) +" 10");

            if( mainBuilding >= 5 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(15) +" 5");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Akademia
    //---------------------------------------------//
    if(academy < 1)
    {
        if(barracks >= 3 && mainBuilding >= 3)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(22) );
            tBuilding->idBuilding = 22;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(22);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(22) );

            if( barracks >= 3 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(19) +" 3");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(19) +" 3");

            if( mainBuilding >= 3 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(15) +" 3");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(15) +" 3");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }

    //---------------------------------------------//
    //Duże Koszary
    //---------------------------------------------//
    if(greatBarracks < 1)
    {
        if(barracks >= 20 && !(*isCapitol))
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(29) );
            tBuilding->idBuilding = 29;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(29);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(29) );

            if( barracks >= 20 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(19) +" 20");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(19) +" 20");

            if( !(*isCapitol) )
                tBuilding->setReq2Green( (*activeLanguage)->NotInCapitol );
            else
                tBuilding->setReq2Red( (*activeLanguage)->NotInCapitol );

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Duża Stajnia
    //---------------------------------------------//
    if(greatStable < 1)
    {
        if(stable >= 20 && !(*isCapitol))
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(30) );
            tBuilding->idBuilding = 30;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(30);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(30) );

            if( barracks >= 20 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(20) +" 20");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(20) +" 20");

            if( !(*isCapitol) )
                tBuilding->setReq2Green( (*activeLanguage)->NotInCapitol );
            else
                tBuilding->setReq2Red( (*activeLanguage)->NotInCapitol );

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Dwór Bohatera
    //---------------------------------------------//
    if(heroMansion < 1)
    {
        if(rallyPoint >= 1 && mainBuilding >= 3)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(37) );
            tBuilding->idBuilding = 37;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(37);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(37) );

            if( mainBuilding >= 3 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 3");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 3");

            if( rallyPoint >= 1 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(16) +" 1");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(16) +" 1");

            tBuilding->idList = 3;
            militaryItemList.append(tBuilding);
        }
    }
    //-------------------------------------------------------------------------------//
    //Resources
    //-------------------------------------------------------------------------------//
    foreach(ItemBuildingHorizontal *i, resourcesItemList)
        delete i;
    resourcesItemList.clear();
    //---------------------------------------------//
    //Tartak
    //---------------------------------------------//
    if(sawmill < 1)
    {
        if(forest >= 10 && mainBuilding >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(5) );
            tBuilding->idBuilding = 5;
            setBuildingInfo(tBuilding);
            resourcesItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(5);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(5) );

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( forest >= 10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(1) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(1) +" 10");

            tBuilding->idList = 3;
            resourcesItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Cegielnia
    //---------------------------------------------//
    if(brickyard < 1)
    {
        if(clayMine >= 10 && mainBuilding >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(6) );
            tBuilding->idBuilding = 6;
            setBuildingInfo(tBuilding);
            resourcesItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(6);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(6) );

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( clayMine >= 10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(2) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(2) +" 10");

            tBuilding->idList = 3;
            resourcesItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Huta Stali
    //---------------------------------------------//
    if(ironFoundry < 1)
    {
        if(ironMine >= 10 && mainBuilding >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(7) );
            tBuilding->idBuilding = 7;
            setBuildingInfo(tBuilding);
            resourcesItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(7);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(7) );

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( ironMine >= 10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(3) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(3) +" 10");

            tBuilding->idList = 3;
            resourcesItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Młyn
    //---------------------------------------------//
    if(grainMill < 1)
    {
        if(fildOfCorn >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(8) );
            tBuilding->idBuilding = 8;
            setBuildingInfo(tBuilding);
            resourcesItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(8);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(8) );
            tBuilding->setReq1Red((*activeLanguage)->Buildings.at(4) +" 5");

            tBuilding->idList = 3;
            resourcesItemList.append(tBuilding);
        }
    }
    //---------------------------------------------//
    //Piekarnia
    //---------------------------------------------//
    if(bakery < 1)
    {
        if(fildOfCorn >= 10 && mainBuilding >= 5 && grainMill >= 5)
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(9) );
            tBuilding->idBuilding = 9;
            setBuildingInfo(tBuilding);
            resourcesItemList.append(tBuilding);
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setBuildingType(9);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(9) );

            if( mainBuilding >= 5 )
                tBuilding->setReq1Green((*activeLanguage)->Buildings.at(15) +" 5");
            else
                tBuilding->setReq1Red((*activeLanguage)->Buildings.at(15) +" 5");

            if( fildOfCorn >= 10 )
                tBuilding->setReq2Green((*activeLanguage)->Buildings.at(4) +" 10");
            else
                tBuilding->setReq2Red((*activeLanguage)->Buildings.at(4) +" 10");

            if( grainMill >= 5 )
                tBuilding->setReq3Green((*activeLanguage)->Buildings.at(8) +" 5");
            else
                tBuilding->setReq3Red((*activeLanguage)->Buildings.at(8) +" 5");

            tBuilding->idList = 3;
            resourcesItemList.append(tBuilding);
        }
    }

    //-------------------------------------------------------------------------------//
    //For Nation
    //-------------------------------------------------------------------------------//
    if(*nation == Rzymianie)
    {
        //---------------------------------------------//
        //Wodopój
        //---------------------------------------------//
        if(wateringPlacenary < 1)
        {
            if(stable >= 20 && rallyPoint >= 10)
            {
                tBuilding = new ItemBuildingHorizontal(this);
                tBuilding->setTitle( (*activeLanguage)->Buildings.at(41) );
                tBuilding->idBuilding = 41;
                setBuildingInfo(tBuilding);
                infrastructureItemList.append(tBuilding);
            }else
            {
                tBuilding = new ItemBuildingHorizontal(this);
                tBuilding->setBuildingType(41);
                tBuilding->setTitle( (*activeLanguage)->Buildings.at(41) );

                if( stable >= 20 )
                    tBuilding->setReq1Green((*activeLanguage)->Buildings.at(20) +" 20");
                else
                    tBuilding->setReq1Red((*activeLanguage)->Buildings.at(20) +" 20");

                if( rallyPoint >= 10 )
                    tBuilding->setReq2Green((*activeLanguage)->Buildings.at(16) +" 10");
                else
                    tBuilding->setReq2Red((*activeLanguage)->Buildings.at(16) +" 10");

                tBuilding->idList = 3;
                infrastructureItemList.append(tBuilding);
            }
        }

    }else if(*nation == Galowie)
    {
        //---------------------------------------------//
        //Chata Trapera
        //---------------------------------------------//
        if(trapper >= 1)
        {
            if(trapperSum%20 == 0)
            {
                tBuilding = new ItemBuildingHorizontal(this);
                tBuilding->setTitle( (*activeLanguage)->Buildings.at(36) );
                tBuilding->idBuilding = 36;
                setBuildingInfo(tBuilding);
                militaryItemList.append(tBuilding);
            }
        }else
        {
            tBuilding = new ItemBuildingHorizontal(this);
            tBuilding->setTitle( (*activeLanguage)->Buildings.at(36) );
            tBuilding->idBuilding = 36;
            setBuildingInfo(tBuilding);
            militaryItemList.append(tBuilding);
        }

    }else
    {
        //---------------------------------------------//
        //Browar
        //---------------------------------------------//
        if(brewery < 1)
        {
            if(warehouse >= 20 && rallyPoint >= 10 && *isCapitol)
            {
                tBuilding = new ItemBuildingHorizontal(this);
                tBuilding->setTitle( (*activeLanguage)->Buildings.at(35) );
                tBuilding->idBuilding = 35;
                setBuildingInfo(tBuilding);
                infrastructureItemList.append(tBuilding);
            }else
            {
                tBuilding = new ItemBuildingHorizontal(this);
                tBuilding->setBuildingType(35);
                tBuilding->setTitle( (*activeLanguage)->Buildings.at(35) );

                if( warehouse >= 20 )
                    tBuilding->setReq1Green((*activeLanguage)->Buildings.at(10) +" 20");
                else
                    tBuilding->setReq1Red((*activeLanguage)->Buildings.at(10) +" 20");

                if( rallyPoint >= 10 )
                    tBuilding->setReq2Green((*activeLanguage)->Buildings.at(16) +" 10");
                else
                    tBuilding->setReq2Red((*activeLanguage)->Buildings.at(16) +" 10");

                if( !(*isCapitol) )
                    tBuilding->setReq3Green( (*activeLanguage)->Capitol );
                else
                    tBuilding->setReq3Red( (*activeLanguage)->Capitol );

                tBuilding->idList = 3;
                infrastructureItemList.append(tBuilding);
            }
        }

    }


}

void DialogBuildingToBuild::assignedItems()
{
    QList<Item*> setList1;
    QList<Item*> setList2;
    QList<Item*> setList3;

    setList1.clear();
    setList2.clear();
    setList3.clear();
    foreach(ItemBuildingHorizontal *i, infrastructureItemList)
    {
        if(i->idList == 1)
        {
            i->setParent(infrastructureList1->page);
            setList1.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));
        }else if(i->idList == 2)
        {
            i->setParent(infrastructureList1->page);
            setList2.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));

        }else
        {
            i->setParent(infrastructureList2->page);
            setList3.append( (Item*) i );
        }

    }
    foreach(Item *i, setList2)
        setList1.append(i);
    infrastructureList1->setItemList(setList1);
    infrastructureList2->setItemList(setList3);


    setList1.clear();
    setList2.clear();
    setList3.clear();
    foreach(ItemBuildingHorizontal *i, militaryItemList)
    {
        if(i->idList == 1)
        {
            i->setParent(militaryList1->page);
            setList1.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));
        }else if(i->idList == 2)
        {
            i->setParent(militaryList1->page);
            setList2.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));

        }else
        {
            i->setParent(militaryList2->page);
            setList3.append( (Item*) i );
        }

    }
    foreach(Item *i, setList2)
        setList1.append(i);
    militaryList1->setItemList(setList1);
    militaryList2->setItemList(setList3);


    setList1.clear();
    setList2.clear();
    setList3.clear();
    foreach(ItemBuildingHorizontal *i, resourcesItemList)
    {
        if(i->idList == 1)
        {
            i->setParent(resourcesList1->page);
            setList1.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));
        }else if(i->idList == 2)
        {
            i->setParent(resourcesList1->page);
            setList2.append( (Item*) i );

        }else
        {
            i->setParent(resourcesList2->page);
            setList3.append( (Item*) i );
            connect(i, SIGNAL(clicked(ItemBuildingHorizontal*)), this, SLOT(selected(ItemBuildingHorizontal*)));
        }

    }
    foreach(Item *i, setList2)
        setList1.append(i);
    resourcesList1->setItemList(setList1);
    resourcesList2->setItemList(setList3);
}

void DialogBuildingToBuild::createList()
{
    idBuilding = -1;
    findeRequestments();
    createItems();
    assignedItems();
}

void DialogBuildingToBuild::setBuildingInfo(ItemBuildingHorizontal *fBuilding)
{
    fBuilding->setBuildingType(fBuilding->idBuilding);
    int timeToUpgrade = 0;
    int tTime = time->secondsTo(Time::currentTime());

    int woodToBuild = travianWiki->buildingTable[fBuilding->idBuilding]->at(0).wood;
    int clayToBuild = travianWiki->buildingTable[fBuilding->idBuilding]->at(0).clay;
    int ironToBuild = travianWiki->buildingTable[fBuilding->idBuilding]->at(0).iron;
    int cornToBuild = travianWiki->buildingTable[fBuilding->idBuilding]->at(0).corn;
    int corn2ToBuild = travianWiki->buildingTable[fBuilding->idBuilding]->at(0).corn2;
    Time buildTime = travianWiki->buildingTimeTable[fBuilding->idBuilding]->at(0).mainBuilding[mainBuilding];

    //Woood
    int tCurrentWood = tTime * (*peerSecWood) + (*currentWood);
    if( tCurrentWood < woodToBuild )
    {
        int tTimeToUpgrade = (double) (woodToBuild - tCurrentWood) / (*peerSecWood);

        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;

        fBuilding->setWoodRed(woodToBuild);
    }else
        fBuilding->setWoodGreen(woodToBuild);

    //Clay
    int tCurrentClay = tTime * (*peerSecClay) + (*currentClay);
    if( tCurrentClay < clayToBuild )
    {

        int tTimeToUpgrade = (double) (clayToBuild - tCurrentClay) / (*peerSecClay);

        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;

        fBuilding->setClayRed(clayToBuild);
    }else
        fBuilding->setClayGreen(clayToBuild);

    //Iron
    int tCurrentIron = tTime * (*peerSecIron) + (*currentIron);
    if( tCurrentIron < ironToBuild )
    {

        int tTimeToUpgrade = (double) (ironToBuild - tCurrentIron) / (*peerSecIron);

        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;

        fBuilding->setIronRed(ironToBuild);
    }else
        fBuilding->setIronGreen(ironToBuild);

    //Corn
    int tCurrentCorn = tTime * (*peerSecCorn) + (*currentCorn);
    if( tCurrentCorn < cornToBuild )
    {

        int tTimeToUpgrade = (double) (cornToBuild - tCurrentCorn) / (*peerSecCorn);

        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;

        fBuilding->setCornRed(cornToBuild);
    }else
        fBuilding->setCornGreen(cornToBuild);

    //Corn2
    if( (*currentCorn2) < corn2ToBuild )
        fBuilding->setCorn2Red(corn2ToBuild);
    else
        fBuilding->setCorn2Green(corn2ToBuild);

    //Clock
    fBuilding->setTimeUpgradeLong(buildTime.toString());

     if(timeToUpgrade == 0)
    {
        fBuilding->setLvlGreen(1);
        fBuilding->setTimeToAvaible("");
        fBuilding->idList = 1;
    }
    else
    {
        fBuilding->setLvlRed(1);
        fBuilding->idList = 2;

        int tHours = timeToUpgrade / 3600;
        int tMinutes = (timeToUpgrade % 3600) /60;
        Time tTime(tHours, tMinutes, timeToUpgrade - (tHours*3600 + tMinutes*60) );
        fBuilding->setTimeToAvaible(tTime.toString());

    }
}
