#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QCalendarWidget>
#include <QComboBox>
#include <QJsonObject>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int selectedMonth;
    int selectedYear;

private slots:
    void updateCalendar();

private:

    QCalendarWidget *calendarWidget;
    QComboBox *monthCombo;
    QComboBox *yearCombo;
    QJsonObject jsonDataObject;
    int firstDay;
    int lastDate;
    QGridLayout *gridLayout;

};

#endif // MAINWINDOW_H
