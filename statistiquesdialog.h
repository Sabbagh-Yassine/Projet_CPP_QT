#ifndef STATISTIQUESDIALOG_H
#define STATISTIQUESDIALOG_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class StatistiquesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatistiquesDialog(QWidget *parent = nullptr);
    ~StatistiquesDialog();

private:
    void setupChart();


    QChartView *chartView;
    QPieSeries *series;
};



#endif // STATISTIQUESDIALOG_H
