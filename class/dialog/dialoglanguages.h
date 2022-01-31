#ifndef DIALOGLANGUAGES_H
#define DIALOGLANGUAGES_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class DialogLanguages;
}

class DialogLanguages : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogLanguages(QWidget *parent = 0);
    ~DialogLanguages();
    
    bool save;
    QComboBox *comboBox;

private slots:
    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::DialogLanguages *ui;
};

#endif // DIALOGLANGUAGES_H
