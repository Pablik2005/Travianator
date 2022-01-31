#include "travianrequest.h"

//----------------------------------------------------------------------------------------------------------//
//  TravianRequest
//----------------------------------------------------------------------------------------------------------//
TravianRequest::TravianRequest()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    type = 0 ;
    connectionError = false;
    havePalace = false;
    haveResidence = false;

}
NationType TravianRequest::checkNationType(QString tType)
{
    if(tType == serverType->Rzymianie )
        return Rzymianie;
    else if(tType == serverType->Galowie )
        return Galowie;
    else if(tType == serverType->Germanie )
        return Germanie;

}

bool TravianRequest::isLoginCheack()
{
    int tFrom = 0;

    tFrom = pageContent.indexOf("<form name=\"login");

    if(tFrom == -1)
        return true;
    else
        return false;
}

bool TravianRequest::findNation()
{
    int tFrom;
    int tEnd;

    tFrom = pageContent.indexOf("<img class=\"nationBig nationBig");
    if(tFrom == -1)
        return false;
    tFrom += 41;
    tEnd = pageContent.indexOf('"', tFrom);
    QString tNation = pageContent.mid(tFrom, tEnd - tFrom );

    *nation = checkNationType(tNation);

    return true;
}



bool TravianRequest::findVillages()
{
    int tFrom =0;
    int tEnd =0;

    villagesTemp->clear();

    tFrom= pageContent.indexOf("<a href=\"?newdid=", tFrom);
    while(tFrom != -1)
    {
        VillageTemp tVillage;

        tFrom += 17;
        tEnd = pageContent.indexOf('"', tFrom);
        tVillage.newdID = pageContent.mid(tFrom, tEnd - tFrom ).toInt();

        tFrom= pageContent.indexOf("title=\"&lt;span class=&quot;coordinates coordinatesWithText&quot;&gt;&lt;span class=&quot;coordText&quot;&gt;", tFrom);
        tFrom += 109;
        tEnd = pageContent.indexOf('&', tFrom);
        tVillage.name = pageContent.mid(tFrom, tEnd - tFrom );

        tFrom= pageContent.indexOf("&lt;/span&gt;&lt;span class=&quot;coordinatesWrapper&quot;&gt;&lt;span class=&quot;coordinateX&quot;&gt;(", tFrom);
        tFrom += 105;
        tEnd = pageContent.indexOf('&', tFrom);
        tVillage.coordinates.setX(pageContent.mid(tFrom, tEnd - tFrom ).toInt());

        tFrom= pageContent.indexOf("&lt;/span&gt;&lt;span class=&quot;coordinatePipe&quot;&gt;|&lt;/span&gt;&lt;span class=&quot;coordinateY&quot;&gt;", tFrom);
        tFrom += 114;
        tEnd = pageContent.indexOf(')', tFrom);
        tVillage.coordinates.setY(pageContent.mid(tFrom, tEnd - tFrom ).toInt());

        villagesTemp->append(tVillage);

        tFrom= pageContent.indexOf("<a href=\"?newdid=", tFrom);
    }


    if(villagesTemp->count())
        return true;
    else
        return false;
}

