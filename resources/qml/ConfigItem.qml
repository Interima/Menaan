import QtQuick 2.0

Rectangle
{
    id: configItem;

    property string titleText: "default text";
    property int titleSize: 14;
    property bool titleBold: false;
    property string titleColor: "#FFFFFF"
    property string titleFont: "DejaVu Sans";

    radius: 4;
    smooth: true;
    border.color: "#838EA8";
    height: title.height+10;

    gradient: Gradient
              {
                  GradientStop { position: 0.0; color: "#87BBC6E0" }
                  GradientStop { position: 1.0; color: "#00BBC6E0" }
              }


    Text
    {
        id: title;
        text: configItem.titleText;
        font.bold: configItem.titleBold;
        color: configItem.titleColor;
        font.family: configItem.titleFont;
        font.pixelSize: configItem.titleSize;
        anchors.left: parent.left;
        anchors.leftMargin: 15;
        anchors.verticalCenter: parent.verticalCenter;
    }
}

