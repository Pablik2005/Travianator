#include "dialoggettime.h"
#include "ui_dialoggettime.h"

DialogGetTime::DialogGetTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGetTime)
{
    ui->setupUi(this);

    ui->dateYear->setValue( QDate::currentDate().year() );
    ui->dateMonth->setValue( QDate::currentDate().month() );
    ui->dateDay->setValue( QDate::currentDate().day() );
    ui->dateHour->setValue( QTime::currentTime().hour() );
    ui->dateMinute->setValue( QTime::currentTime().minute() );
    ui->dateSecond->setValue( QTime::currentTime().second() );

    ui->timeHour->setValue(0);
    ui->timeMinute->setValue(0);
    ui->timeSecond->setValue(0);

    ui->radioButtonTime->setChecked(true);
    //ui->radioButtonTime->setStyleSheet("QRadioButton { selection-background-color: rgba(255, 255, 255, 10) } ");
    //ui->radioButtonDate->setStyleSheet("selection-background-color: rgba(255, 255, 255, 10)");



    save = false;


    QFont tFont;
    tFont.setPixelSize(12);

    ui->radioButtonTime->setFont(tFont);
    ui->radioButtonDate->setFont(tFont);

    ui->radioButtonDate->setFont(tFont);
    ui->radioButtonTime->setFont(tFont);

    ui->labelYear->setFont(tFont);
    ui->labelMonth->setFont(tFont);
    ui->labelDay->setFont(tFont);

    ui->labelHour1->setFont(tFont);
    ui->labelHour2->setFont(tFont);
    ui->labelMinute1->setFont(tFont);
    ui->labelMinute2->setFont(tFont);
    ui->labelSecond1->setFont(tFont);
    ui->labelSecond2->setFont(tFont);

}

DialogGetTime::~DialogGetTime()
{
    delete ui;
}

void DialogGetTime::setLanguage(Language **fLanguage)
{
    this->setWindowTitle( (*fLanguage)->DialogGetTimeTitle );
    ui->radioButtonDate->setText( (*fLanguage)->DialogGetTimeDay );
    ui->radioButtonTime->setText( (*fLanguage)->DialogGetTimeFor );

    ui->labelYear->setText( (*fLanguage)->DialogGetTimeYear );
    ui->labelMonth->setText( (*fLanguage)->DialogGetTimeMonth );
    ui->labelDay->setText( (*fLanguage)->DialogGetTimeDay );

    ui->labelHour1->setText( (*fLanguage)->DialogGetTimeHour );
    ui->labelHour2->setText( (*fLanguage)->DialogGetTimeHour );
    ui->labelMinute1->setText( (*fLanguage)->DialogGetTimeMinute );
    ui->labelMinute2->setText( (*fLanguage)->DialogGetTimeMinute );
    ui->labelSecond1->setText( (*fLanguage)->DialogGetTimeSecound );
    ui->labelSecond2->setText( (*fLanguage)->DialogGetTimeSecound );

}

void DialogGetTime::on_pushButtonOK_clicked()
{
    save = true;

    if(ui->radioButtonDate->isChecked())
        time.setHMS(QDate(ui->dateYear->value(), ui->dateMonth->value(), ui->dateDay->value()), QTime(ui->dateHour->value(), ui->dateMinute->value(), ui->dateSecond->value()));
    else
        time.setHMS( Time::currentTime().addSeconds( Time::toSeconds( Time( ui->timeHour->value(), ui->timeMinute->value(), ui->timeSecond->value() ) )));

    close();
}

void DialogGetTime::on_pushButtonCancel_clicked()
{
    save = false;
    close();
}
