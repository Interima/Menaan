import QtQuick 2.0

Rectangle
{
    id: contentInfoDelegate;

    height: 30;

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
            id: _itemName;
            text: model.itemName;
            color: "#FFFFFF";
            width: parent.width;
            font.family: "DejaVu Sans";
            font.pixelSize: 12;
            horizontalAlignment: Text.AlignLeft;
            elide: Text.ElideMiddle;
        }
    }
}


