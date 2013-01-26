#ifndef PLUGININFO_H
#define PLUGININFO_H

/**
    @file configdata.h
    Contain PluginInfo class description.
    include files: QString.h, QObject.h, pluginInterface.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QString>
#include <QObject>
#include "plugininterface.h"

//! PluginInfo class contain all plugin info and pointer to it
/*!
    All information about plugin reading into PluginInfo class.
    This class also store pointer to plugin.
*/
class PluginInfo
{
public:
    //! Constructor for PluginInfo class
    /*!
        \param val - pointer to plugin
    */
    PluginInfo(QObject* val);

    //! Set name variable value
    /*! \param val - name
        \sa getName(), name
    */
    void setName(const QString val);

    //! Set author variable value
    /*! \param val - author
        \sa getAuthor(), author
    */
    void setAuthor(const QString val);

    //! Set keyLength variable value
    /*! \param val - length of key
        \sa getKeyLength(), keyLength
    */
    void setKeyLength(const int val);

    //! Set blockLength variable value
    /*! \param val - length of block
        \sa getBlockLength(), blockLength
    */
    void setBlockLength(const int val);

    //! Set safetyLevel variable value
    /*! \param val - level of safety (min.value - 1, max.value - 9)
        \sa getSafetyLevel(), safetyLevel
    */
    void setSafetyLevel(const int val);

    //! Set speedLevel variable value
    /*! \param val - level of speed (min.value - 1, max.value - 9)
        \sa getSpeedLevel(), speedLevel
    */
    void setSpeedLevel(const int val);

    //! Set plugin variable value
    /*! \param val - pointer to plugin
        \sa getPlugin(), plugin
    */
    void setPlugin(QObject* val);

    //! Return name variable value
    /*! \sa setName(), name */
    QString getName() const;

    //! Return author variable value
    /*! \sa setAuthor(), author */
    QString getAuthor() const;

    //! Return keyLength variable value
    /*! \sa setKeyLength(), keyLength */
    int getKeyLength() const;

    //! Return blockLength variable value
    /*! \sa setBlockLength(), blockLength */
    int getBlockLength() const;

    //! Return safetyLevel variable value
    /*! \sa setSafetyLevel(), safetyLevel */
    int getSafetyLevel() const;

    //! Return speedLevel variable value
    /*! \sa setSpeedLevel(), speedLevel */
    int getSpeedLevel() const;

    //! Return pointer to plugin
    /*! \sa setPlugin(), plugin */
    PluginInterface * getPlugin();


private:

    //! Store name of plugin's algorithm
    /*!
        \sa getName(), setName()
    */
    QString name;

    //! Store author of plugin's algorithm
    /*!
        \sa getLanguage(), setLanguage()
    */
    QString author;

    //! Store length of key plugin's algorithm
    /*!
        \sa getKeyLength(), setKeyLength()
    */
    int keyLength;

    //! Store length of block plugin's algorithm
    /*!
        \sa getBlockLength(), setBlockLength()
    */
    int blockLength;

    //! Store level of safety plugin's algorithm
    /*! minimum value - 1, maximum value - 9
        \sa getSafetyLevel(), setSafetyLevel();
    */
    int safetyLevel;

    //! Store level of speedLevel plugin's algorithm
    /*! minimal value - 1, maximum value - 9
        \sa getSpeedLevel(), setSpeedLevel()
    */
    int speedLevel;

    //! Store pointer to plugin
    /*!
        \sa getPlugin(), setPlugin()
    */
    PluginInterface * plugin;

};

#endif // PLUGININFO_H
