#ifndef ACTIVEWORKERINFO_H
#define ACTIVEWORKERINFO_H

/*!
    @file activeworkerinfo.h
    Contains ActiveWorkerInfo class description.
    includes files: QString.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QString>

//! ActiveWorkerInfo class contains all config data for application and can save it to file
/*!
    This class used for saving some info about active jobs.
    Contains method to check conflict situation between two jobs.
*/

class ActiveWorkerInfo
{
public:

    //! Default constructor for ActiveWorkerInfo class
    explicit ActiveWorkerInfo();

    //! Constructor for ActiveWorkerInfo class
    /*!
        \param tckt - ticket of job
        \param src  - data source of job
        \param dst  - data destination of job
    */
    ActiveWorkerInfo(quint16 tckt, QString src, QString dst);

    //! Returns true if val have conflict with current object;
    //! otherwise returns false
    /*!
        \param val - ActiveWorkerInfo object for compare
    */
    bool isConflict(const ActiveWorkerInfo& val) const;

    //! Returns ticket of job
    /*!
        \sa setTicket(), ticket
    */
    quint16 getTicket() const;

    //! Returns data source of job
    /*!
        \sa setSource(), source
    */
    QString getSource() const;

    //! Returns data destination of job
    /*!
        \sa setDestination(), destination
    */
    QString getDestination() const;

    //! Sets ticket of job
    /*!
        \param tckt - ticket of job
        \sa getTicket(), ticket
    */
    void setTicket(const quint16 tckt);

    //! Sets ticket of job
    /*!
        \param src - data source of job
        \sa getSource(), source
    */
    void setSource(const QString src);

    //! Sets ticket of job
    /*!
        \param dst - data source of job
        \sa getDestination(), destination
    */
    void setDestination(const QString dst);

private:

    //! This property holds job's ticket
    /*!
        \sa getTicket(), setTicket()
    */
    quint16 ticket;

    //! This property holds job's source data
    /*!
        \sa getSource(), setSource()
    */
    QString source;

    //! This property holds job's destination data
    /*!
        \sa getDestination(), setDestination()
    */
    QString destination;
};

#endif // ACTIVEWORKERINFO_H
