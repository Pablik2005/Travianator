#include "list.h"

List::List()
{
    page = new QWidget(this);
    this->setWidget(page);
    page->setGeometry(0,0,1,1);
    isMousePressed = false;
}

List::List(QWidget *parent, bool fHorizontal) :
    QScrollArea(parent)
{
    isHorizontal=fHorizontal;
    if(isHorizontal)
    {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }else
    {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }

    page = new QWidget(this);
    this->setWidget(page);
    page->setGeometry(0,0,1,1);
    isMousePressed = false;
}

void List::setItemSize(int w, int h)
{
    itemSize.setWidth(w);
    itemSize.setHeight(h);
}

void List::setItemList(QList<Item *> fList)
{
    itemList = fList;
    foreach(Item *i , itemList)
    {
        connect(i, SIGNAL(mouseMoveSignal(QMouseEvent*)), this, SLOT(mouseMoveSlot(QMouseEvent*)));
        connect(i, SIGNAL(mousePressSignal(QMouseEvent*)), this, SLOT(mousePressSlot(QMouseEvent*)));
        connect(i, SIGNAL(mouseReleaseSignal(QMouseEvent*)), this, SLOT(mouseReleaseSlot(QMouseEvent*)));
    }

    refresh();
}

void List::addItem(Item *fItem)
{
    itemList.append(fItem);
}

void List::refresh()
{
    page->setGeometry(0,0,0,0);

    int index=0;
    for(int i=0; i<itemList.count(); i++)
    {
        if(!itemList.at(i)->hidden)
        {
            itemList.at(i)->show();
            if(isHorizontal)
            {
                itemList.at(i)->setGeometry(itemSize.width()*index, 0,itemSize.width(),itemSize.height());
                page->setGeometry(0,0,itemSize.width()*(index+1), itemSize.height());

            }
            else
            {
                itemList.at(i)->setGeometry(0, itemSize.height()*index,itemSize.width(),itemSize.height());
                page->setGeometry(0,0,itemSize.width(), itemSize.height()*(index+1));
            }
            index++;
        }else
        {
            itemList.at(i)->setHidden(true);
        }

    }
}

void List::clear()
{
    foreach(Item *i, itemList)
        delete i;

    itemList.clear();
}

void List::mouseMoveSlot(QMouseEvent *e)
{
    emit mouseMoveEvent(e);
}

void List::mousePressSlot(QMouseEvent *e)
{
    emit mousePressEvent(e);
}

void List::mouseReleaseSlot(QMouseEvent *e)
{
    emit mouseReleaseEvent(e);
}


void List::mouseMoveEvent(QMouseEvent *e)
{
    if(isMousePressed)
    {
        //QMessageBox::information(0,"","");


        if(isHorizontal)
        {
            int tInt = oldMpusePos.x() - e->globalPos().x();
            oldMpusePos = e->globalPos();
            if(tInt > 0)
                this->horizontalScrollBar()->setSliderPosition( this->horizontalScrollBar()->sliderPosition() +(tInt * (page->width() / this->width())) );
            else
                this->horizontalScrollBar()->setSliderPosition( this->horizontalScrollBar()->sliderPosition() +(tInt * (page->width() / this->width())) );


        }else
        {
            int tInt = oldMpusePos.y() - e->globalPos().y();
            oldMpusePos = e->globalPos();

            if(tInt > 0)
                this->verticalScrollBar()->setSliderPosition( this->verticalScrollBar()->sliderPosition() +(tInt * (page->height() / this->height())) );
            else
                this->verticalScrollBar()->setSliderPosition( this->verticalScrollBar()->sliderPosition() +(tInt * (page->height() / this->height())) );
        }
    }

}

void List::mousePressEvent(QMouseEvent *e)
{
    isMousePressed =true;
    oldMpusePos = e->globalPos();
}

void List::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed = false;
}




