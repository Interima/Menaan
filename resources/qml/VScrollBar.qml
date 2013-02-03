import QtQuick 2.0

Item
{
    id: scrollBar

    property real position
    property real pageSize
    property variant orientation : Qt.Vertical

    property string barColor: "#838EA8"

    height: parent.height;
    width: childrenRect.width;

    Rectangle
    {
        id: bar;
        width: 10;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        radius: 4;
        smooth: true;
        border.color: barColor;
        border.width: 1;
        color: "#00000000";
        clip: true;

        Rectangle
        {
            id : chunk;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.horizontalCenterOffset: 1;
            anchors.top: parent.top;
            anchors.topMargin: {
                                 var offset = scrollBar.position * scrollBar.height;
                                 if (offset<2) return 2;
                                 else if (offset>parent.height-chunk.height-2) return parent.height-chunk.height-2;
                                 else return offset
                               }
            width: 7;
            height: (scrollBar.pageSize * (scrollBar.height-2));
            radius: 2;
            smooth: true;
            gradient: Gradient
                      {
                        GradientStop { position: 0.0; color: "#41BBC6E0" }
                        GradientStop { position: 0.5; color: "#10BBC6E0" }
                        GradientStop { position: 1.0; color: "#41BBC6E0" }
                      }
        }
    }
 }
