#include <QtPrintSupport/QPrinter>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "timeplot.h"
#include "baseplot.h"
#include "axis.h"
#include "ticker.h"
#include "grid.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QApplication app(argc, argv);

    qmlRegisterType<QmlQCustomPlot::TimePlot>("QmlQCustomPlot", 1, 0, "TimePlot");
    qmlRegisterType<QmlQCustomPlot::BasePlot>("QmlQCustomPlot", 1, 0, "BasePlot");
    qmlRegisterUncreatableType<QmlQCustomPlot::Axis>("QmlQCustomPlot", 1, 0, "Axis", "");
    qmlRegisterUncreatableType<QmlQCustomPlot::Ticker>("QmlQCustomPlot", 1, 0, "Ticker", "");
    qmlRegisterUncreatableType<QmlQCustomPlot::Grid>("QmlQCustomPlot", 1, 0, "Grid", "");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}