void TravianRequest::findResources()
{
    if(village->setLockResourceTo(2))
    {
        findError = false;

        int tFrom;
        int tEnd;

        //Wood
        tFrom= pageContent.indexOf("<span id=\"l1\" class=\"value \">");
        if(tFrom == -1)
            findError = true;
        tFrom += 29;
        tEnd = pageContent.indexOf("<", tFrom);

        QString tWood = pageContent.mid(tFrom, tEnd - tFrom );
        QStringList tListWood = tWood.split('/');
        village->currentWood = tListWood.at(0).toInt();
        village->maxWood = tListWood.at(1).toInt();

        //Clay
        tFrom= pageContent.indexOf("<span id=\"l2\" class=\"value \">", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 29;
        tEnd = pageContent.indexOf("<", tFrom);

        QString tClay = pageContent.mid(tFrom, tEnd - tFrom );
        QStringList tListClay = tClay.split('/');
        village->currentClay = tListClay.at(0).toInt();
        village->maxClay = tListClay.at(1).toInt();

        //Iron
        tFrom= pageContent.indexOf("<span id=\"l3\" class=\"value \">", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 29;
        tEnd = pageContent.indexOf("<", tFrom);

        QString tIron = pageContent.mid(tFrom, tEnd - tFrom );
        QStringList tListIron = tIron.split('/');
        village->currentIron = tListIron.at(0).toInt();
        village->maxIron = tListIron.at(1).toInt();

        //Corn
        tFrom = pageContent.indexOf("<span id=\"l4\" class=\"value \">", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 29;
        tEnd = pageContent.indexOf("<", tFrom);

        QString tCorn = pageContent.mid(tFrom, tEnd - tFrom );
        QStringList tListCorn = tCorn.split('/');
        village->currentCorn = tListCorn.at(0).toInt();
        village->maxCorn = tListCorn.at(1).toInt();


        // Corn2
        tFrom= pageContent.indexOf("<span id=\"l5\" class=\"value \">", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 29;
        tEnd = pageContent.indexOf("<", tFrom);

        QString tCorn2 = pageContent.mid(tFrom, tEnd - tFrom );
        village->currentCorn2 = tCorn2.toInt();

        village->releaseLockResource();
        waitForLocker.quit();


    }else
        QTimer::singleShot(50, this, SLOT(findResources()));
}

void TravianRequest::findResourcesProduction()
{
    if(village->setLockResourceTo(2))
    {
        findError = false;

        int tFrom;
        int tEnd;

        //Wood
        tFrom = pageContent.indexOf("<li class=\"r1\" title=");
        if(tFrom == -1)
            findError = true;
        tFrom += 25 + serverType->Wood.length();
        tEnd = pageContent.indexOf("\">", tFrom);
        QString tWood = pageContent.mid(tFrom, tEnd - tFrom );
        village->productionWood = tWood.toInt();

        //Clay
        tFrom = pageContent.indexOf("<li class=\"r2\" title=", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 25 + serverType->Clay.length();
        tEnd = pageContent.indexOf("\">", tFrom);
        QString tClay = pageContent.mid(tFrom, tEnd - tFrom );
        village->productionClay = tClay.toInt();

        //Iron
        tFrom = pageContent.indexOf("<li class=\"r3\" title=", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 25 + serverType->Iron.length();
        tEnd = pageContent.indexOf("\">", tFrom);
        QString tIron = pageContent.mid(tFrom, tEnd - tFrom );
        village->productionIron = tIron.toInt();

        //Corn
        tFrom = pageContent.indexOf("<li class=\"r4\" title=", tEnd);
        if(tFrom == -1)
            findError = true;
        tFrom += 25 + serverType->Corn.length();
        tEnd = pageContent.indexOf("\">", tFrom);
        QString tCorn = pageContent.mid(tFrom, tEnd - tFrom );
        village->productionCorn = tCorn.toInt();

        village->peerSecWood = (double) village->productionWood / 3600;
        village->peerSecClay = (double) village->productionClay / 3600;
        village->peerSecIron = (double) village->productionIron / 3600;
        village->peerSecCorn = (double) village->productionCorn / 3600;

        village->releaseLockResource();
        waitForLocker.quit();

    }else
        QTimer::singleShot(50, this, SLOT(findResourcesProduction()));
}

void TravianRequest::findResourceBuilding()
{
    if(village->setLockBuildingTo(2))
    {
        findError = false;

        int tFrom=0;
        int tEnd;
        QString tTemplate = "build.php?id=%1";

        for(int i=1; i<19; i++)
        {
            Building tBuilding;

            //QMessageBox::information(0,"", "index");
            //Index
            tFrom = pageContent.indexOf(tTemplate.arg(i),tFrom);
            if(tFrom == -1)
                findError = true;

            //QMessageBox::information(0,"", "typ");
            //Type
            tFrom = pageContent.indexOf("title", tFrom);
            if(tFrom == -1)
                findError = true;
            tFrom +=7;
            tEnd = pageContent.indexOf('&', tFrom);
            QString tType = pageContent.mid(tFrom, tEnd - tFrom -1);

            //QMessageBox::information(0,"", "lvl");
            //Lvl
            tFrom = pageContent.indexOf(serverType->FindBuildingLevel, tFrom);
            if(tFrom == -1)
                findError = true;
            tFrom += serverType->FindBuildingLevel.length();
            tEnd = pageContent.indexOf('&', tFrom);
            int tLvl = pageContent.mid(tFrom, tEnd - tFrom).toInt();
            //QMessageBox::information(0,"", pageContent.mid(tFrom) );

            tBuilding = createBuilding( tType, i, tLvl);
            tBuilding.isResource = true;

            //QMessageBox::information(0,"", "isUpgrade");
            //IsUpgrading
            if("&lt;/span&gt;||&lt;span class=&quot;notice&quot;&gt;" == pageContent.mid(tEnd, 52))
            {
                tBuilding.isUpgrading = true;
                QStringList tTimeList = findTimeToEndUpgrading(&(tBuilding.abortValueD), serverType->Buildings.at( tBuilding.idBuilding ), ++tBuilding.lvl).split(':');
                tBuilding.timeToUpgradeEnd = Time(tTimeList.at(0).toInt(), tTimeList.at(1).toInt(), tTimeList.at(2).toInt());
            }

            if(pageContent.mid(tEnd, 70).indexOf(serverType->FindBuildingFullUpgraded) == -1 && pageContent.mid(tEnd+52, 100).indexOf(serverType->FindBuildingIsFullUpgrading) == -1)
            {

                //QMessageBox::information(0,"", "wood");
                //WoodToUpdate
                tFrom = pageContent.indexOf("&lt;img class=&quot;r1&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                if(tFrom == -1)
                   findError = true;
                tFrom += 60;
                tEnd = pageContent.indexOf('&', tFrom);
                tBuilding.woodToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                //QMessageBox::information(0,"", "clay");
                //ClayToUpdate
                tFrom = pageContent.indexOf("&lt;img class=&quot;r2&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                if(tFrom == -1)
                    findError = true;
                tFrom += 60;
                tEnd = pageContent.indexOf('&', tFrom);
                tBuilding.clayToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                //QMessageBox::information(0,"", "iron");
                //IronToUpdate
                tFrom = pageContent.indexOf("&lt;img class=&quot;r3&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                if(tFrom == -1)
                    findError = true;
                tFrom += 60;
                tEnd = pageContent.indexOf('&', tFrom);
                tBuilding.ironToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                //QMessageBox::information(0,"", "corn");
                //CornToUpdate
                tFrom = pageContent.indexOf("&lt;img class=&quot;r4&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                if(tFrom == -1)
                    findError = true;
                tFrom += 60;
                tEnd = pageContent.indexOf('&', tFrom);
                tBuilding.cornToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();
            }

            (*village->listBuilding.at(i))= tBuilding;

            //QMessageBox::information(0,"", QString::number(i) +" : "+ tBuilding.name +" : "+ QString::number(tBuilding.lvl) +" : "+QString::number(tBuilding.isUpgrading) +'\n'+ QString::number(tBuilding.woodToUpgrade) +QString::number(tBuilding.clayToUpgrade) +QString::number(tBuilding.ironToUpgrade) +QString::number(tBuilding.cornToUpgrade)  );
        }


        if(!village->isCapital)
            foreach(Building *i, village->listResourceBuilding)
                i->maxLvl = 10;

        village->isFieldOfCornBuilding = false;
        foreach(Building *i, village->listResourceBuilding)
        {
            if(i->lvl != i->maxLvl)
                i->setUpgradeLongTime(travianWiki,village->mainBuildingLvl);

            if(i->isUpgrading)
            {
                village->listUpgradingBuilding.append(i);
                if(i->idBuilding == 4)
                    if( village->isFieldOfCornBuilding )
                    {
                        if( village->fieldOfCornBuildingEnd > i->timeToUpgradeEnd )
                            village->fieldOfCornBuildingEnd = i->timeToUpgradeEnd;
                    }else
                    {
                        village->isFieldOfCornBuilding = true;
                        village->fieldOfCornBuildingEnd = i->timeToUpgradeEnd;
                    }

            }
        }

        village->releaseLockBuilding();
        waitForLocker.quit();

    }else
        QTimer::singleShot(50, this, SLOT(findResourceBuilding()));
}

void TravianRequest::findInfraktrusturBuilding()
{
    if(village->setLockBuildingTo(2))
    {
        findError = false;

        int tFrom=0;
        int tEnd;

        for(int i= 19; i<41; i++)
        {
            Building tBuilding;

            //Type
            tFrom = pageContent.indexOf("<area alt=", tFrom);
            if(tFrom == -1)
                findError = true;
            tFrom +=11;

            if(pageContent.mid(tFrom, serverType->Buildings.at(0).length()) == serverType->Buildings.at(0) )
            {
                tBuilding = Building(i, 0, 0, travianWiki);
                tBuilding.isResource = false;
                tBuilding.isExist = false;
                (*village->listBuilding.at(i)) = tBuilding;
            }else
            {
                tEnd = pageContent.indexOf("span", tFrom);
                QString tType = pageContent.mid(tFrom, tEnd - tFrom -5);

                //Lvl
                tFrom = pageContent.indexOf(serverType->FindBuildingLevel, tFrom);
                if(tFrom == -1)
                    findError = true;
                tFrom +=serverType->FindBuildingLevel.length();
                tEnd = pageContent.indexOf('&', tFrom);
                int tLvl = pageContent.mid(tFrom, tEnd - tFrom).toInt();

                tBuilding = createBuilding(tType, i, tLvl);
                tBuilding.isResource = false;

                if(tBuilding.idBuilding ==15)
                {
                    village->mainBuildingLvl = tBuilding.lvl;
                    village->mainBuildingIdPlace = i;
                }else if(tBuilding.idBuilding == 25)
                {
                    haveResidence = true;
                }else if( tBuilding.idBuilding == 26)
                {
                    havePalace = true;
                }

                //IsUpgrading
                if("&lt;/span&gt;||&lt;span class=&quot;notice&quot;&gt;" == pageContent.mid(tEnd, 52))
                {
                    tBuilding.isUpgrading = true;
                    QStringList tTimeList = findTimeToEndUpgrading(&(tBuilding.abortValueD), serverType->Buildings.at( tBuilding.idBuilding ), ++tBuilding.lvl).split(':');
                    tBuilding.timeToUpgradeEnd = Time(tTimeList.at(0).toInt(), tTimeList.at(1).toInt(), tTimeList.at(2).toInt());
                 }


                if(tBuilding.lvl != tBuilding.maxLvl)
                {
                    //WoodToUpdate
                    tFrom = pageContent.indexOf("&lt;img class=&quot;r1&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                    if(tFrom == -1)
                        findError = true;
                    tFrom += 60;
                    tEnd = pageContent.indexOf('&', tFrom);
                    tBuilding.woodToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                    //ClayToUpdate
                    tFrom = pageContent.indexOf("&lt;img class=&quot;r2&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                    if(tFrom == -1)
                        findError = true;
                    tFrom += 60;
                    tEnd = pageContent.indexOf('&', tFrom);
                    tBuilding.clayToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                    //IronToUpdate
                    tFrom = pageContent.indexOf("&lt;img class=&quot;r3&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                    if(tFrom == -1)
                        findError = true;
                    tFrom += 60;
                    tEnd = pageContent.indexOf('&', tFrom);
                    tBuilding.ironToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();

                    //CornToUpdate
                    tFrom = pageContent.indexOf("&lt;img class=&quot;r4&quot; src=&quot;img/x.gif&quot; /&gt;", tFrom);
                    if(tFrom == -1)
                        findError = true;
                    tFrom += 60;
                    tEnd = pageContent.indexOf('&', tFrom);
                    tBuilding.cornToUpgrade = pageContent.mid(tFrom, tEnd - tFrom - 5).toInt();
                }
                (*village->listBuilding.at(i)) = tBuilding;

            }
        }

        village->listUpgradingBuilding.clear();
        foreach(Building *i, village->listInfrastructureBuilding)
        {
            if(i->lvl != i->maxLvl)
                i->setUpgradeLongTime(travianWiki, village->mainBuildingLvl);
            if(i->isUpgrading)
                village->listUpgradingBuilding.append(i);
        }

        if(!havePalace && !haveResidence)
            village->isCapital = false;
        else if(havePalace)
            village->isCapital = true;
        else
            village->isCapital = false;

        village->releaseLockBuilding();
        waitForLocker.quit();

    }else
        QTimer::singleShot(50, this, SLOT(findInfraktrusturBuilding()));


}

QString TravianRequest::findTimeToEndUpgrading(QString *fAbordValueD, QString fName, int fLvl)
{
    QString returnValue;
    int tFrom = 0;
    int tEnd = 0 ;
    tFrom = pageContent.indexOf("<img src=\"img/x.gif\" class=\"del\" title=\"" +serverType->FindTimeToEndUpgradingCancel+ "\" alt=\"" +serverType->FindTimeToEndUpgradingCancel+ "\" />");
    tFrom = pageContent.indexOf(fName, tFrom);
    tFrom = pageContent.indexOf(QString(serverType->FindBuildingLevel +" %1").arg(fLvl), tFrom);
    tFrom = pageContent.indexOf("id=\"timer", tFrom);
    tFrom +=12;
    tEnd = pageContent.indexOf('<', tFrom);
    returnValue = pageContent.mid(tFrom, tEnd - tFrom);

    tFrom -= 270;
    tFrom = pageContent.indexOf("<tr><td class=\"ico\"><a href=\"?d", tFrom);
    tFrom += 32;
    tEnd = pageContent.indexOf('&', tFrom);
    *fAbordValueD = pageContent.mid(tFrom, tEnd - tFrom);

    return returnValue;
}



Building TravianRequest::createBuilding(QString tType, int fIdPlace, int fLvl)
{
    for(int i=0; i<42; i++)
        if( tType == serverType->BuildingsHTML.at(i) )
        {
            Building tBuilding(fIdPlace, i, fLvl, travianWiki);
            return tBuilding;
        }

    QMessageBox::information(0,"Error", "Finde Building name " + tType);
}

bool TravianRequest::findValueLoginIndex()
{
    int tFrom=0;
    int tEnd=0;
    tFrom = pageContent.indexOf("<input type=\"hidden\" name=\"login\" value=");
    if(tFrom == -1)
        return false;
    tFrom += 41;
    tEnd = pageContent.indexOf('"', tFrom);

    loginIndex = pageContent.mid(tFrom, tEnd - tFrom).toInt();
    return true;
}

bool TravianRequest::findValueCUpgrading(QString *ValueC)
{
    int tFrom=0;
    int tEnd=0;

    //C Value
    tFrom= pageContent.indexOf("class=\"build\" onclick=\"window.location.href");
    if(tFrom == -1)
        return false;

    tFrom= pageContent.indexOf("c=",tFrom);
    if(tFrom == -1)
        return false;
    tFrom += 2;
    tEnd = pageContent.indexOf("\'", tFrom);
    *ValueC = pageContent.mid(tFrom, tEnd - tFrom );


    return true;
}

bool TravianRequest::findValueCBuilding(QString *ValueC)
{
    int tFrom=0;
    int tEnd=0;

    //C Value
    tFrom= pageContent.indexOf("class=\"new\" onclick=\"window.location.href");
    if(tFrom == -1)
        return false;

    tFrom= pageContent.indexOf("c=",tFrom);
    if(tFrom == -1)
        return false;
    tFrom += 2;
    tEnd = pageContent.indexOf("\'", tFrom);
    *ValueC = pageContent.mid(tFrom, tEnd - tFrom );


    return true;
}

bool TravianRequest::findValueCAbort(QString *ValueC , QString fAbortValueD)
{
    int tFrom=0;
    int tEnd=0;

    tFrom= pageContent.indexOf(fAbortValueD);
    if(tFrom == -1)
        return false;

    tFrom= pageContent.indexOf("c=", tFrom);
    tFrom += 2;
    tEnd = pageContent.indexOf('"', tFrom);
    *ValueC = pageContent.mid(tFrom, tEnd - tFrom );

    return true;
}

bool TravianRequest::findValuesDestroy(QString *ValueGID, QString *ValueA, QString *ValueC)
{
    int tFrom=0;
    int tEnd=0;

    tFrom= pageContent.indexOf("<input type=\"hidden\" name=\"gid\" value=");
    if(tFrom == -1)
        return false;
    tFrom += 39;
    tEnd = pageContent.indexOf('"', tFrom);
    *ValueGID = pageContent.mid(tFrom, tEnd - tFrom );

    tFrom= pageContent.indexOf("<input type=\"hidden\" name=\"a\" value=", tFrom);
    if(tFrom == -1)
        return false;
    tFrom += 37;
    tEnd = pageContent.indexOf('"', tFrom);
    *ValueA = pageContent.mid(tFrom, tEnd - tFrom );

    tFrom= pageContent.indexOf("<input type=\"hidden\" name=\"c\" value=", tFrom);
    if(tFrom == -1)
        return false;
    tFrom += 37;
    tEnd = pageContent.indexOf('"', tFrom);
    *ValueC = pageContent.mid(tFrom, tEnd - tFrom );

    return true;

}

bool TravianRequest::findTimeToEndDestroy(QString *fTime)
{
    int tFrom=0;
    int tEnd=0;

    tFrom= pageContent.indexOf("<td class=\"times\"><span id=\"timer");
    if(tFrom == -1)
        return false;
    tFrom += 35;
    tEnd = pageContent.indexOf('<', tFrom);
    *fTime = pageContent.mid(tFrom, tEnd - tFrom );

    return true;

}

bool TravianRequest::resourcesNeededToUpgrade(Building *fBuilding)
{

    int tTime = village->timeDrof1.secondsTo(Time::currentTime());
    int tCurrentWood = tTime * village->peerSecWood + village->currentWood;
    int tCurrentClay = tTime * village->peerSecClay + village->currentClay;
    int tCurrentIron = tTime * village->peerSecIron + village->currentIron;
    int tCurrentCorn = tTime * village->peerSecCorn + village->currentCorn;

    if( tCurrentWood >= fBuilding->woodToUpgrade &&
            tCurrentClay >= fBuilding->clayToUpgrade &&
                tCurrentIron >= fBuilding->ironToUpgrade &&
                    tCurrentCorn >= fBuilding->cornToUpgrade &&
                        village->currentCorn2 >= fBuilding->corn2ToUpgrade )
    {
        return true;
    }else
        return false;

}

void TravianRequest::loginAgain()
{
    postData.clear();
    postData.addQueryItem("name", login);
    postData.addQueryItem("password",password);
    postData.addQueryItem("s1","Login");
    postData.addQueryItem("w","1024%3A600");
    postData.addQueryItem("login",QString::number(loginIndex));
    postData.addQueryItem("lowRes","1");


    QNetworkRequest request(QUrl(server + "/dorf1.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    networkManager->post(request, postData.encodedQuery());
    waitForReply.exec();

}

int TravianRequest::refresh()
{
    int Error = getDorf2();
    if(Error != 0 )
        return Error;

    Error = getDorf1();
    return Error;
}

int TravianRequest::refreshWithOutDrof2()
{
    searchTheDorf2();
    return getDorf1();


}

int TravianRequest::getDorf1()
{    
    int Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/dorf1.php?newdid=%1").arg(village->newdID))));
    if( Error == 0);
    {
        if(pageContent.isEmpty())
            return 1;

        village->timeDrof1 = Time::currentTime();
        searchTheDorf1();
    }

    return Error;
}

void TravianRequest::searchTheDorf1()
{
    QTimer::singleShot(10, this, SLOT(findResources()));
    waitForLocker.exec();
    if(findError)
        QMessageBox::information(parent,"Error", "Finde Resource");

    QTimer::singleShot(10, this, SLOT(findResourcesProduction()));
    waitForLocker.exec();
    if(findError)
        QMessageBox::information(parent,"Error", "Finde Resource Production");

    QTimer::singleShot(10, this, SLOT(findResourceBuilding()));
    waitForLocker.exec();
    if(findError)
        QMessageBox::information(parent,"Error", "Finde Resource Building");

}

int TravianRequest::getDorf2()
{
    int Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/dorf2.php?newdid=%1").arg(village->newdID))));
    if( Error == 0)
    {
        if(pageContent.isEmpty())
            return 1;

        village->timeDrof2 = Time::currentTime();
        searchTheDorf2();
    }

    return Error;
}

void TravianRequest::searchTheDorf2()
{
    QTimer::singleShot(10, this, SLOT(findInfraktrusturBuilding()));
    waitForLocker.exec();
    if(findError)
        QMessageBox::information(parent,"Error", "Finde Infraktrustur Building");

}

int TravianRequest::sendGetReques(QNetworkRequest fRequest)
{

    reply = networkManager->get(fRequest);
    waitForReply.exec();

    if (reply->error() )
        return reply->error();

    pageContent = reply->readAll();

    reply->deleteLater();
    reply->close();

    if( !isLoginCheack() )
    {
        if( findValueLoginIndex() )
        {
            loginAgain();

            reply = networkManager->get(fRequest);
            waitForReply.exec();

            if (reply->error() )
                return reply->error();

            pageContent = reply->readAll();

            reply->deleteLater();
            reply->close();
        }
        else
            QMessageBox::information(parent,"Error", " Cant findex index login on relogin ");
    }

    return 0;

}

int TravianRequest::sendPostReques(QNetworkRequest fRequest, QByteArray fPostDate)
{
    reply = networkManager->post(fRequest, fPostDate);
    waitForReply.exec();

    if (reply->error() )
        return reply->error();

    pageContent = reply->readAll();

    reply->deleteLater();
    reply->close();

    return 0;
}

void TravianRequest::replyWriteTo()
{
    if(reply->isOpen())
    {
        if(reply->error() != 0)
        {
            //QMessageBox::information(parent,"Error", "Coode: " + QString::number(reply->error()));
            connectionError = true;
        }

        pageContent = reply->readAll();

        reply->deleteLater();
        reply->close();
    }

}

void TravianRequest::connectReplay()
{
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), &waitForReply, SLOT(quit()));
}

void TravianRequest::disconnectReplay()
{
    disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), &waitForReply, SLOT(quit()));
}


//----------------------------------------------------------------------------------------------------------//
//  RequestLogin
//----------------------------------------------------------------------------------------------------------//

RequestLogin::RequestLogin(QWidget *fParent,
                           QNetworkAccessManager *fNetworkManager,
                           QString fServer,
                           QString fLogin,
                           QString fPassword,
                           NationType *fNation,
                           bool *fIsLogin,
                           QList<VillageTemp> *fVillagesTemp,
                           ServerType         *fServerType)
{
    type = 1;
    typeName = "Login";
    parent = fParent;
    networkManager = fNetworkManager;
    server = fServer;
    login = fLogin;
    password = fPassword;
    nation = fNation;
    isLogin = fIsLogin;
    villagesTemp = fVillagesTemp;
    serverType = fServerType;
}

int RequestLogin::execute()
{
    connectReplay();

    int Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/"))));
    if(Error == 0)
    {
        if(!findValueLoginIndex())
            QMessageBox::information(parent, "Error", "Can't Finde LoginIndex");

        postData.addQueryItem("name", login);
        postData.addQueryItem("password",password);
        postData.addQueryItem("s1","Login");
        postData.addQueryItem("w","1024%3A600");
        postData.addQueryItem("login",QString::number(loginIndex));
        postData.addQueryItem("lowRes","1");

        QNetworkRequest request(QUrl(server + "/dorf1.php"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        Error = sendPostReques(request, postData.encodedQuery());
        if(Error == 0)
        {
            if(findNation() && findVillages())
                *isLogin = true;
            else
                QMessageBox::information(parent, "Error", login + " - Wrong login or password or global message");

            emit loginFinished();
        }

    }

    disconnectReplay();

    return Error;
}



//----------------------------------------------------------------------------------------------------------//
//  RequestRefresh
//----------------------------------------------------------------------------------------------------------//
RequestRefresh::RequestRefresh(QWidget *fParent,
                               QNetworkAccessManager *fNetworkManager,
                               QString fServer,
                               QString fLogin,
                               QString fPassword,
                               TravianWiki *fTravianWiki,
                               Village *fVillage,
                               ServerType *fServerType)
{
    type = 2;
    typeName = "Refresh";
    parent = fParent;
    networkManager = fNetworkManager ;
    server = fServer;
    login = fLogin;
    password = fPassword;
    travianWiki = fTravianWiki;
    village = fVillage;
    serverType = fServerType;

}

int RequestRefresh::execute()
{
    connectReplay();

    int Error = refresh();
    if(Error == 0)
        emit requestRefreshVillageFinished(village);

    disconnectReplay();

    return Error;

}


//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingUpgrade
//----------------------------------------------------------------------------------------------------------//
RequestBuildingUpgrade::RequestBuildingUpgrade(QWidget *fParent,
                                               QNetworkAccessManager *fNetworkManager,
                                               QString fServer,
                                               QString fLogin,
                                               QString fPassword,
                                               TravianWiki *fTravianWiki,
                                               Village *fVillage,
                                               ServerType *fServerType,

                                               int fIdPlace,
                                               QList<BuildingSocket*> *fSocketList)
{
    type = 3;
    typeName = "Upgrade";
    parent = fParent;
    networkManager = fNetworkManager ;
    server = fServer;
    login = fLogin;
    password = fPassword;
    travianWiki = fTravianWiki;
    village = fVillage;
    serverType = fServerType;

    idPlace = fIdPlace;
    socketList = fSocketList;

    if(village->isActive)
    {
        socketList->at(idPlace)->itemBuilding->movie->start();
        socketList->at(idPlace)->mapItem->movie->start();
    }
}

int RequestBuildingUpgrade::execute()
{
    connectReplay();

    int Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/build.php?newdid=%1&id=%2").arg(village->newdID).arg(idPlace))));
    if( Error == 0)
    {
        QString ValueC;
        if(findValueCUpgrading(&ValueC))
        {
            Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/dorf2.php?newdid=%1&a=%2&c=%3").arg(village->newdID).arg(idPlace).arg(ValueC))));
            if( Error == 0 )
            {
                Error = refreshWithOutDrof2();
                if( Error == 0 )
                    emit requestRefreshVillageFinished(village);
            }

        }else
        {
            village->tasksBuildMakeAndAddTaskBuildingUpgrade( idPlace, Time::currentTime() );
            emit tasksBuildChanged(village);
            Error = 0;

        }
    }

    socketList->at(idPlace)->itemBuilding->movie->stop();
    socketList->at(idPlace)->itemBuilding->movie->jumpToFrame(0);
    socketList->at(idPlace)->mapItem->movie->stop();
    socketList->at(idPlace)->mapItem->movie->jumpToFrame(0);

    disconnectReplay();

    return Error ;
}

//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingBild
//----------------------------------------------------------------------------------------------------------//
RequestBuildingBuild::RequestBuildingBuild(QWidget *fParent,
                                           QNetworkAccessManager *fNetworkManager,
                                           QString fServer,
                                           QString fLogin,
                                           QString fPassword,
                                           TravianWiki *fTravianWiki,
                                           Village *fVillage,
                                           ServerType *fServerType,

                                           int fIdPlace,
                                           QList<BuildingSocket*> *fSocketList,
                                           int fIdBuilding)
{
    type = 4;
    typeName = "Building";
    parent = fParent;
    networkManager = fNetworkManager ;
    server = fServer;
    login = fLogin;
    password = fPassword;
    travianWiki = fTravianWiki;
    village = fVillage;
    serverType = fServerType;

    idPlace = fIdPlace;
    socketList = fSocketList;;
    idBuilding = fIdBuilding;

    if(village->isActive)
        socketList->at(idPlace)->mapItem->movie->start();
}

int RequestBuildingBuild::execute()
{
    int Error;

    Building tBuilding(idPlace, idBuilding, 0, village->mainBuildingLvl, travianWiki);
    if(resourcesNeededToUpgrade(&tBuilding))
    {
        connectReplay();

        Error = sendGetReques( QNetworkRequest(QUrl(server + QString("/build.php?newdid=%1&id=%2").arg(village->newdID).arg(idPlace))));
        if( Error == 0 )
        {
            QString ValueC;
            if(findValueCBuilding(&ValueC))
            {
                Error = sendGetReques( QNetworkRequest(QUrl(server + QString("/dorf2.php?newdid=%1&a=%2&id=%3&c=%4").arg(village->newdID).arg(idBuilding).arg(idPlace).arg(ValueC))));
                if( Error == 0 )
                {
                    Error = refreshWithOutDrof2();
                    if( Error == 0 )
                        emit requestRefreshVillageFinished(village);
                }
            }else
            {
                village->tasksBuildMakeAndAddTaskBuildingBuild(idPlace, idBuilding, Time::currentTime());
                emit tasksBuildChanged(village);
                Error = 0;
            }

            socketList->at(idPlace)->mapItem->movie->stop();
            socketList->at(idPlace)->mapItem->movie->jumpToFrame(0);

        }
        disconnectReplay();
    }else
    {
        village->tasksBuildMakeAndAddTaskBuildingBuild(idPlace, idBuilding, Time::currentTime());
        emit tasksBuildChanged(village);
        Error = 0;

        socketList->at(idPlace)->mapItem->movie->stop();
        socketList->at(idPlace)->mapItem->movie->jumpToFrame(0);

    }

    return Error;
}

//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingBuildAbord
//----------------------------------------------------------------------------------------------------------//

RequestBuildingBuildAbord::RequestBuildingBuildAbord(QWidget *fParent,
                                                     QNetworkAccessManager *fNetworkManager,
                                                     QString fServer,
                                                     QString fLogin,
                                                     QString fPassword,
                                                     TravianWiki *fTravianWiki,
                                                     Village *fVillage,
                                                     ServerType *fServerType,

                                                     QString fAbortValueD,
                                                     QMovie *fMovie)

{
    type = 5;
    typeName = "Building Abord";
    parent = fParent;
    networkManager = fNetworkManager ;
    server = fServer;
    login = fLogin;
    password = fPassword;
    travianWiki = fTravianWiki;
    village = fVillage;
    serverType = fServerType;

    abortValueD = fAbortValueD;
    movie = fMovie;


    if(village->isActive)
        movie->start();


}

int RequestBuildingBuildAbord::execute()
{

    connectReplay();

    int Error = sendGetReques(QNetworkRequest(QUrl(server + QString("/dorf1.php?newdid=%1").arg(village->newdID))));
    if(Error == 0)
    {
        QString ValueC;
        if(findValueCAbort(&ValueC, abortValueD))
        {
            Error = sendGetReques( QNetworkRequest(QUrl(server + QString("/dorf1.php?newdid=%1&d=%2&a=0&c=%3").arg(village->newdID).arg(abortValueD).arg(ValueC))));
            if(Error == 0)
            {
                refresh();
                emit requestRefreshVillageFinished(village);

            }
        }
    }
    disconnectReplay();
    movie->stop();
    movie->jumpToFrame(0);

    return Error;
}

/*
//----------------------------------------------------------------------------------------------------------//
//  RequestBuildingDestroy
//----------------------------------------------------------------------------------------------------------//

RequestBuildingDestroy::RequestBuildingDestroy(QWidget *fParent,
                                               QNetworkAccessManager *fNetworkManager,
                                               QString fServer,

                                               int *fMainBuildingIdPlace,
                                               int fIdPlace,
                                               Time *fLastDestroy,
                                               Time *fDestroyLongTime)

{
    type = 4;
    parent = fParent;
    networkManager = fNetworkManager ;
    server = fServer;

    mainBuildingIdPlace = fMainBuildingIdPlace;
    idPlace = fIdPlace;
    lastDestroy = fLastDestroy;
    destroyLongTime = fDestroyLongTime;
}

void RequestBuildingDestroy::execute()

{   // build.php
    // postdate gid=%1&a=%2&c=%2&abriss=%3    // abriss = idplace

    connectReplay();
    reply = networkManager->get(QNetworkRequest(QUrl(server + QString("/build.php?id=%1").arg(*mainBuildingIdPlace))));
    waitForReply.exec();

    if(reply->isOpen())
    {
        if(reply->error() != 0)
        {
            QMessageBox::information(parent,"Error", "Code: " + QString::number(reply->error()));
            connectionError = true;
        }

        dorf1 = reply->readAll();

        reply->deleteLater();
        reply->close();
    }

    if(!connectionError)
    {
        QString ValueGID;
        QString ValueA;
        QString ValueC;
        if(findValuesDestroy(&dorf1, &ValueGID, &ValueA, &ValueC))
        {
            postData.addQueryItem("gid", ValueGID);
            postData.addQueryItem("a", ValueA);
            postData.addQueryItem("c", ValueC);
            postData.addQueryItem("abriss",QString::number( idPlace ));

            QNetworkRequest request(QUrl(server + "/build.php"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

            reply = networkManager->post(request, postData.encodedQuery());
            waitForReply.exec();
            lastDestroy->setHMS(QDate::currentDate(), QTime::currentTime());

        }
    }

    if(reply->isOpen())
    {
        if(reply->error() != 0)
        {
            QMessageBox::information(parent,"Error", "Code: " + QString::number(reply->error()));
            connectionError = true;
        }

        dorf1 = reply->readAll();

        reply->deleteLater();
        reply->close();
    }
    if(!connectionError)
    {
        QString tTime;
        if(findTimeToEndDestroy(&dorf1, &tTime))
        {
            destroyLongTime->setHMS(tTime);
            QMessageBox::information(0,"",destroyLongTime->toString());
        }
    }


    disconnectReplay();
}

*/



