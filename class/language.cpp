#include "language.h"

Language::Language(QObject *parent, QString fName, QString fShortCut):
    QObject(parent)
{
    name = fName;
    shortCut = fShortCut;

}
