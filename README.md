
<div align="center">
  <h1>QmlQCustomPlot</h1>
  <p>Based on QCustomPlot, a simple package that supports the use of Qml.</p>
  <p>
    <h3><span>English</span>&emsp;|&emsp;<a href="./README_zh-CN.md">简体中文</a></h3>
  </p>
  <p>
    <img src="https://img.shields.io/github/package-json/v/MrHulu/QmlQCustomPlot" alt="version">
    <img src="https://img.shields.io/github/stars/MrHulu/QmlQCustomPlot?style=social" alt="stars">
  </p>
</div>

___
# 🔔Quick Start 
## Build with CMake
Within your project directory, create a new folder, let's say you name it QmlQCustomPlot. The `src` directory from this repository acts as a standalone module; simply copy all files within the src folder into your `QmlQCustomPlot` directory. Afterwards, incorporate this module in the appropriate CMakeLists.txt file of your project.

## Build with qmake
Similarly, for qmake, create a directory named QmlQCustomPlot within your project folder. Copy all the files from src (excluding the CMakeLists.txt) into your newly created QmlQCustomPlot directory. Then, generate a QmlQCustomPlot.pri file within this directory with the following content:
```cmakelist
# QmlQCusomPlot.pri

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp *.cc)

QT += core gui quick widgets printsupport

QTPLUGIN += qmlplugin
QML_IMPORT_PATH = $$PWD
QML_FILE_EXTENSIONS += .qml

# Setting the C++ standard (C++11 is assumed to be used here, adjust as appropriate)
CONFIG += c++11

# Linking Qt libraries
LIBS += -lQt5Core \
        -lQt5Gui \
        -lQt5Quick \
        -lQt5Widgets \
        -lQt5PrintSupport

```
Next, include this .pri file in your .pro file, for example, if your project is named `MyProject.pro`, add the following line to that file:
```
# MyProject.pro

TEMPLATE = app
TARGET = MyProject

# Include QmlQCustomPlot modules
include(QmlQCusomPlot.pri)

# Other...

```
___
# 🔔Discussion Points
1. As of May 27th, 2024, native support for QML in QCustomPlot has not been implemented by the author. However, upon contacting them, they confirmed that implementation is underway but without a definitive timeline for release.

2. Although many properties in the QCustomPlot source code utilize `Q_PROPERTY`, the lack of signals hinders property binding support in QML. Wrapping QCustomPlot for QML usage requires substantial effort; I've managed to encapsulate a portion, but if it doesn't meet your requirements, modifying the source code directly might be a straightforward alternative.

