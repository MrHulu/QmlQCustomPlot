import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QmlQCustomPlot 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello QCustomPlot in QML")

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
                y.grid.lineColor: "#50006EFF"
                x.ticker.baseColor: "#0000FF"
                x.ticker.baseWidth: 2
                x.grid.lineColor: "transparent"
                backgroundColor: "#F2F4F7"
                Component.onCompleted: {
                    y.setRange(0, 100)
                    x.ticker.ticks = false
                    addGraph("1")
                }
            }
            Timer {
                running: true
                repeat: true 
                interval: 3
                property int data: 60
                property int ok: 0
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
                backgroundColor: "#F2F4F7"
            }
            // }
            // Label {
            //     text: qsTr("This is implementation of http://www.qcustomplot.com/index.php/support/forum/172\n" +
            //                "Adding random data on 500 ms tick to plot")
            //     anchors.centerIn: parent
            // }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Plot")
        }
        TabButton {
            text: qsTr("Info")
        }
    }
}