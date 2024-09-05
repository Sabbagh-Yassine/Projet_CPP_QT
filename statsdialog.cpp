#include "statsdialog.h"

statsdialog::~statsdialog() {}

statsdialog::statsdialog(QWidget *parent) :
    QDialog(parent),
    chartView(new QChartView(this)),
    series(new QLineSeries())
{
    setWindowTitle("Candidates Statistics");
    setMinimumSize(800, 600);

    // Create and set up the chart
    setChart();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);

    setLayout(layout);
}

void statsdialog::setChart()
{
    // Clear existing data in the series
    series->clear();

    // Prepare the query to get the number of applications per month
    QSqlQuery query;
    query.prepare("SELECT TO_CHAR(datePostulation, 'YYYY-MM') month, COUNT(*) number FROM candidat GROUP BY TO_CHAR(datePostulation, 'YYYY-MM') ORDER BY TO_CHAR(datePostulation, 'YYYY-MM')");

    // Check if the query executed successfully
    if (!query.exec()) {
        qWarning() << "Failed to execute query:" << query.lastError();
        return;
    }

    while (query.next()) {
        // Fetch the date directly as QDateTime from the database
        QDate date = query.value(0).toDate();  // Ensure the format of datePostulation is correct in your database
        int number = query.value(1).toInt();

        // Check if the date is valid before appending
        if (!date.isValid()) {
            qWarning() << "Invalid date value from database.";
            continue; // Skip invalid dates
        }
        QDateTime dateTime(date);
        // Add the data point to the series
        series->append(dateTime.toMSecsSinceEpoch(), number);
    }

    // Create and configure the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Number of Applications per Month");
    chart->legend()->setVisible(false);

    // Set up Y axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Applications");
    axisY->setLabelFormat("%d");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Set up X axis as DateTime axis
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTitleText("Month");
    axisX->setFormat("MMM yyyy");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Update the chart view
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}
