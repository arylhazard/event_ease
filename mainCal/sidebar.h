#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QDebug>
#include <QSpinBox>
#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "mainwindow.h"

void MainWindow::createSidebar()
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

    dayInfoWidget->setStyleSheet("background-color: #FF6347;"); // Tomato color
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
connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
button->setStyleSheet("background-color: #4CAF50; color: white; border: none; padding: 5px;");


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
    convertModeButton->setStyleSheet("background-color: #008CBA; color: white; border: none; padding: 5px;");
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
convertButton->setStyleSheet("background-color: #f44336; color: white; border: none; padding: 5px;");
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
    convertDateWidget->setStyleSheet("background-color: #B974C2;");

    // Add dayInfo and convertDate to the side layout
    sideLayout->addWidget(dayInfoWidget, 4);
    sideLayout->addWidget(convertDateWidget, 6);

    // Set the side layout on the side widget
    sideWidget->setLayout(sideLayout);

    // Set the background color of the side widget
    sideWidget->setStyleSheet("background-color: #0D98BA;");




}
void MainWindow::updateData()
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

    // qDebug() << "Marriage  " << info.marriage;
    // qDebug() << "Bratabandha  " << info.bratabandha;
    // qDebug() << "Holiday  " << info.holiday;
    // qDebug() << "Tithi  " << info.tithi;

noteInput->setPlaceholderText("Notes for " + fullNepaliDate);

    }
}
MainWindow::additionalInfo MainWindow::showAdditionalInfo(date date)
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
    query.prepare("SELECT note FROM events WHERE date = :eventDate");
    query.bindValue(":eventDate", eventDate);
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
void MainWindow::initSidebar()
{

   convertModeButton->toggle();
   

        QString fullNepaliDate = currentNepaliDay + " " + currentNepaliMonth + " " + currentNepaliYear;
        QString fullEnglishDate = QString::number(currentEnglishDay) + " " + currentEnglishMonth + " " + QString::number(currentEnglishYear);

        dataLabel->setText("Nepali Date: " + fullNepaliDate + "\nEnglish Date: " + fullEnglishDate);
        noteInput->setPlaceholderText("Notes for " + fullNepaliDate);

}


void MainWindow::setThisDate(date dateToSet)
{
    monthCombo->setCurrentIndex(months.indexOf(dateToSet.month));
    yearCombo->setCurrentText(dateToSet.year);
    updateCalendar();

}

void MainWindow::onButtonClicked() {
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
    query.prepare("INSERT INTO events (date, note) VALUES (:eventDate, :note)");
    query.bindValue(":eventDate", eventDate);
    query.bindValue(":note", note);
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


#endif // SIDEBAR_H

