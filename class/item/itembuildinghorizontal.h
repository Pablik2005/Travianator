#ifndef ITEMBUILDINGHORIZONTAL_H
#define ITEMBUILDINGHORIZONTAL_H

#include "item.h"
#include <QMessageBox>
#include <QTimer>

namespace Ui {
class ItemBuildingHorizontal;
}

class ItemBuildingHorizontal : public Item
{
    Q_OBJECT

public:
    explicit ItemBuildingHorizontal(QWidget *parent);
    ~ItemBuildingHorizontal();

    int fontSize;

    //-----BuildingListToBuild-----//
    int idBuilding;
    int idList;
    QFont font;
    int click;

    void setBuildingType(int fIdBuilding);
    void setTitle(QString fTitem);

    void setTimeToAvaibleHidde(bool fBool);
    void setTimeToAvaible(QString fTime);
    void setTimeUpgradeLong(QString fTime);

    void setLvlHidde(bool fBool);
    void setLvlGreen(int fLvl);
    void setLvlRed(int fLvl);
    void setLvlBrown(int fLvl);

    void setWoodGreen(int fWood);
    void setWoodRed(int fWood);

    void setClayGreen(int fClay);
    void setClayRed(int fClay);

    void setIronGreen(int fIron);
    void setIronRed(int fIron);

    void setCornGreen(int fCorn);
    void setCornRed(int fCorn);

    void setCorn2Green(int fCorn2);
    void setCorn2Red(int fCorn2);

    void setReq1Red(QString fReq);
    void setReq1Green(QString fReq);

    void setReq2Red(QString fReq);
    void setReq2Green(QString fReq);

    void setReq3Red(QString fReq);
    void setReq3Green(QString fReq);

    void setReq4Red(QString fReq);
    void setReq4Green(QString fReq);

    void setHiddenAll();

private:
    Ui::ItemBuildingHorizontal *ui;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked(ItemBuildingHorizontal *tItem);

public slots:
    void clearClick();
};

#endif // ITEMBUILDINGHORIZONTAL_H
