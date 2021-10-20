#include "eurusd.h"
#include "ui_eurusd.h"

EURUSD::EURUSD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EURUSD)
{
    ui->setupUi(this);
}

EURUSD::~EURUSD()
{
    delete ui;
}
