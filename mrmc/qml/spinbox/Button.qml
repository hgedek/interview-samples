import QtQuick 2.0

Rectangle{
    id: rectangle
    color: enabled ? "#3c3e49" : "#26262f"
    width: 50
    height: 25

    property alias image : text.text

    signal clicked();

    MouseArea {
        id: mouseArea
        onEntered: parent.color = parent.enabled ? "#4f505a" : "#26262f"
        onPressed: parent.color = parent.enabled ? "#30313a" : "#26262f"
        onExited: parent.color = parent.enabled ? "#3c3e49" : "#26262f"
        anchors.fill: parent
    }

    Text {
        id: text
        color: enabled ? "#ffffff" : "#393946"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component.onCompleted: {
        mouseArea.clicked.connect(rectangle.clicked);
    }
}
