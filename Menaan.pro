
QT += xml declarative

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    plugininfo.cpp \
    plugininfomodel.cpp \
    menaan.cpp \
    configdata.cpp \
    confighandler.cpp \
    jobinfomodel.cpp \
    jobinfo.cpp \
    droparea.cpp \
    worker.cpp \
    jobmanager.cpp \
    activeworkerinfo.cpp


lupdate {
        SOURCES += \
    qml/Menaan/AboutTab.qml\
    qml/Menaan/ConfigChanger.qml\
    qml/Menaan/ConfigItem.qml\
    qml/Menaan/Config.js\
    qml/Menaan/ConfigTab.qml\
    qml/Menaan/Container.qml\
    qml/Menaan/ExitTab.qml\
    qml/Menaan/HelpTab.qml\
    qml/Menaan/ImgButton.qml\
    qml/Menaan/InputFrame.qml\
    qml/Menaan/JobCreaterForm.qml\
    qml/Menaan/JobCreator.js\
    qml/Menaan/JobInfoDelegate.qml\
    qml/Menaan/JobInfoHeader.qml\
    qml/Menaan/JobsTab.qml\
    qml/Menaan/main.qml\
    qml/Menaan/MenuItem.qml\
    qml/Menaan/Menu.js\
    qml/Menaan/Menu.qml\
    qml/Menaan/Message.qml\
    qml/Menaan/PluginInfoDelegate.qml\
    qml/Menaan/ProgressBar.qml\
    qml/Menaan/Separator.qml\
    qml/Menaan/SimpleButton.qml\
    qml/Menaan/SimpleFrame.qml\
    qml/Menaan/TabWidget.js\
    qml/Menaan/TabWidget.qml\
    qml/Menaan/Tools.js\
    qml/Menaan/ToolsTab.qml\
    qml/Menaan/VScrollBar.qml\
    qml/Menaan/Msg.js
}


# Please do not modify the following two lines. Required for deployment.
#include(qmlapplicationviewer/qmlapplicationviewer.pri)
#qtcAddDeployment()

OTHER_FILES +=

# For release project uncomment this
#DEFINES += QT_NO_DEBUG_OUTPUT

HEADERS += \
    plugininfo.h \
    plugininfomodel.h \
    menaan.h \
    configdata.h \
    confighandler.h \
    jobinfomodel.h \
    jobinfo.h \
    droparea.h \
    worker.h \
    jobmanager.h \
    plugininterface.h \
    jobstates.h \
    activeworkerinfo.h \
    jobtypes.h

RESOURCES += \
    resources.qrc

TRANSLATIONS =  menaan_en.ts \
                menaan_ru.ts \
                menaan_de.ts \
                menaan_fr.ts
