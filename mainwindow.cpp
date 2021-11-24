#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>
#include <QtCharts>
#include <QCoreApplication>
#include <QtCore>
#include <QtGui>


CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : QTextStream(device)
{
}

CandlestickDataReader::~CandlestickDataReader()
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QCandlestickSet *CandlestickDataReader::readCandlestickSet()
{
    QString line = readLine();
    if(line.startsWith("#") || line.isEmpty())
        return 0;

    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (strList.count() != 5)
        return 0;

    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();

    QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
    candlestickSet->setOpen(open);
    candlestickSet->setHigh(high);
    candlestickSet->setLow(low);
    candlestickSet->setClose(close);

    return candlestickSet;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , depo()
{
    ui->setupUi(this);
    this->setWindowTitle("Forex PwrTrader");

    ui->comboBox_3->addItem("1");
    ui->comboBox_3->addItem("0.1");
    ui->comboBox_3->addItem("0.01");

    ui->comboBox_2->addItem("1");
    ui->comboBox_2->addItem("0.1");
    ui->comboBox_2->addItem("0.01");

    ui->comboBox_6->addItem("1");
    ui->comboBox_6->addItem("0.1");
    ui->comboBox_6->addItem("0.01");

    ui->comboBox_7->addItem("1");
    ui->comboBox_7->addItem("0.1");
    ui->comboBox_7->addItem("0.01");

    ui->comboBox_4->addItem("$");
    ui->comboBox_4->addItem("€");
    ui->comboBox_4->addItem("zł");

    ui->comboBox_5->addItem("USDCHF");
    ui->comboBox_5->addItem("AUDUSD");
    ui->comboBox_5->addItem("XAUUSD");

    ui->comboBox->addItem("1:5");
    ui->comboBox->addItem("1:30");
    ui->comboBox->addItem("1:500");


    QCandlestickSeries *acmeSeries = new QCandlestickSeries();
    acmeSeries->setName("USDCHF");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));

                            QCandlestickSeries *acmeSeries1 = new QCandlestickSeries();
                            acmeSeries1->setName("AUDUSD");
                            acmeSeries1->setIncreasingColor(QColor(Qt::green));
                            acmeSeries1->setDecreasingColor(QColor(Qt::red));

                                                        QCandlestickSeries *acmeSeries2 = new QCandlestickSeries();
                                                        acmeSeries2->setName("XAUUSD");
                                                        acmeSeries2->setIncreasingColor(QColor(Qt::green));
                                                        acmeSeries2->setDecreasingColor(QColor(Qt::red));


    QFile acmeData("../Projekt1/usdchfdata.txt");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
           QMessageBox::warning(this,"title","File not open");

                                QFile acmeData1("../Projekt1/audusddata.txt");
                                if (!acmeData1.open(QIODevice::ReadOnly | QIODevice::Text))
                                       QMessageBox::warning(this,"title","File not open");

                                                        QFile acmeData2("../Projekt1/xauusddata.txt");
                                                        if (!acmeData2.open(QIODevice::ReadOnly | QIODevice::Text))
                                                               QMessageBox::warning(this,"title","File not open");

    QStringList categories;
                     QStringList categories1;
                                 QStringList categories2;

    CandlestickDataReader dataReader(&acmeData);
    while(!dataReader.atEnd()){
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if(set){
            acmeSeries->append(set);
            categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
        }
    }

                                    CandlestickDataReader dataReader1(&acmeData1);
                                    while(!dataReader1.atEnd()){
                                        QCandlestickSet *set1 = dataReader1.readCandlestickSet();
                                        if(set1){
                                            acmeSeries1->append(set1);
                                            categories1 << QDateTime::fromMSecsSinceEpoch(set1->timestamp()).toString("dd");
                                        }
                                    }

                                                                CandlestickDataReader dataReader2(&acmeData2);
                                                                while(!dataReader2.atEnd()){
                                                                    QCandlestickSet *set2 = dataReader2.readCandlestickSet();
                                                                    if(set2){
                                                                        acmeSeries2->append(set2);
                                                                        categories2 << QDateTime::fromMSecsSinceEpoch(set2->timestamp()).toString("dd");
                                                                    }
                                                                }

    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->setTitle("Para walutowa USDCHF [Interwał 1D]");
    chart->setAnimationOptions(QChart::SeriesAnimations);

                                    QChart *chart1 = new QChart();
                                    chart1->addSeries(acmeSeries1);
                                    chart1->setTitle("Para walutowa AUDUSD [Interwał 1D]");
                                    chart1->setAnimationOptions(QChart::SeriesAnimations);

                                                                QChart *chart2 = new QChart();
                                                                chart2->addSeries(acmeSeries2);
                                                                chart2->setTitle("Surowiec XAUUSD (Złoto) [Interwał 1D]");
                                                                chart2->setAnimationOptions(QChart::SeriesAnimations);


    chart->createDefaultAxes();
            chart1->createDefaultAxes();
                 chart2->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

                                QBarCategoryAxis *axisX1 = qobject_cast<QBarCategoryAxis *>(chart1->axes(Qt::Horizontal).at(0));
                                axisX1->setCategories(categories1);

                                                            QBarCategoryAxis *axisX2 = qobject_cast<QBarCategoryAxis *>(chart2->axes(Qt::Horizontal).at(0));
                                                            axisX2->setCategories(categories2);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.0001);
    axisY->setMin(axisY->min() * 0.999);

                                        QValueAxis *axisY1 = qobject_cast<QValueAxis *>(chart1->axes(Qt::Vertical).at(0));
                                        axisY1->setMax(axisY1->max() * 1.0001);
                                        axisY1->setMin(axisY1->min() * 0.999);

                                                            QValueAxis *axisY2 = qobject_cast<QValueAxis *>(chart2->axes(Qt::Vertical).at(0));
                                                            axisY2->setMax(axisY2->max() * 1.0001);
                                                            axisY2->setMin(axisY2->min() * 0.999);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

                    chart1->legend()->setVisible(true);
                    chart1->legend()->setAlignment(Qt::AlignBottom);

                                chart2->legend()->setVisible(true);
                                chart2->legend()->setAlignment(Qt::AlignBottom);



    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
    chartView->resize(730, 380);

                                        QChartView *chartView1 = new QChartView(chart1);
                                        chartView1->setRenderHint(QPainter::Antialiasing);
                                        chartView1->setParent(ui->horizontalFrame2);
                                        chartView1->resize(730, 380);

                                                                QChartView *chartView2 = new QChartView(chart2);
                                                                chartView2->setRenderHint(QPainter::Antialiasing);
                                                                chartView2->setParent(ui->horizontalFrame3);
                                                                chartView2->resize(730, 380);



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    depo = ui->lineEdit_2->text().toInt();
    ui->label_21->setText(QString::number(depo) + ui->comboBox_4->currentText());
    ui->label_24->setText(QString::number(depo) + ui->comboBox_4->currentText());

    QString nazwa = ui->lineEdit_3->text();
    ui->label_8->setText(nazwa);

    ui->label_46->setText("Zalogowany");

    ui->groupBox_2->hide();
    ui->tabWidget->setGeometry(20,50,761,491);
}

