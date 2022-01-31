#include "dialogshows.h"
#include "ui_dialogshows.h"

DialogShows::DialogShows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShows)
{
    ui->setupUi(this);
    this->setWindowTitle("Shows");

    connect(ui->radioAll1, SIGNAL(clicked()), this, SLOT(changedInGroupBox1()));
    connect(ui->radioResource, SIGNAL(clicked()), this, SLOT(changedInGroupBox1()));
    connect(ui->radioInfrastructure, SIGNAL(clicked()), this, SLOT(changedInGroupBox1()));

    connect(ui->radioAll2, SIGNAL(clicked()), this, SLOT(changedInGroupBox2()));
    connect(ui->radioCantUpgrade, SIGNAL(clicked()), this, SLOT(changedInGroupBox2()));
    connect(ui->radioCanUpgrade, SIGNAL(clicked()), this, SLOT(changedInGroupBox2()));
}

DialogShows::~DialogShows()
{
    delete ui;
}

void DialogShows::on_Ok_clicked()
{
    save = true;
    close();
}

void DialogShows::on_Cancel_clicked()
{
    close();
}

void DialogShows::exec()
{
    save = false;

    if(showResource && showInfrastructure)
    {
        ui->radioAll1->setChecked(true);

    }else if(showResource)
    {
        ui->radioResource->setChecked(true);

    }else
    {
        ui->radioInfrastructure->setChecked(true);

    }

    if(showCanUpgrade && showCantUpgrade)
    {
        ui->radioAll2->setChecked(true);

    }else if(showCanUpgrade)
    {
        ui->radioCanUpgrade->setChecked(true);

    }else
    {
        ui->radioCantUpgrade->setChecked(true);
    }

    QDialog::exec();
}

void DialogShows::changedInGroupBox1()
{
    if(ui->radioAll1->isChecked())
    {
        showResource = true;
        showInfrastructure = true;

    }else if(ui->radioResource->isChecked())
    {
        showResource = true;
        showInfrastructure = false;
    }else
    {
        showResource = false;
        showInfrastructure = true;
    }
}

void DialogShows::changedInGroupBox2()
{
    if(ui->radioAll2->isChecked())
    {
        showCanUpgrade = true;
        showCantUpgrade = true;


    }else if(ui->radioCanUpgrade->isChecked())
    {
        showCanUpgrade = true;
        showCantUpgrade = false;
    }else
    {
        showCanUpgrade = false;
        showCantUpgrade = true;
    }
}
