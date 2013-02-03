import QtQuick 2.0
import ix2.interima.droparea 1.0

Rectangle
{
    id: inputFrame
    width: parent.width;
    height: childrenRect.height + title.anchors.topMargin;
    color: "#00000000";

    property string titleText: "default text";
    property string titleColor: "#ffffff";
    property int titleSize: 14;
    property string titleFamily: "DejaVu Sans";
    property string defaultText: "default text"
    property string realText: textEdit.text;
    property bool titleBold: false;

    signal setText(string str);

    onSetText: {textEdit.text = str;}

    Text
    {
        id: title;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.topMargin: 10;

        font.pixelSize: inputFrame.titleSize;
        font.family: inputFrame.titleFamily;
        font.bold: inputFrame.titleBold;
        color: inputFrame.titleColor;
        text: inputFrame.titleText;
    }

    DropArea
    {
        id: dropArea;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.top: title.bottom;
        anchors.topMargin: 5;
        anchors.right: parent.right;
        height: 20;

        Rectangle
        {
            id: frameRect;
            anchors.fill: parent;
            color: "#00000000";
            border.color: "#838EA8";
            radius: 4;
            smooth: true;
            clip: true;

            TextInput
            {
                id: textEdit;

                width: parent.width;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.leftMargin: 5;

                font.pixelSize: inputFrame.titleSize-2;
                font.family: inputFrame.titleFamily;
                font.bold: inputFrame.titleBold;
                font.italic: true;
                color: inputFrame.titleColor;

                selectByMouse: true;

                text: inputFrame.defaultText;
            }

        }

        onTextDrop: { textEdit.text = textData; }
    }
}
