#ifndef TRAVIANREQUEST_H
#define TRAVIANREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QEventLoop>
#include <QThread>

#include "Enums.h"
#include "building.h"
#include "buildingmapitem.h"
#include "task.h"
#include "travianwiki.h"
#include "buildingsocket.h"
#include "village.h"
#include "servertype.h"


//----------------------------------------------------------------------------------------------------------//
//  TravianRequest
//----------------------------------------------------------------------------------------------------------//

class TravianRequest : public QObject
{
    Q_OBJECT
public:
    TravianRequest();

    NationType  checkNationType(QString tType);
    bool        isLoginCheack();
    bool        findNation();
    bool        findVillages();

    QString     findTimeToEndUpgrading(QString *fAbordValueD, QString fName, int fLvl);
    Building    createBuilding(QString tType, int fIdPlace, int fLvl);

    bool        findValueLoginIndex();
    bool        findValueCUpgrading(QString *ValueC);
    bool        findValueCBuilding(QString *ValueC);
    bool        findValueCAbort(QString *ValueC, QString fAbortValueD);
    bool        findValuesDestroy(QString *ValueGID, QString *ValueA, QString *ValueC);
    bool        findTimeToEndDestroy(QString *fTime);

    bool        resourcesNeededToUpgrade(Building *fBuilding);

    void    connectReplay();
    void    disconnectReplay();

    void    loginAgain();
    int     refresh();
    int     refreshWithOutDrof2();

    int     getDorf1();
    void    searchTheDorf1();
    int     getDorf2();
    void    searchTheDorf2();

    int     sendGetReques(QNetworkRequest fRequest);
    int     sendPostReques(QNetworkRequest fRequest,QByteArray fPostDate);
    void    replyWriteTo();

    virtual int execute()=0;

    //---------------------------------------------------//
    int             type;
    QString         typeName;
    QWidget         *parent;

    QString         login;
    QString         password;
    QString         server;
    int             loginIndex;
    QUrl            postData;


    Village                 *village;
    QList<VillageTemp>      *villagesTemp;
    ServerType              *serverType;
    bool                    haveResidence;
    bool                    havePalace;

    bool                    findError;
    bool                    connectionError;
    QEventLoop              waitForLocker;


    bool            *isLogin;
    NationType      *nation;
    TravianWiki     *travianWiki;

    QString         pageContent;

    QNetworkAccessManager   *networkManager;
    QEventLoop              waitForReply;
    QNetworkReply           *reply;

    int     idPlace;
    int     idBuilding;
    QString abortValueD;
    QList<BuildingSocket*> *socketList;
    QMovie *movie;


signals:
    void loginFinished();

    void requestRefreshVillageFinished(Village *fVillage);

    void tasksBuildChanged(Village *fVillage);
    void tasksBuildingDestroyChanged(Village *fVillage);

public slots:
    void        findResources();
    void        findResourcesProduction();

    void        findResourceBuilding();
    void        findInfraktrusturBuilding();
};




//----------------------------------------------------------------------------------------------------------//
//  RequestLogin
//----------------------------------------------------------------------------------------------------------//
class RequestLogin : public TravianRequest
{
    Q_OBJECT
public:
    RequestLogin(QWidget *fParent,
                 QNetworkAccessManager *fNetworkManager,
                 QString fServer,
                 QString fLogin,
                 QString fPassword,
                 NationType *fNation,
                 bool *fIsLogin,
                 QList<VillageTemp> *fVillagesTemp,
                 ServerType         *fServerType);

    int execute();

public slots:

};


//----------------------------------------------------------------------------------------------------------//
//  RequestRefresh
//----------------------------------------------------------------------------------------------------------//

class RequestRefresh : public TravianRequest
{
    Q_OBJECT
public:

    RequestRefresh( QWidget *fParent,
                    QNetworkAccessManager *fNetworkManager,
                    QString fServer,
                    QString fLogin,
                    QString fPassword,
                    TravianWiki *fTravianWiki,
                    Village *fVillage,
                    ServerType *fServerType);


    int execute();
};

//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingUpgrade
//----------------------------------------------------------------------------------------------------------//

class RequestBuildingUpgrade : public TravianRequest
{
    Q_OBJECT
public:
    RequestBuildingUpgrade(QWidget *fParent,
                           QNetworkAccessManager *fNetworkManager,
                           QString fServer,
                           QString fLogin,
                           QString fPassword,
                           TravianWiki *fTravianWiki,
                           Village *fVillage,
                           ServerType *fServerType,

                           int fIdPlace,
                           QList<BuildingSocket*> *fSocketList);

    int execute();
};

//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingBild
//----------------------------------------------------------------------------------------------------------//

class RequestBuildingBuild : public TravianRequest
{
    Q_OBJECT
public:
    RequestBuildingBuild(QWidget *fParent,
                         QNetworkAccessManager *fNetworkManager,
                         QString fServer,
                         QString fLogin,
                         QString fPassword,
                         TravianWiki *fTravianWiki,
                         Village *fVillage,
                         ServerType *fServerType,

                         int fIdPlace,
                         QList<BuildingSocket*> *fSocketList,
                         int fIdBuilding);

    int execute();
};

//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingBildAbord
//----------------------------------------------------------------------------------------------------------//

class RequestBuildingBuildAbord : public TravianRequest
{
    Q_OBJECT
public:
    RequestBuildingBuildAbord(QWidget *fParent,
                              QNetworkAccessManager *fNetworkManager,
                              QString fServer,
                              QString fLogin,
                              QString fPassword,
                              TravianWiki *fTravianWiki,
                              Village *fVillage,
                              ServerType *fServerType,

                              QString fAbortValueD,
                              QMovie *fMovie);

    int execute();
};
/*
//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingDestroy
//----------------------------------------------------------------------------------------------------------//

class RequestBuildingDestroy : public TravianRequest
{
    Q_OBJECT
public:
    RequestBuildingDestroy(QWidget *fParent,
                           QNetworkAccessManager *fNetworkManager,
                           QString fServer,

                           int *fMainBuildingIdPlace,
                           int fIdPlace,
                           Time *fLastDestroy,
                           Time *fDestroyLongTime);

    void execute();
};
*/
#endif // TRAVIANREQUEST_H
