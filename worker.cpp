#include "worker.h"
#include <QDataStream>
#include <QDebug>

Worker::Worker(QObject *parent) :
    QThread(parent)
{

}

Worker::~Worker()
{
    delete this->plugin;
}

void Worker::init(quint32 t, QString i, QString o, QString k, QString s,
                 PluginInterface *pi, JobTypes::JobType tp)
{
    qDebug()<<"[Worker say:] Init worker start";

    // set files
    inputFile.setFileName(i);
    outputFile.setFileName(o);

    // set algorithm data
    this->key = k;
    this->special = s;

    this->plugin = pi;

    // set worker type
    this->type = tp;

    // set worker index
    this->ticket = t;

    // unset stop flag
    stopFlag = false;

    qDebug()<<"[Worker say:] Init worker end. ["<<ticket<<"]";
}

void Worker::stop()
{
    qDebug()<<"[Worker say:] Worker was stopped. ["<< ticket<<"]";
    stopFlag = true;

    // if not yet started
    if(!this->isRunning()) cleaner();

}

void Worker::run()
{
    qDebug()<<"[Worker say:] Worker run. ["<<ticket<<"]";

    // try to open files
    if (!this->inputFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"[Worker say:] Catastrophic error! Input file opening error"
                <<inputFile.fileName();
        emit error(ticket,Worker::InputFileOpenError);
        return;
    }

    if (!this->outputFile.open(QIODevice::WriteOnly))
    {
        qDebug()<<"[Worker say:] Catastrophic error! Output file opening error"
                <<outputFile.fileName();
        emit error(ticket,Worker::OutputFileOpenError);
        return;
    }

    qDebug()<<"[Worker say:] I/O files was opened";

    emit stateChanged(ticket,JobStates::Running);

    switch (type)
    {
        case JobTypes::ECB_ENC:
        case JobTypes::CBC_ENC: encrypt(); break;
        case JobTypes::ECB_DEC:
        case JobTypes::CBC_DEC: decrypt(); break;

        default: break;
    }

    qDebug()<<"[Worker say:] Worker become idle. ["<<ticket<<"]";

    // event loop
    exec();

    qDebug()<<"[Worker say:] Worker end. ["<<ticket<<"]";
}

void Worker::cleaner()
{
    qDebug()<<"[Worker say:] Worker cleaner start. ["<<ticket<<"]";

    // close files
    if (inputFile.isOpen()) inputFile.close();
    if (outputFile.isOpen()) outputFile.close();

    // remove output file
    outputFile.remove();

    qDebug()<<"[Worker say:] Worker cleaner end. ["<<ticket<<"]";
}

