#include "village.h"

Village::Village(QObject *parent)
{
    this->setParent(parent);
    mainBuildingLvl = 0;

    lockBuilding = 0;
    lockResource = 0;
    lockTasksBuild = 0;
    lockTasksBuild = 0;
    isFieldOfCornBuilding = false;
    connect(&timerRefresh, SIGNAL(timeout()), SLOT(refresh()));


    //Make Building
    listBuilding.append(new Building());
    for(int i=1; i<19; i++)
    {
        Building *tBuilding = new Building();
        listResourceBuilding.append(tBuilding);
        listBuilding.append(tBuilding);
    }
    for(int i=19; i<41; i++)
    {
        Building *tBuilding = new Building();
        listInfrastructureBuilding.append(tBuilding);
        listBuilding.append(tBuilding);
    }

}

Village::~Village()
{
    clearListResourceBuilding(this);
    clearListInfrastructureBuilding(this);
    clearListUpgradingBuilding(this);

    clearTasksBuild(this);
    clearTasksBuildingDestroy(this);
}

void Village::setName(Village &fCopy)
{
    name = fCopy.name;
    newdID = fCopy.newdID;
    coordinates = fCopy.coordinates;
}

void Village::setResource(Village &fCopy)
{
    timeDrof1 = fCopy.timeDrof1;

    currentWood = fCopy.currentWood;
    currentClay = fCopy.currentClay;
    currentIron = fCopy.currentIron;
    currentCorn = fCopy.currentCorn;
    currentCorn2 = fCopy.currentCorn2;

    maxWood = fCopy.maxWood;
    maxClay = fCopy.maxClay;
    maxIron = fCopy.maxIron;
    maxCorn = fCopy.maxCorn;

    productionWood = fCopy.productionWood;
    productionClay = fCopy.productionClay;
    productionIron = fCopy.productionIron;
    productionCorn = fCopy.productionCorn;

    peerSecWood = fCopy.peerSecWood;
    peerSecClay = fCopy.peerSecClay;
    peerSecIron = fCopy.peerSecIron;
    peerSecCorn = fCopy.peerSecCorn;
}

void Village::setBuilding(Village &fCopy)
{
    timeDrof2 = fCopy.timeDrof2;

    mainBuildingLvl = fCopy.mainBuildingLvl;
    mainBuildingIdPlace = fCopy.mainBuildingIdPlace;
    isCapital = fCopy.isCapital;

    for(int i=0; i<fCopy.listBuilding.count(); i++)
        (*listBuilding.at(i)) = (*fCopy.listBuilding.at(i));

    clearListUpgradingBuilding(this);
    foreach(Building *i, listBuilding)
        if(i->isUpgrading)
            listUpgradingBuilding.append(i);

    isFieldOfCornBuilding = fCopy.isFieldOfCornBuilding;
    fieldOfCornBuildingEnd = fCopy.fieldOfCornBuildingEnd;
}

void Village::setTasksBuild(Village &fCopy)
{
    clearTasksBuild(this);
    foreach(Task *i, fCopy.tasksBuild)
    {
        Task *tTask = new Task();
        *tTask = *i;
        tasksBuild.append(tTask);
    }
}

void Village::setTasksBuildingDestroy(Village &fCopy)
{
    clearTasksBuildingDestroy(this);
    foreach(Task *i, fCopy.tasksBuildingDestroy)
    {
        Task *tTask = new Task();
        *tTask = *i;
        tasksBuildingDestroy.append(tTask);
    }
}


void Village::buildingBuild(int idPlace)
{
    emit addRequestBuildingUpgrade(this, idPlace);
}

void Village::buildingBuild(int idPlace, int idBuilding)
{
    emit addRequestBuildingUpgrade(this, idPlace, idBuilding);
}

void Village::buildingBuildAbort(QString fAbordValueD, QMovie *fMovie)
{
    emit addRequestBuildingBuildAbort(this, fAbordValueD, fMovie);
}

