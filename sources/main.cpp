#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QBitmap>
#include "menaan.h"
#include <QTranslator>
#include <QDebug>


Q_DECL_EXPORT int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // we can't read config in menaan contructor
    // because translator must be create and installed before widgets creating
    // so we read conf file there...

    qDebug()<<"[Application say:] Reading configuration";

    ConfigData *configData;

    // read config data for application
    {
        QFile file(QApplication::applicationDirPath()+"/config.xml");

        qDebug()<<"[Application say:] Check file"<<QApplication::applicationDirPath()+"/config.xml";

        QXmlInputSource inputSource(&file);
        QXmlSimpleReader configReader;

        configData = new ConfigData();
        ConfigHandler *configHandler = new ConfigHandler(configData);

        configReader.setContentHandler(configHandler);
        configReader.setErrorHandler(configHandler);

        configReader.parse(inputSource);

        delete configHandler;
    }

    // set translation
    qDebug()<<"[Application say:] Translation install";
    QTranslator trans;
    int lg = configData->getLanguage();
    switch (lg)
    {
        case ConfigData::English:
            trans.load(QApplication::applicationDirPath()+"/translations/en.qm");
            break;
        case ConfigData::Russian:
            trans.load(QApplication::applicationDirPath()+"/translations/ru.qm");
            break;

        case ConfigData::Germany:
            trans.load(QApplication::applicationDirPath()+"/translations/de.qm");
            break;

        case ConfigData::French:
            trans.load(QApplication::applicationDirPath()+"/translations/fr.qm");
            break;


        default:
            trans.load(QApplication::applicationDirPath()+"/translations/en.qm");
    }

    app.installTranslator(&trans);

    Menaan * mainWidget = new Menaan(configData);

    Q_UNUSED(mainWidget)

    return app.exec();
}
