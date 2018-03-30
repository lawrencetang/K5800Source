#include "plotview.h"
#include "plotzoomer.h"
#include <QEvent>
#include <QMouseEvent>

#include <qwt_legend.h>
#include <qwt_symbol.h>
#include <qwt_interval.h>
#include <qwt_plot_item.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_layout.h>
#include <qwt_legend_label.h>
#include <qwt_plot_zoneitem.h>
#include <qwt_plot_textlabel.h>
#include <qwt_plot_legenditem.h>

const QFont titleFont = QFont("微软雅黑", 14, QFont::Bold);//lt:标题字体
const QFont axisTextFont = QFont("微软雅黑", 12, QFont::Bold);//lt:坐标轴文字字体
const QFont axisScaleFont = QFont("微软雅黑", 10);//lt:坐标轴刻度字体
const QFont markerFont = QFont("黑体", 8, QFont::Bold);//lt:标刻线字体
const QFont legendFont = QFont("黑体", 25, QFont::Bold);//lt:右边选项字体
const QFont measureFont = QFont("Times", 35, QFont::Bold);//lt:测量字体


PlotView::PlotView( QWidget *parent ) : QwtPlot( parent ) {
    initializePlot();
}

PlotView::~PlotView() {

}

/**
 * 函数名称: eventFilter
 * 函数用途: 事件处理
 * 输入参数:
 *          QObject object = 触发对象
 *          QEvent  event = 事件
 * 输出参数:
 *          无
 */
