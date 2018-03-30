#include "fittingview.h"
#include "ui_fittingview.h"

#include <QDir>
#include <QtMath>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QMessageBox>

#include "fit.h"
#include "fsdialog.h"
#include "../PlotView/plotview.h"
#include "../RecordView/recordview.h"
#include "../DataModel/absodatamodel.h"
#include "../DataModel/settingdatamodel.h"

FittingView::FittingView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FittingView) {
    ui->setupUi(this);
    initializeSystem();
    initializeWidget();
}

FittingView::~FittingView() {
    delete ui;
}

/**
 * @brief FittingView::insert
 * @param sModel
 */
void FittingView::insert(int id, SettingDataModel *sModel) {

    if (sModel->baseValue( "measure" ) == "Kit Method") {

        QString blStr = sModel->methodValue( "wave" );
        AbsoDataModel *aModel = sModel->absoModel();
        QString absoStr = aModel->absorbance( blStr );

        QString concStr;
        QTableWidget *tableWidget;
        if (0 == ui->toolBox->currentIndex()) {
            concStr = "0";
            tableWidget = ui->fittingTableWidget;
        } else {
            if (m_fitCoefList.isEmpty()) {
                QMessageBox::warning( this, tr( "Warning" ),
                                      tr( "Please fit first!" ), QMessageBox::Ok);
                return;
            }
            concStr = QString::number( yValue( absoStr.toDouble() ) );
            tableWidget = ui->measureTableWidget;
        }

        QStringList dataList;
        dataList.append( absoStr );
        dataList.append( concStr );
        dataList.append( QString::number( id + 1 ) );
        insertRow( tableWidget, dataList );
        if (0 != ui->toolBox->currentIndex()) {
            dataList.insert(0, "\n");
            writemeasuredata( m_currentdatafile, dataList );
        }

        m_infoMap.clear();
        m_infoMap["id"] = sModel->baseValue( "id" );
        m_infoMap["name"] = sModel->baseValue( "name" );
        m_infoMap["measure"] = sModel->baseValue( "measure" );
        m_infoMap["type"] = sModel->methodValue( "type" );
        m_infoMap["wave"] = sModel->methodValue( "wave" );
    }
}

/**
 * @brief FittingView::import
 * @param headerStr
 * @param recordStr
 * @param x
 * @param y
 * @param c
 * @return
 */
QString FittingView::import(QString headerStr, QString recordStr,
                            QVector<double> x, QVector<double> y, QVector<int> c, QVector<QString> f) {

    QStringList headerList = headerStr.split( ",", QString::SkipEmptyParts );//lt:f是dataview传递进入的测量数据
    QStringList recordList = recordStr.split( ",", QString::SkipEmptyParts );
    QMap<QString, QString> rcdMap;
    //qDebug()<<f[1];
    int size = recordList.size();
    for (int i = 0; i < headerList.size(); i ++) {
        if (i < size) {
            rcdMap.insert( headerList.at( i ), recordList.at( i ) );
        } else {
            rcdMap.insert( headerList.at( i ), "NULL" );
        }
    }

    QString unitStr = rcdMap.value( "Unit" );
    int index = m_unitStrList.indexOf( unitStr );
    if (index < 0) {
        return tr( "File is damaged!" );
    }

    QString orderStr = rcdMap.value( "Fit-Order" );
    int count = ui->typeComboBox->count();
    int order = orderStr.toInt();
    if (order <= 0 || order > count) {
        return tr( "File is damaged!" );
    }

    QString typeStr = rcdMap.value( "Type" );
    QString waveStr = rcdMap.value( "Wave" );

    ui->unitComboBox->setCurrentIndex( index );
    ui->typeComboBox->setCurrentIndex( order - 1 );

    QString coefStr = rcdMap.value( "Fit-Coef" );
    m_fitCoefList = coefStr.split( ";", QString::SkipEmptyParts );
    m_r2Str = rcdMap.value( "Fit-R^2" );

    clear();
    QStringList dataList;
    for (int i = 0; i < x.size(); i ++) {
        dataList.clear();
        dataList.append( QString::number( x.at( i ) ) );
        dataList.append( QString::number( y.at( i ) ) );
        dataList.append( QString::number( c.at( i ) ) );
        insertRow( ui->fittingTableWidget, dataList );
    }
    QStringList fitmeasuredata;
    for (int i = 0; i<f.size(); i++) {
        fitmeasuredata.clear();
        fitmeasuredata.append( f.at( 0 ));
        fitmeasuredata.append( f.at( 1 ));
    }
    insertRow( ui->measureTableWidget, fitmeasuredata );

    // 获取样本数据
    QVector<double> xSamples;
    QVector<double> ySamples;
    tableValues( ui->fittingTableWidget, xSamples, ySamples );
    // 作图
    clearPlotView();
    drawCurve( xSamples, ySamples );

    m_infoMap.clear();
    m_infoMap["id"] = rcdMap.value( "ID" );
    m_infoMap["name"] = rcdMap.value( "Name" );
    m_infoMap["measure"] = rcdMap.value( "Measure" );
    m_infoMap["type"] = typeStr;
    m_infoMap["wave"] = waveStr;

    return "Success";
}

