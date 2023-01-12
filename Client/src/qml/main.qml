import QtQuick 2.7
import QtQuick.Window 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQml 2.2
import Owl 1.0 as Owl
ApplicationWindow {
    id:roots;
    visible: true;
    width: roots.screen.width;
    height: roots.screen.height - 100;

    onScreenChanged: {
        width = screen.width;
        height = screen.height - 100;
        minimumHeight = height;
        minimumWidth = width;
        maximumHeight = height;
        maximumWidth = width;
        fields.width = (roots.height)*4/3;
        fields.height = roots.height;
    }

//    minimumHeight: height;
//    minimumWidth: width;
//    maximumHeight: 16777215; //height;
//    maximumWidth: 16777215; //width;
    color:"#e8e8e8";
//    flags:Qt.FramelessWindowHint
    Timer{
        id:fpsTimer;
        interval:1000;
        running:true;
        repeat:true;
        onTriggered: {
            fps.text = (interaction4field.getFPS()).toString() + "\n" + (interaction4field.getRBKFPS(0)).toString()+ "\n" + (interaction4field.getRBKFPS(1)).toString();
        }
    }

    Owl.Interaction4Field { id : interaction4field; }
    Owl.Interaction { id : interaction }

    menuBar: MenuBar {
        height: 25;
        Menu {
            title: "Tools"
            //MenuSeparator{}
            Menu{
                title: "Formation"
                MenuItem{
                    text: "Save As";
                    onTriggered: interaction4field.saveFormation();
                }
                Menu{
                    title: "Load"
                    Repeater{
                        model: interaction4field.getFormationFileName();
                        MenuItem{
                            text: modelData;
                            onTriggered: {
                                interaction4field.readFormationJson(text);
                            }
                        }
                    }
                }
            }
        }
        /**
        Menu {
            title: "Game"
            Menu{
                title: "Challenge"
                Menu{
                    title: "Trail";
                    MenuItem{
                        text: "New Start" 
                        onTriggered: interaction.setChallengeMode(0);
                    }
                    MenuItem{
                        text: "Current Grade" 
                        onTriggered: interaction.showCurrentGrade(0);
                    }
                }
                Menu{
                    title: "Grade";
                    MenuItem{
                        text: "New Start" 
                        onTriggered: interaction.setChallengeMode(1);
                    }
                    MenuItem{
                        text: "Current Progress" 
                        onTriggered: interaction.showCurrentProgress();
                    }
                    MenuItem{
                        text: "Current Grade" 
                        onTriggered: interaction.showCurrentGrade(1);
                    }
                }         
                MenuItem{
                    text: "End"
                    onTriggered: interaction.endChallenge();
                } 
            }
            MenuSeparator{}
            Menu{
                title: "Recorder"
                //MenuSeparator{}
                MenuItem{
                    text: "Stop";
                    onTriggered: interaction.stopGameRecorder();
                }
                MenuItem{
                    text: "Recreate";
                    onTriggered: interaction.createGameRecorder();
                }
            }
        }
        **/
        Menu{
            title: "Help"
            MenuItem{
                text: "About";
                onTriggered: interaction.getBasicInfo();
            }
            MenuSeparator{}
            MenuItem{
                text: "Get More";
                onTriggered: interaction.getMoreInfo();
            }
        }
    }

    Row {
        spacing: 0;

        TabView{
            id:fields;
            width:(roots.height)*4/3;
            height:roots.height;
            currentIndex:1;

            onWidthChanged: {
                interaction4field.setSize(width,height - 20);
            }
            onHeightChanged: {
                interaction4field.setSize(width,height - 20);
            }
            Repeater{
                model:["Origin","Filtered B","Filtered Y"];
                Tab{
//                TabButton {
                    anchors.fill: parent;
                    title: modelData;
                    Rectangle{
                        border.color: "#555";
                        border.width: 1;
                        color: "#303030";
                        anchors.fill: parent;
                    }
                }
            }
            Owl.Field{
                //property int _index:index;
                type:fields.currentIndex+1;//_index+1;
                draw:true;//_index == fields.currentIndex;
                width:fields.width;
                height:fields.height - 20;
            }
            style: TabViewStyle {
                frameOverlap: 0
                tabOverlap: 0
                tab:
                Rectangle {
                    color: styleData.selected ? "#303030" : "grey"
                    implicitWidth: fields.width/fields.count;
                    implicitHeight: 20
                    Text {
                        id: text
                        anchors.centerIn: parent
                        text: styleData.title
                        color: styleData.selected ? "#dddddd" : "black"
                    }
                }
            }
            Text{
               id : fpsWord;
               text : qsTr("FPS");
               x:parent.width - 70;
               y:5;
               color:"white";
               font.pointSize: 10;
               font.weight:  Font.Bold;
            }
            Text{
               id : fps;
               text : "0"
               x:parent.width - 30;
               y:5;
               color:"#0077ff";
               font.pointSize: 12;
               font.weight:  Font.Bold;
            }
            Text{
                color:"white";x:10;y:5;
                property string strX : "0";
                property string strY : "0";
                id:positionLeftDisplay;
                text:qsTr("Left : " + "( " + strX + " , " + strY + " )");
                font.pointSize: 10;
                font.weight:  Font.Bold;
            }
            Text{
                color:"white";x:10;y:30;
                property string strX : "0";
                property string strY : "0";
                id:positionRightDisplay;
                text:qsTr("Right : " + "( " + strX + " , " + strY + " )");
                font.pointSize: 10;
                font.weight:  Font.Bold;
            }
//            Rectangle{
//               id:areaRectangle;
//               width:parent.width;
//               height:parent.height;
//               x:0;
//               y:0;
//               color:"#11ffffff";
//               visible: false;
//            }
            MouseArea{
                anchors.fill: parent;
                hoverEnabled: true;
                acceptedButtons: Qt.NoButton;
                onPositionChanged: {
                    positionLeftDisplay.strX = (interaction4field.getRealX(mouseX)).toString();
                    positionLeftDisplay.strY = (-interaction4field.getRealY(mouseY)).toString();
                    positionRightDisplay.strX = (-interaction4field.getRealX(mouseX)).toString();
                    positionRightDisplay.strY = (interaction4field.getRealY(mouseY)).toString();
                }
            }

//            MouseArea{
//                property int startX : 0;
//                property int startY : 0;
//                anchors.fill: parent;
//                acceptedButtons: Qt.MiddleButton
//                property bool controlMode : false
//                onClicked: {
//                    if(mouse.modifiers === Qt.AltModifier){
//                        interaction4field.setPlacementPoint(mouseX,mouseY);
//                    }
//                }
//                onPressed: {
//                    controlMode = (mouse.modifiers === Qt.ControlModifier)
//                    startX = mouseX;
//                    startY = mouseY;
//                    if(controlMode){
//                        interaction4field.setArea(0,0,0,0);
//                        areaRectangle.visible = true;
//                        areaRectangle.width = 0;
//                        areaRectangle.height = 0;
//                        areaRectangle.x = startX;
//                        areaRectangle.y = startY;
//                    }
//                }
//                onPositionChanged: {
//                    if(controlMode){
//                        areaRectangle.x = Math.min(mouseX,startX);
//                        areaRectangle.y = Math.min(mouseY,startY);
//                        areaRectangle.width = Math.abs(mouseX - startX);
//                        areaRectangle.height = Math.abs(mouseY - startY);
//                    }else{
//                        interaction4field.moveField(mouseX - startX,mouseY - startY)
//                        startX = mouseX;
//                        startY = mouseY;
//                    }
//                }
//                onReleased: {
//                    if(controlMode){
//                        if(areaRectangle.width < 100 && areaRectangle.height < 100){
//                            areaRectangle.x = areaRectangle.y = 0;
//                            areaRectangle.width = areaRectangle.parent.width;
//                            areaRectangle.height = areaRectangle.parent.height;
//                            interaction4field.resetArea();
//                        }else{
//                            interaction4field.setArea(areaRectangle.x,areaRectangle.width + areaRectangle.x,areaRectangle.height + areaRectangle.y,areaRectangle.y);
//                        }
//                        areaRectangle.visible = false;
//                    }
//                    controlMode = false
//                }
//            }

        }
        ControlBoard{
            id:controlBoard;
            width:roots.width - fields.width;
            height:parent.height;
        }
    }
    property variant controlRobotShortCut:["`","1","2","3","4","5","6","7","8","9","0","-","=","i","o","p","[","Ctrl+`","Ctrl+1","Ctrl+2","Ctrl+3","Ctrl+4","Ctrl+5","Ctrl+6","Ctrl+7","Ctrl+8","Ctrl+9","Ctrl+0","Ctrl+-","Ctrl+=","Ctrl+i","Ctrl+o","Ctrl+p","Ctrl+["];
    property variant controlRobotShortCut2:["Shift+`","Shift+1","Shift+2","Shift+3","Shift+4","Shift+5","Shift+6","Shift+7","Shift+8","Shift+9","Shift+0","Shift+-","Shift+=","Shift+i","Shift+o","Shift+p","Shift+[","Alt+`","Alt+1","Alt+2","Alt+3","Alt+4","Alt+5","Alt+6","Alt+7","Alt+8","Alt+9","Alt+0","Alt+-","Alt+=","Alt+i","Alt+o","Alt+p","Alt+["];
    property variant otherShortCut:["Ctrl+q","Ctrl+c","Ctrl+s","Ctrl+v"];

    function robotControl(index){
        var team = (index > 16 ? 1 : 0);
        var id = index%17;
        interaction4field.robotControl(id,team)
    }
    function singleRobotControl(index){
        var team = (index > 16 ? 1 : 0);
        var id = index%17;
        interaction4field.singleRobotControl(id,team)
    }

    Shortcut{
        property int index : 0;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 1;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 2;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 3;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 4;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 5;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 6;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 7;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 8;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 9;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 10;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 11;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 12;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 13;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 14;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 15;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 16;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 17;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 18;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 19;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 20;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 21;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 22;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 23;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 24;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 25;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 26;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 27;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 28;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 29;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 30;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 31;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 32;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 33;
        sequence:controlRobotShortCut[index];
        onActivated: {
            robotControl(index)
        }
    }
    Shortcut{
        property int index : 0;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 1;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 2;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 3;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 4;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 5;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 6;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 7;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 8;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 9;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 10;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 11;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 12;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 13;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 14;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 15;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 16;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 17;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 18;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 19;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 20;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 21;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 22;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 23;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 24;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 25;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 26;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 27;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 28;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 29;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 30;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 31;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 32;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        property int index : 33;
        sequence:controlRobotShortCut2[index];
        onActivated: {
            singleRobotControl(index)
        }
    }
    Shortcut{
        sequence:otherShortCut[0];
        onActivated: {
            Qt.quit();
        }
    }
    Shortcut{
        sequence:otherShortCut[1];
        property bool ctrlC : false;
        onActivated: {
            interaction4field.setCtrlC();
            ctrlC = !ctrlC;
        }
    }
    Shortcut{
        sequence:otherShortCut[2];
        onActivated: {
            interaction4field.saveFormation();
        }
    }
    Shortcut{
        sequence:otherShortCut[3];
        onActivated: {
            interaction4fieldfield.readFormationJson(interaction4fieldfield.getMenubar_CrtFile());
        }
    }
}
