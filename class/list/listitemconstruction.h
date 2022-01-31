#ifndef LISTITEMCONSTRUCTION_H
#define LISTITEMCONSTRUCTION_H

#include "list.h"
#include "../language.h"
#include "../item/itemconstruction.h"

class ListItemConstruction: public List
{
    Q_OBJECT
public:
    ListItemConstruction(QWidget *parent);

    Time time;
    int count;
    Language **activeLanguage;

    void clear();
    void refresh();
    void addItem(Building fBuilding);
    void setItemConstruction(int index, Building fBuilding);

};

#endif // LISTITEMCONSTRUCTION_H




