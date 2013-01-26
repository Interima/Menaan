import QtQuick 1.1

Rectangle
{
    id: pluginDelegate;

    signal pluginClicked(int modelIndex);

    gradient: Gradient
    {
      GradientStop { position: 0.0; color: "#87BBC6E0" }
      GradientStop { position: 1.0; color: "#00BBC6E0" }
    }

    border.color: "#838EA8";
    radius: 4;
    smooth: true;

    MouseArea
    {
        id: ma;
        anchors.fill: parent;
        onClicked: pluginClicked(index);
    }

    Rectangle
    {
        id: leftColumn;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
        height: childrenRect.height;
        width:  childrenRect.width;
        color: "#00000000";
        clip: true;

        Column
        {
            anchors.margins: 2;
            spacing: 10;

            Text
            {
                id: name;
                text: qsTr("Name")+": <i>"+model.name+"</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12;
            }

            Text
            {
                id: author
                text: qsTr("Author")+": <i>"+model.author+"</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12
            }

            Text
            {
                id: keyLength;
                text: qsTr("Key length")+": <i>"+model.keyLength+"</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12
            }

            Text
            {
                id: blockLength;
                text: qsTr("Block length")+": <i>"+model.blockLength+"</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12
            }
        }

    }

    Rectangle
    {
        id: rightColumn;
        anchors.left: leftColumn.right;
        anchors.right: parent.right;
        anchors.rightMargin: 10;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
        height: childrenRect.height;
        color: "#00000000";

        Rectangle
        {
            color:"#00000000";
            height: childrenRect.height;
            anchors.left: parent.left;
            anchors.right: parent.right;

            Text
            {
                id: speedText;
                text: qsTr("Speed Level")+":";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize:12
                anchors.verticalCenter: speedVisual.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: (speedVisual.x - parent.x)/2
            }

            ProgressBar
            {
                id: speedVisual;
                maxValue: 10;
                progress: model.speedLevel;
                width: parent.width - (speedText.width + speedValue.width + 220);
                height: 18;
                anchors.top: parent.top;
                anchors.right: speedValue.left;
                anchors.rightMargin: 10;
            }

            Text
            {
                id: speedValue
                text: "<i>"+model.speedLevel+"/10</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12
                anchors.verticalCenter: speedVisual.verticalCenter;
                anchors.right: parent.right;
            }


            Text
            {
                id: safetyText;
                text: qsTr("Safety Level")+":";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize: 12
                anchors.verticalCenter: safetyVisual.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: (safetyVisual.x - parent.x)/2
            }

            ProgressBar
            {
                id: safetyVisual;
                maxValue: 10;
                progress: parseInt(model.safetyLevel);
                width: speedVisual.width;
                height: 18;
                anchors.top: speedVisual.bottom;
                anchors.topMargin: 10;
                anchors.right: safetyValue.left;
                anchors.rightMargin: 10;
            }

            Text
            {
                id: safetyValue
                text: "<i>"+model.safetyLevel+"/10</i>";
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                font.pixelSize:12
                anchors.verticalCenter: safetyVisual.verticalCenter;
                anchors.right: parent.right;
            }
        }
    }
}

