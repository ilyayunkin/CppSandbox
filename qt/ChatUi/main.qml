import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Window{
    id: chatUi
    signal sendMessage (msg: string)

    property string chatText
    property string userList

    visible: true
    minimumWidth: 640
    minimumHeight: 480

    function sending(){
        chatUi.sendMessage(message.text)
        message.text = ""
    }

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
                        id: chat
                        text: chatUi.chatText
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        anchors.margins: 5
                        background: Rectangle {anchors.fill: parent; radius: 20; color: parent.enabled ? "white" : "grey"}
                        onTextChanged: {
                            chat.cursorPosition = chat.text.length
                        }
                    }
                }
                ScrollView{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    TextArea {
                        id: users
                        text: chatUi.userList
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        anchors.margins: 5
                        background: Rectangle {anchors.fill: parent; radius: 20; color: parent.enabled ? "white" : "grey"}
                    }
                }
            }
            RowLayout{
                TextField{
                    id: message
                    Layout.fillWidth: true
                    background: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 40
                        radius: 20; color: parent.enabled ? "white" : "grey"
                    }
                    onAccepted: chatUi.sending()
                }
                RoundButton{
                    text: "Send" ;Layout.minimumWidth: 100
                    onClicked: chatUi.sending()
                }
            }
        }
    }
}
