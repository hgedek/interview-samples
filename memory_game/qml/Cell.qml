import QtQuick 2.0

Rectangle {
    id:rect
    objectName: "rect"
    state: "passive"
    
    property url url 
    
    Image {
       id: front
       source: rect.url
       visible: true
       opacity: 0.0
       anchors.fill: parent
       height: parent.implicitHeight
       width: parent.implicitWidth
    }
    
    Image {
        id: back
        source: "../images/background"
        visible: true
        opacity: 1.0
        anchors.fill: parent
        height: parent.implicitHeight
        width: parent.implicitWidth
    }
   
    MouseArea {
       id: mouseArea 
       anchors.fill: parent
       
       onClicked: {
            if (rect.state === "active") return;

            // firstly pass to active mode
            rect.state = "active";
            cellModel.updateCellCheckedStatus(index, true);
            
            // if its first time then update cellmodel to keep last updated cell
            if ( grid.previousIndex == -1) {
                grid.previousIndex = index;
                cellModel.setSelected(rect);
            } else {
                // if selected 2 cells are not equal then take back active modes
                // and bring background image forward with opacity updates
                if (!cellModel.isEqual(grid.previousIndex, index)) {
                    var item = cellModel.getSelected();
                    item.state = "passive";
                    rect.state = "passive";
                }
                
                // reset status 
                grid.previousIndex = -1;
                cellModel.setSelected(null);
            }
            
            // check if completed
            if (cellModel.isCompleted()){
                messageDialog.visible = true;
                timer.running = false;
            }
       }
    }
    
    // created states for active and passive statuses 
    // so we can animate transitions easily
    states: [
        State {
            name: "active"
            PropertyChanges {
                target: front
                opacity: 1.0
            }
            PropertyChanges {
                target: back
                opacity: 0.0
            }
        },
        State {
            name: "passive"
            PropertyChanges {
                target: front
                opacity: 0.0
            }
            
            PropertyChanges {
                target: back
                opacity: 1.0
            }
        }
    ]
    
    transitions: [
         Transition {
             from: "active"
             to: "passive"
             
             animations: ParallelAnimation {
                 NumberAnimation {
                     target: front
                     from: 1.0
                     to: 0.0
                     property: "opacity"
                     duration: 3*animTime 
                 }
                 
                 NumberAnimation {
                     target: back
                     from: 0.0
                     to: 1.0
                     property: "opacity"
                     duration: 3*animTime
                }
             }
         },
         Transition {
             from: "passive"
             to: "active"
             
             animations: ParallelAnimation {
                 NumberAnimation {
                     target: back
                     from: 1.0
                     to: 0.0
                     property: "opacity"
                     duration: animTime/8
                 }
                 NumberAnimation {
                     target: front
                     from: 0.0
                     to: 1.0
                     property: "opacity"
                     duration: animTime/8
                 } 
             }
         }
     ]
}
