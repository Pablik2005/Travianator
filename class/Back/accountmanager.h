#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QDialog>
#include <QString>
#include <QList>
#include "class/Enums.h"


namespace Ui {
class AccountManager;
}

class AccountManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountManager(QWidget *parent, QList<Acc> *fAccountList);
    ~AccountManager();

    void loadAccounts();
    void deleteAccount(int index);

    bool save;
    QList<Acc> *accountList;
    
private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonDel_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();
    void textEdited();

private:
    Ui::AccountManager *ui;
};

#endif // ACCOUNTMANAGER_H
