#ifndef BUTTONLIST_H
#define BUTTONLIST_H

#include <QDialog>
#include "button.h"
#include <QMessageBox>
#include <QTimer>

class ButtonList : public QDialog
{
    Q_OBJECT
public:
    explicit ButtonList(QWidget *parent = 0);
    
    int mIndex;
    int mCount;
    int execCount;
    QList<Button*> buttonList;

    void setTitle(QString fTitle);
    void addItem(QString fItem);
    void clear();

    QString currentText();
    int currentIndex();
    int count();

public slots:
    void closeSlot(Button*fButton);

public:
    void exec();
    
};

#endif // BUTTONLIST_H
