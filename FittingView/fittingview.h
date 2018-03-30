#ifndef FITTINGVIEW_H
#define FITTINGVIEW_H

#include <QFrame>
#include <QMap>

namespace Ui {
class FittingView;
}

class FsDialog;
class PlotView;
class RecordView;
class QTableWidget;
class QTableWidgetItem;
class SettingDataModel;
class FittingView : public QFrame
{
    Q_OBJECT

public:
    explicit FittingView(QWidget *parent = 0);
    ~FittingView();

    void installPlotView(PlotView *plot) {
        m_pPlotView = plot;
    }

    void installRecordView(RecordView *recordView) {
        m_pRecordView = recordView;
    }

signals:
    void readySaveFile(QString filename, QStringList data);

public slots:
    void insert(int id, SettingDataModel *sModel);
    QString import(QString headerStr, QString recordStr,
                   QVector<double> x, QVector<double> y, QVector<int> c, QVector<QString> f);//lt:f是dataview传递进入的测量数据

    void restart();
    void clear();

private slots:
    void itemSelected(QTableWidgetItem* item);
    void updateByRow(int id);
    void fit();
    void remove();
    void updateUnit(QString unit);

private:
    Ui::FittingView *ui;
    FsDialog *m_pFsDialog;
    PlotView *m_pPlotView;
    RecordView *m_pRecordView;
    QMap<QString, QString> m_infoMap;

    QString m_r2Str;
    QStringList m_fitCoefList;
    QString m_fitUnit;
    QString m_preUnit;
    QStringList m_unitStrList;
    QString m_currentdatafile;//ltjs:当前拟合的文件名

    void createRecord();
    void clearPlotView();
    void drawCurve(QVector<double> x, QVector<double> y);
    void updatePlotView(QString text);
    void updateTableByUnit(QTableWidget *tableWidget, QString unit);
    void insertRow(QTableWidget *tableWidget, QStringList dataList);

    QString funcStr();
    double yValue(double x);
    void limitValues(QVector<double> data, double &max, double &min);
    void curveValues(double start, double end, QVector<double> &x, QVector<double> &y);

    QString transformUnit(QString unit);
    int transformCoef(QString unit);

    void tableValues(QTableWidget *tableWidget, QVector<double> &x, QVector<double> &y);
    void removeAll(QTableWidget *tableWidget);
    void removeSelectedRow(QTableWidget *tableWidget);

    void initializeSystem();
    void initializeWidget();
    void writemeasuredata( QString filename, QStringList dataList);//ltj:写测量数据到data文件
};

#endif // FITTINGVIEW_H
