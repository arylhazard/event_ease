#include <QGridLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QApplication>
#include <QDateTime>
#include "mainwindow.h"
#include "sidebar.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    noteDisplay = new QLineEdit(this);
    noteInput = new QLineEdit(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../Databse/project"); //Add the path to your database//

    if(mydb.open())
    {
        qDebug()<<"Database is Connected";
    }
    else
    {

        qDebug()<<"Database is Not Connected";
        qDebug()<<"Error:"<<mydb.lastError();
    }
    setMinimumSize(1080, 720);
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    createMainLayout();
    createSidebar();

    totalLayout = new QHBoxLayout;

    // Add the side widget to the total layout
    totalLayout->addWidget(sideWidget, 2); // 20% of the total width

    // Add your existing layout to the QHBoxLayout
    totalLayout->addLayout(mainLayout, 8);

    // Set the total layout on the central widget
    centralWidget->setLayout(totalLayout);

    gridLayout = new QGridLayout;

    // Create combo boxes for month and year
    monthCombo = new QComboBox(this);
    yearCombo = new QComboBox(this);

    // Populate month combo box
    monthCombo->addItems(months);

    // Populate year combo box
    yearCombo->setFixedWidth(80);
    for (int year = 1992; year <= 2099; ++year)
    {
        yearCombo->addItem(QString::number(year));
    }

    // Create previous and next buttons for navigation
    QPushButton *previousButton = new QPushButton;
    previousButton->setIcon(QIcon("assets/icons/prev.png"));
    QPushButton *nextButton = new QPushButton;
    nextButton->setIcon(QIcon("assets/icons/next.png"));

    // Connect navigation button signals to slots to actually navigate
    connect(previousButton, &QPushButton::clicked, this, &MainWindow::previousMonth);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextMonth);

    // Create top layout and add widgets
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(previousButton);
    topLayout->addWidget(monthCombo);
    topLayout->addWidget(yearCombo);
    topLayout->addWidget(nextButton);

    // Add top layout and grid layout to the main layout
    mainLayout->addLayout(topLayout);

    connect(monthCombo, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::updateCalendar);
    connect(yearCombo, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::updateCalendar);

    mainLayout->addLayout(gridLayout);
    // Updating the calendar,This function also is automatically  called whenever there is a change in combobox re-populating datebuttons.
    updateCalendar();
    initSidebar();
}
// createMainLayout function

void MainWindow::createMainLayout()
{
    mainLayout = new QVBoxLayout;
    // Add components to the main layout
    // ...
}
// createSidebar function

