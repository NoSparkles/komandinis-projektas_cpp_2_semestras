// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "service/EntryService.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    entryService = new EntryService("data/income.csv", "data/expense.csv");


    // Dark theme palette setup
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#1e1e1e"));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor("#2d2d2d"));
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
    qApp->setPalette(darkPalette);

    // Mode menu setup
    QMenu *modeMenu = new QMenu(this);
    QAction *expensesAction = modeMenu->addAction("Expenses");
    QAction *incomeAction = modeMenu->addAction("Income");

    ui->modeButton->setMenu(modeMenu);

    connect(expensesAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Expenses");
        updateChartAndTable("Expenses");
    });

    connect(incomeAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Income");
        updateChartAndTable("Income");
    });

    ui->modeButton->setText("Expenses");
    updateChartAndTable("Expenses");
}

MainWindow::~MainWindow()
{
    delete entryService;
    delete ui;
}

void MainWindow::updateChartAndTable(const QString &mode)
{
    QPieSeries *series = new QPieSeries();

    // Clear previous layout
    QLayout *oldLayout = ui->chartContainer->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    if (mode == "Expenses") {
        auto expenses = entryService->getAllExpenses();
        ui->dataTable->setRowCount(static_cast<int>(expenses.size()));
        ui->dataTable->setColumnCount(4);
        ui->dataTable->setHorizontalHeaderLabels(QStringList() << "Type" << "Date" << "Name" << "Amount");

        QMap<QString, double> totals;
        for (int i = 0; i < expenses.size(); ++i) {
            const auto &e = expenses[i];
            ui->dataTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(e.getType())));
            ui->dataTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(e.getDate())));
            ui->dataTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(e.getName())));
            ui->dataTable->setItem(i, 3, new QTableWidgetItem(QString::number(e.getAmount())));
            totals[QString::fromStdString(e.getType())] += e.getAmount();
        }

        for (auto it = totals.begin(); it != totals.end(); ++it) {
            series->append(it.key(), it.value());
        }
    } else if (mode == "Income") {
        auto incomes = entryService->getAllIncomes();
        ui->dataTable->setRowCount(static_cast<int>(incomes.size()));
        ui->dataTable->setColumnCount(4);
        ui->dataTable->setHorizontalHeaderLabels(QStringList() << "Type" << "Date" << "Name" << "Amount");

        QMap<QString, double> totals;
        for (int i = 0; i < incomes.size(); ++i) {
            const auto &e = incomes[i];
            ui->dataTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(e.getType())));
            ui->dataTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(e.getDate())));
            ui->dataTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(e.getName())));
            ui->dataTable->setItem(i, 3, new QTableWidgetItem(QString::number(e.getAmount())));
            totals[QString::fromStdString(e.getType())] += e.getAmount();
        }

        for (auto it = totals.begin(); it != totals.end(); ++it) {
            series->append(it.key(), it.value());
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundBrush(QBrush(QColor("#1e1e1e")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle(mode + " Pie Chart");
    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    for (auto slice : series->slices()) {
        slice->setLabelBrush(Qt::white);
        slice->setLabelFont(QFont("Arial", 10));
        slice->setPen(Qt::NoPen);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chartContainer);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
}