void Village::tasksBuildMakeAndAddTaskBuildingUpgrade(int fIdPlace, Time fBuildOn)
{
    tasksBuildCurrentIdPlace = fIdPlace;
    tasksBuildCurrentBuildOn = fBuildOn;
    QTimer::singleShot(10, this, SLOT(tasksBuildMakeAndAddTaskBuildingUpgrade()));
    waitForLock.exec();
}

void Village::tasksBuildMakeAndAddTaskBuildingBuild(int fIdPlace, int fIdBuilding, Time fBuildOn)
{
    tasksBuildCurrentIdPlace = fIdPlace;
    tasksBuildCurrentIdBuilding = fIdBuilding;
    tasksBuildCurrentBuildOn = fBuildOn;
    QTimer::singleShot(10, this, SLOT(tasksBuildMakeAndAddTaskBuildingBuild()));
    waitForLock.exec();
}

void Village::tasksBuildAddTask(Task fTask)
{

    Task *tTask = new Task();
    *tTask = fTask;

    bool inserted = false;
    for(int i=0; i<tasksBuild.count(); i++)
        if(tTask->buildOn < tasksBuild.at(i)->buildOn)
        {
            tasksBuild.insert(i, tTask);
            inserted = true;
            break;
        }

    if(!inserted)
        tasksBuild.append(tTask);

    if( (*nation) == 0)
    {
        tasksBuildRecount();

        for(int i=tasksBuild.count()-1; i>=0; i-- )
            tasksBuildRemoveTaskFromXML(i);

        foreach(Task *i, tasksBuild)
            tasksBuildAddTaskToXML(*i);

        if(listUpgradingBuilding.count() == 0 || listUpgradingBuilding.count() == 1)
            startTimerRefreshTime();


    }else
        tasksBuildAddTaskToXML(fTask);

    if(tasksBuild.count() == 1)
        startTimerRefreshTime();
}

void Village::tasksBuildRemoveTask(int index)
{
    tasksBuildCurrentRemoveTask = index;
    tasksBuildRemove();
    waitForLock.exec();

    if(index == 0)
        startTimerRefreshTime();
}

