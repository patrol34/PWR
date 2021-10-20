#ifndef PROJEKT_H
#define PROJEKT_H

#include <QMainWindow>
#include "projekt2.h"
#include "usdchf.h"
#include "eurusd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class projekt; }
QT_END_NAMESPACE

class projekt : public QMainWindow
{
    Q_OBJECT

public:
    projekt(QWidget *parent = nullptr);
    ~projekt();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::projekt *ui;
    projekt2 *Projekt2;
    EURUSD *eurusd;
    USDCHF *usdchf;
};
#endif // PROJEKT_H
