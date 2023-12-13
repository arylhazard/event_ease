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
#include <QPushButton>
#include <QApplication>
#include <QDateTime>

#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1080,720);
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
    monthCombo->addItems({"Baisakh", "Jestha", "Asar", "Shrawan", "Bhadra", "Ashwin",
                          "Kartik", "Mangsir", "Paush", "Magh", "Falgun", "Chaitra"});

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
}
// createMainLayout function
void MainWindow::createMainLayout() {
    mainLayout = new QVBoxLayout;
    // Add components to the main layout
    // ...
}
// createSidebar function

void MainWindow::createSidebar() {
    sideWidget = new QWidget;
    QVBoxLayout *sideLayout = new QVBoxLayout;
    QStringList englishMonths = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    // Create dayInfo layout and add components to it
    QWidget *dayInfoWidget = new QWidget;
    QVBoxLayout *dayInfo = new QVBoxLayout(dayInfoWidget);
    dataLabel = new QLabel;
    dayInfo->addWidget(dataLabel);

    dayInfoWidget->setStyleSheet("background-color: #FF6347;"); // Tomato color
    // Create note input for dayInfo
    noteInput = new QLineEdit;
    
    dayInfo->addWidget(noteInput);

    // Create convertDate layout and add components to it
    QWidget *convertDateWidget = new QWidget;
    QVBoxLayout *convertDate = new QVBoxLayout(convertDateWidget);
    QLabel *dateLabel = new QLabel("Convert Date");
    convertDate->addWidget(dateLabel);

    // Create conversion mode button
    QPushButton *convertModeButton = new QPushButton;
    convertModeButton->setCheckable(true);
    convertModeButton->setText("AD to BS");
    convertModeButton->setStyleSheet("background-color: #ADD8E6; color: white; padding: 5px;");

    // Set an icon for the button
    convertModeButton->setIcon(QIcon("assets/icons/switch.png")); // Replace with the path to your icon

    convertDate->addWidget(convertModeButton);

    // Connect toggled signal to lambda function that updates the button's text
    connect(convertModeButton, &QPushButton::toggled, [convertModeButton](bool checked) {
        if (checked) {
            convertModeButton->setText("BS to AD");
        } else {
            convertModeButton->setText("AD to BS");
        }
    });

    // Create date edit for conversion
    QLineEdit *convertDateEdit = new QLineEdit;
    convertDateEdit->setPlaceholderText("YYYY/MM/DD");
    convertDate->addWidget(convertDateEdit);

    // Create convert button
    QPushButton *convertButton = new QPushButton("Convert");
    convertDate->addWidget(convertButton);

    // Create result label for conversion
    QLabel *convertResultLabel = new QLabel;
    convertDate->addWidget(convertResultLabel);

    // Connect convertButton's clicked signal to a slot that performs the conversion
    connect(convertButton, &QPushButton::clicked, [this, convertDateEdit, convertResultLabel, convertModeButton, englishMonths]() {
        QString dateStr = convertDateEdit->text();
        qDebug() << "Date string: " << dateStr;
        QStringList dateParts = dateStr.split("/");
        if (dateParts.size() != 3) {
            // Invalid date format
            convertResultLabel->setText("Invalid date format. Please enter date as YYYY/MM/DD.");
            return;
        }
        qDebug() << "Year string: " << dateParts[0].toInt();    
qDebug() << "Day string: " << dateParts[2].toInt();
        QString year = dateParts[0];
        QString month = dateParts[1];
        QString day = dateParts[2];
        QString mode = convertModeButton->text();

        // Perform the conversion
        date temp;
        QString result;
        if (mode == "AD to BS") {
            qDebug() << "Converting from AD to BS. Year: " << year << " Month: " << englishMonths.at(month.toInt()-1) << " Day: " << day;
            temp = convertADtoBS(year.toInt(), englishMonths.at(month.toInt()-1), day.toInt());        } 
        else {
            date dateToConvert;
            dateToConvert.year = year;
            dateToConvert.month = months.at(month.toInt()-1);
            dateToConvert.day = day;

            qDebug() << "Converting from BS to AD. Year: " << dateToConvert.year << " Month: " << dateToConvert.month << " Day: " << dateToConvert.day;
            temp = convertBStoAD(dateToConvert);
            qDebug() << "Converted date. Year: " << temp.year << " Month: " << temp.month << " Day: " << temp.day;                    
        }
        result=QString("%1/%2/%3").arg(temp.year).arg(temp.month).arg(temp.day);
 
        // Update the result label
        convertResultLabel->setText(result);
    });

    convertDateWidget->setStyleSheet("background-color: #B974C2;"); 

    // Add dayInfo and convertDate to the side layout
    sideLayout->addWidget(dayInfoWidget,4);
    sideLayout->addWidget(convertDateWidget,6);

    // Set the side layout on the side widget
    sideWidget->setLayout(sideLayout);

    // Set the background color of the side widget
    sideWidget->setStyleSheet("background-color: #343746;");
}