void Village::tasksBuildRecount()
{

    int tTime = timeDrof2.secondsTo(Time::currentTime());

    Time timeBuildingConstructionResources(0,0,0);
    Time timeBuildingConstructionInfrastructure(0,0,0);

    foreach(Building *i, listUpgradingBuilding)
        if( i->isResource)
        {
            if( i->timeToUpgradeEnd.addSeconds(-tTime) > timeBuildingConstructionResources )
                timeBuildingConstructionResources.setHMS(i->timeToUpgradeEnd.addSeconds(-tTime));
        }else
        {
            if( i->timeToUpgradeEnd.addSeconds(-tTime) > timeBuildingConstructionInfrastructure )
                timeBuildingConstructionInfrastructure.setHMS(i->timeToUpgradeEnd.addSeconds(-tTime));
        }

    int totalWood = 0;
    int totalClay = 0;
    int totalIron = 0;
    int totalCorn = 0;
    int totalCorn2 = 0;
    int tCurrentWood = tTime * peerSecWood + currentWood;
    int tCurrentClay = tTime * peerSecClay + currentClay;
    int tCurrentIron = tTime * peerSecIron + currentIron;
    int tCurrentCorn = tTime * peerSecCorn + currentCorn;

    for(int i=0; i<tasksBuild.count(); i++)
    {
        tasksBuild.at(i)->timeToWait.setHMS(0,0,0);

        totalWood += tasksBuild.at(i)->neededWood;
        totalClay += tasksBuild.at(i)->neededClay;
        totalIron += tasksBuild.at(i)->neededIron;
        totalCorn += tasksBuild.at(i)->neededCorn;
        totalCorn2 += tasksBuild.at(i)->neededCorn2;

        int timeToResourceEnough = 0;

        //Woood
        if( tCurrentWood < totalWood )
        {
            int tTimeToResourceEnough = (double) (totalWood - tCurrentWood) / peerSecWood;

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;
        }

        //Clay
        if( tCurrentClay < totalClay )
        {
            int tTimeToResourceEnough = (double) (totalClay - tCurrentClay) / peerSecClay;

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;
        }

        //Iron
        if( tCurrentIron < totalIron )
        {
            int tTimeToResourceEnough = (double) (totalIron - tCurrentIron) / peerSecIron;

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;
        }

        //Corn
        if( tCurrentCorn < totalCorn )
        {

            int tTimeToResourceEnough = (double) (totalCorn - tCurrentCorn) / peerSecCorn;

            if(timeToResourceEnough < tTimeToResourceEnough)
                timeToResourceEnough = tTimeToResourceEnough;
        }


        // Avaible Time
        // Resource
        if( tasksBuild.at(i)->isResource )
        {
            QList<Time> tList;
            tList.append( Time().fromSeconds(timeToResourceEnough) );
            tList.append( timeBuildingConstructionResources );
            tList.append( tasksBuild.at(i)->buildOn - Time::currentTime() );

            int index = Time::returnTheLongestTimeIndex(tList);

            if( index == -1)
            {
                if(isFieldOfCornBuilding)
                {
                    tasksBuild.at(i)->timeToWait.setHMS( fieldOfCornBuildingEnd.addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(timeDrof2)) ) );
                    timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildingTime ) + Time::toSeconds( tasksBuild.at(i)->timeToWait )));
                }

            }else if( index == 0 )
            {
                int tHours = timeToResourceEnough / 3600;
                int tMinutes = timeToResourceEnough % 3600 / 60;
                Time tTime(tHours, tMinutes, timeToResourceEnough - (tHours * 3600 + tMinutes*60));

                tasksBuild.at(i)->timeToWait.setHMS( tTime );
                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( timeToResourceEnough + Time::toSeconds( tasksBuild.at(i)->buildingTime )));

            }else if( index == 1 )
            {
                tasksBuild.at(i)->timeToWait.setHMS( timeBuildingConstructionResources );
                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildingTime )));

            }else if( index == 2 )
            {
                tasksBuild.at(i)->timeToWait.setHMS( tasksBuild.at(i)->buildOn - Time::currentTime() );
                timeBuildingConstructionResources.setHMS( timeBuildingConstructionResources.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildOn - Time::currentTime() )));
            }

        // Infrastructure
        }else
        {
            QList<Time> tList;
            tList.append( Time().fromSeconds(timeToResourceEnough) );
            tList.append( timeBuildingConstructionInfrastructure );
            tList.append( tasksBuild.at(i)->buildOn - Time::currentTime() );

            int index = Time::returnTheLongestTimeIndex(tList);


            if( index == -1)
            {
                if(isFieldOfCornBuilding)
                {
                    tasksBuild.at(i)->timeToWait.setHMS( fieldOfCornBuildingEnd.addSeconds(  -(Time::toSeconds(Time::currentTime()) - Time::toSeconds(timeDrof2)) ) );
                    timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildingTime ) + Time::toSeconds( tasksBuild.at(i)->timeToWait )));
                }

            }else if( index == 0 )
            {
                int tHours = timeToResourceEnough / 3600;
                int tMinutes = timeToResourceEnough % 3600 / 60;
                Time tTime(tHours, tMinutes, timeToResourceEnough - (tHours * 3600 + tMinutes*60));

                tasksBuild.at(i)->timeToWait.setHMS( tTime );
                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( timeToResourceEnough + Time::toSeconds( tasksBuild.at(i)->buildingTime )));

            }else if( index == 1 )
            {
                tasksBuild.at(i)->timeToWait.setHMS( timeBuildingConstructionInfrastructure );
                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildingTime )));

            }else if( index == 2 )
            {
                tasksBuild.at(i)->timeToWait.setHMS( tasksBuild.at(i)->buildOn - Time::currentTime() );
                timeBuildingConstructionInfrastructure.setHMS( timeBuildingConstructionInfrastructure.addSeconds( Time::toSeconds( tasksBuild.at(i)->buildOn - Time::currentTime() )));
            }
        }
    }

    qSort(tasksBuild.begin(), tasksBuild.end(), Task::qSort);
}