bool PlotView::eventFilter(QObject *object, QEvent *event) {
    if ( object == canvas()) {

        if (event->type() == QEvent::MouseButtonDblClick) {
            // 双击鼠标左键实现还原
            QMouseEvent *t_pMouseEvent = (QMouseEvent *)event;
            if (Qt::LeftButton == t_pMouseEvent->button()) {
                if (NULL != m_pPlotZoomerBottom) {
                    m_pPlotZoomerBottom->zoom(0);
                }
                if (NULL != m_pPlotZoomerUp) {
                    m_pPlotZoomerUp->zoom(0);
                }
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            // 判断是否选中了标尺
            QMouseEvent *t_pMouseEvent = (QMouseEvent *)event;
            double x = invTransform(QwtPlot::xBottom ,t_pMouseEvent->pos().x());
            double dist = ( axisInterval( QwtPlot::xBottom ).maxValue() - axisInterval( QwtPlot::xBottom ).minValue() )/100;

            const QwtPlotItemList& itmList = this->itemList();
            for ( QwtPlotItemIterator it = itmList.begin();
                  it != itmList.end(); ++it ) {

                if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotMarker ) {
                    QwtPlotMarker *pMarker = static_cast<QwtPlotMarker *>( *it );

                    if (m_scaleMarkers.contains(pMarker)) {

                        if ( !pMarker->isVisible() ) {
                            continue;
                        }

                        int xd = abs(pMarker->xValue() - x);
                        if (xd < dist) {
                            m_pSelectedScaleMarker = pMarker;
                            setZoomerEnable(false);
                            return true;
                        }
                    }
                }
            }
        } else if (event->type() == QEvent::MouseMove) {
            // 移动标尺
            if (NULL != m_pSelectedScaleMarker) {
                QMouseEvent *t_pMouseEvent = (QMouseEvent *)event;

                if (m_scaleMarkers.contains(m_pSelectedScaleMarker)) {
                    moveScaleMarker( m_pSelectedScaleMarker, t_pMouseEvent->pos().x() );
                }

                this->refresh();
                return true;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            // 移动标尺结束
            if (NULL != m_pSelectedScaleMarker) {
                m_pSelectedScaleMarker = NULL;
                setZoomerEnable(true);
                return true;
            }
        }
    }
    return QwtPlot::eventFilter( object, event );
}

/**
 * 函数名称: installPlotZoomer
 * 函数用途: 在Plot中装载Zoomer
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::installPlotZoomer() {

    if (NULL == m_pPlotZoomerBottom) {
        m_pPlotZoomerUp = new PlotZoomer( QwtPlot::xTop, QwtPlot::yRight, canvas() );
        m_pPlotZoomerBottom = new PlotZoomer( QwtPlot::xBottom, QwtPlot::yLeft, canvas() );

        connect(m_pPlotZoomerBottom, SIGNAL(zoomed(QRectF)), this, SLOT(refresh()));
    }
}

/**
 * 函数名称: uninstallPlotZoomer
 * 函数用途: 在Plot中卸载Zoomer
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::uninstallPlotZoomer() {

    if (NULL != m_pPlotZoomerBottom) {
        delete m_pPlotZoomerBottom;
        m_pPlotZoomerBottom = NULL;
    }
    if (NULL != m_pPlotZoomerUp) {
        delete m_pPlotZoomerUp;
        m_pPlotZoomerUp = NULL;
    }
}

/**
 * 函数名称: setCanvasPalette
 * 函数用途: 设置画布的调色板
 * 输入参数:
 *          palette = 调色板
 * 输出参数:
 *          无
 */
void PlotView::setCanvasPalette(QPalette palette) {

    QwtPlotCanvas *canvas = static_cast<QwtPlotCanvas *>(this->canvas());
    canvas->setPalette( palette );
}

/**
 * 函数名称: setZoomerEnable
 * 函数用途: 设置缩放功能是否使能
 * 输入参数:
 *          ok = true使能, false不使能
 * 输出参数:
 *          无
 */
void PlotView::setZoomerEnable(bool ok) {

    if (NULL != m_pPlotZoomerBottom) {
        m_pPlotZoomerBottom->setZoomerEnable(ok);
    }
    if (NULL != m_pPlotZoomerUp) {
        m_pPlotZoomerUp->setZoomerEnable(ok);
    }
}

/**
 * 函数名称: setPannerEnable
 * 函数用途: 设置Panner功能是否使能
 * 输入参数:
 *          ok = true使能, false不使能
 * 输出参数:
 *          无
 */
void PlotView::setPannerEnable(bool ok) {

    if (NULL != m_pPlotPanner) {
        m_pPlotPanner->setEnabled(ok);
    }
}

/**
 * 函数名称: curveTitles
 * 函数用途: 获取曲线的title列表
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
QStringList PlotView::curveTitles() {

    QStringList titles;
    for (int i = 0; i < m_curves.size(); i ++) {
       titles.append( m_curves.at( i )->title().text() );
    }
    return titles;
}

/**
 * 函数名称: setPlotTitle
 * 函数用途: 设置标题
 * 输入参数:
 *          title = 标题
 * 输出参数:
 *          无
 */
void PlotView::setPlotTitle(QString title) {

    QwtText qwtText;
    qwtText.setText( title );
    qwtText.setFont( titleFont );
    setTitle(qwtText);
}

/**
 * 函数名称: setXAxisText
 * 函数用途: 设置X轴的显示信息
 * 输入参数:
 *          text = 信息
 * 输出参数:
 *          无
 */
void PlotView::setXAxisText(QString text) {

    QwtText qwtText;
    qwtText.setText( tr("%1").arg(text) );
    qwtText.setFont( axisTextFont );
    setAxisTitle( QwtPlot::xBottom, qwtText );
}

/**
 * 函数名称: setYAxisText
 * 函数用途: 设置Y轴的显示信息
 * 输入参数:
 *          text = 信息
 * 输出参数:
 *          无
 */
void PlotView::setYAxisText(QString text) {

    QwtText qwtText;
    qwtText.setText( tr("%1").arg(text) );
    qwtText.setFont( axisTextFont );
    setAxisTitle( QwtPlot::yLeft, qwtText );
}

/**
 * 函数名称: clearCurves
 * 函数用途: 清除所有曲线
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::clearCurves() {

    for (int i = m_curves.size() - 1; i >= 0; i --) {
        QwtPlotCurve *pCurveData = m_curves.takeAt(i);

        delete pCurveData;
        pCurveData = NULL;
    }
}

/**
 * 函数名称: addSacleMarker
 * 函数用途: 添加标尺
 * 输入参数:
 *          count = 标尺的数量
 * 输出参数:
 *          无
 */
void PlotView::addSacleMarker(int count) {

    clearSacleMarkers();
    for (int i = 0; i < count; i ++) {

        QwtPlotMarker *pScaleMarker = new QwtPlotMarker();
        pScaleMarker->setTitle( QString( "  S%1  " ).arg( i+1 ) );//ltj
        pScaleMarker->setLineStyle( QwtPlotMarker::VLine );
        pScaleMarker->setLinePen( m_colors.at( i%m_colors.size() ), 2, Qt::DashLine );
        pScaleMarker->setVisible( false );
        pScaleMarker->setItemAttribute( QwtPlotItem::Legend, true );
        pScaleMarker->attach( this );
        m_scaleMarkers.append( pScaleMarker );

    }
    refresh();
}

/**
 * 函数名称: clearSacleMarkers
 * 函数用途: 清空标尺
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::clearSacleMarkers() {

    for (int i = m_scaleMarkers.size() - 1; i >= 0; i --) {
        QwtPlotMarker *pScaleMarker = m_scaleMarkers.takeAt(i);

        delete pScaleMarker;
        pScaleMarker = NULL;
    }

    m_pSelectedScaleMarker = NULL;
    refresh();
}

/**
 * 函数名称: clearPointMarker
 * 函数用途: 清除所有的非ScaleMarker
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::clearPointMarker() {

    for (int i = 0; i < m_pointMarkers.size(); i ++) {
        QwtPlotMarker *pMarker = m_pointMarkers.at( i );
        delete pMarker;
        pMarker = NULL;
    }
    m_pointMarkers.clear();
    refresh();
}

/**
 * 函数名称: drawStaticCurve
 * 函数用途: 画静态曲线
 * 输入参数:
 *          x = 横坐标
 *          y = 纵坐标
 * 输出参数:
 *          无
 */
void PlotView::drawStaticCurve( QVector<double> x, QVector<double> y ) {

    int id = m_curves.size();
    QString curveName = QString("  S%1  ").arg( id+1 );
    drawStaticCurve(curveName, x, y);
}

/**
 * 函数名称: drawStaticCurve
 * 函数用途: 画静态曲线
 * 输入参数:
 *          name = 曲线名称
 *          x = 横坐标
 *          y = 纵坐标
 * 输出参数:
 *          无
 */
void PlotView::drawStaticCurve(QString name, QVector<double> x, QVector<double> y) {

    if (NULL != m_pPlotZoomerBottom) {
        m_pPlotZoomerBottom->zoom( 0 );
    }
    if (NULL != m_pPlotZoomerUp) {
        m_pPlotZoomerUp->zoom( 0 );
    }

    int id = m_curves.size();
    QColor color = m_colors.at( id%m_colors.size() );//lt:曲线颜色除余循环
    QwtPlotCurve *t_pCurve = new QwtPlotCurve( name );//lt:新建一个曲线对象
    if (name != "  OK  ") {
        QwtText titlelengend = t_pCurve->title();
        titlelengend.setColor(Qt::red);
        titlelengend.setFont(measureFont);
        t_pCurve->setTitle(titlelengend);
        for (int i = 0; i < m_scaleMarkers.size(); i++ ) {
            m_scaleMarkers.at(i)->setTitle( QString( "  S%1  " ).arg( i+1 ) );
        }//ltj:循环标尺
    }//ltj:把测量数据的字体颜色变为红色
    t_pCurve->setPen( color );
    t_pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    t_pCurve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );
    t_pCurve->setSamples( x, y );

    t_pCurve->attach(this);
    showPlotItem( t_pCurve, true );

    uninstallPlotZoomer();
    double xMin = axisInterval( QwtPlot::xBottom ).minValue();
    double xMax = axisInterval( QwtPlot::xBottom ).maxValue();
    //getXAxisLimitVal(x, &xMin, &xMax);
    //setAxisScale( QwtPlot::xBottom, xMin, xMax );
    QVector<double> ny;
    int xVal = 0;
    for (int i = 0; i < x.size(); i ++) {
        xVal = x.at( i );
        if (xVal >= xMin && xVal <= xMax) {
            ny.append( y.at( i ) );
        }//lt:根据x轴的波长范围对应获取y轴数组对应的值
    }

    double yMin = 0.0, yMax = 0.0;
    getYAxisLimitVal(ny, &yMin, &yMax);
    if (yMin != yMax && yMax != 0) {
        setAxisScale( QwtPlot::yLeft, yMin, yMax );//lt:根据前面计算的值设置刻度
    }
    installPlotZoomer();
    updateScaleMarker();
    m_curves.append( t_pCurve );
    refresh();
}

