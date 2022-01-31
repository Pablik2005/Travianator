#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QLabel>
#include <QListWidget>
#include <QtGui>
#include <QtCore>

class ComboBox : public QDialog
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = 0);

    QComboBox *comboBox;

    void setTitle(QString fTitle);
    void addItem(QString fItem);
    void clear();

    QString currentText();
    int currentIndex();
    int count();
    

signals:
    void indexChanged(int);
    
public slots:
    void rowSelected(int index);

public:
    void exec();
    
};

#endif // COMBOBOX_H
