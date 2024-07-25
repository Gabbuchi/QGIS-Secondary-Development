#include "feature.h"
#include "ui_feature.h"

feature::feature(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::feature)
{
    ui->setupUi(this);
}

feature::~feature()
{
    delete ui;
}
