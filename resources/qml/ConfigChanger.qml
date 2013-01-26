import QtQuick 1.1

Rectangle
{
    id: configChanger;
    height: parent.height;
    width: parent.width;
    anchors.right: parent.right;
    anchors.rightMargin: 10;
    color: "#00000000";

    default property alias values: item.children;

    signal itemClicked;

    Rectangle
    {
        id: item;
        clip: true;
        color: "#00000000";
        anchors.right: img.left;
        anchors.rightMargin: 20;
        anchors.verticalCenter: parent.verticalCenter;
        width: parent.width;
        height: childrenRect.height;

    }


    Image
    {
        id: img;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        source: "qrc:/other/ArrowNext";
        height: 16;
        width: 14;


        MouseArea
        {
            id: mr;
            onClicked: configChanger.itemClicked();
            anchors.fill: parent;
        }
    }


}
