#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgslayertreemapcanvasbridge.h>
#include "ui_mainwindow.h"
#include <qgis/qgsproject.h>
#include <qgis/qgsvectorlayer.h>
#include <QDebug>
#include <qgis/qgseditorwidgetregistry.h>
#include <QFileDialog>
#include <QMessageBox>
#include <qgis/qgspointxy.h>
#include <qgis/qgsmaptoolpan.h>
#include <qgis/qgscoordinatetransform.h>
#include <qgis/qgscoordinatereferencesystem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QgsMapCanvas *mapcanvas;
    QgsLayerTreeMapCanvasBridge *bridge;
    QgsMapToolPan *mapPanTool;
    QgsCoordinateTransform coordinateTrans;
    QgsCoordinateReferenceSystem Crs;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addVectorLayer();
    void featureCheck();



private slots:

    void on_actionreadVectorLayer_triggered();

    void on_actionFeatureCheck_triggered();

    void on_actionPan_triggered();

    void on_actioncoordinate_triggered();

    void showMousePoint(const QgsPointXY &p);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
