//error message
function errorMsg(str)
{
    var comp = Qt.createComponent("Message.qml");
    var obj = comp.createObject(main);
    obj.titleText = qsTr("Mena'an");
    obj.dataText = str+qsTr("\n\nClick to close.");
}
