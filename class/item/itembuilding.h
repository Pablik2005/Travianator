#ifndef ITEMBUILDING_H
#define ITEMBUILDING_H


#include <QMessageBox>
#include <QtCore>

#include "item.h"
#include "../building.h"
#include "../Enums.h"
#include "../buildingmapitem.h"
#include "../task.h"

namespace Ui {
class ItemBuilding;
}

class ItemBuilding : public Item
{
    Q_OBJECT

protected:
    QFont font;
    QFont fontTime;
    int click;


public:
    ItemBuilding(QWidget *parent);
    ~ItemBuilding();

    QLabel *labelMovie;
    QMovie *movie;
    Building *building;

    void setTitle(QString fTitme);
    void setBuildingType(QString fImgPath);
    void setUpgradeTime(QString fUpgradeTime);

    void setLvlGreen(int fLvl);
    void setLvlRed(int fLvl);
    void setLvlBrown(int fLvl);
    void setLvlBlue(int fLvl);

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



private:
    Ui::ItemBuilding *ui;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked();

public slots:
    void clearClick();

};

#endif // ITEMBUILDING_H
