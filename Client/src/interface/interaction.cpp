#include "interaction.h"
#include "visionmodule.h"
#include "globaldata.h"
#include "maintain.h"
#include "globalsettings.h"
#include "simmodule.h"
#include "refereethread.h"
#include "rec_recorder.h"
#include "rec_player.h"
#include "rec_slider.h"
#include "display.h"
#include "Windows.h"
#include "networkinterfaces.h"
#include "communicator.h"
#include <QProcess>
#include <QFileDialog>
#include <QTextCodec>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include "staticparams.h"
#include "debugger.h"
#include "test.h"
#include "game.h"
#include "shellapi.h"
#include "remotesim.h"
namespace {
QProcess *blueRBKProcess = nullptr;
QProcess *yellowRBKProcess = nullptr;
QProcess *simProcess = nullptr;
//QProcess* crayProcess = nullptr;
QProcess *monitorProcess = nullptr;
auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
}
Interaction::Interaction(QObject *parent) : QObject(parent) {
    RBKpath[PARAM::BLUE] = qApp->applicationDirPath() + "/Core"; //cpm->BlueRBKPath;
    RBKpath[PARAM::YELLOW] = qApp->applicationDirPath() + "/Core"; //cpm->YellowRBKPath;
    RBKdirectory[PARAM::BLUE] = RBKpath[PARAM::BLUE].left(RBKpath[PARAM::BLUE].lastIndexOf('/'));
    RBKdirectory[PARAM::YELLOW] = RBKpath[PARAM::YELLOW].left(RBKpath[PARAM::YELLOW].lastIndexOf('/'));
    SIMpath = qApp->applicationDirPath() + "/grSim"; //cpm->grSimPath;
    SIMdirectory = SIMpath.left(SIMpath.lastIndexOf('/'));
//    Craypath = cpm->CrayPath;
//    Craydirectory = Craypath.left(Craypath.lastIndexOf('/'));
}
Interaction::~Interaction() {
    if (simProcess != nullptr) {
        if (simProcess->isOpen()) {
            simProcess->close();
        }
        delete simProcess;
        simProcess = nullptr;
        QTextStream(stdout) << "\n------------------------------------\nexit Sim\n------------------------------------\n";
    }
    if (blueRBKProcess != nullptr) {
        if (blueRBKProcess->isOpen()) {
            blueRBKProcess->close();
        }
        delete blueRBKProcess;
        blueRBKProcess = nullptr;
        QTextStream(stdout) << "\n------------------------------------\nexit blue rbk\n------------------------------------\n";
    }
    if (yellowRBKProcess != nullptr) {
        if (yellowRBKProcess->isOpen()) {
            yellowRBKProcess->close();
        }
        delete yellowRBKProcess;
        yellowRBKProcess = nullptr;
        QTextStream(stdout) << "\n------------------------------------\nexit yellow rbk\n------------------------------------\n";
    }
    if (monitorProcess != nullptr) {
        if (monitorProcess->isOpen()) {
            monitorProcess->close();
        }
        delete monitorProcess;
        monitorProcess = nullptr;
        QTextStream(stdout) << "\n------------------------------------\nexit Monitor\n------------------------------------\n";
    }
}/**
void Interaction::chooseRBKpath(int team) {
    QFileDialog dialog;
    QString lastRBKpath = RBKpath[team];
    RBKpath[team] = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), RBKdirectory[team], "(*.exe)");
    if (!RBKpath[team].isEmpty())
    {
        int i = RBKpath[team].lastIndexOf('/');
        RBKdirectory[team] = RBKpath[team].left(i);
        QVariant VarPath(RBKpath[team]);
        if (team == PARAM::BLUE) cpm->updateParam(cpm->BlueRBKPath, "Path/BlueRBKPath", VarPath, true);
        else if (team == PARAM::YELLOW) cpm->updateParam(cpm->YellowRBKPath, "Path/YellowRBKPath", VarPath, true);
        cpm->sync();
    }
    else {
        RBKpath[team] = lastRBKpath;
    }
}
void Interaction::chooseSIMpath() {
    QFileDialog dialog;
    QString lastSIMpath = SIMpath;
    SIMpath = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), SIMdirectory, "(*.exe)");
    if (!SIMpath.isEmpty())
    {
        int i = SIMpath.lastIndexOf('/');
        SIMdirectory = SIMpath.left(i);
        QVariant VarPath(SIMpath);
        cpm->updateParam(cpm->grSimPath, "Path/grSimPath", VarPath, true);
        cpm->sync();
    }
    else {
        SIMpath = lastSIMpath;
    }
}
void Interaction::chooseCraypath() {
    QFileDialog dialog;
    QString lastCraypath = Craypath;
    Craypath = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), Craydirectory, "(*.exe)");
    if (!Craypath.isEmpty())
    {
        int i = Craypath.lastIndexOf('/');
        Craydirectory = Craypath.left(i);
        QVariant VarPath(Craypath);
        cpm->updateParam(cpm->CrayPath, "Path/CrayPath", VarPath, true);
        cpm->sync();
    }
    else {
        Craypath = lastCraypath;
    }
}**/
bool Interaction::controlBlueRBK(bool control) {
    if(control == false) {
        if (blueRBKProcess != nullptr) {
            if (blueRBKProcess->isOpen()) {
                blueRBKProcess->close();
            }
            delete blueRBKProcess;
            blueRBKProcess = nullptr;
            QTextStream(stdout) << "\n------------------------------------\nexit blue rbk\n------------------------------------\n";
        }
    } else {
        blueRBKProcess = new QProcess();
        // 告诉要打开的APP他的路径
        blueRBKProcess->setWorkingDirectory(RBKdirectory[PARAM::BLUE]); //"../RBK_RUN_2015/bin");
        blueRBKProcess->setCreateProcessArgumentsModifier(
                       [](QProcess::CreateProcessArguments *args) {
               args->flags |= CREATE_NEW_CONSOLE;
               args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;
           });
        // 要打开APP，用它的绝对路径
        QString name = QString("\"").append(RBKpath[PARAM::BLUE]).append("\""); //"../RBK_RUN_2015/bin/rbk.exe";
        blueRBKProcess->start(name);
        QTextStream(stdout) << "\n------------------------------------\n" << "running " << name << "\n------------------------------------\n";
    }
    return true;
}
bool Interaction::controlYellowRBK(bool control) {
    if(control == false) {
        if (yellowRBKProcess != nullptr) {
            if (yellowRBKProcess->isOpen()) {
                yellowRBKProcess->close();
            }
            delete yellowRBKProcess;
            yellowRBKProcess = nullptr;
            QTextStream(stdout) << "\n------------------------------------\nexit yellow rbk\n------------------------------------\n";
        }
    } else {
        yellowRBKProcess = new QProcess();
        yellowRBKProcess->setWorkingDirectory(RBKdirectory[PARAM::YELLOW]); //"../RBK_RUN_2015/bin");
        yellowRBKProcess->setCreateProcessArgumentsModifier(
                       [](QProcess::CreateProcessArguments *args) {
               args->flags |= CREATE_NEW_CONSOLE;
               args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;
           });
        QString name = QString("\"").append(RBKpath[PARAM::YELLOW]).append("\""); //"../RBK_RUN_2015/bin/rbk.exe";
        yellowRBKProcess->start(name);
        QTextStream(stdout) << "\n------------------------------------\n" << "running " << name << "\n------------------------------------\n";
    }
    return true;
}
bool Interaction::controlSim(bool control, bool show) {
    if(control == false) {
        if (simProcess != nullptr) {
            if (simProcess->isOpen()) {
                simProcess->close();
            }
            delete simProcess;
            simProcess = nullptr;
            QTextStream(stdout) << "\n------------------------------------\nexit Sim\n------------------------------------\n";
        }
    } else {
        simProcess = new QProcess();
        QString name =  QString("\"").append(SIMpath).append("\"");
        QStringList args;
        if(!show) args << "-H";
        else simProcess->setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args) {
               args->flags |= CREATE_NEW_CONSOLE;
               args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;});
        simProcess->start(name, args);
        QTextStream(stdout) << "\n------------------------------------\n" << "running " << name << "\n------------------------------------\n";
    }
    return true;
}/**
bool Interaction::controlCray(bool control) {
    if (control == false) {
        if (crayProcess != nullptr) {
            if (crayProcess->isOpen()) {
                crayProcess->close();
            }
            delete crayProcess;
            crayProcess = nullptr;
            QTextStream(stdout) << "\n------------------------------------\nexit Cray\n------------------------------------\n";
        }
    }
    else {
        crayProcess = new QProcess();
        QString name = QString("\"").append(Craypath).append("\"");
        crayProcess->start(name);
        QTextStream(stdout) << "\n------------------------------------\n" << "running " << name << "\n------------------------------------\n";
    }
    return true;
}**/
bool Interaction::controlMonitor(bool control) {
    if(control == false) {
        if (monitorProcess != nullptr) {
            if (monitorProcess->isOpen()) {
                monitorProcess->close();
            }
            delete monitorProcess;
            monitorProcess = nullptr;
            QTextStream(stdout) << "\n------------------------------------\nexit Monitor\n------------------------------------\n";
        }
    } else {
        monitorProcess = new QProcess();
        QString name = "sh ProcessAlive.sh"; //"./ProcessAlive.exe";
        monitorProcess->start(name);
        QTextStream(stdout) << "\n------------------------------------\n" << "start : " << name << "\n------------------------------------\n";
    }
    return true;
}
bool Interaction::changeRBKSettings(bool color, bool side) {
    opm->updateParam(opm->isYellow, "Alert/isYellow", color, true);
    opm->updateParam(opm->isRight, "Alert/isRight", side, true);
    return true;
}
bool Interaction::connectRadio(bool sw, int color, int frq) {
    if(sw) {
        ZCommunicator::Instance()->disconnectMedusa(color);
        ZCommunicator::Instance()->connectMedusa(color);
        Debugger::Instance()->start(color);
        Owl::ActionModule::Instance()->closeSerialPort();
//        RefereeThread::Instance()->run();
        return Owl::ActionModule::Instance()->openSerialPort();
    } else {
//        return Owl::ActionModule::Instance()->closeSerialPort();
        Debugger::Instance()->stop(color);
//        RefereeThread::Instance()->disconnectTCP();
    }
}
bool Interaction::connectSim(bool sw, int color) { //0 blue 1 yellow
    if(sw) {
        ZCommunicator::Instance()->disconnectMedusa(color);
        ZCommunicator::Instance()->connectMedusa(color);
        Debugger::Instance()->start(color);
        Owl::ZSimModule::Instance()->disconnectSim(color);
        ZSS::ZRemoteSimModule::Instance()->disconnectSim(color);
        if (ZCommunicator::Instance()->getGrsimInterfaceIndex() == 0 && opm->useSimInside)
            return Owl::ZSimModule::Instance()->connectSim(color);
        else
            return ZSS::ZRemoteSimModule::Instance()->connectSim(color);
    } else {
//        return Owl::ZSimModule::Instance()->disconnectSim(color); //fix a bug for Medusa out of Athena
        Debugger::Instance()->stop(color);
    }
}
void Interaction::kill(bool kill) {
    if(!kill) return;
    ZRecRecorder::Instance()->stop();
    QProcess killTask;
#ifdef WIN32
//    RefereeThread::Instance()->disconnectTCP();
    //QString cray = "taskkill -im Cray.exe -f";
    QString core = "taskkill -im Core.exe -f";
    QString grSim = "taskkill -im grSim.exe -f";
    QString client = "taskkill -im Client.exe -f";
#else
    //QString cray = "pkill Cray";
    QString core = "pkill Core";
    QString grSim = "pkill grSim";
    QString client = "pkill Client";
#endif
    if (monitorProcess != nullptr) {
        if (monitorProcess->isOpen()) {
            monitorProcess->close();
        }
        delete monitorProcess;
        monitorProcess = nullptr;
    }
    //killTask.execute(cray);
    killTask.execute(core);
    killTask.execute(grSim);
    killTask.execute(client);
    killTask.close();
}
void Interaction::controlProcess(int index, bool state) {
    GlobalData::Instance()->processControl[index] = state;
}
void Interaction::controlCamera(int index, bool state) {
    GlobalData::Instance()->cameraControl[index] = state;
}
void Interaction::setVision(bool needStart, bool real) {
    if (needStart) {
        opm->updateParam(opm->isSimulation, "Alert/isSimulation", !real, true);
        VisionModule::Instance()->udpSocketConnect();
        //if (real) RefereeThread::instance()->start();
    } else {
        VisionModule::Instance()->udpSocketDisconnect();
        //RefereeThread::instance()->disconnectTCP();
    }
}
void Interaction::setRecorder(bool isRecording) {
    if (isRecording) {
        ZRecRecorder::Instance()->start();
    } else {
        ZRecRecorder::Instance()->stop();
    }
}
void Interaction::setRecorderCut(bool isCutting) {
    ZRecRecorder::Instance()->cut(isCutting);
}
void Interaction::setRecordRawVision(bool recordRawVision) {
    ZRecRecorder::Instance()->setRecordRawVision(recordRawVision);
}
void Interaction::setPlayerRawVision(bool playRawVision) {
    RecPlayer::Instance()->setPlayerRawVision(playRawVision);
}
/**
bool Interaction::chooseLogToPlay() {
    QFileDialog dialog;
    QString filename = "";
    filename = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), "./LOG", "(*.log)");
    if (filename != "") {
        RecSlider::Instance()->loadFile(filename);
        qDebug()<<"You choose "<<filename;
        return true;
    }
    else {
        return false;
    }
}
**/
void Interaction::setIfEdgeTest(bool ifEdgeTest) {
    VisionModule::Instance()->setIfEdgeTest(ifEdgeTest);
}

