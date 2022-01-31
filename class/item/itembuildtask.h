#ifndef ITEMBUILDTASK_H
#define ITEMBUILDTASK_H

#include "item.h"
#include "../task.h"

namespace Ui {
class ItemBuildTask;
}

class ItemBuildTask : public Item
{
    Q_OBJECT

protected:
    QFont font;
    QFont fontTime;
    int click;


public:
    ItemBuildTask(QWidget *parent);
    ~ItemBuildTask();

    Task task;

    void setTitle(QString fTitme);
    void setBuildingType(QString fImgPath);


    void setAvaibleTime(QString fAvaibleTime);
    void setKeyTime(QString fKeyTime);
    void setKeyHidden();
    void setUpgradeTime(QString fUpgradeTime);

    void setLvlGreen(int fLvl);
    void setLvlRed(int fLvl);
    void setLvlBrown(int fLvl);

    void setCorn2Green(int fCorn2);
    void setCorn2Red(int fCorn2);

    void setWoodGreen(int fWood);
    void setWoodRed(int fWood);
    void setWoodTime(QString fTime);

    void setClayGreen(int fClay);
    void setClayRed(int fClay);
    void setClayTime(QString fTime);

    void setIronGreen(int fIron);
    void setIronRed(int fIron);
    void setIronTime(QString fTime);

    void setCornGreen(int fCorn);
    void setCornRed(int fCorn);
    void setCornTime(QString fTime);

    void setBonus(QString fBonus);
    void setBonusPast(QString fBonus);

    bool static qSort(ItemBuildTask *fItem1, ItemBuildTask *fItem2);


private:
    Ui::ItemBuildTask *ui;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked(ItemBuildTask *Item);

public slots:
    void clearClick();

};

#endif // ITEMBUILDTASK_H


