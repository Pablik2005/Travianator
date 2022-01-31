#include "dialoglanguages.h"
#include "ui_dialoglanguages.h"

DialogLanguages::DialogLanguages(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLanguages)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Language");

    save = false;
    comboBox = ui->comboBox;
    comboBox->setStyleSheet("QComboBox { border: 1px solid black; }");
    this->setStyleSheet("QDialog { border: 1px solid black; }");
}

DialogLanguages::~DialogLanguages()
{
    delete ui;
}

void DialogLanguages::on_OK_clicked()
{
    save = true;
    close();
}

void DialogLanguages::on_Cancel_clicked()
{
    close();
}
