#include "statistiquesdialog.h"
#include <QVBoxLayout>
#include <QSqlQuery>

StatistiquesDialog::StatistiquesDialog(QWidget *parent) :
    QDialog(parent),
    chartView(new QChartView(this)),
    series(new QPieSeries())
{
    setWindowTitle("Job Offers Statistics");
    this->setMinimumSize(800, 600);

    // Create and set up the pie chart
    setupChart();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    setLayout(layout);
}

StatistiquesDialog::~StatistiquesDialog()
{
    // Destructor implementation if needed
}

void StatistiquesDialog::setupChart()
{
    // Retrieve data from the database
    QSqlQuery query("SELECT poste, nombreCandidats FROM OffreEmploi");
    while (query.next()) {
        QString poste = query.value(0).toString();
        int nombreCandidats = query.value(1).toInt();
        series->append(poste, nombreCandidats);
    }

    // Create the chart and set its series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Job Offers by Number of Candidates");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Set the chart view's chart
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

