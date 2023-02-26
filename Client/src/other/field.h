#ifndef __FIELD_H__
#define __FIELD_H__
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QMutex>
#include "messageformat.h"
#include "interaction.h"
#include <QInputDialog>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMainWindow>
#include <QApplication>
class Field : public QQuickPaintedItem{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType)
    Q_PROPERTY(bool draw READ ifDraw WRITE setDraw)
public:
    void paint(QPainter* painter) override;
    Field(QQuickItem *parent = 0);
    ~Field();
    inline int type() { return this->_type; }
    inline void setType(int t) { this->_type = t; }
    inline bool ifDraw() { return this->_draw; }
    inline void setDraw(bool t) { this->_draw = t; }
    static float fieldXFromCoordinate(int);
    static float fieldYFromCoordinate(int);
    static void setSize(int width,int height);
    double getpredict_x();
    double getpredict_y();

private slots:
    void updateScreen();
    void repaint();
//paint
private:
    void triggerDraw();
    void initPainterPath();
    void initField();
    void paintInit();
    void paintCar(const QColor& color,quint8 num,qreal x,qreal y,qreal radian
                ,bool ifDrawNum = true,const QColor& textColor = Qt::white,bool needCircle = false);
    void paintCarShadow(qreal x,qreal y,qreal radian);
    void paintOffCar();
    void paintBall(const QColor& color,qreal x,qreal y);
    void paintShadow(const QColor& color,qreal x,qreal y);
    void paintFocus(const QColor& color,qreal x,qreal y,qreal radian = 500,qreal count = 0);
    void drawOriginVision(int);
    void drawMaintainVision(int);
    void drawVision(const Owl::OriginMessage&,bool shadow = false);
    void paintpredict();
    void drawBallLine();
    QPixmap *pixmap;
    QPainter pixmapPainter;
    QMutex repaint_mutex;
    bool cameraMode;
    int _type;
    bool _draw;
//interaction
private:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void resetAfterMouseEvent();
    void leftPressEvent(QMouseEvent *);
    void leftMoveEvent(QMouseEvent *);
    void leftReleaseEvent(QMouseEvent *);
    void leftNoModifierPressEvent(QMouseEvent *);
    void leftNoModifierMoveEvent(QMouseEvent *);
    void leftNoModifierReleaseEvent(QMouseEvent *);
    void leftAltModifierPressEvent(QMouseEvent *);
    void leftAltModifierMoveEvent(QMouseEvent *);
    void leftAltModifierReleaseEvent(QMouseEvent *);
    void leftCtrlModifierPressEvent(QMouseEvent *);
    void leftCtrlModifierMoveEvent(QMouseEvent *);
    void leftCtrlModifierReleaseEvent(QMouseEvent *);
    void leftDoubleClickEvent(QMouseEvent * );
    void checkClosestBall(double,double);
    void rightPressEvent(QMouseEvent *);
    void rightMoveEvent(QMouseEvent *);
    void rightReleaseEvent(QMouseEvent *);
    void rightNoModifierPressEvent(QMouseEvent *);
    void rightNoModifierMoveEvent(QMouseEvent *);
    void rightNoModifierReleaseEvent(QMouseEvent *);
    void rightAltModifierPressEvent(QMouseEvent *);
    void rightAltModifierMoveEvent(QMouseEvent *);
    void rightAltModifierReleaseEvent(QMouseEvent *);
    void rightCtrlModifierPressEvent(QMouseEvent *);
    void rightCtrlModifierMoveEvent(QMouseEvent *);
    void rightCtrlModifierReleaseEvent(QMouseEvent *);
    void rightDoubleClickEvent(QMouseEvent *);
    void checkClosestRobot(double,double, bool include_off_robots = false);
    void middlePressEvent(QMouseEvent *);
    void middleMoveEvent(QMouseEvent *);
    void middleReleaseEvent(QMouseEvent *);
    void middleNoModifierPressEvent(QMouseEvent *);
    void middleNoModifierMoveEvent(QMouseEvent *);
    void middleNoModifierReleaseEvent(QMouseEvent *);
    void middleAltModifierPressEvent(QMouseEvent *);
    void middleAltModifierMoveEvent(QMouseEvent *);
    void middleAltModifierReleaseEvent(QMouseEvent *);
    void middleCtrlModifierPressEvent(QMouseEvent *);
    void middleCtrlModifierMoveEvent(QMouseEvent *);
    void middleCtrlModifierReleaseEvent(QMouseEvent *);
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent * event) override;
#endif
    int pressed;
    bool pressedRobot, pressedBall, pressedRobotMode;
    int robotID;
    int robotTeam;
    QPointF start,end;
    double displayData;
//message
private:
    void drawDebugMessages(int team);
    void drawCtrlC();
    void drawSelectedArea();
    void paintArc();
    void paintLine();
    void paintText();
    void paintCurve();
    void paintPolygon();
    void reportStatus();

    int ballFocusCount = 0;
// draw heat map
private:
    const static int RECT_SIZE = 100;// mm
    const static int RECT_MAX_SUM = 10000;
    const static int COLOR_LEVEL = 256;
//    struct Heat{
//        QRectF area[COLOR_LEVEL][RECT_MAX_SUM];
//        int size[COLOR_LEVEL];
//        Heat();
//        void init();
//    };
//    Heat heat;
    void receiveBlue();
    void receiveYellow();
    void drawHeatMap(int team);

    QPixmap *heat_pixmap;
    QPainter heatPainter;  

};

#endif // __FIELD_H__
