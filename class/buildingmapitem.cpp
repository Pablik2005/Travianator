#include "buildingmapitem.h"

BuildingMapItem::BuildingMapItem(QObject *parent, QSize fSize, bool fIsBuilding) :
    QObject(parent)
{
    isBuilding = fIsBuilding;

    circle = new QLabel((QWidget*)this->parent());
    labelMovie = new QLabel(circle);
    movie = new QMovie(labelMovie);
    movie->setFileName(":/IMG/Others/Wait.gif");
    labelMovie->setMovie(movie);
    value = new QLabel(circle);
    button = new Button(circle);
    //button->setStyleSheet("background-color: rgba( 255, 255, 255, 0% );");
    button->setFocusPolicy(Qt::NoFocus);
    button->raise();
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    font.setPixelSize(11);
    font.setBold(true);


    if(isBuilding)
    {
        backGround = new QLabel((QWidget*)this->parent());

        backGround->setMinimumSize(fSize);
        backGround->setMaximumSize(fSize);
        backGround->setScaledContents(true);

        circle->setMinimumSize(17, 17);
        circle->setMaximumSize(17, 17);
        circle->setScaledContents(true);

        labelMovie->setMinimumSize(17, 17);
        labelMovie->setMaximumSize(17, 17);
        labelMovie->setScaledContents(true);


        button->setMinimumSize(circle->size().width(),circle->size().height());
        button->setMaximumSize(circle->size().width(),circle->size().height());

        value->setGeometry(1,0,15,15);

    }else
    {
        circle->setMinimumSize(fSize);
        circle->setMaximumSize(fSize);
        circle->setScaledContents(true);

        labelMovie->setMinimumSize(fSize.width(),fSize.height());
        labelMovie->setMaximumSize(fSize.width(),fSize.height());
        labelMovie->setScaledContents(true);

        button->setMinimumSize(fSize.width(),fSize.height());
        button->setMaximumSize(fSize.width(),fSize.height());

        value->setGeometry(5,4,15,15);

    }
}

void BuildingMapItem::setBrown(int fValue)
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBrown.png")));
    value->setText(QString("<font color='black'>%1</font>").arg(fValue));
    value->setFont(font);
}

void BuildingMapItem::setGreen(int fValue)
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlGreen.png")));
    value->setText(QString("<font color='black'>%1</font>").arg(fValue));
    value->setFont(font);
}

void BuildingMapItem::setGold(int fValue)
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlGold.png")));
    value->setText(QString("<font color='black'>%1</font>").arg(fValue));
    value->setFont(font);
}

void BuildingMapItem::setRed(int fValue)
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlRed.png")));
    value->setText(QString("<font color='black'>%1</font>").arg(fValue));
    value->setFont(font);
}

void BuildingMapItem::setBlue(int fValue)
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBlue.png")));
    value->setText(QString("<font color='black'>%1</font>").arg(fValue));
    value->setFont(font);
}

void BuildingMapItem::setPlus()
{
    circle->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/Plus.png")));
    value->setText("");

    backGround->setPixmap(QPixmap::fromImage(QImage(":/IMG/Building/0.png")));

}


void BuildingMapItem::buttonClicked()
{
    emit clicked();
}