/**
 * 函数名称: drawDiscretePoint
 * 函数用途: 画离散点(拟合曲线时使用)
 * 输入参数:
 *          x = 横坐标
 *          y = 纵坐标
 * 输出参数:
 *          无
 */
void PlotView::drawDiscretePoint(QVector<double> x, QVector<double> y) {

    QColor color = Qt::yellow;
    QwtPlotCurve *t_pCurve = new QwtPlotCurve( tr("Samples") );
    QPen pen;
    pen.setColor( Qt::black );//lt:使用黑色
    pen.setStyle( Qt::NoPen );
    t_pCurve->setPen( pen );
    t_pCurve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::black, color, QSize( 8, 8 ) ) );
    t_pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    t_pCurve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );
    t_pCurve->setSamples( x, y);
    t_pCurve->attach(this);

    showPlotItem( t_pCurve, true );
    uninstallPlotZoomer();
    double xMin = 0.0, xMax = 0.0;
    getXAxisLimitVal(x, &xMin, &xMax);
    setAxisScale( QwtPlot::xTop, xMin, xMax );//lt:设置顶x轴
    setAxisScale( QwtPlot::xBottom, xMin, xMax );//lt:设置底x轴

    double yMin = 0.0, yMax = 0.0;
    getYAxisLimitVal(y, &yMin, &yMax);
    setAxisScale( QwtPlot::yLeft, yMin, yMax );
    installPlotZoomer();

    m_curves.append( t_pCurve );
    for (int i = 0; i < x.size(); i ++) {

        double xVal = x.at(i);
        double yVal = y.at(i);

        QwtPlotMarker *pMarker = new QwtPlotMarker();
        pMarker->setLineStyle( QwtPlotMarker::NoLine );
        pMarker->setVisible( true );
        pMarker->setItemAttribute( QwtPlotItem::Legend, false );

        QwtText text( QString( "x=%1\ny=%2" ).arg( xVal ).arg( yVal ) );
        text.setRenderFlags( Qt::AlignLeft );
        text.setColor( Qt::red );
        text.setFont( markerFont );

        pMarker->setLabel( text );
        pMarker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
        pMarker->setValue( xVal, yVal );
        pMarker->attach( this );

        m_pointMarkers.append( pMarker );
    }
    refresh();
}

