#ifndef TOOLSVIEW_H
#define TOOLSVIEW_H

#include <QDialog>

namespace Ui {
class ToolsView;
}

class QToolButton;
class ToolsView : public QDialog
{
    Q_OBJECT

public:
    explicit ToolsView(QWidget *parent = 0);
    ~ToolsView();

    void showDirView();
    void showRecordView();
    void hideDirView();
    void hideRecordView();
    void setCameraEnable(bool ok);

signals:
    void triggered(int id, bool ok);

public slots:
    void showDialog();
    void hideDialog();
    void finishOption();

private:
    Ui::ToolsView *ui;
    bool m_isShow;
    bool m_cameraEnable;

    QToolButton *m_pCurToolButton;
    void initializeWidget();
};

#endif // TOOLSVIEW_H
