#include "field.h"
#include "visionmodule.h"
#include "maintain.h"
#include "globaldata.h"
#include "parammanager.h"
#include "globalsettings.h"
#include "simulator.h"
#include "zss_debug.pb.h"
#include "src_heatMap.pb.h"
#include <QColor>
#include <QtMath>
#include <QtDebug>
#include <iostream>
#include "geometry.h"
#include <QElapsedTimer>
#include "test.h"
#include "optionobject.h"
#include "dealrobot.h"
#include "interaction4field.h"
#include <limits>
#include "staticparams.h"

namespace {
const static float MIN_LENGTH = 500;//area length : mm
Qt::KeyboardModifiers mouse_modifiers;
const static QColor CAR_COLOR[PARAM::TEAMS]  = {QColor(25, 30, 150), QColor(241, 201, 50)};
const static QColor CAR_OFF[PARAM::TEAMS] = {QColor(25, 30, 150, 60), QColor(241, 201, 50, 60)};
const static QColor CAR_SHADOW[PARAM::TEAMS] = {QColor(25, 30, 150, 30), QColor(241, 201, 50, 30)};
const static QColor CAR_DIR[PARAM::TEAMS] = {Qt::white, Qt::white};
const static QColor FONT_COLOR[PARAM::TEAMS] = {Qt::white, Qt::white};
const static QColor DEBUG_COLOR[10] = {
    Qt::white,
    Qt::red,
    QColor(255, 100, 0),
    Qt::yellow,
    Qt::green,
    Qt::cyan,
    Qt::blue,
    QColor(128, 0, 255),
    Qt::gray,
    Qt::black
};
const static QColor DEBUG_BRUSH_COLOR = QColor(255, 255, 255, 20);
const static QColor COLOR_VIOLET(255, 0, 255);
const static QColor COLOR_ORANGE_SHADOW(255, 0, 255, 60);
const static QColor COLOR_TRANSORANGE(255, 170, 85, 100);
const static QColor COLOR_DARKGREEN(48, 48, 48);
const static QColor COLOR_RED(220, 53, 47);
const static QColor COLOR_LIGHTWHITE(255, 255, 255, 20);
const static qreal zoomStep = 0.05;
const static qreal zoomMax = 2;
const static qreal zoomMin = 0.35; //0.1;
const int ballRatio = 3;

auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
auto sipm = Owl::SIParamManager::Instance();
auto skpm = Owl::SKParamManager::Instance();
qreal zoomRatio = 1;
QPoint zoomStart = QPoint(0, 0);
QRect area;
QSize size;
// for field lines;
QPainterPath painterPath;
QPainterPath painterPathGoal;
QPainterPath painterPathWall;
QPen pen = QPen(QColor(150, 150, 150), 1);
QPen penGoal = QPen(QColor(150, 150, 150), 1);
QPen penWall = QPen(QColor(150, 150, 150), 1);
double x(double _x) {
    return (_x * opm->canvasWidth / opm->param_canvasWidth + opm->canvasWidth / 2.0 - zoomStart.x()) / zoomRatio;
}
double y(double _y) {
    return (-_y * opm->canvasHeight / opm->param_canvasHeight + opm->canvasHeight / 2.0 - zoomStart.y()) / zoomRatio;
}
QPointF p(QPointF& _p) {
    return QPointF(x(_p.x()), y(_p.y()));
}
double w(double _w) {
    return _w * opm->canvasWidth / opm->param_canvasWidth / zoomRatio;
}
double h(double _h) {
    return -_h * opm->canvasHeight / opm->param_canvasHeight / zoomRatio;
}
double a(double _a) {
    return _a * 16;
}
double r(double _r) {
    return _r * 16;
}
double orx(double _x) {
    return (_x - opm->canvasWidth / 2.0) * opm->param_canvasWidth / opm->canvasWidth;
}
double ory(double _y) {
    return -(_y - opm->canvasHeight / 2.0) * opm->param_canvasHeight / opm->canvasHeight;
}
double orw(double _w) {
    return (_w) * opm->param_canvasWidth / opm->canvasWidth;
}
double orh(double _h) {
    return -(_h) * opm->param_canvasHeight / opm->canvasHeight;
}
double rx(double x) {
    return ::orx(zoomStart.x() + x * zoomRatio);
}
double ry(double y) {
    return ::ory(zoomStart.y() + y * zoomRatio);
}
QPointF rp(const QPointF& p) {
    return QPointF(rx(p.x()), ry(p.y()));
}
double distance2(double dx, double dy) {
    return dx * dx + dy * dy;
}
template<typename T>
T limitRange(T value, T minValue, T maxValue) {
    return value > maxValue ? maxValue : (value < minValue) ? minValue : value;
}
auto GS = GlobalSettings::Instance();

//record
bool isRecord = true;

//draw heat map
std::thread* blueHeatMapThread = nullptr;
std::thread* yellowHeatMapThread = nullptr;

QElapsedTimer _timer;
}
namespace MiddleEvent {
QPoint start;
QPoint zoomStart;
}
qreal Field::getpredict_x() {
    return Maintain::Instance()->getpredict_x();
}
qreal Field::getpredict_y() {
    return Maintain::Instance()->getpredict_y();
}
Field::Field(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , pixmap(nullptr)
    , cameraMode(true)
    , _type(2) {
    setFillColor(COLOR_DARKGREEN);
    setImplicitWidth(opm->canvasWidth);
    setImplicitHeight(opm->canvasHeight);
    pixmap = new QPixmap(QSize(opm->canvasWidth, opm->canvasHeight));
    pixmapPainter.begin(pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing, true);
    heat_pixmap = new QPixmap(QSize(opm->canvasWidth, opm->canvasHeight));
    heatPainter.begin(heat_pixmap);
//    pixmapPainter.setRenderHint(QPainter::TextAntialiasing, true);
//    pixmapPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    ::area = QRect(0, 0, this->property("width").toReal(), this->property("height").toReal());
//    ::size = QSize(this->property("width").toReal(), this->property("height").toReal());
    robotID = -1;
    robotTeam = -1;
    pressedRobot = false;
    pressedRobotMode = 0;
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton | Qt::MiddleButton);
    //setAcceptHoverEvents(true);
    triggerDraw();
    connect(GS, SIGNAL(needRepaint()), this, SLOT(updateScreen())); //repaint()
    connect(VisionModule::Instance(), SIGNAL(needDraw()), this, SLOT(updateScreen())); //repaint()
    resetAfterMouseEvent();
    //draw heat map
    blueHeatMapThread = new std::thread([=] {receiveBlue();});
    blueHeatMapThread->detach();
    yellowHeatMapThread = new std::thread([=] {receiveYellow();});
    yellowHeatMapThread->detach();
    
    _timer.start();
    //lastTabType = tabType = _type;
    //paintOffCar();
}
Field::~Field() {
    delete blueHeatMapThread;
    blueHeatMapThread = nullptr;
    delete yellowHeatMapThread;
    yellowHeatMapThread = nullptr;
}
void Field::paint(QPainter* painter) { // this->update()调用
//    painter->drawPixmap(area, *pixmap, QRect(zoomStart, ::size * zoomRatio));
    painter->drawPixmap(area, *pixmap);
}
//interaction
void Field::mousePressEvent(QMouseEvent *e) {
    pressed = e->buttons();
    start = end = rp(e->pos());
    mouse_modifiers = e->modifiers();
    switch(pressed) {
    case Qt::LeftButton:
        leftPressEvent(e);
        break;
    case Qt::RightButton:
        rightPressEvent(e);
        break;
    case Qt::MiddleButton:
        middlePressEvent(e);
        break;
    default:
        break;
    }
    repaint();
}
void Field::mouseMoveEvent(QMouseEvent *e) {
    end = rp(e->pos());
    switch(pressed) {
    case Qt::LeftButton:
        leftMoveEvent(e);
        break;
    case Qt::RightButton:
        rightMoveEvent(e);
        break;
    case Qt::MiddleButton:
        middleMoveEvent(e);
        break;
    default:
        break;
    }
    repaint();
}
void Field::mouseReleaseEvent(QMouseEvent *e) {
    switch(pressed) {
    case Qt::LeftButton:
        leftReleaseEvent(e);
        break;
    case Qt::RightButton:
        rightReleaseEvent(e);
        break;
    case Qt::MiddleButton:
        middleReleaseEvent(e);
        break;
    default:
        break;
    }
    resetAfterMouseEvent();
    repaint();
}
void Field::mouseDoubleClickEvent(QMouseEvent* e)
{
    pressed = e->buttons();
    mouse_modifiers = e->modifiers();
    start = end = rp(e->pos());
    switch(pressed) {
    case Qt::LeftButton:
        leftDoubleClickEvent(e);
        break;
    case Qt::RightButton:
        rightDoubleClickEvent(e);
        break;
    case Qt::MiddleButton:
        break;
    default:
        break;
    }
    resetAfterMouseEvent();
    repaint();
}
void Field::resetAfterMouseEvent() {
    pressed = 0;
    start = end = QPoint(-9999, -9999);
    mouse_modifiers = Qt::NoModifier;
}
//control ball
void Field::leftPressEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            leftNoModifierPressEvent(e);
            break;
        case Qt::AltModifier:
            leftAltModifierPressEvent(e);
            break;
        case Qt::ControlModifier:
            leftCtrlModifierPressEvent(e);
            break;
        default:
            break;
    }
}
void Field::leftMoveEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            leftNoModifierMoveEvent(e);
            break;
        case Qt::AltModifier:
            leftAltModifierMoveEvent(e);
            break;
        case Qt::ControlModifier:
            leftCtrlModifierMoveEvent(e);
            break;
        default:
            break;
    }
}
void Field::leftReleaseEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            leftNoModifierReleaseEvent(e);
            break;
        case Qt::AltModifier:
            leftAltModifierReleaseEvent(e);
            break;
        case Qt::ControlModifier:
            leftCtrlModifierReleaseEvent(e);
            break;
        default:
            break;
    }
}
void Field::leftNoModifierPressEvent(QMouseEvent *e) {
    leftMoveEvent(e);
}
void Field::leftNoModifierMoveEvent(QMouseEvent *e) {
    Simulator::Instance()->setBall(rx(e->x()) / 1000.0, ry(e->y()) / 1000.0);
}
void Field::leftNoModifierReleaseEvent(QMouseEvent *e) {}
void Field::leftAltModifierPressEvent(QMouseEvent *e) {}
void Field::leftAltModifierMoveEvent(QMouseEvent *e) {}
void Field::leftAltModifierReleaseEvent(QMouseEvent *e) {}
void Field::leftCtrlModifierPressEvent(QMouseEvent *e) {
    checkClosestBall(rx(e->x()), ry(e->y()), 500); // 太难点了，点到Focus里面就行
}
void Field::leftCtrlModifierMoveEvent(QMouseEvent *e) {
    QLineF line(start, end);
    if(pressedBall) {
        displayData = ballRatio * line.length() / 1000.0;
    }
}
void Field::leftCtrlModifierReleaseEvent(QMouseEvent *e) {
    QLineF line(start, end);
    if(pressedBall) {
        const Owl::Ball& ball = GlobalData::Instance()->maintain[0].ball[0];
        Simulator::Instance()->setBall(ball.pos.x()/1000.0, ball.pos.y()/1000.0, ballRatio*line.dx()/1000.0, ballRatio*line.dy()/1000.0);
        pressedBall = false;
    }
}
void Field::leftDoubleClickEvent(QMouseEvent * e){
    double limit = sipm->BallRadius; //opm->ballDiameter;
    checkClosestBall(rx(e->x()), ry(e->y()), limit);
    if (pressedBall) {
        QDialog dialog;
        QFormLayout form(&dialog);
        form.addRow(new QLabel(tr("Set ball pos:")));
        QString value1 = QString(tr("x: "));
        QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
        spinbox1->setRange(std::numeric_limits<double>::lowest(), 1000000);
        spinbox1->setValue(GlobalData::Instance()->maintain[0].ball[0].pos.x()*0.1);
        form.addRow(value1, spinbox1);
        QString value2 = QString(tr("y: "));
        QDoubleSpinBox *spinbox2 = new QDoubleSpinBox(&dialog);
        spinbox2->setRange(std::numeric_limits<double>::lowest(), 1000000);
        spinbox2->setValue(GlobalData::Instance()->maintain[0].ball[0].pos.y()*0.1);
        form.addRow(value2, spinbox2);
        // Add Cancel and OK button
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
        if (dialog.exec() == QDialog::Accepted) {
            qDebug() << "setting ball" << "to" << spinbox1->text() << spinbox2->text();
            Simulator::Instance()->setBall(spinbox1->text().toDouble()*0.01, spinbox2->text().toDouble()*0.01, 0, 0);
        }
        pressedBall = false;
    }
}
void Field::checkClosestBall(double x, double y, double limit) {
    auto& vision = GlobalData::Instance()->maintain[0];
    if (vision.ball[0].valid) {
        const Owl::Ball& ball = vision.ball[0];
        if(distance2(ball.pos.x() - x, ball.pos.y() - y) < pow(limit, 2)) {
            pressedBall = true;
            return;
        }
    }
    pressedBall = false;
}
//control robot
void Field::rightPressEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            rightNoModifierPressEvent(e);
            break;
        case Qt::AltModifier:
            rightAltModifierPressEvent(e);
            break;
        case Qt::ControlModifier:
            rightCtrlModifierPressEvent(e);
            break;
        default:
            break;
    }
}
void Field::rightMoveEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            rightNoModifierMoveEvent(e);
            break;
        case Qt::AltModifier:
            rightAltModifierMoveEvent(e);
            break;
        case Qt::ControlModifier:
            rightCtrlModifierMoveEvent(e);
            break;
        default:
            break;
    }
}
void Field::rightReleaseEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
        case Qt::NoModifier:
            rightNoModifierReleaseEvent(e);
            break;
        case Qt::AltModifier:
            rightAltModifierReleaseEvent(e);
            break;
        case Qt::ControlModifier:
            rightCtrlModifierReleaseEvent(e);
            break;
        default:
            break;
    }
}
void Field::rightNoModifierPressEvent(QMouseEvent *e) {
    if(pressedRobot) {
        auto dir = GlobalData::Instance()->processRobot[0].robot[robotTeam][robotID].angle;
        Simulator::Instance()->setRobot(rx(e->x())/1000.0, ry(e->y())/1000.0, robotID, robotTeam == PARAM::YELLOW, dir*180/M_PI, true);
        robotID = -1;
        robotTeam = -1;
        pressedRobot = false;
    }
    else {
        checkClosestRobot(rx(e->x()), ry(e->y()), true);
        pressedRobotMode = 0;
    }
}
void Field::rightNoModifierMoveEvent(QMouseEvent *e) {
    if(pressedRobot) {
        pressedRobotMode = 1;
        auto dir = GlobalData::Instance()->processRobot[0].robot[robotTeam][robotID].angle;
        Simulator::Instance()->setRobot(rx(e->x())/1000.0, ry(e->y())/1000.0, robotID, robotTeam == PARAM::YELLOW, dir*180/M_PI, true);
    }
}
void Field::rightNoModifierReleaseEvent(QMouseEvent *e) {
    if(pressedRobotMode == 1) {
        robotID = -1;
        robotTeam = -1;
        pressedRobot = false;
    }
}
void Field::rightAltModifierPressEvent(QMouseEvent *e) {}
void Field::rightAltModifierMoveEvent(QMouseEvent *e) {}
void Field::rightAltModifierReleaseEvent(QMouseEvent *e) {}
void Field::rightCtrlModifierPressEvent(QMouseEvent *e) {
    checkClosestRobot(rx(e->x()), ry(e->y()));
}
void Field::rightCtrlModifierMoveEvent(QMouseEvent *e) {
    QLineF line(start, end);
    if(pressedRobot) {
        displayData = -line.angle();
        if(displayData < -180) displayData += 360;
        Simulator::Instance()->setRobot(start.x()/1000.0, start.y()/1000.0, robotID, robotTeam == PARAM::YELLOW, displayData);
    }
}
void Field::rightCtrlModifierReleaseEvent(QMouseEvent *e) {
    robotID = -1;
    robotTeam = -1;
    pressedRobot = false;
}
void Field::rightDoubleClickEvent(QMouseEvent * e){
    checkClosestRobot(rx(e->x()), ry(e->y()), true);
    if (pressedRobot) {
        QDialog dialog;
        QFormLayout form(&dialog);
        form.addRow(new QLabel(tr("Set robot pose:")));
        QString value1 = QString(tr("x: "));
        QDoubleSpinBox *spinbox1 = new QDoubleSpinBox(&dialog);
        spinbox1->setRange(std::numeric_limits<double>::lowest(), 1000000);
        spinbox1->setValue(GlobalData::Instance()->maintain[0].robot[robotTeam][robotID].pos.x()*0.1);
        form.addRow(value1, spinbox1);
        QString value2 = QString(tr("y: "));
        QDoubleSpinBox *spinbox2 = new QDoubleSpinBox(&dialog);
        spinbox2->setRange(std::numeric_limits<double>::lowest(), 1000000);
        spinbox2->setValue(-GlobalData::Instance()->maintain[0].robot[robotTeam][robotID].pos.y()*0.1);
        form.addRow(value2, spinbox2);
        QString value3 = QString(tr("dir: "));
        QDoubleSpinBox *spinbox3 = new QDoubleSpinBox(&dialog);
        spinbox3->setRange(std::numeric_limits<double>::lowest(), 1000000);
        spinbox3->setValue(GlobalData::Instance()->maintain[0].robot[robotTeam][robotID].angle*180/M_PI);
        form.addRow(value3, spinbox3);
        // Add Cancel and OK button
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
        if (dialog.exec() == QDialog::Accepted) {
            qDebug() << "setting robot" << QString::number(robotID) << "to" << spinbox1->text() << spinbox2->text() << spinbox3->text();
            Simulator::Instance()->setRobot(spinbox1->text().toDouble()*0.01, -spinbox2->text().toDouble()*0.01, robotID, robotTeam, spinbox3->text().toDouble(), true);
        }
        robotID = -1;
        robotTeam = -1;
        pressedRobot = false;
    }
}
void Field::checkClosestRobot(double x, double y, bool include_off_robots) {
    double limit = pow(sipm->RobotRadius*2, 2) / 4; //pow(opm->carDiameter, 2) / 4;
    auto& vision = GlobalData::Instance()->processRobot[0];
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        int iter_range = include_off_robots? PARAM::ROBOTMAXID : vision.robotSize[color]%PARAM::ROBOTMAXID;
        int invertflag = color==0? 1: -1;
        for(int j = 0; j < iter_range; j++) {
            Owl::Robot robot;
            if (vision.robotIndex[color][j] != -1) robot = vision.robot[color][j];
            else robot = Owl::Robot(color, ::rx(opm->canvasWidth * 0.5 + 30 * (j+1) * invertflag), ::ry(opm->canvasHeight - 60), M_PI_2 * (invertflag+1) + 0, -1);
            if(distance2(robot.pos.x() - x, robot.pos.y() - y) < limit) {
                robotID = vision.robotIndex[color][j] != -1? robot.id: j;
                robotTeam = color;
                pressedRobot = true;
                return;
            }
        }
    }
    robotID = -1;
    robotTeam = -1;
    pressedRobot = false;
}
//adjust field
void Field::middlePressEvent(QMouseEvent *e) {
    MiddleEvent::start.setX(e->x());
    MiddleEvent::start.setY(e->y());
    switch(mouse_modifiers) {
    case Qt::NoModifier:
        middleNoModifierPressEvent(e);
        break;
    case Qt::AltModifier:
        middleAltModifierPressEvent(e);
        break;
    case Qt::ControlModifier:
        middleCtrlModifierPressEvent(e);
        break;
    default:
        break;
    }
}
void Field::middleMoveEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
    case Qt::NoModifier:
        middleNoModifierMoveEvent(e);
        break;
    case Qt::AltModifier:
        middleAltModifierMoveEvent(e);
        break;
    case Qt::ControlModifier:
        middleCtrlModifierMoveEvent(e);
        break;
    default:
        break;
    }
}
void Field::middleReleaseEvent(QMouseEvent *e) {
    switch(mouse_modifiers) {
    case Qt::NoModifier:
        middleNoModifierReleaseEvent(e);
        break;
    case Qt::AltModifier:
        middleAltModifierReleaseEvent(e);
        break;
    case Qt::ControlModifier:
        middleCtrlModifierReleaseEvent(e);
        break;
    default:
        break;
    }
}
void Field::middleNoModifierPressEvent(QMouseEvent *e) {
    MiddleEvent::zoomStart = zoomStart;
}
void Field::middleNoModifierMoveEvent(QMouseEvent *e) {
    auto t = MiddleEvent::zoomStart + zoomRatio * (MiddleEvent::start - QPoint(e->x(), e->y()));
    zoomStart.setX(limitRange(t.x(), 0, int(area.width() * (zoomMax - zoomRatio))));
    zoomStart.setY(limitRange(t.y(), 0, int(area.height() * (zoomMax - zoomRatio))));
    triggerDraw();
}
void Field::middleNoModifierReleaseEvent(QMouseEvent *e) {}
void Field::middleAltModifierPressEvent(QMouseEvent *e) {
    GlobalSettings::Instance()->setBallPlacementPos(::rx(e->x()), ::ry(e->y()));
}
void Field::middleAltModifierMoveEvent(QMouseEvent *e) {
    middleAltModifierPressEvent(e);
}
void Field::middleAltModifierReleaseEvent(QMouseEvent *e) {
    middleAltModifierPressEvent(e);
}
void Field::middleCtrlModifierPressEvent(QMouseEvent *e) {
    middleCtrlModifierMoveEvent(e);
}
void Field::middleCtrlModifierMoveEvent(QMouseEvent *e) {
    auto x1 = ::rx(e->x());
    auto x2 = ::rx(MiddleEvent::start.x());
    auto y1 = ::ry(e->y());
    auto y2 = ::ry(MiddleEvent::start.y());
    auto minX = std::min(x1, x2);
    auto maxX = std::max(x1, x2);
    auto minY = std::min(y1, y2);
    auto maxY = std::max(y1, y2);
    if(maxX - minX < MIN_LENGTH * zoomRatio || maxY - minY < MIN_LENGTH * zoomRatio)
        GlobalSettings::Instance()->resetArea();
    else
        GlobalSettings::Instance()->setArea(minX, maxX, minY, maxY);
}
void Field::middleCtrlModifierReleaseEvent(QMouseEvent *e) {
    middleCtrlModifierMoveEvent(e);
}
#if QT_CONFIG(wheelevent)
void Field::wheelEvent (QWheelEvent *e) {
    qreal oldRatio = zoomRatio;
    zoomRatio += (e->delta() < 0 ? zoomStep : -zoomStep);
    zoomRatio = limitRange(zoomRatio, zoomMin, zoomMax); //1.0
    qDebug()<<"zoomRatio"<<zoomRatio;
    zoomStart -= e->pos() * (zoomRatio - oldRatio);
    zoomStart.setX(limitRange(zoomStart.x(), 0, int(area.width() * (zoomMax - zoomRatio))));
    zoomStart.setY(limitRange(zoomStart.y(), 0, int(area.height() * (zoomMax - zoomRatio))));
    pixmapPainter.setRenderHint(QPainter::Antialiasing, zoomRatio>0.5);
    triggerDraw();
}
#endif
void Field::setSize(int width, int height) {
    if (width > 0 && height > 0) {
        opm->updateParam(opm->canvasHeight, "Canvas/canvasHeight", height, true);
        opm->updateParam(opm->canvasWidth, "Canvas/canvasWidth", width, true);
        // 自动保持场地的正常尺寸
        opm->updateParam(opm->param_canvasHeight, "Canvas/param_canvasHeight", height * 1.0 / width * opm->param_canvasWidth, true);
        GlobalSettings::Instance()->needRepaint();
    }
}
void Field::triggerDraw() { //滚轮触发一次更新一次
    initPainterPath();
    GlobalData::Instance()->setCameraMatrix();
    heat_pixmap->fill(COLOR_DARKGREEN);
    heatPainter.setPen(Qt::NoPen);
    repaint();
}
void Field::repaint() {//change here!!!!!!! 每帧视觉都更新
//    if(repaint_mutex.try_lock()){
    if(!_draw) return;
    pixmap->fill(COLOR_DARKGREEN);
    switch(_type) {
    case 1:
        paintInit();
        drawOriginVision(0);
        break;
    case 2:
        pixmapPainter.setOpacity(0.3); //先调暗
        drawHeatMap(PARAM::BLUE);
        pixmapPainter.setOpacity(1); //画完热力图再调亮
        paintInit(); // 绘制场地线
        drawMaintainVision(0);
        drawDebugMessages(PARAM::BLUE); //BLUE
        //reportStatus();
        paintOffCar();
        break;
    case 3:
        pixmapPainter.setOpacity(0.3);
        drawHeatMap(PARAM::YELLOW);
        pixmapPainter.setOpacity(1);
        paintInit(); // 绘制场地线
        drawMaintainVision(0);
        drawDebugMessages(PARAM::YELLOW); //YELLOW
        //reportStatus();
        paintOffCar();
        break;
    default:
        break;
    }
    drawBallLine();
    this->update(area); // 清空绘制区域
//        repaint_mutex.unlock();
//    }
}
void Field::updateScreen() {
    if (_timer.elapsed() > 1000.0 / sipm->DesiredFPS) {
        _timer.restart();
        repaint();
    }
}
void Field::paintInit() {
    drawCtrlC();
    pixmapPainter.strokePath(painterPath, pen);
    pixmapPainter.strokePath(painterPathGoal, penGoal);
    pixmapPainter.strokePath(painterPathWall, penWall);
    drawSelectedArea();
}
void Field::drawBallLine() {
    if((pressed == Qt::LeftButton||pressed == Qt::RightButton)&&(mouse_modifiers == Qt::ControlModifier)) {
        pixmapPainter.setBrush(QBrush(FONT_COLOR[0]));
        pixmapPainter.setPen(QPen(FONT_COLOR[0], ::w(20), Qt::DashLine));
        pixmapPainter.drawLine(p(start), p(end));
        pixmapPainter.drawText(p(end), QString::fromStdString(std::to_string(displayData)));
    }
}

