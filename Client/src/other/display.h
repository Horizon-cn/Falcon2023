#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QMutex>
#include <QPainterPath>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMainWindow>
#include <QApplication>
class Display : public QQuickPaintedItem{
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType)
public:
    static void initAxes();
    Q_INVOKABLE void resetSize(int,int);
    void paint(QPainter* painter) override;
    Display(QQuickItem *parent = 0);
    inline int type() { return this->_type; }
    inline void setType(int t) { this->_type = t; }
    Q_INVOKABLE void ifNeedDisplay(bool);
    Q_INVOKABLE void setDisplayMode();
    Q_INVOKABLE int getDisplayHeight();
    virtual ~Display() {}
public slots:
    void draw();
private slots:
    void repaint();
private:
    void init();
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent* event) override;
#endif
private:
    void paintAxes();
    void paintData();
private:
    float x();
    float y();
private:
    int _type;
    bool display;
    QPixmap *pixmap;
    QPainter pixmapPainter;
    QRect area;
    QMutex repaint_mutex;
    QPainterPath axesPath;
    QPen pen;
};

#endif // __DISPLAY_H__
