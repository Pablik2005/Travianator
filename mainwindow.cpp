#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //---------------------Base---------------------//
    onAndroid = true;
    version = "107";
    village = new Village((QObject*) this);
    travianWiki = new TravianWiki((QObject*) this);
    this->setWindowTitle("Travianator");

    //Make Servers and Language
    MakeServerTypes();
    MakeLanguages();

    BuildingSocket *tZero;
    socketList.append(tZero);
    for(int i=1; i<19; i++)
    {
        BuildingSocket *tBuildingSocket = new BuildingSocket((QObject*) this);
        resourceList.append(tBuildingSocket);
        socketList.append(tBuildingSocket);
    }


    for(int i=19; i<41; i++)
    {
        BuildingSocket *tBuildingSocket = new BuildingSocket((QObject*) this);
        infrastructureList.append(tBuildingSocket);
        socketList.append(tBuildingSocket);
    }


    //---------------------GUI---------------------//
    //---------------------Head--------------------//
    QFont tFont;
    tFont.setPixelSize(12);

    labelWoodCurrMax = ui->labelWoodCurrMax;
    labelWoodCurrMax->setFont(tFont);
    labelWoodProduction = ui->labelWoodProduction;
    labelWoodProduction->setFont(tFont);
    labelWoodTimeToMax = ui->labelWoodTimeToMax;
    labelWoodTimeToMax->setFont(tFont);
    progressBarWood = ui->progressBarWood;
    progressBarWood->setFont(tFont);

    labelClayCurrMax = ui->labelClayCurrMax;
    labelClayCurrMax->setFont(tFont);
    labelClayProduction = ui->labelClayProduction;
    labelClayProduction->setFont(tFont);
    labelClayTimeToMax = ui->labelClayTimeToMax;
    labelClayTimeToMax->setFont(tFont);
    progressBarClay = ui->progressBarClay;
    progressBarClay->setFont(tFont);

    labelIronCurrMax = ui->labelIronCurrMax;
    labelIronCurrMax->setFont(tFont);
    labelIronProduction = ui->labelIronProduction;
    labelIronProduction->setFont(tFont);
    labelIronTimeToMax = ui->labelIronTimeToMax;
    labelIronTimeToMax->setFont(tFont);
    progressBarIron = ui->progressBarIron;
    progressBarIron->setFont(tFont);

    labelCornCurrMax = ui->labelCornCurrMax;
    labelCornCurrMax->setFont(tFont);
    labelCornProduction = ui->labelCornProduction;
    labelCornProduction->setFont(tFont);
    labelCornTimeToMax = ui->labelCornTimeToMax;
    labelCornTimeToMax->setFont(tFont);
    progressBarCorn = ui->progressBarCorn;
    progressBarCorn->setFont(tFont);

    labelCorn2Curr = ui->labelCorn2Curr;
    labelCorn2Curr->setFont(tFont);
    labelStatus = ui->labelStatus;
    isStatusOn = false;

    buttonAccounts = ui->AccountsFrame;
        buttonAccounts->setMaximumSize(125,25);
        buttonAccounts->setMinimumSize(125,25);
        buttonAccounts->setFramePolice(1);
        comboBoxAccounts = new ComboBox(this);
        connect(buttonAccounts, SIGNAL(clicked()), this, SLOT(buttonAccountsClicked()));
        connect(comboBoxAccounts, SIGNAL(indexChanged(int)), SLOT(accountChanged(int)));
        comboBoxAccounts->setTitle("Accounts");
    buttonVillages = ui->VillagesFrame;
        buttonVillages->setMaximumSize(125,25);
        buttonVillages->setMinimumSize(125,25);
        buttonVillages->setFramePolice(1);
        comboBoxVillages = new ComboBox(this);
        connect(buttonVillages, SIGNAL(clicked()), this, SLOT(buttonVillagesClicked()));
        connect(comboBoxVillages, SIGNAL(indexChanged(int)), this, SLOT(villageChanged(int)));
        comboBoxVillages->setTitle("Villages");

    tabWidget = ui->tabWidget;

    //---------------------Build---------------------//
    buildWidget = new QWidget(tabWidget);
    tabWidget->addTab(buildWidget, "Build");
    tabWidget->setFont(tFont);

    dialogBuildingToBuild = new DialogBuildingToBuild(this);
    dialogBuildingToBuild->setPointers(   &nation,
                                          travianWiki,
                                          &isCapital,

                                          &maxWood,
                                          &maxClay,
                                          &maxIron,
                                          &maxCorn,

                                          &productionWood,
                                          &productionClay,
                                          &productionIron,
                                          &productionCorn,

                                          &currentWood,
                                          &currentClay,
                                          &currentIron,
                                          &currentCorn,
                                          &currentCorn2,

                                          &peerSecWood,
                                          &peerSecClay,
                                          &peerSecIron,
                                          &peerSecCorn,

                                          &time,
                                          &activeLanguage,

                                          &resourceList,
                                          &infrastructureList);


    buildBuildingMap = new BuildingMap(this, &nation, &resourceList);
        connect(buildBuildingMap, SIGNAL(changedTo(bool)), this, SLOT(buildBuildingMapChangedTo(bool)));

    buildFilter = new Button(this);
        buildFilter->setMaximumSize(110,25);
        buildFilter->setMinimumSize(110,25);
        buildFilter->setText( activeLanguage->BuildFilter );
        buildFilter->setFramePolice(1);
        connect(buildFilter, SIGNAL(clicked()), this, SLOT(buttonFilterClicked()));


    buildBuildingList = new ListItemBuilding(buildWidget);
        buildBuildingList->setStyleSheet("border-color: white");
        buildBuildingList->setMinimumWidth(150);
        buildBuildingList->setMaximumWidth(150);

    buildConstructionList = new ListItemConstruction(buildWidget);
        buildConstructionList->setMinimumWidth(110);
        buildConstructionList->setMaximumWidth(110);
        buildConstructionList->activeLanguage = &activeLanguage;
        connect(((ItemConstruction*)(buildConstructionList->itemList.at(0))), SIGNAL(clicked(QString,QMovie*)), this, SLOT(buildingAbort(QString,QMovie*)));
        connect(((ItemConstruction*)(buildConstructionList->itemList.at(1))), SIGNAL(clicked(QString,QMovie*)), this, SLOT(buildingAbort(QString,QMovie*)));
        connect(((ItemConstruction*)(buildConstructionList->itemList.at(2))), SIGNAL(clicked(QString,QMovie*)), this, SLOT(buildingAbort(QString,QMovie*)));

    buildTaskBuildList = new ListItemBuildTask(buildWidget);
        buildTaskBuildList->setStyleSheet("border-color: white");
        buildTaskBuildList->setMinimumWidth(150);
        buildTaskBuildList->setMaximumWidth(150);
        connect(buildTaskBuildList, SIGNAL(clicked(int)), this, SLOT(tasksBuildRemoveTask(int)));
        buildTaskBuildList->setPointer(&time,
                                       &isFieldOfCornBuilding,
                                       &fieldOfCornBuildingEnd,

                                       &currentWood,
                                       &currentClay,
                                       &currentIron,
                                       &currentCorn,
                                       &currentCorn2,

                                       &maxWood,
                                       &maxClay,
                                       &maxIron,
                                       &maxCorn,

                                       &productionWood,
                                       &productionClay,
                                       &productionIron,
                                       &productionCorn,

                                       &peerSecWood,
                                       &peerSecClay,
                                       &peerSecIron,
                                       &peerSecCorn,
                                       &nation,
                                       &activeLanguage);

    buildHLayout1 = new QHBoxLayout(this);
    buildHLayout2 = new QHBoxLayout(this);
    buildVLayout1 = new QVBoxLayout(this);
    buildVLayout2 = new QVBoxLayout(this);
    buildSpacer1 = new QSpacerItem(100,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    buildSpacer2 = new QSpacerItem(1,100,QSizePolicy::Fixed, QSizePolicy::Expanding);
    buildSpacer3 = new QSpacerItem(100,1,QSizePolicy::Expanding,QSizePolicy::Fixed);

    buildHLayout1->setMargin(0);
    buildHLayout2->setMargin(0);
    buildVLayout1->setMargin(0);
    buildVLayout2->setMargin(0);

    buildWidget->setLayout(buildHLayout1);
    buildHLayout1->addWidget(buildBuildingList);
    buildHLayout1->addLayout(buildVLayout1);
        buildVLayout1->addWidget(buildFilter);
        buildVLayout1->addWidget(buildConstructionList);
     buildHLayout1->addSpacerItem(buildSpacer1);
     buildHLayout1->addWidget(buildBuildingMap);
     buildHLayout1->addSpacerItem(buildSpacer2);
     buildHLayout1->addWidget(buildTaskBuildList);


    //---------------------Config---------------------//

    for(int i=0; i<18; i++)
    {
        resourceList.at(i)->setMapItem( buildBuildingMap->resourceList.at(i) );
        resourceList.at(i)->setItemBuilding( (ItemBuilding*)buildBuildingList->itemList.at(i) );
        resourceList.at(i)->isResource = true;

        resourceList.at(i)->setPointer(&time,
                                       &currentWood,
                                       &currentClay,
                                       &currentIron,
                                       &currentCorn,
                                       &currentCorn2,

                                       &maxWood,
                                       &maxClay,
                                       &maxIron,
                                       &maxCorn,

                                       &productionWood,
                                       &productionClay,
                                       &productionIron,
                                       &productionCorn,

                                       &peerSecWood,
                                       &peerSecClay,
                                       &peerSecIron,
                                       &peerSecCorn,

                                       travianWiki,
                                       &nation,
                                       buildTaskBuildList,
                                       &mainBuildingLvl,
                                       &activeLanguage);

        connect(resourceList.at(i), SIGNAL(clickedUpgrade(int,int,int,Time)), this, SLOT(buildingUpgrade(int,int,int,Time)));
    }


    for(int i=0; i<22; i++)
    {
        if(i == 21)
            infrastructureList.at(i)->itsIdBuilding40 = true;

        infrastructureList.at(i)->setMapItem( buildBuildingMap->infrastructureList.at(i) );
        infrastructureList.at(i)->setItemBuilding( (ItemBuilding*)buildBuildingList->itemList.at(i+18) );
        infrastructureList.at(i)->isResource = false;

        infrastructureList.at(i)->setPointer(&time,
                                             &currentWood,
                                             &currentClay,
                                             &currentIron,
                                             &currentCorn,
                                             &currentCorn2,

                                             &maxWood,
                                             &maxClay,
                                             &maxIron,
                                             &maxCorn,

                                             &productionWood,
                                             &productionClay,
                                             &productionIron,
                                             &productionCorn,

                                             &peerSecWood,
                                             &peerSecClay,
                                             &peerSecIron,
                                             &peerSecCorn,

                                             travianWiki,
                                             &nation,
                                             buildTaskBuildList,
                                             &mainBuildingLvl,
                                             &activeLanguage);

        connect(infrastructureList.at(i), SIGNAL(clickedUpgrade(int,int,int,Time)), this, SLOT(buildingUpgrade(int,int,int,Time)));
        connect(infrastructureList.at(i), SIGNAL(clickedBuild(int,int,int,Time)), this, SLOT(buildingBuild(int,int,int,Time)));
        connect(infrastructureList.at(i), SIGNAL(clickedBuildFortification(int,int,int,int,Time)), this, SLOT(buildingBuildFortification(int,int,int,int,Time)));
    }

    refreshedOn = false;
    firstSetValue = false;

    //XML Tasks
    XMLAccounts = XMLDocument.createElement("Accounts");
    XMLDocument.appendChild(XMLAccounts);

    LoadFromFile();
}

