#include "button.h"

Button::Button(QWidget *parent) :
    QFrame(parent)
{
    this->setLayout(&layout);
    layout.addWidget(&label);
    layout.setMargin(0);

    QFont tFont;
    tFont.setPixelSize(14);

    label.setFont(tFont);

    this->setFrameShadow(QFrame::Raised);

}

void Button::setText(QString fText)
{
    label.setText(fText);
}

void Button::setScaledContents(bool fBool)
{
    label.setScaledContents(fBool);
}

void Button::setMovie(QMovie *fMovie)
{
    label.setMovie(fMovie);
}

void Button::setFramePolice(int fIndex)
{
    framePoliceIndex = fIndex;

    if(framePoliceIndex == 1)
    {
        this->setFrameShape(QFrame::WinPanel);
        label.setAlignment(Qt::AlignCenter);
    }
}


void Button::mouseReleaseEvent(QMouseEvent *e)
{

    emit clicked();
    emit clicked(this);

}


bool Button::event(QEvent *e)
{
    if(framePoliceIndex == 2)
    {
        if(e->type() == QEvent::Enter)
        {
            this->setFrameShape(QFrame::WinPanel);

            return true;
        }else if(e->type() == QEvent::Leave)
        {
            this->setFrameShape(QFrame::NoFrame);

            return true;
        }
    }
    QFrame::event(e);

    return false;
}
