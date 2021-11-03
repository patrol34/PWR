#include "projekt.h"
#include "ui_projekt.h"
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator64>
#include <QTime>

projekt::projekt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::projekt)
{
    ui->setupUi(this);
    ui->comboBox_2->addItem("$");
    ui->comboBox_2->addItem("€");
    ui->comboBox_2->addItem("zł");
    ui->comboBox->addItem("1");
    ui->comboBox->addItem("0.1");
    ui->comboBox->addItem("0.01");
}

projekt::~projekt()
{
    delete ui;
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

void projekt::on_pushButton_2_clicked()
{
    QString nazwa = ui->lineEdit_2->text();
    ui->label_7->setText(nazwa);

    QString depo = ui->lineEdit->text();
    ui->label_10->setText(depo);

    ui->label_11->setText(ui->comboBox_2->currentText());

    ui->label_6->setText("Połączono");

    ui->groupBox->hide();

    ui->tabWidget->setGeometry(20,40,900,540);
}









void projekt::on_pushButton_5_clicked()
{
    QString lot = ui->comboBox->currentText();

    if(lot.compare("1") == 0){
    std::uniform_int_distribution<int>distribution(0,1000);

    double value = distribution(*QRandomGenerator::global());
    int w = value-500;
    ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
    if(w>0){
    int n = w*0.81;
    ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
    }
    else{
        ui->label_16->setText("Przegrana");
    }
    }
    else if(lot.compare("0.1") == 0){
        std::uniform_int_distribution<int>distribution(0,100);

        double value = distribution(*QRandomGenerator::global());
        int w = value-50;
        ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
        if(w>0){
        int n = w*0.81;
        ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
        }
        else{
            ui->label_16->setText("Przegrana");
        }
    }
    else{
        std::uniform_int_distribution<int>distribution(0,10);

        double value = distribution(*QRandomGenerator::global());
        int w = value-5;
        ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
        if(w>0){
        int n = w*0.81;
        ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
        }
        else{
            ui->label_16->setText("Przegrana");
        }
    }
}


void projekt::on_pushButton_4_clicked()
{
    QString lot = ui->comboBox->currentText();

    if(lot.compare("1") == 0){
    std::uniform_int_distribution<int>distribution(0,1000);

    double value = distribution(*QRandomGenerator::global());
    int w = value-500;
    ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
        if(w>0){
        int n = w*0.81;
        ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
        }
        else{
            ui->label_16->setText("Przegrana");
        }
    }
    else if(lot.compare("0.1") == 0){
        std::uniform_int_distribution<int>distribution(0,100);

        double value = distribution(*QRandomGenerator::global());
        int w = value-50;
        ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
        if(w>0){
        int n = w*0.81;
        ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
        }
        else{
            ui->label_16->setText("Przegrana");
        }
    }
    else{
        std::uniform_int_distribution<int>distribution(0,10);

        double value = distribution(*QRandomGenerator::global());
        int w = value-5;
        ui->label_13->setText(QString::number(w) + ui->comboBox_2->currentText());
        if(w>0){
        int n = w*0.81;
        ui->label_16->setText(QString::number(n) + ui->comboBox_2->currentText());
        }
        else{
            ui->label_16->setText("Przegrana");
        }
    }
}


void projekt::on_pushButton_3_clicked()
{
    QMessageBox::information(this, "Co to jest LOT?", "Lot jest standardową jednostką określającą wolumen transakcji na rynkach finansowych. Lot można kojarzyć jako transakcję pakietową (paczkę), która zawiera w sobie daną liczbę jednostek instrumentu. Standardem jest transakcja o wartości 100 000 jednostek waluty bazowej na rynku walutowym. Mini lot – 0.1 lota 10 000 jednostek waluty bazowej Mikro lot – 0.01 lota1 000 jednostek waluty bazowej  ");
}

