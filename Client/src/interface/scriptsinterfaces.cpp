#include "scriptsinterfaces.h"
#include <QFile>
#include <QApplication>

CScriptsInterfaces::CScriptsInterfaces(QObject* parent) : QObject(parent)
{
    QFile file(QApplication::applicationDirPath() + "/../lua_scripts/test/Config.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "fail opening" << file.fileName();
        return;
    }
    qDebug() << "opening" << file.fileName();
    QJsonParseError jsonParserError;
    jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParserError);
    if (!jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError) {
        qDebug() << "successfully parsed" << file.fileName();
        if (jsonDocument.isObject()) {
            jsonObject = jsonDocument.object();
        }
    }
    updatePlayList();
}

void CScriptsInterfaces::updatePlayList() {
    playList.clear();
    QStringList playType = { "gTestPlay" , "gRefPlay" };
    for (int i = 0; i < playType.size(); i++) {
        if (jsonObject.contains(playType[i]) && jsonObject.value(playType[i]).isArray()) {
            QJsonArray playArray = jsonObject.value(playType[i]).toArray();
            for (int i = 0; i < playArray.size(); i++)
                playList.append(playArray[i].toString());
        }
    }
}

void CScriptsInterfaces::changeReadyPlay(int currentIndex) {
    if (currentIndex >= playList.size()) return;
    jsonObject["gReadyPlay"] = playList[currentIndex];
}

void CScriptsInterfaces::writeJsonFile() {
    // 将object设置为本文档的主要对象
    jsonDocument.setObject(jsonObject);

    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile(QApplication::applicationDirPath() + "/../lua_scripts/test/Config.json");
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open error!";
        return;
    }

    // 将修改后的内容写入文件
    QTextStream wirteStream(&writeFile);
    wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
    wirteStream << jsonDocument.toJson();		// 写入文件
    writeFile.close();					// 关闭文件
}