3. For further references and potential solutions, check out the discussions at: https://www.qcustomplot.com/index.php/support/forum/172
___
# 🔔UML
```mermaid
classDiagram-v2

    Graph --|> QObject
    Axis --|> QObject
    Grid --|> QObject
    Ticker --|> QObject
    BasePlot --|> QQuickPaintedItem
    TimePlot --|> BasePlot
    BasePlot "1" --> "*" Graph
    BasePlot "1" --> "4" Axis
    Axis "1" --> "1" Grid
    Axis "1" --> "1" Ticker
    
    class BasePlot {
        - QCustomPlot* m_customPlot
        - QMap<QString, Graph*> m_graphs

        Q_PROPERTY (Axis* x READ x CONSTANT)
        Q_PROPERTY (Axis* x1 READ x1 CONSTANT)
        Q_PROPERTY (Axis* y READ y CONSTANT)
        Q_PROPERTY (Axis* y1 READ y1 CONSTANT)
        Q_PROPERTY (QVariantMap graphs READ graphs NOTIFY graphsChanged)
        Q_PROPERTY (QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

        + BasePlot(QQuickItem* parent)
        + ~BasePlot()
        + void addGraph(const QString& key)
        + void removeGraph(const QString& key)
        + void rescaleAxes(bool onlyVisiblePlottables=false)
        + void paint(QPainter *painter) override
        + QCustomPlot *customPlot() const
        + const QMap<QString, Graph *> &graphsMap() const
        + Graph* getGraph(const QString& key)

        # void onChartViewReplot()
        # void onChartViewSizeChanged()
        # virtual void hoverMoveEvent(QHoverEvent *event) override
        # virtual void mousePressEvent( QMouseEvent* event ) override
        # virtual void mouseReleaseEvent( QMouseEvent* event ) override
        # virtual void mouseMoveEvent( QMouseEvent* event ) override
        # virtual void mouseDoubleClickEvent( QMouseEvent* event ) override
        # virtual void wheelEvent( QWheelEvent *event ) override
        # void routeMouseEvents( QMouseEvent* event )
        # void routeWheelEvents( QWheelEvent* event )
    }

    class TimePlot {
        - QTimer* m_timer
        - qint64 m_lastAddedTime
        - qint64 m_lastClearTime

        Q_PROPERTY (int plotTimeRangeInMilliseconds READ plotTimeRangeInMilliseconds WRITE set_plotTimeRangeInMilliseconds NOTIFY plotTimeRangeInMillisecondsChanged)

        + TimePlot(QQuickItem* parent)
        + ~TimePlot()
        + setTimeFormat(const QString &format)
        + addCurrentTimeValue(const QString& name, double value)
        + addCurrentTimeValues(QVariantMap values)

        # virtual void timerEvent(QTimerEvent *event)
        # virtual void onTimeOut()
    }

    class Axis {
        - QCustomPlot* m_parentPlot
        - QCPAxis* m_axis
        - Grid* m_grid
        - Ticker* m_ticker
        
        Q_PROPERTY (bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY (QString label READ label WRITE setLabel NOTIFY labelChanged)
        Q_PROPERTY (float upper READ upper WRITE setUpper NOTIFY upperChanged)
        Q_PROPERTY (float lower READ lower WRITE setLower NOTIFY lowerChanged)
        Q_PROPERTY (Grid* grid READ grid CONSTANT)
        Q_PROPERTY (Ticker* ticker READ Ticker NOTIFY TickerChanged)
        Q_ENUM (TickerType)
        enum TickerType ( Fixed, Log, Pi, Text, DateTime, Time )

        + Axis(QCPAxis* axis, QObject* parent)
        + ~Axis()
        + setTickerType(TickerType type)
        + setRange(float position, float size, Qt::AlignmentFlag align)
        + setTicker(QSharedPointer<QCPAxisTicker> ticker)
        - updateProperty()
    }

    class Grid {
        - QCustomPlot* m_parentPlot
        - QCPGrid* m_qcpgrid

        Q_PROPERTY (bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY (bool subVisible READ subVisible WRITE setSubVisible NOTIFY subVisibleChanged)
        Q_PROPERTY (int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY (QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY (LineType lineType READ lineType WRITE setLineType NOTIFY lineTypeChanged)
        Q_PROPERTY (int subLineWidth READ subLineWidth WRITE setSubLineWidth NOTIFY subLineWidthChanged)
        Q_PROPERTY (QColor subLineColor READ subLineColor WRITE setSubLineColor NOTIFY subLineColorChanged)
        Q_PROPERTY (LineType subLineType READ subLineType WRITE setSubLineType NOTIFY subLineTypeChanged)
        Q_ENUM (LineType)
        enum LineType ( NoPen, SolidLine, DashLine, DotLine, DashDotLine, DashDotDotLine )

        + Grid(grid, QCustomPlot* parentPlot)
        ~ Grid()
        - updateProperty()
    }

    class Ticker {
        - QCustomPlot* m_parentPlot
        - QSharedPointer<QCPAxisTicker> m_ticker

        Q_PROPERTY (bool ticks READ ticks WRITE setTicks NOTIFY ticksChanged)
        Q_PROPERTY (bool subTicks READ subTicks WRITE setSubTicks NOTIFY subTicksChanged)
        Q_PROPERTY (int tickCount READ tickCount WRITE setTickCount NOTIFY tickCountChanged)
        Q_PROPERTY (QColor tickColor READ tickColor WRITE setTickColor NOTIFY tickColorChanged)
        Q_PROPERTY (QColor subTickColor READ subTickColor WRITE setSubTickColor NOTIFY subTickColorChanged)
        Q_PROPERTY (QColor baseColor READ baseColor WRITE setBaseColor NOTIFY baseColorChanged)
        Q_PROPERTY (int baseWidth READ baseWidth WRITE setBaseWidth NOTIFY baseWidthChanged)
        
        + Ticker(QSharedPointer<QCPAxisTicker> ticker, QCustomPlot* parentPlot)
        + ~Ticker()
        - updateProperty()
        
    }

    class Graph {
        - QCustomPlot* m_parentPlot
        - QCPGraph* m_graph
        Q_PROPERTY (bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
        Q_PROPERTY (bool antialiased READ antialiased WRITE setAntialiased NOTIFY antialiasedChanged)
        Q_PROPERTY (QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY (LineStyle lineStyle READ lineStyle WRITE setLineStyle NOTIFY lineStyleChanged)
        Q_PROPERTY (QColor graphColor READ graphColor WRITE setLineColor NOTIFY graphColorChanged)
        Q_PROPERTY (int graphWidth READ graphWidth WRITE setLineWidth NOTIFY graphWidthChanged)
        Q_ENUM (LineStyle)
        enum LineStyle ( lsNone, lsLine, lsStepLeft, lsStepRight, lsStepCenter, lsImpulse )

        + Graph(QCustomPlot* parentPlot)
        + ~Graph()
        + void setData(const QVector<double>& x, const QVector<double>& y)
        + void addData(double x, double y)
        + void removeDataBefore(double x)
        + void clearData()
        - updateProperty()
    }

 ```