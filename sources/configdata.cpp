#include "configdata.h"
#include <QFile>
#include <QTextStream>

/******************     Constructors     ****************/

ConfigData::ConfigData()
{

}

ConfigData::ConfigData(int l, int mt, int afd, int e, int r)
    : language(l),multiThread(mt),autoFinishedDelete(afd),
      ext(e),rewrite(r)
{
    this->languageStr = lanIntToStr(l);
}

/******************     Property Readers     ****************/

QString ConfigData::getLanguageStr()
{
    return this->languageStr;
}

int ConfigData::getLanguage()
{
    return this->language;
}

int ConfigData::getMultiThread()
{
    return this->multiThread;
}

int ConfigData::getAutoFinishedDelete()
{
    return this->autoFinishedDelete;
}


int ConfigData::getExt()
{
    return this->ext;
}

int ConfigData::getRewrite()
{
    return this->rewrite;
}

/******************     Property Setters     ****************/

void ConfigData::setLanguage(int val)
{
    this->languageStr = lanIntToStr(val);
    this->language = val;
}

void ConfigData::setMultiThread(int val)
{
    this->multiThread = val;
}

void ConfigData::setAutoFinishedDelete(int val)
{
    this->autoFinishedDelete = val;
}

void ConfigData::setExt(int val)
{
    this->ext = val;
}

void ConfigData::setRewrite(int val)
{
    this->rewrite = val;
}

/******************     Other     ****************/

QString ConfigData::lanIntToStr(int val)
{
    // there are without tr
    switch (val)
    {
        case English: return QString("English");
        case Russian: return QString("Russian");
        case Germany: return QString("Germany");
        case French: return QString("French");

        default: return QString("English");
    }

    return QString("");
}

void ConfigData::saveTo(QString name)
{
    QFile file(name);
    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
    stream << "<config>\n";
    stream << "\t<language>"+QString::number(getLanguage())+"</language>\n";
    stream << "\t<multiThread>"+QString::number(getMultiThread())+"</multiThread>\n";
    stream << "\t<autoFinishedDelete>"+QString::number(getAutoFinishedDelete())+"</autoFinishedDelete>\n";
    stream << "\t<ext>"+QString::number(getExt())+"</ext>\n";
    stream << "\t<rewrite>"+QString::number(getRewrite())+"</rewrite>\n";
    stream << "</config>";
}
