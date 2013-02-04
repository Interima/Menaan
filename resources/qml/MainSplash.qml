import QtQuick 2.0

Rectangle
{
    anchors.fill: parent;
    color: "#00000000";

    Image
    {
        id: splashImg;
        source: "qrc:/splash/MainSplash";
        anchors.fill: parent;
        smooth: true;
    }
} 
