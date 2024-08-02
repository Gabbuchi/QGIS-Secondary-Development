#include "featureget.h"
#include "qgis/qgsmaptoolidentify.h"
#include "qgis/qgsmaptool.h"
#include "QMessageBox"
#include "qgsmaptoolselectfeatures.h"
#include<qgis/qgsfeature.h>
#include<qgis/qgsvectorlayer.h>
#include "identifyresultdlg.h"


 mytesttool::mytesttool( QgsMapCanvas * mapCanvas):QgsMapToolIdentify(mapCanvas)
 {

 }

void mytesttool::canvasReleaseEvent(QgsMapMouseEvent *e)
{
    IdentifyMode mode = QgsMapToolIdentify::LayerSelection; // 控制识别模式
    QList<IdentifyResult> results = QgsMapToolIdentify::identify( e->x(), e->y(), mode ); // 这句返回识别结果

    {
        IdentifyResult feature = results.at( 0 );
        QStringList fieldnames =feature.mFeature.fields().names();
        QgsAttributes values=feature.mFeature.attributes();
        int fieldlength =fieldnames.length();
        Show_att_of_feature *attdlg =new Show_att_of_feature();
        attdlg->SetHeader(fieldnames);
        attdlg->Setvalues(fieldlength,values);
        attdlg->show();
    }
}

