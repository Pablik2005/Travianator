#include "itembuildinghorizontal.h"
#include "ui_itembuildinghorizontal.h"

ItemBuildingHorizontal::ItemBuildingHorizontal(QWidget *parent) :
    Item(parent),
    ui(new Ui::ItemBuildingHorizontal)
{
    ui->setupUi(this);

    ui->req1->setHidden(true);
    ui->req2->setHidden(true);
    ui->req3->setHidden(true);
    ui->req4->setHidden(true);

    font.setPixelSize(11);
    font.setBold(true);

    click=0;
}

ItemBuildingHorizontal::~ItemBuildingHorizontal()
{
    delete ui;
}

void ItemBuildingHorizontal::setBuildingType(int fIdBuilding)
{
    ui->imgType->setPixmap(QPixmap::fromImage(QImage(QString(":/IMG/Building/%1.png").arg(fIdBuilding))));
}

void ItemBuildingHorizontal::setTitle(QString fTitem)
{
    ui->Title->setText( fTitem );
    ui->Title->setFont(font);
}

void ItemBuildingHorizontal::setTimeToAvaibleHidde(bool fBool)
{
    if(fBool)
        ui->Time->setHidden(true);
    else
        ui->Time->setHidden(false);
}

void ItemBuildingHorizontal::setTimeToAvaible(QString fTime)
{
    ui->Time->setText(QString("<b><font color='red'>%1</font></b>").arg(fTime));
    ui->Time->setFont(font);
}

void ItemBuildingHorizontal::setTimeUpgradeLong(QString fTime)
{
    ui->Clock->setText(fTime);
    ui->Clock->setFont(font);
}

void ItemBuildingHorizontal::setLvlHidde(bool fBool)
{
    if(fBool)
    {
        ui->imgLvl->setHidden(true);
        ui->lvl->setHidden(true);
    }else
    {
        ui->imgLvl->setHidden(false);
        ui->lvl->setHidden(false);
    }
}

void ItemBuildingHorizontal::setLvlGreen(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlGreen.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);
}

void ItemBuildingHorizontal::setLvlRed(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlRed.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);
}

void ItemBuildingHorizontal::setLvlBrown(int fLvl)
{
    ui->imgLvl->setPixmap(QPixmap::fromImage(QImage(":/IMG/Others/LvlBrown.png")));
    ui->lvl->setText(QString("<font color='black'>%1</font>").arg(fLvl));
    ui->lvl->setFont(font);
}

void ItemBuildingHorizontal::setWoodGreen(int fWood)
{
    ui->Wood->setText( QString("<font color='green'><b>%1</b></font>").arg(fWood) );
    ui->Wood->setFont(font);
}

void ItemBuildingHorizontal::setWoodRed(int fWood)
{
    ui->Wood->setText( QString("<font color='red'><b>%1</b></font>").arg(fWood) );
    ui->Wood->setFont(font);
}

void ItemBuildingHorizontal::setClayGreen(int fClay)
{
    ui->Clay->setText( QString("<font color='green'><b>%1</b></font>").arg(fClay) );
    ui->Clay->setFont(font);
}

void ItemBuildingHorizontal::setClayRed(int fClay)
{
    ui->Clay->setText( QString("<font color='red'><b>%1</b></font>").arg(fClay) );
    ui->Clay->setFont(font);
}

void ItemBuildingHorizontal::setIronGreen(int fIron)
{
    ui->Iron->setText( QString("<font color='green'><b>%1</b></font>").arg(fIron) );
    ui->Iron->setFont(font);
}

void ItemBuildingHorizontal::setIronRed(int fIron)
{
    ui->Iron->setText( QString("<font color='red'><b>%1</b></font>").arg(fIron) );
    ui->Iron->setFont(font);

}

void ItemBuildingHorizontal::setCornGreen(int fCorn)
{
    ui->Corn->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn) );
    ui->Corn->setFont(font);
}

void ItemBuildingHorizontal::setCornRed(int fCorn)
{
    ui->Corn->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn) );
    ui->Corn->setFont(font);
}

void ItemBuildingHorizontal::setCorn2Green(int fCorn2)
{
    ui->Corn2->setText( QString("<font color='green'><b>%1</b></font>").arg(fCorn2) );
    ui->Corn2->setFont(font);
}

void ItemBuildingHorizontal::setCorn2Red(int fCorn2)
{
    ui->Corn2->setText( QString("<font color='red'><b>%1</b></font>").arg(fCorn2) );
    ui->Corn2->setFont(font);
}

void ItemBuildingHorizontal::setReq1Red(QString fReq)
{
    setHiddenAll();

    ui->req1->setHidden(false);
    ui->req1->setText( QString("<font color='red'><b>%1</b></font>").arg(fReq) );
    ui->req1->setFont(font);

}

void ItemBuildingHorizontal::setReq1Green(QString fReq)
{
    setHiddenAll();

    ui->req1->setHidden(false);
    ui->req1->setText( QString("<font color='green'><b>%1</b></font>").arg(fReq) );
    ui->req1->setFont(font);
}

void ItemBuildingHorizontal::setReq2Red(QString fReq)
{
    ui->req2->setHidden(false);
    ui->req2->setText( QString("<font color='red'><b>%1</b></font>").arg(fReq) );
    ui->req2->setFont(font);

}

void ItemBuildingHorizontal::setReq2Green(QString fReq)
{
    ui->req2->setHidden(false);
    ui->req2->setText( QString("<font color='green'><b>%1</b></font>").arg(fReq) );
    ui->req2->setFont(font);

}

void ItemBuildingHorizontal::setReq3Red(QString fReq)
{
    ui->req3->setHidden(false);
    ui->req3->setText( QString("<font color='red'><b>%1</b></font>").arg(fReq) );
    ui->req3->setFont(font);
}

void ItemBuildingHorizontal::setReq3Green(QString fReq)
{
    ui->req3->setHidden(false);
    ui->req3->setText( QString("<font color='green'><b>%1</b></font>").arg(fReq) );
    ui->req3->setFont(font);

}

void ItemBuildingHorizontal::setReq4Red(QString fReq)
{
    ui->req4->setHidden(false);
    ui->req4->setText( QString("<font color='red'><b>%1</b></font>").arg(fReq) );
    ui->req4->setFont(font);
}

void ItemBuildingHorizontal::setReq4Green(QString fReq)
{
    ui->req4->setHidden(false);
    ui->req4->setText( QString("<font color='green'><b>%1</b></font>").arg(fReq) );
    ui->req4->setFont(font);

}

void ItemBuildingHorizontal::setHiddenAll()
{
    setTimeToAvaibleHidde(true);
    setLvlHidde(true);
    ui->imgWood->setHidden(true);
    ui->imgClay->setHidden(true);
    ui->imgIron->setHidden(true);
    ui->imgCorn->setHidden(true);
    ui->imgCorn2->setHidden(true);
    ui->imgClock->setHidden(true);

    ui->Wood->setHidden(true);
    ui->Clay->setHidden(true);
    ui->Iron->setHidden(true);
    ui->Corn->setHidden(true);
    ui->Corn2->setHidden(true);
    ui->Clock->setHidden(true);
}

void ItemBuildingHorizontal::mouseMoveEvent(QMouseEvent *e)
{
    Item::mouseMoveEvent(e);

}

void ItemBuildingHorizontal::mousePressEvent(QMouseEvent *e)
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

void ItemBuildingHorizontal::mouseReleaseEvent(QMouseEvent *e)
{
    Item::mouseReleaseEvent(e);
}

void ItemBuildingHorizontal::clearClick()
{
    click = 0;
}
