import QtQuick 2.0

Rectangle
{
    id: pathDialog;
    color: parent.color;
    anchors.fill: parent;

    Rectangle
    {
        id: driveBar;
        anchors.margins: 10;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: driveContent.left;

        ListView
        {
            id: driveListView
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            width: parent.width - driveVerticalScroll.width ;

            header: Component
                        {
                           Rectangle
                           {
                               id: cont;
                               color: "#00000000";
                               height: 40;
                               width: myListView.width;

                               Text
                               {
                                   id: driveTitle;
                                   anchors.horizontalCenter: parent.horizontalCenter;
                                   anchors.verticalCenter: parent.verticalCenter;
                                   font.pixelSize: 14;
                                   font.family: "DejaVu Sans";
                                   color: "#FFFFFF";
                                   text: qsTr("Places:");
                               }
                           }
                        }



            delegate: Component
                        {
                            DriveInfoDelegate
                            {
                                width: myListView.width;
                            }
                        }
            spacing: 5;
            model: driveInfoModel;
            opacity: 1;
            visible: true;

            Behavior on opacity { NumberAnimation { duration : 600; } }
        }


        VScrollBar
        {
            id: driveVerticalScroll;
            anchors.right: parent.right;
            anchors.rightMargin: 5;
            position: driveListView.visibleArea.yPosition;
            pageSize: driveListView.visibleArea.heightRatio;
        }
    }


        Rectangle
        {
            id: driveContent;
            anchors.margins: 10;
            width: parent.width -200;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;

            ListView
            {
                id: contentListView
                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                width: parent.width - contentVerticalScroll.width ;

                header:
                Component
                {
                    Rectangle
                    {
                        id: contentHeader;
                        color: "#00000000";
                        height: 40;
                        width: contentListView.width;

                        Text
                        {
                            id: pathTitle;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            anchors.verticalCenter: parent.verticalCenter;
                            font.pixelSize: 14;
                            font.family: "DejaVu Sans";
                            color: "#FFFFFF";
                            text: qsTr("Path:")+ " " + model.currentPath;
                        }
                    }
                 }



                delegate: Component
                            {
                                ContentInfoDelegate
                                {
                                    width: contentListView.width;
                                }
                            }
                spacing: 5;
                model: contentInfoModel;
                opacity: 1;
                visible: true;

                Behavior on opacity { NumberAnimation { duration : 600; } }
            }


            VScrollBar
            {
                id: contentVerticalScroll;
                anchors.right: parent.right;
                anchors.rightMargin: 5;
                position: contentListView.visibleArea.yPosition;
                pageSize: contentListView.visibleArea.heightRatio;
            }
        }

}
