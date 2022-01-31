#include "account.h"

Account::Account(QWidget *parent, TravianWiki *fTravianWiki):
    QThread(parent)
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName ("UTF-8"));
    connect(this, SIGNAL(requestHendlerStart()), this, SLOT(requestHendler()));

    isLogin = false;
    dataLock = 0;
    isRequestHendlerWorking = false;
    travianWiki = fTravianWiki;
    requestSendAttempts = 0;
    requestSendCount = 0;
}
Account::~Account()
{
    //Logout();
    foreach(Village *i, villages)
        delete i;

    foreach(TravianRequest *i, requestQueue)
        delete i;
}

void Account::Login()
{
    // XML
    XMLAccount = XMLDocument->createElement("Account");
    XMLAccount.setAttribute("Name", login);
    XMLAccounts->appendChild(XMLAccount);

    RequestLogin *tRequestLogin = new RequestLogin((QWidget*)this->parent(),
                                                   &networkManager ,
                                                   server ,
                                                   login,
                                                   password,
                                                   &nation,
                                                   &isLogin,
                                                   &villagesTemp,
                                                   serverType);

    connect(tRequestLogin, SIGNAL(loginFinished()), this, SLOT(loginFinished()));
    requestQueue.append(tRequestLogin);

    if(!isRequestHendlerWorking)
        emit requestHendlerStart();

}

void Account::Logout()
{
    networkManager.get(QNetworkRequest(QUrl(server + QString("/logout.php"))));
}

void Account::requestHendler()
{

    isRequestHendlerWorking = true;

    TravianRequest *tRequest;

    while(requestQueue.count())
    {
        //if(requestQueue.count() > 1)
        //{
            //wez tą z najeiWkszym priorytetem
        //}else
            tRequest = requestQueue.takeFirst();

            //QMessageBox::information(0, "Acc" + QString::number(idAccount),tRequest->typeName);

            if(tRequest->type != 1)
            {
                if(isLogin)
                {
                    requestSendAttempts = 0;
                    currentRequest = tRequest;
                    requestExecute();
                    requestSendCount++;

                }
            }else
            {

                if( tRequest->execute() )
                {
                    emit setStatusOn(false);
                    QMessageBox::information(0,"Error","Internet connection error");
                }else
                    emit setStatusOn(true);

                QTimer::singleShot(100, this, SLOT( requestExecuteFinished() ));

            }
            waitForFinishExecute.exec();
            delete tRequest;
    }

    isRequestHendlerWorking = false;

}

void Account::requestExecute()
{
    requestSendAttempts++;

    if(requestSendAttempts >24 )
    {
        QMessageBox::information(0,"Error","Internet connection error");
        QTimer::singleShot(10, this, SLOT( requestExecuteFinished() ));
        return;
    }else if( currentRequest->execute() )
    {
        emit setStatusOn(false);
        QTimer::singleShot(5000,this, SLOT(requestExecute()));
    }else
    {
        emit setStatusOn(true);
        QTimer::singleShot(100, this, SLOT( requestExecuteFinished() ));
        return;
    }
}

void Account::requestExecuteFinished()
{
    waitForFinishExecute.quit();
}

void Account::loginFinished()
{
    foreach(Village *i, villages)
        delete i;
    villages.clear();

    int index=0;
    foreach(VillageTemp i, villagesTemp)
    {
        Village *tVillage = new Village(this);
        tVillage->name = i.name;
        tVillage->newdID = i.newdID;
        tVillage->coordinates = i.coordinates;
        tVillage->idVillage = index;

        tVillage->setPointers(&nation,
                              &server,
                              &login,
                              &password,
                              travianWiki,
                              &isRequestHendlerWorking,
                              socketList,
                              XMLDocument,
                              &XMLAccount,
                              onAndroid);

        /*
        connect(tVillage, SIGNAL(requestHendlerStart()), this, SLOT(requestHendler()));
        connect(tVillage, SIGNAL(villageRefreshed(int)), this, SLOT(emitVillagesRefreshed(int)));
        connect(tVillage, SIGNAL(tasksBuildChanged(int)), this, SLOT(emitTasksBuildChanged(int)));
        */
        connect(tVillage, SIGNAL(addRequestRefreshVillage(Village*)), this, SLOT(addRequestRefreshVillage(Village*)));
        connect(tVillage, SIGNAL(addRequestBuildingUpgrade(Village*,int)), this, SLOT(addRequestBuildingUpgrade(Village*,int)));
        connect(tVillage, SIGNAL(addRequestBuildingUpgrade(Village*,int,int)), this, SLOT(addRequestBuildingUpgrade(Village*,int,int)));
        connect(tVillage, SIGNAL(addRequestBuildingBuildAbort(Village*,QString,QMovie*)), this, SLOT(addRequestBuildingBuildAbort(Village*,QString,QMovie*)));

        connect(tVillage, SIGNAL(tasksBuildChanged(Village*)), this, SLOT(tasksBuildChanged(Village*)));

        tVillage->refresh();
        villages.append(tVillage);
        index++;
    }

    this->isLogin = true;
    emit loginFinished(villagesTemp);
}

