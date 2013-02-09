import QtQuick 2.0
import x2.interima.contenttypes 1.0

Rectangle
{
    id: contentInfoDelegate;

    height: 30;

    radius: 4;
    smooth: true;
    border.color: if (ListView.isCurrentItem) return "#FFFFFF";
                  else return "#838EA8";

    MouseArea
    {
        id: ma;
        anchors.fill: parent;
        hoverEnabled: true;
        onEntered: {gradient = hovered; _itemName.color = "#FF000000";}
        onExited: {gradient = released; _itemName.color = "#FFFFFFFF";}
        onClicked: contentListView.currentIndex=index;
        onDoubleClicked: contentInfoModel.cdDown(model.itemName);
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
            id: _itemName;
            text: model.itemName;
            color: "#FFFFFF";
            width: parent.width - _itemType.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;
            height: parent.height;
            elide: Text.ElideMiddle;
        }
    }

    Text
    {
        id: _itemType;
        text: if (model.itemType==ContentTypes.File) return "  file";
              else if (model.itemType==ContentTypes.Dir) return "  dir";
              else if (model.itemType==ContentTypes.Symlink) return "  sym";
              else return "  unknown";

        color: "#FFFFFF";
        anchors.right: parent.right;
        font.family: "DejaVu Sans";
        font.pixelSize: 12;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
        height: parent.height;
        elide: Text.ElideMiddle;
    }


}


