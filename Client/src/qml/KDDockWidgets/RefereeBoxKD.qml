import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import Owl 1.0 as Client
import Components 1.0
Page{
    Client.RefereeBox { id : refereeBox; }
    Client.Interaction4Field { id : interaction4; }
    Timer {
        id:refBoxTimer;
        interval:16;
        running:refBoxSwitch.refereeSwitch && refBoxModeSwitch.refereeAutoMode!=2; //false;
        repeat:true;
        onTriggered: {
            //if (refBoxModeSwitch.refereeAutoMode!=2)
                refereeBox.multicastCommand();
        }
    }
    property var color : ["#ddd","#79a6ea","#fbeb9c"];
    function getColor(index) {
        if (index == 0)
            return "#ddd";
        else if (index == 1)
            return "#79a6ea";
        else if (index == 2)
            return "#fbeb9c";
    }
    property bool haltGame : false;
    property bool stopGame : true;
    property bool forceStart : false;
    property bool normalStart : false;
    property bool teamControl : false;
    property int next_command : Client.RefBoxCommand.HALT;
    property int state : Client.GameState.HALTED;
    function getButtonsCommand(index){
        switch(index){
        case Client.RefBoxCommand.HALT:
            state = Client.GameState.HALTED;break;
        case Client.RefBoxCommand.STOP_GAME:
        case Client.RefBoxCommand.BALL_PLACEMENT_YELLOW:
        case Client.RefBoxCommand.BALL_PLACEMENT_BLUE:
            state = Client.GameState.STOPPED;break;
        case Client.RefBoxCommand.FORCE_START:
        case Client.RefBoxCommand.NORMAL_START:
        case Client.RefBoxCommand.DIRECT_KICK_YELLOW:
        case Client.RefBoxCommand.INDIRECT_KICK_YELLOW:
        case Client.RefBoxCommand.DIRECT_KICK_BLUE:
        case Client.RefBoxCommand.INDIRECT_KICK_BLUE:
            state = Client.GameState.RUNNING;break;
        case Client.RefBoxCommand.TIMEOUT_YELLOW:
            state = Client.GameState.TIMEOUT_YELLOW;break;
        case Client.RefBoxCommand.TIMEOUT_BLUE:
            state = Client.GameState.TIMEOUT_BLUE;break;
        case Client.RefBoxCommand.KICKOFF_YELLOW:
        case Client.RefBoxCommand.KICKOFF_BLUE:
            state = Client.GameState.PREPARE_KICKOFF;break;
        case Client.RefBoxCommand.PENALTY_YELLOW:
        case Client.RefBoxCommand.PENALTY_BLUE:
            state = Client.GameState.PREPARE_PENALTY;break;
        case Client.RefBoxCommand.GOAL_YELLOW:
        case Client.RefBoxCommand.GOAL_BLUE:
            state = Client.GameState.HALTED;break;
        default:
            console.log("RefBox Command ERROR!!!!!!");
            return;
        }
        controlButtons(state);
        refereeBox.changeCommand(index);
    }
    function controlButtons(state){
        function unify(onOff){ haltGame = stopGame = forceStart = normalStart = teamControl = onOff; }
        switch(state){
        case Client.GameState.HALTED:
            unify(false);
            stopGame = true;
            break;
        case Client.GameState.PREPARE_KICKOFF:
        case Client.GameState.PREPARE_PENALTY:
            unify(false);
            normalStart = true;
            break;
        case Client.GameState.RUNNING:
        case Client.GameState.TIMEOUT_BLUE:
        case Client.GameState.TIMEOUT_YELLOW:
            unify(false);
            haltGame = stopGame = true;
            break;
        case Client.GameState.STOPPED:
            unify(true);
            stopGame = normalStart = false;
            break;
        }
    }
StackLayout {
    width: parent.width;
    height:parent.height;
ScrollView {
    id : root;
    clip : true;
    contentWidth: parent.width;
    contentHeight: parent.height * 2;
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
    ScrollBar.horizontal.interactive: true;
    ScrollBar.vertical.interactive: true;
    Grid{
        id : refereeSetting;
        width:parent.width;
        columnSpacing: 0;
        rowSpacing: 14;
        padding: 5;
        columns: 1;
        topPadding: 15;
        horizontalItemAlignment: Grid.AlignHCenter;
        verticalItemAlignment: Grid.AlignVCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        property int itemWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
        ZGroupBox{
            title:qsTr("Referee Setting")+translator.emptyString;
            property bool visionGetter : false;
            Grid{
                columns: 1;
                columnSpacing: 0;
                rowSpacing: 0;
                verticalItemAlignment: Grid.AlignVCenter;
                horizontalItemAlignment: Grid.AlignLeft;
                width:parent.width;
                padding: 5;
                property int itemWidth : width - 2*padding;
                Button{
                    id:refBoxSwitch;
                    text:(refBoxSwitch.refereeSwitch ? qsTr("Stop") : qsTr("Send"))+translator.emptyString;
                    width:parent.itemWidth;
                    property bool refereeSwitch: false;
                    onClicked: changeState();
                    function changeState(){
                        refBoxSwitch.refereeSwitch = !refBoxSwitch.refereeSwitch;
                        //run();
                    }
                    function run(){
                        if(refBoxSwitch.refereeSwitch){
                            refBoxTimer.start();
                        }else{
                            refBoxTimer.stop();
                        }
                    }
                    //Component.onCompleted: run();
                }
                Button{
                    id:refBoxModeSwitch;
                    text:(refBoxModeSwitch.refereeAutoMode ? qsTr("Auto") : qsTr("Manual"))+translator.emptyString;
                    width:parent.itemWidth;
                    property int refereeAutoMode: 0;
                    visible:refBoxSwitch.refereeSwitch;
                    onClicked: {
                        refereeAutoMode = (refereeAutoMode+1)%3;
                        refereeBox.changeRefereeMode(refereeAutoMode);
                    }
                }
            }
        }
    }
    Grid {
        id : manualControl;
        anchors.top: refereeSetting.bottom;
        width:parent.width;
        columnSpacing: 0;
        rowSpacing: 14;
        columns: 1;
        topPadding: 15;
        padding: 5;
        horizontalItemAlignment: Grid.AlignHCenter;
        verticalItemAlignment: Grid.AlignVCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        property int itemWidth : width - 2*padding;
        visible: refBoxModeSwitch.refereeAutoMode!=2;
        enabled: (refBoxModeSwitch.refereeAutoMode!=2)&&refBoxSwitch.refereeSwitch;
        ZGroupBox{
            title:qsTr("Control Command")+translator.emptyString;
            Grid{
                width:parent.width;
                columns:2;
                property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                rowSpacing: 0;
                columnSpacing: 10;
                spacing: 0;
                padding: 0;
                ZRefButton{
                    property int index : Client.RefBoxCommand.HALT;
                    text:qsTr("Halt")+translator.emptyString;
                    onClicked:getButtonsCommand(index);
                    enabled: haltGame;
                }
                ZRefButton{
                    property int index : Client.RefBoxCommand.STOP_GAME;
                    text:qsTr("Stop Game")+translator.emptyString;
                    onClicked:getButtonsCommand(index);
                    enabled: stopGame;
                }
                ZRefButton{
                    property int index : Client.RefBoxCommand.FORCE_START;
                    text:qsTr("Force Start")+translator.emptyString;
                    onClicked:getButtonsCommand(index);
                    enabled: forceStart;
                }
                ZRefButton{
                    property int index : Client.RefBoxCommand.NORMAL_START;
                    text:qsTr("Normal Start")+translator.emptyString;
                    onClicked:getButtonsCommand(index);
                    enabled: normalStart;
                }
            }
        }
        ZGroupBox{
            title:qsTr("Yellow Team Control")+translator.emptyString;
            enabled: teamControl;
            Grid{
                width:parent.width;
                rows:4;
                rowSpacing: 0;
                columns:1;
                property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                Grid{
                    width:parent.width;
                    columns:2;
                    columnSpacing: 10;
                    property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                    Repeater{
                        model:[
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.KICKOFF_YELLOW,cmd_str:qsTr("Kick off")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.PENALTY_YELLOW,cmd_str:qsTr("Penalty")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.DIRECT_KICK_YELLOW,cmd_str:qsTr("Direct Kick")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.INDIRECT_KICK_YELLOW,cmd_str:qsTr("Indirect Kick")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.TIMEOUT_YELLOW,cmd_str:qsTr("Timeout")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.BALL_PLACEMENT_YELLOW,cmd_str:qsTr("Ball Placement")+translator.emptyString},
                            {cmd_type:2,cmd_num:Client.RefBoxCommand.GOAL_YELLOW,cmd_str:qsTr("Goal")+translator.emptyString}
                        ]
                        ZRefButton{
                            property int index : modelData.cmd_num;
                            text:qsTr(modelData.cmd_str);
                            //highlighted:next_command == index;
                            onClicked:getButtonsCommand(index);
                            Component.onCompleted: {
                                color = getColor(modelData.cmd_type); //color[modelData.cmd_type];
                            }
                        }
                    }
                }
            }
        }
        ZGroupBox{
            title:qsTr("Blue Team Control")+translator.emptyString;
            enabled: teamControl;
            Grid{
                width:parent.width;
                rows:4;
                columns:1;
                rowSpacing: 0;
                property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                Grid{
                    width:parent.width;
                    columns:2;
                    columnSpacing: 10;
                    property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                    Repeater{
                        model:[
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.KICKOFF_BLUE,cmd_str:qsTr("Kick off")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.PENALTY_BLUE,cmd_str:qsTr("Penalty")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.DIRECT_KICK_BLUE,cmd_str:qsTr("Direct Kick")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.INDIRECT_KICK_BLUE,cmd_str:qsTr("Indirect Kick")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.TIMEOUT_BLUE,cmd_str:qsTr("Timeout")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.BALL_PLACEMENT_BLUE,cmd_str:qsTr("Ball Placement")+translator.emptyString},
                            {cmd_type:1,cmd_num:Client.RefBoxCommand.GOAL_BLUE,cmd_str:qsTr("Goal")+translator.emptyString}
                        ]
                        ZRefButton{
                            property int index : modelData.cmd_num;
                            text:qsTr(modelData.cmd_str);
                            //highlighted:next_command == index;
                            onClicked:getButtonsCommand(index);
                            Component.onCompleted: {
                                color = getColor(modelData.cmd_type); //color[modelData.cmd_type];
                            }
                        }
                    }
                }
            }
        }
        ZGroupBox{
            title:qsTr("Next Command")+translator.emptyString;
            Grid{
                width:parent.width;
                columns:2;
                property int buttonWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                rowSpacing: 0;
                columnSpacing: 10;
                spacing: 0;
                padding: 0;
                Repeater{
                    model: [
                        {cmd_type:0,cmd_str:qsTr("Stop Game")+translator.emptyString,cmd_num:Client.RefBoxCommand.STOP_GAME},
                        {cmd_type:0,cmd_str:qsTr("Force Start")+translator.emptyString,cmd_num:Client.RefBoxCommand.FORCE_START},
                        {cmd_type:2,cmd_str:qsTr("Direct Yellow")+translator.emptyString,cmd_num:Client.RefBoxCommand.DIRECT_KICK_YELLOW},
                        {cmd_type:1,cmd_str:qsTr("Direct Blue")+translator.emptyString,cmd_num:Client.RefBoxCommand.DIRECT_KICK_BLUE},
                        {cmd_type:2,cmd_str:qsTr("Indirect Yellow")+translator.emptyString,cmd_num:Client.RefBoxCommand.INDIRECT_KICK_YELLOW},
                        {cmd_type:1,cmd_str:qsTr("Indirect Blue")+translator.emptyString,cmd_num:Client.RefBoxCommand.INDIRECT_KICK_BLUE},
                    ]
                    ZRefButton{
                        property int index : modelData.cmd_num;
                        text:qsTr(modelData.cmd_str);
                        highlighted:next_command == index;
                        onClicked: {
                            next_command = index;
                            refereeBox.setNextCommand(index);
                        }
                        Component.onCompleted: {
                            color = getColor(modelData.cmd_type); //color[modelData.cmd_type];
                        }
                    }
                }
            }
        }
    }
}
}
}
