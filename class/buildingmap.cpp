#include "buildingmap.h"

BuildingMap::BuildingMap(QWidget *parent, NationType *fNation, QList<BuildingSocket*> *fResource) :
    QWidget(parent)
{
    isResource = true;
    nation = fNation;
    resource = fResource;
    pixmapBuilding = QPixmap::fromImage(QImage(":/IMG/Building/Rzymianie.png"));
    pixmapResources = QPixmap::fromImage(QImage(":/IMG/Resource/4-4-4-6.png"));
    backGround = new QLabel(this);
    backGround->setGeometry(0,0,336,298);
    this->setMinimumSize(336, 298);
    this->setMaximumSize(336, 298);


    QRect tRect = backGround->geometry();
    double tWidth = (double)tRect.width() /100;
    double tHeight = (double)tRect.height() /100;

    int tWidth1 = 17*tWidth;
    int tHeight1 = 20*tHeight;

    buttonBuildingChange1 = new Button(backGround);
        buttonBuildingChange1->setGeometry(0,0,tWidth1, tHeight1);
        buttonBuildingChange1->setHidden(true);
        connect(buttonBuildingChange1, SIGNAL(clicked()), this, SLOT(changeToResource()));
    buttonBuildingChange2 = new Button(backGround);
        buttonBuildingChange2->setGeometry(backGround->geometry().width()-tWidth1,0,tWidth1,tHeight1);
        buttonBuildingChange2->setHidden(true);
        connect(buttonBuildingChange2, SIGNAL(clicked()), this, SLOT(changeToResource()));
    buttonBuildingChange3 = new Button(backGround);
        buttonBuildingChange3->setGeometry(backGround->geometry().width() -tWidth1, backGround->geometry().height() -tHeight1,tWidth1,tHeight1);
        buttonBuildingChange3->setHidden(true);
        connect(buttonBuildingChange3, SIGNAL(clicked()), this, SLOT(changeToResource()));
    buttonBuildingChange4 = new Button(backGround);
        buttonBuildingChange4->setGeometry(0,backGround->geometry().height() -tHeight1,tWidth1,tHeight1);
        buttonBuildingChange4->setHidden(true);
        connect(buttonBuildingChange4, SIGNAL(clicked()), this, SLOT(changeToResource()));

    int tX = 34*tWidth;
    int tY = 40*tHeight;
    tWidth1 = 61*tWidth - tX;
    tHeight1 = 52*tHeight - tY;

    buttonResourceChange = new Button(backGround);
        buttonResourceChange->setGeometry(tX, tY,tWidth1,tHeight1);
        connect(buttonResourceChange, SIGNAL(clicked()), this, SLOT(changeToBuilding()));

    backGround->setGeometry(0,0,336,298);
    backGround->setPixmap(pixmapResources);
    backGround->setScaledContents(true);
    createResourceObject();
    createInfrastructureObject();

}

void BuildingMap::setType(bool fIsResource)
{
    if(isResource != fIsResource)
    {

        isResource = fIsResource;
        if(isResource)
        {
            emit changedTo(true);
            backGround->setPixmap(pixmapResources);
            foreach(BuildingMapItem *i,resourceList)
            {
                i->circle->setHidden(false);
            }
            buttonResourceChange->setHidden(false);


            for(int i=0; i<21; i++)
            {
                infrastructureList.at(i)->circle->setHidden(true);
                infrastructureList.at(i)->backGround->setHidden(true);
            }
            infrastructureList.at(21)->circle->setHidden(true);
            buttonBuildingChange1->setHidden(true);
            buttonBuildingChange2->setHidden(true);
            buttonBuildingChange3->setHidden(true);
            buttonBuildingChange4->setHidden(true);
        }
        else
        {
            emit changedTo(false);
            backGround->setPixmap(pixmapBuilding);
            foreach(BuildingMapItem *i,resourceList)
                i->circle->setHidden(true);
            buttonResourceChange->setHidden(true);


            for(int i=0; i<21; i++)
            {
                infrastructureList.at(i)->circle->setHidden(false);
                infrastructureList.at(i)->backGround->setHidden(false);
            }
            infrastructureList.at(21)->circle->setHidden(false);
            buttonBuildingChange1->setHidden(false);
            buttonBuildingChange2->setHidden(false);
            buttonBuildingChange3->setHidden(false);
            buttonBuildingChange4->setHidden(false);

        }
    }
}

