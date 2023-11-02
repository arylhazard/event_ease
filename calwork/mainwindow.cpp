#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set the initial size of the main window
    setMinimumSize(800, 600);

    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a vertical layout to hold combo boxes and the grid layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the month and year selectors
    QHBoxLayout *dateSelectorsLayout = new QHBoxLayout;

    // Create a grid layout for weekdays and dates
    gridLayout = new QGridLayout;

    // Add combo boxes for month and year
    QComboBox *monthCom = new QComboBox(this);
    QComboBox *yearComb = new QComboBox(this);

    // Assign combo boxes to class members for later access
    monthCombo = monthCom;
    yearCombo = yearComb;

    // Populate the month combo box
    monthCombo->addItem("Baisakh");
    monthCombo->addItem("Jestha");
    monthCombo->addItem("Asar");
    monthCombo->addItem("Shrawan");
    monthCombo->addItem("Bhadra");
    monthCombo->addItem("Ashwim");
    monthCombo->addItem("Kartik");
    monthCombo->addItem("Mangsir");
    monthCombo->addItem("Paush");
    monthCombo->addItem("Magh");
    monthCombo->addItem("Falgun");
    monthCombo->addItem("Chaitra");

    // Create the year combo box and set its width
    yearCombo->setFixedWidth(100);

    // Populate the year combo box with years from 1970 to 2100
    for (int year = 1970; year <= 2100; ++year) {
        yearCombo->addItem(QString::number(year));
    }

    // Connect signals to slots for combo box changes
    connect(monthCombo, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::updateCalendar);
    connect(yearCombo, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::updateCalendar);

    // Add the combo boxes to the dateSelectorsLayout
    dateSelectorsLayout->addWidget(monthCombo);
    dateSelectorsLayout->addWidget(yearCombo);

    // Add the dateSelectorsLayout to the main layout
    mainLayout->addLayout(dateSelectorsLayout);

    // Add the grid layout below the combo boxes
    mainLayout->addLayout(gridLayout);

    // Add labels for days of the week (customizable)
    QStringList daysOfWeek = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    for (int i = 0; i < 7; ++i) {
        QLabel *dayLabel = new QLabel(daysOfWeek[i]);
        // Add day labels to the grid layout in the first row
        gridLayout->addWidget(dayLabel, 0, i);
    }

    // Initially update the calendar based on combo box selections
    updateCalendar();
}

void MainWindow::updateCalendar()
{
    // Clear the existing gridLayout
    if (gridLayout) {
        QLayoutItem* child;
        while ((child = gridLayout->takeAt(0)) != 0) {
            // Delete any existing widgets within the gridLayout
            delete child->widget();
            delete child;
        }
    } else {
        qDebug() << "gridLayout is not properly initialized.";
        return; // Prevent further execution if gridLayout is not initialized
    }

    // Get the selected month and year from combo boxes
    selectedMonth = monthCombo->currentIndex();
    selectedYear = yearCombo->currentText().toInt();

    // Load JSON data from a file (adjust the path accordingly)
    QString jsonFilePath = "data.json";
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file. Handle the error accordingly.";
        return; // Prevent further execution in case of an error
    }
    QTextStream in(&jsonFile);
    QString jsonData = in.readAll();
    jsonFile.close();

    // Parse the JSON data
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject jsonDataObject = jsonDocument.object();

    // Access data for the selected year and month
    QJsonArray yearData = jsonDataObject[QString::number(selectedYear)].toArray();
    QJsonArray monthData = yearData[selectedMonth].toArray();

    // Retrieve the first day and last date of the month
    firstDay = monthData[0].toInt();
    lastDate = monthData[1].toInt();

    // Create date labels and add them to the grid layout
    int k = 1;
    for (int row = 1; row <= 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            QLabel *dateLabel = new QLabel(QString::number(k)); // You should set the actual date text
            if ((row == 1 && col >= firstDay) || (row > 1 && k <= lastDate)) {
                // Add the date label to the grid layout
                gridLayout->addWidget(dateLabel, row, col);
                k++;
            }
        }
    }
}
