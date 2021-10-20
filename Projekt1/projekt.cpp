#include "projekt.h"
#include "ui_projekt.h"
#include <QMessageBox>
#include <QDebug>

projekt::projekt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::projekt)
{
    ui->setupUi(this);
    connect(ui->lineEdit_2,SIGNAL(textChanged(QString)),
            ui->pushButton_3, SLOT(setWindowTitle(QString)));
}

projekt::~projekt()
{
    delete ui;
}


void projekt::on_pushButton_2_clicked()
{
    hide();
    Projekt2 = new projekt2(this);
    Projekt2->show();
}


void projekt::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "projekt2", "Czy na pewno chcesz zakończyć działanie programu?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }else{
        qDebug()<<"Anulowano próbę zamknięcia aplikacji";
    }
}

