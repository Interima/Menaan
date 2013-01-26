import QtQuick 1.1

Rectangle
{
    id: btn;
    signal buttonClicked;

    property string titleText: "default text";
    property int titleSize: 14;
    property bool titleBold: false;
    property string titleColor: "#ffffffff"
    property string titleFont: "DejaVu Sans";

    radius: 4;
    smooth: true;
    border.color: "#838EA8";

    Gradient
    {
        id: pressed;
        GradientStop { position: 0.0; color: "#00BBC6E0" }
        GradientStop { position: 1.0; color: "#87BBC6E0" }
    }

    Gradient
    {
        id: released;
        GradientStop { position: 0.0; color: "#87BBC6E0" }
        GradientStop { position: 1.0; color: "#00BBC6E0" }
    }

    gradient: if (mr.pressed) pressed; else released;

    Text
    {
        id: title;
        text: btn.titleText;
        font.bold: btn.titleBold;
        color: btn.titleColor;
        font.family: btn.titleFont;
        font.pixelSize: btn.titleSize;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
    }

    MouseArea
    {
        id : mr;
        anchors.fill: parent;
        onClicked: {btn.buttonClicked()}
    }

}
