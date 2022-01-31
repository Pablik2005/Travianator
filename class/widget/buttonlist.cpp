#include "buttonlist.h"

ButtonList::ButtonList(QWidget *parent) :
    QDialog(parent)
{
    mIndex = -1;
    mCount = 0;
    execCount = 0;

    //this->setWindowFlags( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowTitleHint);
    //this->setWindowFlags( Qt::CustomizeWindowHint );
    //this->setWindowFlags( Qt::CustomizeWindowHint|Qt::WindowTitleHint );

                           //& ~Qt::WindowCloseButtonHint) );
    //setWindowFlags(Qt::FramelessWindowHint);
   //setWindowFlags(Qt::WindowTitleHint);
}

void ButtonList::setTitle(QString fTitle)
{
}

void ButtonList::addItem(QString fItem)
{
    Button *tButton = new Button(this);
    tButton->setText(fItem);

    tButton->setGeometry(0,mCount *25 ,125,25);

    connect(tButton, SIGNAL(clicked(Button*)), this, SLOT(closeSlot(Button*)));

    this->setMaximumSize(125, (mCount+1)*25);
    this->setMinimumSize(125, (mCount+1)*25);

    mCount++;
}

void ButtonList::clear()
{
    foreach(Button *i, buttonList)
        delete i;
    buttonList.clear();
    mCount=0;
}


void ButtonList::exec()
{
    execCount++;
    if(execCount == 1)
    {
        QTimer::singleShot(1, this, SLOT(close()));
        this->setHidden(true);
        QDialog::exec();
    }else
    {
        this->setHidden(false);
        QDialog::exec();
    }
}


void ButtonList::closeSlot(Button *fButton)
{
    for(int i=0; i<buttonList.count(); i++)
    {
        if(fButton == buttonList.at(i))
            mIndex = i;
    }
    close();

}
