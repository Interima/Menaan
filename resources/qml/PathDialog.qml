import QtQuick 2.0

Container
{
    id: pathDialog;
    color: parent.color;
    anchors.fill: parent;

    Rectangle
    {
        id: driveBar;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: controlBar.top;
        anchors.bottomMargin: 20;
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
            id: driveListView;
            anchors.left: parent.left;
            anchors.top: header.bottom;
            anchors.topMargin: 10;
            anchors.bottom: parent.bottom;
            width: parent.width - driveVerticalScroll.width*2;

            delegate: Component
                        {
                            DriveInfoDelegate
                            {
                                width: driveListView.width;
                            }
                        }

            snapMode: ListView.SnapToItem;
            spacing: 5;
            model: driveInfoModel;
            clip:true;
            focus:true;

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
        width: parent.width*3/4;
        anchors.top: parent.top;
        anchors.bottom: controlBar.top;
        anchors.bottomMargin: 20;
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
                anchors.right: parent.right;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.margins: 5;
                font.pixelSize: 14;
                font.family: "DejaVu Sans";
                color: "#FFFFFF";
                elide: Text.ElideMiddle;
                horizontalAlignment: Text.AlignHCenter;
                text: qsTr("Path:")+ " " + contentInfoModel.currentPath;
            }
        }


        ListView
        {
            id: contentListView;
            anchors.left: parent.left;
            anchors.top: contentHeader.bottom;
            anchors.bottom: parent.bottom;
            anchors.topMargin: 10;
            width: parent.width - contentVerticalScroll.width*2;
            currentIndex: 0;

            delegate: Component
                        {
                            ContentInfoDelegate
                            {
                                width: contentListView.width;
                                height: 20;

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

    Row
    {
        id: controlBar;
        anchors.bottom: parent.bottom;
        width: childrenRect.width;
        anchors.right: parent.right;
        height: 40;
        spacing: 10;

        SimpleButton
        {
            id: cnacel;
            titleText: qsTr("Cancel");
            width: 80;
            height: 30;
        }

        SimpleButton
        {
            id: choose;
            titleText: qsTr("Choose");
            width: 80;
            height: 30;
        }
    }

    Row
    {
        id: controlBar2;
        anchors.bottom: parent.bottom;
        width: childrenRect.width;
        anchors.left: driveContent.left;
        height: 40;
        spacing: 10;


        ImgButton
        {
            id: refreshContent;
            imgSource: "qrc:/other/Refresh"
            width: 30;
            height: 30;
            onButtonClicked: contentInfoModel.refresh();
        }

        ImgButton
        {
            id: cdUp;
            imgSource: "qrc:/other/Back"
            width: 30;
            height: 30;
            onButtonClicked: contentInfoModel.cdUp();
        }
    }

    Row
    {
        id: driveControlBar;
        anchors.bottom: parent.bottom;
        anchors.left: driveBar.left;
        width: 30;
        height: 40;
        spacing: 10;


        ImgButton
        {
            id: refreshDrive;
            imgSource: "qrc:/other/Refresh"
            width: parent.width;
            height: 30;
            onButtonClicked: driveInfoModel.refresh();
        }
    }
}