void Worker::encrypt()
{

    qDebug()<<"[Worker say:] Worker encrypt. ["<<ticket<<"]";

    QDataStream in,out;
    quint32 bufferLength, bytesRead, bytesWrite;
    quint64 dataSize;
    quint64 counter;
    quint32 blockSize;
    quint32 extraBytes;
    quint32 progressPercent;
    quint8  progress;

    char * inBuffer;
    char * outBuffer;

    // init plugin
    if (!plugin->init(this->type,this->key,this->special))
    {
        // if init failed
        emit error(this->ticket,Worker::PluginInitError);

        qDebug()<<"[Worker say:] Catastrophic error! Plugin init failed";
        return;
    }

    qDebug()<<"[Worker say:] Worker create streams. ["<<ticket<<"]";

    // init streams
    in.setDevice(&inputFile);
    out.setDevice(&outputFile);

    // get algorithm block size
    blockSize = plugin->blockLength();

    // calc size of input buffer in bytes
    bufferLength = blockSize/8;

    // calc extra bytes count
    // write extra bytes to file
    extraBytes = inputFile.size() % bufferLength;

    if (extraBytes) out<<Worker::MAGIC<<static_cast<quint32> (bufferLength-extraBytes);
    else out<<Worker::MAGIC<<static_cast<quint32> (0);

    // input file size without extra bytes in blocks
    dataSize = static_cast<quint64> (inputFile.size()/bufferLength);

    // calc progressProcent
    progressPercent = dataSize/100;

    // set progress to 0
    progress = 0;

    // alloc size for buffers
    inBuffer = new char [bufferLength];
    outBuffer = new char [bufferLength];

    counter = 0;

    qDebug()<<"[Worker say:] Worker start encrypt cycle. ["<<ticket<<"]";

    // start encrypt cycle
    while ((!stopFlag) && (dataSize>counter))
    {

        // read data to input buffer
        bytesRead = in.readRawData(inBuffer,bufferLength);

        // if read incomplete
        if (bytesRead!=bufferLength)
        {

            // try to read
            if (!tryToRead(bytesRead,bufferLength,inBuffer,&in))
            {
                // if can't read then clean and exit
                cleaner();
                emit error(this->ticket,Worker::InputFileReadError);
                return;
            }
        }

        plugin->encode(inBuffer,outBuffer);

        if (!progressPercent==0)
        if ((progress+5)<(counter/progressPercent))
        {
            progress = counter/progressPercent;
            emit progressChange(this->ticket, progress);
        }

        // write data from output buffer
        bytesWrite = out.writeRawData(outBuffer,bufferLength);

        // if write incomplete
        if (bytesWrite!=bufferLength)
        {

            // try to write
            if (!tryToWrite(bytesWrite,bufferLength,outBuffer,&out))
            {
                // if can't write then clean and exit
                cleaner();
                emit error(this->ticket,Worker::OutputFileWriteError);
                return;
            }
        }

        counter++;
    }

    // exit from here if stop flag raised
    if (stopFlag)
    {
        delete[] inBuffer;
        delete[] outBuffer;

        cleaner();
        return;
    }


    // extra bytes encrypt
    if (extraBytes)
    {

        qDebug()<<"[Worker say:] Worker start encrypt extra bytes. ["<<ticket<<"]";
        quint8 i=0;

        // clear buffer
        while (i<bufferLength) { inBuffer[i]=0; i++; }

        // read last bytes
        in.readRawData(inBuffer,bufferLength);

        plugin->encode(inBuffer,outBuffer);

        // write data from output buffer
        bytesWrite = out.writeRawData(outBuffer,bufferLength);

        // if write incomplete
        if (bytesWrite!=bufferLength)
        {
            // try to write
            if (!tryToWrite(bytesWrite,bufferLength,outBuffer,&out))
            {
                // if can't write then clean and exit
                cleaner();
                emit error(this->ticket,Worker::OutputFileWriteError);
                return;
            }
        }
    }

    // emit progress done
    emit progressChange(this->ticket, 100);

    outputFile.flush();

    inputFile.close();
    outputFile.close();

    delete[] inBuffer;
    delete[] outBuffer;

    emit stateChanged(this->ticket, JobStates::Finished);

    qDebug()<<"[Worker say:] End worker encrypt. ["<<ticket<<"]";
}

