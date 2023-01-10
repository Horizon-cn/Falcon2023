#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H
#include <QObject>
#include "geometry.h"
#include <singleton.h>
class CGlobalSettings : public QObject{
    Q_OBJECT
public:
    CGlobalSettings(QObject *parent = 0);
    bool inChosenArea(float x, float y);
    bool inChosenArea(CGeoPoint);
    void setArea(float,float,float,float);
    void resetArea();
    void setBallPlacementPos(float,float);
    CGeoPoint saoConvert(CGeoPoint);
    double saoConvert(double);

    float minimumX,maximumX,minimumY,maximumY;
    float ballPlacementX,ballPlacementY;

signals:
    void needRepaint();
};
typedef Falcon::MeyersSingleton<CGlobalSettings> GlobalSettings;
#endif // GLOBALSETTINGS_H
