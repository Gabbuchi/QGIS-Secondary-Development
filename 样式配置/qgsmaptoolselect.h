#ifndef QGSMAPTOOLSELECT_H
#define QGSMAPTOOLSELECT_H

#include "mainwindow.h"
#include "identifyresultdlg.h"
#include <qgis/qgsrubberband.h>
#include <qgis/qgsgeometry.h>
#include <qgis/qgswkbtypes.h>
#include "qgsmaptoolselectfeatures.h"
class QgsMapToolSelect : public QgsMapTool{
    Q_OBJECT;
public:
    QgsMapToolSelect(QgsMapCanvas*);
    ~QgsMapToolSelect(void);
public:
    void SetSelectLayer(QgsVectorLayer*);
    void SetEnable(bool);//设定工具状态
    //获取属性和属性值
    QList<QMap<QString, QString>> GetAttributeValue(QgsVectorLayer *layer, QgsFeatureIds selectedFIds);
    void setShowFlag(bool flag);
    IdentifyResultDlg* ResultDlg();
private:
    QgsVectorLayer* pLayer;
    QgsFeatureIds LayerSelectedFeatures;//存储要素标识符
    bool StatusFlag;
    QList<QMap<QString, QString>> list;//存储选择后的要素
    bool isShowFlag;//是否选择了shp图层
    IdentifyResultDlg* mIdentifyResultDlg;
private:
    void ExpandSelectRangle(QRect &Rect,QPoint Point);
    //将指定的设备坐标区域转换成地图坐标区域
    void SetRubberBand(QRect &selectRect,QgsRubberBand *);
    //选择图层要素
    QgsMapToolSelectFeatures* SetSelectFeatures;

};

#endif // QGSMAPTOOLSELECT_H
