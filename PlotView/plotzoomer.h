#ifndef PLOTZOOMER_H
#define PLOTZOOMER_H

#include <qwt_plot_zoomer.h>

class PlotZoomer : public QwtPlotZoomer
{
    Q_OBJECT

public:
    PlotZoomer(QWidget *canvas);
    PlotZoomer(int xAxis, int yAxis, QWidget *canvas);
    ~PlotZoomer();

    void setZoomerEnable(bool ok);

protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const;

private:
    void initialize();
};

#endif // PLOTZOOMER_H
