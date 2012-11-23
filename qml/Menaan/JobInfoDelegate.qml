import QtQuick 1.1
import ix2.interima.jobstates 1.0

Rectangle
{
    id: jobDelegate;

    height: 24;

    radius: 4;
    smooth: true;
    border.color: "#838EA8";

    gradient: Gradient
              {
                  GradientStop { position: 0.0; color: "#87BBC6E0" }
                  GradientStop { position: 1.0; color: "#00BBC6E0" }
              }

    property bool expand: false;

    Row
    {
        id: gr;
        anchors.fill: parent;
        anchors.margins: 5;

        height: 24;
        spacing: 6;

        Text
        {
            id: _ticket;
            text: model.ticket+".";
            color: "#FFFFFF";
            width: 30 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Text
        {
            id: _source;
            text: model.source;
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            elide: Text.ElideLeft;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _dest;
            text: model.destination;
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            elide: Text.ElideLeft;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Text
        {
            id: _algorithm;
            text: model.algorithm;
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            elide: Text.ElideRight;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }


        Text
        {
            id: _state;

            text:   if (model.state==JobStates.Stopped) return qsTr("Stopped");
                    else if (model.state==JobStates.Running) return qsTr("Running");
                    else if (model.state==JobStates.Finished) return qsTr("Finished");
                    else if (model.state==JobStates.Error) return qsTr("Error");
                    else if (model.state==JobStates.Frozen) return qsTr("Frozen");

            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            color: "#FFFFFF";
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            elide: Text.ElideRight;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Rectangle
        {
            id: _control;
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            height: parent.height;
            color: "#00000000";
            anchors.verticalCenter: parent.verticalCenter;

            Row
            {
                id: ctrlRow;
                width: childrenRect.width;
                height: parent.height;
                anchors.left: parent.left;
                anchors.leftMargin: 6;
                spacing: 4;


                Image
                {
                    id: jobDeleterImg;
                    source: "qrc:/other/Delete";
                    width: sourceSize.width/sourceSize.height*height;
                    height: 15;
                    smooth: true;
                    anchors.verticalCenter: parent.verticalCenter;

                    MouseArea
                    {
                        id: mr;
                        anchors.fill: parent;
                        onClicked: menaan.deleteJob(index)
                    }
                }


                Image
                {
                    id: jobFreezeImg;
                    source: "qrc:/other/Freeze";
                    width: sourceSize.width/sourceSize.height*height;
                    height: 15;
                    smooth: true;
                    anchors.verticalCenter: parent.verticalCenter;
                    visible: {return (model.state==JobStates.Stopped)}

                    MouseArea
                    {
                        id: mr2;
                        anchors.fill: parent;
                        onClicked: menaan.freezeJob(index)
                    }
                }


                Image
                {
                    id: jobUnFreezeImg;
                    source: "qrc:/other/UnFreeze";
                    width: sourceSize.width/sourceSize.height*height;
                    height: 15;
                    smooth: true;
                    anchors.verticalCenter: parent.verticalCenter;
                    visible: {return (model.state==JobStates.Frozen)}

                    MouseArea
                    {
                        id: mr3;
                        anchors.fill: parent;
                        onClicked: menaan.unfreezeJob(index)
                    }
                }

                Image
                {
                    id: jobUpImg;
                    source: "qrc:/other/Up";
                    width: sourceSize.width/sourceSize.height*height;
                    height: 15;
                    smooth: true;
                    anchors.verticalCenter: parent.verticalCenter;
                    visible: {
                              return (model.state==JobStates.Frozen ||
                                  model.state==JobStates.Stopped);
                             }

                    MouseArea
                    {
                        id: mr4;
                        anchors.fill: parent;
                        onClicked: menaan.upJob(index)
                    }
                }

                Image
                {
                    id: jobDownImg;
                    source: "qrc:/other/Down";
                    width: sourceSize.width/sourceSize.height*height;
                    height: 15;
                    smooth: true;
                    anchors.verticalCenter: parent.verticalCenter;
                    visible: {
                              return (model.state==JobStates.Frozen ||
                                  model.state==JobStates.Stopped);
                             }

                    MouseArea
                    {
                        id: mr6;
                        anchors.fill: parent;
                        onClicked: menaan.downJob(index)
                    }
                }
             }
        }


        Text
        {
            id: _priority;
            text: model.priority;
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Text
        {
            id: _progress;
            text: model.progress +"%";
            color: "#FFFFFF";
            width: (parent.width - parent.spacing*parent.children.length
                    -2*_ticket.width)/7 ;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            anchors.verticalCenter: parent.verticalCenter;
            horizontalAlignment: Text.AlignLeft;
        }

        Rectangle
        {
            id: _rec;
            width: 20;
            height: parent.height;
            color: "#00000000";

            Image
            {
                id: expandImg;
                source: "qrc:/other/Expand";
                width: sourceSize.width/sourceSize.height*height;
                height: 15;
                smooth: true;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: parent.right;

                MouseArea
                {
                    id: rmr;
                    anchors.fill: parent;
                    onClicked: {
                                if (!jobDelegate.expand)
                                {
                                    gr.visible = false;
                                    ex.visible = true;
                                    jobDelegate.expand = true;
                                    jobDelegate.height = ex.height;
                                }
                                else
                                {
                                    gr.visible = true;
                                    ex.visible = false;
                                    jobDelegate.expand = false;
                                    jobDelegate.height = 24;
                                }
                            }
                }
            }
        }

    }

    Rectangle
    {
        id: ex;
        color: "#000ff0ff";
        height: childrenRect.height+12;
        visible: false;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.margins: 6;



        Grid
        {
            id: grd;
            columns: 2;
            spacing: 6;
            anchors.top: parent.top;

            Text
            {
                text: qsTr("Ticket:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: model.ticket;
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
            }

            Text
            {
                text: qsTr("Source:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: model.source;
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                elide: Text.ElideRight;
            }

            Text
            {
                text: qsTr("Destination:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: model.destination;
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                elide: Text.ElideRight;
            }

            Text
            {
                text: qsTr("State:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: if (model.state==JobStates.Stopped) return qsTr("Stopped");
                else if (model.state==JobStates.Running) return qsTr("Running");
                else if (model.state==JobStates.Finished) return qsTr("Finished");
                else if (model.state==JobStates.Error) return qsTr("Error");
                else if (model.state==JobStates.Frozen) return qsTr("Frozen");
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
            }

            Text
            {
                text: qsTr("Priority:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: model.priority;
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
            }

            Text
            {
                text: qsTr("Progress:");
                color: "#FFFFFF";
                width: 120;
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
                font.bold: true;
            }

            Text
            {
                text: model.progress;
                color: "#FFFFFF";
                font.family: "DejaVu Sans";
                font.pixelSize: 12;
            }
        }

        Image
        {
            id: constrictImg;
            source: "qrc:/other/Constrict";
            width: sourceSize.width/sourceSize.height*height;
            height: 15;
            smooth: true;
            anchors.bottom: grd.bottom;
            anchors.right: parent.right;

            MouseArea
            {
                id: rmr2;
                anchors.fill: parent;
                onClicked: {
                            if (!jobDelegate.expand)
                            {
                                gr.visible = false;
                                ex.visible = true;
                                jobDelegate.expand = true;
                                jobDelegate.height = ex.height;
                            }
                            else
                               {
                                   gr.visible = true;
                                   ex.visible = false;
                                   jobDelegate.expand = false;
                                   jobDelegate.height = 24;
                               }
                           }
            }
        }
    }
}


