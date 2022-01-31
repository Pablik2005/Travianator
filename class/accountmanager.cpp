#include "accountmanager.h"
#include "ui_accountmanager.h"

AccountManager::AccountManager(QWidget *parent, QList<Account*> fAccountList) :
    QDialog(parent),
    ui(new Ui::AccountManager)
{

    ui->setupUi(this);
    this->setWindowTitle("Account Manager");

    save = false;
    loadAccounts(fAccountList);
    ui->pushButtonAdd->setDisabled(true);

    connect(ui->lineEditLogin, SIGNAL(textChanged(QString)), this, SLOT(textEdited()));
    connect(ui->lineEditPassword, SIGNAL(textChanged(QString)), this, SLOT(textEdited()));

    for(int i=0; i<9; i++)
        ui->comboBoxServerPrefix->addItem("ts" + QString::number(i+1));
    ui->comboBoxServerPrefix->setStyleSheet("QScrollBar { border-color: white; } QComboBox { border: 1px solid black; }");

    ui->comboBoxServerType->addItem("pl");
    ui->comboBoxServerType->addItem("com");
    ui->comboBoxServerType->setStyleSheet("QScrollBar { border-color: white; } QComboBox { border: 1px solid black; }");



    QFont tFont;
    tFont.setPixelSize(20);

    ui->lineEditLogin->setFont(tFont);
    ui->lineEditPassword->setFont(tFont);

    ui->listWidget->setFont(tFont);

    ui->labelLogin->setFont(tFont);
    ui->labelPassword->setFont(tFont);
    ui->labelServer->setFont(tFont);
    ui->labelTravian->setFont(tFont);

    ui->pushButtonAdd->setFont(tFont);
    ui->pushButtonCancel->setFont(tFont);
    ui->pushButtonClear->setFont(tFont);
    ui->pushButtonDel->setFont(tFont);
    ui->pushButtonOk->setFont(tFont);

    ui->comboBoxServerPrefix->setFont(tFont);
    ui->comboBoxServerType->setFont(tFont);
}

AccountManager::~AccountManager()
{
    delete ui;
}

void AccountManager::loadAccounts(QList<Account*> fAccountList)
{
    accountList = fAccountList;
    foreach(Account *i, accountList)
    {
        QListWidgetItem *tItem = new QListWidgetItem(i->login);
        tItem->setTextColor(Qt::black);
        ui->listWidget->addItem(tItem);
    }
}

void AccountManager::deleteAccount(int index)
{
    delete accountList.at(index);
    accountList.removeAt(index);
    ui->listWidget->takeItem(index);
}

void AccountManager::setLanguage(Language **fLanguage)
{
    this->setWindowTitle( (*fLanguage)->AccoutManagerTitle );

    ui->labelLogin->setText( (*fLanguage)->AccoutManagerLogin );
    ui->labelPassword->setText( (*fLanguage)->AccoutManagerPassword );
    ui->labelServer->setText( (*fLanguage)->AccoutManagerServer );

    ui->pushButtonAdd->setText( (*fLanguage)->AccoutManagerAdd );
    ui->pushButtonOk->setText( (*fLanguage)->AccoutManagerOk );
    ui->pushButtonCancel->setText( (*fLanguage)->AccoutManagerCancel );
    ui->pushButtonDel->setText( (*fLanguage)->AccoutManagerDel );
    ui->pushButtonClear->setText( (*fLanguage)->AccoutManagerClear );
}

void AccountManager::on_pushButtonAdd_clicked()
{
    Account *tAccount = new Account((QWidget*)this->parent(), travianWiki);
    tAccount->login = ui->lineEditLogin->text();
    tAccount->password = ui->lineEditPassword->text();
    tAccount->server = "http://" + ui->comboBoxServerPrefix->currentText() + ".travian." + ui->comboBoxServerType->currentText();
    tAccount->serverType = serverTypes.at( ui->comboBoxServerType->currentIndex() );
    tAccount->socketList = socketList;

    QListWidgetItem *tItem = new QListWidgetItem(tAccount->login);
    tItem->setTextColor(Qt::black);
    ui->listWidget->addItem(tItem);
    accountList.append(tAccount);
}

void AccountManager::on_pushButtonDel_clicked()
{
    if(ui->listWidget->currentRow() >= 0)
        deleteAccount( ui->listWidget->currentRow() );
}

void AccountManager::on_pushButtonClear_clicked()
{
    for(int i=accountList.count()-1; i>=0; i--)
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
    if(ui->lineEditLogin->text().isEmpty() || ui->lineEditPassword->text().isEmpty() )
        ui->pushButtonAdd->setDisabled(true);
    else
        ui->pushButtonAdd->setEnabled(true);
}