void BuildingMap::createResourceObject()
{
    BuildingMapItem *tLabel1 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel1->circle->setGeometry(100,23,27,27);
    resourceList.append(tLabel1);

    BuildingMapItem *tLabel2 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel2->circle->setGeometry(171,23,27,27);
    resourceList.append(tLabel2);

    BuildingMapItem *tLabel3 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel3->circle->setGeometry(238,39,27,27);
    resourceList.append(tLabel3);

    BuildingMapItem *tLabel4 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel4->circle->setGeometry(38,59,27,27);
    resourceList.append(tLabel4);

    BuildingMapItem *tLabel5 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel5->circle->setGeometry(141,70,27,27);
    resourceList.append(tLabel5);

    BuildingMapItem *tLabel6 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel6->circle->setGeometry(214,92,27,27);
    resourceList.append(tLabel6);

    BuildingMapItem *tLabel7 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel7->circle->setGeometry(279,84,27,27);
    resourceList.append(tLabel7);

    BuildingMapItem *tLabel8 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel8->circle->setGeometry(22,119,27,27);
    resourceList.append(tLabel8);

    BuildingMapItem *tLabel9 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel9->circle->setGeometry(79,111,27,27);
    resourceList.append(tLabel9);

    BuildingMapItem *tLabel10 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel10->circle->setGeometry(225,146,27,27);
    resourceList.append(tLabel10);

    BuildingMapItem *tLabel11 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel11->circle->setGeometry(287,149,27,27);
    resourceList.append(tLabel11);

    BuildingMapItem *tLabel12 = new BuildingMapItem(backGround, QSize(27,27), false);;
    tLabel12->circle->setGeometry(33,179,27,27);
    resourceList.append(tLabel12);

    BuildingMapItem *tLabel13 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel13->circle->setGeometry(90,171,27,27);
    resourceList.append(tLabel13);

    BuildingMapItem *tLabel14 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel14->circle->setGeometry(165,193,27,27);
    resourceList.append(tLabel14);

    BuildingMapItem *tLabel15 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel15->circle->setGeometry(254,211,27,27);
    resourceList.append(tLabel15);

    BuildingMapItem *tLabel16 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel16->circle->setGeometry(84,231,27,27);
    resourceList.append(tLabel16);

    BuildingMapItem *tLabel17 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel17->circle->setGeometry(144,244,27,27);
    resourceList.append(tLabel17);

    BuildingMapItem *tLabel18 = new BuildingMapItem(backGround, QSize(27,27), false);
    tLabel18->circle->setGeometry(199,249,27,27);
    resourceList.append(tLabel18);

}

