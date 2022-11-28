#include "ParamManagerNew.h"

CParamManagerNew::CParamManagerNew():settings(nullptr){
    settings = new QSettings("./config.ini",QSettings::IniFormat);
}
CParamManagerNew::CParamManagerNew(const QString& name):settings(nullptr){
    settings = new QSettings(name,QSettings::IniFormat);
}
CParamManagerNew::~CParamManagerNew(){
    if(settings)
        delete settings;
}
bool CParamManagerNew::loadParam(QChar& value, const QString& key, QChar defaultValue){
    value = settings->value(key, defaultValue).toChar();
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
        settings->sync();
        return false;
    }
    return true;
}
bool CParamManagerNew::loadParam(int& value, const QString& key, int defaultValue){
    value = settings->value(key, defaultValue).toInt();
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
        settings->sync();
        return false;
    }
    return true;
}
bool CParamManagerNew::loadParam(double& value, const QString& key, double defaultValue){
    value = settings->value(key, defaultValue).toDouble();
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
        settings->sync();
        return false;
    }
    return true;
}
bool CParamManagerNew::loadParam(QString& value, const QString& key , QString defaultValue){
    value = settings->value(key, defaultValue).toString();
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
        settings->sync();
        return false;
    }
    return true;
}
bool CParamManagerNew::loadParam(bool& value, const QString& key, bool defaultValue){
    value = settings->value(key, defaultValue).toBool();
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
        settings->sync();
        return false;
    }
    return true;
}
bool CParamManagerNew::changeParam(const QString & key, const QVariant & value){
    settings->setValue(key,value);
    settings->sync();
    return true;
}
bool CParamManagerNew::changeParam(const QString & group,const QString & key,const QVariant & value){
    settings->beginGroup(group);
    settings->setValue(key,value);
    settings->endGroup();
    settings->sync();
    return true;
}
QStringList CParamManagerNew::allKeys(){
    return settings->allKeys();
}
QStringList CParamManagerNew::allKeys(const QString& group){
    settings->beginGroup(group);
    auto&& res = settings->allKeys();
    settings->endGroup();
    return res;
}
QStringList CParamManagerNew::allGroups(){
    return settings->childGroups();
}
QVariant CParamManagerNew::value(const QString& key,const QVariant& defaultValue){
    if (!settings->contains(key)){
        settings->setValue(key, defaultValue);
    }
    return settings->value(key,defaultValue);
}
QVariant CParamManagerNew::value(const QString& group,const QString& key,const QVariant& defaultValue){
    if (!settings->contains(group+'/'+key)){
        settings->setValue(group+'/'+key, defaultValue);
    }
    return settings->value(group+'/'+key,defaultValue);
}
void CParamManagerNew::sync(){
    settings->sync();
}
void CParamManagerNew::clear() {
    settings->clear();
    settings->sync();
}
