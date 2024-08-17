#ifndef STYLECONFIGURATION_H
#define STYLECONFIGURATION_H

#include <QWidget>
#include <qgis/qgssinglesymbolrenderer.h>
#include <qgis/qgslinesymbollayer.h>
#include <qgis/qgssymbol.h>
#include <qgis/qgsfillsymbol.h>
#include <qgis/qgslinesymbol.h>
#include <qgis/qgssymbol.h>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgsvectorlayer.h>
#include <qgis/qgsinterpolatedlinerenderer.h>
#include <qgis/qgsarrowsymbollayer.h>
#include <qgis/qgsfillsymbollayer.h>
#include <qgis/qgslinesymbollayer.h>
#include <qgis/qgsmarkersymbollayer.h>
#include <qgis/qgspallabeling.h>
#include <qgis/qgsvectorlayerlabeling.h>
#include <qgis/qgscallout.h>
namespace Ui {
class StyleConfiguration;
}

class StyleConfiguration : public QWidget
{
    Q_OBJECT
public:
    QgsMapCanvas *mapcanvas;

public:
    explicit StyleConfiguration(QgsMapCanvas* mapcanvas_, QWidget *parent = nullptr);
    ~StyleConfiguration();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::StyleConfiguration *ui;
};

#endif // STYLECONFIGURATION_H
