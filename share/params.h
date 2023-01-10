#ifndef _PARAMS_H
#define _PARAMS_H

#include <QApplication>
#include <QSettings>
#include <QDebug>

namespace Falcon {
    class ParamManager {
    public:
        ParamManager();
        ParamManager(const QString&);
        ~ParamManager();
        void setFileName();
        bool loadParam(QChar&, const QString&, QChar d = 0);
        bool loadParam(int&, const QString&, int d = 0);
        bool loadParam(double&, const QString&, double d = 0);
        bool loadParam(QString&, const QString&, QString d = "");
        bool loadParam(bool&, const QString&, bool d = false);
        bool loadParam(double* value, const QString& key1, const QString& key2, double* defaultValue, const int size);
        bool changeParam(const QString&, const QVariant&);
        bool changeParam(const QString&, const QString&, const QVariant&);
        QStringList allKeys();
        QStringList allKeys(const QString&);
        QStringList allGroups();
        QVariant value(const QString&, const QVariant& defaultValue = QVariant());
        QVariant value(const QString&, const QString&, const QVariant& defaultValue = QVariant());
        void sync();
        void clear();
    protected:
        QString filename;
        QSettings* settings;
    };
} // namespace Falcon

#endif // ~_PARAMS_H

// void QSettings::setPath(Format format, Scope scope, const QString &path)
// QSettings settings("./myapp.ini", QSettings::IniFormat);
