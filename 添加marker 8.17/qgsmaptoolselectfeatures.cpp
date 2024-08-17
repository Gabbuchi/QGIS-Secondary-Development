#include "qgsmaptoolselectfeatures.h"
#include"qgis/qgsmaptoolidentify.h"
#include "qgis/qgsapplication.h"
#include "qgis/qgsvectorlayer.h"
#include<QMessageBox>
#include<qgis/qgsfeature.h>
#include<qgis/qgsvectorlayer.h>
#include<qgis/qgsrectangle.h>
#include<QMouseEvent>
#include<QMessageBox>

QgsMapToolSelectFeatures::QgsMapToolSelectFeatures(QgsMapCanvas *mapCanvas,QPoint point)
    : QgsMapToolIdentify(mapCanvas),popPosition(point)
{
}

void QgsMapToolSelectFeatures::canvasMoveEvent(QgsMapMouseEvent * e)
{
    if (e->buttons() != Qt::LeftButton)
        return;
    QRect rect;
    if (!mSelectionActive)
    {
        mSelectionActive = true;
        rect = QRect(e->pos(), e->pos());
    }
    else
    {
        rect = QRect(e->pos(), mInitDragPos);
    }
    if (mSelectionRubberBand)
        mSelectionRubberBand->setToCanvasRectangle(rect);
}

void QgsMapToolSelectFeatures::canvasPressEvent(QgsMapMouseEvent * e)
{
    if (!mSelectionRubberBand)
        initRubberBand();
    mInitDragPos = e->pos();
}

void QgsMapToolSelectFeatures::canvasReleaseEvent(QgsMapMouseEvent * e)
{

    QPoint point = e->pos() - mInitDragPos;
    //点
    if (!mSelectionActive || (point.manhattanLength() < QApplication::startDragDistance()))
    {

        mSelectionActive = false;
        mSelectGeometry = QgsGeometry::fromPointXY(toMapCoordinates(e->pos()));
        identifyFromGeometry();
    }
    //矩形
    if (mSelectionRubberBand && mSelectionActive)
    {
        mSelectGeometry = mSelectionRubberBand->asGeometry();
        mSelectionRubberBand.reset();
        identifyFromGeometry();
    }
    mSelectionActive = false;
}

void QgsMapToolSelectFeatures::initRubberBand()
{
    mSelectionRubberBand.reset(new QgsRubberBand(mCanvas, QgsWkbTypes::PolygonGeometry));
    mSelectionRubberBand->setFillColor(mFillColor);
    mSelectionRubberBand->setStrokeColor(mStrokeColor);
}

void QgsMapToolSelectFeatures::identifyFromGeometry()
{
QMessageBox msgBox;


    //返回选中的结果
    QList<IdentifyResult> results = QgsMapToolIdentify::identify(mSelectGeometry, IdentifyMode::TopDownAll, AllLayers);
    //IdentifyMode::可选选择模式
    //选择的Features集合
    QList<QgsFeature> selectFeatures;

    //显示出来

    Show_att_of_feature *attdlg =new Show_att_of_feature();
    for (int i = 0; i < results.count(); ++i)
    {
        IdentifyResult feature_ = results.at(i);
        QStringList fieldnames =feature_.mFeature.fields().names();
        QgsAttributes values=feature_.mFeature.attributes();
        int fieldlength =fieldnames.length();

        attdlg->SetHeader(fieldnames);
        attdlg->Setvalues(fieldlength,values);


        if (results.at(i).mLayer->type() == QgsMapLayerType::RasterLayer) return; //防止点在栅格图层上报错

        QgsVectorLayer *layer = qobject_cast<QgsVectorLayer*>(results.at(i).mLayer);
        QgsFeatureIds ids;
        for (IdentifyResult var : results)
        {
            QgsFeature _Feature = var.mFeature;
            ids.insert(_Feature.id());
        }

        if (ids.count() > 0) layer->selectByIds(ids);
        QgsFeature feature = results.at(i).mFeature;
        selectFeatures.append(feature);
    }
    attdlg->move(popPosition);//出现在主窗口右侧
    attdlg->show();

    //发出选中的Feature信息信号
    if (selectFeatures.count() > 0)
        emit sigSelectFeatureChange(selectFeatures);
}


