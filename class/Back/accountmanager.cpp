#include "accountmanager.h"
#include "ui_accountmanager.h"

AccountManager::AccountManager(QWidget *parent, QList<Acc> *fAccountList) :
    QDialog(parent),
    ui(new Ui::AccountManager)
{
    ui->setupUi(this);

    save = false;
    accountList = fAccountList;
    loadAccounts();
    ui->lineEditServer->setText("http://ts9.travian.pl");
    ui->pushButtonAdd->setDisabled(true);

    connect(ui->lineEditLogin, SIGNAL(textChanged(QString)), this, SLOT(textEdited()));
    connect(ui->lineEditPassword, SIGNAL(textChanged(QString)), this, SLOT(textEdited()));
    connect(ui->lineEditServer, SIGNAL(textChanged(QString)), this, SLOT(textEdited()));
}

AccountManager::~AccountManager()
{
    delete ui;
}

void AccountManager::loadAccounts()
{

    foreach(Acc i, *accountList)
    {
        QListWidgetItem *tItem = new QListWidgetItem(i.login);
        tItem->setTextColor(Qt::black);
        ui->listWidget->addItem(tItem);
    }
}

void AccountManager::deleteAccount(int index)
{
    accountList->removeAt(index);
    ui->listWidget->takeItem(index);
}

void AccountManager::on_pushButtonAdd_clicked()
{
    Acc tAccount;
    tAccount.login = ui->lineEditLogin->text();
    tAccount.password = ui->lineEditPassword->text();
    tAccount.server = ui->lineEditServer->text();
    tAccount.exist = false;

    QListWidgetItem *tItem = new QListWidgetItem(tAccount.login);
    tItem->setTextColor(Qt::black);
    ui->listWidget->addItem(tItem);
    accountList->append(tAccount);
}

void AccountManager::on_pushButtonDel_clicked()
{
    if(ui->listWidget->currentRow() >= 0)
        deleteAccount( ui->listWidget->currentRow() );

}

void AccountManager::on_pushButtonClear_clicked()
{
    for(int i=accountList->count()-1; i>=0; i--)
    {
        deleteAccount(i);
    }

}

void AccountManager::on_pushButtonOk_clicked()
{
    save = true ;
    close();

}

void AccountManager::on_pushButtonCancel_clicked()
{
    close();
}

void AccountManager::textEdited()
{
    if(ui->lineEditLogin->text().isEmpty() || ui->lineEditPassword->text().isEmpty() ||ui->lineEditServer->text().isEmpty())
        ui->pushButtonAdd->setDisabled(true);
    else
        ui->pushButtonAdd->setEnabled(true);
}
