#ifndef VILLAGE_H
#define VILLAGE_H

#include <QObject>

#include <QtCore>
#include <QtXml>

#include "time.h"
#include "building.h"
#include "task.h"
#include "travianwiki.h"
#include "buildingsocket.h"

class Village : public QObject
{
    Q_OBJECT
public:
    Village(QObject *parent);
    ~Village();

    void setName(Village &fCopy);
    void setResource(Village &fCopy);
    void setBuilding(Village &fCopy);
    void setTasksBuild(Village &fCopy);
    void setTasksBuildingDestroy(Village &fCopy);

    QString name;
    int newdID;
    QPoint coordinates;
    int idVillage;
    bool isActive;

    QEventLoop waitForLock;

    Time lastDestroy;
    Time destroyLongTime;

    QTimer timerRefresh;

    //---------Resource---------//
    int currentWood;
    int currentClay;
    int currentIron;
    int currentCorn;
    int currentCorn2;

    int maxWood;
    int maxClay;
    int maxIron;
    int maxCorn;

    int productionWood;
    int productionClay;
    int productionIron;
    int productionCorn;

    double peerSecWood;
    double peerSecClay;
    double peerSecIron;
    double peerSecCorn;

    Time timeDrof1;

    int lockResource;
    bool setLockResourceTo(int fIdLock){

        if(lockResource == 0 )
        {
            lockResource = fIdLock;
            return true;
        }else
            return false;
    }
    void releaseLockResource(){
        lockResource = 0 ;
    }

    //---------Building---------//    
    int mainBuildingLvl;
    int mainBuildingIdPlace;
    bool isCapital;

    bool isFieldOfCornBuilding;
    Time fieldOfCornBuildingEnd;

    Time timeDrof2;

    QList<Building*> listBuilding;
    QList<Building*> listResourceBuilding;
    QList<Building*> listInfrastructureBuilding;
    QList<Building*> listUpgradingBuilding;
    int lockBuilding;
    bool setLockBuildingTo(int fIdLock){

        if(lockBuilding == 0 )
        {
            lockBuilding = fIdLock;
            return true;
        }else
            return false;
    }
    void releaseLockBuilding(){
        lockBuilding = 0 ;
    }


    void buildingBuild(int idPlace);
    void buildingBuild(int idPlace, int idBuilding);
    void buildingBuildAbort(QString fAbordValueD, QMovie *fMovie);


    //---------TasksBuild---------//
    QList<Task*>     tasksBuild;
    int  tasksBuildCurrentRemoveTask;
    int  tasksBuildCurrentIdPlace;
    int  tasksBuildCurrentIdBuilding;
    Time tasksBuildCurrentBuildOn;
    int lockTasksBuild;
    bool setLockTasksBuildTo(int fIdLock){

        if(lockTasksBuild == 0 )
        {
            lockTasksBuild = fIdLock;
            return true;
        }else
            return false;
    }
    void releaseLockTasksBuild(){
        lockTasksBuild = 0 ;
    }

    void tasksBuildMakeAndAddTaskBuildingUpgrade(int fIdPlace, Time fBuildOn);
    void tasksBuildMakeAndAddTaskBuildingBuild(int fIdPlace, int fIdBuilding, Time fBuildOn);
    void tasksBuildAddTask(Task fTask);
    void tasksBuildRemoveTask(int index);
    void tasksBuildRecount();
    void tasksBuildAddTaskToXML(Task fTask);
    void tasksBuildRemoveTaskFromXML(int index);
    void tasksBuildSaveToXML();


    //---------BuildingDestroy---------//
    QList<Task*>     tasksBuildingDestroy;
    void buildingDestroy(int fIdPlace);
    void taskBuildingDestroyRemoveTask(int index);

    
    void addRefreshRequest();
    void addTaskRequest(Task *fTask);

    void startTimerRefreshTime();


    NationType              *nation;
    QString                 *server;
    QString                 *login;
    QString                 *password;
    TravianWiki             *travianWiki;
    bool                    *isRequestHendlerWorking;
    QList<BuildingSocket*>  *socketList;

    bool            *onAndroid;
    QDomDocument    *XMLDocument;
    QDomElement     *XMLAccount;
    QDomElement     XMLVillage;

    void setPointers(NationType             *fNation,
                     QString                *fServer,
                     QString                *fLogin,
                     QString                *fPassword,
                     TravianWiki            *fTravianWiki,
                     bool                   *fIsRequestHendlerWorking,
                     QList<BuildingSocket*>  *fSocketList,
                     QDomDocument *fXMLDocument,
                     QDomElement *fXMLAccount,
                     bool *fOnAndroid);



    Time static whenCanBuildBilding(Building *fBuilding, Village *fVillage);
    Time static whenCanBuildBilding(Task *fTask, Village *fVillage);
    Time static whenResourceToBuildBilding(Building *fBuilding, Village *fVillage);
    Time static whenResourceToBuildBilding(Task *fTask, Village *fVillage);
    Time static whenBuildingSocketWillByFree(Building *fBuilding, Village *fVillage);
    Time static whenBuildingSocketWillByFree(Task *fTask, Village *fVillage);

    void static clearListResourceBuilding(Village *tVillage);
    void static clearListInfrastructureBuilding(Village *tVillage);
    void static clearListUpgradingBuilding(Village *tVillage);

    void static clearTasksBuild(Village *tVillage);
    void static clearTasksBuildingDestroy(Village *tVillage);

signals:
    void addRequestRefreshVillage(Village *fVillage);
    void addRequestBuildingUpgrade(Village *fVillage, int fIdPlace);
    void addRequestBuildingUpgrade(Village *fVillage, int fIdPlace, int idBuilding);
    void addRequestBuildingBuildAbort(Village *fVillage, QString fAbordValueD, QMovie *fMovie);

    void requestHendlerStart();

    void tasksBuildChanged(Village *fVillage);
    void tasksBuildingDestroyChanged(Village *fVillage);

public slots:
    void refresh();

    void tasksBuildMakeAndAddTaskBuildingBuild();
    void tasksBuildMakeAndAddTaskBuildingUpgrade();
    void tasksBuildRemove();
};

#endif // VILLAGE_H
