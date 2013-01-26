import QtQuick 1.1

Rectangle
{
    id: exitTab;
    anchors.fill: parent;
    color: parent.color;

    signal yesClicked;

    Rectangle
    {
        id: layout;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        color: parent.color;
        width: parent.width;
        height: childrenRect.height;

        Text
        {
            id:title;
            text: qsTr("All running jobs has been terminated.");
            color: "#FFFFFF";
            anchors.top: parent.top;
            anchors.horizontalCenter: parent.horizontalCenter;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
        }

        Text
        {
            id:title2;
            text: qsTr("You really want to exit?");
            color: "#FFFFFF";
            anchors.top: title.bottom;
            anchors.topMargin: 20;
            anchors.horizontalCenter: parent.horizontalCenter;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
        }


        SimpleButton
        {
            id: yes;
            titleText: qsTr("Yes");
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: title2.bottom;
            anchors.topMargin: 20;
            width: parent.width/2;
            height: 30
            onButtonClicked: exitTab.yesClicked();

        }
    }
}
