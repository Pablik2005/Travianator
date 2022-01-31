#include "item.h"

Item::Item(QWidget *parent) :
    QWidget(parent)
{
    hidden = false;
}


void Item::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseMoveSignal(e);
}

void Item::mousePressEvent(QMouseEvent *e)
{
    emit mousePressSignal(e);
}

void Item::mouseReleaseEvent(QMouseEvent *e)
{
    emit mouseReleaseSignal(e);
}
