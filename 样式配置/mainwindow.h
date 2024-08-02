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
#include <QWidget>
#include "identifyresultdlg.h"
#include "qgsmaptoolselectfeatures.h"
#include "show_att_of_feature.h"
#include "featureget.h"
#include "styleconfiguration.h"
#include <qgis/qgssinglesymbolrenderer.h>
#include <qgis/qgslinesymbollayer.h>
#include <qgis/qgssymbol.h>
#include <qgis/qgsfillsymbol.h>
#include <qgis/qgssymbol.h>
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
    //测试，改变样式
    void polygonOutlineMarkerSlot();


private slots:

    void on_actionreadVectorLayer_triggered();

    void on_actionFeatureCheck_triggered();

    void on_actionPan_triggered();

    void on_actioncoordinate_triggered();

    void showMousePoint(const QgsPointXY &p);

    void on_actionfeatureSelect_triggered();

    void on_actionStyle_triggered();

private:
    Ui::MainWindow *ui;
    StyleConfiguration* styleconfiguration;
    mytesttool *mpIdentifyTool;//识别要素工具

    //feature *featurewindow;
    //QgsMapToolSelectFeatures* features;
};
#endif // MAINWINDOW_H
