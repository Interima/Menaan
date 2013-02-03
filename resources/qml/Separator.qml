import QtQuick 2.0

Rectangle
{
    id: separator;
    color: sepColor;
    height: sepHeight;
    width: parent.width;

    property int sepHeight: 20;
    property color sepColor: parent.color;
}
