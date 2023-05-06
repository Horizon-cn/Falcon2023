import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Owl 1.0 as Owl
import Components 1.0

Page{
    id:control;
    property bool radioConnect : false;
    property bool blueRBKConnect : false;
    property bool yellowRBKConnect : false;
    property bool simConnect : false;
    //property bool crayConnect : false;
    property bool monitorConnect : false;
    property bool isSimulation : true;
    property bool kill : false;
    property bool ifEdgeTest : false;
    property bool isTesting: false;
    property bool isRecoring: false;
    property bool isLogPlay: false;
    property bool isRecFile: false;
    property bool isReplaying: false;
    property bool isCutting: true;
    property bool isCuttingLog: true;
    property bool isLabeling: false;

    Timer{
        id:oneSecond;
        interval:800;
        running:!visionControls.ifConnected || (!control.isSimulation && !control.radioConnect); //true;
        repeat:true;
        onTriggered: {
            if (!visionControls.ifConnected) {
                interaction.updateInterfaces();
                interfaces4vision.updateModel();
            }
            if (!control.isSimulation && !control.radioConnect)
                radioComboBox.updateModel();
        }
    }

    Owl.LogSlider{
        id: log
    }
    Owl.LogEventLabel{
        id: eventlabel
    }

    Owl.Interaction{
        id:interaction;
    }

    //Owl.Option{id:myOption}

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

    StackLayout {
        id:controlLayout;
        width: parent.width;
        height:parent.height; //fix display bug at low resolution.2019.3.29 wz
        currentIndex: bar.currentIndex;
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
                }
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
                }/**
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
                                            interaction.connectRadio(control.blueRBKConnect,0,medusaFrq.value);
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
                                            interaction.connectRadio(control.yellowRBKConnect,1,medusaFrq.value);
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
        RefereeBox{}
        Viewer{}
        /*****************************************/
        /*                  UDP                  */
        /*****************************************/
        ScrollView {
            clip: true;
            contentWidth: parent.width;
            contentHeight: parent.height * 2;
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn;
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn;
            ScrollBar.horizontal.interactive: true;
            ScrollBar.vertical.interactive: true;
            Grid {
                id: radio;
                width: controlLayout.width;
                padding:10;
                verticalItemAlignment: Grid.AlignVCenter;
                horizontalItemAlignment: Grid.AlignHCenter;
                spacing: 5;
                columns:1;
                property int itemWidth : width - 2*padding;
                ZGroupBox{
                    title: qsTr("Rec")
                    Grid{
                        id:rec;
                        width:parent.width;
                        property int itemWidth : width - 2*padding;
                        property bool recordRawVision: true;
                        columns: 1;
                        CheckBox{
                            width:parent.itemWidth;
                            checked: true;
                            text: "Contain Raw Vision(Suggest)"
                            onCheckedChanged: {
                                parent.recordRawVision = !parent.recordRawVision;
                                interaction.setRecordRawVision(parent.recordRawVision);
                            }
                        }
                        Grid{
                            width:parent.width;
                            property int itemWidth : (width - 2*padding) / 2;
                            columns: 2;
                            columnSpacing: 10
                            Button{
                                width:parent.itemWidth;
                                icon.source: control.isRecoring ? "/resource/stop.png" : "/resource/start.png";
                                onClicked: {
                                    control.isRecoring = !control.isRecoring;
                                    control.isCutting = !control.isRecoring;
                                    interaction.setRecorder(control.isRecoring);
                                }
                            }
                            ZButton{ //isCutting:not recording
                                width:parent.itemWidth;
                                icon.source:control.isCutting ? "/resource/scissors1.png" : "/resource/scissors2.png";
                                enabled: control.isRecoring;
                                onClicked: {
                                    control.isCutting = !control.isCutting;
                                    interaction.setRecorderCut(control.isCutting);
                                }
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("RecReplay")
                    Column{
                        width:parent.width;
                        height:parent.height;
                        spacing: 0;
                        padding:0;
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 1;
                            property int itemWidth : width - 2*padding;
                            property bool playRawVision : true;
                            CheckBox{
                                width:parent.itemWidth;
                                checked: true;
                                text: "If Play Raw Vision(Suggest But Must Contain)"
                                onCheckedChanged: {
                                    interaction.setPlayerRawVision(parent.playRawVision);
                                }
                            }
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 8;
                            ZButton {
                                id:openBtnr
                                width: 35;
                                icon.source:"/resource/openfile.png";
                                anchors.leftMargin: 10
                                onClicked: {
                                    fdrs.open();
                                    //parent.openLogToPlay();
                                    interaction.setRecorder(control.isRecoring);
                                }
                            }
                            Label {
                                id: labelsr
                                text: qsTr("")
                                height: 25
                                anchors.left:openBtnr.right
                                anchors.leftMargin: 10
                            }
                            /**
                            function openLogToPlay() {
                                if (interaction.chooseLogToPlay()) {
                                    if (control.isReplaying) Owl.RecSlider.toggleStopped();
                                    control.isReplaying = false;
                                    rectimer.running = false;
                                    //console.log("You chose: " + fdrs.fileUrl);
                                    //Owl.RecSlider.loadFile(fdrs.fileUrl);
                                    recslider.to = Owl.RecSlider.maximumValue;
                                    recslider.stepSize = Owl.RecSlider.stepSize;
                                    recslider.value = 0;
                                    control.isRecFile = true;
                                    control.isRecoring = false;
                                    if (Owl.RecSlider.currentFrame > Owl.RecSlider.getMaxFrame()){
                                        Owl.RecSlider.recName = "Import Error File";
                                        control.isRecFile = false;
                                    }
                                }
                                else {
                                    labelsr.text = "";
                                    console.log("Canceled");
                                }
                            }
                            **/
                            FileDialog {
                                id:fdrs
                                title: "Please select"
                                selectExisting: true
                                selectFolder: false
                                selectMultiple: false
                                nameFilters: ["Rec files (*.log)"]
                                onAccepted: {
                                    if (control.isReplaying) Owl.RecSlider.toggleStopped();
                                    control.isReplaying = false;
                                    rectimer.running = false;
                                    console.log("You chose: " + fdrs.fileUrl);
                                    Owl.RecSlider.loadFile(fdrs.fileUrl);
                                    recslider.to = Owl.RecSlider.maximumValue;
                                    recslider.stepSize = Owl.RecSlider.stepSize;
                                    recslider.value = 0;
                                    control.isRecFile = true;
                                    control.isRecoring = false;
                                    if (Owl.RecSlider.currentFrame > Owl.RecSlider.getMaxFrame()){
                                        Owl.RecSlider.recName = "Import Error File";
                                        control.isRecFile = false;
                                    }
                                }
                                onRejected: {
                                    labelsr.text = "";
                                    console.log("Canceled");
                                }
                            }
                            
                            ZButton{
                                id: recPlayerPlay;
                                width: 35;
                                enabled: control.isRecFile;
                                icon.source:control.isReplaying ? "/resource/pause.png" : "/resource/start.png";
                                onClicked: {
                                    control.isReplaying  = !control.isReplaying;
                                    rectimer.running = control.isReplaying;
                                    Owl.RecSlider.toggleStopped();
                                }
                            }
                            ZButton{
                                width: 35;
                                icon.source:"/resource/stop.png";
                                enabled: control.isRecFile;
                                onClicked: {
                                    control.isReplaying = false;
                                    rectimer.running = false;
                                    control.isRecFile = false;
                                    Owl.RecSlider.setStopped(true);
                                    recslider.value = 0;
                                }
                            }
                            ZButton{
                                id: recPlayerForward
                                width: 35;
                                enabled: control.isRecFile /*&& !control.isReplaying*/;
                                icon.source:"/resource/last.png";
                                onClicked: {
                                    recslider.value = recslider.value - recPlaySpinBox.value * recslider.stepSize;
                                }
                            }
                            ZButton{
                                id: recPlayerBack
                                width: 35;
                                enabled: control.isRecFile /*&& !control.isReplaying*/;
                                icon.source:"/resource/next.png";
                                onClicked: {
                                    recslider.value = recslider.value + recPlaySpinBox.value * recslider.stepSize;
                                }
                            }
                            Text{
                                text: "Steps:";
                                color: "white";
                            }
                            SpinBox {
                                id:recPlaySpinBox;
                                height: 46
                                width: 120
                                from: 1
                                to:10000
                                font.pixelSize: 16
                                onValueModified: {
                                    Owl.RecSlider.setPlayerRate(value);
                                }
                            }
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 4;
                            Slider{
                                id: recslider
                                width: parent.width - timeTextr.width;
//                              value: Owl.RecSlider.currentFrame;
                                onValueChanged: {
                                    if (recslider.value != Owl.RecSlider.currentFrame){
                                        Owl.RecSlider.seekFrame(recslider.value);
                                    }
                                    if (Owl.RecSlider.currentFrame == Owl.RecSlider.getMaxFrame()){
                                        control.isReplaying  = false;
                                        rectimer.running = false;
                                        Owl.RecSlider.setStopped(true);
                                        Owl.RecSlider.recName = "Done";
                                    }
                                    else
                                        Owl.RecSlider.recName = Owl.RecSlider.getFilename();
                                }
                            }
                            Text{
                                id: timeTextr;
                                text: Owl.RecSlider.durTime + " / " + Owl.RecSlider.maxTime;
                                color: "white";
                            }
                            Timer{
                                id: rectimer;
                                interval: 1;
                                repeat: true;
                                running: false;
                                onTriggered: {
                                    recslider.value = Owl.RecSlider.currentFrame;
                                }
                            }
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 6;
                            Text{
                                id:recname
                                width: parent.width - 180;
                                text: Owl.RecSlider.recName;
                                color: "white";
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("WorldCupLog")
                    Column{
                        width:parent.width;
                        height:parent.height;
                        spacing: 0;
                        padding:0;
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 6;
                            ZButton {
                                id:openBtn
                                width: 35;
                                icon.source:"/resource/openfile.png";
                                anchors.leftMargin: 10
                                onClicked: {
                                    fds.open();
                                }
                            }
                            Label {
                                id: labels
                                text: qsTr("")
                                height: 25
                                anchors.left:openBtn.right
                                anchors.leftMargin: 10
                            }

                            FileDialog {
                                id:fds
                                title: "Please select"
                                //folder: shortcuts.desktop
                                selectExisting: true
                                selectFolder: false
                                selectMultiple: false
                                nameFilters: ["Log files (*.log *.log.gz)"]
                                onAccepted: {
                                    console.log("You chose: " + fds.fileUrl + " "+fds.folder);
                                    log.loadFile(fds.fileUrl);
                                    logslider.to = log.maximumValue;
                                    logslider.stepSize = log.stepSize;
                                    logslider.value = 0;
                                }
                                onRejected: {
                                    labels.text = "";
                                    console.log("Canceled");
                                }
                            }
                            ZButton{
                                width: 35;
                                icon.source:control.isLogPlay ? "/resource/pause.png" : "/resource/start.png";
                                onClicked: {
                                    control.isLogPlay = !control.isLogPlay;
                                    logtimer.running = !logtimer.running;
                                    log.toggleStopped();
                                }
                            } 
                            ZButton{
                                width: 35;
                                icon.source:"/resource/last.png";
                                onClicked: {
                                    logslider.value = logslider.value - 3 * logslider.stepSize;
                                }
                            }
                            ZButton{
                                width: 35;
                                icon.source:"/resource/next.png";
                                onClicked: {
                                    logslider.value = logslider.value + 3 * logslider.stepSize;
                                }
                            }
                            ZButton{
                                width: 35;
                                icon.source:control.isCuttingLog ? "/resource/scissors1.png" : "/resource/scissors2.png";
                                onClicked: {
                                    if (control.isCuttingLog) {
                                        log.setStartPoint(fds.fileUrl, logslider.value);
                                    } else {
                                        log.setStopPoint(fds.fileUrl, logslider.value);
                                    }
                                    control.isCuttingLog = !control.isCuttingLog;
                                }
                            }
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 4;

                            Slider{
                                id: logslider
                                width: parent.width - timeText.width;
                                onValueChanged: log.seekFrame(logslider.value);
                            }
                            Text{
                                id: timeText;
                                text: log.durTime + " / " + log.maxTime;
                                color: "white";
                            }
                            Timer{
                                id: logtimer;
                                repeat: true;
                                running: false;
                                onTriggered: {
                                    logslider.value = logslider.value + logslider.stepSize;
                                }
                            }
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 6;
                            Text{
                                id:logname
                                width: parent.width - 180;
                                text: log.logName;
                                color: "white";
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("RecEventLabel")
                    Column{
                        width:parent.width;
                        height:parent.height;
                        spacing: 0;
                        padding:0;
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 6;
                            ZButton {
                                id:openLogBtn
                                width: 35;
                                icon.source:"/resource/openfile.png";
                                anchors.leftMargin: 10
                                onClicked: {
                                    openLog.open();
                                }
                            }
                            Label {
                                id: labelstart
                                text: qsTr("")
                                height: 25
                                anchors.left:openLogBtn.right
                                anchors.leftMargin: 10
                            }
                            FileDialog {
                                id:openLog
                                title: "Please select"
                                selectExisting: true
                                selectFolder: false
                                selectMultiple: false
                                nameFilters: ["Rec files (*.log)"]
                                onAccepted: {
                                    console.log("You chose: " + openLog.fileUrl);
                                    Owl.RecEventLabel.loadFile(openLog.fileUrl);
                                }
                                onRejected: {
                                    labelstart.text = "";
                                    console.log("Canceled");
                                }
                            }
                            /**FileDialog {
                                id:labelfilestart
                                title: "Please select"
                                folder: shortcuts.desktop
                                selectExisting: true
                                selectFolder: false
                                selectMultiple: false
                                nameFilters: ["SSL Label files (*.labeler)"]
                                onAccepted: {
                                    console.log("You chose: " + labelfilestart.fileUrl + " "+labelfilestart.folder);
                                    eventlabel.loadFile(labelfilestart.fileUrl);
                                    logslider.to = log.maximumValue;
                                    logslider.stepSize = log.stepSize;
                                    logslider.value = 0;
                                }
                                onRejected: {
                                    labelstart.text = "";
                                    console.log("Canceled");
                                }
                            }**/
                            ZButton{
                                width: 35;
                                icon.source:control.isLabeling ? "/resource/pause.png" : "/resource/start.png";
                                onClicked: {
                                    control.isLabeling = !control.isLabeling;
                                    control.isLabeling = Owl.RecEventLabel.processLabel();
                                }
                            }
                            //设置事件是否标注，确定标注的时间段，也可以添加其他事件
                            /**ZButton{
                                width: 70;
                                icon.source:control.isLabeling ? "/resource/pause.png" : "/resource/start.png";
                                onClicked: {
                                    
                                }
                            }**/
                        }
                        Grid{
                            width:parent.width;
                            verticalItemAlignment: Grid.AlignVCenter;
                            horizontalItemAlignment: Grid.AlignHCenter;
                            spacing: 5;
                            rowSpacing: 5;
                            columns: 6;
                            Text{
                                id:labelname
                                width: parent.width - 180;
                                text: Owl.RecEventLabel.logName;
                                color: "white";
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("Camera Edge Test")
                    Grid{
                        width:parent.width;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignHCenter;
                        spacing: 0;
                        rowSpacing: 5;
                        columns:1;
                        property int itemWidth : width - 2*padding;
                        Button{
                            width:parent.itemWidth;
                            icon.source:control.ifEdgeTest ? "/resource/stop.png" : "/resource/start.png";
                            onClicked: {
                                control.ifEdgeTest = !control.ifEdgeTest;
                                interaction.setIfEdgeTest(control.ifEdgeTest);
                            }
                        }
                    }
                }
                ZGroupBox{
                    title: qsTr("State Estimation Test")
                    Grid{
                        width:parent.width;
                        property int itemWidth : width - 2*padding;
                        property bool runTestingScripts: true;
                        columns: 1;
                        CheckBox{
                            width:parent.itemWidth;
                            text: "Record BallSpeed" //"Run Texting Scripts"
                            checked: true;
                            onCheckedChanged: {
                                parent.runTestingScripts = !parent.runTestingScripts;
                            }
                        }
                        Button{
                            width:parent.itemWidth;
                            icon.source: isTesting ?  "/resource/stop.png" : "/resource/start.png";
                            onClicked: {
                                control.isTesting = !control.isTesting;
                                if(parent.runTestingScripts)
                                    interaction.setTestMode(control.isTesting,parent.runTestingScripts);
                                else
                                    interaction.startRecordCommands(control.isTesting);
                            }
                        }
                    }
                }
            }
        }
        Settings{}
    }
    property variant recplayerShortCut: ["m", "Left", "Right", "Up", "Down"];

    Shortcut{
        sequence: recplayerShortCut[0];
        onActivated: {
            recPlayerPlay.clicked()
        }
    }
    Shortcut{
        sequence: recplayerShortCut[1];
        onActivated: {
            recPlayerForward.clicked()
        }
    }
    Shortcut{
        sequence: recplayerShortCut[2];
        onActivated: {
            recPlayerBack.clicked()
        }
    }
    Shortcut{
        sequence: recplayerShortCut[3];
        onActivated: {
            recPlaySpinBox.value = recPlaySpinBox.value + 1;
        }
    }
    Shortcut{
        sequence: recplayerShortCut[4];
        onActivated: {
            recPlaySpinBox.value = recPlaySpinBox.value - 1;
        }
    }
}
