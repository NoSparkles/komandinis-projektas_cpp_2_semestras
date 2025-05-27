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
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>


#include "model/Income.h"
#include "model/Expense.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateEdit  ->setDate(QDate(2000, 1, 1));
    ui->dateEdit_2->setDate(QDate::currentDate());

    entryService = new EntryService("data/income.csv", "data/expense.csv");

    connect(ui->typeSelect, &QComboBox::currentTextChanged,
            this, [this]{ updateChartAndTable(ui->modeButton->text()); });

    connect(ui->pushButton_3, &QPushButton::clicked,
            this, [this]{ updateChartAndTable(ui->modeButton->text()); });


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

void MainWindow::onTableCellChanged(int row, int column)
{
    if (column == 0) return;

    static bool reentry = false;
    if (reentry) return;
    reentry = true;

    /* retrieve the Entry* we stored in column 0 */
    QTableWidgetItem *first = ui->dataTable->item(row, 0);
    if (!first) { reentry = false; return; }

    quintptr raw   = first->data(Qt::UserRole).value<quintptr>();
    Entry   *entry = reinterpret_cast<Entry*>(raw);
    if (!entry) { reentry = false; return; }

    /* fetch edited values */
    QString newDate = ui->dataTable->item(row,1)->text();
    QString newName = ui->dataTable->item(row,2)->text();
    bool ok = false;
    double  newAmount = ui->dataTable->item(row,3)->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input", "Amount must be numeric.");
        reentry = false;
        return;
    }

    /* update the real object */
    if (auto *ex = dynamic_cast<Expense*>(entry)) {
        ex->setDate  (newDate.toStdString());
        ex->setName  (newName.toStdString());
        ex->setAmount(newAmount);
    } else if (auto *in = dynamic_cast<Income*>(entry)) {
        in->setDate  (newDate.toStdString());
        in->setName  (newName.toStdString());
        in->setAmount(newAmount);
    }

    updateChartAndTable(ui->modeButton->text());
    reentry = false;
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

std::shared_ptr<Filter> MainWindow::createFilterChain() const
{
    using std::make_shared;

    std::shared_ptr<Filter> chain = make_shared<BaseFilter>();

    const QDate from = ui->dateEdit ->date();
    const QDate to   = ui->dateEdit_2->date();
    if (from != QDate(2000,1,1) || to != QDate::currentDate()) {
        chain = make_shared<DateFilter>(chain,
                                        from.toString("yyyy-MM-dd").toStdString(),
                                        to  .toString("yyyy-MM-dd").toStdString());
    }

    bool minOk = false, maxOk = false;
    double minA = ui->lineEdit_2->text().toDouble(&minOk);
    double maxA = ui->lineEdit_3->text().toDouble(&maxOk);
    if (minOk || maxOk) {
        if (!minOk) minA = 0.0;
        if (!maxOk) maxA = std::numeric_limits<double>::max();
        chain = make_shared<AmountFilter>(chain, minA, maxA);
    }

    const QString t = ui->typeSelect->currentText();
    if (t != "None")
        chain = make_shared<TypeFilter>(chain, t.toStdString());

    const QString n = ui->lineEdit->text().trimmed();
    if (!n.isEmpty())
        chain = make_shared<NameFilter>(chain, n.toStdString());

    return chain;
}


void MainWindow::updateChartAndTable(const QString &mode)
{
    QSignalBlocker guard(ui->dataTable);
    auto chain = createFilterChain();

    double totalIncome = 0.0, totalExpense = 0.0;
    for (const auto &i : entryService->getAllIncomes())  totalIncome  += i.getAmount();
    for (const auto &e : entryService->getAllExpenses()) totalExpense += e.getAmount();
    ui->totalBalance->setText(QString::number(totalIncome - totalExpense, 'f', 2) + " Eur");

    std::vector<Entry*> base;
    if (mode == "Expenses") {
        const auto &all = entryService->getAllExpenses();
        base.reserve(all.size());
        for (const auto &e : all) base.push_back(const_cast<Expense*>(&e));
    } else {                                     // Income
        const auto &all = entryService->getAllIncomes();
        base.reserve(all.size());
        for (const auto &e : all) base.push_back(const_cast<Income*>(&e));
    }
    this->filteredItems = chain->apply(base);

    if (QLayout *old = ui->chartContainer->layout()) {
        while (QLayoutItem *it = old->takeAt(0)) { delete it->widget(); delete it; }
        delete old;
    }

    ui->dataTable->clear();
    ui->dataTable->setRowCount(static_cast<int>(this->filteredItems.size()));
    ui->dataTable->setColumnCount(4);
    ui->dataTable->setHorizontalHeaderLabels({"Type","Date","Name","Amount"});

    QMap<QString,double> totals;
    for (int row = 0; row < this->filteredItems.size(); ++row) {
        if (mode == "Expenses") {
            auto *ex = static_cast<Expense*>(this->filteredItems[row]);

            auto *typeItem = new QTableWidgetItem(QString::fromStdString(ex->getType()));
            typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
            typeItem->setData(Qt::UserRole,
                              QVariant::fromValue<quintptr>(reinterpret_cast<quintptr>(ex)));
            ui->dataTable->setItem(row, 0, typeItem);

            ui->dataTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ex->getDate())));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(ex->getName())));
            ui->dataTable->setItem(row, 3, new QTableWidgetItem(QString::number(ex->getAmount())));
            totals[QString::fromStdString(ex->getType())] += ex->getAmount();
        } else {
            auto *in = static_cast<Income*>(this->filteredItems[row]);

            auto *typeItem = new QTableWidgetItem(QString::fromStdString(in->getType()));
            typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
            typeItem->setData(Qt::UserRole,
                              QVariant::fromValue<quintptr>(reinterpret_cast<quintptr>(in)));
            ui->dataTable->setItem(row, 0, typeItem);

            ui->dataTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(in->getDate())));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(in->getName())));
            ui->dataTable->setItem(row, 3, new QTableWidgetItem(QString::number(in->getAmount())));
            totals[QString::fromStdString(in->getType())] += in->getAmount();
        }
    }

    QPieSeries *series = new QPieSeries();
    int idx = 0, totalSlices = totals.size();
    for (auto it = totals.cbegin(); it != totals.cend(); ++it, ++idx) {
        auto *slice = series->append(it.key(), it.value());
        int hue = (360 * idx) / (totalSlices == 0 ? 1 : totalSlices);
        slice->setBrush(QColor::fromHsv(hue, 200, 255));
        slice->setPen(Qt::NoPen);
        slice->setLabelBrush(Qt::white);
    }
    if (series->count() == 0) return;

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setBackgroundBrush(QColor("#1e1e1e"));
    chart->setTitleBrush(Qt::white);
    chart->setTitle(mode + " Pie Chart");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->legend()->setLabelColor(Qt::white);

    auto *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    auto *layout = new QVBoxLayout(ui->chartContainer);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
}

void MainWindow::on_exportButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "CSV Files (*.csv);;All Files (*)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write header (Including ID)
    QStringList headers = {"ID", "Type", "Date", "Name", "Amount"};
    out << headers.join(",") << "\n";

    // Iterate through filteredItems instead of dataTable
    for (const auto &entry : filteredItems) {
        QString id = QString::number(entry->getId());   // Assuming Entry has an `getId()` method
        QString type = QString::fromStdString(entry->getType());
        QString date = QString::fromStdString(entry->getDate());
        QString name = QString::fromStdString(entry->getName());
        QString amount = QString::number(entry->getAmount(), 'f', 2);

        out << QStringList{id, type, date, name, amount}.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Data exported successfully.");
}
