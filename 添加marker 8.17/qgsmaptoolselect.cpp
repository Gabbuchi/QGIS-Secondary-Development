#include "qgsmaptoolselect.h"

//构造和析构函数
QgsMapToolSelect::QgsMapToolSelect(QgsMapCanvas *Mapcanvas):QgsMapTool(Mapcanvas)
{
   pLayer=NULL;
   mCursor=Qt::ArrowCursor;
   mCanvas=Mapcanvas;
   StatusFlag=true;
   isShowFlag = true;
   mIdentifyResultDlg = NULL;
   SetSelectFeatures = new QgsMapToolSelectFeatures(Mapcanvas);
}

QgsMapToolSelect::~QgsMapToolSelect(void)
{
}
//设置当前被选择(活动)的图层
void QgsMapToolSelect::SetSelectLayer(QgsVectorLayer *Layer)
{
   pLayer=Layer;
}

//提取鼠标位置一定范围作为选择区域
void QgsMapToolSelect::ExpandSelectRangle(QRect &Rect,QPoint Point)
{
   int boxSize=0;

//   //如果图层不是面图元类型
   if(!QgsWkbTypes::isMultiType(pLayer->wkbType())){
       boxSize=5;
   }
   else{
       boxSize=1;
   }
   //设置选择区域
   Rect.setLeft(Point.x()-boxSize);
   Rect.setRight(Point.x()+boxSize);
   Rect.setTop(Point.y()-boxSize);
   Rect.setBottom(Point.y()+boxSize);
}
//将指定的设备坐标区域转换成地图坐标区域
void QgsMapToolSelect::SetRubberBand(QRect &selectRect,QgsRubberBand *pRubber)
{
    //得到当前坐标变换对象
    const QgsMapToPixel* transform=mCanvas->getCoordinateTransform();
    //将区域设备坐标转换成地图坐标
    QgsPointXY ll=transform->toMapCoordinates(selectRect.left(),selectRect.bottom());
    QgsPointXY ur = transform->toMapCoordinates(selectRect.right(),selectRect.top());
    pRubber->reset();
    //将区域的4个角点添加到QgsRubberBand对象中
    pRubber->addPoint(ll,false );
    pRubber->addPoint(QgsPoint(ur.x(), ll.y()),false );
    pRubber->addPoint(ur,false );
    pRubber->addPoint(QgsPoint( ll.x(), ur.y() ),true );
}

//设定工具状态
void QgsMapToolSelect::SetEnable(bool flag)
{
    StatusFlag=flag;
    if(StatusFlag){
        mCursor=Qt::CrossCursor;
    }
    else{
        mCursor=Qt::ArrowCursor;
    }
}

IdentifyResultDlg * QgsMapToolSelect::ResultDlg()
{
    if (mIdentifyResultDlg == NULL)
    {
        mIdentifyResultDlg = new IdentifyResultDlg;
    }
    return mIdentifyResultDlg;
}

//得到选择的要素的属性信息
//QList<QMap<QString, QString>> QgsMapToolSelect::GetAttributeValue( QgsVectorLayer *layer, QgsFeatureIds selectedFIds )
//{
////	QStringList strAttribute;
//    QMap<QString, QString> featureValue;
//    QList<QMap<QString, QString>> featureValues;
//    int i = 0, nFeatureCount = 0, nFieldsCount = 0;
//    if (layer == NULL)
//    {
//        return featureValues;
//    }
//    QgsFeatureList featurelist = layer->selectedFeatures();
//    nFeatureCount = featurelist.size();
//    QgsFeature feature;
//    QString fieldName, fieldValue;
////	vector<QgsField> myFields = layer->fields();
//    for (i = 0; i < nFeatureCount; i++)
//    {
//        feature = featurelist.at(i);
//        const QgsAttributeMap &attributes = feature.attributeMap();
//        nFieldsCount = attributes.count();
//        const QgsFieldMap &fields = layer->pendingFields();//从图层得到字段信息
//        QgsField field;
//        for(int j = 0; j < nFieldsCount; j++)
//        {
//            field = fields[j];
//            fieldName = field.name();

//            fieldValue = attributes[j].toString();
//            featureValue.insert(fieldName, fieldValue);
//        }
//        featureValues.push_back(featureValue);
//    }
//    return featureValues;
//}

void QgsMapToolSelect::setShowFlag( bool flag )
{
    isShowFlag = flag;
}
