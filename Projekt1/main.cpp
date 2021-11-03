#include "projekt.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QRandomGenerator64>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Projekt1_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    projekt w;
    w.show();
    return a.exec();

}
