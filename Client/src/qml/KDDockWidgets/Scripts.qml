import QtQuick 2.6
import QtQuick.Controls 1.4 as Control
import QtQuick.Controls 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Components 1.0
import Owl 1.0 as Owl

Page{
    id:scripts;
    Timer{
        id:updateTimer
        interval:1000;
        running:!scriptsSetting.definedSetting; //true;
        repeat:true;
        onTriggered: {
            playSettingComboBox.updateModel();
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
            Rectangle{
                anchors.fill:parent;
                color:"transparent";
                ZGroupBox{
                    id: settingGroupBox;
                    width: parent.width - 15;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.top: parent.top;
                    anchors.margins: 10;
                    title :qsTr("Scripts Setting");
                    Grid{
                        height:parent.height;
                        verticalItemAlignment: Grid.AlignVCenter;
                        horizontalItemAlignment: Grid.AlignLeft;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        columnSpacing: 40;
                        rowSpacing: 5;
                        columns:4;
                        enabled: !scriptsSetting.definedSetting;
                        property int itemWidth : 90;
                        ZText{
                            text: qsTr("gReadyPlay");
                        }
                        Control.ComboBox{
                            id:playSettingComboBox;
                            model:interaction.getPlayList();
                            onActivated: interaction.changeReadyPlay(currentIndex);
                            width:parent.itemWidth;
                            function updateModel(){
                                model = interaction.getPlayList();
                                if(currentIndex >= 0)
                                    interaction.changeReadyPlay(currentIndex);
                            }
                            Component.onCompleted: updateModel();
                        }
                        ZText{
                            text: qsTr(" ");
                        }
                        ZText{
                            text: qsTr(" ");
                        }
                    }
                }
                Control.Button{
                    id : scriptsSetting;
                    text : (definedSetting ? qsTr("Cancel") : qsTr("Define"));
                    property bool definedSetting:false;
                    anchors.top: settingGroupBox.bottom;
                    anchors.right: parent.right;
                    anchors.rightMargin: 20;
                    anchors.topMargin: 10;
                    onClicked: clickEvent();
                    function clickEvent(){
                        if(!definedSetting){
                            interaction.defineScriptsSetting();
                        }
                        else {
                            interaction.updatePlayList();
                        }
                        definedSetting = !definedSetting;
                    }
                }
            }
        }
    }
}