void MainWindow::updateCalendar()
{
    currentEnglishYear = QDate::currentDate().year();
    currentEnglishDay = QDate::currentDate().day();
    currentEnglishMonth = QDate::currentDate().toString("MMM");

    if (!dateSyncedOnce)
    {
        date currentNepaliDate = convertADtoBS(currentEnglishYear, currentEnglishMonth, currentEnglishDay);
        yearCombo->setCurrentText(currentNepaliDate.year);
        monthCombo->setCurrentIndex(months.indexOf(currentNepaliDate.month));
        currentNepaliDay = currentNepaliDate.day;
        currentNepaliMonth = currentNepaliDate.month;
        currentNepaliYear = currentNepaliDate.year;

        // Create the full Nepali and English dates

        dateSyncedOnce = true;
    }

    // Clear the gridLayout
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    // Add day labels to the gridLayout
    QStringList daysOfWeek = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    for (int i = 0; i < 7; ++i)
    {
        QLabel *dayLabel = new QLabel(daysOfWeek[i]);
        gridLayout->addWidget(dayLabel, 0, i);
    }

    // Retrieve selectedMonth and selectedYear from the combo boxes
    selectedMonth = monthCombo->currentIndex();
    selectedYear = yearCombo->currentText().toInt();

    // Construct JSON file path
    QString jsonFilePath = QString("assets/data/%1/%2.json").arg(selectedYear).arg(monthCombo->currentText());

    // Open and read JSON file
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open JSON file.";
        return;
    }

    QTextStream in(&jsonFile);
    QString jsonData = in.readAll();
    jsonFile.close();

    // Parse JSON data
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject root = jsonDocument.object();

    // Extract metadata and days arrays
    metadata = root["metadata"].toObject();
    days = root["days"].toArray();

    // Populate the gridLayout with date buttons
    for (int row = 1; row <= 5; ++row)
    {
        for (int col = 0; col < 7; ++col)
        {
            QJsonObject day = days[((row - 1) * 7 + col)].toObject();
            QString nepaliDay = day["nepaliDay"].toString();
            QString englishDay = day["englishDay"].toString();
            bool isHoliday = day["isHoliday"].toBool();

            QPushButton *dateButton = new QPushButton;

            // Determine if the month starts with the English day 1
            if (englishDay.toInt() == 1)
            {   englishDay =metadata.value("enEnding").toArray().at(0).toString().toUpper() + " " +englishDay;
                enFirstOrSecond = nepaliDay.toInt();
            }
            qDebug() << "Condition Check - Nepali Day: " << (nepaliDay == currentNepaliDay);
            qDebug() << "Current Nepali Year: " << currentNepaliYear;
            qDebug() << "Converted Year from Combo: " << yearCombo->currentText().toInt();
            qDebug() << "Condition Check - Nepali Year: " << currentNepaliYear << "==" << yearCombo->currentText() << (currentNepaliYear == yearCombo->currentText());
            qDebug() << "Condition Check - Nepali Month: " << (currentNepaliMonth == monthCombo->currentText());
            qDebug() << "Final Condition Check: " << (nepaliDay == currentNepaliDay && currentNepaliYear == yearCombo->currentText() && currentNepaliMonth == monthCombo->currentText());

            QLabel *nepaliLabel = new QLabel(nepaliDay);
            QLabel *englishLabel = new QLabel(englishDay);
            if (!nepaliDay.isEmpty())
            {
                if (nepaliDay == currentNepaliDay && currentNepaliYear == yearCombo->currentText() && currentNepaliMonth == monthCombo->currentText())
                {
                    dateButton->setObjectName("currentDateButton");
                    dateButton->setStyleSheet("QPushButton#currentDateButton:hover { color: #FFFFFF; background: qradialgradient(cx: 0.5, cy: 0.5, radius: 1, fx: 0.5, fy: 0.5, stop: 0 #1C5D99, stop: 0.8 #1C5D99, stop: 0.79 transparent, stop: 1 transparent);}"
                                              "QPushButton#currentDateButton { border-radius:20px;background-color: #282A36; }");
                    qDebug() << "The Date syncing is done, and today's date stylesheet has been set";
                }
                else
                {
                    dateButton->setObjectName("dateButton");
                    dateButton->setStyleSheet("QPushButton#dateButton:hover {border-radius:20px; color: #FFFFFF; background: qradialgradient(cx: 0.5, cy: 0.5, radius: 1, fx: 0.5, fy: 0.5, stop: 0 #1C5D99, stop: 0.8 #1C5D99, stop: 0.79 transparent, stop: 1 transparent);}");
                }

                // Common properties for all dates
                dateButton->setProperty("dateIdentifier", (row - 1) * 7 + col);

                // Connect the button click to the custom slot
                connect(dateButton, &QPushButton::clicked, this, &MainWindow::updateData);
            }
            else
            {
                // Properties for empty dates
                dateButton->setProperty("class", "emptyDateButton");
            }

            if (isHoliday)
            {
                // Highlight holiday labels in red
                englishLabel->setStyleSheet("font-size: 12px; background: none; border: none; color:red");
                nepaliLabel->setStyleSheet("font-size: 24px; background: none; border: none; color:red");
            }
            else
            {
                nepaliLabel->setStyleSheet("font-size: 18px; background: none; border: none;");
                englishLabel->setStyleSheet("font-size: 10px; background: none; border: none; margin:10px;");
            }

            englishLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
            nepaliLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

            dateButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
            gridLayout->addWidget(dateButton, row, col);

            QVBoxLayout *labelLayout = new QVBoxLayout(dateButton);
            labelLayout->addWidget(nepaliLabel);
            labelLayout->addWidget(englishLabel);
        }
    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QSize newSize = size();
    if (newSize.width() / 16.0 != newSize.height() / 9.0)
    {
        newSize.setHeight(newSize.width() * (9.0 / 16.0)); //
        resize(newSize);
    }
}


