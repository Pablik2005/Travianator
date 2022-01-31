#ifndef LIST_H
#define LIST_H

#include <QScrollArea>
#include <QScrollBar>
#include <QList>
#include <QMessageBox>
#include <QMouseEvent>

#include "../item/item.h"

class List : public QScrollArea
{
    Q_OBJECT
public:
    List();
    List(QWidget *parent, bool fHorizontal);

    QWidget *page;
    bool isHorizontal;

    bool isMousePressed;
    QPoint oldMpusePos;

    QSize   itemSize;
    QList<Item*> itemList;

    void setItemSize(int w, int  h);
    void addItem(Item* fItem);
    void setItemList(QList<Item*> fList);

    void refresh();
    void clear();

signals:

public slots:
    void mouseMoveSlot(QMouseEvent *e);
    void mousePressSlot(QMouseEvent *e);
    void mouseReleaseSlot(QMouseEvent *e);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // LIST_H
