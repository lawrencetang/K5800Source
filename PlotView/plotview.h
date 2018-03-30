#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <qwt_plot.h>

class PlotZoomer;
class QwtPlotCurve;
class QwtPlotPanner;
class QwtPlotZoomer;
class QwtPlotMarker;
class QwtPlotLegendItem;
class PlotView : public QwtPlot
{
    Q_OBJECT

public:
    PlotView( QWidget *parent= NULL );
    ~PlotView();

    virtual bool eventFilter( QObject *, QEvent * );
    void installPlotZoomer();
    void uninstallPlotZoomer();

    void setCanvasPalette(QPalette palette);
    void setZoomerEnable(bool ok);
    void setPannerEnable(bool ok);

    inline int dynamicCurveSize() {
        return m_curves.size();
    }
    QStringList curveTitles();
    inline void setType(QString type) {
        m_type = type;
    }

public slots:
    void setPlotTitle(QString title);
    void setXAxisText(QString text);
    void setYAxisText(QString text);
    void clearCurves();

    void addSacleMarker(int count);
    void clearSacleMarkers();
    void clearPointMarker();

    void drawStaticCurve( QVector<double> x, QVector<double> y );
    void drawStaticCurve( QString name, QVector<double> x, QVector<double> y );
    void drawDiscretePoint( QVector<double> x, QVector<double> y );
    void drawFitCurve( QVector<double> x, QVector<double> y );
    void addDynamicsCurve(int count);
    void addDynamicsCurve(QStringList names);
    void drawDynamicsCurve(double x, QList<double> y );

    void legendChecked( const QVariant &itemInfo, bool on );
    void refresh();

private:
    QList<QColor> m_colors;
    QList<QwtPlotCurve *> m_curves;
    PlotZoomer *m_pPlotZoomerBottom;
    PlotZoomer *m_pPlotZoomerUp;
    QwtPlotPanner *m_pPlotPanner;
    QString m_type;

    QwtPlotMarker *m_pSelectedScaleMarker;
    QList<QwtPlotMarker *> m_scaleMarkers;
    QList<QwtPlotMarker *> m_pointMarkers;

    void showPointMarker(bool ok);
    void updateScaleMarker();

    void moveScaleMarker(QwtPlotMarker *plotMarker, double xPos , bool transform = true);
    QList<double> findPointOnScale( double xPos, double *pos );
    void showPlotItem( QwtPlotItem *item, bool on );
    void getXAxisLimitVal( QVector<double> xList, double *xMin, double *xMax );
    void getYAxisLimitVal( QVector<double> yList, double *yMin, double *yMax );

    void installPlotCanvas();
    void installPlotGrid();
    void installPlotLegend();
    void installPlotPanner();
    void initializePlot();
    void initializeAxis();
};

#endif // PLOTVIEW_H
