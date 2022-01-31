#ifndef ENUMS_H
#define ENUMS_H

#include <QString>
#include <QPoint>

enum NationType
{
    Rzymianie = 0,
    Germanie = 1,
    Galowie = 2

};

struct AccountTemp
{
    QString login;
    QString password;
    QString server;
    bool exist;
    void *account;
};

struct VillageTemp
{
    QPoint coordinates;
    QString name;
    int newdID;
};

struct BuildingName
{
    QString name;
    QString nameInHTML;
};


#endif // ENUMS_H
