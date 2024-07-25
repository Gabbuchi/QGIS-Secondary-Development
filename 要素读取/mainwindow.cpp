#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapcanvas = new QgsMapCanvas(this);
    ui->verticalLayout->addWidget(mapcanvas);
    QString str = QString("/home/cjl/practice/qgis/proj1/tets1.qgz");
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
    //要素
    //初始化识别要素属性地图工具
    mpIdentifyTool = new mytesttool(mapcanvas);
    mpIdentifyTool->setAction(ui->actionFeatureCheck);
    //填充
    ui->toolBar->addAction(ui->actionfill);
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


//    QgsMapToolSelectFeatures* mapidentifyfeature = new QgsMapToolSelectFeatures(mapcanvas);
//    mapcanvas->setMapTool(mapidentifyfeature);

}

//QgsMapToolSelectFeatures* m_mapidentifyfeature = new QgsMapToolSelectFeatures(m_mapcanvas);
//    m_mapcanvas->setMapTool(m_mapidentifyfeature);

void MainWindow::on_actionPan_triggered()
{
    mapPanTool = new QgsMapToolPan(mapcanvas);
    ui->toolBar->addAction(ui->actionPan);
    mapcanvas->setMapTool(mapPanTool);//平移
}

void MainWindow::on_actioncoordinate_triggered()
{

}

void MainWindow::on_actionfeatureSelect_triggered()
{
    QgsMapToolSelectFeatures* mapidentifyfeature = new QgsMapToolSelectFeatures(mapcanvas);
    mapcanvas->setMapTool(mapidentifyfeature);
}

void MainWindow::on_actionfill_triggered()
{

}