// Function to convert AD to BS
MainWindow::date MainWindow::convertADtoBS(int EnglishYear, QString EnglishMonth, int EnglishDay)
{
    // Initialize variables
    date nepaliDate;
    bool forward = true;
    bool backward = true;
    int begYear = 1992;
    int endYear = 2099;
    int midYear;
    int m = 8;
    int iterationCount = 0; // Counter for the number of iterations

    // Loop until iterationCount is less than 50
    while (iterationCount < 50)
    {
        iterationCount++;
        midYear = (begYear + endYear) / 2;
        QString tempFilePath = QString("assets/data/%1/%2.json").arg(midYear).arg(months.at(m));
        QFile tempFile(tempFilePath);

        // Debug statements
        qDebug() << "\nIteration:" << iterationCount;
        qDebug() << "Mid Year:" << midYear;
        qDebug() << "File Path:" << tempFilePath;

        // Open file
        if (!tempFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open JSON file at the start";
            return nepaliDate;
        }

        // Read file
        QTextStream in(&tempFile);
        QString tempData = in.readAll();
        tempFile.close();

        // Parse JSON data
        QJsonDocument tempDocument = QJsonDocument::fromJson(tempData.toUtf8());
        QJsonObject tempRoot = tempDocument.object();

        // Extract metadata and days arrays
        QJsonObject tempmetadata = tempRoot["metadata"].toObject();
        QJsonArray tempNepaliDate = tempmetadata["nepaliDate"].toArray();
        QJsonArray tempEnBeginning = tempmetadata["enBeginning"].toArray();
        QJsonArray tempEnEnding = tempmetadata["enEnding"].toArray();
        QJsonArray tempdays = tempRoot["days"].toArray();

        // Check if current English year matches the beginning year in the JSON data
        if (tempEnBeginning[1].toString().toInt() == EnglishYear && backward)
        {
            qDebug() << "Iterating backwards";
            if (tempEnBeginning[0].toString() == EnglishMonth)
            {
                qDebug() << "Month matches, checking days";
                for (const QJsonValue &dayValue : tempdays)
                {
                    QJsonObject dayObject = dayValue.toObject();

                    // Check if current English day matches the day in the JSON data
                    if (dayObject["englishDay"].toString().toInt() == EnglishDay)
                    {
                        qDebug() << "Day matches. Syncing date.";
                        
                        nepaliDate.year = tempNepaliDate[1].toString();
                        nepaliDate.month = months.at(m);
                        nepaliDate.day = dayObject["nepaliDay"].toString();
                        qDebug() << "Synced Nepali Date: " << nepaliDate.day << " " << nepaliDate.month << " " << nepaliDate.year;
                        return nepaliDate;
                    }
                }
                decreaseMonth(m, midYear);
            }
            else
            {
                qDebug() << "Month does not match, moving to previous month";
                decreaseMonth(m, midYear);
                forward = false;
            }
        }
        // Check if current English year matches the ending year in the JSON data
        else if (tempEnEnding[1].toString().toInt() == EnglishYear && forward)
        {
            qDebug() << "Iterating forward";
            if (tempEnEnding[0].toString() == EnglishMonth)
            {
                qDebug() << "Month matches, checking days";
                for (const QJsonValue &dayValue : tempdays)
                {
                    QJsonObject dayObject = dayValue.toObject();

                    // Check if current English day matches the day in the JSON data
                    if (dayObject["englishDay"].toString().toInt() == EnglishDay)
                    {
                        dateSyncedOnce = true;
                        nepaliDate.year = tempNepaliDate[1].toString();
                        nepaliDate.month = months.at(m);
                        nepaliDate.day = dayObject["nepaliDay"].toString();
                        break;
                    }
                }
                increaseMonth(m, midYear);
                forward = false;
                backward = true;
            }
            else
            {
                qDebug() << "Month does not match, moving to next month";
                increaseMonth(m, midYear);
                backward = false;
            }
        }
        else
        {
            qDebug() << "Adjusting year range";
            if (EnglishYear < tempEnBeginning[1].toString().toInt())
            {
                endYear = midYear - 1;
            }
            else if (EnglishYear > tempEnEnding[1].toString().toInt())
            {
                begYear = midYear + 1;
            }
        }
    }
    qDebug() << "\nFinished conversion. Nepali Year: " << nepaliDate.year << " Month: " << nepaliDate.month << " Day: " << nepaliDate.day;

    return nepaliDate;
}


MainWindow::date MainWindow::convertBStoAD(date nepaliDate)
{
    qDebug() << "Converting from BS to AD. Year: " << nepaliDate.year << " Month: " << nepaliDate.month << " Day: " << nepaliDate.day;

    date englishDate;
    int enFirstOrSecondConv = -1;

    // Construct the file path for the JSON file
    QString filePath = QString("assets/data/%1/%2.json").arg(nepaliDate.year).arg(nepaliDate.month);
    qDebug() << "File path: " << filePath;

    // Open the JSON file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open JSON file";
        return englishDate;
    }

    // Read the JSON data
    QTextStream in(&file);
    QString data = in.readAll();
    file.close();
    QJsonArray metaDataArray;
    // Parse the JSON data
    QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject root = document.object();
    QJsonArray days = root["days"].toArray();

    // Find the English date for the Nepali day
    for (const QJsonValue &dayValue : days)
    {
        QJsonObject dayObject = dayValue.toObject();
        if (dayObject["englishDay"].toString().toInt() == 1)
        {
            enFirstOrSecondConv = dayObject["nepaliDay"].toString().toInt();
            qDebug() << "Found the first or second English month. Nepali day: " << enFirstOrSecondConv;
        }
    }
    for (const QJsonValue &dayValue : days)
    {
        QJsonObject dayObject = dayValue.toObject();

        if (dayObject["nepaliDay"].toString() == nepaliDate.day)
        {
            if (nepaliDate.day.toInt() >= enFirstOrSecondConv)
            {
                metaDataArray = root["metadata"].toObject()["enEnding"].toArray();
            }
            else
            {
                metaDataArray = root["metadata"].toObject()["enBeginning"].toArray();
            }
            englishDate.day = dayObject["englishDay"].toString();
            englishDate.month = metaDataArray[0].toString();
            englishDate.year = metaDataArray[1].toString();
            qDebug() << "Match found. English date. Year: " << englishDate.year << " Month: " << englishDate.month << " Day: " << englishDate.day;
            break;
        }
    }

    qDebug() << "Converted date. Year: " << englishDate.year << " Month: " << englishDate.month << " Day: " << englishDate.day;

    return englishDate;
}
