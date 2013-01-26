#ifndef JOBTYPE_H
#define JOBTYPE_H

/*!
    @file jobtypes.h
    Contains JobTypes class description.
    includes files: QObject.h, QMetaType.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QObject>
#include <QMetaType>

//! JobTypes class is wrapper for JobType enum
/*!
    This is class using as enum of job's types. Every job has one of these types.
    One job can has several types. So job use several flags by OR combination.
    Used to interact with QML. This enum available from Qml code.
    But there is some Bug from Qt. Qt can't send this type value from
    QML to C++, therefore we use static_cast.
    This enum available as Qt Meta Object System. We can use it as variant cast.
*/
class JobTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(JobType)

public:

    //! JobType enum
    /*!
        The enum describes job's types
    */
    enum JobType
    {
        ECB_ENC = 0x01, /*!< value for ECB encoder job */
        CBC_ENC = 0x02, /*!< value for CBC encoder job */
        ECB_DEC = 0x04, /*!< value for ECB decoder job */
        CBC_DEC = 0x08  /*!< value for CBC decoder job */
    };
};

Q_DECLARE_METATYPE(JobTypes::JobType)

#endif // JOBTYPE_H
