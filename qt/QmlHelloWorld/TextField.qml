import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle{
    //property type name: value
    property alias text: text.text // Свойство, связанное с свойством потомка
    property string name: "TextField" // Имя элемента
    radius: 20

    color: "chartreuse" // SVG Color

    border.color: "lemonchiffon"
    border.width: 10
    ScrollView{ // TextArea Сама не скролится. Нужно это
        x: 10
        y: 10
        width: parent.width - 10 * 2
        height: parent.height - 10 * 2
        TextArea {
            id: text
            text:
                "Lorem ipsum dolor sit amet, consectetur adipisicing elit, " +
                "sed do eiusmod tempor incididunt ut labore et dolore magna " +
                "aliqua. Ut enim ad minim veniam, quis nostrud exercitation " +
                "ullamco laboris nisi ut aliquip ex ea commodo cosnsequat. ";
            wrapMode: TextEdit.Wrap
        }
    }
}
