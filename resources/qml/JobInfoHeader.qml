import QtQuick 2.0

Rectangle
{
    id: jobHeader;

    radius: 4;
    smooth: true;
    border.color: "#838EA8";

    gradient: Gradient
              {
                  GradientStop { position: 0.0; color: "#87BBC6E0" }
                  GradientStop { position: 1.0; color: "#00BBC6E0" }
              }

    Row
    {
        id: gr;
        anchors.fill: parent;
        anchors.margins: 5;

        spacing: 6;

        Text
        {
            id: _ticket;
            text: qsTr("№");
            color: "#FFFFFF";
            width: 30;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _source;
            text: qsTr("Input");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            elide: Text.ElideLeft;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _dest;
            text: qsTr("Output");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            elide: Text.ElideLeft;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _algorithm;
            text: qsTr("Algorithm");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            elide: Text.ElideRight;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _state;
            text: qsTr("State")
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            color: "#FFFFFF";
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            elide: Text.ElideRight;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Text
        {
            id: _control;
            text: qsTr("Control");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _priority;
            text: qsTr("Priority");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Text
        {
            id: _progress;
            text: qsTr("Progress");
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*(parent.children.length+1)
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


    }

}

