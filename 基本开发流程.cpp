1. 初始化 QGIS 应用程序和 Qt 环境
//初始化 QApplication：
//初始化 QGIS 应用程序：
2. 加载数据文件和创建图层
//读取数据文件
QString filePath = QString("/home/cjl/practice/qgis/proj1/tets1.qgz");
//创建矢量图层
QgsVectorLayer *vectorLayer = new QgsVectorLayer(filePath, "Layer Name", "ogr");
if (!vectorLayer->isValid()) {
    qDebug() << "Layer failed to load!";
    return;
}
//将图层添加到地图项目中
QgsMapLayerRegistry::instance()->addMapLayer(vectorLayer);
3. 显示地图数据
//创建地图画布
QgsMapCanvas *mapCanvas = new QgsMapCanvas();
//将图层添加到地图画布
mapCanvas->setExtent(vectorLayer->extent());
mapCanvas->setLayerSet(QList<QgsMapLayer*>() << vectorLayer);
//在界面中显示地图画布
QMainWindow mainWindow;
mainWindow.setCentralWidget(mapCanvas);
mainWindow.show();
...