void Field::initPainterPath() {
    pen.setWidth(::w(opm->line_thickness)); //30
    painterPath = QPainterPath();
    painterPath.addRect(::x(-opm->field_length / 2.0), ::y(-opm->field_width / 2.0), ::w(opm->field_length), ::h(opm->field_width));
    painterPath.moveTo(::x(-opm->field_length / 2.0), ::y(0));
    painterPath.lineTo(::x(opm->field_length / 2.0), ::y(0));
    painterPath.moveTo(::x(0), ::y(opm->field_width / 2.0));
    painterPath.lineTo(::x(0), ::y(-opm->field_width / 2.0));
    painterPath.addEllipse(::x(-opm->center_radius), ::y(-opm->center_radius), ::w(2 * opm->center_radius), ::h(2 * opm->center_radius));
    if ( opm->field == "Division_B" && opm->if_ellipse_penalty ) {
        painterPath.moveTo(::x(-opm->field_length / 2.0 + opm->penalty_radius),
                           ::y(opm->penalty_area_l / 2.0));
        painterPath.arcTo(QRectF(::x( -opm->field_length / 2.0 -
                                      opm->penalty_radius),
                                 ::y( opm->penalty_area_l / 2.0 -
                                      opm->penalty_radius),
                                 ::w( opm->penalty_radius * 2.0 ),
                                 ::h( opm->penalty_radius * 2.0)),
                          0.0,
                          -90.0);
        painterPath.moveTo(::x( -opm->field_length / 2.0 + opm->penalty_radius ),
                           ::y( -opm->penalty_area_l / 2.0 ) );
        painterPath.arcTo(QRectF(::x( -opm->field_length / 2.0 -
                                      opm->penalty_radius ),
                                 ::y( -opm->penalty_area_l / 2.0 -
                                      opm->penalty_radius),
                                 ::w( opm->penalty_radius * 2.0 ),
                                 ::h( opm->penalty_radius * 2.0)),
                          0.0,
                          90.0);
        painterPath.moveTo(::x(-opm->field_length / 2.0 + opm->penalty_radius),
                           ::y(opm->penalty_area_l / 2.0));
        painterPath.lineTo(::x(-opm->field_length / 2.0 + opm->penalty_radius),
                           ::y(-opm->penalty_area_l / 2));

        painterPath.moveTo(::x(opm->field_length / 2.0 - opm->penalty_radius),
                           ::y(opm->penalty_area_l / 2.0));
        painterPath.arcTo(QRectF(::x( opm->field_length / 2.0 -
                                      opm->penalty_radius),
                                 ::y( opm->penalty_area_l / 2.0 -
                                      opm->penalty_radius),
                                 ::w( opm->penalty_radius * 2.0 ),
                                 ::h( opm->penalty_radius * 2.0)),
                          180.0,
                          90.0);
        painterPath.moveTo(::x( opm->field_length / 2.0 - opm->penalty_radius ),
                           ::y( -opm->penalty_area_l / 2.0 ) );
        painterPath.arcTo(QRectF(::x( opm->field_length / 2.0 -
                                      opm->penalty_radius ),
                                 ::y( -opm->penalty_area_l / 2.0 -
                                      opm->penalty_radius),
                                 ::w( opm->penalty_radius * 2.0 ),
                                 ::h( opm->penalty_radius * 2.0)),
                          180.0,
                          -90.0);
        painterPath.moveTo(::x(opm->field_length / 2.0 - opm->penalty_radius),
                           ::y(opm->penalty_area_l / 2.0));
        painterPath.lineTo(::x(opm->field_length / 2.0 - opm->penalty_radius),
                           ::y(-opm->penalty_area_l / 2));
    } else {
        painterPath.addRect(::x(-opm->field_length / 2.0), ::y(-opm->penalty_width / 2.0), ::w(opm->penalty_depth), ::h(opm->penalty_width));
        painterPath.addRect(::x(opm->field_length / 2.0), ::y(-opm->penalty_width / 2.0), ::w(-opm->penalty_depth), ::h(opm->penalty_width));
    }
    penGoal.setWidth(::w(opm->goal_thickness)); //30
    painterPathGoal = QPainterPath();
    painterPathGoal.addRect(::x(-opm->field_length / 2.0), ::y(-opm->goal_width / 2.0), ::w(-opm->goal_depth), ::h(opm->goal_width));
    painterPathGoal.addRect(::x(opm->field_length / 2.0), ::y(-opm->goal_width / 2.0), ::w(opm->goal_depth), ::h(opm->goal_width));
    penWall.setWidth(::w(opm->wall_thickness)); //30
    painterPathWall = QPainterPath();
    painterPathWall.addRect(::x(-opm->field_length / 2.0 - opm->field_wall_dist), ::y(-opm->field_width / 2.0 - opm->field_wall_dist), ::w(opm->field_length + 2 * opm->field_wall_dist), ::h(opm->field_width + 2 * opm->field_wall_dist));
}
void Field::drawOriginVision(int index) { //TODO: Draw field here!
    for(int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraControl[i] == true)
            drawVision(GlobalData::Instance()->camera[i][index]);
    }
    for (int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraControl[i] == true) {
            pixmapPainter.setBrush(Qt::NoBrush);
            pixmapPainter.setPen(COLOR_DARKGREEN);
            pixmapPainter.drawRect(QRect(QPoint(::x(GlobalData::Instance()->cameraMatrix[i].leftedge.min), ::y(GlobalData::Instance()->cameraMatrix[i].downedge.min)), QPoint(::x(GlobalData::Instance()->cameraMatrix[i].rightedge.min), ::y(GlobalData::Instance()->cameraMatrix[i].upedge.min))));
            pixmapPainter.setPen(COLOR_RED);
            pixmapPainter.drawRect(QRect(QPoint(::x(GlobalData::Instance()->cameraMatrix[i].leftedge.max), ::y(GlobalData::Instance()->cameraMatrix[i].downedge.max)), QPoint(::x(GlobalData::Instance()->cameraMatrix[i].rightedge.max), ::y(GlobalData::Instance()->cameraMatrix[i].upedge.max))));
            pixmapPainter.setFont(QFont("Helvetica [Cronyx]", 13, QFont::Bold));
            pixmapPainter.drawText(::x(GlobalData::Instance()->cameraMatrix[i].campos.x()), ::y(GlobalData::Instance()->cameraMatrix[i].campos.y()), QString::number(i));
        }
    }
}
void Field::drawMaintainVision(int index) {
//    for(int i = -99; i < 0; i ++) {
////        drawVision(GlobalData::Instance()->maintain[index + i],true);
//        auto& ball = GlobalData::Instance()->maintain[index + i].ball[0];
//        paintShadow(COLOR_TRANSORANGE, ball.pos.x(), ball.pos.y());
//    }
    const Owl::OriginMessage &robot_vision = GlobalData::Instance()->processRobot[index];
//    qDebug() << "FUCK GLOBALDATA" << GlobalData::Instance()->processRobot[index].robotSize[0] << GlobalData::Instance()->processRobot[index].robotSize[1];
//    qDebug() << "FUCK LAST GLOBALDATA" << GlobalData::Instance()->processRobot[index-1].robotSize[0] << GlobalData::Instance()->processRobot[index].robotSize[1];
    auto last_touch = GlobalData::Instance()->lastTouch % PARAM::ROBOTMAXID;
    auto last_touch_team = GlobalData::Instance()->lastTouch < PARAM::ROBOTMAXID ? PARAM::BLUE : PARAM::YELLOW;
//    qDebug() << "FUCK LAST TOUCH" << last_touch;
    /**for(int i = -99; i < 0; i ++) {
//        drawVision(GlobalData::Instance()->maintain[index + i],true);
        auto& robot = GlobalData::Instance()->maintain[index + i].robot[PARAM::BLUE][0];
        paintCarShadow(robot.pos.x(), robot.pos.y(), robot.angle);
    }**/
    if (last_touch < PARAM::ROBOTMAXID)
        for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
            for(int j = 0; j < robot_vision.robotSize[color]; j++) {
                auto& robot = robot_vision.robot[color][j];
                paintCar(CAR_COLOR[color], robot.id, robot.pos.x(), robot.pos.y(), robot.angle, true, FONT_COLOR[color], robot.id == robotID && color == robotTeam); //robot.id == last_touch && color == last_touch_team);
//            paintCarShadow(robot.pos.x(), robot.pos.y(), robot.angle);
//                qDebug() << "FUCK PAINT";
            }
        }

    auto& maintain = GlobalData::Instance()->maintain[index];

    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        for(int j = 0; j < maintain.robotSize[color]; j++) {
            auto& robot = maintain.robot[color][j];
            paintCarShadow(robot.pos.x(), robot.pos.y(), robot.angle);
        }
    }

    for(int i = -99; i < 0; i ++) {
//        drawVision(GlobalData::Instance()->maintain[index + i],true);
        auto& robot = GlobalData::Instance()->maintain[index + i].robot[PARAM::BLUE][0];
        paintShadow(COLOR_LIGHTWHITE, robot.pos.x(), robot.pos.y());
        auto& ball = GlobalData::Instance()->maintain[index + i].ball[0];
        paintShadow(COLOR_TRANSORANGE, ball.pos.x(), ball.pos.y());
    }
    for(int j = 0; j < maintain.ballSize; j++) {
        auto& ball = maintain.ball[j];
        QColor ballColor;
        if (ball.valid == 1)
            ballColor = COLOR_RED;
        else if (ball.valid == 2)
            ballColor = COLOR_VIOLET;
        else
            ballColor = COLOR_ORANGE_SHADOW;
        paintBall(ballColor, ball.pos.x(), ball.pos.y());
        paintFocus(ballColor, ball.pos.x(), ball.pos.y(), 500, ballFocusCount++);
    }
}
void Field::paintCar(const QColor& color, quint8 num, qreal x, qreal y, qreal radian, bool ifDrawNum, const QColor& textColor, bool needCircle) {
    static qreal radius = sipm->RobotRadius; //opm->carDiameter / 2.0;
    static qreal chordAngel = qRadiansToDegrees(qAsin(1.0 * sipm->CenterFromKicker / sipm->RobotRadius)); //qRadiansToDegrees(qAsin(2.0 * sipm->CenterFromKicker / opm->carDiameter)); //qRadiansToDegrees(qAcos(1.0 * opm->carFaceWidth / opm->carDiameter));
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(QPen(COLOR_RED, ::w(30), Qt::DotLine));
    pixmapPainter.drawLine(QPointF(::x(x), ::y(y)), QPointF(::x(x), ::y(y)) + QPointF(::w(200) * qSin(radian + M_PI_2), ::w(200) * qCos(radian + M_PI_2)));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawChord(QRectF(::x(x - radius), ::y(y - radius), ::w(2 * radius), ::h(2 * radius)), ::a(90.0 - chordAngel + 180 / M_PI * radian), ::r(180.0 + 2 * chordAngel));
    if (needCircle) {
        pixmapPainter.setBrush(Qt::NoBrush);
        pixmapPainter.setPen(QPen(COLOR_RED, ::w(30)));
        pixmapPainter.drawChord(QRectF(::x(x - radius), ::y(y - radius), ::w(2 * radius), ::h(2 * radius)), ::a(90.0 - chordAngel + 180 / M_PI * radian), ::r(180.0 + 2 * chordAngel));
    }
    if (ifDrawNum) {
        pixmapPainter.setBrush(Qt::NoBrush);
        pixmapPainter.setPen(QPen(textColor, ::w(30)));
        QFont font;
        int fontSize = ::h(-opm->numberSize);
        font.setPixelSize(fontSize);
        pixmapPainter.setFont(font);
        pixmapPainter.drawText(::x(x - opm->numberSize), ::y(y + sipm->RobotRadius * 0.8), QString::number(num, 16).toUpper()); //pixmapPainter.drawText(::x(x - opm->numberSize), ::y(y + opm->carDiameter * 0.4), QString::number(num, 16).toUpper());
    }
}
void Field::paintOffCar() {
    for (int color=0; color < PARAM::TEAMS; color++) {
        int invertflag = color==0? 1: -1;
        for (int i = 0; i < PARAM::ROBOTMAXID; i++ ) {
            if (GlobalData::Instance()->maintain[0].robotIndex[color][i] == -1) {
//                Simulator::Instance()->setRobot(::rx(opm->canvasWidth * 0.5 + 30 * (i+1) * invertflag), ::ry(opm->canvasHeight - 60), i, color, M_PI_2 * (invertflag+1) + 0, false);
                paintCar(CAR_OFF[color], i, ::rx(opm->canvasWidth * 0.5 + 30 * (i+1) * invertflag), ::ry(opm->canvasHeight - 60), M_PI_2 * (invertflag+1), true, FONT_COLOR[color]);
            }
        }
    }
}
void Field::paintCarShadow(qreal x, qreal y, qreal radian) {
    static qreal radius = sipm->RobotRadius; //opm->carDiameter / 2.0;
    static qreal chordAngel = qRadiansToDegrees(qAsin(1.0 * sipm->CenterFromKicker / sipm->RobotRadius)); //qRadiansToDegrees(qAsin(2.0 * sipm->CenterFromKicker / opm->carDiameter)); //qRadiansToDegrees(qAcos(1.0 * opm->carFaceWidth / opm->carDiameter));
    pixmapPainter.setBrush(QBrush(QColor(255, 255, 255, 80)));
    pixmapPainter.setPen(Qt::NoPen);
//    pixmapPainter.drawLine(QPointF(::x(x), ::y(y)), QPointF(::x(x), ::y(y)) + QPointF(30 * qSin(radian + M_PI_2), 30 * qCos(radian + M_PI_2)));
    pixmapPainter.drawChord(QRectF(::x(x - radius), ::y(y - radius), ::w(2 * radius), ::h(2 * radius)), ::a(90.0 - chordAngel + 180 / M_PI * radian), ::r(180.0 + 2 * chordAngel));
}
void Field::paintBall(const QColor& color, qreal x, qreal y) {
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(QRectF(::x(x - sipm->BallRadius), ::y(y - sipm->BallRadius), ::w(sipm->BallRadius*2), ::h(sipm->BallRadius*2))); //pixmapPainter.drawEllipse(QRectF(::x(x - opm->ballDiameter / 2.0), ::y(y - opm->ballDiameter / 2.0), ::w(opm->ballDiameter), ::h(opm->ballDiameter)));
}
void Field::paintpredict() {
    pixmapPainter.setBrush(QBrush(Qt::black));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(::x(getpredict_x() - sipm->BallRadius), ::y(getpredict_y() - sipm->BallRadius), ::w(sipm->BallRadius*2), ::h(sipm->BallRadius*2)); //pixmapPainter.drawEllipse(::x(getpredict_x() - opm->ballDiameter / 2.0), ::y(getpredict_y() - opm->ballDiameter / 2.0), ::w(opm->ballDiameter), ::h(opm->ballDiameter));
}
void Field::paintShadow(const QColor& color, qreal x, qreal y) {
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(QRectF(::x(x - opm->shadowDiameter / 2.0), ::y(y - opm->shadowDiameter / 2.0), ::w(opm->shadowDiameter), ::h(opm->shadowDiameter)));
}
void Field::paintFocus(const QColor& color, qreal x, qreal y, qreal radian, qreal count) {
    static int length = 40;
    pixmapPainter.setBrush(Qt::NoBrush);
    pixmapPainter.setPen(QPen(color, ::w(30)));
    pixmapPainter.drawEllipse(QRectF(::x(x - radian), ::y(y - radian), ::w(2 * radian), ::h(2 * radian)));
    for(int i = 0; i < 4; i++) {
        pixmapPainter.drawLine(QPointF(::x(x + (radian + length)*qCos(count / 60.0 + i * M_PI / 2)), ::y(y + (radian + length)*qSin(count / 60.0 + i * M_PI / 2))), QPointF(::x(x + (radian - length)*qCos(count / 60.0 + i * M_PI / 2)), ::y(y + (radian - length)*qSin(count / 60.0 + i * M_PI / 2))));
    }
}
void Field::drawVision(const Owl::OriginMessage &vision, bool shadow) {
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        for(int j = 0; j < vision.robotSize[color]; j++) {
            auto& robot = vision.robot[color][j];
            if(!shadow) {
                paintCar(CAR_COLOR[color], robot.id, robot.pos.x(), robot.pos.y(), robot.angle, true, FONT_COLOR[color]);
            } else {
                paintShadow(CAR_SHADOW[color], robot.pos.x(), robot.pos.y());
            }
        }
    }
    //paintpredict();
    for(int j = 0; j < vision.ballSize; j++) {
        auto& ball = vision.ball[j];
        if(!shadow) {
            paintBall(COLOR_RED, ball.pos.x(), ball.pos.y());
        } else {
            paintShadow(COLOR_TRANSORANGE, ball.pos.x(), ball.pos.y());
        }
    }

}
void Field::drawCtrlC() {
    pixmapPainter.setFont(QFont("Helvetica [Cronyx]", 300, QFont::Bold));
    GlobalData::Instance()->ctrlCMutex.lock();
    bool ctrlC = GlobalData::Instance()->ctrlC;
    GlobalData::Instance()->ctrlCMutex.unlock();
    if(ctrlC) {
        pixmapPainter.drawText(QPointF(0, 300), "CTRL_C");
    }
    pixmapPainter.setFont(QFont("Helvetica [Cronyx]", 13, QFont::Bold));
}
void Field::drawSelectedArea() {
    pixmapPainter.setBrush(QBrush(COLOR_LIGHTWHITE));
    pixmapPainter.setPen(Qt::NoPen);
    float width = abs(GS->maximumX - GS->minimumX),
        height = abs(GS->maximumY - GS->minimumY);
    pixmapPainter.drawRect(QRectF(::x(GS->minimumX), ::y(GS->minimumY), ::w(width), ::h(height)));
}
void Field::drawDebugMessages(int team) {
    if (!opm->debug) return;
    static ZSS::Protocol::Debug_Msgs msgs;
    GlobalData::Instance()->debugMutex.lock();
    if (team == 0) {
        msgs.ParseFromArray(GlobalData::Instance()->debugBlueMessages.data(), GlobalData::Instance()->debugBlueMessages.size());
    } else {
        msgs.ParseFromArray(GlobalData::Instance()->debugYellowMessages.data(), GlobalData::Instance()->debugYellowMessages.size());
    }
//    qDebug() << "FUCK DEBUG MESSAGE SIZE" << msgs.ByteSize();
    GlobalData::Instance()->debugMutex.unlock();
    if (msgs.has_login_name() && msgs.login_name() != opm->LoginName)
        return;
//    qDebug() << "FUCK DEBUG SIZE" << msgs.msgs_size();
    pixmapPainter.setFont(QFont("Helvetica [Cronyx]", ::w(130), QFont::Normal)); //QFont::Bold));
    pixmapPainter.setBrush(QBrush(DEBUG_BRUSH_COLOR));
    for(int i = 0; i < msgs.msgs_size(); i++) {
        auto& msg = msgs.msgs(i);
        pixmapPainter.setPen(QPen(DEBUG_COLOR[msg.color()], ::w(10)));
        double radius;
        switch(msg.type()) {
        case ZSS::Protocol::Debug_Msg_Debug_Type_ARC:
            if (!opm->type_arc) break;
            radius = (msg.arc().rectangle().point2().x() - msg.arc().rectangle().point1().x()) / 2;
            pixmapPainter.drawArc(QRectF( ::x(double(msg.arc().rectangle().point1().x()) * 10),
                                          ::y(-double(msg.arc().rectangle().point1().y()) * 10),
                                          ::w(2 * radius * 10),
                                          ::h(- 2 * radius * 10)),
                                  msg.arc().start() * 16,
                                  msg.arc().end() * 16);

            break;
        case ZSS::Protocol::Debug_Msg_Debug_Type_LINE:
            if (!opm->type_line) break;
            pixmapPainter.drawLine(::x(msg.line().start().x() * 10), ::y(-msg.line().start().y() * 10), ::x(msg.line().end().x() * 10), ::y(-msg.line().end().y() * 10));
            break;
        case ZSS::Protocol::Debug_Msg_Debug_Type_Points: {
            if (!opm->type_points) break;
            QVector<QLine> lines;
            for(int i = 0; i < msg.points().point_size(); i++) {
                lines.push_back(QLine(::x(msg.points().point(i).x() + opm->debugPointSize * 10), ::y(-msg.points().point(i).y() + opm->debugPointSize * 10), ::x(msg.points().point(i).x() - opm->debugPointSize * 10), ::y(-msg.points().point(i).y() - opm->debugPointSize * 10)));
                lines.push_back(QLine(::x(msg.points().point(i).x() - opm->debugPointSize * 10), ::y(-msg.points().point(i).y() + opm->debugPointSize * 10), ::x(msg.points().point(i).x() + opm->debugPointSize * 10), ::y(-msg.points().point(i).y() - opm->debugPointSize * 10)));
            }
            pixmapPainter.drawLines(lines);
            break;
        }
        case ZSS::Protocol::Debug_Msg_Debug_Type_TEXT:
            if (!opm->type_text) break;
            pixmapPainter.drawText(QPointF(::x(msg.text().pos().x() * 10), ::y(-msg.text().pos().y() * 10)), QString::fromStdString(msg.text().text()));
            //if(Test::Instance()->testing && Test::Instance()->runScripts) {
            //    Test::Instance()->judgeStateMachine(QString::fromStdString(msg.text().text()));
            //}
            break;
        case ZSS::Protocol::Debug_Msg_Debug_Type_ROBOT:
            if (!opm->type_robot) break;
            pixmapPainter.drawEllipse(::x(msg.robot().pos().x() * 10 - sipm->RobotRadius), ::y(-msg.robot().pos().y() * 10 + sipm->RobotRadius), ::w((sipm->RobotRadius*2)), ::h(-(sipm->RobotRadius*2))); //pixmapPainter.drawEllipse(::x(msg.robot().pos().x() * 10 - opm->carDiameter / 2.0), ::y(-msg.robot().pos().y() * 10 + opm->carDiameter / 2.0), ::w((opm->carDiameter)), ::h(-(opm->carDiameter)));
            break;
        //case Owl::Protocol::Debug_Msg_Debug_Type_CURVE:
        //case Owl::Protocol::Debug_Msg_Debug_Type_POLYGON:
        default:
            qDebug() << "debug message type not support!";
        }
    }
}

