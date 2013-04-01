import QtQuick 2.0
import "qrc:/js/Config.js" as ConfigEngine

Rectangle
{
    id: configTab;
    anchors.fill: parent;
    color: "#00000000";

    property int titleSize: 14;
    property string titleColor: "#FFFFFF"
    property string titleFont: "DejaVu Sans";

    property int currentLanguageItem: 0;
    property int currentMultiThreadItem: 0;
    property int currentExtItem: 0;
    property int currentRewriteItem: 0;
    property int currentFinishDeleteItem: 0;


    Connections
    {
        target: menaan;
        onConfigDataUpdated: ConfigEngine.configDefaulter(l,mt,afd,e,r);
    }

    Flickable
    {
        id: flickArea;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        width: parent.width - verticalScroll.width - 30
        contentWidth: parent.width;
        contentHeight: content.height;
        flickableDirection: Flickable.VerticalFlick;
        clip: true;

        Rectangle
        {
            id: content;
            anchors.top: parent.top;
            height: childrenRect.height;
            anchors.left:parent.left;
            width: flickArea.width;
            color: "#00000000";


            SimpleFrame
            {
                id: header;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: parent.top;
                height: 40;

                Text
                {
                    text: qsTr("Options");
                    anchors.left: parent.left;
                    anchors.leftMargin: 15;
                    anchors.verticalCenter: parent.verticalCenter;
                    color: "#FFFFFF";
                    font.family: "DejaVu Sans";
                    font.pixelSize: 14;
                }

                Text
                {
                    text: qsTr("Values");
                    anchors.right: parent.right;
                    anchors.rightMargin: 25;
                    anchors.verticalCenter: parent.verticalCenter;
                    color: "#FFFFFF";
                    font.family: "DejaVu Sans";
                    font.pixelSize: 14;
                }
            }

            ConfigItem
            {
                id: languageConfig;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: header.bottom;
                anchors.topMargin: 10;
                titleText: qsTr("Language:");

                ConfigChanger
                {
                    id: languageChanger;
                    anchors.top: parent.top;
                    onItemClicked: {ConfigEngine.languageSwitcher(currentLanguageItem);}

                    Text
                    {
                        id: english;
                        text: qsTr("English");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        id: russian;
                        text: qsTr("Russian");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        id: french;
                        text: qsTr("French");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        id: germany;
                        text: qsTr("Germany");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }
                }
            }

            ConfigItem
            {
                id: multiThreadConfig;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: languageConfig.bottom;
                anchors.topMargin: 5;
                titleText: qsTr("Use multi thread:");

                ConfigChanger
                {
                    id: multiThreadChanger;
                    anchors.top: parent.top;
                    width: parent.width;
                    onItemClicked: {ConfigEngine.multiThreadSwitcher(currentMultiThreadItem);}

                    Text
                    {
                        text: qsTr("Disabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        text: qsTr("Enabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }
                }
            }


            ConfigItem
            {
                id: finishDeleteConfig;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: multiThreadConfig.bottom;
                anchors.topMargin: 5;
                titleText: qsTr("Auto delete finished job:");

                ConfigChanger
                {
                    id: finishDeleteChanger;
                    anchors.top: parent.top;
                    width: parent.width;
                    onItemClicked: {ConfigEngine.finishDeleteSwitcher(currentFinishDeleteItem);}

                    Text
                    {
                        text: qsTr("Disabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        text: qsTr("Enabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }
                }
            }

            ConfigItem
            {
                id: extConfig;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: finishDeleteConfig.bottom;
                anchors.topMargin: 5;
                titleText: qsTr("Use special extension:");

                ConfigChanger
                {
                    id: extChanger;
                    anchors.top: parent.top;
                    width: parent.width;
                    onItemClicked: {ConfigEngine.extSwitcher(currentExtItem);}

                    Text
                    {
                        text: qsTr("Disabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        text: qsTr("Enabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                }
            }

            ConfigItem
            {
                id: rewriteConfig;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.top: extConfig.bottom;
                anchors.topMargin: 5;
                titleText: qsTr("Rewrite exists files:");

                ConfigChanger
                {
                    id: rewriteChanger;
                    anchors.top: parent.top;
                    width: parent.width;
                    onItemClicked: {ConfigEngine.rewriteSwitcher(currentRewriteItem);}

                    Text
                    {
                        text: qsTr("Disabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }

                    Text
                    {
                        text: qsTr("Enabled");
                        color: configTab.titleColor;
                        font.pixelSize: configTab.titleSize;
                        font.family: configTab.titleFont;
                        anchors.right: parent.right;
                    }
                }
            }

            SimpleButton
            {
                id: saveBtn;
                width: parent.width/2 - 5;
                height: 26;
                titleText: qsTr("Save");
                anchors.left: parent.left;
                anchors.top: rewriteConfig.bottom;
                anchors.topMargin: 15;
                onButtonClicked: {ConfigEngine.saveConfig();}
            }

            SimpleButton
            {
                id: resetBtn;
                width: parent.width/2 - 5;
                height: 26;
                titleText: qsTr("Reset");
                anchors.right: parent.right
                anchors.top: rewriteConfig.bottom;
                anchors.topMargin: 15;
                onButtonClicked: {ConfigEngine.resetConfig();}
            }
        }
    }


    VScrollBar
    {
        id: verticalScroll;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        position: flickArea.visibleArea.yPosition;
        pageSize: flickArea.visibleArea.heightRatio;
    }
}
