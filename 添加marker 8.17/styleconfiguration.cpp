#include "styleconfiguration.h"
#include "ui_styleconfiguration.h"

StyleConfiguration::StyleConfiguration(QgsMapCanvas* mapcanvas_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleConfiguration)
{
    ui->setupUi(this);
    mapcanvas = mapcanvas_;

}

StyleConfiguration::~StyleConfiguration()
{
    delete ui;
}


void StyleConfiguration::on_pushButton_clicked()
{
    QgsMapLayer* mplayer = mapcanvas->layer(0);
    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
    //从图层获取渲染器
    QgsFeatureRenderer * layerRenderer= veclayer->renderer();
    QgsSingleSymbolRenderer *singleSymbolRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    //需要包含qgssymbollayer.h，继承自qgslinesymbollayer
        //改这里
    auto markerSymbolLayer = new QgsSimpleLineSymbolLayer(true,3);
    markerSymbolLayer->setColor(QColor(123,123,123));
    markerSymbolLayer->setPenStyle(Qt::DashLine);
    markerSymbolLayer->setWidth(0.5);
    //多个Symbol Layer构成一个Symbol
    QgsSymbolLayerList layerList;
    layerList << markerSymbolLayer;
    auto fillSymbol = new QgsFillSymbol(layerList);
    singleSymbolRenderer->setSymbol(fillSymbol);
    veclayer->setRenderer(singleSymbolRenderer);
}

void StyleConfiguration::on_pushButton_2_clicked()
{
    QgsMapLayer* mplayer = mapcanvas->layer(0);
    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
    //从图层获取渲染器
    QgsFeatureRenderer * layerRenderer= veclayer->renderer();
    QgsSingleSymbolRenderer *singleSymbolRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    //需要包含qgssymbollayer.h，继承自qgslinesymbollayer
        //改这里
    auto markerSymbolLayer = new QgsMarkerLineSymbolLayer(true,3);

    //多个Symbol Layer构成一个Symbol
    QgsSymbolLayerList layerList;
    layerList << markerSymbolLayer;
    auto fillSymbol = new QgsFillSymbol(layerList);
    singleSymbolRenderer->setSymbol(fillSymbol);
    veclayer->setRenderer(singleSymbolRenderer);
}

void StyleConfiguration::on_pushButton_3_clicked()
{
    QgsMapLayer* mplayer = mapcanvas->layer(0);
    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
    //从图层获取渲染器
    QgsFeatureRenderer * layerRenderer= veclayer->renderer();
    QgsSingleSymbolRenderer *singleSymbolRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    //需要包含qgssymbollayer.h，继承自qgslinesymbollayer
        //改这里
    auto markerSymbolLayer = new QgsInterpolatedLineSymbolLayer();

    //多个Symbol Layer构成一个Symbol
    QgsSymbolLayerList layerList;
    layerList << markerSymbolLayer;
    auto fillSymbol = new QgsFillSymbol(layerList);
    singleSymbolRenderer->setSymbol(fillSymbol);
    veclayer->setRenderer(singleSymbolRenderer);
}

void StyleConfiguration::on_pushButton_4_clicked()
{
    QgsMapLayer* mplayer = mapcanvas->layer(0);
    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
    //从图层获取渲染器
    QgsFeatureRenderer * layerRenderer= veclayer->renderer();
    QgsSingleSymbolRenderer *singleSymbolRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    //需要包含qgssymbollayer.h，继承自qgslinesymbollayer
    //改这里
    auto markerSymbolLayer = new QgsLinePatternFillSymbolLayer();
    //多个Symbol Layer构成一个Symbol
    QgsSymbolLayerList layerList;
    layerList << markerSymbolLayer;
    auto fillSymbol = new QgsFillSymbol(layerList);
    singleSymbolRenderer->setSymbol(fillSymbol);
    veclayer->setRenderer(singleSymbolRenderer);
}

void StyleConfiguration::on_pushButton_5_clicked()
{
    QgsMapLayer* mplayer = mapcanvas->layer(0);
    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
    //从图层获取渲染器
    QgsFeatureRenderer * layerRenderer= veclayer->renderer();
    QgsSingleSymbolRenderer *singleSymbolRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    //需要包含qgssymbollayer.h，继承自qgslinesymbollayer
    //改这里
    auto markerSymbolLayer = new QgsSimpleFillSymbolLayer();
    markerSymbolLayer->setStrokeColor(QColor(123,123,123));
    //多个Symbol Layer构成一个Symbol
    QgsSymbolLayerList layerList;
    layerList << markerSymbolLayer;
    auto fillSymbol = new QgsFillSymbol(layerList);
    singleSymbolRenderer->setSymbol(fillSymbol);
    veclayer->setRenderer(singleSymbolRenderer);
}


