#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->calendarWidget->setFirstDayOfWeek(Qt::Sunday);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    ui->calendarWidget->setNavigationBarVisible(false); // Hide navigation bar
    ui->calendarWidget->setDateEditEnabled(false); // Hide date navigation widget

    // Set date range to limit the calendar to the current month
    QDate currentDate = QDate::currentDate();
    ui->calendarWidget->setMinimumDate(currentDate.addDays(-currentDate.day() + 1));
    ui->calendarWidget->setMaximumDate(currentDate.addDays(currentDate.daysInMonth() - currentDate.day()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

//by this event you can get selected date in calendar
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    qDebug()<<"Selected Date: "<< date;
}

//BY this event you can get selected year and month in calendar
void MainWindow::on_calendarWidget_currentPageChanged(int year, int month)
{
    qDebug()<<"Selected year :"<<year;
    qDebug()<<"Selected Month:"<<month;
}

