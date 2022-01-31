#ifndef DIALOGGETTIME_H
#define DIALOGGETTIME_H

#include <QDialog>
#include <QDate>
#include <QTime>
#include <QMessageBox>

#include "../time.h"
#include "../language.h"

namespace Ui {
class DialogGetTime;
}

class DialogGetTime : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogGetTime(QWidget *parent = 0);
    ~DialogGetTime();

    Time time;
    bool save;

    void setLanguage(Language **fLanguage);
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::DialogGetTime *ui;
};

#endif // DIALOGGETTIME_H
