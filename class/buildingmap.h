#ifndef BUILDINGMAP_H
#define BUILDINGMAP_H

#include <QWidget>
#include "buildingmapitem.h"
#include "widget/button.h"
#include "Enums.h"
#include "buildingsocket.h"

class BuildingMap : public QWidget
{
    Q_OBJECT
public:
    explicit BuildingMap(QWidget *parent, NationType *fNation, QList<BuildingSocket*> *fResource);

    NationType *nation;
    QList<BuildingSocket*> *resource;

    QPixmap pixmapResources;
    QPixmap pixmapBuilding;

    Button *buttonBuildingChange1;
    Button *buttonBuildingChange2;
    Button *buttonBuildingChange3;
    Button *buttonBuildingChange4;
    Button *buttonResourceChange;

    bool isResource;
    QLabel *backGround;
    QList<BuildingMapItem*> resourceList;
    QList<BuildingMapItem*> infrastructureList;


    void setType(bool fIsResource);
    void createResourceObject();
    void createInfrastructureObject();
    void setBackGround();
    
signals:
    void changedTo(bool fResource);
    
public slots:
    void changeToBuilding();
    void changeToResource();
};

#endif // BUILDINGMAP_H
