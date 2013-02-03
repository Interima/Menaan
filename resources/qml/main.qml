import QtQuick 2.0
import "qrc:/js/Msg.js" as MsgEngine;
Rectangle
{
    id: main;
    width: 200
    height: 200
    color: "#4A5570"

    Connections
    {
        target: menaan;
        onError: MsgEngine.errorMsg(error);
    }

    TabWidget
    {
        id :tablet;
    }

}


