import QtQuick 2.6
import QtQuick.Controls 1.4 as Control
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtGamepad 1.0
import Components 1.0
import Gamepad 1.0
import Owl 1.0 as Owl

Page{
    id:window;
	property bool useGamepad:false;
    Timer{
        id:updateTimer
        interval:1000;
        running:!crazyConnect.ifConnected; //true;
        repeat:true;
        onTriggered: {
            radioComboBox.updateModel();
        }
    }
	Timer{
        id:timer;
        interval:15;//15ms启动一次
        running:false;
        repeat:true;
        onTriggered: {
            if(switchControl.checked)
                crazyShow.updateFromGamepad();
            crazyShow.updateByCallBack();
            crazyShow.updateCommand();//调用interaction.updateCommandParams()
            interaction.sendCommand(1);//把数据发出去，仅限一辆车
            if(crazyShow.shoot){
                crazyShow.shoot = !crazyShow.shoot;
            }
        }
    }
    Owl.Interaction { id : interaction }
    StackLayout {
        width: parent.width;
        height:parent.height;
        ScrollView {
            clip: true;
            contentWidth: parent.width;
            contentHeight: parent.height * 2;
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            ScrollBar.horizontal.interactive: true;
            ScrollBar.vertical.interactive: true;
            Column{
                anchors.fill:parent;
                Rectangle{
                    id : radio;
                    width:parent.width;
                    height:420;
                    color:"transparent";
                    Rectangle{
                        width:parent.width;
                        anchors.top: parent.top;
                        anchors.bottom: parent.bottom;
                        color:"transparent";
                        id:radioRectangle;
                        //最上面一条Box
                        ZGroupBox{
                            id : crazyListRectangle;
                            width: parent.width - 15;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.top: parent.top;
                            anchors.margins: 10;
                            title :qsTr("Sender Setting");
                            Grid{
                                height:parent.height;
                                id : crazyListView;
                                verticalItemAlignment: Grid.AlignVCenter;
                                horizontalItemAlignment: Grid.AlignLeft;
                                anchors.horizontalCenter: parent.horizontalCenter;
                                columnSpacing: 40;
                                rowSpacing: 5;
                                columns:4;
                                enabled: !crazyConnect.ifConnected;
                                property int itemWidth : 90;
                                ZText{
                                    text: qsTr("Control Mode");
                                }
                                Control.Switch {
                                    id : switchControl;
                                    checked :window.useGamepad
                                    onClicked: {
                                        window.useGamepad = checked;
                                    }
                                }
                                ZText{
                                    text: qsTr(" ");
                                }
                                ZText{
                                    text: qsTr(" ");
                                }
                                //端口相关
                                ZText{
                                    text: qsTr("Ports");
                                    width:parent.itemWidth;
                                }
                                Control.ComboBox{
                                    id:radioComboBox;
                                    model:interaction.getSerialPortsList();
                                    onActivated: interaction.changeSerialPort(currentIndex);
                                    width:parent.itemWidth;
                                    function updateModel(){
                                        model = interaction.getSerialPortsList();
                                        if(currentIndex >= 0)
                                            interaction.changeSerialPort(currentIndex);
                                    }
                                    Component.onCompleted: updateModel();
                                }
                                //频率相关
                                ZText{
                                    text: qsTr("Frequency");
                                    width:parent.itemWidth;
                                }
                                Control.ComboBox{
                                    model: interaction.getFrequencyList();
                                    onActivated: interaction.changeSerialFrequency(currentIndex);
                                    width:parent.itemWidth;
                                }
                            }
                        }
                        //连接按钮
                        Control.Button{
                            id : crazyConnect;
                            text : (ifConnected ? qsTr("Disconnect") : qsTr("Connect"));
                            property bool ifConnected:false;
                            anchors.top: crazyListRectangle.bottom;
                            anchors.right: parent.right;
                            anchors.rightMargin: 20;
                            anchors.topMargin: 10;
                            onClicked: clickEvent();
                            function clickEvent(){
                                if(ifConnected){
                                    timer.stop();
                                    if(crazyStart.ifStarted) crazyStart.handleClickEvent();
                                    interaction.connectSerialPort(ifConnected);
                                }else{
                                    if(radioComboBox.currentText != ""){
                                        interaction.connectSerialPort(ifConnected);
                                    }
                                }
                                ifConnected = !ifConnected;
                            }
                        }
                        //下面大的Box
                        ZGroupBox{
                            title : qsTr("Manual Control");
                            width:parent.width - 15;
                            anchors.top:crazyConnect.bottom;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            id : groupBox2;
                            Grid{
                                id : crazyShow;
                                columns: 6;//6列
                                verticalItemAlignment: Grid.AlignVCenter;
                                horizontalItemAlignment: Grid.AlignLeft;
                                anchors.horizontalCenter: parent.horizontalCenter;
                                columnSpacing: 10;
                                rowSpacing: 5;
                                property int robotID : 0;//Robot
                                property int velX : 0;//Vx
                                property int velY : 0;//Vy
                                property int velR : 0;//Vr
                                property bool shoot : false;//Shoot
                                property bool dribble : false;//Dribble

                                property int velXStep : 15;//VxStep
                                property int velYStep : 15;//VyStep
                                property int velRStep : 15;//VrStep
                                property int mode : 2;//KickMode
                                property int modeTypes : 4;//num of KickMode
                                property int dribbleLevel : 2;//DribLevel
                                property int rushSpeed : 100;//RushSpeed

                                property int m_VELX : 255//MaxVelX
                                property int m_VELY : 255//MaxVelY
                                property int velocityRMax : 511;//MaxVelR
                                property int power : 20;//KickPower

                                property int m_VELR : 1023
                                property int velocityMax : 511;//最大速度
                                property int dribbleMaxLevel : 3;//吸球最大等级
                                property int kickPowerMax: 127;//最大踢球力量
                                property int convertPowerMax: 800;//最大踢球力量
                                
                                property bool infrared: false;
                                property bool autoShoot: false;
                                property bool autoDribble: false;
                                property bool rush: false;
                                property bool back: false;
                                property int itemWidth : 99;

                                ZText{ text:qsTr("Robot") }
                                //最多12辆车
                                ZSpinBox{ minimumValue:0; maximumValue:15; value:parent.robotID; width:parent.itemWidth
                                    onEditingFinished:{parent.robotID = value}}
                                ZText{ text:"Stop" }
                                //有用吗？
                                Control.Button{ 
                                    text:qsTr("[Space]");width:parent.itemWidth 
                                    onClicked:crazyShow.updateStop();
                                }
                                ZText{ text:" " }
                                ZText{ text:" " }
                                ZText{ text:qsTr("Vx [W/S]") }
                                //Vx:(-m_VELX, m_VELX)
                                ZSpinBox{ minimumValue:-crazyShow.m_VELX; maximumValue:crazyShow.m_VELX; value:parent.velX;width:parent.itemWidth
                                    onEditingFinished:{parent.velX = value;}}
                                ZText{ text:qsTr("VxStep") }
                                //VxStep:(1, m_VELX)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.m_VELX; value:parent.velXStep;width:parent.itemWidth;
                                    onEditingFinished:{parent.velXStep = value;}}
                                ZText{ text:qsTr("MaxVelX") }
                                //MaxVelX:(1, velocityMax)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.velocityMax; value:parent.m_VELX;width:parent.itemWidth
                                    onEditingFinished:{parent.m_VELX = value;}}
                                ZText{ text:qsTr("Vy [A/D]") }
                                //Vy:(-m_VELY, m_VELY)
                                ZSpinBox{ minimumValue:-crazyShow.m_VELY; maximumValue:crazyShow.m_VELY; value:parent.velY;width:parent.itemWidth
                                    onEditingFinished:{parent.velY = value;}}
                                ZText{ text:qsTr("VyStep") }
                                //VyStep:(1, m_VELY)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.m_VELY; value:parent.velYStep;width:parent.itemWidth
                                    onEditingFinished:{parent.velYStep = value;}}
                                ZText{ text:qsTr("MaxVelY") }
                                //MaxVelY:(1, velocityMax)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.velocityMax; value:parent.m_VELY;width:parent.itemWidth
                                    onEditingFinished:{parent.m_VELY = value;}}
                                ZText{ text:qsTr("Vr [Z/C]") }
                                //Vr:(-m_VELR, m_VELR)
                                ZSpinBox{ minimumValue:-crazyShow.m_VELR; maximumValue:crazyShow.m_VELR; value:parent.velR;width:parent.itemWidth
                                    onEditingFinished:{parent.velR = value;}}
                                ZText{ text:qsTr("VrStep") }
                                //VrStep:(1, m_VELR)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.m_VELR; value:parent.velRStep;width:parent.itemWidth
                                    onEditingFinished:{parent.velRStep = value;}}
                                ZText{ text:qsTr("MaxVelR") }
                                //MaxVelR:(1, velocityRMax)
                                ZSpinBox{ minimumValue:1; maximumValue:crazyShow.velocityRMax; value:parent.m_VELR;width:parent.itemWidth
                                    onEditingFinished:{parent.m_VELR = value;}}
                                ZText{ text:qsTr("Shoot [E]") }
                                Control.Button{ text:(parent.shoot? qsTr("true") : qsTr("false"));width:parent.itemWidth
                                    onClicked: {
                                        parent.shoot = !parent.shoot;
                                    }
                                }
                                ZText{ text:qsTr("KickMode [X]") }
                                Control.Button{ text:selectMode();width:parent.itemWidth
                                    onClicked: {
                                        parent.mode = (parent.mode + 1) % parent.modeTypes;
                                    }
                                    function selectMode() {
                                        if (parent.mode == 0) 
                                            return "convert flat";
                                        else if (parent.mode == 1)
                                            return "convert chip";
                                        else if (parent.mode == 2)
                                            return "flat";
                                        else 
                                            return "chip";
                                    }
                                }
                                ZText{ text:qsTr("KickPower") }
                                //KickPower:(1, kickPowerMax)
                                ZSpinBox{ minimumValue:0; maximumValue:parent.mode>1? parent.kickPowerMax:parent.convertPowerMax; value:parent.power;width:parent.itemWidth
                                    onEditingFinished:{parent.power = value;}}
                                ZText{ text:qsTr("Dribble [Q]") }
                                Control.Button{ text:(parent.dribble ? qsTr("true") : qsTr("false"));width:parent.itemWidth
                                    onClicked: {
                                        parent.dribble = !parent.dribble;
                                    }
                                }
                                ZText{ text:qsTr("DribbleLevel") }
                                //DribbleLevel:(0, dribbleMaxLevel)
                                ZSpinBox{ minimumValue:0; maximumValue:crazyShow.dribbleMaxLevel; value:parent.dribbleLevel;width:parent.itemWidth
                                    onEditingFinished:{parent.dribbleLevel = value;}}
                                Rectangle{
                                    width:parent.itemWidth; height:20; color:changeColor();
                                    function changeColor(){
                                        if(parent.shoot) return "red";
                                        else if(parent.dribble) return "blue";
                                        else return "transparent"; //"lightgrey";
                                    }
                                }
                                ZText{ text:" " }
                                ZText{ text:qsTr("AutoShoot") }
                                Control.Button{ text:(parent.autoShoot ? qsTr("true") : qsTr("false"));width:parent.itemWidth
                                    onClicked: {
                                        parent.autoShoot = !parent.autoShoot;
                                    }
                                }
                                ZText{ text:qsTr("AutoDribble") }
                                Control.Button{ text:(parent.autoDribble ? qsTr("true") : qsTr("false"));width:parent.itemWidth
                                    onClicked: {
                                        parent.autoDribble = !parent.autoDribble;
                                    }
                                }
                                ZText{ text:qsTr("Infrared") }
                                Rectangle{ width:parent.itemWidth; height:20; color:parent.infrared? "red" : "lightgrey"; }
                                ZText{ text:qsTr("Rush") }
                                Control.Button{ text:(parent.rush ? qsTr("true") : qsTr("false"));width:parent.itemWidth;
                                    onClicked: {
                                        //parent.rush = !parent.rush;
                                        //crazyShow.updateRush();
                                    }
                                }
                                ZText{ text:qsTr("Back") }
                                Control.Button{ text:(parent.back ? qsTr("true") : qsTr("false"));width:parent.itemWidth;
                                    onClicked: {
                                        //parent.back = !parent.back;
                                        //crazyShow.updateBack();
                                    }
                                }
                                ZText{ text:qsTr("RushSpeed") }
                                //RushSpeed:(0, m_VELX)
                                ZSpinBox{ minimumValue:0; maximumValue:crazyShow.m_VELX; value:parent.rushSpeed;width:parent.itemWidth
                                    onEditingFinished:{parent.rushSpeed = value;}}
                                function updateByCallBack(){
                                    crazyShow.infrared = interaction.getInfrared(crazyShow.robotID);
                                    if(crazyShow.autoShoot && !crazyShow.shoot){
                                        crazyShow.shoot = crazyShow.infrared;
                                        crazyShow.power = 100;
                                    }
                                    if(crazyShow.autoDribble && !crazyShow.dribble){
                                        crazyShow.dribble = crazyShow.infrared;
                                        crazyShow.dribbleLevel = 2;
                                    }
                                }
                                function updateFromGamepad(){
                                    crazyShow.velX = -parseInt(gamepad.axisLeftY*10)/10.0*crazyShow.m_VELX;
                                    crazyShow.velY = parseInt(gamepad.axisLeftX*10)/10.0*crazyShow.m_VELY;
                                    crazyShow.velR = parseInt(gamepad.axisRightX*10)/10.0*crazyShow.m_VELR*0.3;
                                    crazyShow.power = parseInt(gamepad.buttonL2*10)/10.0*crazyShow.kickPowerMax;
                                    if(gamepad.buttonX > 0){    
                                        crazyShow.mode = 3;
                                        crazyShow.shoot = gamepad.buttonX;
                                    }
                                    else if(gamepad.buttonY > 0){
                                        crazyShow.mode = 2;
                                        crazyShow.shoot = gamepad.buttonY;
                                    }
                                    else{
                                        crazyShow.shoot = 0;
                                    }

                                    if(gamepad.buttonR2 > 0){
                                        crazyShow.dribbleLevel =  parseInt(gamepad.buttonR2*10)/10.0*crazyShow.dribbleMaxLevel;
                                        crazyShow.dribble = true ;
                                    }
                                    else{
                                        crazyShow.dribble = false ;
                                    }

                                    if(gamepad.buttonL1 > 0){
                                        crazyShow.autoShoot = !crazyShow.autoShoot;
                                    }
                                    if(gamepad.buttonR1 > 0){
                                        crazyShow.autoDribble = !crazyShow.autoDribble;
                                    }
                                    if(gamepad.buttonA > 0){
                                        crazyShow.rush = true;
                                        crazyShow.updateRush();
                                    }
                                    else if(gamepad.buttonB > 0){
                                        crazyShow.back = true;
                                        crazyShow.updateBack();
                                    }
                                    else{
                                        crazyShow.back = crazyShow.rush = false;
                                    }
                                }
                                function updateStop(){
                                    crazyShow.velX = 0;
                                    crazyShow.velY = 0;
                                    crazyShow.velR = 0;
                                    crazyShow.shoot = false;
                                    crazyShow.dribble = false;
                                    crazyShow.autoShoot = false;
                                    crazyShow.autoDribble = false;
                                }
                                function updateRush(){
                                    //if(crazyShow.rush){
                                        crazyShow.velX = crazyShow.rushSpeed;
                                        crazyShow.velY = 0;
                                        crazyShow.velR = 0;
                                        crazyShow.shoot = false; // true;
                                        crazyShow.dribble = false;
                                        crazyShow.autoShoot = true;
                                        crazyShow.autoDribble = false;
                                    //}else{
                                    //    crazyShow.updateStop();
                                    //}
                                }
                                function updateBack(){
                                    //if(crazyShow.back){
                                        crazyShow.velX = -crazyShow.rushSpeed;
                                        crazyShow.velY = 0;
                                        crazyShow.velR = 0;
                                        crazyShow.shoot = false;
                                        crazyShow.dribble = true;
                                        crazyShow.autoShoot = false;
                                        crazyShow.autoDribble = false;
                                    //}else{
                                    //    crazyShow.updateStop();
                                    //}
                                }
                                //键盘响应实现
                                Keys.onPressed:getFocus(event);
                                function getFocus(event){
                                    switch(event.key){
                                    case Qt.Key_Enter:
                                    case Qt.Key_Return:
                                    case Qt.Key_Escape:
                                        crazyShow.focus = true;
                                        break;
                                    default:
                                        event.accepted = false;
                                        return false;
                                    }
                                    event.accepted = true;
                                }
                                function handleKeyboardEvent(e){
                                    switch(e){
                                    case 'x':{crazyShow.mode = (crazyShow.mode + 1) % crazyShow.modeTypes;break;}
                                    case 'a':{crazyShow.velY = crazyShow.limitVel(crazyShow.velY-crazyShow.velYStep,-crazyShow.m_VELY,crazyShow.m_VELY);
                                        break;}
                                    case 'd':{crazyShow.velY = crazyShow.limitVel(crazyShow.velY+crazyShow.velYStep,-crazyShow.m_VELY,crazyShow.m_VELY);
                                        break;}
                                    case 'w':{crazyShow.velX = crazyShow.limitVel(crazyShow.velX+crazyShow.velXStep,-crazyShow.m_VELX,crazyShow.m_VELX);
                                        break;}
                                    case 's':{crazyShow.velX = crazyShow.limitVel(crazyShow.velX-crazyShow.velXStep,-crazyShow.m_VELX,crazyShow.m_VELX);
                                        break;}
                                    case 'q':{crazyShow.dribble = !crazyShow.dribble;
                                        break;}
                                    case 'e':{crazyShow.shoot = !crazyShow.shoot;
                                        break;}
                                    case 'z':{crazyShow.velR = crazyShow.limitVel(crazyShow.velR-crazyShow.velRStep,-crazyShow.m_VELR,crazyShow.m_VELR);
                                        break;}
                                    case 'c':{crazyShow.velR = crazyShow.limitVel(crazyShow.velR+crazyShow.velRStep,-crazyShow.m_VELR,crazyShow.m_VELR);
                                        break;}
                                    case 'S':{crazyShow.updateStop();
                                        break;}
                                    case 'g':{crazyShow.rush = !crazyShow.rush;
                                        updateRush();
                                        break;}
                                    default:
                                        return false;
                                    }
                                    updateCommand();
                                }
                                //interaction.updateCommandParams在C++中实现
                                function updateCommand(){
                                    interaction.updateCommandParams(crazyShow.robotID,crazyShow.velX,crazyShow.velY,crazyShow.velR,crazyShow.dribble,crazyShow.dribbleLevel,crazyShow.mode,crazyShow.shoot,crazyShow.power);
                                }
                                function limitVel(vel,minValue,maxValue){
                                    if(vel>maxValue) return maxValue;
                                    if(vel<minValue) return minValue;
                                    return vel;
                                }
                                Shortcut{
                                    sequence:"G";
                                    onActivated:crazyShow.handleKeyboardEvent('g');
                                }
                                Shortcut{
                                    sequence:"A";
                                    onActivated:crazyShow.handleKeyboardEvent('a');
                                }
                                Shortcut{
                                    sequence:"X";
                                    onActivated:crazyShow.handleKeyboardEvent('x');
                                }
                                Shortcut{
                                    sequence:"D"
                                    onActivated:crazyShow.handleKeyboardEvent('d');
                                }
                                Shortcut{
                                    sequence:"W"
                                    onActivated:crazyShow.handleKeyboardEvent('w');
                                }
                                Shortcut{
                                    sequence:"S"
                                    onActivated:crazyShow.handleKeyboardEvent('s');
                                }
                                Shortcut{
                                    sequence:"Q"
                                    onActivated:crazyShow.handleKeyboardEvent('q');
                                }
                                Shortcut{
                                    sequence:"E"
                                    onActivated:crazyShow.handleKeyboardEvent('e');
                                }
                                Shortcut{
                                    sequence:"Z"
                                    onActivated:crazyShow.handleKeyboardEvent('z');
                                }
                                Shortcut{
                                    sequence:"C"
                                    onActivated:crazyShow.handleKeyboardEvent('c');
                                }
                                Shortcut{
                                    sequence:"Space"
                                    onActivated:crazyShow.handleKeyboardEvent('S');
                                }
                            }
                        }
                        //最下面的Start按钮
                        Control.Button{
                            id:crazyStart;
                            text:qsTr("Start");
                            property bool ifStarted:false;
                            anchors.right:parent.right;
                            anchors.rightMargin: 20;
                            anchors.top:groupBox2.bottom;
                            anchors.topMargin: 10;
                            enabled : crazyConnect.ifConnected;//如果连接成功按钮才有效
                            onClicked:{
                                handleClickEvent();
                            }
                            function handleClickEvent(){
                                if(ifStarted){//若开始，定时器关闭
                                    timer.stop();
                                }else{//若未开始，定时器打开
                                    timer.start();
                                }
                                ifStarted = !ifStarted;
                                text = (ifStarted ? qsTr("Stop") : qsTr("Start"));
                            }
                        }
                    }
                }
                Rectangle{
                    id:blank;
                    height:20;
                    width:parent.width;
                    color:"transparent"
                }
                //Repeater{
                //    model:["Player1","Player2"]
                Rectangle{
                    id : gamepadInterface;
                    height:parent.height*0.4 - radio.height;
                    width:parent.width;
                    color:"#333"
                    Item {
                        id: background
                        anchors.fill: parent

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 8
                            RowLayout {
                                id: topRow
                                width: parent.width
                                ColumnLayout {
                                    id: buttonL2Item
                                    Layout.alignment: Qt.AlignLeft
                                    ButtonImage {
                                        id: leftTrigger
                                        Layout.alignment: Qt.AlignCenter
                                        source: "/resource/gamepad/xboxControllerLeftTrigger.png"
                                        active: gamepad.buttonL2 != 0
                                    }
                                    Control.ProgressBar {
                                        id: buttonL2Value
                                        value: gamepad.buttonL2
                                    }
                                }

                                Item {
                                    id: centerButtons
                                    Layout.alignment: Qt.AlignCenter
                                    Layout.fillWidth: true
                                    height: guideButton.height
                                    width: guideButton.width + 16 + backButton.width + startButton.width
                                    ButtonImage {
                                        id: backButton
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.right: guideButton.left
                                        anchors.rightMargin: 8
                                        source: "/resource/gamepad/xboxControllerBack.png"
                                        active: gamepad.buttonSelect
                                    }
                                    ButtonImage {
                                        id: guideButton
                                        anchors.centerIn: parent
                                        source: "/resource/gamepad/xboxControllerButtonGuide.png"
                                        active: gamepad.buttonGuide
                                    }
                                    ButtonImage {
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.left: guideButton.right
                                        anchors.leftMargin: 8
                                        id: startButton
                                        source: "/resource/gamepad/xboxControllerStart.png"
                                        active: gamepad.buttonStart
                                    }
                                }

                                ColumnLayout {
                                    id: buttonR2Item
                                    Layout.alignment: Qt.AlignRight
                                    ButtonImage {
                                        id: rightTrigger
                                        Layout.alignment: Qt.AlignCenter
                                        source: "/resource/gamepad/xboxControllerRightTrigger.png"
                                        active: gamepad.buttonR2 != 0
                                    }

                                    Control.ProgressBar {
                                        id: buttonR2Value
                                        value: gamepad.buttonR2
                                    }
                                }
                            }

                            RowLayout {
                                id: middleRow
                                ButtonImage {
                                    id: buttonL1
                                    source: "/resource/gamepad/xboxControllerLeftShoulder.png"
                                    active: gamepad.buttonL1
                                }
                                Item {
                                    id: spacer1
                                    Layout.fillWidth: true
                                }

                                ButtonImage {
                                    id: buttonR1
                                    source: "/resource/gamepad/xboxControllerRightShoulder.png"
                                    active: gamepad.buttonR1
                                }
                            }

                            RowLayout {
                                id: bottomRow
                                width: parent.width
                                DPad {
                                    id: dPad
                                    Layout.alignment: Qt.AlignLeft
                                    gamepad: gamepad
                                }

                                LeftThumbstick {
                                    id: leftThumbstick
                                    Layout.alignment: Qt.AlignLeft
                                    gamepad: gamepad
                                }

                                Item {
                                    id: spacer2
                                    Layout.fillWidth: true
                                }

                                RightThumbstick {
                                    id: rightThumbstick
                                    Layout.alignment: Qt.AlignRight
                                    gamepad: gamepad
                                }

                                Item {
                                    width: 100
                                    height: 100
                                    Layout.alignment: Qt.AlignRight
                                    ButtonImage {
                                        id: buttonA
                                        anchors.bottom: parent.bottom
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        source: "/resource/gamepad/xboxControllerButtonA.png";
                                        active: gamepad.buttonA
                                    }
                                    ButtonImage {
                                        id: buttonB
                                        anchors.right: parent.right
                                        anchors.verticalCenter: parent.verticalCenter
                                        source: "/resource/gamepad/xboxControllerButtonB.png";
                                        active: gamepad.buttonB
                                    }
                                    ButtonImage {
                                        id: buttonX
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                        source: "/resource/gamepad/xboxControllerButtonX.png";
                                        active: gamepad.buttonX
                                    }
                                    ButtonImage {
                                        id: buttonY
                                        anchors.top: parent.top
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        source: "/resource/gamepad/xboxControllerButtonY.png";
                                        active: gamepad.buttonY
                                    }
                                }
                            }
                        }
                    }

                    //Connections {
                    //    target: GamepadManager
                    //    onGamepadConnected: gamepad.deviceId = deviceId
                    //}

                    Gamepad {
                        id: gamepad
                        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1
                        onButtonGuideChanged: {
                            if(gamepad.buttonGuide == false)
                                switchControl.checked = !switchControl.checked
                        }
                        onButtonStartChanged: {
                            if(gamepad.buttonStart == false){
//                              timer.start();
                                crazyStart.handleClickEvent();
                            }
                        }
                        onButtonUpChanged: {
                            if(gamepad.buttonUp == false){
                                crazyShow.robotID += 1;
                            }
                        }
                        onButtonDownChanged: {
                            if(gamepad.buttonDown == false){
                                crazyShow.robotID -= 1;
                            }
                        }
                    }
                }
            }
        }
    }
}
