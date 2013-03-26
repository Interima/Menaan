import QtQuick 2.0
import x2.interima.contenttypes 1.0

Rectangle
{
    id: contentInfoDelegate;

    height: 30;
    color: "#00000000";

    MouseArea
    {
        id: ma;
        anchors.fill: parent;
        hoverEnabled: true;
        onEntered: _itemName.anchors.leftMargin=60;
        onExited: _itemName.anchors.leftMargin=10;
        onClicked: contentListView.currentIndex=index;
        onDoubleClicked: contentInfoModel.cdDown(model.itemName);
    }

    Rectangle
    {
        id: gr;
        anchors.fill: parent;
        anchors.margins: 5;
        color: "#00000000";

        Text
        {
            id: _itemName;
            text: model.itemName;
            color: if (contentInfoDelegate.ListView.isCurrentItem) return "#FFFFFFFF";
                   else return "#F0BBC6E0";
            anchors.left: parent.left;
            anchors.right: _itemType.left;
            anchors.leftMargin: 10;
            anchors.rightMargin: 10;
            font.family: "DejaVu Sans";
            font.pixelSize: 14;
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            height: parent.height;
            elide: Text.ElideMiddle;

            Behavior on anchors.leftMargin { NumberAnimation { duration: 200 }}
        }

        Image
        {
            id: _itemType;
            source: if (model.itemType==ContentTypes.File) return "qrc:/other/File"
                  else if (model.itemType==ContentTypes.Dir) return "qrc:/other/Directory"
                  else if (model.itemType==ContentTypes.Symlink) return "qrc:/other/File"
                  else return "qrc:/other/File";

            anchors.right: parent.right;
            anchors.rightMargin: 10;
            anchors.verticalCenter: parent.verticalCenter;
        }
    }

    Separator
    {
        anchors.top: gr.bottom;
        anchors.topMargin: 2;
        anchors.left: parent.left;
        anchors.right: parent.right;
        sepColor: if (contentInfoDelegate.ListView.isCurrentItem) return "#FFFFFFFF";
                  else return "#838EA8";
        sepHeight: 1;


    }

}


