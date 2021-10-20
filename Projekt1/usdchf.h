#ifndef USDCHF_H
#define USDCHF_H

#include <QDialog>

namespace Ui {
class USDCHF;
}

class USDCHF : public QDialog
{
    Q_OBJECT

public:
    explicit USDCHF(QWidget *parent = nullptr);
    ~USDCHF();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::USDCHF *ui;
};

#endif // USDCHF_H
