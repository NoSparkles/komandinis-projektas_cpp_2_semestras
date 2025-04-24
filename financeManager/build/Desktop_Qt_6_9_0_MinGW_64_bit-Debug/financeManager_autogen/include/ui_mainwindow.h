/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *chartContainer;
    QPushButton *modeButton;
    QTableWidget *dataTable;
    QLabel *label;
    QLabel *totalBalance;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setAutoFillBackground(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        chartContainer = new QWidget(centralwidget);
        chartContainer->setObjectName("chartContainer");
        chartContainer->setEnabled(true);
        chartContainer->setGeometry(QRect(0, 170, 281, 271));
        modeButton = new QPushButton(centralwidget);
        modeButton->setObjectName("modeButton");
        modeButton->setGeometry(QRect(90, 100, 80, 24));
        dataTable = new QTableWidget(centralwidget);
        if (dataTable->columnCount() < 5)
            dataTable->setColumnCount(5);
        dataTable->setObjectName("dataTable");
        dataTable->setGeometry(QRect(290, 100, 491, 421));
        dataTable->setColumnCount(5);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 10, 49, 16));
        totalBalance = new QLabel(centralwidget);
        totalBalance->setObjectName("totalBalance");
        totalBalance->setGeometry(QRect(330, 40, 131, 16));
        totalBalance->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(290, 540, 80, 24));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(700, 540, 80, 24));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        modeButton->setText(QCoreApplication::translate("MainWindow", "Select mode", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Balance:", nullptr));
        totalBalance->setText(QCoreApplication::translate("MainWindow", "24 000 Eur", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Save Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
