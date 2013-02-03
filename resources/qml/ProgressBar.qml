import QtQuick 2.0

Rectangle
{
    width: 0;
    height: 0;
    color: "#00000000";

    property int maxValue: 0;
    property int progress: 0;
    property string fillColor: "#4A5570";

    Rectangle
    {
        anchors.fill: parent;
        border.color: "#FFFFFF";
        border.width: 1;
        color: "#00000000";
        radius: 4;
        smooth: true;
        z: 1;
    }

    Rectangle
    {
        id:fill;
        z: 0;
        anchors.fill: parent;
        anchors.rightMargin: parent.width-(parent.width * progress / maxValue);
        color: fillColor;
        radius: 4;
        smooth: true;
    }

}
