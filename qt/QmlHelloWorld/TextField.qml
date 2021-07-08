import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle{
    //property type name: value
    property alias text: text.text // Свойство, связанное с свойством потомка
    property string name: "TextField" // Имя элемента
    radius: 20

    color: "chartreuse" // SVG Color

    border.color: "lemonchiffon"
    border.width: 10
        TextArea {
            anchors.fill: parent
            id: text
            width: parent.width - 40
            height: parent.height - 40
        }
}
