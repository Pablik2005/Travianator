#include "listitembuilding.h"

ListItemBuilding::ListItemBuilding(QWidget *parent)
{
    this->setParent(parent);

    isHorizontal=false;
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    page->setGeometry(0,0,130,6800);

    setItemSize(130,185);
    for(int i=1; i<41; i++)
    {
        ItemBuilding *tItem = new ItemBuilding(page);
        connect(tItem, SIGNAL(mouseMoveSignal(QMouseEvent*)), this, SLOT(mouseMoveSlot(QMouseEvent*)));
        connect(tItem, SIGNAL(mousePressSignal(QMouseEvent*)), this, SLOT(mousePressSlot(QMouseEvent*)));
        connect(tItem, SIGNAL(mouseReleaseSignal(QMouseEvent*)), this, SLOT(mouseReleaseSlot(QMouseEvent*)));
        itemList.append( (Item*)tItem );
    }


    showResource = true;
    showInfrastructure = false;
    showCanUpgrade = true;
    showCantUpgrade = true;

}

void ListItemBuilding::refresh()
{
    page->setGeometry(0,0,0,0);

    //Filter
    foreach(Item *i, itemList)
    {
        ItemBuilding* b = (ItemBuilding*) i;

        b->setHidden(false);
        b->hidden = false;

        b->building = static_cast<Building*>(b->building);
        if(b->building->lvl == b->building->maxLvl)
        {
            b->setHidden(true);
            b->hidden = true;
        }

        if(b->building->idBuilding == 0)
        {
            b->setHidden(true);
            b->hidden = true;
        }

        if(!showResource)
            if(b->building->isResource)
            {
                b->setHidden(true);
                b->hidden = true;
            }

        if(!showInfrastructure)
            if(!b->building->isResource)
            {
                b->setHidden(true);
                b->hidden = true;
            }

        if(!showCanUpgrade)
            if(b->building->canUpgrade)
            {
                b->setHidden(true);
                b->hidden = true;
            }

        if(!showCantUpgrade)
            if(!b->building->canUpgrade)
            {
                b->setHidden(true);
                b->hidden = true;
            }


    }

    int index=0;
    for(int i=0; i<40; i++)
    {
        if(!itemList.at(i)->hidden)
        {
            itemList.at(i)->setGeometry(0, itemSize.height()*index,itemSize.width(),itemSize.height());
            page->setGeometry(0,0,itemSize.width(), itemSize.height()*(index+1));
            index++;
        }
    }
}

void ListItemBuilding::changedTo(bool fResource)
{
    if(fResource)
    {
        showInfrastructure = false;
        showResource = true;
        refresh();

    }else
    {
        showInfrastructure = true;
        showResource = false;
        refresh();
    }
}

