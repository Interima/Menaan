import QtQuick 2.0
import "qrc:/js/Menu.js" as MenuEngine

Rectangle
{
    id: menu;
    height: childrenRect.height;
    color: parent.color;
    width: parent.width;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 20;
    anchors.rightMargin: 30;

    signal menuClicked;

    property MenuItem currentItem: mitem1;
    property int currentItemNum: 1;
    property int mitemSpacing: (width - MenuEngine.getMenuItemsWidth())/5;

    MenuItem
    {
        id:mitem1;
        titleText: qsTr("Tools");
        state: "active";
        anchors.left: parent.left;
        onItemClicked: {MenuEngine.mitemOnClick(mitem1,1);menu.menuClicked();}
    }

    MenuItem
    {
        id:mitem2;
        titleText: qsTr("Job's list");
        anchors.left: mitem1.right;
        anchors.leftMargin: mitemSpacing;
        onItemClicked: {MenuEngine.mitemOnClick(mitem2,2);menu.menuClicked();}
    }

    MenuItem
    {
        id:mitem3;
        titleText: qsTr("Config");
        anchors.left: mitem2.right;
        anchors.leftMargin: mitemSpacing;
        onItemClicked: {MenuEngine.mitemOnClick(mitem3,3);menu.menuClicked();}
    }

    MenuItem
    {
        id:mitem4;
        titleText: qsTr("Help");
        anchors.left: mitem3.right;
        anchors.leftMargin: mitemSpacing;
        onItemClicked: {MenuEngine.mitemOnClick(mitem4,4);menu.menuClicked();}
    }

    MenuItem
    {
        id:mitem5;
        titleText: qsTr("About");
        anchors.left: mitem4.right;
        anchors.leftMargin: mitemSpacing;
        onItemClicked: {MenuEngine.mitemOnClick(mitem5,5);menu.menuClicked();}
    }

    MenuItem
    {
        id:mitem6;
        titleText: qsTr("Exit");
        anchors.left: mitem5.right;
        anchors.leftMargin: mitemSpacing;
        onItemClicked: {MenuEngine.mitemOnClick(mitem6,6);menu.menuClicked();}
    }

}
