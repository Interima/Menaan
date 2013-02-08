import QtQuick 2.0

Rectangle
{
    id: driveInfoDelegate;

    height: 84;

    radius: 4;
    smooth: true;
    border.color: "#838EA8";

    gradient: Gradient
              {
                  GradientStop { position: 0.0; color: "#87BBC6E0" }
                  GradientStop { position: 1.0; color: "#00BBC6E0" }
              }

    Column
    {
        id: gr;
        anchors.fill: parent;
        anchors.margins: 5;

        spacing: 6;

        Text
        {
            id: _label;
            text: qsTr("Label")+": "+model.label;
            color: "#FFFFFF";
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }

        Text
        {
            id: _mount;
            text: qsTr("Mount")+": "+model.mount;
            color: "#FFFFFF";
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }


        Text
        {
            id: _total;
            text: qsTr("Total size")+": "+model.totalSize +" "+ qsTr("Mb");
            color: "#FFFFFF";
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }

        Text
        {
            id: _free;
            text: qsTr("Free size")+": "+model.freeSize+" "+qsTr("Mb");
            color: "#FFFFFF";
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }
    }
}


