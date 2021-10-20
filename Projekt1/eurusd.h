#ifndef EURUSD_H
#define EURUSD_H

#include <QDialog>

namespace Ui {
class EURUSD;
}

class EURUSD : public QDialog
{
    Q_OBJECT

public:
    explicit EURUSD(QWidget *parent = nullptr);
    ~EURUSD();

private:
    Ui::EURUSD *ui;
};

#endif // EURUSD_H
