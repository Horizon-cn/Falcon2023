#include "interaction4field.h"
#include "globalsettings.h"
#include "globaldata.h"
#include <QFileDialog>
#include "parammanager.h"
#include <QtMath>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QComboBox>
#include "simulator.h"
#include "staticparams.h"
QString Interaction4Field::menubar_crt_file = "";
namespace  {}
Interaction4Field::Interaction4Field(QObject *parent) : QObject(parent) {}
Interaction4Field::~Interaction4Field() {}
void Interaction4Field::setArea(int a,int b,int c,int d){
    GlobalSettings::Instance()->setArea(a,b,c,d);
}
void Interaction4Field::resetArea(){
    GlobalSettings::Instance()->resetArea();
}
void Interaction4Field::setSize(int width,int height){
    Field::setSize(width,height);
}
//void Interaction4Field::setPlacementPoint(int x,int y){
//    GlobalSettings::Instance()->setBallPlacementPos(x,y);
//}
void Interaction4Field::setCtrlC(){
    GlobalData::Instance()->ctrlCMutex.lock();
    GlobalData::Instance()->ctrlC = !GlobalData::Instance()->ctrlC;
    GlobalData::Instance()->ctrlCMutex.unlock();
}
int Interaction4Field::getRealX(int x){// cm
    return (int)Field::fieldXFromCoordinate(x)/10;
}
int Interaction4Field::getRealY(int y){// cm
    return (int)Field::fieldYFromCoordinate(y)/10;
}
void keyPress(QKeyEvent event);
void keyRelease(QKeyEvent event);
void Interaction4Field::robotControl(int id, int team) {
    Simulator::Instance()->controlRobot(id, team == 1);
}
void Interaction4Field::singleRobotControl(int id, int team) {
    Simulator::Instance()->controlSingleRobot(id, team == 1);
}
void Interaction4Field::saveFormation() {
    QString file_name = QFileDialog::getSaveFileName(NULL, tr("Save File"),QApplication::applicationDirPath()+"/../Formations", tr(" (*.json)"));
    QFile *file = new QFile(file_name);
    qDebug() << file_name;
    if(!file->open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"File open!";
    }

    QJsonDocument formation_jsonDoc;
    generateFormationJson(formation_jsonDoc);

    // 将json以文本形式写入文件并关闭文件。
    file->write(formation_jsonDoc.toJson());
    file->close();
}

void Interaction4Field::generateFormationJson(QJsonDocument& jsonDoc) {
    QJsonObject jsonball;
    QJsonArray jsonballpos;
    const Owl::Ball& b = GlobalData::Instance()->maintain[0].ball[0];
    jsonballpos.append(b.pos.x());
    jsonballpos.append(b.pos.y());
    jsonballpos.append(b.height);
    jsonball.insert("pos", QJsonValue(jsonballpos));

    QJsonArray jsonbots;
    for (int color = 0; color < PARAM::TEAMS; color++)
        for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
            int idx = GlobalData::Instance()->maintain[0].robotIndex[color][id];
            if (idx != -1){
                const Owl::Robot& r = GlobalData::Instance()->maintain[0].robot[color][idx];
                QJsonArray jsonpos;
                jsonpos.append(r.pos.x());
                jsonpos.append(r.pos.y());
                jsonpos.append(r.angle);

                QJsonObject jsonobj;
                jsonobj.insert("pos", QJsonValue(jsonpos));

                QJsonObject jsonid;
                jsonid.insert("number", id);
                color ? jsonid.insert("color", "YELLOW"): jsonid.insert("color", "BLUE");

                QJsonObject jsonbot;
                jsonbot.insert("obj", QJsonValue(jsonobj));
                jsonbot.insert("id", QJsonValue(jsonid));

                jsonbots.append(QJsonValue(jsonbot));
            }
        }

    QJsonObject jsonpack;
    jsonpack.insert("ball", QJsonValue(jsonball));
    jsonpack.insert("bots", QJsonValue(jsonbots));
    // 使用QJsonDocument设置该json对象
    
    jsonDoc.setObject(jsonpack);
}

