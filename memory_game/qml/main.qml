import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import "../qml"

Window {
    id: window
    maximumWidth: 900
    maximumHeight: 900
    width: maximumWidth
    height: maximumHeight

    visible: true
    title: qsTr("Memory Game")
     
    readonly property int animTime: 1000
    
    MessageDialog {
        id: messageDialog
        standardButtons: MessageDialog.Ok
        title: "Game Completed !"
        text: "Duration: " + duration.text
        onAccepted: {
            window.count = 0;
            cellModel.reset();
            duration.reset();
            timer.running = true;
        }
    }
    
    // timer counter
    property int count: 0
    
    Timer {
        id: timer
        interval: 1000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: duration.set()
    }

    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 20
        
        GridView {
            id: grid 
            Layout.preferredWidth: 800
            Layout.preferredHeight: 800
            Layout.leftMargin: 50
            cellWidth: 80
            cellHeight: 80
            model: cellModel
            focus: true
            
            property int previousIndex: -1
            
            delegate: Cell {
                id: cell
                height: grid.cellHeight - 10
                width: grid.cellWidth - 10
                url: model.url
            }
        }    
    }

    
    RowLayout {
        id:rowLayout
        height: 50
        anchors.bottom: parent.bottom
        Text {
            id: label
            text: qsTr("Duration:")
            width: 40
        }
        
        Text {
            id: duration
            font.pointSize: 12
            
            function set() {
                duration.text = new Date(window.count += 1).toLocaleTimeString(Qt.locale(), 
                                                                                 "mm " + "ss " + "zzz") 
            }
            
            function reset() {
                duration.text = '';
                
            }
        }
    }
}
