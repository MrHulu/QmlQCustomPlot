import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QmlQCustomPlot 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("QCustomPlot in QML")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false

        Page {
            TimePlot {
                id: timePlot
                anchors.fill: parent
                plotTimeRangeInMilliseconds: 10         
                x.visible: true
                y.visible: true
                x1.visible: false
                y1.visible: false
                y.ticker.tickCount: 6
                y.ticker.ticks: false
                y.ticker.subTicks: false
                y.ticker.baseColor: "transparent"
                y.grid.lineColor: "mediumaquamarine"
                x.ticker.baseColor: "midnightblue"
                x.ticker.baseWidth: 2
                x.grid.lineColor: "transparent"
                backgroundColor: "mistyrose"
                Component.onCompleted: {
                    y.setRange(0, 100)
                    addGraph("1")
                    graphs["1"].graphColor = "slategrey"
                }
            }
            Timer {
                running: true
                repeat: true 
                interval: 20
                property int data: 60
                onTriggered: {
                    data = data - 1
                    if(data == 20) {
                        data = 60 
                    } 
                    timePlot.addCurrentTimeValue("1", data)                    
                }
            }
        }
        Page {
            BasePlot {
                anchors.fill: parent
                backgroundColor: "gainsboro"
                x.ticker.ticks: false
                x.ticker.subTicks: false
                y.ticker.ticks: false
                y.ticker.subTicks: false
                Component.onCompleted: {
                    x.label = "x"
                    y.label = "y'"
                    addGraph("1")
                    graphs["1"].graphColor = "lightcoral"
                    graphs["1"].graphWidth = 2
                    let xData = []
                    let yData = []
                    for (var i = 0; i <= 100; ++i) {
                        xData.push(i - 50);
                        yData.push(xData[i] * xData[i])
                    }
                    graphs["1"].setData(xData, yData)
                    graphs["1"].name = "y = x^2"
                    addGraph("2")
                    graphs["2"].graphColor = "lightseagreen"
                    graphs["2"].graphWidth = 3
                    xData = []
                    yData = []
                    for (var i = 0; i <= 100; ++i) {
                        xData.push(i - 50);
                        yData.push(xData[i] * xData[i] * 2  + 100)
                    }
                    graphs["2"].setData(xData, yData)
                    graphs["2"].name = "y = 2x^2 + 100"
                    rescaleAxes(true)
                }
            }
        }
        Page {
            Label {
                id: label
                readonly property var url: "https://github.com/MrHulu/QmlQCustomPlot" 
                text: qsTr("This is implementation of %1\n".arg(label.url))
                anchors.centerIn: parent
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: Qt.openUrlExternally(label.url) 
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("TimePlot")
        }
        TabButton {
            text: qsTr("BasePlot")
        }
        TabButton {
            text: qsTr("Info")
        }
    }
}