/**
 * 函数名称: drawFitCurve
 * 函数用途: 画拟合曲线(拟合曲线时使用)
 * 输入参数:
 *          x = 横坐标
 *          y = 纵坐标
 * 输出参数:
 *          无
 */
void PlotView::drawFitCurve(QVector<double> x, QVector<double> y) {

    int id = m_curves.size();
    QColor color = m_colors.at( id%m_colors.size() );
    QwtPlotCurve *t_pCurve = new QwtPlotCurve( tr("Fitting") );
    t_pCurve->setPen( color );
    t_pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    t_pCurve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );
    t_pCurve->setSamples( x, y);

    t_pCurve->attach(this);
    showPlotItem( t_pCurve, true );

    uninstallPlotZoomer();
    double xMin = 0.0, xMax = 0.0;
    getXAxisLimitVal(x, &xMin, &xMax);
    setAxisScale( QwtPlot::xBottom, xMin, xMax );

    double yMin = 0.0, yMax = 0.0;
    getYAxisLimitVal(y, &yMin, &yMax);
    setAxisScale( QwtPlot::yLeft, yMin, yMax );
    installPlotZoomer();

    m_curves.append( t_pCurve );
    refresh();
}

/**
 * 函数名称: addDynamicsCurve
 * 函数用途: 添加动态曲线(动力学检测时使用)
 * 输入参数:
 *          count = 曲线数量
 * 输出参数:
 *          无
 */
void PlotView::addDynamicsCurve(int count) {

    QStringList names;
    for (int i = 0; i < count; i ++) {
        names.append( tr("S%1").arg(i) );//ltg
    }

    addDynamicsCurve(names);
}

/**
 * 函数名称: addDynamicsCurve
 * 函数用途: 添加动态曲线(动力学检测时使用)
 * 输入参数:
 *          names = 曲线名称列表
 * 输出参数:
 *          无
 */
