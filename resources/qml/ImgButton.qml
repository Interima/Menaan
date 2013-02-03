import QtQuick 2.0

Rectangle
{
    id: btn;
    signal buttonClicked;

    property string imgSource: "";

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

    Image
    {
        id: name
        source: btn.imgSource;
        anchors.centerIn: parent;
        height: parent.height - 6;
        smooth: true;
        width: sourceSize.width/sourceSize.height*height;

    }

    MouseArea
    {
        id : mr;
        anchors.fill: parent;
        onClicked: {btn.buttonClicked()}
    }

}