MainWindow::~MainWindow()
{
    SaveToFile();
    delete ui;
}

void MainWindow::SaveToFile()
{   
    //----------Accounts----------//
    QFile tAccFile("file");
    if(onAndroid)
    {
        QDir tDir("/sdcard");
        tDir.mkpath("Travianator");
        tAccFile.setFileName("/sdcard/Travianator/Config" + version);

    }else
    {
        tAccFile.setFileName(QCoreApplication::applicationDirPath() + "/Config" + version);
    }


    if(tAccFile.open(QIODevice::WriteOnly))
    {
        QDataStream tStream(&tAccFile);

        tStream  << activeLanguage->shortCut;

        tStream  << accountList.count();
        foreach(Account *a, accountList)
            tStream << a;


    }
    tAccFile.flush();
    tAccFile.close();


    //----------Tasks----------//
    QFile XMLFile("file");
    if(onAndroid)
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
        tStream  << XMLDocument;

    }else
        QMessageBox::information(0,"Error","Can't open Task.xml");

    XMLFile.flush();
    XMLFile.close();

}

void MainWindow::LoadFromFile()
{
    QFile tAccFile("file");
    if(onAndroid)
    {
        tAccFile.setFileName("/sdcard/Travianator/Config" + version);
    }else
    {
        tAccFile.setFileName(QCoreApplication::applicationDirPath() + "/Config" + version);
    }

    if(tAccFile.exists())
    {

        accountList.clear();
        if(tAccFile.open(QIODevice::ReadOnly))
        {
            QDataStream tStream(&tAccFile);

            QString tLanguageShortCut;
            tStream >> tLanguageShortCut;
            for(int i=0; i<languages.count(); i++)
                if(languages.at(i)->shortCut == tLanguageShortCut)
                {
                    changeLanguage(i);
                    break;
                }

            int accCount;
            tStream >> accCount;
            for(int a=0; a<accCount; a++)
            {
                Account *tAccount = new Account(this, travianWiki);
                tStream >> tAccount;

                int tFrom = tAccount->server.indexOf("travian.");
                QString tPrefix = tAccount->server.mid(tFrom+8);

                foreach(ServerType *i, serverTypes)
                    if( tPrefix == i->name.toLower() )
                    {
                        tAccount->serverType = i;
                        break;
                    }

                connect(tAccount, SIGNAL(setStatusOn(bool)), this, SLOT(setStatusOn(bool)));

                tAccount->socketList = &socketList;
                accountList.append(tAccount);
                comboBoxAccounts->addItem(tAccount->login);



            }
        }

        if(accountList.count() > 0)
        {
            comboBoxAccountsLastIndex = 0;
            connect(accountList.at(comboBoxAccountsLastIndex), SIGNAL(loginFinished(QList<VillageTemp>)), this, SLOT(loginFinished(QList<VillageTemp>)));
        }

        for(int a=0; a<accountList.count(); a++)
        {
            accountList.at(a)->XMLDocument = &XMLDocument;
            accountList.at(a)->XMLAccounts = &XMLAccounts;
            accountList.at(a)->onAndroid = &onAndroid;
            accountList.at(a)->idAccount = a;

            connect(accountList.at(a), SIGNAL(setStatusOn(bool)), this, SLOT(setStatusOn(bool)));
            connect(accountList.at(a), SIGNAL(villageRefreshed(int,int)), this, SLOT(villageRefreshed(int,int)));
            connect(accountList.at(a), SIGNAL(tasksBuildChanged(int,int)), this, SLOT(tasksBuildChanged(int,int)));

            accountList.at(a)->Login();
        }

        LoadTaskFromFile();
    }

}

