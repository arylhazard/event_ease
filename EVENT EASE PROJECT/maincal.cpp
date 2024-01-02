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
#include "maincal.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QDebug>
#include <QSpinBox>

MainCal::MainCal(QString userId, QWidget *parent) : QMainWindow(parent)
{     
    eventUserId=userId;
    noteDisplay = new QLineEdit(this);
    noteInput = new QLineEdit(this);

    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./database/project"); //Add the path to your database//

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
    connect(previousButton, &QPushButton::clicked, this, &MainCal::previousMonth);
    connect(nextButton, &QPushButton::clicked, this, &MainCal::nextMonth);

    // Create top layout and add widgets
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(previousButton);
    topLayout->addWidget(monthCombo);
    topLayout->addWidget(yearCombo);
    topLayout->addWidget(nextButton);

    // Add top layout and grid layout to the main layout
    mainLayout->addLayout(topLayout);

    connect(monthCombo, QOverload<int>::of(&QComboBox::activated), this, &MainCal::updateCalendar);
    connect(yearCombo, QOverload<int>::of(&QComboBox::activated), this, &MainCal::updateCalendar);

    mainLayout->addLayout(gridLayout);
    // Updating the calendar,This function also is automatically  called whenever there is a change in combobox re-populating datebuttons.
    updateCalendar();
    initSidebar();
}
// createMainLayout function

void MainCal::createMainLayout()
{
    mainLayout = new QVBoxLayout;
    // Add components to the main layout
    // ...
}
// createSidebar function

