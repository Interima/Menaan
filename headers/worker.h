#ifndef WORKER_H
#define WORKER_H

/*!
    @file worker.h
    Contain JobInfo class description.
    include files: QString.h, QFile.h, jobstates.h, jobtypes.h,
    QThread, plugininfo.h, plugininterface.h

    @author Interima.ix2
    @author Interima.Inmay
*/

#include <QThread>
#include <QFile>
#include "plugininfo.h"
#include "plugininterface.h"
#include "jobstates.h"
#include "jobtypes.h"

#define BYTE_SIZE 8

#define FILE_SIZE_SMALL     1000
#define FILE_SIZE_MEDIUM    10000
#define FILE_SIZE_LARGE     100000
#define FILE_SIZE_EXTRA     1000000


//! Worker class is Qthread based class for perform job
/*!
    Perform jobs, starts plugin encode/decode function
*/
class Worker : public QThread
{
    Q_OBJECT
    Q_ENUMS(WorkerErrors)

public:

    enum WorkerErrors
    {
        InputFileOpenError = 1,
        OutputFileOpenError,
        InputFileReadError,
        OutputFileWriteError,
        PluginInitError,
        MagicNumberError
    };

    static const quint32 MAGIC = 0xBBADBEEF; //?? WebKit detected :)

    //! Constructor for Worker class
    /*!
        Default constructor
    */
    explicit Worker(QObject *parent = 0);

    //! Destructor for Worker class
    /*!
        Destructor.
        Explicit calling. Delete all heap allocated memory.
    */
    ~Worker();

    //! Initialize worker
    /*!
        \param t - ticket of job
        \param i - path to input file
        \param o - path to output data
        \param k - key
        \param s-  special parameters
        \param pi - plugin instance
        \param tp - type of job
    */
    void init(quint32 t, QString i, QString o, QString k,
             QString s, PluginInterface *pi, JobTypes::JobType tp);

    //! Run function. Override QThread::run
    /*!
        Run thread.
    */
    void run();

    //! Check is worker perform job with _ticket
    /*!
        \param ticket - job's ticket for cheking
    */
    bool isTicket(quint32 _ticket) const;
    
private:

    //! Store stop flag
    /*!
        Flag cheked by worker. If set to true, worker go to idle
        \sa stop(), cleaner()
    */
    bool stopFlag;

    //! Store input file
    /*!
        File with input data for plugin
        \sa init()
    */
    QFile inputFile;

    //! Store output file
    /*!
        File with output data for plugin
        \sa init()
    */
    QFile outputFile;

    //! Store key
    /*!
        User key for plugin
        \sa init()
    */
    QString key;

    //! Store special parameters
    /*!
        Special parameters for plugin
        \sa init()
    */
    QString special;

    //! Pointer to plugin instance
    /*!
        \sa init()
    */
    PluginInterface* plugin;

    //! Store type of job
    /*!
        \sa init()
    */
    JobTypes::JobType type;

    //! Store job ticket
    /*!
        Unique job ticket. Used to link worker with job.
        \sa init(), isTicket()
    */
    quint32 ticket;

    //! Decrypt function
    /*!
        Init plugin, read data from file,
        decrypt it by plugin decrypt function,
        write data to output

        \sa encrypt()
    */
    void decrypt();

    //! Encrypt function
    /*!
        Init plugin, read data from file,
        decrypt it by plugin encrypt function,
        write data to output
        \sa decrypt()
    */
    void encrypt();

    //! Clean function
    /*!
        Clean all temporary files
        created by worker when stop signal arrived
        \sa stopFlag, stop()
    */
    void cleaner();

    //! Emergency reader
    /*!
        Try to read data (if error occured).
        After some tries emit error.

        \param br - number of already readed bytes
        \param bl - buffer length
        \param buf -  buffer for data
        \param ds - data stream
        \sa tryToWrite()
    */
    bool tryToRead(quint32 br, quint32 bl, char * buf, QDataStream * ds);

    //! Emergency writer
    /*!
        Try to write data (if error occured).
        After some tries emit error.

        \param br - number of already written bytes
        \param bl - buffer length
        \param buf -  buffer for data
        \param ds - data stream
        \sa tryToRead()
    */
    bool tryToWrite(quint32 bw, quint32 bl, char * buf, QDataStream * ds);

signals:
    //! State change signal
    /*!
        Emit when state of job was changed
        \param ticket - job's ticket
        \param state - new job state
    */
    void stateChanged(quint32 ticket, JobStates::JobState state);

    //! Error signal
    /*!
        Emit when some error has been occured.
        \param ticket - job's ticket
        \param err - error type
    */
    void error(quint32 ticket, Worker::WorkerErrors err);

    //! Progress signal
    /*!
        Emit when progress was changed
        \param ticket - job's ticket
        \param progress - new progress
    */
    void progressChange(quint32 ticket, quint8 progress);
    
public slots:

    //! Stop slot
    /*!
        Slot used to catch stop command.
        \sa stopFlag, cleaner()
    */
    void stop();
};

Q_DECLARE_METATYPE(Worker::WorkerErrors)

#endif // WORKER_H