/**
 * @brief FittingView::restart
 */
void FittingView::restart() {
    // 删除表格中的数据
    removeAll( ui->fittingTableWidget );
    removeAll( ui->measureTableWidget );

    // 清空数据曲线
    clearPlotView();

    // 清空拟合信息
    m_fitCoefList.clear();
    m_r2Str.clear();
    m_infoMap.clear();

    // 初始化单位转换
    m_preUnit = ui->unitComboBox->currentText();
    m_fitUnit = m_preUnit;
}

/**
 * @brief FittingView::clear
 */
void FittingView::clear() {
    removeAll( ui->fittingTableWidget );
    removeAll( ui->measureTableWidget );
}

/**
 * @brief FittingView::itemSelected
 * @param item
 */
void FittingView::itemSelected(QTableWidgetItem *item) {
    int row = ui->fittingTableWidget->row( item );
    QString concStr = ui->fittingTableWidget->item( row, 1 )->text();
    QString unitStr = ui->unitComboBox->currentText();
    m_pFsDialog->showView( row, concStr, unitStr );
}

/**
 * @brief FittingView::updateByRow
 * @param id
 */
void FittingView::updateByRow(int id) {
    QString concStr = m_pFsDialog->concStr();
    QString unitStr = m_pFsDialog->unitStr();

    double conc = concStr.toDouble() * transformUnit( unitStr ).toDouble();
    concStr = QString::number( conc );

    QList<QTableWidgetItem *> usedItems = ui->fittingTableWidget->findItems( concStr, Qt::MatchFixedString );
    if (!usedItems.isEmpty()) {
        if (id == ui->fittingTableWidget->row( usedItems.first() ) ) {
            return;
        }
        int result = QMessageBox::warning(this, tr( "Warning" ),
                                          tr( "Do you want to merge?" ),
                                          QMessageBox::Ok|QMessageBox::Cancel);
        if ( QMessageBox::Ok == result) {

            for (int i = 0; i < usedItems.size(); i ++) {
                QTableWidgetItem *item = usedItems.at( i );
                int row = ui->fittingTableWidget->row( item );
                double value1 = ui->fittingTableWidget->item( row, 0 )->text().toDouble();
                double value2 = ui->fittingTableWidget->item( id, 0 )->text().toDouble();
                double value = (value1 + value2)/2;
                ui->fittingTableWidget->item( row, 0 )->setText( QString::number( value ) );
            }
            if (id != -1) {
                ui->fittingTableWidget->removeRow( id );
            }
        }
        return;
    }

    QTableWidgetItem *item = ui->fittingTableWidget->item( id, 1 );
    item->setText( concStr );
}

/**
 * @brief FittingView::fit 执行拟合操作
 */
