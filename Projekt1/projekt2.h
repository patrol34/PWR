#ifndef PROJEKT2_H
#define PROJEKT2_H

#include <QDialog>
#include "usdchf.h"
#include "eurusd.h"
#include "gbpaud.h"

namespace Ui {
class projekt2;
}

class projekt2 : public QDialog
{
    Q_OBJECT

public:
    explicit projekt2(QWidget *parent = nullptr);
    ~projekt2();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::projekt2 *ui;
    USDCHF *usdchf;
    EURUSD *eurusd;
    gbpaud *GBPAUD;

};

#endif // PROJEKT2_H
