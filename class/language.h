#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QIcon>

class Language: public QObject
{
    Q_OBJECT

public:
    Language(QObject *parent, QString fName, QString fShortCut);

    QString name;
    QString shortCut;
    int index;

    QString Rzymianie;
    QString Galowie;
    QString Germanie;

    QString Capitol;
    QString NotInCapitol;

    QList<QString> Buildings;

    QString MenuRefresh;
    QString MenuRefreshVillage;
    QString MenuRefreshAccount;
    QString MenuRefreshAccounts;

    QString MenuOptions;
    QString MenuOptionsAccounts;
    QString MenuOptionsLanguage;

    QString BuildFilter;

    QString BuildMenuBuildNow;
    QString BuildMenuUpgradeNow;
    QString BuildMenuAddTask;
    QString BuildMenuAddTasks;
    QString BuildMenuAddTaskOn;
    QString BuildMenuAddTasksOn;

    QString AccoutManagerTitle;
    QString AccoutManagerLogin;
    QString AccoutManagerPassword;
    QString AccoutManagerServer;
    QString AccoutManagerAdd;
    QString AccoutManagerOk;
    QString AccoutManagerCancel;
    QString AccoutManagerDel;
    QString AccoutManagerClear;

    QString DialogGetTimeTitle;
    QString DialogGetTimeOn;
    QString DialogGetTimeFor;
    QString DialogGetTimeYear;
    QString DialogGetTimeMonth;
    QString DialogGetTimeDay;
    QString DialogGetTimeHour;
    QString DialogGetTimeMinute;
    QString DialogGetTimeSecound;

    QString DialogLoadTaskFromFileTittle;
    QString DialogLoadTaskFromFileMessage;

    QString DialogCloseAppTittle;
    QString DialogCloseAppMessage;
};

#endif // LANGUAGE_H