void PlotView::addDynamicsCurve(QStringList names) {
    QwtPlotCurve *t_pCurve = NULL;
    for (int i = 0; i < names.size(); i ++) {
        QColor color = m_colors.at( i%m_colors.size() );

        t_pCurve = new QwtPlotCurve( names.at(i) );
        t_pCurve->setPen( color );
        t_pCurve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, color, color, QSize( 8, 8 ) ) );
        t_pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        t_pCurve->setPaintAttribute( QwtPlotCurve::ClipPolygons, false );

        t_pCurve->attach( this );
        showPlotItem( t_pCurve, true );
        m_curves.append( t_pCurve );
    }
}

/**
 * 函数名称: drawDynamicsCurve
 * 函数用途: 画动态曲线(动力学检测时使用)
 * 输入参数:
 *          x = x轴坐标
 *          y = 所有检测的值
 * 输出参数:
 *          无
 */
void PlotView::drawDynamicsCurve(double x, QList<double> y) {
    if (m_curves.size() != y.size()) {
        return;
    }

    double yMin = 100000.0;
    double yMax = -100000.0;
    QVector<double> xData;
    QVector<double> yData;
    for (int i = 0; i < m_curves.size(); i ++) {
        QwtPlotCurve *curve = m_curves.at( i );
        int size = static_cast<int>( curve->dataSize() );
        xData.clear();
        yData.clear();
        for ( int j = 0; j < size; j ++ ) {
            const QPointF sample = curve->sample( j );
            xData.append( sample.x() );
            yData.append( sample.y() );
            if (yMin > yData[j]) {
                yMin = yData[j];
            }
            if (yMax < yData[j]) {
                yMax = yData[j];
            }
        }
        double yVal = y.at( i );
        if (yMin > yVal) {
            yMin = yVal;
        }

        if (yMax < yVal) {
            yMax = yVal;
        }

        xData.append( x );
        yData.append( y.at( i ) );
        curve->setSamples( xData, yData );
    }

    if (yMax > 0) {
        yMax = 1.125 * yMax;
        yMin = 0 - 0.125 * yMax;
    } else {
        double width = (yMax - yMin);
        yMax = yMax + 0.125 * width;
        yMin = yMin - 0.125 * width;
    }
    uninstallPlotZoomer();
    setAxisScale( QwtPlot::yLeft, yMin, yMax );
    double xMax = axisInterval( QwtPlot::xBottom ).maxValue();
    if (xMax < x) {
        xMax = x;
    }
    double xMin = axisInterval( QwtPlot::xBottom ).minValue();
    if (xMin > x) {
        xMin = x;
    }
    setAxisScale( QwtPlot::xTop, xMin, xMax + 1 );
    setAxisScale( QwtPlot::xBottom, xMin, xMax + 1 );
    installPlotZoomer();
    updateScaleMarker();//ltj
    refresh();
}

/**
 * 函数名称: legendChecked
 * 函数用途: 响应legend的点击动作
 * 输入参数:
 *          itemInfo = itemInfo
 *          on       = 是否使能
 * 输出参数:
 *          无
 */
void PlotView::legendChecked(const QVariant &itemInfo, bool on) {

    QwtPlotItem *plotItem = infoToItem( itemInfo );
    if ( plotItem ) {
        showPlotItem( plotItem, on );

        // 在画拟合曲线时, 如果隐藏离散点则将提示一起隐藏掉
        if (plotItem->rtti() == QwtPlotItem::Rtti_PlotCurve) {
            QwtPlotCurve *pPlotCurve = static_cast<QwtPlotCurve *>( plotItem );
            if ( pPlotCurve->title().text() == "Samples" ) {
                showPointMarker( on );
            }
        }

         // 每次显示标尺时,设定显示位置为画布的中心位置
        if (on) {
            if (plotItem->rtti() == QwtPlotItem::Rtti_PlotMarker) {
                QwtPlotMarker *pScaleMarker = static_cast<QwtPlotMarker *>( plotItem );
                if (m_scaleMarkers.contains( pScaleMarker )) {

                    double x = 0.0;
                    if (m_type == "Nucleic Acid"  ||
                            m_type == "Protein" ) {

                        if (pScaleMarker->title().text() == "  S1  " ||
                            pScaleMarker->title().text() == "    S1  ") {
                            x = 280;
                        } else if (pScaleMarker->title().text() == "  S2  " ||
                                   pScaleMarker->title().text() == "    S2  ") {
                            x = 260;
                        } else if (pScaleMarker->title().text() == "  S3  " ||
                                   pScaleMarker->title().text() == "    S3  ") {
                            x = 230;
                        }
                    } else if (m_type == "Cell Culture" ) {
                        if (pScaleMarker->title().text() == "  S1  ") {
                            x = 600;
                        } else if (pScaleMarker->title().text() == "  S2  ") {
                            x = 520;
                        } else if (pScaleMarker->title().text() == "  S3  ") {
                            x = 520;
                        }
                    } else {
                        QwtInterval xInterval = axisInterval(QwtPlot::xBottom);
                        x = (xInterval.minValue() + xInterval.maxValue())/2;//lt:放到中间
                    }
                    pScaleMarker->setValue(x, 0.0);
                    moveScaleMarker(pScaleMarker, x, false);
                }
            }
        }
    }
}

