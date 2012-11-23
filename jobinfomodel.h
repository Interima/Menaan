#ifndef JOBINFOMODEL_H
#define JOBINFOMODEL_H

/*!
    @file jobinfomodel.h
    Contains JobInfoModel class description.
    includes files: QAbstractListModel.h QList.h, jobinfo.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QAbstractListModel>
#include <QList>
#include "jobinfo.h"

//! JobInfoModel class describes job's model
/*!
    This is class using as model for job's
*/
class JobInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:

    //! JobRoles enum
    /*!
        The enum describes model data roles
    */
    enum JobRoles
    {
        TicketRole = Qt::UserRole+1, /*!< value for ticket role */
        SourceRole,                  /*!< value for source role */
        DestinationRole,             /*!< value for destination role */
        AlgorithmRole,               /*!< value for algorithm role */
        StateRole,                   /*!< value for state role */
        ProgressRole,                /*!< value for progress role */
        PriorityRole                 /*!< value for priority role */
    };

    //! Constructor for JobInfoModel class
    /*!
        \param dt - non null pointer to model data
        \param parent - parent object
    */
    explicit JobInfoModel(QList<JobInfo> *dt, QObject* parent=0);

    //! Overrides QAbstractListModel::rowCount function
    int rowCount(const QModelIndex &parent) const;

    //! Overrides QAbstractListModel::data function
    QVariant data(const QModelIndex &index, int role) const;

    //! Overrides QAbstractListModel::setData function
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    //! Insert new job to model data
    /*!
        \param job - JobInfo object
        \sa removeJob(), _data
    */
    void insertJob(const JobInfo &job);

    //! Remove job with jobIndex from model data
    /*!
        \param val - ticket
        \sa insertJob(), _data
    */
    void removeJob(const int jobIndex);

    //! Returns index of job by it's ticket
    /*!
        \param ticket - tiket of job
    */
    QModelIndex ticketToIndex(quint32 ticket);

private:

    //! This property holds pointer to model data
    QList<JobInfo> *_data;
};

#endif // JOBINFOMODEL_H
