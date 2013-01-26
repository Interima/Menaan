#ifndef JOBSTATES_H
#define JOBSTATES_H

/*!
    @file jobstates.h
    Contains JobStates class description.
    includes files: QObject.h, QMetaType.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QObject>
#include <QMetaType>

//! JobStates is wrapper for JobState enum
/*!
    This is class using as enum of job's states. Every job has one of these states.
    Used to interact with QML. This enum available from Qml code.
    But there is some Bug from Qt. Qt can't send this type value from
    QML to C++, therefore we use static_cast.
    This enum available as Qt Meta Object System. We can use it as variant cast.
*/
class JobStates: public QObject
{
    Q_OBJECT
    Q_ENUMS(JobState)

public:
    //! JobState enum
    /*!
        The enum describes job's states
    */
    enum JobState
    {
        Stopped  = 1, /*!< value for stopped job */
        Running  = 2, /*!< value for running job */
        Finished = 3, /*!< value for finished job */
        Error    = 4, /*!< value for job with some error */
        Frozen   = 5  /*!< value for frozen job */
    };
};

Q_DECLARE_METATYPE(JobStates::JobState)

#endif // JOBSTATES_H
