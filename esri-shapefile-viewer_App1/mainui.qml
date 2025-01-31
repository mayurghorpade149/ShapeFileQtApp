import QtQuick 2.0
import QtQuick 2.4
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import QtLocation 5.6
import QtPositioning 5.5
import QtQuick.Controls 2.5
import ShapeFileLib 1.0
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: mainWindowWithStackView
    title: "AeroGCS_v1.1_21_01_2020"
    width: 800
    height: 500
    visible: true
    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }
    FileDialog{
        id: fileDialog
//        fileMode:{ FileDialog.SaveFile}
        nameFilters: "*.shp"
        selectMultiple : true
        onAccepted: {
            console.log(fileDialog.fileUrls)
            MainWindow.openDataset(fileDialog.fileUrls)
            fileDialog.close()
        }
        onRejected: {
            console.log("File closed")
            fileDialog.close()
        }
    }
    Rectangle{
        id : navBar
        width: parent.width
        height: parent.height * 0.08
        color: "grey"
        Button{
            id: fileSelect
            anchors.left: parent.left
            text: "Select File"
            onClicked: {
                fileDialog.open()
            }
        }
    }

    Rectangle{
        id : leftBar
        width: parent.width * 0.3
        height: parent.height - (parent.height * 0.08)
        anchors.top: navBar.bottom
        anchors.left : navBar.left
        color: "#73c2e6"
        ListView{
            id: listView
            clip: true
            anchors.fill: parent
            spacing :0
            model : MainWindow.layerList
            highlight: Rectangle {
                width: listView.width
                height: listView.height*0.07
                color: "lightsteelblue"
                radius: 3

                Behavior on y {
                    SpringAnimation {
                        spring: 3
                        damping: 0.2
                    }
                }
            }
            highlightFollowsCurrentItem: true
            focus: true
            delegate: Rectangle {
                width: listView.width
                height: listView.height*0.05

                radius: 3

                border.width:1
                property color tempcolor: "transparent"
                color: tempcolor
                Row {
                    id: row1
                    anchors.fill: parent
                    spacing: 10
                    anchors.leftMargin: 10
//                    Text {
//                        text: index+1
//                        anchors.verticalCenter: parent.verticalCenter
//                        font.bold: true
//                        font.pointSize: (listView.currentIndex === index) ? parent.height*0.6 : parent.height*0.5
//                    }

//                    Rectangle {
//                        width:  parent.height*0.8
//                        height: parent.height*0.8
//                        color: "red"
//                        anchors.verticalCenter: parent.verticalCenter

//                    }
                    Text {
                        text: (index+1)+" "+modelData
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.pointSize: parent.height*0.5//(listView.currentIndex === index) ? parent.height*0.6 : parent.height*0.5
                    }
                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            listView.currentIndex = index
                            //console.log(index)
                        }
                        onEntered: {
                            tempcolor = "#a7e094"
                        }

                        onExited: {
                            tempcolor = "transparent"
                        }
                    }
                    Rectangle {
                        id:deleteBtn
                        anchors.right: upBtn.left
                        width:  height
                        height: parent.height
                        color: "red"
                        anchors.verticalCenter: parent.verticalCenter
                        visible: (listView.currentIndex === index)
                        Text {
                            text: "X"
                            anchors.centerIn : parent
                            font.pointSize: parent.height*0.5//(listView.currentIndex === index) ? parent.height*0.6 : parent.height*0.5
                        }
                        MouseArea{
                            anchors.fill: deleteBtn
                            height: listView.height*0.05
                            onClicked: {
                                console.log("Action delete layer")
                                MainWindow.removeLayer(listView.currentIndex)
                            }
                        }
                    }
                    Rectangle {
                        id : upBtn
                        anchors.right: dwnBtn.left
                        width:  height
                        height: parent.height
                        color: "yellow"
                        anchors.verticalCenter: parent.verticalCenter
                        visible: (listView.currentIndex === index)
                        Text {
                            text: "▲"
                            anchors.centerIn : parent
                            font.pointSize: parent.height*0.5//(listView.currentIndex === index) ? parent.height*0.6 : parent.height*0.5
                        }
                        MouseArea{
                            anchors.fill: upBtn
                            height: listView.height*0.05
                            onClicked: {
                                console.log("Action move layer up")
                                MainWindow.layerUp(listView.currentIndex)
                            }
                        }
                    }
                    Rectangle {
                        id: dwnBtn
                        anchors.right: parent.right
                        width:  height
                        height: parent.height
                        color: "#afc1c9"
                        anchors.verticalCenter: parent.verticalCenter
                        visible: (listView.currentIndex === index)
                        Text {
                            text: "▼"
                            anchors.centerIn : parent
                            font.pointSize: parent.height*0.5//(listView.currentIndex === index) ? parent.height*0.6 : parent.height*0.5
                        }
                        MouseArea{
                            anchors.fill: dwnBtn
                            height: listView.height*0.05
                            onClicked: {
                                console.log("Action move layer down")
                                MainWindow.layerDown(listView.currentIndex)
                            }
                        }
                    }
                }
            }
        }
//        ListView {
//            width: parent.width
//            height: parent.height
//            anchors.centerIn: parent
//            model: MainWindow.layerList
//            delegate:
//             Rectangle{
//                id : background
//                Text {
//                    text: index+" "+modelData
//                }
//            }
//        }
    }

    Rectangle{
        id : rightBar
//        objectName: "viewForm"
        width: parent.width * 0.7
        height: parent.height - (parent.height * 0.08)
        anchors.top: navBar.bottom
        anchors.right: navBar.right
        color: "#afc1c9"
//        ViewFormCust{
//            id : viewForm
//            objectName: "viewForm"
//            anchors.fill: parent
//        }
        Map {
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(59.91, 10.75) // Oslo
            zoomLevel: 14
            MapQuickItem {
                id: marker
                anchorPoint.x: viewForm.width/4
                anchorPoint.y: viewForm.height
                coordinate: QtPositioning.coordinate(59.91, 10.75) // Oslo
                sourceItem: ViewFormCust{
                    id : viewForm
                    objectName: "viewForm"
                    anchors.fill: parent
                }
            }
        }

//        MainWindow{
//            id : mainWnd
//    //        width: parent.width
//    //        height: parent.height
//        }
    }
}
