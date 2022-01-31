#ifndef BUILDINGMAPITEM_H
#define BUILDINGMAPITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QMovie>

#include "class/widget/button.h"

class BuildingMapItem : public QObject
{
    Q_OBJECT
public:
    explicit BuildingMapItem(QObject *parent, QSize fSize, bool fIsBuilding);

    bool isBuilding;

    Button *button;
    QLabel *value;
    QLabel *backGround;
    QLabel *circle;
    QLabel *labelMovie;
    QMovie *movie;

    QFont font;


    void setBrown(int fValue);
    void setGreen(int fValue);
    void setGold(int fValue);
    void setRed(int fValue);
    void setBlue(int fValue);

    void setPlus();

signals:
    void clicked();
public slots:
    void buttonClicked();
};

#endif // BUILDINGMAPITEM_H
