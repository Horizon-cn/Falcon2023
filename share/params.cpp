#include "params.h"

namespace Falcon {
    ParamManager::ParamManager() :settings(nullptr) {
        filename = "../data/config.ini";
    }
    ParamManager::ParamManager(const QString& name) : settings(nullptr) {
        filename = name;
    }
    ParamManager::~ParamManager() {
        if (settings)
            delete settings;
    }
    void ParamManager::setFileName() {
        settings = new QSettings(QApplication::applicationDirPath() + "/" + filename, QSettings::IniFormat);
    }
    int ParamManager::setFileName(QString appPath) {
        settings = new QSettings(appPath + "/" + filename, QSettings::IniFormat);
        return 0;
    }
    bool ParamManager::loadParam(QChar& value, const QString& key, QChar defaultValue) {
        value = settings->value(key, defaultValue).toChar();
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(int& value, const QString& key, int defaultValue) {
        //value = settings->value(key, defaultValue).toInt();
        value = (int)settings->value(key, defaultValue).toDouble(); // 避免类型错误直接为0
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(double& value, const QString& key, double defaultValue) {
        value = settings->value(key, defaultValue).toDouble();
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(QString& value, const QString& key, QString defaultValue) {
        value = settings->value(key, defaultValue).toString();
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(std::string& value, const QString& key, QString defaultValue) {
        value = settings->value(key, defaultValue).toString().toStdString();
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(bool& value, const QString& key, bool defaultValue) {
        value = settings->value(key, defaultValue).toBool();
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::loadParam(double* value, const QString& key1, const QString& key2, double* defaultValue, const int size) {
        settings->beginReadArray(key1);
        for (int i = 0; i < size; ++i) {
            settings->setArrayIndex(i);
            *(value + i) = settings->value(key2, *(defaultValue + i)).toDouble();
        }
        settings->endArray();
        if (!settings->contains(key1 + key2)) {
            settings->beginWriteArray(key1);
            for (int i = 0; i < size; ++i) {
                settings->setArrayIndex(i);
                settings->setValue(key2, *(defaultValue + i));
            }
            settings->endArray();
            settings->sync();
            return false;
        }
        return true;
    }
    bool ParamManager::changeParam(const QString& key, const QVariant& value) {
        settings->setValue(key, value);
        settings->sync();
        return true;
    }
    bool ParamManager::changeParam(const QString& group, const QString& key, const QVariant& value) {
        settings->beginGroup(group);
        settings->setValue(key, value);
        settings->endGroup();
        settings->sync();
        return true;
    }
    QStringList ParamManager::allKeys() {
        return settings->allKeys();
    }
    QStringList ParamManager::allKeys(const QString& group) {
        settings->beginGroup(group);
        auto&& res = settings->allKeys();
        settings->endGroup();
        return res;
    }
    QStringList ParamManager::allGroups() {
        return settings->childGroups();
    }
    QVariant ParamManager::value(const QString& key, const QVariant& defaultValue) {
        if (!settings->contains(key)) {
            settings->setValue(key, defaultValue);
        }
        return settings->value(key, defaultValue);
    }
    QVariant ParamManager::value(const QString& group, const QString& key, const QVariant& defaultValue) {
        if (!settings->contains(group + '/' + key)) {
            settings->setValue(group + '/' + key, defaultValue);
        }
        return settings->value(group + '/' + key, defaultValue);
    }

    void ParamManager::sync() {
        settings->sync();
    }
    void ParamManager::clear() {
        settings->clear();
        settings->sync();
    }
}