void MainWindow::LoadTaskFromFile()
{
    QFile XMLFile("file");
    if(onAndroid)
    {
        XMLFile.setFileName("/sdcard/Travianator/Tasks.xml");

    }else
    {
        XMLFile.setFileName(QCoreApplication::applicationDirPath() + "/Tasks.XML");
    }

    if(XMLFile.exists())
    {
        if(XMLFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            int loadTasks = 1;
            //0 - dont add, 1 - ask, 2 - add

            QTextStream tStream(&XMLFile);
            QDomDocument tXMLDocument;
            tXMLDocument.setContent(tStream.readAll());

            QDomElement root = tXMLDocument.firstChildElement("Accounts");

            QDomNodeList Accounts = root.elementsByTagName("Account");
            for(int a=0; a< Accounts.count(); a++)
            {
                if(loadTasks)
                {
                    //Check Account Exist
                    QString AccountName = Accounts.at(a).toElement().attribute("Name");

                    int AccountIndex = -1;
                    foreach(Account *aa, accountList)
                    {
                        AccountIndex++;
                        if(aa->login == AccountName)
                            break;
                    }

                    if( AccountIndex != -1)
                    {
                        QDomNodeList Villages = Accounts.at(a).toElement().elementsByTagName("Village");
                        for(int v=0; v< Villages.count(); v++)
                        {
                            //Check Village Exist
                            QString VillageName = Villages.at(v).toElement().attribute("Name");

                            int VillageIndex = -1;
                            foreach(Village *vv, accountList.at(AccountIndex)->villages)
                            {
                                VillageIndex++;
                                if(vv->name == VillageName)
                                    break;
                            }

                            if( VillageIndex != -1)
                            {
                                QDomNodeList Tasks = Villages.at(v).toElement().elementsByTagName("Task");
                                for(int t=0; t< Tasks.count(); t++)
                                {
                                    if(loadTasks == 1)
                                    {
                                        QMessageBox::StandardButton reply;
                                        reply = QMessageBox::warning(this, activeLanguage->DialogLoadTaskFromFileTittle, activeLanguage->DialogLoadTaskFromFileMessage, QMessageBox::Ok | QMessageBox::Cancel);

                                        if(reply == QMessageBox::Ok)
                                            loadTasks = 2;
                                        else
                                            loadTasks = 0;

                                    }

                                    if(loadTasks)
                                    {
                                        int tType = Tasks.at(t).toElement().attribute("type").toInt();
                                        int tIdPlace = Tasks.at(t).toElement().attribute("idPlace").toInt();
                                        int tIdBuilding = Tasks.at(t).toElement().attribute("idBuilding").toInt();
                                        Time tTime( Tasks.at(t).toElement().attribute("buildOn") );
                                        switch(tType)
                                        {
                                            case 1:
                                                accountList.at(AccountIndex)->villages.at(VillageIndex)->tasksBuildMakeAndAddTaskBuildingUpgrade(tIdPlace, tTime);
                                                break;
                                            case 2:
                                                accountList.at(AccountIndex)->villages.at(VillageIndex)->tasksBuildMakeAndAddTaskBuildingBuild(tIdPlace, tIdBuilding, tTime);
                                                break;
                                        }
                                    }
                                }
                            }
                            accountList.at(AccountIndex)->tasksBuildChanged(VillageIndex);
                        }
                    }
                }
            }

        }else
            QMessageBox::information(0,"Error","Can't open Task.xml");

        XMLFile.flush();
        XMLFile.close();

    }

}

void MainWindow::MakeServerTypes()
{
    ServerType *PL = new ServerType((QObject*)this,"PL");
    LoadServerType(PL, "PL");
    serverTypes.append(PL);

    ServerType *COM = new ServerType((QObject*)this,"COM");
    LoadServerType(COM, "COM");
    serverTypes.append(COM);
}

void MainWindow::LoadServerType(ServerType *fServer, QString fName)
{
    QSettings setting(":/Data/Servers.ini", QSettings::IniFormat);
    setting.setIniCodec("UTF-8");

    setting.beginGroup(fName);

    fServer->Rzymianie = setting.value("Rzymianie").toString();
    fServer->Galowie = setting.value("Galowie").toString();
    fServer->Germanie = setting.value("Germanie").toString();

    fServer->Wood = setting.value("Wood").toString();
    fServer->Iron = setting.value("Iron").toString();
    fServer->Clay = setting.value("Clay").toString();
    fServer->Corn = setting.value("Corn").toString();

    fServer->FindBuildingLevel = setting.value("FindBuildingLevel").toString();

    fServer->FindBuildingFullUpgraded = setting.value("FindBuildingFullUpgraded").toString();
    fServer->FindBuildingIsFullUpgrading = setting.value("FindBuildingIsFullUpgrading").toString();

    fServer->FindTimeToEndUpgradingCancel = setting.value("FindTimeToEndUpgradingCancel").toString();

    for(int i=0; i<42; i++)
        fServer->Buildings.append( setting.value( "Building" + QString::number(i) ).toString() );

    for(int i=0; i<42; i++)
        fServer->BuildingsHTML.append( setting.value( "BuildingHTML" + QString::number(i) ).toString() );

    setting.endGroup();
}

void MainWindow::MakeLanguages()
{
    Language *PL = new Language((QObject*)this, "Polish", "PL");
    LoadLanguages(PL, "PL");
    PL->index = 0;
    languages.append(PL);

    Language *ENG = new Language((QObject*)this, "English", "ENG");
    LoadLanguages(ENG, "ENG");
    ENG->index = 1;
    languages.append(ENG);

    activeLanguage = ENG;

}

