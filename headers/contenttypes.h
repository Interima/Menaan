#ifndef CONTENTTYPES_H
#define CONTENTTYPES_H

/*!
    @file ContentTypes.h
    Contains ContentTypes class description.
    includes files: QObject.h, QMetaType.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QObject>
#include <QMetaType>

//! ContentTypes is wrapper for ContentType enum
/*!
    This is class using as enum of job's states. Every job has one of these states.
    Used to interact with QML. This enum available from Qml code.
    But there is a Bug from Qt. Qt can't send this type value from
    QML to C++, therefore we use static_cast.
    This enum available as Qt Meta Object System. We can use it as variant cast.
*/
class ContentTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(ContentType)

public:
    //! ContentType enum
    /*!
        The enum describes content's type
    */
    enum ContentType
    {
        Dir     = 1, /*!< value for dir */
        File    = 2, /*!< value for file */
        Symlink = 3, /*!< value for symlink */
        Unknown = 4  /*!< value for unknown types*/
    };
};

Q_DECLARE_METATYPE(ContentTypes::ContentType)

#endif
