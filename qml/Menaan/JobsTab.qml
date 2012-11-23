import QtQuick 1.1

Rectangle
{
    color: parent.color;
    anchors.fill: parent;

    ListView
    {
        id: myListView
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: parent.width - verticalScroll.width-20;

        header: Component
                    {
                       Rectangle
                       {
                           id: cont;
                           color: "#00000000";
                           height: childrenRect.height;
                           width: myListView.width;

                           JobInfoHeader
                                {
                                    id: head;
                                    width: parent.width;
                                    height: 40;
                                    anchors.left: parent.left;
                                    anchors.top: parent.top;
                                }

                           Item
                           {
                               anchors.top: head.bottom;
                               width:  myListView.width;
                               height: 10;
                           }
                       }
                    }



        delegate: Component
                    {
                        JobInfoDelegate
                        {
                            width: myListView.width;
                        }
                    }
        spacing: 5;
        model: jobInfoModel;
        opacity: 1;


        Behavior on opacity { NumberAnimation { duration : 400; } }
    }

    VScrollBar
    {
        id: verticalScroll;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        position: myListView.visibleArea.yPosition;
        pageSize: myListView.visibleArea.heightRatio;
    }
}
