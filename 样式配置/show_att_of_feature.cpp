#include "show_att_of_feature.h"
#include "ui_show_att_of_feature.h"


Show_att_of_feature::Show_att_of_feature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_att_of_feature)
{
    ui->setupUi(this);
    feature_model = new QStandardItemModel();

}

Show_att_of_feature::~Show_att_of_feature()
{
    delete ui;
}

//设置字段名
void Show_att_of_feature::SetHeader(QStringList items)
{
   feature_model->setHorizontalHeaderLabels(items);
    ui->tableView->setModel(feature_model);
}

//设置属性值
void Show_att_of_feature::Setvalues(int a,QgsAttributes values)
{
    feature_model->insertRows(0,1); //插入一行
    for(int field=0;field<=a-1;field++)
    {
        feature_model->setData(feature_model->index(0,field), values.value(field));
    }
    ui->tableView->setModel(feature_model);

}

