import QtQuick 2.0
import "qrc:/js/Tools.js" as ToolsEngine

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
        delegate: Component
                    {
                        PluginInfoDelegate
                        {
                            width: myListView.width;
                            height: 100;
                            onPluginClicked: ToolsEngine.openForm(modelIndex);
                        }
                    }
        spacing: 10;
        model: pluginInfoModel;
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

    VScrollBar
    {
        id: verticalScroll2;
        anchors.right: parent.right;
        anchors.rightMargin: 5;
        position: jobCreatorForm.calcYPos();
        pageSize: jobCreatorForm.calcHRatio()
        visible: false;
    }

    JobCreatorForm
    {
        id: jobCreatorForm;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: parent.width - verticalScroll.width-20;
        visible: false;
        onBackClicked: ToolsEngine.closeForm();
    }
}
