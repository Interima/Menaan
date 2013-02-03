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
    // TODO
    // show message about fatal error

    ::exit(1);
}
