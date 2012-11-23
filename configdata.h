#ifndef CONFIGDATA_H
#define CONFIGDATA_H

/*!
    @file configdata.h
    Contains ConfigData class description.
    includes files: QString.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QString>

//! ConfigData class contain all config data for application and can save it to file
/*!
    All application settings reading in ConfigData class by xml parser.
    This class provide function to save all data to xml file.
*/
class ConfigData
{


public:

    //! Languages enum
    /*!
        Contain all avaible language translations.
        If you have new translation add it here.
    */
    enum Languages
    {
        English,    /*!< value for english translation */
        Russian,    /*!< value for russian translation */
        Germany,    /*!< value for germany translation */
        French      /*!< value for french translation */
    };

    //! Default constructor for ConfidData class
    explicit ConfigData();

    //! Constructor for ConfigData class
    /*!
        \param l   - language id (can be any value from enum Languages)
        \param mt  - multi thread state (can be 0 - disabled, 1 - enabled)
        \param afd - finished jobs auto delete (can be 0 - disabled, 1 - enabled)
        \param e   - extension using state (can be 0 - disabled, 1 - enabled)
        \param r   - files rewrite state (can be 0 - disabled, 1 - enabled)
    */
    explicit ConfigData(int l,int mt, int af, int e, int r);

    //! Returns language in string form
    /*! \sa setLanguage(), lanIntToStr(), languageStr*/
    QString getLanguageStr();

    //! Returns language id in int form
    /*! \sa setLanguage(), language */
    int getLanguage();

    //! Returns multiThread variable value
    /*! \sa setMultiThread(), multiThread*/
    int getMultiThread();

    //! Returns autoFinishedDeleted variable value
    /*! \sa setAutoFinishedDelete(), autoFinishedDelete*/
    int getAutoFinishedDelete();

    //! Returns ext variable value
    /*! \sa setExt(), ext*/
    int getExt();

    //! Returns rewrite variable value
    /*! \sa setRewrite(), rewrite*/
    int getRewrite();

    //! Sets language and languageStr variables value
    /*! \param val - language id (can be any value from enum Languages)
        \sa getLanguageStr(), lanIntToStr()
    */
    void setLanguage(int val);

    //! Sets multiThread variable value
    /*! \param val - multi thread state (can be 0 - disabled, 1 - enabled)
        \sa getLanguage(), language, languageStr
    */
    void setMultiThread(int val);

    //! Sets autoFinishedDelete variable value
    /*! \param val - auto finished jobs delete state (can be 0 - disabled, 1 - enabled)
        \sa getAutoFinishedDelete(), autoFinishedDelete
    */
    void setAutoFinishedDelete(int val);

    //! Sets ext variable value
    /*! \param val - extension using state (can be 0 - disabled, 1 - enabled)
        \sa getExt(), ext
    */
    void setExt(int val);

    //! Sets rewrite variable value
    /*! \param val - files rewrite state (can be 0 - disabled, 1 - enabled)
        \sa getRewrite(), rewrite
    */
    void setRewrite(int val);

    //! Saves all data from ConfigData to xml file
    /*! \param name - target xml file name*/
    void saveTo(QString name);

private:

    //! This property holds translation language in string form
    /*!
        \sa getLanguageStr(), setLanguage(), lanIntToStr()
    */
    QString languageStr;

    //! This property holds translation language id in int form
    /*! Can be any value from enum Languages
        \sa getLanguage(), setLanguage()
    */
    int language;

    //! This property holds multi thread state
    /*! Can be 0 - disabled, 1 - enabled
        \sa getMultiThread(), setMultiThread()
    */
    int multiThread;

    //! This property holds finished jobs auto delete state
    /*! Can be 0 - disabled, 1 - enabled
        \sa getAutoFinishedDelete(), setAutoFinishedDelete()
    */
    int autoFinishedDelete;

    //! This property holds extension using state
    /*! Can be 0 - disabled, 1 - enabled
        \sa getExt(), setExt()
    */
    int ext;

    //! This property holds files rewrite state
    /*! Can be 0 - disabled, 1 - enabled
        \sa getRewrite(), setRewrite()
    */
    int rewrite;

    //! Converts language id to string form
    /*! \param val - language id (can be any value from enum Languages)
        If can't find val in enum Languages then return default language (English)
    */
    QString lanIntToStr(int val);
};

#endif // CONFIGDATA_H
