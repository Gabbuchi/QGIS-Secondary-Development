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

QgsMapToolSelectFeatures::QgsMapToolSelectFeatures(QgsMapCanvas *mapCanvas)
    : QgsMapToolIdentify(mapCanvas)
{
}

//void QgsMapToolSelectFeatures::IsVectorLayer()
//{
//	//改进！只筛选出矢量图层 不然有栅格图层会报错退出
//	QList< QgsMapLayer * > 	layers;
//	//筛选出矢量图层
//	for (int i = 0; i < Templayers.size(); i++)
//	{
//		if (Templayers[i]->type() == QgsMapLayerType::VectorLayer)
//		{
//			layers.append(Templayers[i]);
//		}
//	}
//};




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
    if (mCanvas)
    {
        mCanvas->setSelectionColor(Qt::yellow);//设置颜色

        //改进！只筛选出矢量图层 不然有栅格图层会报错退出
        QList< QgsMapLayer * > 	Templayers = mCanvas->layers();
        QList< QgsMapLayer * > 	layers;
        //筛选出矢量图层
        for (int i = 0; i < Templayers.size(); i++)
        {
            if (Templayers[i]->type() == QgsMapLayerType::VectorLayer)
            {
                layers.append(Templayers[i]);
            }
        }
        /* QList< QgsMapLayer * > 	layers = mCanvas->layers();*/
        foreach(QgsMapLayer *l, layers)
        {
            QgsVectorLayer *l1 = qobject_cast<QgsVectorLayer*>(l);
            l1->removeSelection();
        }


    }

    //返回选中的结果
    QList<IdentifyResult> results = QgsMapToolIdentify::identify(mSelectGeometry, IdentifyMode::TopDownAll, AllLayers);
    //选择的Features集合
    QList<QgsFeature> selectFeatures;

    //显示出来

    Show_att_of_feature *attdlg =new Show_att_of_feature();
    for (int i = 0; i < results.count(); ++i)
    {

        //
        IdentifyResult feature_ = results.at(i);
        QStringList fieldnames =feature_.mFeature.fields().names();
        QgsAttributes values=feature_.mFeature.attributes();
        int fieldlength =fieldnames.length();

        attdlg->SetHeader(fieldnames);
        attdlg->Setvalues(fieldlength,values);
        //

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
    attdlg->show();

    //发出选中的Feature信息信号
    if (selectFeatures.count() > 0)
        emit sigSelectFeatureChange(selectFeatures);
}


