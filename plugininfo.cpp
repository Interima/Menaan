#include "plugininfo.h"

/******************     Constructors     ****************/

PluginInfo::PluginInfo(QObject* _val)
{
    plugin = qobject_cast<PluginInterface*>(_val);

    name = plugin->name();
    author = plugin->author();
    keyLength = plugin->keyLength();
    blockLength = plugin->blockLength();
    speedLevel = plugin->speedLevel();
    safetyLevel = plugin->safetyLevel();
}

/******************     Property Setters     ****************/

void PluginInfo::setName(const QString _val)
{
    this->name=_val;
}

void PluginInfo::setAuthor(const QString _val)
{
    this->author=_val;
}

void PluginInfo::setKeyLength(const int _val)
{
    this->keyLength=_val;
}

void PluginInfo::setBlockLength(const int _val)
{
    this->blockLength=_val;
}

void PluginInfo::setSafetyLevel(const int _val)
{
    this->safetyLevel=_val;
}

void PluginInfo::setSpeedLevel(const int _val)
{
    this->speedLevel=_val;
}

void PluginInfo::setPlugin(QObject * _val)
{
    this->plugin= qobject_cast<PluginInterface*>(_val);
}

/******************     Property Readers     ****************/

QString PluginInfo::getName() const
{
    return this->name;
}

QString PluginInfo::getAuthor() const
{
    return this->author;
}

int PluginInfo::getKeyLength() const
{
    return this->keyLength;
}

int PluginInfo::getBlockLength() const
{
    return this->blockLength;
}

int PluginInfo::getSafetyLevel() const
{
    return this->safetyLevel;
}

int PluginInfo::getSpeedLevel() const
{
    return this->speedLevel;
}

PluginInterface * PluginInfo::getPlugin()
{
    return plugin;
}
