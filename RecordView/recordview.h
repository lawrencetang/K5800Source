#ifndef RECORDVIEW_H
#define RECORDVIEW_H

#include <QFrame>
#include <QMap>
#include <QVBoxLayout>

namespace Ui {
class RecordView;
}

class QTableWidget;
class OTablescroll;
class RecordView : public QFrame
{
    Q_OBJECT

public:
    explicit RecordView(QString path, QWidget *parent = 0);
    ~RecordView();

    QString headerLabels();

signals:
    void moveCoef(double coef);
    void clearid();
    void sampleLEchange(QString text);
    void sendConcValue(QString text);

public slots:
    void setRecordDir(QString dir);
    void insertRecord(QString recordStr);

    void save();
    void move();
    void hideRow();
    void hideColumn();
    void clear();
private:
    Ui::RecordView *ui;
    QString m_currentDir;
    QString m_systemPath;
    OTablescroll *m_poscorllArea;
    QVBoxLayout *m_pdvlayout;

    void saveRecord(QString recordStr);
    void setHeaderLabels(QString headerStr);
    void removeAll();

    void insert(QStringList record, int row);
    bool updateRecord(QStringList data);
    bool updateRecord(QMap<QString, QString> data);

    void readRecord(QString filename);
    void createRecordFile(QString path, QString flagStr);
    void clearRecord();

    void initializeSystem();
    void initializeWidget();
};

#endif // RECORDVIEW_H