void MainWindow::LoadLanguages(Language *fLanguage, QString fName)
{
    QSettings setting(":/Data/Language/Languages.ini", QSettings::IniFormat);
    setting.setIniCodec("UTF-8");

    setting.beginGroup(fName);

    fLanguage->Rzymianie = setting.value("Rzymianie").toString();   if(fLanguage->Rzymianie.isEmpty()) QMessageBox::information(this,fName,"Load: Rzymianie");
    fLanguage->Galowie = setting.value("Galowie").toString();   if(fLanguage->Galowie.isEmpty()) QMessageBox::information(this,fName,"Load: Galowie");
    fLanguage->Germanie = setting.value("Germanie").toString(); if(fLanguage->Germanie.isEmpty()) QMessageBox::information(this,fName,"Load: Germanie");

    fLanguage->Capitol = setting.value("Capitol").toString();   if(fLanguage->Capitol.isEmpty()) QMessageBox::information(this,fName,"Load: Capitol");
    fLanguage->NotInCapitol = setting.value("NotInCapitol").toString(); if(fLanguage->NotInCapitol.isEmpty()) QMessageBox::information(this,fName,"Load: NotInCapitol");

    for(int i=0; i<42; i++)
    {
        fLanguage->Buildings.append( setting.value( "Building" + QString::number(i) ).toString() );

        if(i != 12)
            if( setting.value( "Building" + QString::number(i) ).toString().isEmpty() ) QMessageBox::information(this,fName,"Load: Building" + QString::number(i));
    }

    fLanguage->MenuRefresh = setting.value("MenuRefresh").toString();   if(fLanguage->MenuRefresh.isEmpty()) QMessageBox::information(this,fName,"Load: MenuRefresh");
    fLanguage->MenuRefreshVillage = setting.value("MenuRefreshVillage").toString(); if(fLanguage->MenuRefreshVillage.isEmpty()) QMessageBox::information(this,fName,"Load: MenuRefreshVillage");
    fLanguage->MenuRefreshAccount = setting.value("MenuRefreshAccount").toString(); if(fLanguage->MenuRefreshAccount.isEmpty()) QMessageBox::information(this,fName,"Load: MenuRefreshAccount");
    fLanguage->MenuRefreshAccounts = setting.value("MenuRefreshAccounts").toString();   if(fLanguage->MenuRefreshAccounts.isEmpty()) QMessageBox::information(this,fName,"Load: MenuRefreshAccounts");
    fLanguage->MenuOptions = setting.value("MenuOptions").toString();   if(fLanguage->MenuOptions.isEmpty()) QMessageBox::information(this,fName,"Load: MenuOptions");
    fLanguage->MenuOptionsAccounts = setting.value("MenuOptionsAccounts").toString();   if(fLanguage->MenuOptionsAccounts.isEmpty()) QMessageBox::information(this,fName,"Load: MenuOptionsAccounts");
    fLanguage->MenuOptionsLanguage = setting.value("MenuOptionsLanguage").toString();   if(fLanguage->MenuOptionsLanguage.isEmpty()) QMessageBox::information(this,fName,"Load: MenuOptionsLanguage");

    fLanguage->BuildFilter = setting.value("BuildFilter").toString();   if(fLanguage->BuildFilter.isEmpty()) QMessageBox::information(this,fName,"Load: BuildFilter");

    fLanguage->BuildMenuBuildNow = setting.value("BuildMenuBuildNow").toString();   if(fLanguage->BuildMenuBuildNow.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuBuildNow");
    fLanguage->BuildMenuUpgradeNow = setting.value("BuildMenuUpgradeNow").toString();   if(fLanguage->BuildMenuUpgradeNow.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuUpgradeNow");
    fLanguage->BuildMenuAddTask = setting.value("BuildMenuAddTask").toString(); if(fLanguage->BuildMenuAddTask.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuAddTask");
    fLanguage->BuildMenuAddTasks = setting.value("BuildMenuAddTasks").toString();   if(fLanguage->BuildMenuAddTasks.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuAddTasks");
    fLanguage->BuildMenuAddTaskOn = setting.value("BuildMenuAddTaskOn").toString(); if(fLanguage->BuildMenuAddTaskOn.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuAddTaskOn");
    fLanguage->BuildMenuAddTasksOn = setting.value("BuildMenuAddTasksOn").toString();   if(fLanguage->BuildMenuAddTasksOn.isEmpty()) QMessageBox::information(this,fName,"Load: BuildMenuAddTasksOn");

    fLanguage->AccoutManagerTitle = setting.value("AccoutManagerTitle").toString(); if(fLanguage->AccoutManagerTitle.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerTitle");
    fLanguage->AccoutManagerLogin = setting.value("AccoutManagerLogin").toString(); if(fLanguage->AccoutManagerLogin.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerLogin");
    fLanguage->AccoutManagerPassword = setting.value("AccoutManagerPassword").toString();   if(fLanguage->AccoutManagerPassword.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerPassword");
    fLanguage->AccoutManagerServer = setting.value("AccoutManagerServer").toString();   if(fLanguage->AccoutManagerServer.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerServer");
    fLanguage->AccoutManagerAdd = setting.value("AccoutManagerAdd").toString(); if(fLanguage->AccoutManagerAdd.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerAdd");
    fLanguage->AccoutManagerOk = setting.value("AccoutManagerOk").toString();   if(fLanguage->AccoutManagerOk.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerOk");
    fLanguage->AccoutManagerCancel = setting.value("AccoutManagerCancel").toString();   if(fLanguage->AccoutManagerCancel.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerCancel");
    fLanguage->AccoutManagerDel = setting.value("AccoutManagerDel").toString(); if(fLanguage->AccoutManagerDel.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerDel");
    fLanguage->AccoutManagerClear = setting.value("AccoutManagerClear").toString(); if(fLanguage->AccoutManagerClear.isEmpty()) QMessageBox::information(this,fName,"Load: AccoutManagerClear");

    fLanguage->DialogGetTimeTitle = setting.value("DialogGetTimeTitle").toString(); if(fLanguage->DialogGetTimeTitle.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeTitle");
    fLanguage->DialogGetTimeOn = setting.value("DialogGetTimeOn").toString();   if(fLanguage->DialogGetTimeOn.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeOn");
    fLanguage->DialogGetTimeFor = setting.value("DialogGetTimeFor").toString(); if(fLanguage->DialogGetTimeFor.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeFor");
    fLanguage->DialogGetTimeYear = setting.value("DialogGetTimeYear").toString();   if(fLanguage->DialogGetTimeYear.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeYear");
    fLanguage->DialogGetTimeMonth = setting.value("DialogGetTimeMonth").toString(); if(fLanguage->DialogGetTimeMonth.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeMonth");
    fLanguage->DialogGetTimeDay = setting.value("DialogGetTimeDay").toString(); if(fLanguage->DialogGetTimeDay.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeDay");
    fLanguage->DialogGetTimeHour = setting.value("DialogGetTimeHour").toString();   if(fLanguage->DialogGetTimeHour.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeHour");
    fLanguage->DialogGetTimeMinute = setting.value("DialogGetTimeMinute").toString();   if(fLanguage->DialogGetTimeMinute.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeMinute");
    fLanguage->DialogGetTimeSecound = setting.value("DialogGetTimeSecound").toString(); if(fLanguage->DialogGetTimeSecound.isEmpty()) QMessageBox::information(this,fName,"Load: DialogGetTimeSecound");

    fLanguage->DialogLoadTaskFromFileTittle = setting.value("DialogLoadTaskFromFileTittle").toString(); if(fLanguage->DialogLoadTaskFromFileTittle.isEmpty()) QMessageBox::information(this,fName,"Load: DialogLoadTaskFromFileTittle");
    fLanguage->DialogLoadTaskFromFileMessage = setting.value("DialogLoadTaskFromFileMessage").toString();   if(fLanguage->DialogLoadTaskFromFileMessage.isEmpty()) QMessageBox::information(this,fName,"Load: DialogLoadTaskFromFileMessage");

    fLanguage->DialogCloseAppTittle = setting.value("DialogCloseAppTittle").toString();  if(fLanguage->DialogCloseAppTittle.isEmpty()) QMessageBox::information(this,fName,"Load: DialogCloseAppTitle");
    fLanguage->DialogCloseAppMessage = setting.value("DialogCloseAppMessage").toString();   if(fLanguage->DialogCloseAppMessage.isEmpty()) QMessageBox::information(this,fName,"Load: DialogCloseAppMessage");

    setting.endGroup();
}

void MainWindow::changeLanguage(int index)
{
    activeLanguage = languages.at(index);

    ui->menuRefresh->setTitle( activeLanguage->MenuRefresh );
    ui->actionRefresh_Village->setText( activeLanguage->MenuRefreshVillage );
    ui->actionRefresh_Account->setText( activeLanguage->MenuRefreshAccount );
    ui->actionRefresh_Accounts->setText( activeLanguage->MenuRefreshAccounts );

    ui->menuOptions->setTitle( activeLanguage->MenuOptions );
    ui->actionAccounts->setText( activeLanguage->MenuOptionsAccounts );
    ui->actionLanguage->setText( activeLanguage->MenuOptionsLanguage );

    buildFilter->setText( activeLanguage->BuildFilter );


    if(firstSetValue)
    {
        for(int i=1; i<41; i++)
            if(socketList.at(i)->building.idBuilding != 0)
            {
                socketList.at(i)->itemBuilding->setTitle( activeLanguage->Buildings.at( socketList.at(i)->building.idBuilding ) );
                socketList.at(i)->refresh();
            }

        for(int i=0; i<buildConstructionList->count; i++)
        {
            Item *tItem = buildConstructionList->itemList.at(i);
            ((ItemConstruction*)tItem)->setTitle( activeLanguage->Buildings.at( ((ItemConstruction*)tItem)->building.idBuilding ) );
        }
        buildConstructionList->refresh();

        for(int i=0; i<buildTaskBuildList->itemList.count(); i++)
        {
            Item *tItem = buildTaskBuildList->itemList.at(i);
            ((ItemBuildTask*)tItem)->setTitle( activeLanguage->Buildings.at( ((ItemBuildTask*)tItem)->task.idBuilding ) );
        }
        buildTaskBuildList->refresh();


    }
}

void MainWindow::setAll()
{
    setResources();
    setBuildingList();
    setConstructionItems();
    setTaskBuildList();
}

void MainWindow::refreshAll()
{
    refreshResources();
    refreshBuildingList();
    refreshConstructionItems();
    refreshTaskBuildList();
}

void MainWindow::setResources()
{
    maxWood = village->maxWood;
    maxClay = village->maxClay;
    maxIron = village->maxIron;
    maxCorn = village->maxCorn;

    currentWood = village->currentWood;
    currentClay = village->currentClay;
    currentIron = village->currentIron;
    currentCorn = village->currentCorn;
    currentCorn2 = village->currentCorn2;

    productionWood = village->productionWood;
    productionClay = village->productionClay;
    productionIron = village->productionIron;
    productionCorn = village->productionCorn;

    peerSecWood = village->peerSecWood;
    peerSecClay = village->peerSecClay;
    peerSecIron = village->peerSecIron;
    peerSecCorn = village->peerSecCorn;

    if(productionWood < 0)
    {
        QString tBuilder = "<font color='red'> %1 </font>";
        labelWoodProduction->setText(tBuilder.arg(productionWood));
    }
    else
    {
        QString tBuilder = "<font color='green'>+ %1 </font>";
        labelWoodProduction->setText(tBuilder.arg(productionWood));
    }

    if(productionClay < 0)
    {
        QString tBuilder = "<font color='red'> %1 </font>";
        labelClayProduction->setText(tBuilder.arg(productionClay));
    }
    else
    {
        QString tBuilder = "<font color='green'>+ %1 </font>";
        labelClayProduction->setText(tBuilder.arg(productionClay));
    }

    if(productionIron < 0)
    {
        QString tBuilder = "<font color='red'> %1 </font>";
        labelIronProduction->setText(tBuilder.arg(productionIron));
    }
    else
    {
        QString tBuilder = "<font color='green'>+ %1 </font>";
        labelIronProduction->setText(tBuilder.arg(productionIron));
    }

    if(productionCorn < 0)
    {
        QString tBuilder = "<font color='red'> %1 </font>";
        labelCornProduction->setText(tBuilder.arg(productionCorn));
    }
    else
    {
        QString tBuilder = "<font color='green'>+ %1 </font>";
        labelCornProduction->setText(tBuilder.arg(productionCorn));
    }


    time = village->timeDrof1;
}

void MainWindow::refreshResources()
{
    double tCurrent;
    int    tTime = time.secondsTo(Time::currentTime());
    int    tToFull;
    int    tMin;
    int    tHours;


    //Wood
    tCurrent = tTime * peerSecWood + currentWood;
    if( maxWood <= (int)tCurrent )
       labelWoodCurrMax->setText(QString::number(maxWood) + '/' + QString::number(maxWood));
    else
        labelWoodCurrMax->setText(QString::number((int)tCurrent) + '/' + QString::number(maxWood));
    progressBarWood->setValue( (int)tCurrent / (maxWood /100) );

    if(village->peerSecWood > 0)
    {
        tToFull = maxWood - (int)tCurrent;
        tMin = ((double) tToFull / peerSecWood) /60;
        tHours = tMin / 60;
        labelWoodTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));
    }else
    {
        tMin = ((double)tCurrent / (-peerSecWood)) /60;
        tHours = tMin / 60;
        labelWoodTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));

    }

    //Clay
    tCurrent = tTime * peerSecClay + currentClay;
    if( maxClay <= (int)tCurrent )
       labelClayCurrMax->setText(QString::number(maxClay) + '/' + QString::number(maxClay));
    else
        labelClayCurrMax->setText(QString::number((int)tCurrent) + '/' + QString::number(maxClay));
    progressBarClay->setValue( (int)tCurrent / (maxClay /100) );

    if(village->peerSecClay > 0)
    {
        tToFull = maxClay - (int)tCurrent;
        tMin = ((double) tToFull / peerSecClay) /60;
        tHours = tMin / 60;
        labelClayTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));
        }else
    {
        tMin = ((double)tCurrent / (-peerSecClay)) /60;
        tHours = tMin / 60;
        labelClayTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));

    }

    //Iron
    tCurrent = tTime * peerSecIron + currentIron;
    if( maxIron <= (int)tCurrent )
       labelIronCurrMax->setText(QString::number(maxIron) + '/' + QString::number(maxIron));
    else
        labelIronCurrMax->setText(QString::number((int)tCurrent) + '/' + QString::number(maxIron));
    progressBarIron->setValue( (int)tCurrent / (maxIron /100) );

    if(village->peerSecIron > 0)
    {
        tToFull = maxIron - (int)tCurrent;
        tMin = ((double) tToFull / peerSecIron) /60;
        tHours = tMin / 60;
        labelIronTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));
        }else
    {
        tMin = ((double)tCurrent / (-peerSecIron)) /60;
        tHours = tMin / 60;
        labelIronTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));
    }

    //Corn
    tCurrent = tTime * peerSecCorn + currentCorn;
    if( maxCorn <= (int)tCurrent )
       labelCornCurrMax->setText(QString::number(maxCorn) + '/' + QString::number(maxCorn));
    else
        labelCornCurrMax->setText(QString::number((int)tCurrent) + '/' + QString::number(maxCorn));
    progressBarCorn->setValue( (int)tCurrent / (maxCorn /100) );

    if(village->peerSecCorn > 0)
    {
        tToFull = maxCorn - (int)tCurrent;
        tMin = ((double) tToFull / peerSecCorn) /60;
        tHours = tMin / 60;
        labelCornTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));
        }else
    {
        tMin = ((double)tCurrent / (-peerSecCorn)) /60;
        tHours = tMin / 60;
        labelCornTimeToMax->setText(QString::number(tHours) + ':' + QString::number( tMin - tHours *60 ));

    }
    //Corn2
    labelCorn2Curr->setText(QString::number(currentCorn2));

}

void MainWindow::setBuildingList()
{
    for(int i=0; i<18; i++)
        resourceList.at(i)->setBuilding( *(village->listResourceBuilding.at(i)));

    for(int i=0; i<22; i++)
        infrastructureList.at(i)->setBuilding( *(village->listInfrastructureBuilding.at(i)));

    isFieldOfCornBuilding = village->isFieldOfCornBuilding;
    fieldOfCornBuildingEnd = village->fieldOfCornBuildingEnd;

    buildBuildingList->refresh();
}

void MainWindow::refreshBuildingList()
{
    foreach(BuildingSocket *i, infrastructureList)
        i->refresh();

    foreach(BuildingSocket *i, resourceList)
        i->refresh();
}

void MainWindow::setConstructionItems()
{
    buildConstructionList->clear();
    buildTaskBuildList->buildingInConstrction.clear();

    foreach(Building *i, village->listUpgradingBuilding)
    {
        buildConstructionList->addItem( *i );
        buildTaskBuildList->buildingInConstrction.append(*i);

    }

    buildConstructionList->time = village->timeDrof2;
}

void MainWindow::refreshConstructionItems()
{
    buildConstructionList->refresh();
}

void MainWindow::setTaskBuildList()
{
    buildTaskBuildList->clear();

    foreach(Task *i, village->tasksBuild)
    {
        buildTaskBuildList->addTask( *i );
        if(i->type == 2)
        {
            BuildingSocket *tSocket = socketList.at(i->idPlace);
            tSocket->setNotExistBuilding(Building(i->idPlace, i->idBuilding, i->lvl, mainBuildingLvl, travianWiki));
            buildBuildingList->refresh();
        }
    }

}

void MainWindow::refreshTaskBuildList()
{
    buildTaskBuildList->refresh();
}

void MainWindow::closeEvent(QCloseEvent *e)
{


    /*
    QMessageBox lol(this);
    lol.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    lol.exec();
*/
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, activeLanguage->DialogCloseAppTittle, activeLanguage->DialogCloseAppMessage, QMessageBox::Ok | QMessageBox::Cancel);

    if(reply == QMessageBox::Cancel)
        e->ignore();

}

void MainWindow::buildingUpgrade(int fIdPlace, int fMenuChoice, int fLvlCount, Time fTime)
{
    if(firstSetValue && fMenuChoice >= 0  && fMenuChoice<=4)
    {
        if(fMenuChoice == 0)
        {
            if(socketList.at(fIdPlace)->building.isExist)
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->buildingBuild(fIdPlace);
            else
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());

        }else if(fMenuChoice == 1 || fMenuChoice == 2)
        {

            if(fMenuChoice == 1)
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());
            else
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, fTime);



        }else if(fMenuChoice == 3 || fMenuChoice == 4)
        {
            int taskCountInList = 0;
            foreach(Item *i, buildTaskBuildList->itemList)
                if( ((ItemBuildTask*)i)->task.idPlace == fIdPlace )
                    taskCountInList++;

            int loopCount = fLvlCount - taskCountInList;
            for(int i=0; i<loopCount; i++)
            {
                if(fMenuChoice == 3)
                    accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());
                else
                    accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, fTime);           }

        }

        if(fMenuChoice !=0 || !socketList.at(fIdPlace)->building.isExist )
            accountList.at(comboBoxAccounts->currentIndex())->tasksBuildChanged( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex()) );
    }
}



