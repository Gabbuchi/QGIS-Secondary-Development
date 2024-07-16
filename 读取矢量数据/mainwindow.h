#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgslayertreemapcanvasbridge.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QgsMapCanvas *mapcanvas;
    QgsLayerTreeMapCanvasBridge *bridge;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addVectorLayer();
    void addRastLayer();

private slots:
    void on_actionopenVectorLayer_triggered();

    void on_actionopenRastLayer_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
