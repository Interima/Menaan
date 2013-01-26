import QtQuick 1.1

Rectangle
{
    id: message;
    smooth: true;
    radius: 4;
    anchors.horizontalCenter: parent.horizontalCenter;
    anchors.verticalCenter: parent.verticalCenter;
    width: 2*parent.width/3;
    height: 2*parent.height/3;

    border.color: "#FFFFFFFF";
    gradient: Gradient
              {
                GradientStop { position: 0.0; color: "#FF8390ab" }
                GradientStop { position: 1.0; color: "#FF4B5670" }
              }

    property string titleText: "default text";
    property string dataText: "default text";
    property bool titleEnabled: true;

    property int titleSize: 14;
    property bool titleBold: false;
    property string titleColor: "#FFFFFFFF"
    property string titleFont: "DejaVu Sans";

    property int dataSize: 14;
    property bool dataBold: false;
    property string dataColor: "#FFFFFFFF"
    property string dataFont: "DejaVu Sans";

    Text
    {
        id: title;
        text: message.titleText;
        font.family: message.titleFont;
        font.pixelSize: message.titleSize;
        font.bold: message.titleBold;
        color: message.titleColor;
        visible: message.titleEnabled;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 10;
    }

    Separator
    {
        id: titleSeparator;
        width: 2*parent.width/3;
        sepHeight: 1;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: title.bottom;
        anchors.topMargin: 5;
    }

    Text
    {
        id: data;
        text: message.dataText
        font.family: message.dataFont;
        font.pixelSize: message.dataSize;
        font.bold: message.dataBold;
        color: message.dataColor;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: title.height+titleSeparator.height;
    }

    MouseArea
    {
        id: mr;
        anchors.fill: parent;
        onClicked: {message.state="inactive"}
    }

    states:
    [
        State
        {
            name: "active";
            PropertyChanges
            {
                target: message;
                opacity: 1;
            }
        },

        State
        {
            name: "inactive";
            PropertyChanges
            {
                target: message;
                opacity: 0;
            }
        }
    ]

    Behavior on opacity
                        {
                            NumberAnimation
                            {
                                duration: 400;
                                onRunningChanged: {if (!running) message.destroy();}
                            }
                        }
}
