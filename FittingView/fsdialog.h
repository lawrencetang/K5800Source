#ifndef FSDIALOG_H
#define FSDIALOG_H

#include <QDialog>

namespace Ui {
class FsDialog;
}

class FsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FsDialog(QWidget *parent = 0);
    ~FsDialog();

    void showView(int id, QString concStr, QString unitStr);
    QString unitStr();
    QString concStr();

signals:
    void settingOk(int id);

private slots:
    void hideView();

private:
    Ui::FsDialog *ui;
    int m_rowId;

    void initializeSystem();
    void initializeWidget();

};

#endif // FSDIALOG_H