/**
 * 函数名称: refresh
 * 函数用途: 刷新函数
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::refresh() {
    this->replot();
}

void PlotView::showPointMarker(bool ok) {
    for (int i = 0; i < m_pointMarkers.size(); i ++) {
        m_pointMarkers.at(i)->setVisible( ok );
    }
}

/**
 * 函数名称: moveScaleMarker
 * 函数用途: 移动标尺函数
 * 输入参数:
 *          plotMarker = 选中的标尺
 *          xPos       = 鼠标的水平位置
 * 输出参数:
 *          无
 */
void PlotView::moveScaleMarker(QwtPlotMarker *plotMarker, double xPos, bool transform) {

    double xValue = 0.0;
    double x;
    if (transform) {
        x = invTransform(QwtPlot::xBottom , xPos);
    } else {
        x = xPos;
    }
    QList<double> yValueList = findPointOnScale(x, &xValue);
    plotMarker->setValue(xValue, 0.0);

    // 显示内容
    QString s = QString("%1:\nx0=%2").arg( plotMarker->title().text() ).arg( xValue );
    for (int i = 0; i < yValueList.size(); i ++) {
        s.append(QString("\ny%1=%2").arg(i+1).arg(yValueList.at(i)));
    }
    QwtText text( s );
    text.setRenderFlags(Qt::AlignLeft);
    text.setColor( plotMarker->linePen().color() );
    text.setFont( markerFont );
    plotMarker->setLabel(text);

    // 显示位置
    QwtInterval xInterval = axisInterval( QwtPlot::xBottom );
    int xMidPos = (xInterval.minValue() + xInterval.maxValue())/2;
    int xCurPos = xValue;
    if (xCurPos > xMidPos) {
        plotMarker->setLabelAlignment( Qt::AlignLeft | Qt::AlignTop );
    } else {
        plotMarker->setLabelAlignment( Qt::AlignRight | Qt::AlignTop );
    }
    plotMarker->setLabelOrientation( Qt::Horizontal );
}

/**
 * 函数名称: updateScaleMaker
 * 函数用途: 更新标尺函数ltj
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::updateScaleMarker() {
    for ( int i = 0; i < m_scaleMarkers.size(); i++ ) {
        //double xValue = 0.0;
        double x;
        x = m_scaleMarkers.at( i )->xValue();
        m_scaleMarkers.at ( i )->setValue( x, 0.0 );
        moveScaleMarker( m_scaleMarkers.at( i ), x, false );
        //QList<double> yValueList = findPointOnScale( x, &xValue );
        //m_scaleMarkers.at( i )->setValue( xValue, yValueList.at( i ) );
        /*QString s = QString("%1:\nx0=%2").arg( m_scaleMarkers.at( i )->title().text() ).arg( xValue );
        s.append(QString("\ny%1=%2").arg(i+1).arg(yValueList.at(i)));
        QwtText text( s );
        text.setRenderFlags(Qt::AlignLeft);
        text.setColor( m_scaleMarkers.at( i )->linePen().color() );
        text.setFont( markerFont );
        m_scaleMarkers.at( i )->setLabel(text);*/
    }
}

/**
 * 函数名称: findPointOnScale
 * 函数用途: 搜索在标尺上所有曲线的数据
 * 输入参数:
 *          xPos = 当前标尺移动的位置
 *          pos  = 最后标尺的水平位置
 * 输出参数:
 *          标尺上所有曲线的数据
 */