void Village::tasksBuildAddTaskToXML(Task fTask)
{

    QDomElement tElement = XMLDocument->createElement("Task");
    tElement.setAttribute("type", fTask.type);
    tElement.setAttribute("idPlace", fTask.idPlace);
    tElement.setAttribute("idBuilding", fTask.idBuilding);
    tElement.setAttribute("buildOn", fTask.buildOn.toString());
    XMLVillage.appendChild(tElement);

    tasksBuildSaveToXML();
}

void Village::tasksBuildRemoveTaskFromXML(int index)
{
    QDomNodeList tList = XMLVillage.elementsByTagName("Task");
    XMLVillage.removeChild( tList.at(index) );
    tasksBuildSaveToXML();

}

void Village::tasksBuildSaveToXML()
{
    QFile XMLFile("file");
    if(*onAndroid)
    {
        QDir tDir("/sdcard");
        tDir.mkpath("Travianator");
        XMLFile.setFileName("/sdcard/Travianator/Tasks.xml");

    }else
    {
        XMLFile.setFileName(QCoreApplication::applicationDirPath() + "/Tasks.XML");
    }

    if(XMLFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream tStream(&XMLFile);
        tStream  << (*XMLDocument);

    }else
        QMessageBox::information(0,"Error","Can't open Task.xml");

    XMLFile.flush();
    XMLFile.close();
}


void Village::buildingDestroy(int fIdPlace)
{/*
    if(tasksBuildingDestroy.count())
    {

    }else
    {
        RequestBuildingDestroy *tRequest = new RequestBuildingDestroy((QWidget*)this->parent(),
                                                                      &networkManager,
                                                                      server,

                                                                      &mainBuildingIdPlace,
                                                                      fIdPlace,
                                                                      &lastDestroy,
                                                                      &destroyLongTime);

        connect(tRequest, SIGNAL(tasksBuildingDestroyChanged()), this, SLOT(emitTasksBuildingDestroyChanged()));
        requestQueue.append(tRequest);

        if(!isRequestHendlerWorking)
            emit requestHendlerStart();

    }
*/
}



void Village::taskBuildingDestroyRemoveTask(int index)
{/*
    delete tasksBuildingDestroy.at(index);
    tasksBuildingDestroy.removeAt(index);
    emit tasksBuildingDestroyChanged();
*/
}





void Village::addRefreshRequest()
{
    emit addRequestRefreshVillage(this);
}

void Village::addTaskRequest(Task *fTask)
{

    if(fTask->type == 1)
    {
        buildingBuild(fTask->idPlace);
    }
    else if(fTask->type == 2)
    {
        buildingBuild(fTask->idPlace, fTask->idBuilding);
    }

}

void Village::startTimerRefreshTime()
{
    Time timeTask(0,1,0);
    if(tasksBuild.count())
    {
        Task *tTask = tasksBuild.at(0);

        Time tTime = whenCanBuildBilding(tTask, this);

        if(tTime < timeTask)
            timeTask = tTime;
    }

    Time timeBuilding(0,1,0);
    foreach(Building *i, listUpgradingBuilding)
    {
         if(timeBuilding > i->timeToUpgradeEnd)
            timeBuilding.setHMS(i->timeToUpgradeEnd.hours(), i->timeToUpgradeEnd.minutes(), i->timeToUpgradeEnd.seconds());
    }


    if(timeTask < Time(0,1,0) && timeBuilding < Time(0,1,0))
    {
        if(timeBuilding > timeTask)
            timerRefresh.start( Time(0,0,0).secondsTo(timeTask)*1000 );
        else
            timerRefresh.start( Time(0,0,0).secondsTo(timeBuilding)*1000 );

    }else if(timeTask < Time(0,1,0))
    {
        timerRefresh.start( Time(0,0,0).secondsTo(timeTask)*1000 );

    }else if(timeBuilding < Time(0,1,0))
    {
        timerRefresh.start( Time(0,0,0).secondsTo(timeBuilding)*1000 );

    }else
        timerRefresh.start(60000);
}