void Worker::decrypt()
{

    qDebug()<<"[Worker say:] Start worker decrypt. ["<<ticket<<"]";

    QDataStream in,out;
    quint32 bufferLength, bytesRead, bytesWrite;
    quint64 dataSize;
    quint64 counter;
    quint32 blockSize;
    quint32 extraBytes;
    quint32 magic;
    quint32 progressPercent;
    quint8  progress;

    char * inBuffer;
    char * outBuffer;

    // init plugin
    if (!plugin->init(this->type,this->key,this->special))
    {
        // if init failed
        emit error(this->ticket,Worker::PluginInitError);

        qDebug()<<"[Worker say:] Catastrophic error! Plugin init failed";
        return;
    }

    qDebug()<<"[Worker say:] Worker create streams. ["<<ticket<<"]";

    // init streams
    in.setDevice(&inputFile);
    out.setDevice(&outputFile);

    // get algorithm block size
    blockSize = plugin->blockLength();

    // calc size of input buffer in bytes
    bufferLength = blockSize/8;


    // read extra bytes
    in>>magic>>extraBytes;

    if (magic!=Worker::MAGIC)
    {
        qDebug()<<"[Worker say:] Catastrophic error! Magic is not valid. ["<<ticket<<"]";
        cleaner();
        emit error(this->ticket,Worker::MagicNumberError);
        return;
    }

    qDebug()<<"[Worker say:] Magic is valid. ["<<ticket<<"]";
    // input file size without extra bytes in blocks
    dataSize=static_cast<quint64> (inputFile.size()-2*sizeof(quint32)-
                                   static_cast<bool>(extraBytes))/bufferLength;

    // calc progressProcent
    progressPercent = dataSize/100;

    // set progress to 0
    progress = 0;

    // alloc size for buffers
    inBuffer = new char [bufferLength];
    outBuffer = new char [bufferLength];

    qDebug()<<"[Worker say:] Worker start encrypt cycle. ["<<ticket<<"]";

    counter = 0;

    while ((!stopFlag) && (dataSize>counter))
    {
        // read data from input buffer
        bytesRead = in.readRawData(inBuffer,bufferLength);

        //qDebug()<<"[Worker say:] ------Read bytes count: "<<bytesRead;

        // if read incomplete
        if (bytesRead!=bufferLength)
        {
            // try to read
            if (!tryToRead(bytesRead,bufferLength,inBuffer,&in))
            {
                // if can't read then clean and exit
                cleaner();
                emit error(this->ticket,Worker::InputFileReadError);
                return;
            }
        }

        plugin->decode(inBuffer,outBuffer);
        //qDebug()<<"[Worker say:] ------Decode end";


        if (!progressPercent==0)
        // emit progress change every 5%
        if ((progress+5)<(counter/progressPercent))
        {
            progress = counter/progressPercent;
            emit progressChange(this->ticket, progress);
        }

        //qDebug()<<"[Worker say:] ------Progress end";

        // write data to output buffer
        bytesWrite = out.writeRawData(outBuffer,bufferLength);

        // if write incomplete
        if (bytesWrite!=bufferLength)
        {
            // try to write
            if (!tryToWrite(bytesWrite,bufferLength,outBuffer,&out))
            {
                // if can't write then clean and exit
                cleaner();
                emit error(this->ticket,Worker::OutputFileWriteError);
                return;
            }
        }

        counter++;
    }

    // exit from here
    if (stopFlag)
    {
        cleaner();
        return;
    }

    // extra bytes encrypt
    if (extraBytes)
    {
        // read last block
        bytesRead = in.readRawData(inBuffer,bufferLength);

        plugin->decode(inBuffer,outBuffer);

        // write data from output buffer
        // without extra bytes
        bytesWrite = out.writeRawData(outBuffer,bufferLength - extraBytes);

        // if write incomplete
        if (bytesWrite!=(bufferLength-extraBytes))
        {
            // try to write
            if (!tryToWrite(bytesWrite,bufferLength,outBuffer,&out))
            {
                // if can't write then clean and exit
                cleaner();
                emit error(this->ticket,Worker::OutputFileWriteError);
                return;
            }
        }
    }

    // emit progress done
    emit progressChange(this->ticket, 100);

    // i/o scheduler flush data
    outputFile.flush();

    inputFile.close();
    outputFile.close();

    delete[] inBuffer;
    delete[] outBuffer;

    // emit finish job
    emit stateChanged(this->ticket, JobStates::Finished);

    qDebug()<<"[Worker say:] End worker decrypt. ["<<ticket<<"]";
}

bool Worker::tryToRead(quint32 br, quint32 bl, char *buf, QDataStream *ds)
{

    qDebug()<<"[Worker say:] Warning! Worker start tryToRead. ["<<ticket<<"]";
    // count of attempts
    quint8 i=bl+1;

    // attempt
    /*while ((i) || (br!=bl))
    {
        //br+=ds->readRawData( &(buf[br]), bl-br );
        i--;
    }

    if (i==0) return false; else return true;
    */
    return false;
}

bool Worker::tryToWrite(quint32 bw, quint32 bl, char *buf, QDataStream *ds)
{
    qDebug()<<"[Worker say:] Warning! Worker start tryToWrite. ["<<ticket<<"]";
    // count of attempts
    quint8 i=bl+1;

    // attempt
    /*while ((i) || (bw!=bl))
    {
        //bw+=ds->writeRawData( &(buf[bw]), bl-bw );
        i--;
    }
    if (i==0) return false; else return true;
    */
    return false;
}

bool Worker::isTicket(quint32 t) const
{
    return (this->ticket == t);
}