void FittingView::fit() {

    int rowCount = ui->fittingTableWidget->rowCount();
    if (0 == rowCount) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("No data to fit!"), QMessageBox::Ok);
        return;
    }

    if (m_infoMap.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Data lose!"), QMessageBox::Ok);
        return;
    }

    updatePlotView( "Kit Method" );

    // 获取样本数据
    QVector<double> x;
    QVector<double> y;
    tableValues( ui->fittingTableWidget, x, y );
    int order = ui->typeComboBox->currentIndex() + 2;

    // 执行拟合
    QList<double> fitCeofs;
    int ok = CalFit( x, y, x.size(), order, &fitCeofs );
    if (0 != ok) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Fit error!"), QMessageBox::Ok);
        return;
    }
    // 获取r2
    double r2 = 0.0;
    ok = CalAvgVar( x, y, x.size(), order, fitCeofs, &r2 );
    if (0 != ok) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Fit error!"), QMessageBox::Ok);
        return;
    }
    // 保存全局变量
    m_r2Str.clear();
    m_fitCoefList.clear();
    m_r2Str = QString::number( r2 );
    for (int i = 0; i < fitCeofs.size(); i ++) {
        m_fitCoefList.append( QString::number( fitCeofs.at( i ) ) );
    }
    m_fitUnit = ui->unitComboBox->currentText();

    // 绘制波形
    clearPlotView();
    drawCurve( x, y );
    // 保存文件
    createRecord();
}

/**
 * @brief FittingView::remove
 */
void FittingView::remove() {
    QTableWidget *tableWidget = NULL;
    if (0 == ui->toolBox->currentIndex()) {
        tableWidget = ui->fittingTableWidget;
    } else {
        tableWidget = ui->measureTableWidget;
    }

    removeSelectedRow( tableWidget );
}

/**
 * @brief FittingView::updateUnit
 * @param unit
 */
void FittingView::updateUnit(QString unit) {

    // 更新table中的数据
    updateTableByUnit( ui->fittingTableWidget, m_preUnit );
    updateTableByUnit( ui->measureTableWidget, m_preUnit );

    if (!m_fitCoefList.isEmpty()) {
        // 获取样本数据
        QVector<double> xSamples;
        QVector<double> ySamples;
        tableValues( ui->fittingTableWidget, xSamples, ySamples );

        // 更新图形曲线
        clearPlotView();
        drawCurve( xSamples, ySamples );
    }
    // 更新单位
    m_preUnit = unit;
}

/**
 * @brief FittingView::createRecord
 */
void FittingView::createRecord() {

    if (NULL != m_pRecordView) {

        QString recordStr = "record:,";
        recordStr.append( m_infoMap[ "id" ] );
        recordStr.append( "," );
        recordStr.append( m_infoMap[ "name" ] );
        recordStr.append( "," );
        recordStr.append( m_infoMap[ "measure" ] );
        recordStr.append( "," );
        recordStr.append( m_infoMap[ "type" ] );
        recordStr.append( "," );
        recordStr.append( m_infoMap[ "wave" ] );
        recordStr.append( "," );
        recordStr.append( ui->unitComboBox->currentText() );
        recordStr.append( "," );
        recordStr.append( funcStr() );
        recordStr.append( "," );
        recordStr.append( QString::number( ui->typeComboBox->currentIndex() + 1 ) );
        recordStr.append( "," );
        recordStr.append( m_r2Str );

        QString fitCoefStr;
        int size = m_fitCoefList.size();
        for (int i = 0; i < m_fitCoefList.size(); i ++) {
            fitCoefStr.append( m_fitCoefList.at( i ) );
            if (i < size - 1) {
                fitCoefStr.append( ";" );
            }
        }
        recordStr.append( "," );
        recordStr.append( fitCoefStr );
        QString filename = QDateTime::currentDateTime().toString("yyMMddhhmmss") + ".csv";
        recordStr.append( "," );
        recordStr.append( filename );
        m_currentdatafile = filename;

        QString tempStr = recordStr;
        m_pRecordView->insertRecord( tempStr.replace( "record:,", "" ) );
        QString headerStr = "header:,";
        headerStr.append( m_pRecordView->headerLabels() );

        QStringList dataList;
        dataList.append( headerStr );
        dataList.append( recordStr );
        QTableWidget *tableWidget = ui->fittingTableWidget;
        int rowCount = tableWidget->rowCount();
        for (int r = 0; r < rowCount; r ++) {
            QTableWidgetItem *itemX = tableWidget->item( r, 0 );
            QTableWidgetItem *itemY = tableWidget->item( r, 1 );
            QTableWidgetItem *itemC = tableWidget->item( r, 2 );

            QString xStr = itemX->text();
            QString yStr = itemY->text();
            QString cStr = itemC->text();

            dataList.append( QString( "data:,%1,%2,%3" ).arg( xStr ).arg( yStr ).arg( cStr ) );
        }
        readySaveFile( filename, dataList );
    }
}