void Account::addRequestRefreshVillage(Village *fVillage)
{
    RequestRefresh *tRequest = new RequestRefresh(((QWidget*) this->parent()),
                                                  &networkManager,
                                                  server,
                                                  login,
                                                  password,
                                                  travianWiki,
                                                  fVillage,
                                                  serverType);

    connect(tRequest, SIGNAL(requestRefreshVillageFinished(Village*)), this, SLOT(requestRefreshVillageFinished(Village*)));

    requestQueue.append(tRequest);
    if(!(isRequestHendlerWorking))
        emit requestHendlerStart();
}

void Account::addRequestBuildingUpgrade(Village *fVillage, int fIdPlace)
{
    RequestBuildingUpgrade *tRequest = new RequestBuildingUpgrade(((QWidget*) this->parent()),
                                                                  &networkManager,
                                                                  server,
                                                                  login,
                                                                  password,
                                                                  travianWiki,
                                                                  fVillage,
                                                                  serverType,

                                                                  fIdPlace,
                                                                  socketList);

    connect(tRequest, SIGNAL(requestRefreshVillageFinished(Village*)), this, SLOT(requestRefreshVillageFinished(Village*)));
    connect(tRequest, SIGNAL(tasksBuildChanged(Village*)), this, SLOT(tasksBuildChanged(Village*)));

    requestQueue.append(tRequest);
    if(!(isRequestHendlerWorking))
        emit requestHendlerStart();

}

void Account::addRequestBuildingUpgrade(Village *fVillage, int fIdPlace, int fIdBuilding)
{
    RequestBuildingBuild *tRequest = new RequestBuildingBuild(((QWidget*) this->parent()),
                                                              &networkManager,
                                                              server,
                                                              login,
                                                              password,
                                                              travianWiki,
                                                              fVillage,
                                                              serverType,

                                                              fIdPlace,
                                                              socketList,
                                                              fIdBuilding);

    connect(tRequest, SIGNAL(requestRefreshVillageFinished(Village*)), this, SLOT(requestRefreshVillageFinished(Village*)));
    connect(tRequest, SIGNAL(tasksBuildChanged(Village*)), this, SLOT(tasksBuildChanged(Village*)));

    requestQueue.append(tRequest);
    if(!(isRequestHendlerWorking))
        emit requestHendlerStart();
}

void Account::addRequestBuildingBuildAbort(Village *fVillage, QString fAbordValueD, QMovie *fMovie)
{
    RequestBuildingBuildAbord *tRequest = new RequestBuildingBuildAbord(((QWidget*) this->parent()),
                                                                        &networkManager,
                                                                        server,
                                                                        login,
                                                                        password,
                                                                        travianWiki,
                                                                        fVillage,
                                                                        serverType,

                                                                        fAbordValueD,
                                                                        fMovie);

    connect(tRequest, SIGNAL(requestRefreshVillageFinished(Village*)), this, SLOT(requestRefreshVillageFinished(Village*)));

    requestQueue.append(tRequest);
    if(!(isRequestHendlerWorking))
        emit requestHendlerStart();
}


//-------------------Slots-------------------//


void Account::requestRefreshVillageFinished(Village *fVillage)
{
    emit villageRefreshed(idAccount, fVillage->idVillage);
}

void Account::tasksBuildChanged(Village *fVillage)
{
    emit tasksBuildChanged(idAccount, fVillage->idVillage);
}

void Account::tasksBuildChanged(int fVillage)
{
    emit tasksBuildChanged(idAccount, fVillage);
}

void Account::tasksBuildingDestroyChanged(Village *fVillage)
{
    emit tasksBuildingDestroyChanged(idAccount, fVillage->idVillage);
}


/*

void Account::emitVillagesRefreshed(int indexVillage)
{
    emit villageRefreshed(indexVillage);
}

void Account::emitTasksBuildChanged(int indexVillage)
{
    emit tasksBuildChanged(indexVillage);
}


void Account::emitTasksBuildingDestroyChanged()
{
    emit tasksBuildingDestroyChanged();
}
*/

//-------------------Operatory-------------------//

QDataStream &operator <<(QDataStream &fStream, Account *fAccount)
{
    fStream << fAccount->login << fAccount->password << fAccount->server;
    return fStream;
}

QDataStream &operator >>(QDataStream &fStream, Account *fAccount)
{
    fStream >> fAccount->login >> fAccount->password >> fAccount->server;
    return fStream;
}


