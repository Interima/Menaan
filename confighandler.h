#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

/**
    @file configdata.h
    Contains ConfigHandler class description.
    includes files: configdata.h, QXmlDefaultHandler.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QtXml/QXmlDefaultHandler>
#include "configdata.h"

//! ConfigHandler class represent parser handler for application config file
/*!
    Data parse by this class and inflate ConfigData object.
    This class inherited from QXmlDefaultHandler and overrides some functions.
*/
class ConfigHandler : public QXmlDefaultHandler
{
public:

    //! Constructor for ConfigHandler class
    /*!
        \param cfg  - non null pointer for existing ConfigData object
    */
    explicit ConfigHandler(ConfigData * _cfg);

    //! Overrides QXmlDefaultHandler::startElement function
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);

    //! Overrides QXmlDefaultHandler::endElement function
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

    //! Overrides QXmlDefaultHandler::characters function
    bool characters(const QString &ch);

    //! Overrides QXmlDefaultHandler::characters function
    /*!
        Try recovery user config file from default
    */
    bool fatalError(const QXmlParseException &exception);

private:
    //! This property holds pointer to ConfigData object
    /*! Can't be a null pointer
        \sa ConfigHandler()
    */
    ConfigData * cfg;

    //! This property holds current characters data
    /*!
        \sa characters()
    */
    QString str;
};

#endif // CONFIGHANDLER_H
