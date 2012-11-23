import QtQuick 1.1

Rectangle
{
    id:mitem;

    width: childrenRect.width;
    height: childrenRect.height;
    color: parent.color;

    // internal signal and propers
    signal itemClicked;

    property string titleText: "default text";
    property color titleColor: "#838EA8";
    property string titleFont: "DejaVu Sans";
    property bool titleBold: false;
    property int titleSize: 14;

    property color markerColor: "#838EA8";
    property int markerWidth: 2;
    property int markerHeight: 22;

    // marker element
    Rectangle
    {
        id: marker;
        height: mitem.markerHeight;
        width: mitem.markerWidth;
        color: mitem.markerColor;
        radius: mitem.markerWidth;
        anchors.top: parent.top;
        anchors.left: parent.left;
        smooth: true;
    }

    // menuitem text
    Text
    {
        id: title;
        text: mitem.titleText;
        color: mitem.titleColor;
        font.family: mitem.titleFont;
        font.bold: mitem.titleBold;
        font.pixelSize: mitem.titleSize;
        anchors.verticalCenter: marker.verticalCenter;
        anchors.left: marker.right;
        anchors.leftMargin: 10;
        smooth: true;
    }

    MouseArea
    {
        id:mr;
        anchors.fill:parent;
        onClicked: mitem.itemClicked();
    }

    states:
    [
        State
        {
            name: "active"
            PropertyChanges
            {
                target: mitem;
                titleColor: "#ffffff";
                markerColor: "#ffffff";
            }
        },

        State
        {
            name: "inactive"
            PropertyChanges
            {
                target: mitem;
                titleColor: "#7A859F";
                markerColor: "#7A859F";
            }
         }
    ]

    Behavior on titleColor { ColorAnimation { duration: 400 }}
    Behavior on markerColor { ColorAnimation { duration: 400 }}

}
