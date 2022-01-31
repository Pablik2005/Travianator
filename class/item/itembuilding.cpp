#include "itembuilding.h"
#include "ui_itembuilding.h"

ItemBuilding::ItemBuilding(QWidget *parent) :
    Item(parent),
    ui(new Ui::ItemBuilding)
{
    ui->setupUi(this);

    fontTime.setPixelSize(11);
    font.setPixelSize(11);
    font.setBold(true);

    labelMovie = ui->labelMovie;
    movie = new QMovie(labelMovie);
    movie->setFileName(":/IMG/Others/Wait.gif");
    labelMovie->setMovie(movie);

    click = 0;

}

ItemBuilding::~ItemBuilding()
{
    delete ui;
}


void ItemBuilding::setBuildingType(QString fImgPath)
{
    ui->imgType->setPixmap(QPixmap::fromImage(QImage(fImgPath)));
}

void ItemBuilding::setTitle(QString fTitle)
{
    ui->title->setText(fTitle);
    ui->title->setFont(font);
}

void ItemBuilding::setUpgradeTime(QString fUpgradeTime)
{
    ui->timeBild->setText(fUpgradeTime);
    ui->timeBild->setFont(font);
}

void ItemBuilding::setLvlGreen(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlGreen.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);

}

void ItemBuilding::setLvlRed(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlRed.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);

}
void ItemBuilding::setLvlBrown(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBrown.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);
}

void ItemBuilding::setLvlBlue(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBlue.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);
}
void ItemBuilding::setCorn2Green(int fCorn2)
{
    ui->corn2->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn2) );
    ui->corn2->setFont(font);
}
void ItemBuilding::setCorn2Red(int fCorn2)
{
    ui->corn2->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn2) );
    ui->corn2->setFont(font);
}

void ItemBuilding::setWoodGreen(int fWood)
{
    ui->wood->setText( QString("<font color='green'>%1</font>").arg(fWood) );
    ui->wood->setFont(font);

}
void ItemBuilding::setWoodRed(int fWood)
{
    ui->wood->setText( QString("<font color='red'><b>%1</b></font>").arg(fWood) );
    ui->wood->setFont(font);

}
void ItemBuilding::setWoodTime(QString fTime)
{
    ui->timeWood->setText( fTime );
    ui->timeWood->setFont(fontTime);
}

void ItemBuilding::setClayGreen(int fClay)
{
    ui->clay->setText( QString("<font color='green'><b>%1</b></font>").arg(fClay) );
    ui->clay->setFont(font);

}
void ItemBuilding::setClayRed(int fClay)
{
    ui->clay->setText( QString("<font color='red'><b>%1</b></font>").arg(fClay) );
    ui->clay->setFont(font);
}
void ItemBuilding::setClayTime(QString fTime)
{
    ui->timeClay->setText( fTime );
    ui->timeClay->setFont(fontTime);
}


void ItemBuilding::setIronGreen(int fIron)
{
    ui->iron->setText( QString("<font color='green'><b>%1</b></font>").arg(fIron) );
    ui->iron->setFont(font);
}

void ItemBuilding::setIronRed(int fIron)
{
    ui->iron->setText( QString("<font color='red'><b>%1</b></font>").arg(fIron) );
    ui->iron->setFont(font);
}

void ItemBuilding::setIronTime(QString fTime)
{
    ui->timeIron->setText( fTime );
    ui->timeIron->setFont(fontTime);
}

void ItemBuilding::setCornGreen(int fCorn)
{
    ui->corn->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn) );
    ui->corn->setFont(font);

}
void ItemBuilding::setCornRed(int fCorn)
{
    ui->corn->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn) );
    ui->corn->setFont(font);
}

void ItemBuilding::setCornTime(QString fTime)
{
    ui->timeCorn->setText( fTime );
    ui->timeCorn->setFont(fontTime);
}

void ItemBuilding::setBonus(QString fBonus)
{
    ui->bonus->setText( fBonus );
    ui->bonus->setFont(font);
}

void ItemBuilding::setBonusPast(QString fBonus)
{
    ui->bonusPast->setText( fBonus );
    ui->bonusPast->setFont(fontTime);
}


void ItemBuilding::mouseMoveEvent(QMouseEvent *e)
{
    Item::mouseMoveEvent(e);

}

void ItemBuilding::mousePressEvent(QMouseEvent *e)
{
    Item::mousePressEvent(e);
    click++;

    if( click >= 2 )
        emit clicked();

    QTimer::singleShot(400, this, SLOT(clearClick()));

}

void ItemBuilding::mouseReleaseEvent(QMouseEvent *e)
{
    Item::mouseReleaseEvent(e);
}

void ItemBuilding::clearClick()
{
    click = 0;
}
