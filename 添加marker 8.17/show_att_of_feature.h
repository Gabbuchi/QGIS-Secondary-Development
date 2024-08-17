#ifndef SHOW_ATT_OF_FEATURE_H
#define SHOW_ATT_OF_FEATURE_H

#include <QWidget>
#include "qstandarditemmodel.h"
#include "qgis/qgsattributes.h"
#include <QPoint>
namespace Ui {
class Show_att_of_feature;
}

class Show_att_of_feature : public QWidget
{
    Q_OBJECT

public:
    explicit Show_att_of_feature(QWidget *parent = nullptr);
    ~Show_att_of_feature();
    void SetHeader(QStringList items);
    void Setvalues(int a,QgsAttributes values);
    void SetPopPosition(QPoint point);
private:
    Ui::Show_att_of_feature *ui;
    QPoint popPosition;
    QStandardItemModel *feature_model;



};

#endif // SHOW_ATT_OF_FEATURE_H

