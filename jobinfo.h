#ifndef JOBINFO_H
#define JOBINFO_H

/*!
    @file jobinfo.h
    Contains JobInfo class description.
    includes files: QString.h, jobstates.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QString>
#include "jobstates.h"

//! PluginInfo class contains all plugin info and pointer to it
/*!
    All information about job stores in PluginInfo class.
*/
class JobInfo
{
public:

    //! Constructor for JobInfo class
    /*!
        Default constructor
    */
    explicit JobInfo();

    //! Constructor for JobInfo class
    /*!
        \param t - ticket of job
        \param s - source file name of job
        \param d - destination file name of job
        \param a - algorithm name of job
        \param st- state of job
        \param p - progress of job
        \param pr - priority of job
    */
    explicit JobInfo(int t, QString s, QString d, QString a, JobStates::JobState st, int p, int pr);

    //! Returns ticket variable value
    /*!
        \sa setTicket(), ticket
    */
    quint16 getTicket() const;

    //! Returns source variable value
    /*!
        \sa setSource(), source
    */
    QString getSource() const;

    //! Returns destination variable value
    /*!
        \sa setDestination(), destination
    */
    QString getDestination() const;

    //! Returns algorithm variable value
    /*!
        \sa setAlgorithm(), algorithm
    */
    QString getAlgorithm() const;

    //! Returns state variable value
    /*!
        \sa setState(), state
    */
    JobStates::JobState getState() const;

    //! Returns progress variable value
    /*!
        \sa setProgress(), progress
    */
    int getProgress() const;

    //! Returns priority variable value
    /*!
        \sa setPriority(), priority
    */
    int getPriority() const;

    //! Sets ticket variable value
    /*! \param val - ticket
        \sa getTicket(), ticket
    */
    void setTicket(const quint16 val);

    //! Sets source variable value
    /*! \param val - source
        \sa setSource(), source
    */
    void setSource(const QString val);

    //! Sets destination variable value
    /*! \param val - destination
        \sa getDestination(), destination
    */
    void setDestination(const QString val);

    //! Sets algorithm variable value
    /*! \param val - algorithm
        \sa getAlgorithm(), algorithm
    */
    void setAlgorithm(const QString val);

    //! Sets state variable value
    /*! \param val - JobState value
        \sa getState(), state
    */
    void setState(const JobStates::JobState val);

    //! Sets progress variable value
    /*! \param val - progress
        \sa getProgress(), progress
    */
    void setProgress(const int val);

    //! Sets priority variable value
    /*! \param val - priority
        \sa getPriority(), priority
    */
    void setPriority(const int val);

private:

    //! This property holds job's ticket
    /*!
        Unique for every job
        \sa getTicket(), setTicket()
    */
    quint16 ticket;

    //! This property holds job's source file name
    /*!
        Holds full path with filename
        \sa getSource(), setSource()
    */
    QString source;

    //! This property holds job's destination file name
    /*!
        Holds full path with filename
        \sa getDestination(), setDestination()
    */
    QString destination;

    //! This property holds job's algorithm
    /*!
        Holds plugin's algorithm name for job
        \sa getAlgorithm(), setAlgorithm();
    */
    QString algorithm;

    //! This property holds job's state
    /*!
        Holds current state of job
        \sa getState, setState();
    */
    JobStates::JobState state;

    //! This property holds job's progress
    /*!
        Min.value - 0, max.value - 100
        \sa getProgress(), setProgress()
    */
    int progress;

    //! This property holds job's priority
    /*!
        Min.value -10, max.value +10
        \sa getProgress(), setProgress()
    */
    int priority;


};

#endif // JOBINFO_H
