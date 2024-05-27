import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
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
            Label {
                text: qsTr("AAA")
                anchors.centerIn: parent
            }
        }
        Page {
            Label {
                text: qsTr("This is implementation of http://www.qcustomplot.com/index.php/support/forum/172\n" +
                           "Adding random data on 500 ms tick to plot")
                anchors.centerIn: parent
            }
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