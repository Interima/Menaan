import QtQuick 1.1
import "TabWidget.js" as TabWidgetEngine

Rectangle
{
    id: tabWidget;
    anchors.fill: parent;
    color: parent.color;

    Rectangle
    {
        id: menuArea
        anchors.top: parent.top;
        width: parent.width;
        color: parent.color;
        height: childrenRect.height;

        Separator { id: topSpacer; sepHeight: 24; anchors.top: parent.top; }

        Menu
        {
            id:mainMenu;
            anchors.top: topSpacer.bottom;
            onMenuClicked: {TabWidgetEngine.tabSwitch(mainMenu.currentItemNum)}
        }

        Separator { id: bottomSpacer; sepHeight: 14; anchors.top: mainMenu.bottom; }

        Separator
        {
            id: mainMenuLine; sepColor:"#838EA8"; sepHeight: 2;
            anchors.top:bottomSpacer.bottom;
        }
    }

    Separator { id: middleSpacer; sepHeight: 16; anchors.top: menuArea.bottom; }


    Rectangle
    {
        id: containerArea;
        anchors.top: middleSpacer.bottom;
        anchors.bottom: footerTopSpacer.top;
        anchors.left: parent.left;
        color: parent.color;
        width: parent.width;


        Container
        {
            id: toolsContainer;
            titleText: qsTr("Please choose encode/decode algorithm:");
            titleSize: 14;
            state: "active"

            ToolsTab
            {

            }

        }
        Container
        {
            id: jobListContainer;
            titleText: qsTr("Jobs:");
            titleSize: 14;
            state: "inactive"


           JobsTab
           {

           }
        }

        Container
        {
            id: configContainer;
            titleText: qsTr("Configure parameters:");
            titleSize: 14;
            state: "inactive"

            ConfigTab
            {
                id: configTab;
            }
        }

        Container
        {
            id: helpContainer;
            titleText: qsTr("Help pages:");
            titleSize: 14;
            state: "inactive"

            HelpTab
            {

            }

        }

        Container
        {
            id: aboutContainer;
            titleText: qsTr("About application:");
            titleSize: 14;
            state: "inactive"

            AboutTab
            {
                id: aboutTab;
            }

        }

        Container
        {
            id: exitContainer;
            titleText: qsTr("Confirm your exit:");
            titleSize: 14;
            state: "inactive"

            ExitTab
            {
                id: exitTab;
                onYesClicked: menaan.exitRequired();
            }


        }

    }

    Separator { id: footerTopSpacer; sepHeight: 16; anchors.bottom: footerLine.top; }

    Separator
    {
        id: footerLine; sepColor:"#838EA8"; sepHeight: 2;
        anchors.bottom: footerBottomSpacer.top;
    }

    Separator { id: footerBottomSpacer; sepHeight: 16; anchors.bottom: parent.bottom; }

}