QList<double> PlotView::findPointOnScale(double xPos, double *pos) {

    int id = -1;
    double fx = 0.0;
    double fy = 0.0;
    double xDist = 10000.0;
    double x = xPos;

    // 曲线上与标尺的x坐标距离最近点的y坐标
    QList<double> yList;
    const QwtPlotItemList& itmList = this->itemList();
    for ( QwtPlotItemIterator it = itmList.begin();
          it != itmList.end(); ++it ) {

        if (( *it )->rtti() == QwtPlotItem::Rtti_PlotCurve) {
            QwtPlotCurve *pPlotCurve = static_cast<QwtPlotCurve *>( *it );
            if ( !pPlotCurve->isVisible() ) {
                continue;
            }
            int size = static_cast<int>( pPlotCurve->dataSize() );
            if (id >= size) {
                continue;
            }

            if (-1 == id) {
                for(int i = 0; i < size; i ++) {
                    const QPointF sample = pPlotCurve->sample( i );
                    double dx = abs(x - sample.x());
                    if (dx < xDist) {
                        xDist = dx;
                        id = i;
                        fx = sample.x();
                        fy = sample.y();
                    }
                }
            } else {
                const QPointF sample = pPlotCurve->sample( id );
                fy = sample.y();
            }

            if (-1 != id) {
                yList.append(fy);
                xDist = 10000.0;
            }
        }
    }

    if (-1 != id) {
        *pos = fx;
    } else {
        *pos = xPos;
    }

    return yList;
}

/**
 * 函数名称: showPlotItem
 * 函数用途: 显示item
 * 输入参数:
 *          item = item
 *          on  = 是否显示
 * 输出参数:
 *          无
 */
void PlotView::showPlotItem(QwtPlotItem *item, bool on) {
    item->setVisible( on );
    QwtLegend *legend = qobject_cast<QwtLegend *>( this->legend() );
    QList<QWidget *> legendWidgets = legend->legendWidgets( itemToInfo( item ) );

    if ( legendWidgets.size() == 1 ) {
        QwtLegendLabel *legendLabel = qobject_cast<QwtLegendLabel *>( legendWidgets[0] );
        if ( legendLabel ) {
            legendLabel->setChecked( on );
        }
    }
    refresh();
}

/**
 * 函数名称: getXAxisLimitVal
 * 函数用途: 获取x轴的最大最小值
 * 输入参数:
 *          xList = x轴数据
 *          xMin  = x轴的最小值
 *          xMax  = x轴的最大值
 * 输出参数:
 *          无
 */
void PlotView::getXAxisLimitVal(QVector<double> xList, double *xMin, double *xMax) {

    double minVal = 1000000.0;
    double maxVal = -1000000.0;

    if (xList.isEmpty()) {
        minVal = axisInterval(QwtPlot::xBottom).minValue();
        maxVal = axisInterval(QwtPlot::xBottom).maxValue();
    } else if (xList.size() == 1) {
        minVal = xList.first();
        maxVal = minVal;
    } else {
        double curVal = 0.0;
        for (int i = 0; i < xList.size(); i ++) {
            curVal = xList.at(i);
            if (minVal >= curVal) {
                minVal = curVal;
            }

            if (maxVal <= curVal) {
                maxVal = curVal;
            }
        }
    }

    if (!m_curves.isEmpty()) {
        double xAxisMax = axisInterval(QwtPlot::xBottom).maxValue();
        if (maxVal < xAxisMax) {
            maxVal = xAxisMax;
        }

        double xAxisMin = axisInterval(QwtPlot::xBottom).maxValue();
        if (minVal > xAxisMin) {
            minVal = xAxisMin;
        }
    }
    *xMin = minVal - 1;
    *xMax = maxVal + 1;
}

/**
 * 函数名称: getYAxisLimitVal
 * 函数用途: 获取Y轴的最大最小值
 * 输入参数:
 *          yList = y轴数据
 *          yMin  = y轴的最小值
 *          yMax  = y轴的最大值
 * 输出参数:
 *          无
 */
