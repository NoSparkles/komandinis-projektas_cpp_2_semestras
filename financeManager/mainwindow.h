#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QMenu>
#include <QPoint>

#include <memory>
#include <limits>

#include "service/EntryService.h"

#include "filter/BaseFilter.h"
#include "filter/DateFilter.h"
#include "filter/AmountFilter.h"
#include "filter/TypeFilter.h"
#include "filter/NameFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onAddButtonClicked();
    void onTableContextMenu(const QPoint &pos);
    void onTableCellChanged(int row, int column);

    void updateTypeFilter(const QString &mode);

    void on_exportButton_clicked();

private:
    std::shared_ptr<Filter> createFilterChain() const;

    void updateChartAndTable(const QString &mode);

    Ui::MainWindow *ui {nullptr};
    EntryService   *entryService {nullptr};
    std::vector<Entry*> filteredItems;
};

#endif
