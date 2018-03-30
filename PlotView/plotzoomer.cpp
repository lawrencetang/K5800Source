#include "plotzoomer.h"

PlotZoomer::PlotZoomer(QWidget *canvas) :
    QwtPlotZoomer( canvas ) {
    initialize();
}//lt:选择图形局部放大的一个类

PlotZoomer::PlotZoomer(int xAxis, int yAxis,
                       QWidget *canvas) : QwtPlotZoomer( xAxis, yAxis, canvas ) {
    initialize();
}

PlotZoomer::~PlotZoomer() {

}

/**
 * 函数名称: setZoomerEnable
 * 函数用途: 设置Zoomer是否使能
 * 输入参数:
 *           ok = 使能或不使能
 * 输出参数:
 *           无
 */
void PlotZoomer::setZoomerEnable(bool ok) {
    if (!ok) {
        QwtPlotZoomer::reset();
    }
    setEnabled(ok);
}

/**
 * 函数名称: trackerTextF
 * 函数用途: 设置trackerText
 * 输入参数:
 *           pos = tracker点的位置
 * 输出参数:
 *           无
 */
QwtText PlotZoomer::trackerTextF(const QPointF &pos) const {

    QString s = QString("x = %1").arg(pos.x()) +
            "\n" + QString("y = %1\n").arg(pos.y());

    QwtText text( s, QwtText::TeXText );
    text.setRenderFlags( Qt::AlignLeft );
    text.setColor( Qt::black );
    text.setFont( QFont("黑体", 9) );
    return text;
}

/**
 * 函数名称: initialize
 * 函数用途: 初始化
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void PlotZoomer::initialize() {

    setRubberBandPen( QColor( Qt::red ) );//lt:勾选扩大区域的颜色
    setTrackerPen( QColor( Qt::black ) );

    /*设置鼠标动作
    * Ctrl + 鼠标右键: 直接还原
    * 鼠标右键: 逐步还原
    */
    setMousePattern( QwtEventPattern::MouseSelect2,
                     Qt::RightButton, Qt::ControlModifier );
    setMousePattern( QwtEventPattern::MouseSelect3,
                     Qt::RightButton );

    /*设置键盘动作
    * I: 逐步还原
    * O: 逐步还原
    * Home: 直接还原
    */
    setKeyPattern( QwtEventPattern::KeyRedo, Qt::Key_I );
    setKeyPattern( QwtEventPattern::KeyUndo, Qt::Key_O );
    setKeyPattern( QwtEventPattern::KeyHome, Qt::Key_Home );
}