void MainWindow::buildingBuild(int fIdPlace, int fMenuChoice, int fLvlCount, Time fTime)
{
    if(firstSetValue && fMenuChoice >= 0  && fMenuChoice<=4)
    {
        //Zwykłę budynki
        if(fIdPlace != 39)
        {
            dialogBuildingToBuild->createList();
            dialogBuildingToBuild->exec();
            if(dialogBuildingToBuild->idBuilding != -1)
            {

                if(fMenuChoice == 0)
                {
                    accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->buildingBuild(fIdPlace, dialogBuildingToBuild->idBuilding);
                }else if(fMenuChoice == 1 || fMenuChoice == 2 || fMenuChoice == 3 || fMenuChoice == 4)
                {

                    if(fMenuChoice == 1 || fMenuChoice == 3 )
                        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, dialogBuildingToBuild->idBuilding, Time::currentTime());
                    else
                        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, dialogBuildingToBuild->idBuilding, fTime);

                    BuildingSocket *tSocket = socketList.at(fIdPlace);
                    tSocket->setNotExistBuilding(Building(fIdPlace, dialogBuildingToBuild->idBuilding, 1, travianWiki));
                    buildBuildingList->refresh();

                    if(fMenuChoice == 3 || fMenuChoice == 4 )
                        for(int i=0; i<fLvlCount; i++)
                        {
                            if(fMenuChoice == 3)
                                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());
                            else
                                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, fTime);
                        }

                    accountList.at(comboBoxAccounts->currentIndex())->tasksBuildChanged( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex()) );
                }
            }
        // Miejsce Zbiórki
        }else
        {
            if(fMenuChoice == 0)
            {
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->buildingBuild(fIdPlace, 16);
            }else if(fMenuChoice == 1 || fMenuChoice == 2 || fMenuChoice == 3 || fMenuChoice == 4)
            {
                if(fMenuChoice == 1 || fMenuChoice == 3 )
                    accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, 16, Time::currentTime());
                else
                    accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, 16, fTime);


                BuildingSocket *tSocket = socketList.at(fIdPlace);
                tSocket->setNotExistBuilding(Building(fIdPlace, 16, 1, travianWiki));
                buildBuildingList->refresh();

                if(fMenuChoice == 3 || fMenuChoice == 4 )
                    for(int i=0; i<fLvlCount; i++)
                    {
                        if(fMenuChoice == 3)
                            accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());
                        else
                            accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, fTime);
                    }
                accountList.at(comboBoxAccounts->currentIndex())->tasksBuildChanged( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex()) );
            }

        }

    }
}