void Interaction::setTestMode(bool isTesting, bool runTestingScripts){
    Test::Instance()->setMode(isTesting, runTestingScripts);
}

void Interaction::changeGrsimInterface(int index) {
    ZCommunicator::Instance()->setGrsimInterfaceIndex(index);
}
QStringList Interaction::getGrsimInterfaces() {
    return NetworkInterfaces::Instance()->getGrsimInterfaces();
}

void Interaction::getBasicInfo() {
    QDialog dialog;
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Falcon - AI framework developed by SRC team\nmainly used for controlling and debugging robots\ncreated in " + cpm->version));
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    if (dialog.exec() == QDialog::Accepted) {}
}
void Interaction::getMoreInfo() {
    QFileDialog dialog;
    QString Infopath = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), QApplication::applicationDirPath()+"/../Help", "All files(*.*)");
    if (!Infopath.isEmpty()) {        
        QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
        char* cexe = code->fromUnicode(Infopath).data();
        //QByteArray temp = Infopath.toLatin1();
        //char *cexe = temp.data();

        //QString qexe = QApplication::applicationDirPath()+QString("/owl2.exe");
        //QString str2 = qexe.replace(QRegExp("\\/"),"\\\\");//左右斜杠转换
        //QByteArray str1 = str2.toLatin1();
        //LPCSTR path1 = str1.data();
        
        ShellExecuteA(0,"open",cexe,NULL,NULL,true);
    }
}
/**
void Interaction::getSoftwareInfo() {
    QFileDialog dialog;
    Softwarepath = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), Softwaredirectory, "All files(*.*)");
    if (!Softwarepath.isEmpty())
    {
        int i = Softwarepath.lastIndexOf('/');
        Softwaredirectory = Softwarepath.left(i);
        QVariant VarPath(Softwarepath);
        cpm->updateParam("Softwarepath", VarPath, true);
        cpm->sync();
        
        QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
        char* cexe = code->fromUnicode(Softwarepath).data();
        
        ShellExecuteA(0,"open",cexe,NULL,NULL,true);
    }
}
**//**
void Interaction::showCurrentGrade(int mode) {
    QFileDialog dialog;
    QString path;
    switch(mode) {
        case 0:
           path = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), "./GameInfo/Trail", "All files(*.*)");
           break;
        case 1:
           path = dialog.getOpenFileName(&dialog, QString::fromLocal8Bit("open"), "./GameInfo/Grade", "All files(*.*)");
           break;
        default:
           break;
    }
    if (!path.isEmpty())
    {        
        QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
        char* cexe = code->fromUnicode(path).data();
        
        ShellExecuteA(0,"open",cexe,NULL,NULL,true);
    }
}
void Interaction4Field::setChallengeMode(int mode){
    Game::Instance()->setChallengeMode(mode);
}
void Interaction4Field::endChallenge(){
    Game::Instance()->endChallenge();
}
void Interaction4Field::showCurrentProgress(){
    Game::Instance()->showCurrentProgress();
}
void Interaction4Field::startTimer() {
    Game::Instance()->startTimer();
}
void Interaction4Field::createGameRecorder() {
    Game::Instance()->createGameRecorder();
}
void Interaction4Field::stopGameRecorder() {
    Game::Instance()->stopGameRecorder();
}
**/
void Interaction::updateInterfaces(){
    NetworkInterfaces::Instance()->updateInterfaces();
}
QStringList Interaction::getInterfaces(){
    return NetworkInterfaces::Instance()->getInterfaces();
}
void Interaction::changeVisionInterface(int index){
//    if(portNum < ports.size() && portNum >= 0){
//        serial.setPortName(ports[portNum]);
//        return true;
//    }
    VisionModule::Instance()->setInterfaceIndex(index);
//    qDebug() << "vision interface : " << index;
}