void PlotView::getYAxisLimitVal(QVector<double> yList, double *yMin, double *yMax) {

    double minVal = 1000000.0;
    double maxVal = -1000000.0;
    if (yList.isEmpty()) {
        maxVal = axisInterval( QwtPlot::yLeft ).maxValue();//lt:y轴最大值
        minVal = axisInterval( QwtPlot::yLeft ).minValue();//lt:y轴最小值
    } else {
        double curVal = 0.0;
        for (int i = 0; i < yList.size(); i ++) {
            curVal = yList.at( i );
            if (minVal >= curVal) {
                minVal = curVal;
            }
            if (maxVal <= curVal) {
                maxVal = curVal;
            }
        }//lt:把实际的最大和最下y值映射到minval和maxval中,maxval永远是最大值，minval永远是最小值

        if (maxVal > 0 && minVal < 0) {
            maxVal = 1.125 * maxVal;
            minVal = 0 - 0.125 * maxVal;
        } else {
            maxVal = maxVal + 0.125 * (maxVal - minVal);
            minVal = minVal - 0.125 * (maxVal - minVal);
        }
    }//lt:动态坐标轴范围

    if (!m_curves.isEmpty()) {
        double yAxisMax = axisInterval( QwtPlot::yLeft ).maxValue();
        if (maxVal < yAxisMax) {
            maxVal = yAxisMax;
        }

        double yAxisMin = axisInterval( QwtPlot::yLeft ).minValue();
        if (minVal > yAxisMin) {
            minVal = yAxisMin;
        }
    }//lt:如果minval和maxval在设定坐标范围内则采用设定坐标,第一次由于m_curves空不进入该判断，第二次进入，yaxismax和yaxismin值为上次设定的坐标值

    *yMax = maxVal;
    *yMin = minVal;
}

/**
 * 函数名称: installPlotCanvas
 * 函数用途: 在Plot中装载Canvas
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::installPlotCanvas() {

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPaintAttribute( QwtPlotCanvas::BackingStore, false );
    canvas->setBorderRadius( 10 );//lt:设置画布倒角
    setCanvas(canvas);
}

/**
 * 函数名称: installPlotGrid
 * 函数用途: 在Plot中装载Grid
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::installPlotGrid() {

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( Qt::gray, 0.0, Qt::DotLine );//lt:设置网格为圆点
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( true );
    grid->enableYMin( false );
    grid->attach( this );//lt:粘贴网格
}

/**
 * 函数名称: installPlotLegend
 * 函数用途: 在Plot中装载Legend
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::installPlotLegend() {

    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    legend->setFont( legendFont );
    insertLegend( legend, QwtPlot::RightLegend );

    connect( legend, SIGNAL( checked( const QVariant &, bool, int ) ),
             SLOT( legendChecked( const QVariant &, bool ) ) );
}

/**
 * 函数名称: installPlotPanner
 * 函数用途: 在Plot中装载Panner
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::installPlotPanner() {

    if (NULL == m_pPlotPanner) {
        m_pPlotPanner = new QwtPlotPanner( canvas() );//lt:设置移动功能
        m_pPlotPanner->setMouseButton( Qt::MidButton );//lt:设置中键移动
    }
}

/**
 * 函数名称: initializePlot
 * 函数用途: 初始化Plot
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::initializePlot() {

    m_pPlotZoomerUp = NULL;
    m_pPlotZoomerBottom = NULL;
    m_pPlotPanner = NULL;
    m_curves.clear();
    m_colors.clear();

    m_pSelectedScaleMarker = NULL;
    m_scaleMarkers.clear();

    m_colors << Qt::black << Qt::red << Qt::darkRed << Qt::green
             << Qt::darkGreen << Qt::blue << Qt::darkBlue << Qt::cyan
             << Qt::darkCyan << Qt::magenta << Qt::darkMagenta << Qt::yellow
             << Qt::darkYellow << Qt::gray << Qt::darkGray << Qt::darkBlue;

    plotLayout()->setAlignCanvasToScales( true );

    initializeAxis();//lt:装载轴刻度字体
    installPlotCanvas();
    installPlotGrid();
    installPlotLegend();
    installPlotPanner();
}

/**
 * 函数名称: initializeAxis
 * 函数用途: 初始化坐标轴
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotView::initializeAxis() {
    enableAxis( QwtPlot::xTop );
    setAxisFont( QwtPlot::xTop, axisScaleFont );
    setAxisFont( QwtPlot::xBottom, axisScaleFont );
    setAxisFont( QwtPlot::yLeft, axisScaleFont );
}

