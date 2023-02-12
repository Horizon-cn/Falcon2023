import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Owl 1.0 as Owl
import Components 1.0

Page{
    id:control;
    //property bool radioConnect : false;
    property bool blueRBKConnect : false;
    property bool yellowRBKConnect : false;
    property bool simConnect : false;
    //property bool crayConnect : false;
    property bool monitorConnect : false;
    property bool isSimulation : true;
    property bool kill : false;

    Timer{
        id:oneSecond;
        interval:800;
        running:!visionControls.ifConnected; //true;
        repeat:true;
        onTriggered: {
            interaction.updateInterfaces();
            interfaces4vision.updateModel();
            //radioComboBox.updateModel();
        }
    }

    Owl.Interaction{
        id:interaction;
    }

    //Owl.Option{id:myOption}
    /**
    header:TabBar {
        id: bar
        width:parent.width;
        contentHeight:50;
        height:contentHeight;
        position: TabBar.Header;
        TabButton {
            icon.source:"/resource/camera.png";
        }
        TabButton {
            icon.source:"/resource/referee.png";
        }
        TabButton {
            icon.source:"/resource/viewer.png";
        }
        TabButton {
            icon.source:"/resource/joy3.png";
        }
        TabButton {
            icon.source:"/resource/settings.png";
        }
    }
    **/
    StackLayout {
        id:controlLayout;
        width: parent.width;
        height:parent.height; //fix display bug at low resolution.2019.3.29 wz
    //    currentIndex: bar.currentIndex;
        ScrollView {
            clip: true;
            contentWidth: parent.width;
            contentHeight: parent.height * 2;
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            ScrollBar.horizontal.interactive: true;
            ScrollBar.vertical.interactive: true;
            Grid{
                padding: 5;
                topPadding: 15;
                width:controlLayout.width;
                //height:controlLayout.height;
                columns: 1;
                horizontalItemAlignment: Grid.AlignHCenter;
                verticalItemAlignment: Grid.AlignVCenter;
                id:vision
                columnSpacing: 0;
                rowSpacing: 0;
                property int itemWidth : width - padding*2;
                ZGroupBox{
                    title: qsTr("Vision")
                    Column{
                        id:visionControls;
                        width:parent.width;
                        height:parent.height;
                        spacing: 0;
                        padding:0;
                        property int itemWidth : width - 2*padding;
                        property bool ifConnected : false;
                        ZComboBox{
                            id:interfaces4vision;
                            enabled:!visionControls.ifConnected;
                            model:interaction.getInterfaces();
                            onActivated: interaction.changeVisionInterface(currentIndex);
                            function updateModel(){
                                model = interaction.getInterfaces();
                                if(currentIndex >= 0)
                                    interaction.changeVisionInterface(currentIndex);
                            }
                            Component.onCompleted: {
                                interaction.getInterfaces();
                            }
                        }
                        ZComboBox{
                            id:grsimInterface;
                            enabled:!visionControls.ifConnected;
                            model:interaction.getGrsimInterfaces();
                            onActivated: interaction.changeGrsimInterface(currentIndex);
                            function updateModel(){
                                model = interaction.getGrsimInterfaces();
                                if(currentIndex >= 0)
                                    interaction.changeGrsimInterface(currentIndex);
                            }
                            Component.onCompleted: {
                                interaction.getGrsimInterfaces();
                            }
                        }
                        ZSwitch{
                            id:simulation;
                            enabled:!visionControls.ifConnected;
                            width:parent.itemWidth;
                            leftText:qsTr("Simulation");
                            rightText:qsTr("Real");
                            checked: false;
                            onCheckedChanged: {
                                control.isSimulation = !control.isSimulation;
                            }
                        }
                        Grid{
                            id:cameraControls;
                            enabled:!visionControls.ifConnected;
                            width:parent.itemWidth - 10;
                            columns:8;
                            columnSpacing: 0;
                            rowSpacing: 0;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            verticalItemAlignment: Grid.AlignVCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            property int itemWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                            Repeater{
                                model:parent.columns;
                                CheckBox{
                                    property int itemIndex : index;
                                    checked: index < interaction.getCameraNumber();
                                    width:cameraControls.itemWidth;
                                    height:40;
                                    // anchors.fill: parent;
                                    onCheckStateChanged: {
                                        interaction.controlCamera(itemIndex,checked);
                                    }
                                }
                            } 
                        }
                        Button{
                            width:parent.itemWidth;
                            icon.source:visionControls.ifConnected ? "/resource/connect.png" : "/resource/disconnect.png";
                            onClicked: {
                                visionControls.ifConnected = !visionControls.ifConnected;
                                interaction.setVision(visionControls.ifConnected,simulation.checked);
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("Simulator")
                    visible: control.isSimulation;
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        rowSpacing: 0;
                        columns: 2;//3;
                        columnSpacing: 5
                        property int itemWidth :width - 2*padding;
                        Grid {
                            property int buttonWidth: parent.itemWidth/2; //60;
                            ZButton{
                                id: simCtrlBtn;
                                icon.source:control.simConnect ? "/resource/stop.png" : "/resource/start.png";
                                onClicked: {
                                    control.simConnect = !control.simConnect;
                                    interaction.controlSim(control.simConnect, simModeBtn.text == "Show");
                                    interaction.controlProcess(2, control.simConnect);
                                }
                            }
                        }
                        Grid {
                            property int buttonWidth: parent.width - parent.itemWidth/2 - 4; //70;
                            ZButton{
                                id: simModeBtn;
                                enabled:!control.simConnect;
                                text: "Hide";
                                onClicked: {
                                    simModeBtn.text = simModeBtn.text == "Hide" ? "Show": "Hide";
                                }
                            }
                        }/**
                        Grid {
                            property int buttonWidth: (parent.width - simCtrlBtn.parent.buttonWidth - simModeBtn.parent.buttonWidth-10);
                            ZButton{
                                id:simPathBtn;
                                enabled:!control.simConnect;
                                text: interaction.getSIMpath();
                                onClicked: {
                                    interaction.chooseSIMpath();
                                    simPathBtn.text= interaction.getSIMpath();
                                }
                                contentItem: Label {
                                    text: simPathBtn.text
                                    font: simPathBtn.font
                                    elide: Text.ElideMiddle
                                }
                            }
                        }**/
                    }
                }/**
                ZGroupBox{
                    title: qsTr("Radio")
                    visible: !control.isSimulation;
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        columns:1;
                        property int itemWidth : width - 2*padding;
                        SpinBox{
                            id:medusaFrq;
                            enabled: !control.radioConnect;
                            width:parent.itemWidth;
                            from:0;to:interaction.getMaxFrequency();
                            wrap:true;
                            value:interaction.getFrequency();
                            onValueModified: {
                                if(!interaction.changeSerialFrequency(value))
                                    value:interaction.getFrequency();
                            }
                        }
                        ComboBox{
                            id:radioComboBox;
                            enabled: !control.radioConnect;
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
                        Button{
                            width:parent.itemWidth;
                            icon.source:control.radioConnect ? "/resource/connect.png" : "/resource/disconnect.png";
                            onClicked: {
                                if(interaction.connectSerialPort(control.radioConnect)){
                                    control.radioConnect = !control.radioConnect;
                                }
                            }
                        }
                    }
                }**//**
                ZGroupBox{
                    title: qsTr("Cray")
                    visible: !control.isSimulation;
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        rowSpacing: 0;
                        columns:2;
                        columnSpacing: 5
                        property int itemWidth :width - 2*padding;
                        Grid {
                            property int buttonWidth: 60;
                            ZButton{
                                id: crayCtrlBtn;
                                icon.source:control.crayConnect ? "/resource/stop.png" : "/resource/start.png";
                                onClicked: {
                                    control.crayConnect = !control.crayConnect;
                                    interaction.controlCray(control.crayConnect);
                                    interaction.controlProcess(3, control.crayConnect);
                                }
                            }
                        }
                        Grid {
                            property int buttonWidth: (parent.width - crayCtrlBtn.parent.buttonWidth - 5);
                            ZButton{
                                id:crayPathBtn;
                                text: interaction.getCraypath()
                                onClicked: {
                                    interaction.chooseCraypath();
                                    crayPathBtn.text= interaction.getCraypath();
                                }
                                contentItem: Label {
                                    text: crayPathBtn.text
                                    font: crayPathBtn.font
                                    elide: Text.ElideMiddle
                                }
                            }
                        }
                    }
                }**/
                ZGroupBox{
                    title: qsTr("Controller")
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        rowSpacing: -5;
                        columnSpacing: 5
                        columns:1;
                        property int itemWidth : (width - (columns-1) * columnSpacing - 2*padding)/columns;
                        ZButton{
                            icon.source:control.monitorConnect ? "/resource/stop.png" : "/resource/start.png";
                            onClicked: {
                                control.monitorConnect = !control.monitorConnect;
                                interaction.controlMonitor(control.monitorConnect)
                            }
                        }
                        Grid {
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 0;
                            rowSpacing: -5;
                            columnSpacing: 5;
                            columns:2; //3;
                            Grid {
                                property int buttonWidth : parent.parent.itemWidth/2; //60;
                                ZButton{
                                    id: bluerbk;
                                    icon.source:control.blueRBKConnect ? "/resource/stop.png" : "/resource/start.png";
                                    icon.color: "#2976ca";
                                    onClicked: {
                                        control.blueRBKConnect = !control.blueRBKConnect;
                                        interaction.changeRBKSettings(false, blueSideBtn.text == "RIGHT"); // false: blue
                                        if(!simulation.checked){
                                            interaction.connectSim(control.blueRBKConnect,0);
                                        }else{
                                            interaction.connectRadio(control.blueRBKConnect,0,0); // freq is useless
                                            //interaction.connectRadio(control.blueRBKConnect,0,medusaFrq.value);
                                        }
                                        //while(myOption.processIsRunning());
                                        interaction.controlBlueRBK(control.blueRBKConnect);
                                        //if(control.blueRBKConnect){
                                        //    myOption.start();
                                        //}
                                        interaction.controlProcess(0, control.blueRBKConnect);
                                    }
                                }
                            }
                            Grid{
                                property int buttonWidth : parent.width - parent.parent.itemWidth/2 - 4; //70;
                                ZButton{
                                    id: blueSideBtn;
                                    enabled:!control.blueRBKConnect;
                                    text: "LEFT";
                                    onClicked: {
                                        blueSideBtn.text = blueSideBtn.text == "LEFT" ? "RIGHT": "LEFT";
                                    }
                                }
                            }/**
                            Grid{
                                property int buttonWidth : parent.width - bluerbk.parent.buttonWidth - blueSideBtn.parent.buttonWidth - 10;
                                ZButton{
                                    id:bluePathBtn;
                                    enabled:!control.blueRBKConnect;
                                    text: interaction.getRBKpath(0);
                                    onClicked: {
                                        interaction.chooseRBKpath(0);
                                        bluePathBtn.text= interaction.getRBKpath(0);
                                    }
                                    contentItem: Label {
                                        text: bluePathBtn.text;
                                        font: bluePathBtn.font;
                                        elide: Text.ElideMiddle;
                                    }
                                }
                            }**/
                            Grid{
                                property int buttonWidth : parent.parent.itemWidth/2; //60;
                                ZButton{
                                    id: yellowrbk;
                                    icon.source:control.yellowRBKConnect ? "/resource/stop.png" : "/resource/start.png";
                                    icon.color: "#ebdb7c";
                                    onClicked: {
                                        control.yellowRBKConnect = !control.yellowRBKConnect;
                                        interaction.changeRBKSettings(true, yellowSideBtn.text == "RIGHT"); // true: yellow
                                        if(!simulation.checked){
                                            interaction.connectSim(control.yellowRBKConnect,1);
                                        }else{
                                            interaction.connectRadio(control.yellowRBKConnect,1,8);
                                            //interaction.connectRadio(control.yellowRBKConnect,1,medusaFrq.value);
                                        }
                                        //while(myOption.processIsRunning());
                                        interaction.controlYellowRBK(control.yellowRBKConnect);
                                        //if(control.yellowRBKConnect){
                                        //    myOption.start();
                                        //}
                                        interaction.controlProcess(1, control.yellowRBKConnect);
                                    }
                                }
                            }
                            Grid{
                                property int buttonWidth : parent.width - parent.parent.itemWidth/2 - 4; //70;
                                ZButton{
                                    id: yellowSideBtn;
                                    enabled:!control.yellowRBKConnect;
                                    text: "RIGHT";
                                    onClicked: {
                                        yellowSideBtn.text = yellowSideBtn.text == "LEFT" ? "RIGHT": "LEFT";
                                    }
                                }
                            }/**
                            Grid{
                                property int buttonWidth : parent.width - yellowrbk.parent.buttonWidth - yellowSideBtn.parent.buttonWidth - 10;;
                                ZButton{
                                    id:yellowPathBtn;
                                    enabled:!control.yellowRBKConnect;
                                    text: interaction.getRBKpath(1);
                                    onClicked: {
                                        interaction.chooseRBKpath(1);
                                        yellowPathBtn.text= interaction.getRBKpath(1);
                                    }
                                    contentItem: Label {
                                        text: yellowPathBtn.text;
                                        font: yellowPathBtn.font;
                                        elide: Text.ElideMiddle;
                                    }
                                }
                            }**/ 
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("Kill")
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        rowSpacing: 5;
                        columns:1;
                        property int itemWidth : width - 2*padding;
                        ZButton {
                            icon.source:control.kill ? "/resource/stop.png" : "/resource/start.png";
                            onClicked: {
                                control.kill = !control.kill;
                                interaction.kill(control.kill);
                                if(control.kill) {
                                    interaction.controlProcess(0, false);
                                    interaction.controlProcess(1, false);
                                    interaction.controlProcess(2, false);
                                    interaction.controlProcess(3, false);
                                }
                            }
                        }
                    }
                }
            }
        }
        //RefereeBox{}
        //Viewer{}
        
        //Settings{}
    }
}