void Village::refresh()
{
    if(tasksBuild.count())
    {
        Task *tTask = tasksBuild.at(0);
        tTask->timeToWait.setHMS( whenCanBuildBilding(tTask, this) );

        if(tTask->timeToWait == Time(0,0,0))
        {
            addTaskRequest(tTask);

            delete tasksBuild.at(0);
            tasksBuild.removeFirst();
            emit tasksBuildChanged(this);

        }else
            addRefreshRequest();

    }else
    {
        addRefreshRequest();
    }

    startTimerRefreshTime();
}

void Village::tasksBuildMakeAndAddTaskBuildingBuild()
{
    if(setLockTasksBuildTo(1))
    {

        Building tBuilding(tasksBuildCurrentIdPlace, tasksBuildCurrentIdBuilding, 0, mainBuildingLvl, travianWiki);
        TaskBuildingBuild tTask( tBuilding );
        tTask.lvl++;
        tTask.buildOn = tasksBuildCurrentBuildOn;

        tasksBuildAddTask(tTask);
        releaseLockTasksBuild();
        waitForLock.quit();

    }else
        QTimer::singleShot(100, this, SLOT(tasksBuildMakeAndAddTaskBuildingUpgrade()));
}

void Village::tasksBuildMakeAndAddTaskBuildingUpgrade()
{
    if(setLockTasksBuildTo(1))
    {
        Building *tBuilding = listBuilding.at(tasksBuildCurrentIdPlace);

        if(tBuilding->isExist)
        {
            int tLvl = tBuilding->lvl+1;

            foreach( Task *i, tasksBuild )
                if(i->type == 1 || i->type == 2 )
                    if( i->idPlace == tasksBuildCurrentIdPlace )
                        tLvl++;


            if(tLvl <= tBuilding->maxLvl)
            {
                TaskBuildingUpgrade tTask(Building(tBuilding->idPlace, tBuilding->idBuilding, tLvl-1, mainBuildingLvl, travianWiki));
                tTask.lvl++;
                tTask.buildOn = tasksBuildCurrentBuildOn;

                tasksBuildAddTask(tTask);
            }
        }else
        {
            int tLvl = 1;
            int tIdBuilding;
            foreach( Task *i, tasksBuild )
                if(i->type == 1 || i->type == 2 )
                    if( i->idPlace == tasksBuildCurrentIdPlace )
                    {
                        tLvl++;
                        tIdBuilding = i->idBuilding;
                    }

            TaskBuildingUpgrade tTask(Building(tasksBuildCurrentIdPlace, tIdBuilding, tLvl-1, mainBuildingLvl, travianWiki));
            tTask.lvl++;
            tTask.buildOn = tasksBuildCurrentBuildOn;

            tasksBuildAddTask(tTask);
        }
        releaseLockTasksBuild();
        waitForLock.quit();

    }else
        QTimer::singleShot(100, this, SLOT(tasksBuildMakeAndAddTaskBuildingUpgrade()));
}



