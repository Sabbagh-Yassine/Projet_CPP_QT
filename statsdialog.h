#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QDate>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>

QT_CHARTS_USE_NAMESPACE

class statsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit statsdialog(QWidget *parent = nullptr);
    ~statsdialog();

private:
    void setChart();

    QChartView *chartView;
    QLineSeries *series;
};

#endif // STATSDIALOG_H
