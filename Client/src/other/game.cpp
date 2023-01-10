/**
#include "game.h"
#include "globaldata.h"
#include "staticparams.h"
#include "parammanager.h"
#include "interaction4field.h"
#include <QScreen>
#include <qDebug>
#include <QtMath>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QDir>
#include <QDateTime>
#include <limits>
namespace {
   auto opm = Owl::OParamManager::Instance();
   double init_basic_score[6] = {8,10,11,12,15,17}, init_K_time[4] = {1.2, 1, 0.8, 0},
          init_K_mode[2] = {1, 1.5}, init_K_rate[4] = {0, 0.8, 1, 1.2},
          init_K_spec[6] = {1, 1.35, 1.45, 1.25, 0.9, 0.7};
   double init_speed_mode[4] = {0, 8, 14, 20};
}

CGame::CGame() {
   start = false;
   isGrade = 0;
   opm->loadParam(param_width, "Division B/length", 12000);
   opm->loadParam(param_height, "Division B/width", 9000);
   opm->loadParam(param_goalWidth, "Division B/goal width", 1200);
   opm->loadParam(param_goalDepth, "Division B/goal depth", 200);
   opm->loadParam(maxTime, "game/maxTime", 30); //s
   opm->loadParam(maxDist, "game/maxDist", 90); //mm
   opm->loadParam(maxSpeed, "game/maxSpeed", 7000); //mm/s
   opm->loadParam(formation_num, "game/formation_num", 6);
   opm->loadParam(speed_num, "game/speed_num", 4);
   opm->loadParam(mode_num, "game/mode_num", 2);
   opm->loadParam(rate_num, "game/rate_num", 4);
   opm->loadParam(spec_rule_num, "game/spec_rule_num", 6);
   opm->loadParam(trail_num, "game/trail_num", 3);
   opm->loadParam(basic_score, "game", "basic_score", init_basic_score, formation_num);
   opm->loadParam(K_time, "game", "K_time", init_K_time, speed_num);
   opm->loadParam(K_mode, "game", "K_mode", init_K_mode, mode_num);
   opm->loadParam(K_rate, "game", "K_rate", init_K_rate, rate_num);
   opm->loadParam(K_spec, "game", "K_spec", init_K_spec, spec_rule_num);
   opm->loadParam(speed_mode, "game", "speed_mode", init_speed_mode, speed_num);
   opm->loadParam(detectFault, "game/detectFault", true);
   opm->loadParam(detectCrash, "game/detectCrash", true);
   opm->loadParam(detectOverSpeed, "game/detectOverSpeed", true);
   opm->loadParam(detectOverHeight, "game/detectOverHeight", true);
   opm->loadParam(fixDist, "game/fixDist", 70);
   list = Interaction4Field::getFormationFileName();
}

CGame::~CGame() {

}
// 犯规检测、自动裁判盒雏形
void CGame::startTimer() {
   start = true;
   t0 = QTime::currentTime();
   QScreen *screen=QGuiApplication::primaryScreen();
   QRect mm=screen->availableGeometry() ;
   int screen_width = mm.width();
   int screen_height = mm.height();
   qDebug()<<"width"<<screen_width<<"height"<<screen_height;
}

bool CGame::isGoal() {
   if(GlobalData::Instance()->maintain[0].ball[0].pos.x()<param_width/2+param_goalDepth
      && GlobalData::Instance()->maintain[0].ball[0].pos.x()>param_width/2+fixDist
      && abs(GlobalData::Instance()->maintain[0].ball[0].pos.y())<param_goalWidth/2)
      return true;
   return false;
}

bool CGame::outOfBoundary() {
   if(abs(GlobalData::Instance()->maintain[0].ball[0].pos.x())>param_width/2+fixDist ||
      abs(GlobalData::Instance()->maintain[0].ball[0].pos.y())>param_height/2+fixDist)
      return true;
   return false;
}

bool CGame::hasCrashed() {
   if(mode=="hard") return false;
   QFile file(QDir::currentPath() + "/Formations/" + formation + ".json");
    if ( !file.open( QIODevice::ReadWrite ) ) {
        qDebug() << "fail opening file";
        return true;
    }
    qDebug() << "opening" << file.fileName();
    bool crash = false;
    crashedCar.clear();
    QJsonParseError jsonParserError;
    QJsonDocument   jsonDocument = QJsonDocument::fromJson( file.readAll(), &jsonParserError );
    if ( !jsonDocument.isNull() && jsonParserError.error == QJsonParseError::NoError ) {
        qDebug() << "json successfully parsed";
        if ( jsonDocument.isObject() ) {
            QJsonObject jsonObject = jsonDocument.object();
            if ( jsonObject.contains("bots") && jsonObject.value("bots").isArray() ) {
                 QJsonArray botArray = jsonObject.value( "bots" ).toArray();
                 for ( int i = 0; i < botArray.size(); i++ ) {
                     if ( botArray[ i ].isObject() ) {
                         QJsonObject jsonbot = botArray[ i ].toObject();
                         Robot r;
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
                             }
                         }
                         ReceiveVisionMessage maintain = GlobalData::Instance()->maintain[0];
                         qDebug() << "bot from json" << r.team << r.id << r.pos.x() << r.pos.y();
                         qDebug() << "bot from maintain" << maintain.robot[r.team][maintain.robotIndex[r.team][r.id]].pos.x() 
                                  << maintain.robot[r.team][maintain.robotIndex[r.team][r.id]].pos.y();
                         if(maintain.robot[r.team][maintain.robotIndex[r.team][r.id]].pos.dist(r.pos)>maxDist) {
                           crash = true;
                           crashedCar.append(QString::number(r.id));
                         }
                     }
                 }
             }
         }
     }

     file.close();
     return crash;
}

QString CGame::getCrashedCar() {
   QString s;
   for(int i=0; i<crashedCar.size(); i++)
      s += " "+crashedCar.at(i);
   return s; 
}

void CGame::hasOverSpeed() {
   if(overSpeed) return;
   if(GlobalData::Instance()->maintain[0].ball[0].velocity.mod()>maxSpeed) overSpeed = true;
   else overSpeed = false;
}

bool CGame::hasOverHeight() {
   return false;
}

void CGame::detectFaults() {
   total_faults.clear();
   if(!detectFault) return;
   int faultNum = 1;
   if(detectCrash && hasCrashed()) {
      delta_time = maxTime + 10;
      total_faults.append("Fault"+QString::number(faultNum++)+": Attacker has crashed Defender"+getCrashedCar());
   }
   if(detectOverSpeed && overSpeed) {
      delta_time = maxTime + 20;
      total_faults.append("Fault"+QString::number(faultNum++)+": Attacker kicked ball too fast");
   }
   if(detectOverHeight && hasOverHeight()) {
      delta_time = maxTime + 30;
      total_faults.append("Fault"+QString::number(faultNum++)+": The goal is too high");
   }
}

void CGame::report(int mode) {
   QDialog dialog;
   QFormLayout form(&dialog);
   QString message;
   detectFaults();
   switch(mode) {
      case 0:
         message = "Overtime";
         break;
      case 1:
         if(total_faults.size())
            message = "Invalid Goal";
         else
            message = "GOAL!!! It takes " + QString::number(delta_time, 'f', 3) + "s";
         break;
      case 2:
         message = "Failure: Ball out of boundary";
         break;
      case 3:
         message = "Congratulations!!! Final result is" + QString::number(total_grade, 'f', 3);
         break;
      default:
         message = "Error";
         break;
   }
   form.addRow(new QLabel(message));
   for(int i = 0; i< total_faults.size();++i) {
      form.addRow(new QLabel(total_faults.at(i)));
   }
   //QPushButton* button_add = new QPushButton(tr("&Edit Faults"));
   //QObject::connect(button_add, SIGNAL(clicked()), this, SLOT(OnClicked()));
   //form.addRow(button_add);
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   if (dialog.exec() == QDialog::Accepted) {}
   else return;
}

void CGame::OnClicked() {
   
}

void CGame::judgeBallState() {
   delta_time = t0.msecsTo(QTime::currentTime()) * 0.001;
   if(delta_time > maxTime) {
      report(0);
      dealWithData();
   }
   else {
      hasOverSpeed();
      if(isGoal()) {
         report(1);
         dealWithData();
      }
      else if(outOfBoundary()) {
         delta_time = maxTime + 40;
         report(2);
         dealWithData();
      }
   }
}
// 挑战模式选择
void CGame::setChallengeMode(int mode) {
    switch(mode) {
        case 0:
           isTrailMode();
           break;
        case 1:
           isGradeMode();
           break;
        default:
           break;
    }
}

void CGame::isTrailMode() {
   if(!checkNewStart()) return;
   isGrade = 1;
   cur_formation = cur_mode = cur_spec_rule = cur_trail = cur_recorder = 0;
   if(setOptions()) {
      createGameRecorder();
   }
}

void CGame::isGradeMode() {
   if(!checkNewStart()) return;
   isGrade = 2;
   cur_formation = cur_mode = cur_spec_rule = cur_recorder = 0;
   cur_trail = 1;
   if(setOptions()) {
      createGameRecorder();
      single_grade = total_grade = 0;
   }
}
// 交互界面设计
bool CGame::setOptions() {
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("Please select game conditions:"));
   QString value3 = QString("Formation: ");
   QComboBox *comboBox3 = new QComboBox(&dialog);
   for(int i=0; i<formation_num; i++)
      comboBox3->addItem(list[i]);
   comboBox3->setCurrentIndex(cur_formation);
   form.addRow(value3, comboBox3);
   QString value1 = QString("Level: ");
   QComboBox *comboBox1 = new QComboBox(&dialog);
   comboBox1->addItem("easy");
   comboBox1->addItem("hard");
   comboBox1->setCurrentIndex(cur_mode);
   form.addRow(value1, comboBox1);
   QString value2 = QString("Special rules: ");
   QComboBox *comboBox2 = new QComboBox(&dialog);
   for(int i=0; i<spec_rule_num; i++)
      comboBox2->addItem("Spec_rule_"+QString::number(i));
   comboBox2->setCurrentIndex(cur_spec_rule);
   form.addRow(value2, comboBox2);
   QString value4 = QString("Need record: ");
   QComboBox *comboBox4 = new QComboBox(&dialog);
   comboBox4->addItem("None");
   comboBox4->addItem("Excel");
   comboBox4->addItem("Log");
   comboBox4->addItem("Both");
   comboBox4->setCurrentIndex(cur_recorder);
   form.addRow(value4, comboBox4);
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
   if (dialog.exec() == QDialog::Accepted) {
      overSpeed = false;
      formation = comboBox3->currentText();
      mode = comboBox1->currentText();
      spec_rule = comboBox2->currentText();
      recorder = comboBox4->currentText();
      cur_formation = comboBox3->currentIndex();
      cur_mode = comboBox1->currentIndex();
      cur_spec_rule = comboBox2->currentIndex();
      cur_recorder = comboBox4->currentIndex();
      Interaction4Field::readFormationJson(formation);
      return true;
   }
   else return false;
}

bool CGame::checkNewStart() {
   if(isGrade==0) return true;
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("The last game is not over, please confirm whether to start again"));
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
   if (dialog.exec() == QDialog::Accepted) {
      stopGameRecorder();
      return true;
   }
   else return false;
}

void CGame::endChallenge() {
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("The game will be forced to end, please confirm whether to continue this operation"));
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
   if (dialog.exec() == QDialog::Accepted) {
      stopGameRecorder();
      isGrade = 0;
   }
   else return;
}

void CGame::showCurrentProgress() {
   if(cur_trail==1) {
      setOptions();
      return;
   }
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("Please select game conditions:"));
   form.addRow(new QLabel("Formation "+formation+"  Trial"+QString::number(cur_trail)));
   form.addRow(new QLabel("Level: "+mode));
   form.addRow(new QLabel("Special rule: "+spec_rule));
   form.addRow(new QLabel("Recorder: "+recorder));
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
   if (dialog.exec() == QDialog::Accepted) {
      overSpeed = false;
      Interaction4Field::readFormationJson(formation);
   }
   else return;
}

void CGame::calGrade() {
   for(int i=speed_num-1; i>=0; i--)
      if(minTime>speed_mode[i]) {
         cur_speed = i;
         break;
      }
   cur_rate = success_num;
   single_grade = basic_score[cur_formation]*K_time[cur_speed]*K_mode[cur_mode]*K_rate[cur_rate]*K_spec[cur_spec_rule];
   total_grade += single_grade;
}

void CGame::dealWithData() {
   start = false;
   if(isGrade==1) {
      writeToFile();
      setOptions();
      return;
   }
   else if(isGrade==2) {
      if(cur_trail==1) {
         minTime = delta_time;
         success_num = 0;
      }
      if(delta_time<=minTime) minTime = delta_time;
      if(delta_time<=maxTime) success_num++;
      if(cur_trail==trail_num) calGrade();
      writeToFile();
      cur_trail = cur_trail % trail_num + 1;
      showCurrentProgress();
   }
}

void CGame::createGameRecorder() {
   switch(cur_recorder) {
      case 0:
         break;
      case 1:
         writeGameInfo();
         break;
      case 2:
         Interaction4Field::setRecorder(true, true);
         break;
      case 3:
         writeGameInfo();
         Interaction4Field::setRecorder(true, true);
         break;
      default:
         break;
   }
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("Game Recorder is created: "+recorder));
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   if (dialog.exec() == QDialog::Accepted) return;
   else return;
}

void CGame::stopGameRecorder() {
   switch(cur_recorder) {
      case 0:
         break;
      case 1:
         if(isGrade==2) report(3);
         break;
      case 2:
         Interaction4Field::setRecorder(false, true);
         break;
      case 3:
         if(isGrade==2) report(3);
         Interaction4Field::setRecorder(false, true);
         break;
      default:
         break;
   }
   QDialog dialog;
   QFormLayout form(&dialog);
   form.addRow(new QLabel("Game Recorder is stopped"));
   QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
   form.addRow(&buttonBox);
   QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
   if (dialog.exec() == QDialog::Accepted) filepath = " ";
   else return;
}

void CGame::writeGameInfo() {
   if(isGrade==1) filepath = QDir::currentPath() + "/GameInfo/Trail/trail"+QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")+".xlsx";
   else filepath = QDir::currentPath()+"/GameInfo/Grade/grade"+QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")+".xlsx";
   QAxObject *excel = new QAxObject(this);
   excel->setControl("Excel.Application");
   excel->setProperty("Visiblie", false);
   QAxObject *workbooks = excel->querySubObject("WorkBooks");
   workbooks->dynamicCall("Add");
   QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
   QAxObject *worksheets = workbook->querySubObject("Sheets"); //获取工作表集合  
   QAxObject *worksheet = worksheets->querySubObject("Item(int)",1); //获取工作表集合的工作表1，即sheet1
   QAxObject *cell;
   if(isGrade==1) {
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","A1"); //获取单元格
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("trail_time")); //设置单元格的值
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","B1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("formation"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","C1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("delta_time"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","D1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("mode"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","E1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("rate"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","F1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("spec_rule"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","G1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("Fault"));
   }
   else if(isGrade==2) {
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","A1"); //获取单元格
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("formation")); //设置单元格的值
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","B1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("basic_score"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","C1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("delta_time"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","D1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("K_time"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","E1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("mode"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","F1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("K_mode"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","G1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("rate"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","H1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("K_rate"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","I1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("spec_rule"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","J1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("K_spec"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","K1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("calculated_scores"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","L1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("cumulative_scores"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","M1");
      cell->dynamicCall("SetValue(const QVariant&)",QVariant("Fault"));
   }
   workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));
   workbook->dynamicCall("Close (Boolean)", false);
   excel->dynamicCall("Quit (void)");
   delete excel;
   excel = NULL;
   rowCount = 1;
}

void CGame::writeToFile() {
   if(filepath.isEmpty()) return;
   QAxObject *excel = new QAxObject(this);
   excel->setControl("Excel.Application");
   excel->setProperty("Visiblie", false);
   QAxObject *workbooks = excel->querySubObject("WorkBooks");
   workbooks->dynamicCall("Open(const QString&)", filepath);
   QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
   QAxObject *worksheets = workbook->querySubObject("Sheets"); //获取工作表集合
   QAxObject *worksheet = worksheets->querySubObject("Item(int)",1); //获取工作表集合的工作表1，即sheet1
   QAxObject *cell;
   if(isGrade==1) {
      rowCount++;
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","A"+QString::number(rowCount)); //获取单元格
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))); //设置单元格的值
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","B"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(formation));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","C"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(delta_time));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","D"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(mode));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","E"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(delta_time<=maxTime? "success":"failure"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","F"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(spec_rule));
      for(int i = 0; i< total_faults.size();++i) {
         QChar ch = i + 'G';
         cell = worksheet->querySubObject("Range(QVariant, QVariant)",QString(ch)+QString::number(rowCount));
         cell->dynamicCall("SetValue(const QVariant&)",QVariant(total_faults.at(i)));
      }
   }
   else if(isGrade==2) {
      rowCount++;
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","A"+QString::number(rowCount)); //获取单元格
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(formation)); //设置单元格的值
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","B"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(basic_score[cur_formation]));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","C"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(delta_time));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","D"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(cur_trail==trail_num? QString::number(K_time[cur_speed]):"-"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","E"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(mode));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","F"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(K_mode[cur_mode]));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","G"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(delta_time<=maxTime? "success":"failure"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","H"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(cur_trail==trail_num? QString::number(K_rate[cur_rate]):"-"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","I"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(spec_rule));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","J"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(K_spec[cur_spec_rule]));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","K"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(cur_trail==trail_num? QString::number(single_grade):"-"));
      cell = worksheet->querySubObject("Range(QVariant, QVariant)","L"+QString::number(rowCount));
      cell->dynamicCall("SetValue(const QVariant&)",QVariant(cur_trail==trail_num? QString::number(total_grade):"-"));
      for(int i = 0; i< total_faults.size();++i) {
         QChar ch = i + 'M';
         cell = worksheet->querySubObject("Range(QVariant, QVariant)",QString(ch)+QString::number(rowCount));
         cell->dynamicCall("SetValue(const QVariant&)",QVariant(total_faults.at(i)));
      }
   }
   workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath)); //保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了
   workbook->dynamicCall("Close()"); //关闭工作簿  
   excel->dynamicCall("Quit()"); //关闭excel
   delete excel;
   excel = NULL;  
}
**/
   //QFileDialog dialog;
   //QString filepath = QFileDialog::getSaveFileName(&dialog,"Save As","./GameInfo/Trail","All files(*.*)");
   //if(!filepath.isEmpty()){
   /**QAxObject *excel = new QAxObject(this);
      excel->setControl("Excel.Application");//连接Excel控件  
      excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体  
      excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示  
      QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合  
      workbooks->dynamicCall("Add");//新建一个工作簿  
      QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿  
      QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合  
      QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1  
      QAxObject *cellX,*cellY;
      for(int i=0;i<1;i++){
          QString X="A"+QString::number(i+1);//设置要操作的单元格，如A1
          QString Y="B"+QString::number(i+1);
          cellX = worksheet->querySubObject("Range(QVariant, QVariant)",X);//获取单元格
          cellY = worksheet->querySubObject("Range(QVariant, QVariant)",Y);
          cellX->dynamicCall("SetValue(const QVariant&)",QVariant(1.0));//设置单元格的值
          cellY->dynamicCall("SetValue(const QVariant&)",QVariant(2.0));
      }
      workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了
      workbook->dynamicCall("Close()");//关闭工作簿  
      excel->dynamicCall("Quit()");//关闭excel  
      delete excel;  
      excel = NULL;**/
   //}

