#ifndef BUTTON_H
#define BUTTON_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMessageBox>

class Button : public QFrame
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = 0);
    
    QLabel label;
    QVBoxLayout layout;
    int framePoliceIndex;

    void setText(QString fText);
    void setScaledContents(bool fBool);
    void setMovie(QMovie *fMovie);

    void setFramePolice(int fIndex);

private:
    void mouseReleaseEvent(QMouseEvent *e);

    bool event(QEvent *e);

signals:
    void clicked();
    void clicked(Button*);
    
};

#endif // BUTTON_H
