#ifndef IDENTIFYRESULTDLG_H
#define IDENTIFYRESULTDLG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QAbstractItemView>
namespace Ui {
class IdentifyResultDlg;
}

class IdentifyResultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit IdentifyResultDlg(QWidget *parent = nullptr);
    ~IdentifyResultDlg();
    void InitialDlg();
    void InitialData(QList<QMap<QString, QString>>);
private:
    Ui::IdentifyResultDlg *ui;
    QStandardItemModel *fieldmodel;
};

#endif // IDENTIFYRESULTDLG_H
