#ifndef FEATURE_H
#define FEATURE_H

#include <QMainWindow>

namespace Ui {
class feature;
}

class feature : public QMainWindow
{
    Q_OBJECT

public:
    explicit feature(QWidget *parent = nullptr);
    ~feature();

private:
    Ui::feature *ui;
};

#endif // FEATURE_H
