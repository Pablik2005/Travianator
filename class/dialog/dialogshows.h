#ifndef DIALOGSHOWS_H
#define DIALOGSHOWS_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DialogShows;
}

class DialogShows : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogShows(QWidget *parent = 0);
    ~DialogShows();

    bool showResource;
    bool showInfrastructure;
    bool showCanUpgrade;
    bool showCantUpgrade;

    bool save;

    void exec();
    
private slots:
    void changedInGroupBox1();
    void changedInGroupBox2();

    void on_Ok_clicked();
    void on_Cancel_clicked();

private:
    Ui::DialogShows *ui;

};

#endif // DIALOGSHOWS_H