/*
 *
 * ltj:写测量数据到data文件
 *
 */
void FittingView::writemeasuredata(QString filename, QStringList dataList) {
    //qDebug()<<dataList.at(0);
    readySaveFile( filename, dataList );
}

/**
 * @brief FittingView::clearPlotView
 */
void FittingView::clearPlotView() {
    if (NULL != m_pPlotView) {
        // 清空曲线以及marker
        m_pPlotView->clearCurves();
        m_pPlotView->clearPointMarker();
    }
}

/**
 * @brief FittingView::drawCurve
 * @param x
 * @param y
 */
void FittingView::drawCurve(QVector<double> x, QVector<double> y) {
    if (NULL != m_pPlotView) {
        if (x.isEmpty()) {
            return;
        }
        // 获取拟合曲线上的数据
        QVector<double> xCurve, yCurve;
        double max = 0.0, min = 0.0;
        limitValues( x, max, min );
        curveValues( min, max, xCurve, yCurve );

        // 更新plot的title
        QString title = "Function:" + funcStr();
        m_pPlotView->setPlotTitle( title );

        // 更新y轴的坐标
        QString ytext = QString( "concentration(%1)" ).arg( ui->unitComboBox->currentText() );
        m_pPlotView->setYAxisText( ytext );

        // 先画离散点再画拟合曲线
        m_pPlotView->drawDiscretePoint( x, y );
        m_pPlotView->drawFitCurve( xCurve, yCurve );
    }
}

/**
 * @brief FittingView::updatePlotView
 * @param text
 */
