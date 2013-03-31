import QtQuick 2.0
import "qrc:/js/Msg.js" as MsgEngine;

Rectangle
{
    id: main;
    width: 800
    height: 400
    color: "#4A5570"

//    PathDialog
//    {
//        id: dialog;
//    }

    Timer
    {
       interval: 2000;
       repeat: false;
       running: true;
       onTriggered:
       {
            tablet.opacity = 1;
            splash.opacity = 0;
       }
    }

    MainSplash
    {
        id: splash;
        visible: true;
        opacity: 1;

        Behavior on opacity
        {
            NumberAnimation
            {
                duration: 600;
                onRunningChanged: if (!running) splash.visible = false;
            }
        }
    }

    Connections
    {
        target: menaan;
        onError: MsgEngine.errorMsg(error);
    }

    TabWidget
    {
        id: tablet;
        visible: true;
        opacity: 0;

        Behavior on opacity
        {
            NumberAnimation
            {
                duration: 600;
            }
        }
    }

}