void MainCal::updateCalendar()
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
            dayLabel->setStyleSheet("background-color: transparent;");
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
            // qDebug() << "Condition Check - Nepali Day: " << (nepaliDay == currentNepaliDay);
            // qDebug() << "Current Nepali Year: " << currentNepaliYear;
            // qDebug() << "Converted Year from Combo: " << yearCombo->currentText().toInt();
            // qDebug() << "Condition Check - Nepali Year: " << currentNepaliYear << "==" << yearCombo->currentText() << (currentNepaliYear == yearCombo->currentText());
            // qDebug() << "Condition Check - Nepali Month: " << (currentNepaliMonth == monthCombo->currentText());
            // qDebug() << "Final Condition Check: " << (nepaliDay == currentNepaliDay && currentNepaliYear == yearCombo->currentText() && currentNepaliMonth == monthCombo->currentText());

            QLabel *nepaliLabel = new QLabel(nepaliDay);
            QLabel *englishLabel = new QLabel(englishDay);
            if (!nepaliDay.isEmpty())
            {
                if (nepaliDay == currentNepaliDay && currentNepaliYear == yearCombo->currentText() && currentNepaliMonth == monthCombo->currentText())
                {
                    dateButton->setObjectName("currentDateButton");
                    dateButton->setStyleSheet("QPushButton#currentDateButton:hover { color: #FFFFFF; background: qradialgradient(cx: 0.5, cy: 0.5, radius: 1, fx: 0.5, fy: 0.5, stop: 0 #034D66, stop: 0.8 #034D66, stop: 0.79 transparent, stop: 1 transparent);}"
                                              "QPushButton#currentDateButton { border-radius:20px;background-color: #034D66; }");
                    qDebug() << "The Date syncing is done, and today's date stylesheet has been set";
                }
                else
                {
                    dateButton->setObjectName("dateButton");
                    dateButton->setStyleSheet("QPushButton#dateButton:hover {border-radius:20px; color: #FFFFFF; background: qradialgradient(cx: 0.5, cy: 0.5, radius: 1, fx: 0.5, fy: 0.5, stop: 0 #034D66, stop: 0.8 #034D66, stop: 0.79 transparent, stop: 1 transparent);}");
                }

                // Common properties for all dates
                dateButton->setProperty("dateIdentifier", (row - 1) * 7 + col);

                // Connect the button click to the custom slot
                connect(dateButton, &QPushButton::clicked, this, &MainCal::updateData);
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


void MainCal::resizeEvent(QResizeEvent *event)
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
MainCal::date MainCal::convertADtoBS(int EnglishYear, QString EnglishMonth, int EnglishDay)
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
                        qDebug() << "Day matches.";
                        
                        nepaliDate.year = tempNepaliDate[1].toString();
                        nepaliDate.month = months.at(m);
                        nepaliDate.day = dayObject["nepaliDay"].toString();
                        qDebug() << "converted Nepali Date: " << nepaliDate.day << " " << nepaliDate.month << " " << nepaliDate.year;
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
                backward =true;
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
qDebug() << "Value of englishDay: " << dayObject["englishDay"].toString();
                    // Check if current English day matches the day in the JSON data
                    if (dayObject["englishDay"].toString().toInt() == EnglishDay)
                    {
                        
                        nepaliDate.year = tempNepaliDate[1].toString();
                        nepaliDate.month = months.at(m);
                        nepaliDate.day = dayObject["nepaliDay"].toString();
                        return nepaliDate;
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
                forward = true;
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


MainCal::date MainCal::convertBStoAD(date nepaliDate)
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
void MainCal::createSidebar()
{
    sideWidget = new QWidget;
    QVBoxLayout *sideLayout = new QVBoxLayout;
    QStringList englishMonths = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    // Create dayInfo layout and add components to it
    QWidget *dayInfoWidget = new QWidget;
    QVBoxLayout *dayInfo = new QVBoxLayout(dayInfoWidget);
    // Create QLabel objects
    dataLabel = new QLabel;
        eventsLabel =new QLabel;
    holidayLabel = new QLabel;

    tithiLabel = new QLabel;

    // Add QLabel objects to dayInfo
    dayInfo->addWidget(dataLabel);
    dayInfo->addWidget(eventsLabel);
    dayInfo->addWidget(holidayLabel);
    dayInfo->addWidget(tithiLabel);

    dayInfoWidget->setStyleSheet("background-color: #034D66;");
    // Create note input for dayInfo
// Create a QWidget to act as a container
QWidget *containerWidget = new QWidget;

// Create a QHBoxLayout to arrange the QLineEdit and QPushButton
QHBoxLayout *containerLayout = new QHBoxLayout(containerWidget);

// Create the QLineEdit
noteInput = new QLineEdit;

// Create the QPushButton
QPushButton *button = new QPushButton;
button->setText("Add"); 
connect(button, &QPushButton::clicked, this, &MainCal::onButtonClicked);
button->setStyleSheet("background-color: #F3533D; color: white; border: none; padding: 5px;");


// Add the QLineEdit and QPushButton to the layout
containerLayout->addWidget(noteInput);
containerLayout->addWidget(button);

// Add the container widget to the dayInfo layout
dayInfo->addWidget(containerWidget);

    // Create convertDate layout and add components to it
    QWidget *convertDateWidget = new QWidget;
    QVBoxLayout *convertDate = new QVBoxLayout(convertDateWidget);
    QLabel *dateLabel = new QLabel("Convert Date");
    convertDate->addWidget(dateLabel);

    convertModeButton = new QPushButton;
    convertModeButton->setCheckable(true);
    convertModeButton->setText("AD to BS");
    convertModeButton->setStyleSheet("background-color: #F3533D; color: white; border: none; padding: 5px;");
    convertModeButton->setIcon(QIcon("assets/icons/switch.png")); // Replace with the path to your icon
    convertDate->addWidget(convertModeButton);
    // Connect toggled signal to lambda function that updates the button's text


 QWidget *nepaliDatePicker = new QWidget;
    QHBoxLayout *nepaliDateLayout = new QHBoxLayout(nepaliDatePicker);

    // Create day, month, and year spin boxes
    QSpinBox *daySpinBox = new QSpinBox;
    daySpinBox->setRange(1, 32);
    QComboBox *monthComboBox = new QComboBox;
    QSpinBox *yearSpinBox = new QSpinBox;

    // Add spin boxes to layout
    nepaliDateLayout->addWidget(daySpinBox);
    nepaliDateLayout->addWidget(monthComboBox);
    nepaliDateLayout->addWidget(yearSpinBox);
        connect(convertModeButton, &QPushButton::toggled, 
                [englishMonths,daySpinBox ,monthComboBox, yearSpinBox, this](bool checked)
                {
                    if (checked) {
                        convertModeButton->setText("BS to AD");
monthComboBox->clear();
                        monthComboBox->addItems(months); // months is a QStringList of Nepali month names
                        yearSpinBox->setRange(1992, 2099);
                        yearSpinBox->setValue(currentNepaliYear.toInt());
                        monthComboBox->setCurrentIndex(months.indexOf(currentNepaliMonth));
                        daySpinBox->setValue(currentNepaliDay.toInt());
                    } else {
                        convertModeButton->setText("AD to BS");
                        monthComboBox->clear();

                        monthComboBox->addItems(englishMonths); // months is a QStringList of Nepali month names
                        yearSpinBox->setRange(1936, 2042);
                        yearSpinBox->setValue(currentEnglishYear);
                        monthComboBox->setCurrentIndex(englishMonths.indexOf(currentEnglishMonth));
                        daySpinBox->setValue(currentEnglishDay);
                    } 
                });

    // Add Nepali date picker to convertDate layout
    convertDate->addWidget(nepaliDatePicker);
// Declare and create convertButton
QPushButton *convertButton = new QPushButton("Convert");
convertButton->setStyleSheet("background-color: #F3533D; color: white; border: none; padding: 5px;");
// Add convertButton to convertDate layout
convertDate->addWidget(convertButton);
// Declare and create convertResultLabel
QLabel *convertResultLabel = new QLabel;
convertDate->addWidget(convertResultLabel);

    // Connect convertButton's clicked signal to a slot that performs the conversion
    connect(convertButton, &QPushButton::clicked, [this, convertResultLabel, yearSpinBox, monthComboBox, daySpinBox]()
            {
                int year = yearSpinBox->value();
                QString month = monthComboBox->currentText();
                int day = daySpinBox->value();
                QString mode = convertModeButton->text();

                qDebug() << "Year SpinBox Value: " << yearSpinBox->value();
                qDebug() << "Month ComboBox Text: " << monthComboBox->currentText();
                qDebug() << "Day SpinBox Value: " << daySpinBox->value();

                // Perform the conversion
                date temp;
                QString result;
                if (mode == "AD to BS") {
                    qDebug() << "Converting from AD to BS. Year: " << year << " Month: " << month << " Day: " << day;
                    temp = convertADtoBS(year, month, day);
                    gotoDate = temp;
                }
                else {
                    date dateToConvert;
                    
                    dateToConvert.year = QString::number(year);
                    dateToConvert.month = month;
                    dateToConvert.day = QString::number(day);
                    gotoDate=dateToConvert;

                    qDebug() << "Converting from BS to AD. Year: " << dateToConvert.year << " Month: " << dateToConvert.month << " Day: " << dateToConvert.day;
                                        qDebug() << "Converting from BS to AD. Year: " << year << " Month: " <<month << " Day: " <<day;

                    temp = convertBStoAD(dateToConvert);
                    qDebug() << "Converted date. Year: " << temp.year << " Month: " << temp.month << " Day: " << temp.day;
                }
                result=QString("%1/%2/%3").arg(temp.year).arg(temp.month).arg(temp.day);

                // Update the result label
                convertResultLabel->setText(result);
                check=true; 
                
            });
         
            QPushButton *setDateButton = new QPushButton("Set Date");
            convertDate->addWidget(setDateButton);
connect(setDateButton, &QPushButton::clicked, [this]()
{if (check) {
    qDebug() << "gotoDate: " << gotoDate.year << "/" << gotoDate.month << "/" << gotoDate.day;
    int monthIndex = months.indexOf(gotoDate.month);
    qDebug() << "Index of gotoDate.month in months array: " << monthIndex;
    this->setThisDate(gotoDate);
}
    
});
    convertDateWidget->setStyleSheet("background-color:#034D66 ;");

    // Add dayInfo and convertDate to the side layout
    sideLayout->addWidget(dayInfoWidget, 4);
    sideLayout->addWidget(convertDateWidget, 6);

    // Set the side layout on the side widget
    sideWidget->setLayout(sideLayout);

    // Set the background color of the side widget
    sideWidget->setStyleSheet("background-color:transparent;");




}
void MainCal::updateData()
{    // Get the clicked button
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

        clickedDate.year = nepaliDate[1].toString();
        clickedDate.month = nepaliDate[0].toString();
        clickedDate.day = nepaliDay;


        qDebug() << "Clicked Date: Year - " << clickedDate.year << ", Month - " << clickedDate.month << ", Day - " << clickedDate.day;
        // Create the full Nepali and English dates
        QString fullNepaliDate = nepaliDay + " " + nepaliDate[0].toString() + " " + nepaliDate[1].toString();
        bool isSecondEnglishMonth = (nepaliDay.toInt() >= enFirstOrSecond);
        QString fullEnglishDate = englishDay + " " + (isSecondEnglishMonth ? (enEnding[0].toString() + " " + enEnding[1].toString()) : (enBeginning[0].toString() + " " + enBeginning[1].toString()));



    additionalInfo info= showAdditionalInfo(clickedDate);
    dataLabel->setText("Nepali Date: " + fullNepaliDate + "\nEnglish Date: " + fullEnglishDate+"\n");
        eventsLabel->setText("Events:\n" + info.events.join("\n"));
    if(info.holiday.isEmpty())
    {
        holidayLabel->setText("No Occasion today");
    }
    else
    {
        holidayLabel->setText("Occasion: " + info.holiday);
    }
    holidayLabel->setWordWrap(true);
    tithiLabel->setText("Tithi: " + info.tithi);


noteInput->setPlaceholderText("Notes for " + fullNepaliDate);

    }
}
MainCal::additionalInfo MainCal::showAdditionalInfo(date date)
{
    QString dataYear = date.year;
    QString datamonth = date.month;
    QString dataDay = date.day;
    additionalInfo info;
    QString eventDate=clickedDate.year+"-"+clickedDate.month+"-"+clickedDate.day;
    qDebug() << "Date: " << dataYear << "/" << datamonth << "/" << dataDay;

    QString jsonDataFilePath = QString("assets/data/%1/%2.json").arg(dataYear).arg(dataYear);

    qDebug() << "JSON data file path: " << jsonDataFilePath;

    // Open and read JSON file
    QFile jsonDataFile(jsonDataFilePath);
    if (!jsonDataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open JSON file.";

        
    }
    QSqlDatabase mydb = QSqlDatabase::database();

    if(!mydb.open()) {
        qDebug() << "Failed to open the database.";
        //  return;
    }
    else
    {
        qDebug()<<"Database is connected";
    }
    QString note = noteInput->text();//
    QSqlQuery query;
    query.prepare("SELECT note FROM events WHERE date = :eventDate AND userid= :userid");
    query.bindValue(":eventDate", eventDate);
    query.bindValue(":userid",eventUserId);
    query.exec();

    QStringList events;
    while (query.next()) {
        QString note = query.value(0).toString();
        events.append(note);
    }

    // ... existing code ...




    QTextStream addData(&jsonDataFile);
    QString jsonAdditionalData = addData.readAll();
    jsonDataFile.close();

    qDebug() << "JSON Additional Data: " << jsonAdditionalData;

    QJsonObject additionalInfoObject = QJsonDocument::fromJson(jsonAdditionalData.toUtf8()).object();
    QJsonObject reqmonthData    = additionalInfoObject[datamonth].toObject();
    QJsonObject holidayObject   = reqmonthData["holidays"].toObject();
    QJsonObject tithiObject     = reqmonthData["tithi"].toObject();

    qDebug() << "Additional Info Object: " << additionalInfoObject;
    qDebug() << "Requested Month Data: " << reqmonthData;
    qDebug() << "Holiday Object: " << holidayObject;
    qDebug() << "Tithi Object: " << tithiObject;
for (const QString &month : months) {
    if (additionalInfoObject.contains(month)) {
        qDebug() << "additionalInfoObject contains " << month;
    } else {
        qDebug() << "additionalInfoObject does not contain " << month;
    }
}
    bool isEmpty=true;
for (const QJsonValue &value : tithiObject) {
    if (!value.toString().isEmpty()) {
        isEmpty = false;
        break;
    }
}
qDebug() << "dataDay " << dataDay;
qDebug() << "holidayObject " << holidayObject;
qDebug() << "holidayObject.contains(dataDay) " << holidayObject.contains(dataDay);
   QString tempDay = dataDay.length() == 2 ? dataDay : "0" + dataDay;
    if (holidayObject.contains(tempDay))
    {
        info.holiday = holidayObject[tempDay].toString();
    }
    if (tithiObject.contains(dataDay))
    {
        info.tithi = tithiObject[dataDay].toString();
    }
   info.events = events;  // Store events in the additionalInfo structure

  
    if (!isEmpty) {
        qDebug() << "Holiday: " << info.holiday;
        qDebug() << "Tithi: " << info.tithi;

        qDebug() <<"Events: \n" <<info.events;
        return info;
    }





}
void MainCal::initSidebar()
{

   convertModeButton->toggle();
   

        QString fullNepaliDate = currentNepaliDay + " " + currentNepaliMonth + " " + currentNepaliYear;
        QString fullEnglishDate = QString::number(currentEnglishDay) + " " + currentEnglishMonth + " " + QString::number(currentEnglishYear);

        dataLabel->setText("Nepali Date: " + fullNepaliDate + "\nEnglish Date: " + fullEnglishDate);
        noteInput->setPlaceholderText("Notes for " + fullNepaliDate);

}


void MainCal::setThisDate(date dateToSet)
{
    monthCombo->setCurrentIndex(months.indexOf(dateToSet.month));
    yearCombo->setCurrentText(dateToSet.year);
    updateCalendar();

}

void MainCal::onButtonClicked() {
    QString note = noteInput->text();
    QSqlDatabase mydb = QSqlDatabase::database();

    if(!mydb.open()) {
        qDebug() << "Failed to open the database.";
        return;
    }
    else
    {
        qDebug()<<"Database is connected";
    }
    QString
        eventDate=clickedDate.year+"-"+clickedDate.month+"-"+clickedDate.day;
   // qDebug() << "Note for " << eventDate << " is:" << note;
    QSqlQuery query;
    query.prepare("INSERT INTO events (userid,date, note) VALUES (:userid,:eventDate, :note)");
    query.bindValue(":eventDate", eventDate);
    query.bindValue(":note", note);
    query.bindValue(":userid",eventUserId);         //Add it later on//
    if(query.exec()){
        qDebug()<<"Data Inserted Successfully";

      //  this->hide();
    }
    else {
        qDebug() << "Error: " << query.lastError().text();
    }

   query.prepare("SELECT note FROM events WHERE date = :eventDate");
    query.bindValue(":eventDate", eventDate);
   if(query.exec()){
        qDebug()<<"Database is working";
       //this ->hide();
    }        // Execute the SELECT query
else
   {
        qDebug() << "Error: " << query.lastError().text();
   }
    while (query.next()) {
       QString note = query.value(0).toString();
       qDebug() << "Note on " << eventDate << ": " << note;
        //Display the note on the UI or do something else with it
    }
}

void MainCal::previousMonth() {
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

void MainCal::nextMonth() {
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
void MainCal::increaseMonth(int& month, int& year)
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

void MainCal::decreaseMonth(int& month, int& year)
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


