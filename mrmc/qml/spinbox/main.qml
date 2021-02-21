import QtQuick 2.12
import QtQuick.Window 2.12
import "parseInt.js" as Parse

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    SpinBox{}

    Component.onCompleted: {
        console.log(Parse.parseInt("16"));
        console.log(Parse.parseInt("0x10"));
        console.log(Parse.parseInt(""));
        console.log(Parse.parseInt("abc"));
    }
}
