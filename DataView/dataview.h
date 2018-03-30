#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QFrame>
#include <QMap>
#include <QListView>
#include <QVBoxLayout>


namespace Ui {
class DataView;
}

class QListWidgetItem;
class OListscroll;
class DataView : public QFrame
{
    Q_OBJECT

public:
    explicit DataView(QString systemPath, bool supportCuvette = true, QWidget *parent = 0);
    ~DataView();

    QMap<QString, QString> getViewTitle();

signals:
    void dirChanged(QString name);
    void fileReadReady(QString type, QString filename);

public slots:
    void setCurrentDir(QString name);
    void showDataFile(QString dirname);
    void updateView(QString dirname);

    void itemSelected(QListWidgetItem *item);
    void saveDataFile(QStringList data);
    void saveDataFile(QString filename, QStringList data);

    void remove();
    void moveTo();

private:
    Ui::DataView *ui;
    QString m_systemPath;
    bool m_supportCuvette;
    OListscroll *m_poscorllArea;
    QVBoxLayout *m_pdvlayout;


    QMap<QString, int> m_dirMap;
    QMap<QString, QString> m_viewTitle;

    void insert(QString filename);

    void initializeSystem();
    void initializeWidget();
    bool m_leftButtonPressed;
    QPoint m_originalPoint;
    QPoint m_originalPointBackup;
};

#endif // DATAVIEW_H
