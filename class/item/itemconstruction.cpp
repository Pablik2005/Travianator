#include "itemconstruction.h"
#include "ui_itemconstruction.h"

ItemConstruction::ItemConstruction(QWidget *parent) :
    Item(parent),
    ui(new Ui::ItemConstruction)
{
    ui->setupUi(this);

    font.setPixelSize(11);
    font.setBold(true);

    movie = new QMovie(ui->Abord);
    movie->setFileName(":/IMG/Others/x.gif");
    ui->Abord->setMovie(movie);
    movie->jumpToFrame(0);
    click = 0;
}

ItemConstruction::~ItemConstruction()
{
    delete ui;
}

void ItemConstruction::setLvl(int fValue)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBrown.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fValue));
    ui->lvl->setFont(font);
}

void ItemConstruction::setTime(QString fTime)
{
    ui->Clock->setText(fTime);
    ui->Clock->setFont(font);
}

void ItemConstruction::setType(QString fImgPath)
{
    ui->imgType->setPixmap(QPixmap::fromImage(QImage(fImgPath)));
}

void ItemConstruction::setTitle(QString fTitle)
{
    ui->title->setText(fTitle);
    ui->title->setFont(font);
}

void ItemConstruction::mousePressEvent(QMouseEvent *)
{
    click++;

    if( click >= 2 )
    {
        click = 0;
        emit clicked(building.abortValueD, movie);

    }else
        QTimer::singleShot(400, this, SLOT(clearClick()));
}


void ItemConstruction::clearClick()
{
    click = 0;
}