void StyleConfiguration::on_pushButton_6_clicked()
{
    //设置图层显示标签

//    QgsMapLayer* mplayer = mapcanvas->layer(0);
//    QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
//            // 首先是定义一个 QgsPalLayerSettings 变量，并启用他的属性设置
//            QgsPalLayerSettings layerSettings;
//            layerSettings.drawLabels = true;
//            //根据API文档中的属性，进行自定义配置
//            //layerSettings.fieldName = mplayer->fields()[5].name(); // 设置Label图层与标注字段
//            layerSettings.centroidWhole = true; //设置位置参考的中心点
//            layerSettings.isExpression = true;
//            layerSettings.placement = QgsPalLayerSettings::OverPoint;
//            layerSettings.yOffset = 2.5;
//            // Label 字体设置:轮廓buffer设置
//            QgsTextBufferSettings buffersettings;
//            buffersettings.setEnabled(true);
//            buffersettings.setSize(1);
//            buffersettings.setColor(QColor(255, 0, 0));
//            //字体阴影
//            QgsTextShadowSettings shadowsetings;
//            shadowsetings.setEnabled(true);
//            shadowsetings.setOffsetAngle(135);
//            shadowsetings.setOffsetDistance(1);
//            //字体格式
//            QgsTextFormat textformat;
//            QFont font("SimSun", 5, 5, false);
//            font.setUnderline(false);
//            textformat.setFont(font);
//            textformat.setBuffer(buffersettings);
//            textformat.setShadow(shadowsetings);
//            layerSettings.setFormat(textformat);
//            QgsVectorLayerSimpleLabeling* labeling = new QgsVectorLayerSimpleLabeling(layerSettings);

//            mplayer->setLabeling(labeling);
//            layer->setLabelsEnabled(true);
//            QgsProject::instance()->addMapLayer(layer);  //这句话加不加的话无法在图层控制器中显示
//            mapCanvas->setExtent(layer->extent());
//            layers.append(layer);
//            mapCanvas->setLayers(layers);
//            mapCanvas->freeze(false);
//            mapCanvas->refresh();

//        //添加一个线图层
//        QgsMapLayer* mplayer = mapcanvas->layer(0);
//        QgsVectorLayer *veclayer = qobject_cast<QgsVectorLayer*>(mplayer);
//        QgsPalLayerSettings settings;
//        settings.drawLabels = true;
//        settings.fieldName = "name";
//        //文字设置
//        QgsTextFormat textFormat;
//        QgsTextBackgroundSettings backgroundSettings;
//        QgsTextBufferSettings bufferSettings;
//        QgsTextMaskSettings maskSettings;
//        QgsTextShadowSettings shadowSettings;
//        //开启背景并设置为白色
//        backgroundSettings.setEnabled(true);
//        backgroundSettings.setFillColor(QColor("white"));
//        textFormat.setBackground(backgroundSettings);
//        //开启buffer并设置颜色为黑色
//        bufferSettings.setEnabled(true);
//        bufferSettings.setColor(QColor("black"));
//        textFormat.setBuffer(bufferSettings);
//        //开启mask并设置size
//        maskSettings.setEnabled(true);
//        maskSettings.setSize(1.0);
//        textFormat.setMask(maskSettings);
//        //开启shadow
//        shadowSettings.setEnabled(true);
//        shadowSettings.setColor(QColor("red"));
//        textFormat.setShadow(shadowSettings);
//        settings.setFormat(textFormat);
//        //设置callout
//        auto callout = new QgsBalloonCallout();
//        settings.setCallout(callout);
//        //设置位置
////        QgsLabelPlacementSettings placementSettings;
////        placementSettings.setAllowDegradedPlacement(true);
////        settings.setPlacementSettings(placementSettings);

//        QgsVectorLayerSimpleLabeling* simpleLabeling = new QgsVectorLayerSimpleLabeling(settings);
//        mplayer->setLabelsEnabled(true);
//        mplayer->setLabeling(simpleLabeling);
//    }

}

void StyleConfiguration::on_pushButton_7_clicked()
{
    //预计开发修改路网线路颜色功能
}
