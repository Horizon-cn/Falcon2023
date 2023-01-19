import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import Owl 1.0 as Owl
Page{
StackLayout {
    width: parent.width;
    height:parent.height;
ScrollView{
    id:viewer;
    clip:true;
    contentWidth: parent.width;
    contentHeight: parent.height * 2;
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
    ScrollBar.horizontal.interactive: true;
    ScrollBar.vertical.interactive: true;
    property bool needDisplay : false;
    property bool freezeDisplay : false;
    //Owl.ViewerInterface{ id : viewerInterface; }
    Grid{
        padding: 5;
        topPadding: 15;
        width:viewer.width;
        //height:viewer.height;
        columns: 1;
        horizontalItemAlignment: Grid.AlignHCenter;
        verticalItemAlignment: Grid.AlignVCenter;
        columnSpacing: 0;
        rowSpacing: 0;
        property int itemWidth : width - padding*2;
        ZGroupBox{
            title: qsTr("Display")
            Grid{
                width:parent.width;
                verticalItemAlignment: Grid.AlignVCenter;
                horizontalItemAlignment: Grid.AlignHCenter;
                spacing: 0;
                rowSpacing: 0;
                columns:4;
                columnSpacing: 5
                property int itemWidth :(width - (columns-1) * columnSpacing - 2*padding)/columns;
                Grid {
                    property int buttonWidth: parent.itemWidth;
                    ZButton{
                        icon.source:viewer.needDisplay ? "/resource/stop.png" : "/resource/start.png";
                        onClicked: {
                            viewer.needDisplay = !viewer.needDisplay;
                            display.ifNeedDisplay(viewer.needDisplay);
                        }
                    }
                }
                Grid {
                    property int buttonWidth: parent.itemWidth;
                    ZButton{
                        text:"SET";
                        onClicked: {
                            display.setDisplayMode();
                        }
                    }
                }
                Grid {
                    property int buttonWidth: parent.itemWidth;
                    ZButton{
                        text:viewer.freezeDisplay?"RESUME":"FREEZE";
                        onClicked: {
                            display.ifNeedDisplay(viewer.freezeDisplay);
                            viewer.freezeDisplay = !viewer.freezeDisplay;
                        }
                    }
                }
                Grid {
                    property int buttonWidth: parent.itemWidth;
                    ZButton{
                        text:"LOAD";
                        onClicked: {
                            fdrs.open();
                        }
                    }
                }
                FileDialog {
                    id:fdrs
                    title: "Please select"
                    selectExisting: true
                    selectFolder: false
                    selectMultiple: false
                    nameFilters: ["Rec files (*.txt)"]
                    onAccepted: {
                        console.log("You chose: " + fdrs.fileUrl);
                    }
                    onRejected: {
                        console.log("Canceled");
                    }
                }
            }
        }
        Owl.Display{
            id:display;
            type:1;
            width:parent.width - 2*parent.padding;
            height:getDisplayHeight();
            visible:viewer.needDisplay;
            onWidthChanged: {
                resetSize(width,height);
            }
            onHeightChanged: {
                resetSize(width,height);
            }
        }/**
        ZGroupBox{
            title: qsTr("Robot")
            Grid{
                anchors.fill: parent;
                spacing: 0;
                rowSpacing: 0;
                columns:2;
                property int itemHeight : 40;
                property int itemWidth : width/2;
                Repeater{
//                  model:[0,7,8,9,10,11,12,13,14,15,16];
                    model: viewerInterface;
                    ZRobot{
                        number: mID;
                        team : mTeam;
                        valid : mValid;
                        //battery : mBattery;
                        //capacity: mCapacitance;
                        infrared: mInfrared;
                    }
                }
            }
        }**/
    }
}
}
}