void Village::tasksBuildRemove()
{
    if(setLockTasksBuildTo(1))
    {
        if(tasksBuild.count() >= tasksBuildCurrentRemoveTask+1)
        {
            int tIdPlace = tasksBuild.at(tasksBuildCurrentRemoveTask)->idPlace;
            for(int i=tasksBuild.count()-1; i>=tasksBuildCurrentRemoveTask; i--)
            {
                if(tasksBuild.at(i)->idPlace == tIdPlace)
                {
                    delete tasksBuild.at(i);
                    tasksBuild.removeAt(i);
                    tasksBuildRemoveTaskFromXML(i);
                }
            }
            releaseLockTasksBuild();
            emit tasksBuildChanged(this);

        }else
            releaseLockTasksBuild();

        waitForLock.quit();

    }else
        QTimer::singleShot(100, this, SLOT(tasksBuildRemove()));
}

void Village::setPointers(NationType *fNation,
                          QString *fServer,
                          QString *fLogin,
                          QString *fPasswird,
                          TravianWiki *fTravianWiki,
                          bool *fIsRequestHendlerWorking,
                          QList<BuildingSocket*>  *fSocketList,
                          QDomDocument *fXMLDocument,
                          QDomElement *fXMLAccount,
                          bool *fOnAndroid)
{
    nation = fNation;
    server = fServer;
    login = fLogin;
    password = fPasswird;
    travianWiki = fTravianWiki;
    isRequestHendlerWorking = fIsRequestHendlerWorking;
    socketList = fSocketList;

    XMLDocument = fXMLDocument;
    XMLAccount = fXMLAccount;
    onAndroid = fOnAndroid;

    XMLVillage = XMLDocument->createElement("Village");
    XMLVillage.setAttribute("Name",name);
    XMLAccount->appendChild(XMLVillage);


}


Time Village::whenCanBuildBilding(Building *fBuilding, Village *fVillage)
{
    QList<Time> tTimes;
    tTimes.append( whenResourceToBuildBilding(fBuilding, fVillage) );
    tTimes.append( whenBuildingSocketWillByFree(fBuilding, fVillage) );

    return Time::returnTheLongestTime(tTimes);
}

Time Village::whenCanBuildBilding(Task *fTask, Village *fVillage)
{
    QList<Time> tTimes;
    tTimes.append( whenResourceToBuildBilding(fTask, fVillage) );
    tTimes.append( whenBuildingSocketWillByFree(fTask, fVillage) );
    tTimes.append( fTask->buildOn - Time::currentTime() );

    return Time::returnTheLongestTime(tTimes);
}