bool Interaction::connectSerialPort(bool sw){
    if(!sw){
        return Owl::ActionModule::Instance()->openSerialPort();
    }
    return Owl::ActionModule::Instance()->closeSerialPort();
}
bool Interaction::changeSerialFrequency(int frequency){
    return Owl::ActionModule::Instance()->changeFrequency(frequency);
}
bool Interaction::changeSerialPort(int index){
    return Owl::ActionModule::Instance()->changePorts(index);
}
QStringList Interaction::getSerialPortsList(){
    return Owl::ActionModule::Instance()->updatePortsList();
}
int Interaction::getFrequency(){
    return Owl::ActionModule::Instance()->getFrequency();
}
int Interaction::getMaxFrequency(){
    return Owl::ActionModule::Instance()->getMaxFrequency();
}
void Interaction::updateCommandParams(int robotID, int velX, int velY, int velR, bool dribble, int dribbleLevel, int mode, bool shoot, int power) {
    static int last_mode = -1;
    if (mode != last_mode) {
        last_mode = mode;
        if (mode <= 1) {
            Owl::KParamManager::Instance()->updateParam(Owl::KParamManager::Instance()->convertPower, "General/convertPower", true, true);
        }
        else {
            Owl::KParamManager::Instance()->updateParam(Owl::KParamManager::Instance()->convertPower, "General/convertPower", false, true);        
        }
    }
    mode = mode % 2; // 处理RemoteControl里的特殊mode，actionmodule只接受0/1
    Owl::ActionModule::Instance()->updateCommandParams(robotID, velX, velY, velR, dribble, dribbleLevel, mode, shoot, power);
}
bool Interaction::sendCommand(int robotNum) {
    return Owl::ActionModule::Instance()->sendLegacy(robotNum);
}
bool Interaction::getInfrared(int robotID) {
    return GlobalData::Instance()->robotInformation[opm->isYellow][robotID].infrared;
}
void Interaction::startRecordCommands(bool start){
    ZCommunicator::Instance()->startRecordCommands(start);
}