void FittingView::updatePlotView(QString text)
{
    QString filename = QDir::currentPath() + "/configure/plot.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    QString title = configIniReader->value( QString("/%1/title").arg( text ) ).toString();
    QString xAxisText = configIniReader->value( QString("/%1/xAxisText").arg( text ) ).toString();
    QString yAxisText = configIniReader->value( QString("/%1/yAxisText").arg( text ) ).toString();

    int xAxisMinVaule = configIniReader->value( QString("/%1/xAxisMinVaule").arg( text ) ).toInt();
    int xAxisMaxVaule = configIniReader->value( QString("/%1/xAxisMaxVaule").arg( text ) ).toInt();

    int yAxisMinVaule = configIniReader->value( QString("/%1/yAxisMinVaule").arg( text ) ).toInt();
    int yAxisMaxVaule = configIniReader->value( QString("/%1/yAxisMaxVaule").arg( text ) ).toInt();

    int scaleCount = configIniReader->value( QString("/%1/scaleCount").arg( text ) ).toInt();

    m_pPlotView->setTitle( title );
    m_pPlotView->setXAxisText( xAxisText );
    m_pPlotView->setYAxisText( yAxisText );

    m_pPlotView->uninstallPlotZoomer();
    m_pPlotView->setAxisScale( QwtPlot::xBottom, xAxisMinVaule, xAxisMaxVaule );
    m_pPlotView->setAxisScale( QwtPlot::yLeft, yAxisMinVaule, yAxisMaxVaule );
    m_pPlotView->installPlotZoomer();
    m_pPlotView->addSacleMarker( scaleCount );

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief FittingView::updateTableByUnit 根据单位更新Table中的数据
 * @param tableWidget table
 * @param unit 单位
 */
void FittingView::updateTableByUnit(QTableWidget *tableWidget, QString unit) {
    QString coefStr = transformUnit( unit );
    if ("NULL" == coefStr) {
        return;
    }
    int index = 1;
    int rowCount = tableWidget->rowCount();
    for (int r = 0; r < rowCount; r ++) {
        QTableWidgetItem *item = tableWidget->item( r, index );
        double value = coefStr.toDouble()*item->text().toDouble();
        item->setText( QString::number( value ) );
    }
}

/**
 * @brief FittingView::insertRow
 * @param tableWidget
 * @param dataList
 */
void FittingView::insertRow(QTableWidget *tableWidget, QStringList dataList) {
    int rowCount = tableWidget->rowCount();
    int columnCount = tableWidget->columnCount();
    tableWidget->insertRow( rowCount );

    int size = dataList.size();
    for (int c = 0; c < columnCount; c ++) {

        QString itemStr;
        if (c < size) {
            itemStr = dataList.at( c );
        } else {
            itemStr = "NULL";
        }
        QTableWidgetItem *item = new QTableWidgetItem( itemStr );
        item->setTextColor( Qt::blue );
        item->setFont( QFont( "微软雅黑", 9 ) );
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        tableWidget->setItem( rowCount, c, item );
    }
}

/**
 * @brief FittingView::funcStr 获取拟合函数如y=a+bx形式的字符串
 * @return 字符串
 */
QString FittingView::funcStr() {
    QString str;
    if (m_unitStrList.isEmpty()) {
        return str;
    }
    str.append( "y=" );
    int size = m_fitCoefList.size();
    for(int i = 0; i < size; i ++) {
        if (i < size -1) {
            str.append( QString( "%1x^%2+" ).arg( m_fitCoefList.at( i ) ).arg( size - i - 1 ) );
        } else {
            str.append( QString( "%1" ).arg( m_fitCoefList.at( i ) ) );
        }
    }
    return str;
}

/**
 * @brief FittingView::yValue 根据拟合公式,输入x输出y
 * @param x 输入
 * @return 输出
 */
double FittingView::yValue(double x) {
    double y = 0.0;
    int size = m_fitCoefList.size();
    for (int i = 0; i < size; i ++) {
        QString fitCoefStr = m_fitCoefList.at( i );
        y += qPow( x, size - i - 1 ) * fitCoefStr.toDouble();
    }
    return y;
}

/**
 * @brief FittingView::limitValues 获取队列的上下限值
 * @param data 队列(输入)
 * @param max 上限(输出)
 * @param min 下限(输出)
 */
void FittingView::limitValues(QVector<double> data,
                              double &max, double &min) {
    double minValue = 10000.0;
    double maxValue = -10000.0;
    int size = data.size();
    for (int i = 0; i < size; i ++) {
        double value = data.at( i );
        if (value < minValue) {
            minValue = value;
        }
        if (value > maxValue) {
            maxValue = value;
        }
    }
    max = maxValue;
    min = minValue;
}

/**
 * @brief FittingView::curveValues 根据上下限获取曲线上的点(用于画图)
 * @param start 起始点
 * @param end 终止点
 * @param x x坐标
 * @param y y坐标
 */
void FittingView::curveValues(double start, double end,
                              QVector<double> &x, QVector<double> &y) {
    x.clear();
    y.clear();
    QString coefStr = transformUnit( m_fitUnit );
    if ("NULL" == coefStr) {
        return;
    }

    double width = end - start;
    double xMin = start - width * 0.1;
    double xMax = end + width * 0.1;

    int size = 100;
    double step = (xMax - xMin)/size;
    double ceof = coefStr.toDouble();
    for (int i = 0; i < size; i ++) {
        double xData = xMin + i*step;
        double yData = ceof*yValue( xData );
        x.append( xData );
        y.append( yData );
    }
}

/**
 * @brief FittingView::transformUnit 单位转换
 * @param unit 单位
 * @return 比例系数
 */
QString FittingView::transformUnit(QString unit) {

    int coef1 = transformCoef( unit );
    if (0 == coef1) {
        return "NULL";
    }

    int coef2 = transformCoef( ui->unitComboBox->currentText() );
    if (0 == coef2) {
        return "NULL";
    }

    double proption = (double)coef1/(double)coef2;
    return QString::number( proption );
}

/**
 * @brief FittingView::transformCoef 获取转换系数
 * @param unit 单位
 * @return 系数
 */
int FittingView::transformCoef(QString unit) {
    int coef = 0;
    switch( m_unitStrList.indexOf( unit ) ) {
    case 0:
    case 2:
    case 5:
        coef = 1000;
        break;
    case 1:
    case 4:
        coef = 1;
        break;
    case 3:
        coef = 1000000;
        break;
    default:
        break;
    }

    return coef;
}

/**
 * @brief FittingView::tableValues 获取table中所有的数据
 * @param tableWidget table
 * @param x x轴数据(输出)
 * @param y y轴数据(输出)
 */
void FittingView::tableValues(QTableWidget *tableWidget,
                              QVector<double> &x, QVector<double> &y) {
    x.clear();
    y.clear();

    int rowCount = tableWidget->rowCount();
    for (int r = 0; r < rowCount; r ++) {
        QTableWidgetItem *itemX = tableWidget->item( r, 0 );
        QTableWidgetItem *itemY = tableWidget->item( r, 1 );

        QString xStr = itemX->text();
        QString yStr = itemY->text();

        x.append( xStr.toDouble() );
        y.append( yStr.toDouble() );
    }
}

/**
 * @brief FittingView::removeAll
 * @param tableWidget
 */
void FittingView::removeAll(QTableWidget *tableWidget) {
    int rowCount = tableWidget->rowCount();
    for (int r = rowCount - 1; r >= 0; r --) {
        tableWidget->removeRow( r );
    }
}

/**
 * @brief FittingView::removeSelectedRow 删除选中的行
 * @param tableWidget table
 */
void FittingView::removeSelectedRow(QTableWidget *tableWidget) {
    if (tableWidget != NULL) {
        QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
        if (!selectedItems.isEmpty()) {
            QTableWidgetItem *selectedItem = selectedItems.first();
            int row = tableWidget->row( selectedItem );
            if (row != -1) {
                tableWidget->removeRow( row );
            }
        }
    }
}

/**
 * @brief FittingView::initializeSystem 初始化
 */
void FittingView::initializeSystem() {

    m_r2Str.clear();
    m_fitCoefList.clear();
    m_unitStrList.clear();

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_unitStrList = configIniReader->value( "/FittingView/Unit" ).toStringList();
    QStringList typeList = configIniReader->value( "/FittingView/Type" ).toStringList();
    for(int i = 0; i < m_unitStrList.size(); i ++) {
        ui->unitComboBox->addItem( QIcon( ":/icons/uint.png" ), m_unitStrList.at( i ) );
    }
    ui->unitComboBox->setCurrentText( "mg/mL" );

    for(int i = 0; i < typeList.size(); i ++) {
        ui->typeComboBox->addItem( typeList.at( i ) );
    }

    QStringList measureHeaders = configIniReader->value( "/FittingView/Measure Header Labels" ).toStringList();
    ui->measureTableWidget->setColumnCount( measureHeaders.size() );
    ui->measureTableWidget->setHorizontalHeaderLabels( measureHeaders );
    ui->measureTableWidget->horizontalHeader()->setFont( QFont( "微软雅黑", 10 ) );
    ui->measureTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    QStringList fittingHeaders = configIniReader->value( "/FittingView/Fitting Header Labels" ).toStringList();
    ui->fittingTableWidget->setColumnCount( fittingHeaders.size() );
    ui->fittingTableWidget->setHorizontalHeaderLabels( fittingHeaders );
    ui->fittingTableWidget->horizontalHeader()->setFont( QFont( "微软雅黑", 10 ) );
    ui->fittingTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    ui->toolBox->setCurrentIndex( 0 );


    if (!m_unitStrList.isEmpty()) {
        m_preUnit = m_unitStrList.first();
    }
    m_fitUnit = m_preUnit;

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief FittingView::initializeWidget 初始化
 */
void FittingView::initializeWidget() {

    m_pFsDialog = new FsDialog();
    connect(m_pFsDialog, SIGNAL(settingOk(int)), this, SLOT(updateByRow(int)));

    connect(ui->fitBtn, SIGNAL(clicked(bool)), this, SLOT(fit()));
    connect(ui->removeBtn, SIGNAL(clicked(bool)), this, SLOT(remove()));
    // 单位切换
    connect(ui->unitComboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(updateUnit(QString)));

    connect(ui->fittingTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SLOT(itemSelected(QTableWidgetItem*)));
}