void MainWindow::on_pushButton_clicked()
{
    QString lot = ui->comboBox_2->currentText();
    std::uniform_int_distribution<int>distribution(1800,1804);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_28->setText(QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        std::uniform_int_distribution<int>distribution(0,wynik1);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik1/2;
        int w = value - a;
        int n = w * 0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;


        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString lot = ui->comboBox_2->currentText();
    std::uniform_int_distribution<int>distribution(1800,1804);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_28->setText(QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        int wynik = wynik1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;


        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_25->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_20->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_25->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString lot = ui->comboBox_6->currentText();
    std::uniform_int_distribution<int>distribution(73200,73260);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_29->setText("0." + QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        int wynik = wynik1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString lot = ui->comboBox_6->currentText();
    std::uniform_int_distribution<int>distribution(73200,73260);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_29->setText("0." + QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        int wynik = wynik1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_30->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_34->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_30->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}



void MainWindow::on_pushButton_7_clicked()
{
    QString lot = ui->comboBox_7->currentText();
    std::uniform_int_distribution<int>distribution(92680,92740);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_37->setText("0." + QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        int wynik = wynik1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - (1.5*a);
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - (1.25*a);
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}
void MainWindow::on_pushButton_8_clicked()
{
    QString lot = ui->comboBox_7->currentText();
    std::uniform_int_distribution<int>distribution(92680,92740);
    int kurs = distribution(*QRandomGenerator::global());
    ui->label_37->setText("0." + QString::number(kurs));

    if(lot.compare("1")==0){
        int wynik1 = depo;
        int wynik = wynik1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - (1.5*a);
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.1")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.1;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - (1.25*a);
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }

    if(lot.compare("0.01")==0){
        int wynik1 = depo;
        int wynik = wynik1*0.01;
        std::uniform_int_distribution<int>distribution(0,wynik);
        int value = distribution(*QRandomGenerator::global());
        int a = wynik/2;
        int w = value - a;
        int n = w*0.81;
        depo = wynik1+w;

        if(depo>0){
            if(w>0){
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
                ui->label_38->setText(QString::number(n) + ui->comboBox_4->currentText());
            }
            else{
                wynik1 = wynik1 + w;
                ui->label_42->setText(QString::number(w) + ui->comboBox_4->currentText());
                ui->label_38->setText(" - ");
                ui->label_21->setText(QString::number(wynik1) + ui->comboBox_4->currentText());
            }
        }
        else{
            QMessageBox::critical(this, "Forex PwrTrader", "Brak pieniędzy na koncie. Koniec gry.");
            QApplication::quit();
       }
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    QString lawer = ui->comboBox->currentText();
    QString depozyt = ui->lineEdit_2->text();
    int oblicz = depozyt.toInt();

    if(lawer.compare("1:5")==0){
        oblicz = oblicz * 5;
        ui->label_6->setText(QString::number(oblicz) + ui->comboBox_4->currentText());
    }
    if(lawer.compare("1:30")==0){
        oblicz = oblicz * 30;
        ui->label_6->setText(QString::number(oblicz) + ui->comboBox_4->currentText());
    }
    if(lawer.compare("1:500")==0){
        oblicz = oblicz * 500;
        ui->label_6->setText(QString::number(oblicz) + ui->comboBox_4->currentText());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString depozyt = ui->lineEdit_2->text();
    int wynik = depozyt.toInt();
    ui->label_24->setText(QString::number(wynik));

    QString lotRyzyko = ui->comboBox_3->currentText();
    QString parawalutowa = ui->comboBox_5->currentText();

    if(parawalutowa.compare("XAUUSD")==0){
            if(wynik<=500){
                    if(lotRyzyko.compare("1")==0)
                        ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 372" + ui->comboBox_4->currentText() + "\nRyzyko transakcji WYSOKIE");
                    if(lotRyzyko.compare("0.1")==0)
                        ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 37,2" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                    if(lotRyzyko.compare("0.01")==0)
                        ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 3,72" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
            }
            if(wynik>501 && wynik<=2500){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 372" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 37,2" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 3,72" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");

            }
            if(wynik>2501){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 372" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 37,2" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 3,72" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
            }
    }

    if(parawalutowa.compare("USDCHF")==0){
            if(wynik<=500){
                    if(lotRyzyko.compare("1")==0)
                        ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\nRyzyko transakcji WYSOKIE");
                    if(lotRyzyko.compare("0.1")==0)
                        ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                    if(lotRyzyko.compare("0.01")==0)
                        ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
            }
            if(wynik>501 && wynik<=2500){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");

            }
            if(wynik>2501){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla pary walutowej USDCHF\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
            }
    }

    if(parawalutowa.compare("AUDUSD")==0){
            if(wynik<=500){
                    if(lotRyzyko.compare("1")==0)
                        ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\nRyzyko transakcji WYSOKIE");
                    if(lotRyzyko.compare("0.1")==0)
                        ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                    if(lotRyzyko.compare("0.01")==0)
                        ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
            }
            if(wynik>501 && wynik<=2500){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\nRyzyko transakcji ŚREDNIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla pary walutowej AUDUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\nRyzyko transakcji NISKIE");

            }
            if(wynik>2501){
                if(lotRyzyko.compare("1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 100" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.1")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 10" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
                if(lotRyzyko.compare("0.01")==0)
                    ui->textBrowser->setText("Dla surowca XAUUSD\nDla depozytu: " + depozyt + ui->comboBox_4->currentText() + "\nRyzyko w wysokości: " + ui->comboBox_3->currentText() + "\nlota, wynosi: 1" + ui->comboBox_4->currentText() + "\n\nRyzyko transakcji NISKIE");
            }
    }


}



void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Projekt1", "Czy na pewno chcesz zakończyć działanie programu?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            QApplication::quit();
        }else{
            qDebug()<<"Anulowano próbę zamknięcia aplikacji";
        }
}





void MainWindow::on_pushButton_11_clicked()
{
    QMessageBox::information(this, "Co to jest LOT?", "Lot jest standardową jednostką określającą wolumen transakcji na rynkach finansowych. Lot można kojarzyć jako transakcję pakietową (paczkę), która zawiera w sobie daną liczbę jednostek instrumentu. \nStandardem jest transakcja o wartości 100 000 jednostek waluty bazowej na rynku walutowym. \nMini lot – 0.1 lota 10 000 jednostek waluty bazowej \nMikro lot – 0.01 lota1 000 jednostek waluty bazowej  ");
}


void MainWindow::on_pushButton_13_clicked()
{
   QMessageBox::information(this, "Co to jest LOT?", "Lot jest standardową jednostką określającą wolumen transakcji na rynkach finansowych. Lot można kojarzyć jako transakcję pakietową (paczkę), która zawiera w sobie daną liczbę jednostek instrumentu. \nStandardem jest transakcja o wartości 100 000 jednostek waluty bazowej na rynku walutowym. \nMini lot – 0.1 lota 10 000 jednostek waluty bazowej \nMikro lot – 0.01 lota1 000 jednostek waluty bazowej  ");
}


void MainWindow::on_pushButton_12_clicked()
{
   QMessageBox::information(this, "Co to jest LOT?", "Lot jest standardową jednostką określającą wolumen transakcji na rynkach finansowych. Lot można kojarzyć jako transakcję pakietową (paczkę), która zawiera w sobie daną liczbę jednostek instrumentu. \nStandardem jest transakcja o wartości 100 000 jednostek waluty bazowej na rynku walutowym. \nMini lot – 0.1 lota 10 000 jednostek waluty bazowej \nMikro lot – 0.01 lota1 000 jednostek waluty bazowej  ");
}


void MainWindow::on_pushButton_15_clicked()
{
    QMessageBox::information(this, "Spread", "Spread – różnica pomiędzy kursem sprzedaży a kursem kupna aktywów.");
}


void MainWindow::on_pushButton_14_clicked()
{
    QMessageBox::information(this, "Spread", "Spread – różnica pomiędzy kursem sprzedaży a kursem kupna aktywów.");
}


void MainWindow::on_pushButton_16_clicked()
{
    QMessageBox::information(this, "Spread", "Spread – różnica pomiędzy kursem sprzedaży a kursem kupna aktywów.");
}

