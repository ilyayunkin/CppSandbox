import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Hello World")

    TextField{
        id: rightBottomRect
        x: parent.width / 2
        y: parent.height / 2
        width: parent.width / 2
        height: parent.height / 2
    }
    TextField{
        id: rightTopRect
        x: parent.width / 2
        y: 0
        width: parent.width / 2
        height: parent.height / 2
        text: "1<br>2<br>3<br>4<br>5<br>6<br>7<br>8<br>9<br>10<br>11<br>12<br>13<br>14<br>15<br>16<br>17<br>18<br>19"
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
