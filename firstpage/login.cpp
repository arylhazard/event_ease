#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include "mainwindow.h"

login::login(QWidget *parent, MainWindow* mainWindow) :
    QDialog(parent),
    ui(new Ui::login),
    mainWindow(mainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_back, &QPushButton::clicked, this, &login::on_pushButton_back_clicked);
}


void login::returnToMainWindow()
{
    accept(); // Return QDialog::Accepted result
    if (mainWindow) {
        mainWindow->show(); // Show the main window
    }
}

void login::on_pushButton_back_clicked()
{
    returnToMainWindow(); // Call the returnToMainWindow function
}


login::~login()
{
    delete ui;
}
