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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
 // Function to create the main layout
    void createMainLayout();

    // Function to create the sidebar
    void createSidebar();
public slots:
    // Slots for handling user actions
    void previousMonth();
    void updateData();
    void nextMonth();
    void updateCalendar();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    // Declare QLabel pointer
QLabel *dataLabel; 
QLineEdit *noteInput;
        QString currentNepaliYear;
    QString currentNepaliMonth;
    QString currentNepaliDay;
    bool updateNeeded;
     QVBoxLayout *mainLayout; // Layout for the main content
    QHBoxLayout *totalLayout; // Layout for the entire window
    QWidget *sideWidget;
    QVBoxLayout *sideLayout;
    QCalendarWidget *calendarWidget; // Calendar widget
    QComboBox *monthCombo;           // Combo box for selecting months
    QComboBox *yearCombo;            // Combo box for selecting years
    QJsonObject jsonDataObject;      // JSON data container
    int selectedMonth;                // Currently selected month index
    QJsonObject metadata;            // Metadata for the calendar
    int enFirstOrSecond = -1;         // Flag for tracking English month
    int selectedYear;                 // Currently selected year
    QGridLayout *gridLayout;          // Layout for calendar grid
    QJsonArray days;                  // Array to store day information
    bool dateSyncedOnce=false;   
    struct date {
        QString year;
        QString month;
        QString day;
    };    // Boolean value that can be used to check if syncing algorithm can be skipped
        date convertADtoBS(int currentEnglishYear, QString currentEnglishMonth, int currentEnglishDay);
            date convertBStoAD(date nepaliDate);
                QStringList  months = { "Baisakh", "Jestha", "Asar", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangsir", "Paush", "Magh", "Falgun", "Chaitra" };

};

#endif // MAINWINDOW_H
