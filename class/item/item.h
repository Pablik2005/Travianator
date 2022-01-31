#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QMessageBox>

class Item : public QWidget
{
    Q_OBJECT
public:
    explicit Item(QWidget *parent = 0);
    bool hidden;
    
signals:
    void mouseMoveSignal(QMouseEvent *e);
    void mousePressSignal(QMouseEvent *e);
    void mouseReleaseSignal(QMouseEvent *);

    
public slots:

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // ITEM_H
