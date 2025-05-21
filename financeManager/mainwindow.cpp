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

#include <QInputDialog>
#include <QMessageBox>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QDateEdit>

#include "model/Income.h"
#include "model/Expense.h"

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

    updateTypeFilter("Expenses");

    ui->modeButton->setMenu(modeMenu);

    connect(expensesAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Expenses");
        updateChartAndTable("Expenses");
        updateTypeFilter("Expenses");
    });

    connect(incomeAction, &QAction::triggered, this, [=]() {
        ui->modeButton->setText("Income");
        updateChartAndTable("Income");
        updateTypeFilter("Income");
    });


    ui->modeButton->setText("Expenses");
    updateChartAndTable("Expenses");


    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    ui->dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataTable, &QTableWidget::customContextMenuRequested, this, &MainWindow::onTableContextMenu);
    connect(ui->dataTable, &QTableWidget::cellChanged, this, &MainWindow::onTableCellChanged);
}

MainWindow::~MainWindow()
{
    delete entryService;
    delete ui;
}

void MainWindow::onTableCellChanged(int row, int column) {
    static bool updating = false;
    if (updating) return;
    updating = true;

    QString mode = ui->modeButton->text();

    QString type = ui->dataTable->item(row, 0)->text();
    QString date = ui->dataTable->item(row, 1)->text();
    QString name = ui->dataTable->item(row, 2)->text();
    double amount = ui->dataTable->item(row, 3)->text().toDouble();

    bool updated = false;

    if (mode == "Expenses") {
        auto expenses = entryService->getAllExpenses();
        if (row < expenses.size()) {
            Expense oldExpense = expenses[row];
            Expense newExpense = oldExpense;
            newExpense.setType(type.toStdString());
            newExpense.setDate(date.toStdString());
            newExpense.setName(name.toStdString());
            newExpense.setAmount(amount);
            entryService->updateExpense(oldExpense, newExpense);
            updated = true;
        }
    } else {
        auto incomes = entryService->getAllIncomes();
        if (row < incomes.size()) {
            Income oldIncome = incomes[row];
            Income newIncome = oldIncome;
            newIncome.setType(type.toStdString());
            newIncome.setDate(date.toStdString());
            newIncome.setName(name.toStdString());
            newIncome.setAmount(amount);
            entryService->updateIncome(oldIncome, newIncome);
            updated = true;
        }
    }

    if (updated) {
        entryService->saveEntriesToFile();
        updateChartAndTable(mode);
    }

    updating = false;
}
void MainWindow::onTableContextMenu(const QPoint &pos) {
    QModelIndex index = ui->dataTable->indexAt(pos);
    if (!index.isValid()) return;

    QMenu contextMenu;
    QAction *deleteAction = contextMenu.addAction("Delete Entry");
    QAction *selectedAction = contextMenu.exec(ui->dataTable->viewport()->mapToGlobal(pos));
    if (selectedAction == deleteAction) {
        int row = index.row();

        // Get entry data from the row
        QString type = ui->dataTable->item(row, 0)->text();
        QString date = ui->dataTable->item(row, 1)->text();
        QString name = ui->dataTable->item(row, 2)->text();
        double amount = ui->dataTable->item(row, 3)->text().toDouble();

        QString mode = ui->modeButton->text();

        bool deleted = false;
        if (mode == "Expenses") {
            auto expenses = entryService->getAllExpenses();
            for (const auto& e : expenses) {
                if (QString::fromStdString(e.getType()) == type &&
                    QString::fromStdString(e.getDate()) == date &&
                    QString::fromStdString(e.getName()) == name &&
                    e.getAmount() == amount) {
                    entryService->removeExpense(e);
                    deleted = true;
                    break;
                }
            }
        } else {
            auto incomes = entryService->getAllIncomes();
            for (const auto& e : incomes) {
                if (QString::fromStdString(e.getType()) == type &&
                    QString::fromStdString(e.getDate()) == date &&
                    QString::fromStdString(e.getName()) == name &&
                    e.getAmount() == amount) {
                    entryService->removeIncome(e);
                    deleted = true;
                    break;
                }
            }
        }

        if (deleted) {
            entryService->saveEntriesToFile();
            updateChartAndTable(mode);
        } else {
            QMessageBox::warning(this, "Delete Failed", "Could not find the entry to delete.");
        }
    }

}

