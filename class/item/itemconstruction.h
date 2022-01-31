#ifndef ITEMCONSTRUCTION_H
#define ITEMCONSTRUCTION_H

#include "item.h"
#include "../building.h"

namespace Ui {
class ItemConstruction;
}

class ItemConstruction : public Item
{
    Q_OBJECT

public:
    explicit ItemConstruction(QWidget *parent);
    ~ItemConstruction();

    Building building;
    QFont font;
    QMovie *movie;
    int click;

    void setLvl(int fValue);
    void setTime(QString fTime);
    void setType(QString fImgPath);
    void setTitle(QString fTitle);

private:
    Ui::ItemConstruction *ui;
    void mousePressEvent(QMouseEvent *e);

signals:
    void clicked(QString fAbortValueD, QMovie *fMovie);

public slots:
    void clearClick();
};

#endif // ITEMCONSTRUCTION_H
