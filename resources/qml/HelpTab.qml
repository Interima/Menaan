import QtQuick 2.0

Rectangle
{
    id: helpTab;
    anchors.fill: parent;
    color: "#00000000";

    Flickable
    {
        id: flickArea;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        width: parent.width - verticalScroll.width - 20
        contentWidth: parent.width;
        contentHeight: content.height;
        flickableDirection: Flickable.VerticalFlick;
        clip: true;

        Rectangle
        {
            id: content;
            anchors.top: parent.top;
            height: childrenRect.height;
            anchors.left:parent.left;
            width: flickArea.width;
            color: "#00000000";


            Text
            {
                id: toolsHeader;
                anchors.top: parent.top;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Tools");
            }


            Separator
            {
                id: toolsSeparator;
                anchors.top: toolsHeader.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: toolsText
                anchors.top: toolsSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                textFormat: Text.StyledText;
                color: "#FFFFFF";
                text: qsTr("<i>\"Tools\"</i> pane displays the list of avaiable cryptographic algorithms and its features.<br><br>\
 Cryptographic algorithms are designed as plugin and located in <i>\"/plugins\"</i> subdirectory in <i>\"Mena'an\"</i> installation path. You can add\
 plugins to this directory and restart application.<br><br>\
 Every plugin provides some information about itself and you can compare it and make a right choice.\
 Select algorithm that you choose by clicking on it. Mena'an prompt you to enter the settings needed for that particular type of algorithm.\
 You may input parameters manually by clicking and edit text field or use drag and drop.<br><br>\
 After enter algorithm request parameters you can start encode/decode operations using <i>\"Encode\"</i> and <i>\"Decode\"</i> buttons.\
 When you click one of them <i>\"Mena'an\"</i> create the job if your input parameters is valid.<br><br>\
 You can create new job or return to list of cryptographic algorithms by clicking <i>\"Back\"</i> button.");
            }




            Text
            {
                id: jobHeader;
                anchors.top: toolsText.bottom;
                anchors.topMargin: 20;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Job List");
            }


            Separator
            {
                id: jobSeparator;
                anchors.top: jobHeader.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: jobText
                anchors.top: jobSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                textFormat: Text.StyledText;
                color: "#FFFFFF";
                text: qsTr("<i>\"Job List\"</i> pane displays the list of jobs that you created.<br><br>\
 Every job provides information about itself.<br><br>\
 You can browse the jobs and can control them. More job than one job may be run simultaneously.\
 This depend on your settings and number of processor's cores.<br><br>\
 Running jobs have state <i>\"Running\"</i>. When progress of the running job will be 100%, its state changes to <i>\"Finished\"</i>.\
 If some error occurred when job running, its state changes to <i>\"Error\"</i>.\
 This state indicates that job never could be finished. You may delete this job and recreate it again.<br><br>\
 If job is not launched yet it has state <i>\"Stopped\"</i>. Don't worry about it, it start later.<br><br>\
 You may freeze and unfreeze jobs that is not running. Freezed jobs can't be running. The state <i>\"Freezed\"</i> indicates that job was freezed.");
            }


            Text
            {
                id: configHeader;
                anchors.top: jobText.bottom;
                anchors.topMargin: 20;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Config");
            }


            Separator
            {
                id: configSeparator;
                anchors.top: configHeader.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: configText
                anchors.top: configSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                textFormat: Text.StyledText;
                color: "#FFFFFF";
                text: qsTr("<i>\"Config\"</i> pane displays configuration of <i>\"Mena'an\"</i>.<br><br>\
 You can select option by clicking on arrow.<br><br>\
 <i>\"Language\"</i> option allows to choose application language. By default it is set to <i>\"English\"</i>.<br><br>\
 <i>\"Use multi thread\"</i> option allows enabling or disabling several threads simultaneously, if you processor\
 have more than one cores (including logical cores). By default it is set to <i>\"Enabled\"</i> and it is recommended to use.<br><br>\
  <i>\"Auto delete finish jobs\"</i> option allow choose how will be processed finished jobs. If it is set to <i>\"Enabled\"</i>\
 every finished job will be deleted from <i>\"Job List\"</i>. If it is set to <i>\"Disabled\"</i>, you must delete jobs manually.\
 By default it is set to <i>\"Disabled\"</i>.<br><br>\
 <i>\"Use special extension\"</i> option allows using special extension for encoded/decoded files. If it set to <i>\"Enabled\"</i>, then <i>\"Mena'an\"</i>\
 add to file name special extension: <i>\"enc\"</i> for encoded files, <i>\"dec\"</i> for decoded files. By default it is set to <i>\"Enabled\"</i>.<br><br>\
 <i>\"Rewrite existing files\"</i> option allows to control file rewriting. If it is set to <i>\"Enabled\"</i>, then <i>\"Mena'an\"</i> rewrite\
 existing files if they have the same name. If it is set to <i>\"Disabled\"</i>, then <i>\"Mena'an\"</i> adds unique symbols for a new file and doesn't rewrite old file.\
 By default it is set to <i>\"Enabled\"</i>.<br><br>\
 After changing options you must save new configuration by click on <i>\"Save\"</i> button and restart application.<br><br>\
 To restore default values click on <i>\"Reset\"</i> button.<br><br>\
 <i>\"Import\"</i> and <i>\"Export\"</i> buttons import and export configurations respectively.<br><br>\
 Be careful. If you do not know what you are doing, do not do anything.");
            }


            Text
            {
                id: helpHeader;
                anchors.top: configText.bottom;
                anchors.topMargin: 20;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("Help");
            }


            Separator
            {
                id: helpSeparator;
                anchors.top: helpHeader.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: helpText
                anchors.top: helpSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                textFormat: Text.StyledText;
                color: "#FFFFFF";
                text: qsTr("<i>\"Help\"</i> pane displays help pages of application.<br><br>\
 For detailed help you may visit developer's site: <i>www.blogspot.exsector.com</i> \
 or read pdf manual which located in <i>\"/help\"</i> directory in <i>\"Mena'an\"</i> installation path.<br><br>\
 Also you may send you question to developer's e-mail.");
            }



            Text
            {
                id: aboutHeader;
                anchors.top: helpText.bottom;
                anchors.topMargin: 20;
                anchors.left: parent.left;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                font.bold: true;
                color: "#FFFFFF";
                text: qsTr("About");
            }


            Separator
            {
                id: aboutSeparator;
                anchors.top: aboutHeader.bottom;
                anchors.topMargin: 8;
                anchors.left: parent.left;
                sepColor: "#838EA8";
                sepHeight: 1;
                width: 2*parent.width/3;
            }


            Text
            {
                id: aboutText
                anchors.top: aboutSeparator.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.leftMargin: 8;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                font.pixelSize: 12;
                font.family: "DejaVu Sans";
                wrapMode: TextEdit.WordWrap;
                textFormat: Text.StyledText;
                color: "#FFFFFF";
                text: qsTr("<i>\"About\"</i> pane displays some information about developers and\
 license.<br><br>");
            }


    }
}
    VScrollBar
    {
        id: verticalScroll;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        position: flickArea.visibleArea.yPosition;
        pageSize: flickArea.visibleArea.heightRatio;
    }
}
