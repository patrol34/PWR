#ifndef GBPAUD_H
#define GBPAUD_H

#include <QDialog>

namespace Ui {
class gbpaud;
}

class gbpaud : public QDialog
{
    Q_OBJECT

public:
    explicit gbpaud(QWidget *parent = nullptr);
    ~gbpaud();

private:
    Ui::gbpaud *ui;
};

#endif // GBPAUD_H