float Field::fieldXFromCoordinate(int x) {
    return ::rx(x);
}
float Field::fieldYFromCoordinate(int y) {
    return ::ry(y);
}

void Field::reportStatus(){
    int cnt = 0;
    pixmapPainter.setBrush(Qt::NoBrush);
    pixmapPainter.setPen(QPen(FONT_COLOR[0], ::w(30)));
    for (int team = 0; team < PARAM::TEAMS; ++team) {
        for (int num = 0; num < PARAM::ROBOTMAXID; ++num) {
            if (GlobalData::Instance()->robotInformation[team][num].infrared) {
                cnt++;
                pixmapPainter.drawText(::x(team?-6550:5000), ::y(3000-cnt*500), (team?"YELLOW ":"BLUE ")+QString::number(num, 16).toUpper()+" infrared");
            }
        }
    }
    return;
    pixmapPainter.setBrush(QBrush(FONT_COLOR[0]));
    pixmapPainter.setPen(QPen(FONT_COLOR[0]));
    for (int team = PARAM::BLUE;team <= PARAM::YELLOW;team++)
        //for (int num = 0;num < 6;num++) {
        for (int id = 0;id < PARAM::ROBOTMAXID;id++) {
            //if ((id < PARAM::ROBOTMAXID) && (id >= 0))
                if (DealRobot::Instance()->visionProblem[team][id]) {
                    QString color = team==0?"BLUE":"YELLOW";
                    pixmapPainter.drawText(::x(4900), ::y(pow(-1,team)*(3350-id*200)), "Lost "+color+" "+QString::number(id,10));
                }
        }
}
// draw heat map
//Field::Heat::Heat(){
//}
//void Field::Heat::init(){
//    for(int i=0;i<COLOR_LEVEL;i++){
//        this->size[i] = 0;
//        for(int j=0;j<RECT_MAX_SUM;j++){
//            this->area[i][j].setSize(QSizeF(::w(RECT_SIZE),::h(RECT_SIZE)));
//        }
//    }
//    //test
//    for(int i=-6000;i<6000;i+=RECT_SIZE){
//        for(int j=-4500;j<4500;j+=RECT_SIZE){
//            auto color = (abs(i/RECT_SIZE) + abs(j/RECT_SIZE))%COLOR_LEVEL;
//            if(this->size[color] >= RECT_MAX_SUM)
//                continue;
//            this->area[color][this->size[color]].moveCenter(QPointF(::x(i),::y(j)));
//            this->size[color]++;
//        }
//    }
//}
void Field::receiveBlue(){
    QUdpSocket* receiverBlue = new QUdpSocket();
    if(!receiverBlue->bind(QHostAddress(cpm->local_address), cpm->blue_heat, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug()<<"Fail to bind blue heat";
    }
    auto& datagram = GlobalData::Instance()->blueHeatMap;
    //static OWL::Protocol::Heat_Map blueHeatMap;
    static OWL::Protocol::Heat_Map_New blueHeatMap;
    bool isRight = false;
    bool lastProcessControl = false;

    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500)); //微秒
        if (!lastProcessControl && GlobalData::Instance()->processControl[0])
            isRight = opm->isRight;
        lastProcessControl = GlobalData::Instance()->processControl[0];

        if (!opm->heatMap || _type != 2) continue;
        while (receiverBlue->state() == QUdpSocket::BoundState && receiverBlue->hasPendingDatagrams()) {
            datagram.resize(receiverBlue->pendingDatagramSize());
            receiverBlue->readDatagram(datagram.data(),datagram.size());
            blueHeatMap.ParseFromArray(datagram.data(), datagram.size());
            if (blueHeatMap.has_login_name() && blueHeatMap.login_name() != opm->LoginName)
                break;
            auto size = blueHeatMap.points_size();
            for(int i = 0; i < size; i++) {
                auto heatPoints = blueHeatMap.points(i);
                auto color = heatPoints.color();
                if(color < 0 || color >= COLOR_LEVEL) {
                    std::cerr << "Error : not correct color for heat: " << color << std::endl;
                    continue;
                }
                auto size = heatPoints.pos_size();
                auto c = limitRange((double)(color) / COLOR_LEVEL, 0.0, 1.0); // 确定颜色，化为RGB
                auto r = limitRange(4 * c - 2, 0.0, 1.0) * 255;
                auto g = limitRange(c < 0.5 ? 2 * c : 4 - 4 * c, 0.0, 1.0) * 255;
                auto b = limitRange(-2 * c + 1, 0.0, 1.0) * 255;
                heatPainter.setBrush(QColor(r, g, b));
                for(int k = 0; k < size; k++) {
                    auto pos = heatPoints.pos(k); // 以传入的点为端点画方框，减少复杂度
                    GlobalData::Instance()->blueHeatMutex.lock();
                    //heatPainter.drawRect(QRectF(::x(pos.x()*10), ::y(-pos.y()*10), ::w(RECT_SIZE), ::h(-RECT_SIZE)));
                    int point_num_width = opm->field_width / skpm->drawStep; //宽边可以绘制的点数
                    float pos_x = skpm->startPosX + int(pos / point_num_width) * skpm->drawStep; //mm，默认从左上角开始，纵向给点编号
                    float pos_y = skpm->startPosY + pos % point_num_width * skpm->drawStep;
                    if (isRight)
                        heatPainter.drawRect(QRectF(::x(-pos_x), ::y(pos_y), ::w(skpm->drawStep), ::h(-skpm->drawStep)));
                    else
                        heatPainter.drawRect(QRectF(::x(pos_x), ::y(-pos_y), ::w(skpm->drawStep), ::h(-skpm->drawStep)));

                    GlobalData::Instance()->blueHeatMutex.unlock();
                }
            }
        }
    }
}
void Field::receiveYellow(){
    QUdpSocket* receiverYellow = new QUdpSocket();
    if(!receiverYellow->bind(QHostAddress(cpm->local_address), cpm->yellow_heat, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug()<<"Fail to bind blue heat";
    }
    auto& datagram = GlobalData::Instance()->yellowHeatMap;
    //static OWL::Protocol::Heat_Map yellowHeatMap;
    static OWL::Protocol::Heat_Map_New yellowHeatMap;
    bool isRight = false;
    bool lastProcessControl = false;

    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        if (!lastProcessControl && GlobalData::Instance()->processControl[1])
            isRight = opm->isRight;
        lastProcessControl = GlobalData::Instance()->processControl[1];

        if (!opm->heatMap || _type != 3) continue;
        while (receiverYellow->state() == QUdpSocket::BoundState && receiverYellow->hasPendingDatagrams()) {
            datagram.resize(receiverYellow->pendingDatagramSize());
            receiverYellow->readDatagram(datagram.data(),datagram.size());
            yellowHeatMap.ParseFromArray(datagram.data(), datagram.size());
            if (yellowHeatMap.has_login_name() && yellowHeatMap.login_name() != opm->LoginName)
                break;
            auto size = yellowHeatMap.points_size();
            for(int i = 0; i < size; i++) {
                auto heatPoints = yellowHeatMap.points(i);
                auto color = heatPoints.color();
                if(color < 0 || color >= COLOR_LEVEL) {
                    std::cerr << "Error : not correct color for heat: " << color << std::endl;
                    continue;
                }
                auto size = heatPoints.pos_size();
                auto c = limitRange((double)(color) / COLOR_LEVEL, 0.0, 1.0); // 确定颜色，化为RGB
                auto r = limitRange(4 * c - 2, 0.0, 1.0) * 255;
                auto g = limitRange(c < 0.5 ? 2 * c : 4 - 4 * c, 0.0, 1.0) * 255;
                auto b = limitRange(-2 * c + 1, 0.0, 1.0) * 255;
                heatPainter.setBrush(QColor(r, g, b));
                for(int k = 0; k < size; k++) {
                    auto pos = heatPoints.pos(k); // 以传入的点为端点画方框，减少复杂度
                    GlobalData::Instance()->yellowHeatMutex.lock();
                    int point_num_width = opm->field_width / skpm->drawStep; //宽边可以绘制的点数
                    float pos_x = skpm->startPosX + int(pos / point_num_width) * skpm->drawStep; //mm，默认从左上角开始，纵向给点编号
                    float pos_y = skpm->startPosY + pos % point_num_width * skpm->drawStep;
                    if (isRight)
                        heatPainter.drawRect(QRectF(::x(-pos_x), ::y(pos_y), ::w(skpm->drawStep), ::h(-skpm->drawStep)));
                    else
                        heatPainter.drawRect(QRectF(::x(pos_x), ::y(-pos_y), ::w(skpm->drawStep), ::h(-skpm->drawStep)));

                    //heatPainter.drawRect(QRectF(::x(pos.x()*10), ::y(-pos.y()*10), ::w(RECT_SIZE), ::h(-RECT_SIZE)));
                    GlobalData::Instance()->yellowHeatMutex.unlock();
                }
            }
        }
    }
}
void Field::drawHeatMap(int team) {
    if(!opm->heatMap) return;
    auto& heat_mutex = team == PARAM::BLUE? GlobalData::Instance()->blueHeatMutex : GlobalData::Instance()->yellowHeatMutex;
    heat_mutex.lock();
    pixmapPainter.drawPixmap(0, 0, *heat_pixmap);
    heat_mutex.unlock();
}
//void Field::receiveHeat() {
//    heat_socket = new QUdpSocket();
//    heat_socket->bind(QHostAddress(ZSS::LOCAL_ADDRESS), 20003);
//    heat_mutex.lock();
//    heat_pixmap->fill(COLOR_DARKGREEN);
//    heat_mutex.unlock();
//    heatPainter.setPen(Qt::NoPen);
//    double c = 0;
//    double step = 0.0000001;
//    while(true) {
//        std::this_thread::sleep_for(std::chrono::microseconds(500));
//        QElapsedTimer timer;
//        timer.start();
//        for(int i=-6600;i<6600;i+=RECT_SIZE){
//            for(int j=-5000;j<5000;j+=RECT_SIZE){
//                c += step;
//                if(c >= 1 || c <= 0) step = - step;
//                c = limitRange(c,0.0,1.0);
//                auto r = limitRange(4*c-2,0.0,1.0)*255;
//                auto g = limitRange(c<0.5?2*c:4-4*c,0.0,1.0)*255;
//                auto b = limitRange(-2*c+1,0.0,1.0)*255;
//                heatPainter.setBrush(QColor(r,g,b));
//                heat_mutex.lock();
//                heatPainter.drawRect(QRectF(::x(i),::y(j),::w(RECT_SIZE),::h(RECT_SIZE)));
//                heat_mutex.unlock();
//            }
//        }
//        qDebug() << timer.nsecsElapsed()/1000000.0 << "millisecond";
//    }
//}
