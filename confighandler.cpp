#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>

#include "confighandler.h"
#include "menaan.h"

ConfigHandler::ConfigHandler(ConfigData *_cfg):
    cfg(_cfg)
{
}

bool ConfigHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    Q_UNUSED(namespaceURI);
    Q_UNUSED(localName);
    Q_UNUSED(qName);
    Q_UNUSED(atts);

    // open tags all ignored
    return true;
}

bool ConfigHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    Q_UNUSED(namespaceURI);
    Q_UNUSED(localName);

    // inflate cfg
    if (qName=="language") cfg->setLanguage(str.toInt());
    if (qName=="multiThread") cfg->setMultiThread(str.toInt());
    if (qName=="autoFinishedDelete") cfg->setAutoFinishedDelete(str.toInt());
    if (qName=="ext") cfg->setExt(str.toInt());
    if (qName=="rewrite") cfg->setRewrite(str.toInt());


    str = "";
    return true;
}

bool ConfigHandler::characters(const QString &ch)
{
    str+=ch;
    return true;
}

bool ConfigHandler::fatalError(const QXmlParseException &exception)
{
    // error occurred. tell to user error information
    QMessageBox::critical(0,QObject::tr("Config Reader"),
                         QObject::tr("Error in config file\nLine: %1\nColumn: %2\nError: %3")
                         .arg(exception.lineNumber())
                         .arg(exception.columnNumber())
                         .arg(exception.message()),QMessageBox::Ok);

    int ret = QMessageBox::information(0,QObject::tr("Recovery"),
                                       QObject::tr("Do you want reset config?"),
                                       QMessageBox::Yes,QMessageBox::No);


    // try to recovery user config from default config file
    switch (ret)
    {
        case QMessageBox::Yes:
             if (Menaan::configDataRecovery())
                 QMessageBox::information(0,QObject::tr("Recovery"),
                                          QObject::tr("Config has been successfully restored!\nNow restart application."));
             else
                 QMessageBox::critical(0,QObject::tr("Recovery"),
                                       QObject::tr("Can't recovery config file.\nPlease visit to application site."));


        case QMessageBox::No: break;
    }


    ::exit(1);
}
