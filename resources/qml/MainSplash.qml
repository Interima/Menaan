import QtQuick 2.0

Rectangle
{
    width: childrenRect.width;
    height: childrenRect.height;
    color: "#00000000";

    Image
    {
        id: splashImg;
        source: "qrc:/splash/MainSplash";
    }
} 
