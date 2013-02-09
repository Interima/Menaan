import QtQuick 2.0

Rectangle
{
    id: driveInfoDelegate;

    height: 84;

    radius: 4;
    smooth: true;
    border.color: if (ListView.isCurrentItem) return "#FFFFFF";
                  else return "#838EA8";

    property string textColor: "#FFFFFFFF";

    MouseArea
    {
        id: ma;
        anchors.fill: parent;
        hoverEnabled: true;
        onEntered: {gradient = hovered; textColor = "#FF000000";}
        onExited: {gradient = released; textColor = "#FFFFFFFF";}
        onClicked: {driveListView.currentIndex=index;
                    contentInfoModel.changePath(model.mount);}
    }

    Gradient
    {
        id: hovered;
        GradientStop { position: 0.0; color: "#F0BBC6E0" }
        GradientStop { position: 1.0; color: "#24BBC6E0" }
    }

    Gradient
    {
        id: released;
        GradientStop { position: 0.0; color: "#87BBC6E0" }
        GradientStop { position: 1.0; color: "#00BBC6E0" }
    }

    gradient: released;

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
            color: driveInfoDelegate.textColor;
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
            color: driveInfoDelegate.textColor;
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
            color: driveInfoDelegate.textColor;
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
            color: driveInfoDelegate.textColor;
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }
    }
}


