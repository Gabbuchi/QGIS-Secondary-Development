#ifndef FEATUREGET_H
#define FEATUREGET_H
#include <QMouseEvent>
#include "qgis/qgsmaptoolidentify.h"
#include "show_att_of_feature.h"
//属性识别地图工具的类
class mytesttool : public QgsMapToolIdentify
{
    Q_OBJECT
public:
    mytesttool( QgsMapCanvas * canvas );


    void canvasReleaseEvent(QgsMapMouseEvent *e) override;
};


#endif //FEATUREGET_H
