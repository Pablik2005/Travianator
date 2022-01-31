#include "servertype.h"

ServerType::ServerType(QObject *parent, QString fName):
    QObject(parent)
{
    name = fName;
}
