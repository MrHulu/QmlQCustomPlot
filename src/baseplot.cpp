#include "baseplot.h"
#include "axis.h"
#include "graph.h"
#include "qcustomplot.h"

#include <stdexcept>

namespace QmlQCustomPlot
{


BasePlot::BasePlot(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_customPlot(new QCustomPlot())
{
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);  
    connect(this, &QQuickPaintedItem::widthChanged, this, &BasePlot::onChartViewSizeChanged);
    connect(this, &QQuickPaintedItem::heightChanged, this, &BasePlot::onChartViewSizeChanged);   
    connect(m_customPlot, &QCustomPlot::afterReplot, this, &BasePlot::onChartViewReplot, Qt::UniqueConnection);
    try {
        m_x = new Axis(m_customPlot->xAxis, m_customPlot, this);
        m_x1 = new Axis(m_customPlot->xAxis2, m_customPlot, this);
        m_y = new Axis(m_customPlot->yAxis, m_customPlot, this);
        m_y1 = new Axis(m_customPlot->yAxis2, m_customPlot, this);
        connect(m_x, &Axis::destroyed, this, [this]{ m_x = nullptr; Q_EMIT xChanged(nullptr); });
        connect(m_x1, &Axis::destroyed, this, [this]{ m_x1 = nullptr; Q_EMIT x1Changed(nullptr);});
        connect(m_y, &Axis::destroyed, this, [this]{ m_y = nullptr; Q_EMIT yChanged(nullptr); });
        connect(m_y1, &Axis::destroyed, this, [this]{ m_y1 = nullptr; Q_EMIT y1Changed(nullptr);});
        connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->yAxis2, SLOT(setRange(QCPRange)));
   
    }
    catch(const std::exception &e) {
        qCritical() << e.what();
        m_x = nullptr;
        m_x1 = nullptr;
        m_y = nullptr;
        m_y1 = nullptr;
    }
    update();
}

BasePlot::~BasePlot()
{
    delete m_customPlot;
}

void BasePlot::set_backgroundColor(const QColor &value)
{
    // m_backgroundColor = m_customPlot->background().toImage().pixelColor(0, 0);
    if(m_backgroundColor == value) return;
    m_backgroundColor = value;
    m_customPlot->axisRect()->setBackground(QBrush(m_backgroundColor));
    emit backgroundColorChanged(m_backgroundColor);
    m_customPlot->replot();
}

QVariantMap BasePlot::graphs() const
{
    QVariantMap map;
    for(auto it = m_graphs.begin(); it != m_graphs.end(); ++it) {
        map.insert(it.key(), QVariant::fromValue(it.value()));
    }
    return map;
}

Q_INVOKABLE void BasePlot::addGraph(const QString &name)
{
    if(m_graphs.contains(name)) return;

    auto g = m_customPlot->addGraph();
    if(g == nullptr) return;
    g->setName(name);
    auto graph = new Graph(g, m_customPlot, this);
    m_graphs.insert(name, graph);
    connect(graph, &Graph::nameChanged, this, [this, name]{
        auto graph = m_graphs.take(name);
        m_graphs.insert(graph->name(), graph);
    }, Qt::UniqueConnection);
    emit graphsChanged();
}

Q_INVOKABLE void BasePlot::removeGraph(const QString &name)
{
    if(m_graphs.contains(name)) {
        auto graph = m_graphs.take(name);
        delete graph;
        emit graphsChanged();
    }
}

Graph *BasePlot::getGraph(const QString &name) const
{
    if(m_graphs.contains(name)) {
        return m_graphs.value(name);
    }
    return nullptr;
}

void BasePlot::paint(QPainter *painter)
{
    if (!painter->isActive())
        return;
    QPixmap picture( boundingRect().size().toSize() );
    QCPPainter qcpPainter( &picture );
    m_customPlot->toPainter(&qcpPainter);
    painter->drawPixmap(QPoint(), picture);
}

void BasePlot::onChartViewSizeChanged()
{
    m_customPlot->setGeometry(0, 0, (int)width(), (int)height());
    m_customPlot->setViewport(QRect(0, 0, (int)width(), (int)height()));
    m_customPlot->axisRect()->setOuterRect(QRect(0, 0, (int)width(), (int)height()));
    m_customPlot->axisRect()->setMinimumMargins (QMargins(0, 0, 0, 0));
    m_customPlot->axisRect()->setMargins(QMargins(0, 0, 0, 0));
}

void BasePlot::routeMouseEvents(QMouseEvent *event)
{
    QMouseEvent* newEvent = new QMouseEvent(event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers());
    QCoreApplication::postEvent(m_customPlot, newEvent);
}

void BasePlot::routeWheelEvents(QWheelEvent *event)
{
    QWheelEvent* newEvent = new QWheelEvent(event->position(), event->globalPosition(),
                                            event->pixelDelta(), event->angleDelta(), 
                                            event->buttons(), event->modifiers(), 
                                            event->phase(), event->inverted());
    QCoreApplication::postEvent(m_customPlot, newEvent);
}

} // namespace QmlQCustomPlot   