Time Village::whenResourceToBuildBilding(Building *fBuilding, Village *fVillage)
{
    int timeToUpgrade = 0;
    int tTime = fVillage->timeDrof1.secondsTo(Time::currentTime());
    int tCurrentWood = tTime * fVillage->peerSecWood + fVillage->currentWood;
    int tCurrentClay = tTime * fVillage->peerSecClay + fVillage->currentClay;
    int tCurrentIron = tTime * fVillage->peerSecIron + fVillage->currentIron;
    int tCurrentCorn = tTime * fVillage->peerSecCorn + fVillage->currentCorn;

    if( tCurrentWood < fBuilding->woodToUpgrade )
    {
        int tTimeToUpgrade = (double) (fBuilding->woodToUpgrade - tCurrentWood) / fVillage->peerSecWood;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentClay < fBuilding->clayToUpgrade )
    {
        int tTimeToUpgrade = (double) (fBuilding->clayToUpgrade - tCurrentClay) / fVillage->peerSecClay;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentIron < fBuilding->ironToUpgrade)
    {
        int tTimeToUpgrade = (double) (fBuilding->ironToUpgrade - tCurrentIron) / fVillage->peerSecIron;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentCorn < fBuilding->cornToUpgrade )
    {
        int tTimeToUpgrade = (double) (fBuilding->cornToUpgrade - tCurrentCorn) / fVillage->peerSecCorn;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( fVillage->currentCorn2 < fBuilding->corn2ToUpgrade )
    {
        int tTimeToUpgrade = 60;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }

    if(timeToUpgrade == 0)
        return Time(0,0,0);

    int tHours = timeToUpgrade / 3600;
    int tMinuts = (timeToUpgrade - (tHours * 3600)) /60;
    Time returnValue = Time(tHours, tMinuts, timeToUpgrade - ((tHours * 3600) + (tMinuts * 60)));
    return returnValue;

}

Time Village::whenResourceToBuildBilding(Task *fTask, Village *fVillage)
{

    int timeToUpgrade = 0;
    int tTime = fVillage->timeDrof1.secondsTo(Time::currentTime());
    int tCurrentWood = tTime * fVillage->peerSecWood + fVillage->currentWood;
    int tCurrentClay = tTime * fVillage->peerSecClay + fVillage->currentClay;
    int tCurrentIron = tTime * fVillage->peerSecIron + fVillage->currentIron;
    int tCurrentCorn = tTime * fVillage->peerSecCorn + fVillage->currentCorn;

    if( tCurrentWood < fTask->neededWood )
    {
        int tTimeToUpgrade = (double) (fTask->neededWood - tCurrentWood) / fVillage->peerSecWood;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentClay < fTask->neededClay )
    {
        int tTimeToUpgrade = (double) (fTask->neededClay - tCurrentClay) / fVillage->peerSecClay;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentIron < fTask->neededIron)
    {
        int tTimeToUpgrade = (double) (fTask->neededIron - tCurrentIron) / fVillage->peerSecIron;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( tCurrentCorn < fTask->neededCorn )
    {
        int tTimeToUpgrade = (double) (fTask->neededCorn - tCurrentCorn) / fVillage->peerSecCorn;
        if(timeToUpgrade < tTimeToUpgrade)
            timeToUpgrade = tTimeToUpgrade;
    }
    if( fVillage->currentCorn2 < fTask->neededCorn2 )
    {
        int tTimeToUpgrade;

        if(fTask->idBuilding != 4)
        {
            if(fVillage->isFieldOfCornBuilding)
                tTimeToUpgrade = Time::toSeconds( fVillage->fieldOfCornBuildingEnd.addSeconds( -(fVillage->timeDrof2.secondsTo( Time::currentTime() )) ));
            else
                tTimeToUpgrade = 60;

            if(timeToUpgrade < tTimeToUpgrade)
                timeToUpgrade = tTimeToUpgrade;
        }
    }

    if(timeToUpgrade == 0)
        return Time(0,0,0);

    int tHours = timeToUpgrade / 3600;
    int tMinuts = (timeToUpgrade - (tHours * 3600)) /60;
    Time returnValue = Time(tHours, tMinuts, timeToUpgrade - ((tHours * 3600) + (tMinuts * 60)));
    return returnValue;
}

Time Village::whenBuildingSocketWillByFree(Building *fBuilding, Village *fVillage)
{
    int tTime = fVillage->timeDrof1.secondsTo(Time::currentTime());


    switch(fVillage->listUpgradingBuilding.count())
    {
        case 0:
            {
                return Time(0,0,0);
            }
            break;
        case 1:
            {
                 if(*(fVillage->nation) == Rzymianie)
                     if(fVillage->listUpgradingBuilding.at(0)->isResource != fBuilding->isResource)
                         return Time(0,0,0);

                 return fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd.addSeconds(-tTime);

            }
            break;
        case 2:
            {
                if(*(fVillage->nation) == Rzymianie)
                {
                    if(fVillage->listUpgradingBuilding.at(0)->isResource == fVillage->listUpgradingBuilding.at(1)->isResource)
                        return Time(0,0,0);

                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fBuilding->isResource)
                            return i->timeToUpgradeEnd.addSeconds(-tTime);
                }

                if(fVillage->listUpgradingBuilding.at(0)->isResource != fVillage->listUpgradingBuilding.at(1)->isResource)
                {
                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fBuilding->isResource)
                            return i->timeToUpgradeEnd.addSeconds(-tTime);
                }else
                {
                    if(fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd >=  fVillage->listUpgradingBuilding.at(1)->timeToUpgradeEnd)
                        return fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd.addSeconds(-tTime);
                    else
                        return fVillage->listUpgradingBuilding.at(1)->timeToUpgradeEnd.addSeconds(-tTime);
                }

            }
            break;
        default :
            {
                    Time returnValue(0,0,0);
                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fBuilding->isResource)
                            if(i->timeToUpgradeEnd > returnValue)
                                returnValue = i->timeToUpgradeEnd;
                    return returnValue.addSeconds(-tTime);
            }
            break;
    }
}

