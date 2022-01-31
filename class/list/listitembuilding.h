#ifndef LISTITEMBUILDING_H
#define LISTITEMBUILDING_H

#include "list.h"
#include "../item/itembuilding.h"


class ListItemBuilding : public List
{
     Q_OBJECT
public:
    ListItemBuilding(QWidget *parent);


    bool showResource;
    bool showInfrastructure;
    bool showCanUpgrade;
    bool showCantUpgrade;


    void refresh();
    void changedTo(bool fResource);

};

#endif // LISTITEMBUILDING_H