/**bool CGame::writeCurrentSheet(const QList<QList<QVariant> > &cells)
{
    if(cells.size() <= 0)
        return false;
    if(NULL == this->sheet || this->sheet->isNull())
        return false;
    int row = cells.size();
    int col = cells.at(0).size();
    QString rangStr;
    convertToColName(col,rangStr);
    rangStr += QString::number(row);
    rangStr = "A1:" + rangStr;
    qDebug()<<rangStr;
    QAxObject *range = this->sheet->querySubObject("Range(const QString&)",rangStr);
    if(NULL == range || range->isNull())
    {
        return false;
    }
    bool succ = false;
    QVariant var;
    castListListVariant2Variant(cells,var);
    succ = range->setProperty("Value", var);
    delete range;
    return succ;
}

void CGame::convertToColName(int data, QString &res)
{
    Q_ASSERT(data>0 && data<65535);
    int tempData = data / 26;
    if(tempData > 0)
    {
        int mode = data % 26;
        convertToColName(mode,res);
        convertToColName(tempData,res);
    }
    else
    {
        res=(to26AlphabetString(data)+res);
    }
}

QString CGame::to26AlphabetString(int data)
{
    QChar ch = data + 0x40; //A对应0x41
    return QString(ch);
}

void CGame::castVariant2ListListVariant(const QVariant &var, QList<QList<QVariant> > &res)
{
    QVariantList varRows = var.toList();
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount = varRows.size();
    QVariantList rowData;
    for(int i=0;i<rowCount;++i)
    {
        rowData = varRows[i].toList();
        res.push_back(rowData);
    }
}**/
