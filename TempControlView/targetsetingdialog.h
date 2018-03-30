#ifndef TARGETSETINGDIALOG_H
#define TARGETSETINGDIALOG_H

#include <QDialog>

namespace Ui {
class TargetSetingDialog;
}

class TargetSetingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TargetSetingDialog(QWidget *parent = 0);
    ~TargetSetingDialog();

signals:
    void targetChanged(double target);

public slots:
    void okBtnClicked();

private:
    Ui::TargetSetingDialog *ui;
};

#endif // TARGETSETINGDIALOG_H
