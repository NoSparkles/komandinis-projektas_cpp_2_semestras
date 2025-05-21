#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include "service/EntryService.h" 

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EntryService* entryService;
    void onAddButtonClicked();
    void updateChartAndTable(const QString &mode);
    void updateTypeFilter(const QString &mode);
    void onTableContextMenu(const QPoint &pos);
    void onTableCellChanged(int row, int column);
};

#endif // MAINWINDOW_H
