#include "itembuildtask.h"
#include "ui_itembuildtask.h"

ItemBuildTask::ItemBuildTask(QWidget *parent) :
    Item(parent),
    ui(new Ui::ItemBuildTask)
{
    ui->setupUi(this);

    fontTime.setPixelSize(11);
    font.setPixelSize(11);
    font.setBold(true);

    click = 0;

}

ItemBuildTask::~ItemBuildTask()
{
    delete ui;
}


void ItemBuildTask::setBuildingType(QString fImgPath)
{
    ui->imgType->setPixmap(QPixmap::fromImage(QImage(fImgPath)));
}

void ItemBuildTask::setTitle(QString fTitle)
{
    ui->title->setText(fTitle);
    ui->title->setFont(font);
}

void ItemBuildTask::setAvaibleTime(QString fAvaibleTime)
{
    ui->timeAvaible->setText(fAvaibleTime);
    ui->timeAvaible->setFont(font);
}

void ItemBuildTask::setKeyTime(QString fKeyTime)
{
    ui->imgKey->setHidden(false);
    ui->timeKey->setHidden(false);
    ui->timeKey->setText(fKeyTime);
    ui->timeKey->setFont(font);
}

void ItemBuildTask::setKeyHidden()
{
    ui->imgKey->setHidden(true);
    ui->timeKey->setHidden(true);
}


void ItemBuildTask::setUpgradeTime(QString fUpgradeTime)
{
    ui->timeBild->setText(fUpgradeTime);
    ui->timeBild->setFont(font);
}

void ItemBuildTask::setLvlGreen(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlGreen.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);

}

void ItemBuildTask::setLvlRed(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlRed.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);

}
void ItemBuildTask::setLvlBrown(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBrown.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);

}
void ItemBuildTask::setCorn2Green(int fCorn2)
{
    ui->corn2->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn2) );
    ui->corn2->setFont(font);
}
void ItemBuildTask::setCorn2Red(int fCorn2)
{
    ui->corn2->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn2) );
    ui->corn2->setFont(font);
}

void ItemBuildTask::setWoodGreen(int fWood)
{
    ui->wood->setText( QString("<font color='green'>%1</font>").arg(fWood) );
    ui->wood->setFont(font);

}
void ItemBuildTask::setWoodRed(int fWood)
{
    ui->wood->setText( QString("<font color='red'><b>%1</b></font>").arg(fWood) );
    ui->wood->setFont(font);

}
void ItemBuildTask::setWoodTime(QString fTime)
{
    ui->timeWood->setText( fTime );
    ui->timeWood->setFont(fontTime);
}

void ItemBuildTask::setClayGreen(int fClay)
{
    ui->clay->setText( QString("<font color='green'><b>%1</b></font>").arg(fClay) );
    ui->clay->setFont(font);

}
void ItemBuildTask::setClayRed(int fClay)
{
    ui->clay->setText( QString("<font color='red'><b>%1</b></font>").arg(fClay) );
    ui->clay->setFont(font);
}
void ItemBuildTask::setClayTime(QString fTime)
{
    ui->timeClay->setText( fTime );
    ui->timeClay->setFont(fontTime);
}


void ItemBuildTask::setIronGreen(int fIron)
{
    ui->iron->setText( QString("<font color='green'><b>%1</b></font>").arg(fIron) );
    ui->iron->setFont(font);
}

void ItemBuildTask::setIronRed(int fIron)
{
    ui->iron->setText( QString("<font color='red'><b>%1</b></font>").arg(fIron) );
    ui->iron->setFont(font);
}

void ItemBuildTask::setIronTime(QString fTime)
{
    ui->timeIron->setText( fTime );
    ui->timeIron->setFont(fontTime);
}

void ItemBuildTask::setCornGreen(int fCorn)
{
    ui->corn->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn) );
    ui->corn->setFont(font);

}
void ItemBuildTask::setCornRed(int fCorn)
{
    ui->corn->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn) );
    ui->corn->setFont(font);
}

void ItemBuildTask::setCornTime(QString fTime)
{
    ui->timeCorn->setText( fTime );
    ui->timeCorn->setFont(fontTime);
}

void ItemBuildTask::setBonus(QString fBonus)
{
    ui->bonus->setText( QString("<b>%1</b>").arg(fBonus) );
    ui->bonus->setFont(font);
}

void ItemBuildTask::setBonusPast(QString fBonus)
{
    ui->bonusPast->setText( fBonus );
    ui->bonusPast->setFont(fontTime);
}

bool ItemBuildTask::qSort(ItemBuildTask *fItem1, ItemBuildTask *fItem2)
{
    return ( fItem1->task.timeToWait < fItem2->task.timeToWait );
}


void ItemBuildTask::mouseMoveEvent(QMouseEvent *e)
{
    Item::mouseMoveEvent(e);

}

void ItemBuildTask::mousePressEvent(QMouseEvent *e)
{
    Item::mousePressEvent(e);
    click++;

    if( click >= 2 )
    {
        click = 0;
        emit clicked(this);

    }else
        QTimer::singleShot(400, this, SLOT(clearClick()));

}

void ItemBuildTask::mouseReleaseEvent(QMouseEvent *e)
{
    Item::mouseReleaseEvent(e);
}

void ItemBuildTask::clearClick()
{
    click = 0;
}


