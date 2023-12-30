#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

// Entry point for the application
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    MainWindow mainWindow;

    // Apply styles from an external file
    QFile styleFile("styles.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        app.setStyleSheet(stream.readAll());
        styleFile.close();
    }

    // Display the main window
    mainWindow.show();

    // Start the application event loop
    return app.exec();
}

void MainWindow::previousMonth() {
    // Move to the previous month in the combo boxes
    int selectedMonth = monthCombo->currentIndex();
    int selectedYear = yearCombo->currentIndex();

    if (selectedMonth > 0) {
        monthCombo->setCurrentIndex(selectedMonth - 1);
    } else if (selectedYear > 0) {
        // If at January, switch to the previous year
        monthCombo->setCurrentIndex(11); // December
        yearCombo->setCurrentIndex(selectedYear - 1);
    }

    // Update the calendar grid
    updateCalendar();
}

void MainWindow::nextMonth() {
    // Move to the next month in the combo boxes
    int selectedMonth = monthCombo->currentIndex();
    int selectedYear = yearCombo->currentIndex();

    if (selectedMonth < 11) {
        monthCombo->setCurrentIndex(selectedMonth + 1);
    } else {
        // If at December, switch to the next year
        monthCombo->setCurrentIndex(0); // January
        yearCombo->setCurrentIndex(selectedYear + 1);
    }

    // Update the calendar grid
    updateCalendar();
}
void MainWindow::increaseMonth(int& month, int& year)
{
    if (month == 11)
    {
        month = 0;
        year++;
    }
    else
    {
        month++;
    }
    qDebug() << "Increased month to " << month << ", year is now " << year;
}

void MainWindow::decreaseMonth(int& month, int& year)
{
    if (month == 0)
    {
        month = 11;
        year--;
    }
    else
    {
        month--;
    }
    qDebug() << "Decreased month to " << month << ", year is now " << year;
}
