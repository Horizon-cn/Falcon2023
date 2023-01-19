import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Owl 1.0 as Owl

Page{
    property bool ifEdgeTest : false;
    property bool isTesting: false;
    property bool isRecoring: false;
    property bool isLogPlay: false;
    property bool isRecFile: false;
    property bool isReplaying: false;
    property bool isCutting: true;
    property bool isCuttingLog: true;
    property bool isLabeling: false;
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

    id : toolkit;
    
    Owl.LogSlider{
        id: log
    }
    Owl.LogEventLabel{
        id: eventlabel
    }

    Owl.Interaction{
        id:interaction;
    }
    
    Grid {
        id: radio;
        width: parent.width;
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
                        icon.source: isRecoring ? "/resource/stop.png" : "/resource/start.png";
                        onClicked: {
                            isRecoring = !isRecoring;
                            isCutting = !isRecoring;
                            interaction.setRecorder(isRecoring);
                        }
                    }
                    ZButton{ //isCutting:not recording
                        width:parent.itemWidth;
                        icon.source:isCutting ? "/resource/scissors1.png" : "/resource/scissors2.png";
                        enabled: isRecoring;
                        onClicked: {
                            isCutting = !isCutting;
                            interaction.setRecorderCut(isCutting);
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
                            interaction.setRecorder(isRecoring);
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
                            if (isReplaying) Owl.RecSlider.toggleStopped();
                            isReplaying = false;
                            rectimer.running = false;
                            //console.log("You chose: " + fdrs.fileUrl);
                            //Owl.RecSlider.loadFile(fdrs.fileUrl);
                            recslider.to = Owl.RecSlider.maximumValue;
                            recslider.stepSize = Owl.RecSlider.stepSize;
                            recslider.value = 0;
                            isRecFile = true;
                            isRecoring = false;
                            if (Owl.RecSlider.currentFrame > Owl.RecSlider.getMaxFrame()){
                                Owl.RecSlider.recName = "Import Error File";
                                isRecFile = false;
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
                            if (isReplaying) Owl.RecSlider.toggleStopped();
                            isReplaying = false;
                            rectimer.running = false;
                            console.log("You chose: " + fdrs.fileUrl);
                            Owl.RecSlider.loadFile(fdrs.fileUrl);
                            recslider.to = Owl.RecSlider.maximumValue;
                            recslider.stepSize = Owl.RecSlider.stepSize;
                            recslider.value = 0;
                            isRecFile = true;
                            isRecoring = false;
                            if (Owl.RecSlider.currentFrame > Owl.RecSlider.getMaxFrame()){
                                Owl.RecSlider.recName = "Import Error File";
                                isRecFile = false;
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
                        enabled: isRecFile;
                        icon.source:isReplaying ? "/resource/pause.png" : "/resource/start.png";
                        onClicked: {
                            isReplaying  = !isReplaying;
                            rectimer.running = isReplaying;
                            Owl.RecSlider.toggleStopped();
                        }
                    }
                    ZButton{
                        width: 35;
                        icon.source:"/resource/stop.png";
                        enabled: isRecFile;
                        onClicked: {
                            isReplaying = false;
                            rectimer.running = false;
                            isRecFile = false;
                            Owl.RecSlider.setStopped(true);
                            recslider.value = 0;
                        }
                    }
                    ZButton{
                        id: recPlayerForward
                        width: 35;
                        enabled: isRecFile /*&& !isReplaying*/;
                        icon.source:"/resource/last.png";
                        onClicked: {
                            recslider.value = recslider.value - recPlaySpinBox.value * recslider.stepSize;
                        }
                    }
                    ZButton{
                        id: recPlayerBack
                        width: 35;
                        enabled: isRecFile /*&& !isReplaying*/;
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
//                      value: Owl.RecSlider.currentFrame;
                        onValueChanged: {
                            if (recslider.value != Owl.RecSlider.currentFrame){
                                Owl.RecSlider.seekFrame(recslider.value);
                            }
                            if (Owl.RecSlider.currentFrame == Owl.RecSlider.getMaxFrame()){
                                isReplaying  = false;
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
                        icon.source:isLogPlay ? "/resource/pause.png" : "/resource/start.png";
                        onClicked: {
                            isLogPlay = !isLogPlay;
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
                        icon.source:isCuttingLog ? "/resource/scissors1.png" : "/resource/scissors2.png";
                        onClicked: {
                            if (isCuttingLog) {
                                log.setStartPoint(fds.fileUrl, logslider.value);
                            } else {
                                log.setStopPoint(fds.fileUrl, logslider.value);
                            }
                            isCuttingLog = !isCuttingLog;
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
                        icon.source:isLabeling ? "/resource/pause.png" : "/resource/start.png";
                        onClicked: {
                            isLabeling = !isLabeling;
                            isLabeling = Owl.RecEventLabel.processLabel();
                        }
                    }
                    //设置事件是否标注，确定标注的时间段，也可以添加其他事件
                    /**ZButton{
                        width: 70;
                        icon.source:isLabeling ? "/resource/pause.png" : "/resource/start.png";
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
                    icon.source:ifEdgeTest ? "/resource/stop.png" : "/resource/start.png";
                    onClicked: {
                        ifEdgeTest = !ifEdgeTest;
                        interaction.setIfEdgeTest(ifEdgeTest);
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
                        isTesting = !isTesting;
                        if(parent.runTestingScripts)
                            interaction.setTestMode(isTesting,parent.runTestingScripts);
                        else
                            interaction.startRecordCommands(isTesting);
                    }
                }
            }
        }
    }
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
}
