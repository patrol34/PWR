#ifndef PROJEKT_H
#define PROJEKT_H

#include <QMainWindow>

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
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_label_12_linkActivated(const QString &link);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::projekt *ui;
};
#endif // PROJEKT_H