void MainWindow::buildingBuildFortification(int fIdPlace, int fIdBuilding, int fMenuChoice, int fLvlCount, Time fTime)
{
    if(firstSetValue && fMenuChoice >= 0  && fMenuChoice<=4)
    {

        if(fMenuChoice == 0)
        {
            accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->buildingBuild(fIdPlace, fIdBuilding);
        }else if(fMenuChoice == 1 || fMenuChoice == 2 || fMenuChoice == 3 || fMenuChoice == 4)
        {
            if(fMenuChoice == 1 || fMenuChoice == 3 )
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, fIdBuilding, Time::currentTime());
            else
                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingBuild(fIdPlace, fIdBuilding, fTime);

            if(fMenuChoice == 3 || fMenuChoice == 4 )
                for(int i=0; i<fLvlCount; i++)
                {
                    if(fMenuChoice == 3 || fMenuChoice == 4 )
                        for(int i=0; i<fLvlCount; i++)
                        {
                            if(fMenuChoice == 3)
                                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, Time::currentTime());
                            else
                                accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildMakeAndAddTaskBuildingUpgrade(fIdPlace, fTime);
                        }
                  }
            accountList.at(comboBoxAccounts->currentIndex())->tasksBuildChanged( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex()) );
        }
    }

}

