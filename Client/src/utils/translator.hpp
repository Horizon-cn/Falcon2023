#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QTranslator>
#include <QCoreApplication>
#include <QtDebug>
class Translator : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)

public:
  Translator() {
    translator = new QTranslator(this);
  }

  QString getEmptyString() {
    return "";
  }

  Q_INVOKABLE void selectLanguage(QString language) {
    if (language == tr("Chinese")) {
      if(!translator->load("zh_CN", QCoreApplication::applicationDirPath()+"/../Language")){
        qWarning("Miss Language Package zh_CN.qm!");
      }
      QCoreApplication::instance()->installTranslator(translator);
    }
    else {
      QCoreApplication::instance()->removeTranslator(translator);
    }
    emit languageChanged();
  }

signals:
  void languageChanged();

private:
  QTranslator *translator;
};

#endif // TRANSLATOR_H
