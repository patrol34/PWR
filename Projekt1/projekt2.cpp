#include "projekt2.h"
#include "ui_projekt2.h"


projekt2::projekt2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::projekt2)
{
    ui->setupUi(this);
}

projekt2::~projekt2()
{
    delete ui;
}

void projekt2::on_pushButton_clicked()
{
    hide();
    eurusd = new EURUSD(this);
    eurusd->show();
}

void projekt2::on_pushButton_2_clicked()
{
    hide();
    usdchf = new USDCHF(this);
    usdchf->show();
}

void projekt2::on_pushButton_3_clicked()
{
    hide();
    GBPAUD = new gbpaud(this);
    GBPAUD->show();
}
