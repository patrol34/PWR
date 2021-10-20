#include <QPixmap>
#include <QCoreApplication>
#include <QRandomGenerator64>
#include <QDebug>
#include "usdchf.h"
#include "ui_usdchf.h"
#include "projekt.h"
#include "projekt2.h"

projekt2 *Projekt2;

USDCHF::USDCHF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::USDCHF)
{
    ui->setupUi(this);
}

USDCHF::~USDCHF()
{
    delete ui;
}

void USDCHF::on_pushButton_clicked()
{
    hide();
    Projekt2 = new projekt2(this);
    Projekt2->show();
}

void USDCHF::on_pushButton_2_clicked()
{
    /*int argc;
    char *argv[1];

    QCoreApplication a(argc, argv);

    std::uniform_int_distribution<int> distribution(1,2);

    double value = distribution(*QRandomGenerator::global());
    qDebug()<<value;
    for(int i=0; i<1; i++){
        value = distribution(*QRandomGenerator::global());
        ui->label_6->setText(QString::number(value));
    }*/

}

