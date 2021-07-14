import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 640
    height: 480

    title: qsTr("Hello World")
    Rectangle{
        color: "skyblue"
        anchors.fill: parent
        ColumnLayout{
            anchors.margins: 5
            anchors.fill: parent
            GridLayout{
                columns: 2
                Text {text: qsTr("Chat") ;Layout.fillWidth: true}
                Text {text: qsTr("Users") ;Layout.fillWidth: true}
                ScrollView{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    TextArea {
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        anchors.margins: 5
                        background: Rectangle {radius: 20; color: parent.enabled ? "white" : "grey"}
                    }
                }
                ScrollView{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    TextArea {
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        anchors.margins: 5
                        background: Rectangle {radius: 20; color: parent.enabled ? "white" : "grey"}
                    }
                }
            }
            RowLayout{
                TextField{
                    text: "hhh" ;Layout.fillWidth: true
                    background: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 40
                        radius: 20; color: parent.enabled ? "white" : "grey"
                    }
                }
                RoundButton{text: "Send" ;Layout.minimumWidth: 100}
            }
        }
    }
}
