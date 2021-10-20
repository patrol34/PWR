#include "gbpaud.h"
#include "ui_gbpaud.h"

gbpaud::gbpaud(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gbpaud)
{
    ui->setupUi(this);
}

gbpaud::~gbpaud()
{
    delete ui;
}
