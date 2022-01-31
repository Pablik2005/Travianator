#include "listitemconstruction.h"

ListItemConstruction::ListItemConstruction(QWidget *parent)
{
    this->setParent(parent);
    page->setGeometry(0,0,100,279);

    ItemConstruction *tItem1 = new ItemConstruction(page);
    tItem1->setGeometry(0,0,100,93);
    itemList.append((Item*)tItem1);

    ItemConstruction *tItem2 = new ItemConstruction(page);
    tItem2->setGeometry(0,94,100,93);
    itemList.append((Item*)tItem2);

    ItemConstruction *tItem3 = new ItemConstruction(page);
    tItem3->setGeometry(0,186,100,93);
    itemList.append((Item*)tItem3);

    itemSize = QSize(100,93);
    count = 0;
}

void ListItemConstruction::clear()
{
    page->setGeometry(0,0,100,0);
    count = 0;
}

void ListItemConstruction::refresh()
{
    for(int i=0; i<count; i++)
    {
        int secCout = time.secondsTo(Time::currentTime());
        ((ItemConstruction*)itemList.at(i))->setTime( ((ItemConstruction*)itemList.at(i))->building.timeToUpgradeEnd.addSeconds(-secCout).toString());
    }
}

void ListItemConstruction::addItem(Building fBuilding)
{
    if(count == 0)
    {
        page->setGeometry(0,0,itemSize.width(),itemSize.height());
        setItemConstruction(0, fBuilding);
        count = 1;
    }else if(count == 1)
    {
        page->setGeometry(0,0,itemSize.width(),2*itemSize.height());

        if(((ItemConstruction*)itemList.at(0))->building.timeToUpgradeEnd < fBuilding.timeToUpgradeEnd)
        {
            setItemConstruction(1, fBuilding);
            count = 2;

        }else
        {
            setItemConstruction(1, ((ItemConstruction*)itemList.at(0))->building);
            setItemConstruction(0, fBuilding);
            count = 2;
        }
    }else
    {
        page->setGeometry(0,0,itemSize.width(),3*itemSize.height());

        if(fBuilding.timeToUpgradeEnd > ((ItemConstruction*)itemList.at(1))->building.timeToUpgradeEnd)
        {
            setItemConstruction(2, fBuilding);
        }else if(fBuilding.timeToUpgradeEnd > ((ItemConstruction*)itemList.at(0))->building.timeToUpgradeEnd)
        {
            setItemConstruction(2, ((ItemConstruction*)itemList.at(1))->building);
            setItemConstruction(1, fBuilding);

        }else
        {
            setItemConstruction(2, ((ItemConstruction*)itemList.at(1))->building);
            setItemConstruction(1, ((ItemConstruction*)itemList.at(0))->building);
            setItemConstruction(0, fBuilding);
        }

        count = 3;
    }
}

void ListItemConstruction::setItemConstruction(int index, Building fBuilding)
{
    if(index >=0 && index <3)
    {
        ((ItemConstruction*)itemList.at(index))->building = fBuilding;
        ((ItemConstruction*)itemList.at(index))->setType(fBuilding.imgPath);
        ((ItemConstruction*)itemList.at(index))->setLvl(fBuilding.lvl);
        ((ItemConstruction*)itemList.at(index))->setTitle( (*activeLanguage)->Buildings.at( fBuilding.idBuilding ) );
    }
}