Time Village::whenBuildingSocketWillByFree(Task *fTask, Village *fVillage)
{
    int tTime = fVillage->timeDrof1.secondsTo(Time::currentTime());

    switch(fVillage->listUpgradingBuilding.count())
    {
        case 0:
            {
                return Time(0,0,0);
            }
            break;
        case 1:
            {
                 if(*(fVillage->nation) == Rzymianie)
                     if(fVillage->listUpgradingBuilding.at(0)->isResource != fTask->isResource)
                         return Time(0,0,0);

                 return fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd.addSeconds(-tTime);

            }
            break;
        case 2:
            {
                if(*(fVillage->nation) == Rzymianie)
                {
                    if(fVillage->listUpgradingBuilding.at(0)->isResource == fVillage->listUpgradingBuilding.at(1)->isResource)
                        return Time(0,0,0);

                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fTask->isResource)
                            return i->timeToUpgradeEnd.addSeconds(-tTime);
                }

                if(fVillage->listUpgradingBuilding.at(0)->isResource != fVillage->listUpgradingBuilding.at(1)->isResource)
                {
                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fTask->isResource)
                            return i->timeToUpgradeEnd.addSeconds(-tTime);
                }else
                {
                    if(fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd >=  fVillage->listUpgradingBuilding.at(1)->timeToUpgradeEnd)
                        return fVillage->listUpgradingBuilding.at(0)->timeToUpgradeEnd.addSeconds(-tTime);
                    else
                        return fVillage->listUpgradingBuilding.at(1)->timeToUpgradeEnd.addSeconds(-tTime);
                }

            }
            break;
        default :
            {
                    Time returnValue(0,0,0);
                    foreach(Building *i, fVillage->listUpgradingBuilding)
                        if(i->isResource == fTask->isResource)
                            if(i->timeToUpgradeEnd > returnValue)
                                returnValue = i->timeToUpgradeEnd;
                    return returnValue.addSeconds(-tTime);
            }
            break;
    }
}

void Village::clearListResourceBuilding(Village *tVillage)
{
    foreach(Building *i, tVillage->listResourceBuilding)
        delete i;
    tVillage->listResourceBuilding.clear();
}

void Village::clearListInfrastructureBuilding(Village *tVillage)
{
    foreach(Building *i, tVillage->listInfrastructureBuilding)
        delete i;
    tVillage->listInfrastructureBuilding.clear();
}

void Village::clearListUpgradingBuilding(Village *tVillage)
{
    tVillage->listUpgradingBuilding.clear();
}

void Village::clearTasksBuild(Village *tVillage)
{
    foreach(Task *i, tVillage->tasksBuild)
        delete i;
    tVillage->tasksBuild.clear();
}

void Village::clearTasksBuildingDestroy(Village *tVillage)
{
    foreach(Task *i, tVillage->tasksBuildingDestroy)
        delete i;
    tVillage->tasksBuildingDestroy.clear();
}


/*
void Village::emitVillageRefreshed()
{
    emit villageRefreshed(idVillage);
    startTimerRefreshTime();
}

void Village::emitTasksBuildChanged()
{
    emit tasksBuildChanged(idVillage);
    startTimerRefreshTime();
}

void Village::emitTasksBuildingDestroyChanged()
{
}
*/