void MainWindow::updateCalendar()
{
    int currentEnglishYear = QDate::currentDate().year();
    int currentEnglishDay = QDate::currentDate().day();
    QString currentEnglishMonth = QDate::currentDate().toString("MMM");

    if (!dateSyncedOnce)
    {
        date currentNepaliDate = convertADtoBS(currentEnglishYear, currentEnglishMonth, currentEnglishDay);
        yearCombo->setCurrentText(currentNepaliDate.year);
        monthCombo->setCurrentIndex(months.indexOf(currentNepaliDate.month));
        currentNepaliDay =currentNepaliDate.day;
        currentNepaliMonth = currentNepaliDate.month;
        currentNepaliYear = currentNepaliDate.year;

        // Create the full Nepali and English dates
        QString fullNepaliDate = currentNepaliDay + " " + currentNepaliMonth + " " + currentNepaliYear;
        QString fullEnglishDate = QString::number(currentEnglishDay) + " " + currentEnglishMonth + " " + QString::number(currentEnglishYear);

        dataLabel->setText("Nepali Date: " + fullNepaliDate + "\nEnglish Date: " + fullEnglishDate);
        noteInput->setPlaceholderText("Notes for "+fullNepaliDate);
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
            {
                enFirstOrSecond = nepaliDay.toInt();
            }
            qDebug() << "Condition Check - Nepali Day: " << (nepaliDay == currentNepaliDay);
            qDebug() << "Current Nepali Year: " << currentNepaliYear;
            qDebug() << "Converted Year from Combo: " << yearCombo->currentText().toInt();
            qDebug() << "Condition Check - Nepali Year: "<<currentNepaliYear<<"=="<<yearCombo->currentText()<< (currentNepaliYear == yearCombo->currentText());
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

            void MainWindow::resizeEvent(QResizeEvent *event)
            {
                QMainWindow::resizeEvent(event);

                QSize newSize = size();
                if (newSize.width() / 16 != newSize.height() / 9) {
                    newSize.setHeight(newSize.width() *(9/16)); //
                    resize(newSize);
                }
            }

            void MainWindow::updateData() {
                // Get the clicked button
                QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
                if (clickedButton)
                {
                    // Get the button identifier and corresponding day information
                    int buttonIdentifier = clickedButton->property("dateIdentifier").toInt();
                    QJsonObject day = days[buttonIdentifier].toObject();
                    QString nepaliDay = day["nepaliDay"].toString();
                    QString englishDay = day["englishDay"].toString();
                    QJsonArray nepaliDate = metadata["nepaliDate"].toArray();
                    QJsonArray enBeginning = metadata["enBeginning"].toArray();
                    QJsonArray enEnding = metadata["enEnding"].toArray();

                    // Create the full Nepali and English dates
                    QString fullNepaliDate = nepaliDay + " " + nepaliDate[0].toString() + " " + nepaliDate[1].toString();
                    bool isSecondEnglishMonth = (nepaliDay.toInt() >= enFirstOrSecond);
                    QString fullEnglishDate = englishDay + " " + (isSecondEnglishMonth ? (enEnding[0].toString() + " " + enEnding[1].toString()) : (enBeginning[0].toString() + " " + enBeginning[1].toString()));

                    // Update the text of dataLabel
                    dataLabel->setText("Nepali Date: " + fullNepaliDate + "\nEnglish Date: " + fullEnglishDate);
                    noteInput->setPlaceholderText("Notes for "+fullNepaliDate);

                }
            }

            MainWindow::date MainWindow::convertADtoBS(int currentEnglishYear, QString currentEnglishMonth, int currentEnglishDay)
            {
                date nepaliDate;
                bool forward = true;
                bool backward = true;

                int begYear = 1992;
                int endYear = 2099;
                int midYear;

                int m = 8;
                int iterationCount = 0; // Counter for the number of iterations

                while (iterationCount < 50)
                {
                    iterationCount++;

                    midYear = (begYear + endYear) / 2;
                    QString tempFilePath = QString("assets/data/%1/%2.json").arg(midYear).arg(months.at(m));
                    QFile tempFile(tempFilePath);
                    qDebug() << "Iteration:" << iterationCount;
                    qDebug() << "Mid Year:" << midYear;
                    qDebug() << "File Path:" << tempFilePath;

                    if (!tempFile.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        qDebug() << "Failed to open JSON file at the start";
                        return nepaliDate;
                    }

                    QTextStream in(&tempFile);
                    QString tempData = in.readAll();
                    tempFile.close();
                    // qDebug() << "File Data:" << tempData;

                    // Parse JSON data
                    QJsonDocument tempDocument = QJsonDocument::fromJson(tempData.toUtf8());
                    QJsonObject tempRoot = tempDocument.object();

                    // Extract metadata and days arrays
                    QJsonObject tempmetadata = tempRoot["metadata"].toObject();
                    qDebug() << "Metadata:" << tempmetadata;

                    QJsonArray tempNepaliDate = tempmetadata["nepaliDate"].toArray();
                    QJsonArray tempEnBeginning = tempmetadata["enBeginning"].toArray();
                    QJsonArray tempEnEnding = tempmetadata["enEnding"].toArray();
                    QJsonArray tempdays = tempRoot["days"].toArray();

                    if (tempEnBeginning[1].toString().toInt() == currentEnglishYear && backward)
                    {
                        if (tempEnBeginning[0].toString() == currentEnglishMonth)
                        {
                            for (const QJsonValue &dayValue : tempdays)
                            {
                                QJsonObject dayObject = dayValue.toObject();

                                if (dayObject["englishDay"].toString().toInt() == currentEnglishDay)
                                {
                                    dateSyncedOnce = true;
                                    nepaliDate.year = tempNepaliDate[1].toString();
                                    nepaliDate.month = months.at(m);
                                    nepaliDate.day = dayObject["nepaliDay"].toString();
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (m == 0)
                            {
                                m = 11;
                                midYear--;
                            }
                            else
                                m--;
                            forward = false;
                        }
                    }
                    else if (tempEnEnding[1].toString().toInt() == currentEnglishYear && forward)
                    {
                        if (tempEnEnding[0].toString() == currentEnglishMonth)
                        {
                            for (const QJsonValue &dayValue : tempdays)
                            {
                                QJsonObject dayObject = dayValue.toObject();

                                if (dayObject["englishDay"].toString().toInt() == currentEnglishDay)
                                {
                                    dateSyncedOnce = true;
                                    nepaliDate.year = tempNepaliDate[1].toString();
                                    nepaliDate.month = months.at(m);
                                    nepaliDate.day = dayObject["nepaliDay"].toString();
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (m == 11)
                            {
                                m = 0;
                                midYear++;
                            }
                            else
                                m++;
                            backward = false;
                        }
                    }
                    else
                    {
                        if (currentEnglishYear < tempEnBeginning[1].toString().toInt())
                        {
                            endYear = midYear - 1;
                        }
                        else if (currentEnglishYear > tempEnEnding[1].toString().toInt())
                        {
                            begYear = midYear + 1;
                        }
                    }
                }
                qDebug() << "Finished conversion. Nepali Year: " << nepaliDate.year << " Month: " << nepaliDate.month << " Day: " << nepaliDate.day;

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
                        if(nepaliDate.day.toInt()>=enFirstOrSecondConv)
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
