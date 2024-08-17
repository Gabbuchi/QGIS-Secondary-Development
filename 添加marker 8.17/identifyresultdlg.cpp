#include "identifyresultdlg.h"
#include "ui_identifyresultdlg.h"

IdentifyResultDlg::IdentifyResultDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IdentifyResultDlg)
{
    ui->setupUi(this);
    QStringList lists;
    InitialDlg();
}

IdentifyResultDlg::~IdentifyResultDlg()
{
    delete ui;
}

void IdentifyResultDlg::InitialDlg()
{
    this->setWindowTitle(tr("查询要素属性信息"));
    fieldmodel = new QStandardItemModel();
    fieldmodel->setColumnCount(2);

    ui->tableView->setModel(fieldmodel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    ui->tableView->verticalHeader()->hide(); //列头不显示
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选择整行高亮
    setWindowFlags(Qt::WindowStaysOnTopHint);//使窗口置顶
    this->resize( 240, 300);
}
//将数据显示在表格中
void IdentifyResultDlg::InitialData( QList<QMap<QString, QString>> datas)
{
    fieldmodel->clear();//注意：在clear之后，表头名称也被清除了，需再设置表头
    fieldmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("属性名称")));
    fieldmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("属性值")));

    QString name, value;
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (i = 0; i < datas.count(); i ++)
    {
        QMap<QString,QString> data = datas.at(i);
        int j = 0;
        for (it = data.begin(),  j = 0; it != data.end(), j < data.count(); ++it, ++j)
        {
            int index = i * data.count() +j;
            fieldmodel->setItem(index, 0, new QStandardItem(it.key()));
            if (it.value() == NULL)
            {
                it.value() = "0";
            }
            fieldmodel->setItem(index, 1, new QStandardItem(it.value()));
            fieldmodel->item(index, 0)->setTextAlignment(Qt::AlignCenter);
            fieldmodel->item(index, 1)->setTextAlignment(Qt::AlignCenter);
            if ( j%(data.count()) == 0)
            {
                fieldmodel->item(index, 0)->setBackground(QBrush(QColor(188, 188, 188)));
                fieldmodel->item(index, 1)->setBackground(QBrush(QColor(188, 188, 188)));
            }
        }
    }
}
