#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qgis/qgsproject.h>
#include <qgis/qgsvectorlayer.h>
#include <QDebug>
#include <qgis/qgseditorwidgetregistry.h>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mapcanvas = new QgsMapCanvas(this);
    ui->verticalLayout->addWidget(mapcanvas);
    QString str = QString("/home/cjl/practice/qgis/proj1/tets1.qgz");
    QgsProject::instance()->read(str);
    QVector<QgsVectorLayer*> vecLayers = QgsProject::instance()->layers<QgsVectorLayer*>();

//    QList<QgsMapLayer*>layers;
//    layers.append(vecLayers[0]);
//    mapcanvas -> setLayers(layers);
    QgsEditorWidgetRegistry a;
    a.initEditors(mapcanvas);
    bridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(),mapcanvas,this);
    ui->toolBar->addAction(ui->actionopenRastLayer);
    ui->toolBar->addAction(ui->actionopenVectorLayer);
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

void MainWindow::addRastLayer()
{

}


void MainWindow::on_actionopenVectorLayer_triggered()
{
    addVectorLayer();
}

void MainWindow::on_actionopenRastLayer_triggered()
{

}