void MainWindow::buildingAbort(QString AbortValueD, QMovie *fMovie)
{
    if(firstSetValue)
        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->buildingBuildAbort(AbortValueD, fMovie);


}

void MainWindow::tasksBuildRemoveTask(int index)
{
    if(firstSetValue)
    {
        Task tTask = ((ItemBuildTask*)buildTaskBuildList->itemList.at(index))->task;
        if(!socketList.at(tTask.idPlace)->building.isExist && tTask.type == 2)
        {
            BuildingSocket *tSocket = socketList.at(tTask.idPlace);
            Building tBuilding(tTask.idPlace, 0, 0, travianWiki);
            tBuilding.isResource =false;
            tSocket->setBuilding( tBuilding );
            tSocket->refresh();

            buildBuildingList->refresh();
        }
        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuildRemoveTask(index);
    }
}

Task MainWindow::makeTaskBuildingUpgrade(int fIdPlace)
{
    BuildingSocket *tSocket = socketList.at(fIdPlace);

    int tLvl = tSocket->building.lvl+1;

    foreach( Task *i, accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->tasksBuild )
        if( i != 0 )
            if(i->type == 1 || i->type == 2 )
                if( i->idPlace == fIdPlace )
                    tLvl++;


    TaskBuildingUpgrade tTask(Building(tSocket->building.idPlace, tSocket->building.idBuilding, tLvl-1, mainBuildingLvl, travianWiki));
    tTask.lvl++;
    return tTask;
}

Task MainWindow::makeTaskBuildingBuild(int fIdPlace, int fIdBuilding)
{
    Building tBuilding(fIdPlace, fIdBuilding, 0, mainBuildingLvl, travianWiki);
    TaskBuildingBuild tTask( tBuilding );
    tTask.lvl++;
    tTask.buildOn = Time::currentTime();


    return tTask;
}


void MainWindow::loginFinished(QList<VillageTemp> fVillageTemp)
{
    comboBoxVillagesRefresh(fVillageTemp);

    if(!refreshedOn)
    {
        loopingRefresh();
        refreshedOn = true;
    }
}

void MainWindow::loginFirstConfig()
{
    firstSetValue = true;

    nation = accountList.at(comboBoxAccounts->currentIndex())->nation;

    mainBuildingLvl = accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->mainBuildingLvl;
    isCapital = accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->isCapital;
    villageIsActive = &(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->isActive);
    *villageIsActive = true;
}

void MainWindow::comboBoxVillagesRefresh(QList<VillageTemp> fVillagesTemp)
{
    comboBoxVillages->clear();

    foreach(VillageTemp i, fVillagesTemp)
        comboBoxVillages->addItem( i.name );

    buttonVillages->setText(comboBoxVillages->currentText());

}

void MainWindow::comboBoxVillagesRefresh(QList<Village *> fVillages)
{
    disconnect(comboBoxVillages, SIGNAL(indexChanged(int)), this, SLOT(villageChanged(int)));

    comboBoxVillages->clear();

    foreach(Village *i, fVillages)
        comboBoxVillages->addItem( i->name );

    buttonVillages->setText(comboBoxVillages->currentText());

    connect(comboBoxVillages, SIGNAL(indexChanged(int)), this, SLOT(villageChanged(int)));


}

void MainWindow::villageRefreshed(int fIdAccount, int fIdVillage)
{
    if(fIdAccount == comboBoxAccounts->currentIndex() && fIdVillage == comboBoxVillages->currentIndex())
        takeFromThreadVillage();
}

void MainWindow::tasksBuildChanged(int fIdAccount, int fIdVillage)
{
    if(fIdAccount == comboBoxAccounts->currentIndex() && fIdVillage == comboBoxVillages->currentIndex())
    {
        QTimer::singleShot(10, this, SLOT(takeFromThreadTasksBuild()));
        waitForLocker.exec();
    }
}

void MainWindow::takeFromThreadVillage()
{
    if(!firstSetValue)
        loginFirstConfig();

    village->setName( *(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())) );

    QTimer::singleShot(10, this, SLOT(takeFromThreadResource()));
    waitForLocker.exec();

    QTimer::singleShot(10, this, SLOT(takeFromThreadBuilding()));
    waitForLocker.exec();

    QTimer::singleShot(10, this, SLOT(takeFromThreadTasksBuild()));
    waitForLocker.exec();

    *villageIsActive = false;
    villageIsActive = &(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->isActive);
    *villageIsActive = true;
}

void MainWindow::takeFromThreadResource()
{
    if( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->setLockResourceTo(3) )
    {
        village->setResource(*(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())));

        setResources();

        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->releaseLockResource();

        refreshResources();
        waitForLocker.quit();
    }else
        QTimer::singleShot(50, this, SLOT(takeFromThreadResource()));
}

