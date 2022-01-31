#include "combobox.h"

ComboBox::ComboBox(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(250,45);
    this->setMaximumSize(250,45);

    this->setStyleSheet("border: 1px solid black");
    comboBox = new QComboBox(this);

    comboBox->setGeometry(0,0,250,45);

    comboBox->setStyleSheet("QComboBox QAbstractItemView { color : black; }");
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(rowSelected(int)));
    connect(comboBox, SIGNAL(activated(int)), this, SLOT(close()));

    QFont tFont;
    tFont.setPixelSize(16);

    comboBox->setFont(tFont);
}



void ComboBox::setTitle(QString fTitle)
{
    this->setWindowTitle( fTitle );
}

void ComboBox::addItem(QString fItem)
{
    comboBox->addItem(fItem);
}

void ComboBox::clear()
{
    comboBox->clear();
}

QString ComboBox::currentText()
{
    return comboBox->currentText();
}

int ComboBox::currentIndex()
{
    return comboBox->currentIndex();
}

int ComboBox::count()
{
    return comboBox->count();
}


void ComboBox::rowSelected(int index)
{

    emit indexChanged(index);

}

void ComboBox::exec()
{
    this->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 250, 45 );
    QDialog::exec();

}
