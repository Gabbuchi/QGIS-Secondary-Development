#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapcanvas = new QgsMapCanvas(this);
    ui->verticalLayout->addWidget(mapcanvas);
    QString str = QString("/home/cjl/practice/qgis/proj1/tets1.qgz");
    //QString str = QString("/home/cjl/practice/qgis/luwangproj/luwang.qgz");
    QgsProject::instance()->read(str);

    //链接画布和图层
    bridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(),mapcanvas,this);
    //读取vectorLayer
    ui->toolBar->addAction(ui->actionreadVectorLayer);
    ui->toolBar->addAction(ui->actionFeatureCheck);
    //平移工具
    ui->toolBar->addAction(ui->actionPan);
    //要素选择工具
    ui->toolBar->addAction(ui->actionfeatureSelect);
    //添加marker要素
    ui->toolBar->addAction(ui->actionaddMarker);
    //要素
    //初始化识别要素属性地图工具
    mpIdentifyTool = new mytesttool(mapcanvas);
    mpIdentifyTool->setAction(ui->actionFeatureCheck);
    //初始化layerTree
    layertreeview = new QgsLayerTreeView();
    layerMagDialog = new QDialog(this);
    QVBoxLayout* dialogLayout = new QVBoxLayout(layerMagDialog);
    dialogLayout->addWidget(layertreeview);
    QgsLayerTreeModel* layertreemodel = new QgsLayerTreeModel(QgsProject::instance()->layerTreeRoot(),this);
    layertreemodel->setFlag(QgsLayerTreeModel::AllowNodeChangeVisibility);
    layertreemodel->setFlag(QgsLayerTreeModel::ShowLegendAsTree);
    layertreeview->setModel(layertreemodel);
    ui->toolBar->addAction(ui->actionlayerView);
    //填充
    ui->toolBar->addAction(ui->actionStyle);
    //坐标变换
    //CoordinateReferenceSystem:坐标系参考系统
    //EPSG:4326 表示 WGS 84 坐标系(经纬度）
    //EPSG:900913 使用椭圆形球体（ellipsoidal sphere）的墨卡托投影（Mercator projection),主要用于在线地图服务（web），和EPSG:3857完全一致
    //似乎不需要转换？
    Crs = QgsCoordinateReferenceSystem(900913,QgsCoordinateReferenceSystem::EpsgCrsId);
    QgsCoordinateReferenceSystem epsg = QgsCoordinateReferenceSystem(4326,QgsCoordinateReferenceSystem::EpsgCrsId);
    coordinateTrans = QgsCoordinateTransform(Crs,epsg,QgsProject::instance());

    connect(mapcanvas,SIGNAL(xyCoordinates(QgsPointXY)),this,SLOT(showMousePoint(QgsPointXY)));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addVectorLayer()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open shape file"),"","*.shp");
    QgsVectorLayer *vecLayer = new QgsVectorLayer(filename,"test","ogr");
    if(vecLayer->isValid()){
        QgsProject::instance()->addMapLayer(vecLayer);
        mapcanvas->refresh();
    }else{
        QMessageBox::critical(this,"error","open ship file error");
    }
}

void MainWindow::showMousePoint(const QgsPointXY &p){
    //std::cout << p.x() << " " << p.y() << endl;
    QgsPointXY point = coordinateTrans.transform(p,QgsCoordinateTransform::ForwardTransform);
    ui->label->setText(QString("LONGITUDE:%1，LATITUDE:%2").arg(p.x()).arg(p.y()));
}

void MainWindow::on_actionreadVectorLayer_triggered()
{
    addVectorLayer();
}

void MainWindow::on_actionFeatureCheck_triggered()
{
        mapcanvas->setMapTool(mpIdentifyTool);

}

//QgsMapToolSelectFeatures* m_mapidentifyfeature = new QgsMapToolSelectFeatures(m_mapcanvas);
//    m_mapcanvas->setMapTool(m_mapidentifyfeature);

void MainWindow::on_actionPan_triggered()
{
    mapPanTool = new QgsMapToolPan(mapcanvas);
    ui->toolBar->addAction(ui->actionPan);
    mapcanvas->setMapTool(mapPanTool);//平移
}


