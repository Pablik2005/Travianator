#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QDataStream>
#include <QtXml>

#include "Enums.h"
#include "building.h"
#include "task.h"
#include "buildingmapitem.h"
#include "travianrequest.h"
#include "travianwiki.h"
#include "village.h"

#include "servertype.h"


class Account: public QThread
{
    Q_OBJECT
public:
    Account(QWidget *parent, TravianWiki* fTravianWiki);
    ~Account();

    int             idAccount;

    QString         server;
    ServerType      *serverType;

    QString         login;
    QString         password;

    bool            *onAndroid;
    QDomDocument    *XMLDocument;
    QDomElement     *XMLAccounts;
    QDomElement     XMLAccount;

    bool            isLogin;
    int             dataLock;

    NationType      nation;
    QList<Village*> villages;
    QList<VillageTemp> villagesTemp;

    QEventLoop waitForFinishExecute;
    TravianRequest *currentRequest;
    int requestSendAttempts;
    int requestSendCount;
    bool isRequestHendlerWorking;
    QList<TravianRequest*> requestQueue;
    QNetworkAccessManager networkManager;
    TravianWiki     *travianWiki;
    QList<BuildingSocket*> *socketList;

    void Login();
    void Logout();

signals:
    void setStatusOn(bool fBool);

    void requestHendlerStart();
    void loginFinished(QList<VillageTemp> fVillagesTemp);
    void villageRefreshed(int idAccount, int idVillage);

    void tasksBuildChanged(int idAccount, int idVillage);
    void tasksBuildingDestroyChanged(int idAccount, int idVillage);


public slots:
    void requestHendler();
    void requestExecute();
    void requestExecuteFinished();

    void loginFinished();

    void addRequestRefreshVillage(Village *fVillage);
    void addRequestBuildingUpgrade(Village *fVillage, int fIdPlace);
    void addRequestBuildingUpgrade(Village *fVillage, int fIdPlace, int fIdBuilding);
    void addRequestBuildingBuildAbort(Village *fVillage, QString fAbordValueD, QMovie *fMovie);


    void requestRefreshVillageFinished(Village *fVillage);

    void tasksBuildChanged(Village *fVillage);
    void tasksBuildChanged(int fVillage);
    void tasksBuildingDestroyChanged(Village *fVillage);

    
};

QDataStream &operator<<(QDataStream &fStream, Account *fAccount);
QDataStream &operator>>(QDataStream &fStream, Account *fAccount);


#endif // ACCOUNT_H
