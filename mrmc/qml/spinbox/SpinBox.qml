import QtQuick 2.12
import QtQuick.Layouts 1.0

Item {
    id: item
    property int step: 10
    property int topValue: 100
    property int bottomValue: 0
    property int value: 0
    property string prefix: ""
    property string postfix: ""

    onValueChanged: {
        if (value < bottomValue || value > topValue) {
            item.enabled = false;
            item.value = value < item.bottomValue ? item.bottomValue :
                                                    value > item.topValue ? item.topValue : value;
        }
    }

    implicitWidth: increaseButton.width + rect.width + decreaseButton.width

    Row {
        spacing: 2

        Button {
            id: increaseButton
            image: "+"
            onClicked: {
                item.value += item.step;
            }
        }

        Rectangle {
            id: rect
            color: enabled ? "#2a2c37": "transparent"
            border.color: enabled ? "#787b92" : "2a2a33"
            height: increaseButton.height
            width: 80

            TextInput {
                id: textInput
                font.pixelSize: 12
                anchors.fill: parent
                padding: 4
                maximumLength: 10
                color: enabled ? "#ffffff" : "#393946"
                text: "" + item.value

                onAccepted: {
                    var values = textInput.text.split(" ");
                    textInput.text = "";
                    var value = 0;

                    if (values.length === 3)
                        value = parseInt(values[1]);
                    else if(values.length === 2) {
                        value = parseInt(values[0]);
                        if (isNaN(value))
                            value = parseInt(values[1]);
                    }
                    else if(values.length === 1)
                        value = parseInt(values[0]);

                    if (!isNaN(value))
                        item.value = value;
                }
            }
        }

        Button {
            id: decreaseButton
            image: "-"
            onClicked: {
               item.value -= item.step;
            }
        }
    }
}