void MainWindow::takeFromThreadBuilding()
{
    if( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->setLockBuildingTo(3) )
    {
        village->setBuilding(*(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())));

        setBuildingList();
        setConstructionItems();

        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->releaseLockBuilding();

        mainBuildingLvl = village->mainBuildingLvl;
        isCapital = village->isCapital;

        refreshConstructionItems();
        refreshBuildingList();
        buildBuildingMap->setBackGround();
        waitForLocker.quit();

    }else
        QTimer::singleShot(50, this, SLOT(takeFromThreadBuilding()));
}

void MainWindow::takeFromThreadTasksBuild()
{
    //QMessageBox::information(0,"",QString::number( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->lockTasksBuild ));
    if( accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->setLockTasksBuildTo(3) )
    {
        village->setTasksBuild(*(accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())));

        setTaskBuildList();

        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->releaseLockTasksBuild();

        refreshTaskBuildList();
        waitForLocker.quit();

    }else
        QTimer::singleShot(50, this, SLOT(takeFromThreadTasksBuild()));

}


void MainWindow::loopingRefresh()
{

    if(firstSetValue)
    {
        refreshAll();
    }

    QTimer::singleShot(5000, this, SLOT(loopingRefresh()));
}

void MainWindow::buttonAccountsClicked()
{
    if(comboBoxAccounts->count())
        comboBoxAccounts->exec();
}

void MainWindow::buttonVillagesClicked()
{
    if(comboBoxVillages->count())
        comboBoxVillages->exec();
}

void MainWindow::buttonFilterClicked()
{
    DialogShows tDialog(this);

    tDialog.showCanUpgrade = buildBuildingList->showCanUpgrade;
    tDialog.showCantUpgrade = buildBuildingList->showCantUpgrade;
    tDialog.showInfrastructure = buildBuildingList->showInfrastructure;
    tDialog.showResource = buildBuildingList->showResource;

    tDialog.exec();

    if(tDialog.save)
    {
        buildBuildingList->showCantUpgrade = tDialog.showCantUpgrade;
        buildBuildingList->showCanUpgrade = tDialog.showCanUpgrade;
        buildBuildingList->showInfrastructure = tDialog.showInfrastructure;
        buildBuildingList->showResource = tDialog.showResource;
        buildBuildingList->refresh();

    }
}

void MainWindow::accountChangedStaf()
{
    nation = accountList.at(comboBoxAccounts->currentIndex())->nation;

    comboBoxVillagesRefresh( accountList.at(comboBoxAccounts->currentIndex())->villages);
    villageChanged(0);

}

void MainWindow::accountChanged(int index)
{
    if(index >=0 && accountList.at(index)->isLogin)
    {
        accountChangedStaf();
    }

    buttonAccounts->setText(comboBoxAccounts->currentText());

}

void MainWindow::villageChangedStaf()
{
    // dupa
}

void MainWindow::villageChanged(int index)
{
    if(index >=0 && firstSetValue)
    {
        takeFromThreadVillage();
        villageChangedStaf();
        buttonVillages->setText(comboBoxVillages->currentText());
    }
}

void MainWindow::buildBuildingMapChangedTo(bool fResources)
{
    if(firstSetValue)
        buildBuildingList->changedTo(fResources);

}

void MainWindow::on_actionAccounts_triggered()
{
    AccountManager tDialog(this, accountList);
    //tDialog.setStyleSheet("border-color: white");
    tDialog.travianWiki = travianWiki;
    tDialog.socketList = &socketList;
    tDialog.serverTypes = serverTypes;
    tDialog.setLanguage( &activeLanguage );
    tDialog.exec();

    if(tDialog.save )
    {
        firstSetValue = false;

        accountList = tDialog.accountList;
        buttonAccounts->setText("");
        buttonVillages->setText("");
        comboBoxAccounts->clear();
        comboBoxVillages->clear();

        if(tDialog.accountList.count())
        {
            disconnect(comboBoxVillages, SIGNAL(indexChanged(int)), this, SLOT(villageChanged(int)));

            accountList.clear();
            for(int a=0; a<tDialog.accountList.count(); a++)
            {
                accountList.append(tDialog.accountList.at(a));
                comboBoxAccounts->addItem(tDialog.accountList.at(a)->login);
                accountList.at(a)->idAccount = a;
            }

            if(accountList.count())
            {
                connect(accountList.at(0), SIGNAL(loginFinished(QList<VillageTemp>)), this, SLOT(loginFinished(QList<VillageTemp>)));

                if(accountList.at(0)->isLogin)
                    firstSetValue = true;
            }

            foreach(Account *i, accountList)
            {
                connect(i, SIGNAL(setStatusOn(bool)), this, SLOT(setStatusOn(bool)));
                connect(i, SIGNAL(villageRefreshed(int,int)), this, SLOT(villageRefreshed(int,int)));
                connect(i, SIGNAL(tasksBuildChanged(int,int)), this, SLOT(tasksBuildChanged(int,int)));

                if(!i->isLogin)
                {
                    i->XMLDocument = &XMLDocument;
                    i->XMLAccounts = &XMLAccounts;
                    i->onAndroid = &onAndroid;
                    i->Login();
                }
            }

            buttonAccounts->setText(comboBoxAccounts->currentText());
            connect(comboBoxVillages, SIGNAL(indexChanged(int)), this, SLOT(villageChanged(int)));

            villageChanged(0);
        }

    }

}

void MainWindow::on_actionRefresh_Village_triggered()
{
    if(firstSetValue)
        accountList.at(comboBoxAccounts->currentIndex())->villages.at(comboBoxVillages->currentIndex())->addRefreshRequest();
}

void MainWindow::on_actionRefresh_Account_triggered()
{
    if(firstSetValue)
        for(int i=0; i<comboBoxVillages->count(); i++)
           accountList.at(comboBoxAccounts->currentIndex())->villages.at(i)->addRefreshRequest();

}

void MainWindow::on_actionRefresh_Accounts_triggered()
{
    if(firstSetValue)
        for(int a=0; a<comboBoxAccounts->count(); a++)
            for(int i=0; i<accountList.at(a)->villages.count(); i++)
               accountList.at(a)->villages.at(i)->addRefreshRequest();

}

void MainWindow::on_actionInfo_triggered()
{
    DialogInfo tDialog(this);
    tDialog.exec();
}

void MainWindow::on_actionLanguage_triggered()
{
    DialogLanguages tDialog(this);

    foreach(Language *i, languages)
        tDialog.comboBox->addItem(QIcon(QString(":/Data/Language/%1.PNG").arg(i->shortCut)), i->name);

    int tIndex = activeLanguage->index;
    tDialog.comboBox->setCurrentIndex( activeLanguage->index );
    tDialog.exec();

    if(tDialog.save)
        if(tIndex != tDialog.comboBox->currentIndex())
            changeLanguage(tDialog.comboBox->currentIndex());

}
