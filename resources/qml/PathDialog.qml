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
        anchors.rightMargin: 20;
        color: parent.color;


        SimpleFrame
        {
            id: header;
            color: "#00000000";
            height: 30;
            anchors.top: parent.top;
            width: parent.width;

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

        ListView
        {
            id: driveListView
            anchors.left: parent.left;
            anchors.top: header.bottom;
            anchors.topMargin: 10;
            anchors.bottom: parent.bottom;
            width: parent.width - driveVerticalScroll.width*2 ;


            delegate: Component
                        {
                            DriveInfoDelegate
                            {
                                width: driveListView.width;
                            }
                        }

            //highlight: Rectangle{color:"red"; width:100; height: 200;}

            snapMode: ListView.SnapToItem;
            spacing: 5;
            model: driveInfoModel;
            clip:true;
            focus:true;

            Behavior on opacity { NumberAnimation { duration : 600; } }
        }


        VScrollBar
        {
            id: driveVerticalScroll;
            anchors.right: parent.right;
            anchors.rightMargin: 0;
            anchors.top: driveListView.top;
            anchors.bottom: driveListView.bottom;
            position: driveListView.visibleArea.yPosition;
            pageSize: driveListView.visibleArea.heightRatio;
        }
    }


        Rectangle
        {
            id: driveContent;
            anchors.margins: 10;
            width: parent.width*3/4;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;
            color: parent.color;



            SimpleFrame
            {
                id: contentHeader;
                color: "#00000000";
                height: 30;
                width: parent.width;

                Text
                {
                    id: pathTitle;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.leftMargin: 4;
                    font.pixelSize: 14;
                    font.family: "DejaVu Sans";
                    color: "#FFFFFF";
                    text: qsTr("Path:")+ " " + contentInfoModel.currentPath;
                }
            }


            ListView
            {
                id: contentListView
                anchors.left: parent.left;
                anchors.top: contentHeader.bottom;
                anchors.bottom: parent.bottom;
                anchors.topMargin: 10;
                width: parent.width - contentVerticalScroll.width*2;

                delegate: Component
                            {
                                ContentInfoDelegate
                                {
                                    width: contentListView.width;
                                }
                            }
                spacing: 5;
                clip: true;
                snapMode: ListView.SnapToItem;
                model: contentInfoModel;
            }


            VScrollBar
            {
                id: contentVerticalScroll;
                anchors.right: parent.right;
                anchors.rightMargin: 0;
                anchors.top: contentListView.top;
                anchors.bottom: contentListView.bottom;
                position: contentListView.visibleArea.yPosition;
                pageSize: contentListView.visibleArea.heightRatio;
            }
        }

}
