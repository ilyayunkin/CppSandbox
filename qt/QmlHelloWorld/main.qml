import QtQuick 2.12
import QtQuick.Window 2.12
import ru.ilya.helloworld 1.0 // Подключаем свой C++ класс, наследующий QObject, зарегистрированный в функции main() из main.cpp

Window {
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Hello World")

    Data{// Наш C++ класс
        id: cppData
    }

    TextField{
        id: rightBottomRect
        x: parent.width / 2
        y: parent.height / 2
        width: parent.width / 2
        height: parent.height / 2
    }
    TextField {       
        id: rightTopRect
        x: parent.width / 2
        y: 0
        width: parent.width / 2
        height: parent.height / 2

        text: cppData.number // Печатаем  свойство из нашего C++ класса
    }
    Rectangle{
        id: topLeftText
        x: 0
        y: 0
        width: parent.width / 2
        height: parent.height / 2
        Grid {
            id: colorPicker
            x: 4; anchors.fill: parent; anchors.bottomMargin: 4
            rows: 2; columns: 3; spacing: 3
            Cell { cellColor: "red"; onClicked: rightBottomRect.color = cellColor }
            Cell { cellColor: "green"; onClicked: rightBottomRect.color = cellColor }
            Cell { cellColor: "blue"; onClicked: rightBottomRect.color = cellColor }
            Cell { cellColor: "yellow"; onClicked: rightBottomRect.color = cellColor }
            Cell { cellColor: "steelblue"; onClicked: rightBottomRect.color = cellColor }
            Cell { cellColor: "black"; onClicked: rightBottomRect.color = cellColor }
        }
    }

    // Slots
    onWidthChanged: {
        console.log("Width: " + width);
        rightBottomRect.text = "Width: " + width + "<br>Height: " + height + "\r\n"
    }
    onHeightChanged:  {
        console.log("Height: " + height);
        rightBottomRect.text = "Width: " + width + "<br>Height: " + height + "\r\n"
    }
}
