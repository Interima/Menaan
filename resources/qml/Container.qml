import QtQuick 2.0

Rectangle
{
    id: container;
    width: parent.width;
    color: parent.color;
    height: parent.height
    anchors.fill: parent;
    anchors.margins: 10;

    property string titleText: "default text";
    property string titleColor: "#ffffff";
    property int titleSize: 14;
    property string titleFamily: "DejaVu Sans";
    property bool titleBold: false;

    default property alias content: contentArea.children

    Text
    {
        id: title;
        width: parent.width;
        text: titleText;
        color: titleColor;
        font.pixelSize: titleSize;
        font.family: titleFamily;
        font.bold: titleBold;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
    }

    Rectangle
    {
        id: containerElement;
        width: parent.width;
        color: parent.color;
        border.width: 2;
        border.color: "#838EA8";
        anchors.top: title.bottom;
        anchors.topMargin: 4;
        anchors.bottom: parent.bottom;

        Rectangle
        {
            id: contentArea;
            anchors.fill: parent;
            anchors.margins: 14;
            color: parent.color;
            clip: true;
        }

    }

    states:
    [
        State
        {
            name: "active"
            PropertyChanges
            {
                target: container;
                opacity: 1;
            }
        },

        State
        {
            name: "inactive"
            PropertyChanges
            {
                target: container;
                opacity: 0;
            }
         }
    ]

    Behavior on opacity { NumberAnimation { duration: 400 }}

}
