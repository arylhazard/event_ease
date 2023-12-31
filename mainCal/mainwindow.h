#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QCalendarWidget>
#include <QComboBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QPushButton>
#include <QtSql>

class MainWindow: public QMainWindow {
    Q_OBJECT

private:     struct date {
        QString year;
        QString month;
        QString day;
    };
    struct additionalInfo {
        QString tithi;
        QString holiday;

        QStringList events;
    };
public:
    MainWindow(QWidget *parent = nullptr);  // Constructor

    void createMainLayout();  // Function to create the main layout
    void createSidebar();     // Function to create the sidebar
    void initSidebar();
    void setThisDate(date);


public slots:
    void previousMonth();     // Slots for handling user actions
    void updateData();
    void nextMonth();
    void updateCalendar();
    void onButtonClicked();


protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *dataLabel;
    QLabel *eventsLabel;
    QLabel *holidayLabel ;
    QLabel *tithiLabel;


    QLineEdit *noteDisplay;
    QLineEdit *noteInput;
    int currentEnglishYear;
    int currentEnglishDay;
    QString currentEnglishMonth;
    QString currentNepaliYear;
    QString currentNepaliMonth;
    QString currentNepaliDay;
    bool updateNeeded;
    QVBoxLayout *mainLayout;  // Layout for the main content
    QHBoxLayout *totalLayout; // Layout for the entire window
    QWidget *sideWidget;
    QVBoxLayout *sideLayout;
    QCalendarWidget *calendarWidget; // Calendar widget
    QComboBox *monthCombo;           // Combo box for selecting months
    QComboBox *yearCombo;            // Combo box for selecting years
    QJsonObject jsonDataObject;      // JSON data container
    int selectedMonth;               // Currently selected month index
    QJsonObject metadata;            // Metadata for the calendar
    int enFirstOrSecond = -1;        // Flag for tracking English month
    int selectedYear;                // Currently selected year
    QGridLayout *gridLayout;         // Layout for calendar grid
    QJsonArray days;                 // Array to store day information
    bool dateSyncedOnce = false;  
    QPushButton *convertModeButton;
    date clickedDate;
QLabel *convertResultLabel;
bool check=false;
    
 


    date gotoDate;
    date convertADtoBS(int currentEnglishYear, QString currentEnglishMonth, int currentEnglishDay);
    date convertBStoAD(date nepaliDate);
    additionalInfo showAdditionalInfo(date);
    void increaseMonth(int& month, int& year);
    void decreaseMonth(int& month, int& year);

    QStringList months = { "Baisakh", "Jestha", "Asadh", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangshir", "Poush", "Magh", "Falgun", "Chaitra" };
};

#endif // MAINWINDOW_H
