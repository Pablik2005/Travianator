#ifndef SERVERTYPE_H
#define SERVERTYPE_H

#include <QString>
#include <QObject>
#include <QTextCodec>

class ServerType: public QObject
{
    Q_OBJECT

public:
    ServerType(QObject *parent, QString fName);

    QString name;

    QString Rzymianie;
    QString Galowie;
    QString Germanie;

    QString Wood;
    QString Clay;
    QString Iron;
    QString Corn;

    QString FindBuildingLevel;
    QString FindBuildingFullUpgraded;
    QString FindBuildingIsFullUpgrading;

    QString FindTimeToEndUpgradingCancel;

    QList<QString> Buildings;
    QList<QString> BuildingsHTML;
};

#endif // SERVERTYPE_H