void Interaction4Field::readFormationJson(QString fileName) {
    menubar_crt_file = fileName;
    QFile file(QApplication::applicationDirPath() + "/../Formations/" + fileName + ".json");
    if ( !file.open( QIODevice::ReadWrite ) ) {
        qDebug() << "fail opening file";
        return;
    }
    qDebug() << "opening" << file.fileName();
    QJsonParseError jsonParserError;
    QJsonDocument   jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );
    if ( !jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError ) {
        qDebug() << "json successfully parsed";
        Simulator::Instance()->controlRobot(0, PARAM::BLUE);
        Simulator::Instance()->controlRobot(0, PARAM::YELLOW);
        if ( jsonDocument.isObject() ) {
            QJsonObject jsonObject = jsonDocument.object();
            if ( jsonObject.contains("ball") && jsonObject.value("ball").isObject()) {
                 Owl::Ball b;
                 QJsonObject jsonball = jsonObject.value("ball").toObject();
                 if (jsonball.contains("pos") && jsonball.value("pos").isArray()) {
                     QJsonArray jsonballpos = jsonball.value("pos").toArray();
                     b.fill(jsonballpos[0].toDouble(), jsonballpos[1].toDouble(), Owl::RawInfo(), jsonballpos[2].toDouble());
                 }
                 qDebug() << "ball from json" << b.pos.x() << b.pos.y();
                 Simulator::Instance()->setBall(b.pos.x()/1000.0, b.pos.y()/1000.0, 0, 0);
            }

            if ( jsonObject.contains("bots") && jsonObject.value("bots").isArray() ) {
                 QJsonArray botArray = jsonObject.value( "bots" ).toArray();
                 for ( int i = 0; i < botArray.size(); i++ ) {
                     if ( botArray[ i ].isObject() ) {
                         QJsonObject jsonbot = botArray[ i ].toObject();
                         Owl::Robot r;
                         if ( jsonbot.contains("id") && jsonbot.value("id").isObject() &&
                              jsonbot.contains("obj") && jsonbot.value("obj").isObject()) {
                             // parsing id
                             QJsonObject jsonid = jsonbot.value("id").toObject();
                             if (jsonid.contains("color") && jsonid.value("color").isString()) {
                                 if(jsonid.value("color").toString() == "BLUE") r.team = 0;
                                 else if(jsonid.value("color").toString() == "YELLOW") r.team = 1;
                                 else qDebug()<<"error team in json!";
                             }
                             if (jsonid.contains("number") && jsonid.value("number").isDouble()){
                                 r.id = jsonid.value("number").toInt();
                             }
                             // parsing obj
                             QJsonObject jsonobj = jsonbot.value("obj").toObject();
                             if (jsonobj.contains("pos") && jsonobj.value("pos").isArray()) {
                                 QJsonArray jsonbotpos = jsonobj.value("pos").toArray();
                                 r.pos.setX(jsonbotpos[0].toDouble());
                                 r.pos.setY(jsonbotpos[1].toDouble());
                                 r.angle = jsonbotpos[2].toDouble();
                             }
                         }
                         qDebug() << "bot from json" << r.team << r.id << r.pos.x() << r.pos.y() << r.angle;
                         Simulator::Instance()->setRobot(r.pos.x()/1000.0, r.pos.y()/1000.0, r.id, r.team, r.angle * 180 / M_PI, true);
                     }
                 }
             }
         }
     }

     file.close();
}

QStringList Interaction4Field::getFormationFileName() {
    QStringList list;

    QDir dir(QApplication::applicationDirPath()+"/../Formations");
        if(!dir.exists())
            return list;

    QStringList filters;
    filters<<QString("*.json");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    for(int i=0; i < dir.count(); i++)
    {
       list.append(dir[i].chopped(5));  //文件名称
    }
    return list;
}


