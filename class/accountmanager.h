#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QDialog>
#include <QString>
#include <QList>
#include "account.h"
#include "travianwiki.h"
#include "buildingsocket.h"
#include "language.h"

namespace Ui {
class AccountManager;
}

class AccountManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountManager(QWidget *parent, QList<Account*> fAccountList);
    ~AccountManager();

    void loadAccounts(QList<Account*> fAccountList);
    void deleteAccount(int index);

    void setLanguage(Language **fLanguage);

    bool save;
    TravianWiki *travianWiki;
    QList<BuildingSocket*> *socketList;
    QList<Account*> accountList;
    QList<ServerType*> serverTypes;
    
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