void BuildingMap::createInfrastructureObject()
{
    BuildingMapItem *tLabel1 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel1->backGround->setGeometry(43,48,64,64);
    infrastructureList.append(tLabel1);

    BuildingMapItem *tLabel2 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel2->backGround->setGeometry(94,25,64,64);
    infrastructureList.append(tLabel2);

    BuildingMapItem *tLabel3 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel3->backGround->setGeometry(140,17,64,64);
    infrastructureList.append(tLabel3);

    BuildingMapItem *tLabel4 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel4->backGround->setGeometry(190,31,64,64);
    infrastructureList.append(tLabel4);

    BuildingMapItem *tLabel5 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel5->backGround->setGeometry(230,56,64,64);
    infrastructureList.append(tLabel5);

    BuildingMapItem *tLabel6 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel6->backGround->setGeometry(24,75,64,64);
    infrastructureList.append(tLabel6);

    BuildingMapItem *tLabel7 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel7->backGround->setGeometry(260,82,64,64);
    infrastructureList.append(tLabel7);

    BuildingMapItem *tLabel8 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel8->backGround->setGeometry(135,55,64,64);
    infrastructureList.append(tLabel8);

    BuildingMapItem *tLabel9 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel9->backGround->setGeometry(38,148,64,64);
    infrastructureList.append(tLabel9);

    BuildingMapItem *tLabel10 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel10->backGround->setGeometry(18,108,64,64);
    infrastructureList.append(tLabel10);

    BuildingMapItem *tLabel11 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel11->backGround->setGeometry(239,110,64,64);
    infrastructureList.append(tLabel11);

    BuildingMapItem *tLabel12 = new BuildingMapItem(backGround, QSize(64,64), true);;
    tLabel12->backGround->setGeometry(83,117,64,64);
    infrastructureList.append(tLabel12);

    BuildingMapItem *tLabel13 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel13->backGround->setGeometry(84,78,64,64);
    infrastructureList.append(tLabel13);

    BuildingMapItem *tLabel14 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel14->backGround->setGeometry(122,142,64,64);
    infrastructureList.append(tLabel14);

    BuildingMapItem *tLabel15 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel15->backGround->setGeometry(255,147,64,64);
    infrastructureList.append(tLabel15);

    BuildingMapItem *tLabel16 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel16->backGround->setGeometry(82,180,64,64);
    infrastructureList.append(tLabel16);

    BuildingMapItem *tLabel17 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel17->backGround->setGeometry(158,175,64,64);
    infrastructureList.append(tLabel17);

    BuildingMapItem *tLabel18 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel18->backGround->setGeometry(216,155,64,64);
    infrastructureList.append(tLabel18);

    BuildingMapItem *tLabel19 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel19->backGround->setGeometry(129,198,64,64);
    infrastructureList.append(tLabel19);

    BuildingMapItem *tLabel20 = new BuildingMapItem(backGround, QSize(64,64), true);
    tLabel20->backGround->setGeometry(195,190,64,64);
    infrastructureList.append(tLabel20);

    BuildingMapItem *tLabel21 = new BuildingMapItem(backGround, QSize(64,85), true);
    tLabel21->backGround->setGeometry(190,110,64,85);
    infrastructureList.append(tLabel21);

    for(int i=0; i<21; i++)
    {
        QRect tRect = infrastructureList.at(i)->backGround->geometry();
        int tW = (tRect.width() -17) /2;
        int tH = (tRect.height() - 17) /2;
        infrastructureList.at(i)->circle->setGeometry(tRect.x() + tW, tRect.y() + tH, 17, 17 );

        infrastructureList.at(i)->backGround->setHidden(true);
        infrastructureList.at(i)->circle->setHidden(true);
        infrastructureList.at(i)->circle->raise();
    }

    BuildingMapItem *tLabel22 = new BuildingMapItem(backGround, QSize(17,17), false);
    tLabel22->circle->setGeometry(170,260,17,17);
    tLabel22->circle->setHidden(true);
    tLabel22->circle->raise();
    infrastructureList.append(tLabel22);
}

void BuildingMap::setBackGround()
{
    int tWood=0;
    int tClay=0;
    int tIron=0;
    int tCorn=0;

    foreach(BuildingSocket *i, *resource)
    {
        if(i->building.idBuilding== 1)
            tWood++;
        else if(i->building.idBuilding == 2)
            tClay++;
        else if(i->building.idBuilding == 3)
            tIron++;
        else if(i->building.idBuilding == 4)
            tCorn++;

    }
    pixmapResources = QPixmap::fromImage(QImage(QString(":/IMG/Resource/%1-%2-%3-%4.png").arg(tWood).arg(tClay).arg(tIron).arg(tCorn)));


    int tValue = *nation;
    if(tValue == 0)
    {
        pixmapBuilding = QPixmap::fromImage(QImage(":/IMG/Building/Rzymianie.png"));
        backGround->setPixmap(pixmapBuilding);
    }
    else if(tValue == 1)
    {
        pixmapBuilding = QPixmap::fromImage(QImage(":/IMG/Building/Germanie.png"));
        backGround->setPixmap(pixmapBuilding);
    }
    else
    {
        pixmapBuilding = QPixmap::fromImage(QImage(":/IMG/Building/Galowie.png"));
        backGround->setPixmap(pixmapBuilding);
    }


    if(isResource)
        backGround->setPixmap(pixmapResources);
    else
        backGround->setPixmap(pixmapBuilding);

}

void BuildingMap::changeToBuilding()
{
    setType(false);
}

void BuildingMap::changeToResource()
{
    setType(true);
}
