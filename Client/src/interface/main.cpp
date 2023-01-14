#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QDir>
#include "interaction.h"
#include "interaction4field.h"
#include "field.h"
#include "display.h"
#include "parammanager.h"
#include "paraminterface.h"
#include "simulator.h"
#include "refereebox.h"
#include "game.h"
#include "debugger.h"
#include "test.h"
#include "viewerinterface.h"
#include "log_slider.h"
#include "logeventlabel.h"
#include "rec_slider.h"
#include "rec_eventlabel.h"
#include "optionobject.h"
#include "globaldata.h"

void qmlRegister() {
    qmlRegisterType<Field>("Owl", 1, 0, "Field");
    qmlRegisterType<Display>("Owl", 1, 0, "Display");
    qmlRegisterType<Interaction>("Owl", 1, 0, "Interaction");
    qmlRegisterType<Interaction4Field>("Owl", 1, 0, "Interaction4Field");
    qmlRegisterType<RefBoxCommand>("Owl", 1, 0, "RefBoxCommand");
    qmlRegisterType<GameState>("Owl", 1, 0, "GameState");
    qmlRegisterType<RefereeBox>("Owl", 1, 0, "RefereeBox");
    qmlRegisterType<ParamInterface>("Owl", 1, 0, "ParamModel");
    qmlRegisterType<ViewerInterface>("Owl", 1, 0, "ViewerInterface");
    qmlRegisterType<LogSlider>("Owl", 1, 0, "LogSlider");
    qmlRegisterType<LogEventLabel>("Owl", 1, 0, "LogEventLabel");
    //qmlRegisterType<optionObject>("Owl", 1, 0, "Option");
    //qmlRegisterType<Test>("Owl", 1, 0, "Test");
    qmlRegisterSingletonType<rec_slider>("Owl", 1, 0, "RecSlider", &rec_slider::Instance);
    qmlRegisterSingletonType<RecEventLabel>("Owl", 1, 0, "RecEventLabel", &RecEventLabel::Instance);
}

int main(int argc, char *argv[]) {
    // 展示可视化界面，使用KDDockWidgets
    // 博客链接https://blog.csdn.net/luoyayun361/article/details/117752657
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // 注册App
    QApplication app(argc, argv);
    app.setOrganizationName("SRC");
    app.setOrganizationDomain("https://src-ssl.github.io/");
    app.setFont(QFont("Microsoft YaHei", 9));
    // 创建必要文件夹
    QDir dir = qApp->applicationDirPath();
    QString folder_name[4] = { "../data","../LOG","../Formations","../Help" };
    for (int i = 0; i < 4; i++) {
        if (!dir.exists(folder_name[i])) {
            if (!dir.mkpath(folder_name[i]))
                qDebug() << "Fail to Create" << folder_name[i];
            else
                qDebug() << "Create" << folder_name[i] << "Successfully";
        }
    }
    // 公共参数初始化
    Owl::OParamManager::Instance()->setFileName();
    Owl::VParamManager::Instance()->setFileName();
    Owl::CParamManager::Instance()->setFileName();
    Owl::LParamManager::Instance()->setFileName();
    Owl::SIParamManager::Instance()->setFileName();
    Owl::SKParamManager::Instance()->setFileName();
    Owl::OParamManager::Instance()->loadParamFromFile();
    Owl::VParamManager::Instance()->loadParamFromFile();
    Owl::CParamManager::Instance()->loadParamFromFile();
    Owl::LParamManager::Instance()->clear();
    GlobalData::Instance();
    // 注册QML接口
    qmlRegister();
    // 启动程序    
    //auto flags = KDDockWidgets::Config::self().flags();
    //KDDockWidgets::Config::self().setFlags(flags);
    // config.setSeparatorThickness(0);
    // config.setFrameworkWidgetFactory(new CustomFrameworkWidgetFactory());

    QQmlApplicationEngine engine;

    //KDDockWidgets::Config::self().setQmlEngine(&engine);

    // engine.addImportPath("qrc:/src/qml/main.qml");
    const QUrl url(QStringLiteral("qrc:/src/qml/main.qml"));
    //QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    //    &app, [url](QObject* obj, const QUrl& objUrl) {
    //        if (!obj && url == objUrl)
    //            QCoreApplication::exit(-1);
    //    }, Qt::QueuedConnection);
    engine.load(url);
    
    return app.exec();
}
