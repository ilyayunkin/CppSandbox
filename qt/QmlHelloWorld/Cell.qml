import QtQuick 2.0

Item {
    id: container
    property alias cellColor: rectangle.color
    signal clicked(cellColor: color)

    width: 40; height: 25

    Rectangle {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea;
        anchors.fill: parent
        onClicked: container.clicked(container.cellColor)
    }

    // State и  Transition описывают реакцию на клик мышью
    states: State {
        name: "down"; // Имя конечного состояния
        when: mouseArea.pressed == true // Анимация проигрывается пока кнопка мыши нажата
        PropertyChanges {
            target: rectangle; // Анимируем прямоугольник
            rotation: 180 // полный цикл анимации поворачивает прямоугольник на 180 градусов
        }
    }
    transitions: Transition {
        from: ""; to: "down";
        reversible: true // Анимация открутится назад потом
        ParallelAnimation {
            NumberAnimation { properties: "y,rotation"; duration: 500; easing.type: Easing.InOutQuad }
        }
    }
}