void MainWindow::onAddButtonClicked() {
    QString mode = ui->modeButton->text();

    // Create dialog
    QDialog dialog(this);
    dialog.setWindowTitle("Add Entry");

    QFormLayout form(&dialog);

    // Type ComboBox
    QComboBox *typeCombo = new QComboBox(&dialog);
    QStringList typeList;
    if (mode == "Expenses") {
        for (const auto& t : Expense::getTypes()) typeList << QString::fromStdString(t);
    } else {
        for (const auto& t : Income::getTypes()) typeList << QString::fromStdString(t);
    }
    typeCombo->addItems(typeList);
    form.addRow("Type:", typeCombo);

    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    dateEdit->setCalendarPopup(true);
    form.addRow("Date:", dateEdit);

    // Name LineEdit
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    form.addRow("Name:", nameEdit);

    // Amount DoubleSpinBox
    QDoubleSpinBox *amountSpin = new QDoubleSpinBox(&dialog);
    amountSpin->setRange(-1000000, 1000000);
    amountSpin->setDecimals(2);
    form.addRow("Amount:", amountSpin);

    // Dialog buttons
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Show dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString type = typeCombo->currentText();
        QString name = nameEdit->text();
        double amount = amountSpin->value();
        QString date = dateEdit->date().toString("yyyy-MM-dd");

        if (name.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Name cannot be empty.");
            return;
        }


        if (mode == "Expenses") {
            Expense newExpense(0, type.toStdString(), date.toStdString(), name.toStdString(), amount);
            entryService->addExpense(newExpense);
        } else {
            Income newIncome(0, type.toStdString(), date.toStdString(), name.toStdString(), amount);
            entryService->addIncome(newIncome);
        }


        entryService->saveEntriesToFile();

        updateChartAndTable(mode);


        QMessageBox::information(this, "Entry Added",
                                 QString("Type: %1\nName: %2\nAmount: %3\nDate: %4")
                                     .arg(type, name).arg(amount).arg(date));
    }

    updateChartAndTable(mode);

}


void MainWindow::updateTypeFilter(const QString &mode) {
    std::vector<std::string> types;
    if(mode == "Expenses") {
        types = Expense::getTypes();
    } else {
        types = Income::getTypes();
    }
    ui->typeSelect->clear();
    ui->typeSelect->addItem("None");
    for (const std::string &type : types) {
        ui->typeSelect->addItem(QString::fromStdString(type));
    }
}


void MainWindow::updateChartAndTable(const QString &mode)
{
    QPieSeries *series = new QPieSeries();

    double totalIncome = 0.0;
    double totalExpense = 0.0;

    auto incomes = entryService->getAllIncomes();
    for (const auto& income : incomes) {
        totalIncome += income.getAmount();
    }

    auto expenses = entryService->getAllExpenses();
    for (const auto& expense : expenses) {
        totalExpense += expense.getAmount();
    }

    double balance = totalIncome - totalExpense;
    ui->totalBalance->setText(QString::number(balance, 'f', 2) + " Eur");

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

        int i = 0;
        int totalItems = totals.size();

        for (auto it = totals.begin(); it != totals.end(); ++it, ++i) {
            QPieSlice* slice = series->append(it.key(), it.value());

            // Generate a unique hue based on index
            int hue = (360 * i) / totalItems;  // evenly spaced around color wheel
            QColor color = QColor::fromHsv(hue, 200, 255);  // vibrant and bright

            slice->setBrush(color);
            slice->setBrush(color);
            slice->setPen(QPen(Qt::NoPen));
            slice->setLabelBrush(Qt::white);
            slice->setLabelFont(QFont("Arial", 10));
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

        int i = 0;
        int totalItems = totals.size();

        for (auto it = totals.begin(); it != totals.end(); ++it, ++i) {
            QPieSlice* slice = series->append(it.key(), it.value());

            // Generate a unique hue based on index
            int hue = (360 * i) / totalItems;  // evenly spaced around color wheel
            QColor color = QColor::fromHsv(hue, 200, 255);  // vibrant and bright

            slice->setBrush(color);
            slice->setPen(QPen(Qt::NoPen));
            slice->setLabelBrush(Qt::white);
            slice->setLabelFont(QFont("Arial", 10));
        }


    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundBrush(QBrush(QColor("#1e1e1e")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle(mode + " Pie Chart");



    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setLabelColor(Qt::white);
    chart->legend()->setFont(QFont("Arial", 10));



    for (auto slice : series->slices()) {
        slice->setLabelBrush(Qt::white);
        slice->setLabelFont(QFont("Arial", 10));
        slice->setPen(QPen(Qt::NoPen));
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->chartContainer);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);
}
