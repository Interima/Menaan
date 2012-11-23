import QtQuick 1.1
import ix2.interima.jobtypes 1.0
import "JobCreator.js" as JobEngine;


Rectangle
{
    id: form;
    width: 300;
    height: 62;
    color: "#00000000";

    //! emit when click to back button
    signal backClicked();
    //! hold current plugin index inS model
    property int pluginIndex: 0;

    //! Qt can't use JS binding...
    //! repair it in Qt 5.0

    function calcYPos(){return flickArea.visibleArea.yPosition;}
    function calcHRatio(){return flickArea.visibleArea.heightRatio;}

    Connections
    {
        target: menaan;
        onDialogAnswer: JobEngine.answerArrived(sender,path);
    }


    Flickable
    {
        id: flickArea;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        width: parent.width;
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

            InputFrame
            {
                id: inputPath;
                anchors.top: parent.top;
                anchors.left: parent.left;
                anchors.right: inputDatabaseOpenBtn.left;
                anchors.rightMargin: 8;
                titleText: qsTr("Input path:");
                defaultText: qsTr("Write input path or drag it here");
            }

            ImgButton
            {
                id: inputDatabaseOpenBtn;
                anchors.bottom: inputPath.bottom;
                anchors.right: inputFileOpenBtn.left;
                anchors.rightMargin: 4;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Database";
                onButtonClicked: { menaan.openDatabase("input"); }
            }


            ImgButton
            {
                id: inputFileOpenBtn;
                anchors.bottom: inputPath.bottom;
                anchors.right: inputDirectoryOpenBtn.left;
                anchors.rightMargin: 4;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/File";
                onButtonClicked: { menaan.openFile("input"); }
            }

            ImgButton
            {
                id: inputDirectoryOpenBtn;
                anchors.bottom: inputPath.bottom;
                anchors.right: inputClearBtn.left;
                anchors.rightMargin: 4;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Directory";
                onButtonClicked: { menaan.openDirectory("input");}
            }

            ImgButton
            {
                id: inputClearBtn;
                anchors.bottom: inputPath.bottom;
                anchors.right: cancelBtn.right;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Clear";
                onButtonClicked: { JobEngine.setTextFor(inputPath,""); }
            }


            InputFrame
            {
                id: outputPath
                anchors.top: inputPath.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.right: outputFileOpenBtn.left;
                anchors.rightMargin: 8;
                titleText: qsTr("Output path:");
                defaultText: qsTr("Write output path or drag it here");
            }

            ImgButton
            {
                id: outputFileOpenBtn;
                anchors.bottom: outputPath.bottom;
                anchors.right: outputDirectoryOpenBtn.left;
                anchors.rightMargin: 4;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/File";
                onButtonClicked: { menaan.openFile("output");}
            }

            ImgButton
            {
                id: outputDirectoryOpenBtn;
                anchors.bottom: outputPath.bottom;
                anchors.right: outputClearBtn.left;
                anchors.rightMargin: 4;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Directory";
                onButtonClicked: { menaan.openDirectory("output"); }
            }

            ImgButton
            {
                id: outputClearBtn;
                anchors.bottom: outputPath.bottom;
                anchors.right: cancelBtn.right;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Clear";
                onButtonClicked: { JobEngine.setTextFor(outputPath,""); }
            }

            InputFrame
            {
                id: key;
                anchors.top: outputPath.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.right: keyClearBtn.left;
                anchors.rightMargin: 8;
                titleText: qsTr("Key:");
                defaultText: qsTr("Write key or drag it here");
            }

            ImgButton
            {
                id: keyClearBtn;
                anchors.bottom: key.bottom;
                anchors.right: cancelBtn.right;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Clear";
                onButtonClicked: { JobEngine.setTextFor(key,""); }
            }

            InputFrame
            {
                id: special;
                anchors.top: key.bottom;
                anchors.topMargin: 10;
                anchors.left: parent.left;
                anchors.right: specialClearBtn.left;
                anchors.rightMargin: 8;
                titleText: qsTr("Special:");
                defaultText: qsTr("Write special parameters or drag it here");
                width: parent.width - 26*2;
            }

            ImgButton
            {
                id: specialClearBtn;
                anchors.bottom: special.bottom;
                anchors.right: cancelBtn.right;
                width: 26;
                height: 20;
                imgSource: "qrc:/other/Clear";
                onButtonClicked: { JobEngine.setTextFor(special,""); }
            }


            SimpleButton
            {
                id: encodeBtn;
                width: parent.width/3;
                height: 50;
                titleText: qsTr("Encode");
                anchors.left: parent.left;
                anchors.top: special.bottom;
                anchors.topMargin: 45;
                onButtonClicked: {JobEngine.command(form,JobTypes.ECB_ENC);}
            }

            SimpleButton
            {
                id: decodeBtn;
                width: parent.width/3 - 5;
                height: 50;
                titleText: qsTr("Decode");
                anchors.left: encodeBtn.right;
                anchors.leftMargin: 5;
                anchors.top: special.bottom;
                anchors.topMargin: 45;
                onButtonClicked: {JobEngine.command(form,JobTypes.ECB_DEC);}
            }

            SimpleButton
            {
                id: cancelBtn;
                width: parent.width/3 - 5;
                height: 50;
                titleText: qsTr("Back");
                anchors.right: parent.right
                anchors.top: special.bottom;
                anchors.topMargin: 45;
                onButtonClicked: backClicked();
            }
        }
    }

    Behavior on opacity { NumberAnimation { duration : 400; } }
}