void MainWindow::on_actionfeatureSelect_triggered()
{
    QPoint position = this->geometry().topRight();
    QgsMapToolSelectFeatures* mapidentifyfeature = new QgsMapToolSelectFeatures(mapcanvas,position);
    mapcanvas->setMapTool(mapidentifyfeature);
}

void MainWindow::on_actionStyle_triggered()
{
    StyleConfiguration* childWindow = new StyleConfiguration(mapcanvas);
    childWindow->show();
    //polygonOutlineMarkerSlot();
}



void MainWindow::on_actionlayerView_triggered()
{
    layerMagDialog->show();
}

void MainWindow::on_actionaddMarker_triggered()
{
    QgsField field1 =QgsField("id", QVariant::Int,"int",10,0);
    QgsField field2 =QgsField("name", QVariant::String,"String",10,0);
    QgsField field3 =QgsField("depth", QVariant::Double,"Double",10,2);
    QgsFields sumfield=QgsFields();
    sumfield.append(field1);
    sumfield.append(field2);
    sumfield.append(field3);

    const QgsCoordinateReferenceSystem crs=QgsCoordinateReferenceSystem("EPSG:4326"); //制定坐标系

    QgsVectorLayer* pointLayer = QgsMemoryProviderUtils::createMemoryLayer("mypoint",sumfield,QgsWkbTypes::MultiPoint,crs);//创建矢量图层
    pointLayer->startEditing(); // 设置图层状态为开始编辑
    QgsGeometry point = QgsGeometry::fromPointXY(QgsPointXY(110, 19));//pointgeometry
    QgsFeature feature; // 创建要素
    feature.setGeometry(point); // 将几何点设置为要素

    //设置要素属性值
    feature.setAttributes(QgsAttributes() << QVariant(3)<< QVariant("point1")<< QVariant(178.6));

    QgsVectorDataProvider* provider = pointLayer->dataProvider(); // 获取点图层的数据提供者的指针，用于添加要素
    provider->addFeature(feature); // 将点要素添加到矢量层
    pointLayer->commitChanges(); // 保存图层
    pointLayer->updateExtents(); // 更新图层
    QgsProject::instance()->addMapLayer(pointLayer);
    mapcanvas->setExtent(pointLayer->extent()); // 设置画布范围为当前图层的范围，也就是将图层平铺到画布
    mapcanvas->setVisible(true);
    mapcanvas->freeze(false);
    mapcanvas->refresh(); // 刷新画布


}

void MainWindow::on_pushButton_clicked()
{
    QgsField field1 =QgsField("id", QVariant::Int,"int",10,0);
    QgsField field2 =QgsField("name", QVariant::String,"String",10,0);
    QgsField field3 =QgsField("depth", QVariant::Double,"Double",10,2);
    QgsFields sumfield=QgsFields();
    sumfield.append(field1);
    sumfield.append(field2);
    sumfield.append(field3);

    const QgsCoordinateReferenceSystem crs=QgsCoordinateReferenceSystem("EPSG:4326"); //制定坐标系

    QgsVectorLayer* pointLayer = QgsMemoryProviderUtils::createMemoryLayer("mypoint",sumfield,QgsWkbTypes::MultiPoint,crs);//创建矢量图层
    pointLayer->startEditing(); // 设置图层状态为开始编辑
    //获取文本框的内容
    QString longitudein = ui->longitude->text();
    QString latitudein = ui->latitude->text();
    QgsGeometry point = QgsGeometry::fromPointXY(QgsPointXY(longitudein.toFloat(), latitudein.toFloat()));//pointgeometry
    QgsFeature feature; // 创建要素
    feature.setGeometry(point); // 将几何点设置为要素

    //设置要素属性值
    feature.setAttributes(QgsAttributes() << QVariant(3)<< QVariant("point1")<< QVariant(178.6));

    QgsVectorDataProvider* provider = pointLayer->dataProvider(); // 获取点图层的数据提供者的指针，用于添加要素
    provider->addFeature(feature); // 将点要素添加到矢量层
    pointLayer->commitChanges(); // 保存图层
    pointLayer->updateExtents(); // 更新图层
    QgsProject::instance()->addMapLayer(pointLayer);
    mapcanvas->setExtent(pointLayer->extent()); // 设置画布范围为当前图层的范围，也就是将图层平铺到画布
    mapcanvas->setVisible(true);
    mapcanvas->freeze(false);
    mapcanvas->refresh(); // 刷新画布
}
