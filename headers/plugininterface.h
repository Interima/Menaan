#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtGlobal>
#include <jobtypes.h>

class QString;

class PluginInterface
{


public:

    virtual ~PluginInterface() {}

    virtual QString name()=0;
    virtual QString author()=0;
    virtual int keyLength()=0;
    virtual int blockLength()=0;
    virtual int speedLevel()=0;
    virtual int safetyLevel()=0;
    virtual int types()=0;

    virtual void encode (char *in, char* out)=0;
    virtual void decode (char *in, char* out)=0;

    virtual bool init(JobTypes::JobType type, QString key,QString args)=0;

    virtual PluginInterface* clone()=0;

};


Q_DECLARE_INTERFACE(PluginInterface,"Interima.Menaan.PluginInterface/1.0")

#endif // PLUGININTERFACE_H
