#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QDebug>
using namespace  std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 🌙 Dark theme palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#1e1e1e"));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor("#2d2d2d"));           // Table background
    darkPalette.setColor(QPalette::AlternateBase, QColor("#252525"));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor("#2d2d2d"));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor("#4444aa"));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);

    this->setAutoFillBackground(true);
    this->setPalette(darkPalette);
    qApp->setPalette(darkPalette); // apply to entire app


    // Create dropdown menu
    QMenu *modeMenu = new QMenu(this);
    QAction *expensesAction = modeMenu->addAction("Expenses");
    QAction *incomeAction = modeMenu->addAction("Income");

    ui->modeButton->setMenu(modeMenu);

    // Connect to update chart and table for Expenses
    connect(expensesAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Expenses");
        updateChartAndTable("Expenses");
    });

    // Connect to update chart and table for Income
    connect(incomeAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Income");
        updateChartAndTable("Income");
    });

    // ✅ Default to "Expenses" on startup
    ui->modeButton->setText("Expenses");
    updateChartAndTable("Expenses");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateChartAndTable(const QString &mode)
{

    int dates = 30;
    int period = 6;
    int typesOf = (mode == "Expenses") ? 2 : 3;
    QString expenses[2] = {"Transportation", "Grocery"};
    QString incomes[3] = {"Work", "Parents", "Ivesting"};

    // Clean up old chart if needed
    QLayout *oldLayout = ui->chartContainer->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Prepare random data
    QPieSeries *series = new QPieSeries();
    ui->dataTable->setRowCount(dates);
    ui->dataTable->setColumnCount(period);
    ui->dataTable->setHorizontalHeaderLabels(QStringList() << "Type" << "Day" << "Week" << "Month" << "Year" << "All");

    if(mode == "Expenses") {
        string name = "";
        for(int i = 0; i < dates; ++i) {
            if(i % 3 == 0)
                name = "Transportation";
            else
                name = "Grocery";

            QString tp = QString("%1").arg(name);
            ui->dataTable->setItem(i, 0, new QTableWidgetItem(tp));
        }

        for(int i = 0; i < typesOf; ++i) {
            int value = QRandomGenerator::global()->bounded(10, 300);
            series->append(expenses[i], value);
        }
    }
    else if(mode == "Income") {
        string name = "";
        for(int i = 0; i < dates; ++i) {
            if(i % 3 == 0)
                name = "Work";
            else if(i % 5 == 0) {
                name = "Parents";
            }
            else
                name = "Ivesting";

            QString tp = QString("%1").arg(name);
            ui->dataTable->setItem(i, 0, new QTableWidgetItem(tp));
        }

        for(int i = 0; i < typesOf; ++i) {
            int value = QRandomGenerator::global()->bounded(10, 300);
            series->append(incomes[i], value);
        }
    }
    for(int j = 0; j < dates; ++j) { //row
        for (int i = 1; i < period; ++i) { //column
            int value = QRandomGenerator::global()->bounded(10, 100);
            ui->dataTable->setItem(j, i, new QTableWidgetItem(QString::number(value)));
        }

    }

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setBackgroundBrush(QBrush(QColor("#1e1e1e")));
    chart->setTitleBrush(QBrush(Qt::white));
    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    for (auto slice : series->slices()) {
        slice->setLabelBrush(Qt::white);     // Label text color
        slice->setLabelFont(QFont("Arial", 10));
        slice->setPen(Qt::NoPen);
    }



    chart->setTitle(mode + " Pie Chart");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chartContainer);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
}

