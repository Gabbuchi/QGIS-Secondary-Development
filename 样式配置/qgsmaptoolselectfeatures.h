#ifndef QGSMAPTOOLSELECTFEATURES_H
#define QGSMAPTOOLSELECTFEATURES_H

#include <QObject>
#include <QList>
#include <QScopedPointer>
#include <qmath.h>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgsmaptoolidentify.h>
#include <qgis/qgsrubberband.h>
#include <qgis/qgsmapmouseevent.h>
#include "show_att_of_feature.h"
class QgsMapToolSelectFeatures : public QgsMapToolIdentify
{
    Q_OBJECT
public:
    QgsMapToolSelectFeatures(QgsMapCanvas *mapCanvas);
protected:
    //重写鼠标移动
    void canvasMoveEvent(QgsMapMouseEvent *e) override;
    //重写鼠标按下
    void canvasPressEvent(QgsMapMouseEvent *e) override;
    //重写鼠标抬起
    void canvasReleaseEvent(QgsMapMouseEvent *e) override;

    void initRubberBand();
    void identifyFromGeometry();
    void IsVectorLayer();
signals:
    //发出选中的要素信号
    void sigSelectFeatureChange(QList<QgsFeature>);
private:
    // 是否正在选择
    bool mSelectionActive = false;
    QScopedPointer<QgsRubberBand> mSelectionRubberBand;
    QColor mFillColor = QColor(254, 178, 76, 63);
    QColor mStrokeColor = QColor(254, 58, 29, 100);
    QPoint mInitDragPos;
    //选择的Geometry
    QgsGeometry mSelectGeometry;
    QList< QgsMapLayer * > 	Templayers;
};

#endif // QGSMAPTOOLSELECTFEATURES_H
