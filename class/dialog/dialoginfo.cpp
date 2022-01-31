#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("Info");
    this->setStyleSheet("QDialog { border: 1px solid black; }");

}

DialogInfo::~DialogInfo()
{
    delete ui;
}
